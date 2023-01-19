#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "hikvision/HCISUPCMS.h"
#include "hikvision/HCISUPStream.h"
#include "hikvision/HCISUPAlarm.h"

LONG lLoginID = -1;
LONG lLinkHandle = -1;
LONG lRealHandle = -1;
FILE *Videofile = NULL;
int lTransHandle = -1;

//注册回调函数
BOOL CALLBACK RegisterCallBack(LONG lUserID, DWORD dwDataType, void *pOutBuffer, DWORD dwOutLen, void *pInBuffer, DWORD dwInLen, void *pUser){
    if(ENUM_DEV_ON == dwDataType){
        NET_EHOME_DEV_REG_INFO *pDevInfo = (NET_EHOME_DEV_REG_INFO *)pOutBuffer;

        printf("dev IP:%s\n", pDevInfo->struDevAdd.szIP);

        if(pDevInfo != NULL){
            lLoginID = lUserID;
            printf("On-line, lUserID: %d, Device ID: %s\n", lLoginID, pDevInfo->byDeviceID);
        }
        //输入参数
        NET_EHOME_SERVER_INFO *pServerInfo = (NET_EHOME_SERVER_INFO *)pInBuffer;
        pServerInfo->dwTimeOutCount = 6; //心跳超时次数
        pServerInfo->dwKeepAliveSec = 15; //心跳间隔
    }else if(ENUM_DEV_OFF == dwDataType){
        printf("Off-line, lUserID: %d\n", lUserID);
        NET_ECMS_ForceLogout(lUserID);
    }else if(ENUM_DEV_AUTH == dwDataType){
       //密码校验
        memcpy(pInBuffer, "123456", 32);	
    }else if(ENUM_DEV_SESSIONKEY == dwDataType){
        NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12 *)pOutBuffer;
        NET_EHOME_DEV_SESSIONKEY devSessionkey = { 0 };
        memcpy(devSessionkey.sDeviceID, pDevInfo->struRegInfo.byDeviceID, MAX_DEVICE_ID_LEN);
        memcpy(devSessionkey.sSessionKey, pDevInfo->struRegInfo.bySessionKey, MAX_MASTER_KEY_LEN);

        char szSessionKey[17] = { 0 };
        memcpy(szSessionKey, devSessionkey.sSessionKey, MAX_MASTER_KEY_LEN);
        
        NET_ECMS_SetDeviceSessionKey(&devSessionkey);
        NET_EALARM_SetDeviceSessionKey(&devSessionkey);
    }else if(ENUM_DEV_DAS_REQ == dwDataType){
        sprintf((char*)pInBuffer, "{\"Type\":\"DAS\",\"DasInfo\":{\"Address\":\"192.168.10.103\","
            "\"Domain\":\"\",\"ServerID\":\"\",\"Port\":7663,\"UdpPort\":7663}}");
    }else{}

    return TRUE;
}

//实时流数据回调函数
void CALLBACK fnPREVIEW_DATA_CB(LONG lPreviewHandle, NET_EHOME_PREVIEW_CB_MSG *pPreviewCBMsg, void *pUserData){
    if(NULL == pPreviewCBMsg){
        return;
    }
    if(pPreviewCBMsg->byDataType == 1){
        if(Videofile == NULL){
            Videofile = fopen("./record/Test.mp4", "wb");
			fwrite(pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, 1, Videofile);
            printf("Save data to file: Test.mp4!\n");
        }
        printf("HIK stream header info length: %d\n", pPreviewCBMsg->dwDataLen);
        //lTransHandle = SIMPLERTMP_CreatHandle(SIMPLE_TYPE_FLV, (unsigned char*)pPreviewCBMsg->pRecvdata, NULL);
        //if (lTransHandle < 0)
        //{
        //    printf("Ctreat handle errcode: %x", SIMPLERTMP_GetLastError());
        //}
        //else
        //{
        //    printf("Ctreat handle success!\n");
        //}
    }else if(pPreviewCBMsg->byDataType == 2){
        printf("get stream data:%d\n", pPreviewCBMsg->dwDataLen);
		fwrite(pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, 1, Videofile);
        //printf("pBuffer[0]:%x\t%x\t%x\t%x\n", pBuffer[0], pBuffer[1], pBuffer[2], pBuffer[3]);
        //PushH264ToBuffer(lRealHandle, pBuffer, iDataLen);
        //boolean bRet = SIMPLERTMP_InputData(lTransHandle, (unsigned char*)pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen);
        //if (bRet)
        //    printf("input data success!\n");
        //else
        //    printf("input data errcode: %x", SIMPLERTMP_GetLastError());
    }
}

//VTDU预览请求回应回调函数
BOOL CALLBACK fnPREVIEW_NEWLINK_CB(LONG lPreviewHandle, NET_EHOME_NEWLINK_CB_MSG *pNewLinkCBMsg, void *pUserData){
    lLinkHandle = lPreviewHandle;
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
    //流媒体服务器(VTDU)监听取流

    //取流库初始化
	NET_ESTREAM_Init();
    //char cryptoPath[2048] = {0};
    //sprintf(cryptoPath, "/mnt/hgfs/Ubuntu_share/ISUPLinuxC++/libcrypto.so");
    //NET_ESTREAM_SetSDKInitCfg(NET_EHOME_ESTREAM_INIT_CFG_LIBEAY_PATH, cryptoPath);
    //NET_ESTREAM_SetSDKInitCfg(NET_EHOME_ESTREAM_INIT_CFG_LIBEAY_PATH, (void *)"/mnt/hgfs/Ubuntu_share/ISUPLinuxC++/libcrypto.so"); 

    //char sslPath[2048] = {0};
    //sprintf(sslPath, "/mnt/hgfs/Ubuntu_share/ISUPLinuxC++/libssl.so");
    //NET_ESTREAM_SetSDKInitCfg(NET_EHOME_ESTREAM_INIT_CFG_SSLEAY_PATH, sslPath);
    //NET_ESTREAM_SetSDKInitCfg(NET_EHOME_ESTREAM_INIT_CFG_SSLEAY_PATH, (void *)"/mnt/hgfs/Ubuntu_share/ISUPLinuxC++/libssl.so"); 

    char log_file[] = "./record/";
    NET_ESTREAM_SetLogToFile(3, log_file, FALSE);

    //预览监听参数
    NET_EHOME_LISTEN_PREVIEW_CFG struListen = { 0 };
    memcpy(struListen.struIPAdress.szIP, "192.168.10.103", sizeof("192.168.10.103"));
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
    //CMS注册和预览请求

    //CMS注册模块初始化
    NET_ECMS_Init();
    NET_ECMS_SetLogToFile(3, log_file, false);
    //注册监听参数
    NET_EHOME_CMS_LISTEN_PARAM struCMSListenPara = { 0 };
    memcpy(struCMSListenPara.struAddress.szIP, "192.168.10.103", sizeof("192.168.10.103"));
    struCMSListenPara.struAddress.wPort = 7663;
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

    //预览请求输入参数
    NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = { 0 };
    struPreviewIn.iChannel = 1; //通道号
    struPreviewIn.dwLinkMode = 0; //0- TCP方式，1- UDP方式 
    struPreviewIn.dwStreamType = 0; //码流类型：0- 主码流，1- 子码流, 2- 第三码流
    memcpy(struPreviewIn.struStreamSever.szIP, "192.168.10.103", sizeof("192.168.10.103"));//流媒体服务器IP地址
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