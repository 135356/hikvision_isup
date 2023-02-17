
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include "bb/Time.h"
#include "hikvision/HCISUPCMS.h"
#include "hikvision/HCISUPStream.h"
#include "hikvision/HCISUPAlarm.h"

LONG lLoginID = -1;

LONG lRealHandle = -1;
FILE *Videofile = NULL;
int lTransHandle = -1;

//注册回调函数
BOOL CALLBACK RegisterCallBack(LONG lUserID, DWORD dwDataType, void *pOutBuffer, DWORD dwOutLen, void *pInBuffer, DWORD dwInLen, void *pUser){
    std::cout<<"Type: "<<dwDataType<<std::endl<<std::endl<<std::endl;

    if(dwDataType == ENUM_DEV_AUTH){ //密钥输入
        memcpy(pInBuffer, "abc123456", 32);
    }else{
        //不需要验证的情况
        if(dwDataType == ENUM_DEV_DAS_EHOMEKEY_ERROR){
            perror("注册失败！");
        }else if(dwDataType == ENUM_DEV_SESSIONKEY_REQ){
            perror("注册成功！");
        }else{
            //需要验证
            if(dwDataType == ENUM_DEV_SESSIONKEY){ //Sessionkey回调
                NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12 *)pOutBuffer;
                NET_EHOME_DEV_SESSIONKEY devSessionkey = { 0 };
                memcpy(devSessionkey.sDeviceID, pDevInfo->struRegInfo.byDeviceID, MAX_DEVICE_ID_LEN);
                memcpy(devSessionkey.sSessionKey, pDevInfo->struRegInfo.bySessionKey, MAX_MASTER_KEY_LEN);

                char szSessionKey[17] = { 0 };
                memcpy(szSessionKey, devSessionkey.sSessionKey, MAX_MASTER_KEY_LEN);
                
                NET_ECMS_SetDeviceSessionKey(&devSessionkey);
                NET_EALARM_SetDeviceSessionKey(&devSessionkey);
            }else if(dwDataType == ENUM_DEV_DAS_REQ){ //认证完成之后，设备发送重定向请求，这里的IP是CMS注册服务器的IP、端口。如果设备很多，有多个注册服务器，这里就可以配置设备注册到另外一台服务器
                //在注册期间，设备请求获取 DAS 信息
                char szDASIP[128] = "39.96.177.4"; //DAS IP address
                DWORD dwPort = 7660; //DAS port No.
                sprintf((char*)pInBuffer, "{\"Type\":\"DAS\",\"DasInfo\":{\"Address\": \"%s\",\"Domain\":\"test.ys7.com\",\"ServerID\":\"das_%s_%d\",\"Port\": %d,\"UdpPort\":%d}}", szDASIP, szDASIP, dwPort, dwPort, dwPort);
            }else if(dwDataType == ENUM_DEV_ON){ //设备成功注册
                NET_EHOME_DEV_REG_INFO *pDevInfo = (NET_EHOME_DEV_REG_INFO *)pOutBuffer;
                printf("dev IP:%s\n", pDevInfo->struDevAdd.szIP);
                if(pDevInfo != NULL){
                    lLoginID = lUserID;
                    printf("On-line, lUserID: %d, Device ID: %s\n", lLoginID, pDevInfo->byDeviceID);
                }
                //输入参数
                NET_EHOME_SERVER_INFO *pServerInfo = (NET_EHOME_SERVER_INFO *)pInBuffer;
                //pServerInfo->dwTimeOutCount = 6; //心跳超时次数
                //pServerInfo->dwKeepAliveSec = 15; //心跳间隔

                /* //设置报警服务器的 IP 地址
                pServerInfo->dwAlarmServerType = 1; //two alarm server types are supported: TCP and UDP
                //设置 TCP 报警服务器的地址
                strcpy(pServerInfo->struTCPAlarmSever.szIP, "39.96.177.4");
                pServerInfo->struTCPAlarmSever.wPort = 7332;
                //设置 UDP 报警服务器的地址
                strcpy(pServerInfo->struUDPAlarmSever.szIP, "39.96.177.4");
                pServerInfo->struUDPAlarmSever.wPort = 7332; */
            }else if(dwDataType == ENUM_DEV_OFF){ //设备掉线
                printf("设备掉线 Off-line, lUserID: %d\n", lUserID);
                NET_ECMS_ForceLogout(lUserID);
            }else if(dwDataType == ENUM_DEV_ADDRESS_CHANGED){
                //设备 IP 地址变化(比如，当设备在移动网络中或跨基站时)
                NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12 *)pOutBuffer;
                //输出设备信息
                printf("设备在移动网络中或跨基站 [Device IP Changed] DeviceID[%s] New IP[%s]\n", pDevInfo->struRegInfo.byDeviceID, pDevInfo->struRegInfo.struDevAdd.szIP);
            }else if(dwDataType == ENUM_DEV_DAS_REREGISTER){
                //当设备信息发生变化时，重新注册已注册的设备
                NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12 *)pOutBuffer;
                //输出设备信息
                printf("重新注册已注册的设备 [Device ReRegister] DeviceID[%s] IP[%s]\n", pDevInfo->struRegInfo.byDeviceID, pDevInfo->struRegInfo.struDevAdd.szIP);
            }else{
                std::cout<<"其它状态 dwDataType: "<<dwDataType<<std::endl;
            }
        }   
    }
    
    return TRUE;
}

