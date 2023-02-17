#include "cms.h"

namespace isup{
    FILE *video_fp{}; //视频文件
    long preview_handle{}; //预览句柄
    long link_handle{}; //连接句柄

    //处理实时码流数据
    BOOL InputStreamData(BYTE byDataType, char* pBuffer, int iDataLen){
        if(!video_fp){
            video_fp = fopen(video_path,"wb");
            std::cout<<"数据将保存到:"<<video_path<<std::endl;
        }
        if(video_fp){
            fwrite(pBuffer,iDataLen,1,video_fp);
        }else{
            return false;
        }

        //调用播放库解码并显示码流实现预览
        if(byDataType == 1){
        }else{
        }
        return TRUE;
    }

    //注册回放码流回调函数
    void CALLBACK fnPREVIEW_DATA_CB(LONG lPreviewHandle, NET_EHOME_PREVIEW_CB_MSG *pPreviewCBMsg, void *pUserData){
        if(pPreviewCBMsg == NULL){
            return ;
        }
        preview_handle = lPreviewHandle;
        InputStreamData(pPreviewCBMsg->byDataType, (char*)pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen);
    }

    //注册回访请求的响应回调函数
    BOOL CALLBACK fnPREVIEW_NEWLINK_CB(LONG lPreviewHandle, NET_EHOME_NEWLINK_CB_MSG *pNewLinkCBMsg, void *pUserData){
        link_handle = lPreviewHandle;
        std::cout<<"预览回调, Device ID:"<<pNewLinkCBMsg->szDeviceID<<','<<"Channel:"<<pNewLinkCBMsg->dwChannelNo<<std::endl;

        //预览数据的回调参数
        NET_EHOME_PREVIEW_DATA_CB_PARAM struDataCB = {0};
        struDataCB.fnPreviewDataCB = fnPREVIEW_DATA_CB;
        struDataCB.byStreamFormat = 0;//封装格式:0-PS 格式
        if(!NET_ESTREAM_SetPreviewDataCB(lPreviewHandle, &struDataCB)){
            printf("预览回调失败, error code: %d\n", NET_ESTREAM_GetLastError());
            return FALSE;
        }
        printf("预览回调成功\n");
        return TRUE;
    }

    //流媒体服务器(VTDU)监听取流
    int videoStream(){
        /* cms监听 */
        //logOn();

        /* 判断是否支持预览 */
        //NET_ECMS_XMLConfig 和 GetDevAbility

        /* 开启 SMS 监听服务并接收来自设备的连接请求 */
        NET_ESTREAM_Init(); //取流库初始化
        NET_ESTREAM_SetLogToFile(3, log_dir, FALSE); //日志
        //预览的监听参数
        NET_EHOME_LISTEN_PREVIEW_CFG struListen = {0};
        memcpy(struListen.struIPAdress.szIP,serve_l_ip, sizeof(serve_l_ip));
        struListen.struIPAdress.wPort = 8003; //流媒体服务器监听端口
        struListen.fnNewLinkCB = fnPREVIEW_NEWLINK_CB; //预览请求回调函数，用于接收来自设备的实时流
        struListen.pUser = NULL;
        struListen.byLinkMode = 1; //0-TCP, 1-UDP
        //开启监听服务
        LONG lHandle = NET_ESTREAM_StartListenPreview(&struListen);
        //NET_ESTREAM_SetExceptionCallBack //为 SMS 注册异常回调函数
        if(lHandle < -1){
            printf("NET_ESTREAM_StartListenPreview failed, error code: %d\n", NET_ESTREAM_GetLastError());
            NET_ESTREAM_Fini();
            return -1;
        }
        printf("NET_ESTREAM_StartListenPreview!\n");

        /* 将预览开始请求从 CMS 发送给设备 */
        NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = { 0 };
        struPreviewIn.iChannel = 1; //通道号
        struPreviewIn.dwLinkMode = 0; //0- TCP方式，1- UDP方式 
        struPreviewIn.dwStreamType = 0; //码流类型：0- 主码流，1- 子码流, 2- 第三码流
        memcpy(struPreviewIn.struStreamSever.szIP, serve_w_ip, sizeof(serve_w_ip));//流媒体服务器IP地址
        struPreviewIn.struStreamSever.wPort = 8003; //流媒体服务器端口，需要跟服务器启动监听端口一致
        NET_EHOME_PREVIEWINFO_OUT struPreviewOut = { 0 }; //预览请求输出参数
        //预览请求
        if(!NET_ECMS_StartGetRealStreamV11(user_id, &struPreviewIn, &struPreviewOut)){
            printf("NET_ECMS_StartGetRealStreamV11 failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }
        printf("NET_ECMS_StartGetRealStreamV11!\n");

        /* 将实时流传输请求从 CMS 发送给设备(设备自动连接 SMS 并开始发送实时流给 SMS) */
        NET_EHOME_PUSHSTREAM_IN struPushStreamIn = { 0 }; //预览请求推流输入参数
        struPushStreamIn.dwSize = sizeof(struPushStreamIn);
        struPushStreamIn.lSessionID = struPreviewOut.lSessionID; //SessionID，预览请求会话ID
        NET_EHOME_PUSHSTREAM_OUT struPushStreamOut = { 0 }; //码流传输请求的输出参数

        //发送请求给设备并开始传输实时码流(向设备发送命令请求开始发送实时码流，EHOME协议版本大于等于4.0的设备支持)
        if(!NET_ECMS_StartPushRealStream(user_id, &struPushStreamIn, &struPushStreamOut)){
            printf("NET_ECMS_StartPushRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }
        printf("NET_ECMS_StartPushRealStream!\n\n\n");

        /* n秒后停止 SMS 的实时流转发 */
        bb::Time::sleep(50);
        /* 将预览停止请求从 CMS 发送给设备 */
        if(!NET_ECMS_StopGetRealStream(user_id, struPreviewOut.lSessionID)) {
            printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        /* 停止CMS监听服务 */
        if(!NET_ECMS_StopListen(user_id)){
            printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        //释放被 CMS 占用的资源
        NET_ECMS_Fini();
        /* 停止 SMS 的实时流转发 */
        if(preview_handle >= 0) {
            if(!NET_ESTREAM_StopPreview(preview_handle)){
                printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }
        /* 停止 SMS 监听服务并断开其与设备的连接 */
        if(lHandle >= 0) {
            if(!NET_ESTREAM_StopListenPreview(lHandle)){
                printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            } 
        }
        //释放被 SMS 占用的资源
        NET_ESTREAM_Fini();

        /* 释放文件资源 */
        if(video_fp){
            fclose(video_fp);
            video_fp = {};
        }

        /* 强制注销设备 */
        //NET_ECMS_ForceLogout

        printf("Exit!\n");

        return 0;
    }
}