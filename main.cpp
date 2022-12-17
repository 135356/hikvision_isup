#include <iostream>
#include <cstring>
#include "bb/Time.h"

#include <stdio.h>
//#include <Windows.h>
#include "hikvision/HCISUPCMS.h"
#include "hikvision/HCISUPStream.h"
//#include "hikvision/plaympeg4.h"

LONG lLoginID = -1;
LONG lLinkHandle = -1;
LONG lRealHandle = -1;
FILE *Videofile = NULL;
//注册回调函数
BOOL CALLBACK RegisterCallBack(LONG lUserID, DWORD dwDataType, void *pOutBuffer, DWORD dwOutLen, void *pInBuffer, DWORD dwInLen, void *pUser){
    if(ENUM_DEV_ON == dwDataType){
        NET_EHOME_DEV_REG_INFO *pDevInfo = (NET_EHOME_DEV_REG_INFO *)pOutBuffer;
        if(pDevInfo != NULL){
            lLoginID = lUserID;
            printf("On-line, lUserID: %d, Device ID: %s\n", lLoginID, pDevInfo->byDeviceID);
        }
        // 输入参数
        NET_EHOME_SERVER_INFO *pServerInfo = (NET_EHOME_SERVER_INFO *)pInBuffer;
        pServerInfo->dwTimeOutCount = 6; //心跳超时次数
        pServerInfo->dwKeepAliveSec = 15; //心跳间隔
    }else if(ENUM_DEV_OFF == dwDataType){
        printf("Off-line, lUserID: %d\n", lUserID);
        NET_ECMS_ForceLogout(lUserID);
    }else if(ENUM_DEV_AUTH == dwDataType){
        // 对于支持 ISUP5.0 的设备认证，必须设置认证密钥
        NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12 *)pOutBuffer;
        // 输出设备信息
        printf("[Device Auth] DeviceID[%s] IP[%s]\n", pDevInfo->struRegInfo.byDeviceID, pDevInfo->struRegInfo.struDevAdd.szIP);
        char szEHomeKey[32] = "13535135356"; // 假设密钥为 i#Rhg&8D5lP
        strcpy((char*)pInBuffer, szEHomeKey); // Set device EhomeKey for authentication
    }else if(ENUM_DEV_SESSIONKEY == dwDataType){
        // 对于支持 ISUP5.0 的设备认证，必须配置 EHomeKey
        NET_EHOME_DEV_REG_INFO_V12 *pDevInfo = (NET_EHOME_DEV_REG_INFO_V12*)pOutBuffer;
        printf("[Device SessionKey] DeviceID[%s]\n", pDevInfo->struRegInfo.byDeviceID);
        NET_EHOME_DEV_SESSIONKEY struSessionkey = {0};
        memcpy(struSessionkey.sDeviceID, pDevInfo->struRegInfo.byDeviceID, MAX_DEVICE_ID_LEN);
        memcpy(struSessionkey.sSessionKey, pDevInfo->struRegInfo.bySessionKey, MAX_MASTER_KEY_LEN);
        NET_ECMS_SetDeviceSessionKey(&struSessionkey);
    }else{
        //...
    }
    return TRUE;
}
//处理实时码流数据
BOOL InputStreamData(BYTE byDataType, char *pBuffer, int iDataLen){
    if(Videofile == NULL){
        Videofile = fopen("Test.mp4", "wb");
        printf("Save data to file: Test.mp4!\n");
    }
    if(Videofile != NULL){
        fwrite(pBuffer, iDataLen, 1, Videofile); // 回调实时码流并保存视频文件
    }
    // 调用播放库解码并显示码流实现预览
    /* if(1 == byDataType){
        if(!PlayM4_GetPort(&m_lPort)){
            return FALSE;
        }
    if(!PlayM4_SetStreamOpenMode(m_lPort, STREAME_REALTIME)){
        return FALSE;
    }
    // 输入头部的前 40 字节
    if(!PlayM4_OpenStream(m_lPort, (unsigned char *)pBuffer, (DWORD)iDataLen, 2 * 1024 * 1024)){
        return FALSE;
    }
    if(!PlayM4_Play(m_lPort, hWnd)){
        return FALSE;
    }
    }else{
        for(int i = 0; i < 1000; i++){
            BOOL bRet = PlayM4_InputData(m_lPort, (unsigned char *)pBuffer, (DWORD)iDataLen);
            if(!bRet){
                if(i >= 999){
                    printf("PlayM4_InputData failed, error code: %d!", PlayM4_GetLastError(m_lPort));
                }
                bb::Time::sleep(0.002);
                //Sleep(2);
            }else{
                break;
            }
        }
    } */
    return TRUE;
}