//实时流数据回调函数
void CALLBACK fnPREVIEW_DATA_CB(LONG lPreviewHandle, NET_EHOME_PREVIEW_CB_MSG *pPreviewCBMsg, void *pUserData){
    if(pPreviewCBMsg == NULL){
        return ;
    }
    if(pPreviewCBMsg->byDataType == 1){
        if(Videofile == NULL){
            Videofile = fopen("./record/Test.mp4", "wb");
            fwrite(pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, 1, Videofile);
            std::cout<<"数据保存到文件 Save data to file:"<<"./record/Test.mp4"<<std::endl;
        }
        printf("HIK流标头信息长度 HIK stream header info length: %d\n", pPreviewCBMsg->dwDataLen);
    }else if(pPreviewCBMsg->byDataType == 2){
        fwrite(pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, 1, Videofile);
        std::cout<<"获取流数据 get stream data:"<<pPreviewCBMsg->dwDataLen<<std::endl;
    }
}

//VTDU预览请求回应回调函数
BOOL CALLBACK fnPREVIEW_NEWLINK_CB(LONG lPreviewHandle, NET_EHOME_NEWLINK_CB_MSG *pNewLinkCBMsg, void *pUserData){
    //LONG lLinkHandle = lPreviewHandle;
    printf("Callback of preview listening, Device ID: %s, Channel: %d\n", pNewLinkCBMsg->szDeviceID, pNewLinkCBMsg->dwChannelNo);

    //预览数据回调参数
    NET_EHOME_PREVIEW_DATA_CB_PARAM struDataCB = { 0 };
    struDataCB.fnPreviewDataCB = fnPREVIEW_DATA_CB;
    struDataCB.byStreamFormat = 0;//封装格式：0- PS 

    if(!NET_ESTREAM_SetPreviewDataCB(lPreviewHandle, &struDataCB)){
        printf("NET_ESTREAM_SetPreviewDataCB failed, error code: %d\n", NET_ESTREAM_GetLastError());
        return FALSE;
    }
    printf("NET_ESTREAM_SetPreviewDataCB!\n");

    return TRUE;
}

