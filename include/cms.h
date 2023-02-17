#include "public.h"

namespace isup{
    long user_id = -1; //设备用户的id
    long monitor_state = -1; //监听状态
    std::string dev_id{}; //设备的id
    std::string dev_ip{}; //设备的ip

    //注册回调函数
    BOOL CALLBACK RegisterCallBack(LONG lUserID, DWORD dwDataType, void *pOutBuffer, DWORD dwOutLen, void *pInBuffer, DWORD dwInLen, void *pUser){
        std::cout<<"Type: "<<dwDataType<<std::endl<<std::endl<<std::endl;

        if(dwDataType == ENUM_DEV_AUTH){ //密钥输入
            //memcpy(pInBuffer, home_key, 32);
            strcpy((char*)pInBuffer, home_key); //Set device EhomeKey forauthentication
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
                    //char szDASIP[128] = "39.96.177.4"; //DAS IP address
                    DWORD dwPort = 7660; //DAS port No.
                    sprintf((char*)pInBuffer, "{\"Type\":\"DAS\",\"DasInfo\":{\"Address\": \"%s\",\"Domain\":\"test.ys7.com\",\"ServerID\":\"das_%s_%d\",\"Port\": %d,\"UdpPort\":%d}}", serve_w_ip, serve_w_ip, dwPort, dwPort, dwPort);
                }else if(dwDataType == ENUM_DEV_ON){ //设备成功注册
                    NET_EHOME_DEV_REG_INFO *pDevInfo = (NET_EHOME_DEV_REG_INFO *)pOutBuffer;
                    if(pDevInfo != NULL){
                        user_id = lUserID;
                        dev_id = (char *)pDevInfo->byDeviceID;
                        dev_ip = pDevInfo->struDevAdd.szIP;
                        printf("On-line, lUserID: %d, Device ID: %s, dev IP: %s, \n", user_id, pDevInfo->byDeviceID, pDevInfo->struDevAdd.szIP);
                    }
                    //输入参数
                    NET_EHOME_SERVER_INFO *pServerInfo = (NET_EHOME_SERVER_INFO *)pInBuffer;
                    pServerInfo->dwTimeOutCount = 6; //心跳超时次数
                    pServerInfo->dwKeepAliveSec = 15; //心跳间隔

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

    //cms监听设备注册
    int logOn(){
        //CMS注册模块初始化
        NET_ECMS_Init();
        //日志
        NET_ECMS_SetLogToFile(3, log_dir, false);
        //注册监听参数
        NET_EHOME_CMS_LISTEN_PARAM struCMSListenPara = { 0 };
        memcpy(struCMSListenPara.struAddress.szIP, "0.0.0.0", sizeof("0.0.0.0"));
        struCMSListenPara.struAddress.wPort = 7660;
        struCMSListenPara.fnCB = RegisterCallBack;

        //启动监听，接收设备注册信息
        LONG monitor_state = NET_ECMS_StartListen(&struCMSListenPara);
        if(monitor_state < -1){
            printf("cms监听失败 NET_ECMS_StartListen failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }

        printf("NET_ECMS_StartListen!\n");

        //注册成功之后再做后续操作
        while(1){
            bb::Time::sleep(2);
            if(user_id > -1){
                break;
            }
        }

        return 0;
    }
}