//注册实时码流回调函数
void CALLBACK fnPREVIEW_DATA_CB(LONG lPreviewHandle, NET_EHOME_PREVIEW_CB_MSG * pPreviewCBMsg, void *pUserData){
    if(NULL == pPreviewCBMsg){
        return;
    }
    lRealHandle = lPreviewHandle;
    InputStreamData(pPreviewCBMsg->byDataType, (char *)pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen);
}

//注册预览请求的响应回调函数
BOOL CALLBACK fnPREVIEW_NEWLINK_CB(LONG lPreviewHandle, NET_EHOME_NEWLINK_CB_MSG * pNewLinkCBMsg, void *pUserData){
    lLinkHandle = lPreviewHandle;
    printf("Callback of preview listening, Device ID: %s, Channel: %d\n", pNewLinkCBMsg->szDeviceID, pNewLinkCBMsg->dwChannelNo);
    // 预览数据的回调参数
    NET_EHOME_PREVIEW_DATA_CB_PARAM struDataCB = {0};
    struDataCB.fnPreviewDataCB = fnPREVIEW_DATA_CB;
    struDataCB.byStreamFormat = 0; // 封装格式:0-PS 格式
    if(!NET_ESTREAM_SetPreviewDataCB(lPreviewHandle, &struDataCB)){
        printf("NET_ESTREAM_SetPreviewDataCB failed, error code: %d\n", NET_ESTREAM_GetLastError());
        return FALSE;
    }
    printf("NET_ESTREAM_SetPreviewDataCB!\n");
    return TRUE;
}

//设置异常回调
void CALLBACK StreamExceptionCallback(DWORD dwType, LONG iUserID, LONG iHandle, void *pUser){
    if(EHOME_PREVIEW_EXCEPTION == dwType){
        // 预览异常
        //printf("Preview exception, handle=%d, Error:%d", iHandle, dwError);
        printf("Preview exception, handle=%d\n", iHandle);
    }else if(EHOME_PLAYBACK_EXCEPTION == dwType){
        // 回放异常
        //printf("Playback exception, handle=%d, Error:%d", iHandle, dwError);
        printf("Playback exception, handle=%d\n", iHandle);
    }else if (EHOME_AUDIOTALK_EXCEPTION == dwType){
        // 语音对讲(转发)异常
        //printf("Stream VoiceTalk exception, handle=%d, Error:%d", iHandle, dwError);
        printf("Stream VoiceTalk exception, handle=%d\n", iHandle);
    }
}