int main(){
    //日志文件目录
    char log_file[] = "./record/";
    //CMS注册模块初始化
    NET_ECMS_Init();
    //日志
    NET_ECMS_SetLogToFile(3, log_file, false);
    //注册监听参数
    NET_EHOME_CMS_LISTEN_PARAM struCMSListenPara = { 0 };
    memcpy(struCMSListenPara.struAddress.szIP, "0.0.0.0", sizeof("0.0.0.0"));
    struCMSListenPara.struAddress.wPort = 7660;
    struCMSListenPara.fnCB = RegisterCallBack;

    //启动监听，接收设备注册信息
    LONG lListen = NET_ECMS_StartListen(&struCMSListenPara);
    if(lListen < -1){
        printf("NET_ECMS_StartListen failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }

    printf("NET_ECMS_StartListen!\n");

    while(1){
        bb::Time::sleep(2); //注册成功之后再做后续操作
        if(lLoginID >= 0){
            break;
        }
    }

    std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    //流媒体服务器(VTDU)监听取流

    //取流库初始化
	NET_ESTREAM_Init();
    //日志
    NET_ESTREAM_SetLogToFile(3, log_file, FALSE);

    //预览监听参数
    NET_EHOME_LISTEN_PREVIEW_CFG struListen = { 0 };
    memcpy(struListen.struIPAdress.szIP, "172.26.118.120", sizeof("172.26.118.120"));
    struListen.struIPAdress.wPort = 8003; //流媒体服务器监听端口
    struListen.fnNewLinkCB = fnPREVIEW_NEWLINK_CB; //预览连接请求回调函数
    struListen.pUser = NULL;
    struListen.byLinkMode = 0; //0- TCP方式，1- UDP方式 

    //启动预览监听
    LONG lHandle = NET_ESTREAM_StartListenPreview(&struListen);
    if(lHandle < -1){
        printf("NET_ESTREAM_StartListenPreview failed, error code: %d\n", NET_ESTREAM_GetLastError());
        NET_ESTREAM_Fini();
        return -1;
    }
    printf("NET_ESTREAM_StartListenPreview!\n");
	printf("NET_ESTREAM_StartListenPreview ip:%s\n", struListen.struIPAdress.szIP);



    //预览请求输入参数
    NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = { 0 };
    struPreviewIn.iChannel = 1; //通道号
    struPreviewIn.dwLinkMode = 0; //0- TCP方式，1- UDP方式 
    struPreviewIn.dwStreamType = 0; //码流类型：0- 主码流，1- 子码流, 2- 第三码流
    memcpy(struPreviewIn.struStreamSever.szIP, "39.96.177.4", sizeof("39.96.177.4"));//流媒体服务器IP地址
    struPreviewIn.struStreamSever.wPort = 8003; //流媒体服务器端口，需要跟服务器启动监听端口一致

    //预览请求输出参数
    NET_EHOME_PREVIEWINFO_OUT struPreviewOut = { 0 };

    //预览请求
    if(!NET_ECMS_StartGetRealStreamV11(lLoginID, &struPreviewIn, &struPreviewOut)){
        printf("NET_ECMS_StartGetRealStreamV11 failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }
    printf("NET_ECMS_StartGetRealStreamV11!\n");

    //预览请求推流输入参数 
    NET_EHOME_PUSHSTREAM_IN struPushStreamIn = { 0 };
    struPushStreamIn.dwSize = sizeof(struPushStreamIn);
    struPushStreamIn.lSessionID = struPreviewOut.lSessionID; //SessionID，预览请求会话ID

    //预览请求推流输出参数 
    NET_EHOME_PUSHSTREAM_OUT struPushStreamOut = { 0 };

    //向设备发送命令请求开始发送实时码流，EHOME协议版本大于等于4.0的设备支持
    if(!NET_ECMS_StartPushRealStream(lLoginID, &struPushStreamIn, &struPushStreamOut)){
        printf("NET_ECMS_StartPushRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }
    printf("NET_ECMS_StartPushRealStream!\n");

    bb::Time::sleep(10);

    /* 退出 */
    //释放CMS预览请求资源
    if(!NET_ECMS_StopGetRealStream(lLoginID, struPreviewOut.lSessionID)){
        printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
    }

    //CMS停止监听
    if(!NET_ECMS_StopListen(lListen)){
        printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
    }

    //SIMPLERTMP_DestroyHandle(lTransHandle);

    //释放文件资源
    if(Videofile != NULL){
        fclose(Videofile);
        Videofile = NULL;
    }


    //SIMPLERTMP_Fini();

    //VTDU停止预览
    if(lRealHandle >= 0){
        if(!NET_ESTREAM_StopPreview(lRealHandle)){
            printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
        }
    }

    //VTDU停止预览监听
    if(lHandle >= 0){
        if(!NET_ESTREAM_StopListenPreview(lHandle)){
            printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
        }
    }
    //取流库反初始化，释放资源
    NET_ESTREAM_Fini();
    //CMS库反初始化，释放资源
    NET_ECMS_Fini();

    //RTMP264_Destory();
    printf("Exit!\n");
}