int main(int, char **){
    NET_ESTREAM_SetExceptionCallBack(0, 0, StreamExceptionCallback, NULL); //设置异常回调
    // SMS 在监听服务开启后获取码流
    // 初始化 SMS 库
    NET_ESTREAM_Init();
    // 预览的监听参数
    NET_EHOME_LISTEN_PREVIEW_CFG struListen = {0};
    memcpy(struListen.struIPAdress.szIP, "192.168.31.181", sizeof("192.168.31.181"));
    struListen.struIPAdress.wPort = 8003; // SMS 的监听端口号
    struListen.fnNewLinkCB = fnPREVIEW_NEWLINK_CB; //预览请求回调函数
    struListen.pUser = NULL;
    struListen.byLinkMode = 1; // 0-TCP, 1-UDP
    // 开启监听服务
    LONG lHandle = NET_ESTREAM_StartListenPreview(&struListen);
    if(lHandle < -1){
        printf("NET_ESTREAM_StartListenPreview failed, error code: %d\n", NET_ESTREAM_GetLastError());
        NET_ESTREAM_Fini();
        return -1;
    }
    printf("NET_ESTREAM_StartListenPreview!\n");

    // 注册和预览请求
    // 初始化 CMS 库 NET_ECMS_Init();
    // 注册的监听参数
    NET_EHOME_CMS_LISTEN_PARAM struCMSListenPara = {0};
    memcpy(struCMSListenPara.struAddress.szIP, "0.0.0.0", sizeof("0.0.0.0"));
    struCMSListenPara.struAddress.wPort = 7660;
    struCMSListenPara.fnCB = RegisterCallBack;
    // 开启监听并接收设备注册信息
    LONG lListen = NET_ECMS_StartListen(&struCMSListenPara);
    if(lListen < -1){
        printf("NET_ECMS_StartListen failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }
    printf("NET_ECMS_StartListen!\n");
    while (1){
        bb::Time::sleep(1);
        //Sleep(1000); // The following operations should be done when theregistration is completed
        if(lLoginID >= 0){
            break;
        }
    }
    // 预览请求的输入参数
    NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = {0};
    struPreviewIn.iChannel = 1; // 通道号
    struPreviewIn.dwLinkMode = 1; // 0-TCP, 1-UDP
    struPreviewIn.dwStreamType = 0; //码流类型:0-主码流，1-子码流 2-第三码流
    memcpy(struPreviewIn.struStreamSever.szIP, "192.168.31.181", sizeof("192.168.31.181")); //SMS 的 IP 地址
    struPreviewIn.struStreamSever.wPort = 8003; // SMS 的端口号，需和监听端口号一致
    // 预览请求的输出参数
    NET_EHOME_PREVIEWINFO_OUT struPreviewOut = {0};
    // 预览请求
    if (!NET_ECMS_StartGetRealStreamV11(lLoginID, &struPreviewIn, &struPreviewOut)){
        printf("NET_ECMS_StartGetRealStreamV11 failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }
    printf("NET_ECMS_StartGetRealStreamV11!\n");
    // 码流传输请求的输入参数
    NET_EHOME_PUSHSTREAM_IN struPushStreamIn = {0};
    struPushStreamIn.dwSize = sizeof(struPushStreamIn);
    struPushStreamIn.lSessionID = struPreviewOut.lSessionID; // 预览请求的会话 ID
    // 码流传输请求的输出参数
    NET_EHOME_PUSHSTREAM_OUT struPushStreamOut = {0};
    // 发送请求给设备并开始传输实时码流
    if (!NET_ECMS_StartPushRealStream(lLoginID, &struPushStreamIn, &struPushStreamOut)){
        printf("NET_ECMS_StartPushRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        NET_ECMS_Fini();
        return -1;
    }
    printf("NET_ECMS_StartPushRealStream!\n");
    bb::Time::sleep(50);
    //Sleep(50000);
    //登出
    // 释放被 CMS 预览请求占用的资源
    if(!NET_ECMS_StopGetRealStream(lLoginID, struPreviewOut.lSessionID)){
        printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
    }
    // CMS 停止监听服务
    if(!NET_ECMS_StopListen(lListen)) {
        printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
    }
    // 释放被 CMS 占用的资源
    NET_ECMS_Fini();
    // SMS 停止转发码流
    if(lRealHandle >= 0){
        if (!NET_ESTREAM_StopPreview(lRealHandle)){
            printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
        }
    }
    // SMS 停止监听服务
    if(lHandle >= 0){
        if(!NET_ESTREAM_StopListenPreview(lHandle)){
            printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
        }
    }
    // 释放被 SMS 占用的资源
    NET_ESTREAM_Fini();
    // 释放文件资源
    if(Videofile != NULL) {
        fclose(Videofile);
        Videofile = NULL;
    }
    printf("Exit!\n");

    return 0;
}