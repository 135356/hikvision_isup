#include "cms.h"

namespace isup{
    FILE *video_fp{}; //视频文件
    long preview_handle{}; //预览句柄
    
    //实时流数据回调函数
    void CALLBACK fnPREVIEW_DATA_CB(LONG lPreviewHandle, NET_EHOME_PREVIEW_CB_MSG *pPreviewCBMsg, void *pUserData){
        if(pPreviewCBMsg == NULL){
            return ;
        }
        if(pPreviewCBMsg->byDataType == 1){
            if(!video_fp){
                video_fp = fopen(video_path,"wb");
            }
            std::cout<<"数据将保存到:"<<video_path<<", HIK流标头信息长度:"<<pPreviewCBMsg->dwDataLen<<std::endl;
        }else if(pPreviewCBMsg->byDataType == 2){
            std::cout<<"获取流数据:"<<pPreviewCBMsg->dwDataLen<<std::endl;
        }

        if(video_fp){
            fwrite(pPreviewCBMsg->pRecvdata, pPreviewCBMsg->dwDataLen, 1, video_fp);
        }
    }

    //VTDU预览请求回应回调函数
    BOOL CALLBACK fnPREVIEW_NEWLINK_CB(LONG lPreviewHandle, NET_EHOME_NEWLINK_CB_MSG *pNewLinkCBMsg, void *pUserData){
        preview_handle = lPreviewHandle;
        std::cout<<"预览回调, Device ID:"<<pNewLinkCBMsg->szDeviceID<<','<<"Channel:"<<pNewLinkCBMsg->dwChannelNo<<std::endl;

        //预览数据回调参数
        NET_EHOME_PREVIEW_DATA_CB_PARAM struDataCB = { 0 };
        struDataCB.fnPreviewDataCB = fnPREVIEW_DATA_CB;
        struDataCB.byStreamFormat = 0; //封装格式：0- PS

        if(!NET_ESTREAM_SetPreviewDataCB(lPreviewHandle, &struDataCB)){
            printf("预览回调失败, error code: %d\n", NET_ESTREAM_GetLastError());
            return FALSE;
        }else{
            printf("预览回调成功\n");
            return TRUE;
        }
    }

    //取流初始化
    /* int videoInit(){
        //取流库初始化
        NET_ESTREAM_Init();
        //日志
        NET_ESTREAM_SetLogToFile(3, log_dir, FALSE);

        //预览监听参数
        NET_EHOME_LISTEN_PREVIEW_CFG struListen = { 0 };
        memcpy(struListen.struIPAdress.szIP, serve_l_ip, sizeof(serve_l_ip));
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
        printf("NET_ESTREAM_StartListenPreview ip:%s\n", struListen.struIPAdress.szIP);
        return 0;
    } */

    //取流实时预览
    /* int videoPreview(){
        //预览请求输入参数
        NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = { 0 };
        struPreviewIn.iChannel = 1; //通道号
        struPreviewIn.dwLinkMode = 0; //0- TCP方式，1- UDP方式 
        struPreviewIn.dwStreamType = 0; //码流类型：0- 主码流，1- 子码流, 2- 第三码流
        memcpy(struPreviewIn.struStreamSever.szIP, serve_w_ip, sizeof(serve_w_ip));//流媒体服务器IP地址
        struPreviewIn.struStreamSever.wPort = 8003; //流媒体服务器端口，需要跟服务器启动监听端口一致

        //预览请求输出参数
        NET_EHOME_PREVIEWINFO_OUT struPreviewOut = { 0 };

        //预览请求
        if(!NET_ECMS_StartGetRealStreamV11(user_id, &struPreviewIn, &struPreviewOut)){
            printf("NET_ECMS_StartGetRealStreamV11 failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }

        printf("NET_ECMS_StartGetRealStreamV11!\n");

        //预览请求推流输入参数 
        NET_EHOME_PUSHSTREAM_IN struPushStreamIn = { 0 };
        struPushStreamIn.dwSize = sizeof(struPushStreamIn);
        struPushStreamIn.lSessionID = struPreviewOut.lSessionID; //SessionID，预览请求会话ID

        //码流传输请求的输出参数
        NET_EHOME_PUSHSTREAM_OUT struPushStreamOut = { 0 };

        //发送请求给设备并开始传输实时码流(向设备发送命令请求开始发送实时码流，EHOME协议版本大于等于4.0的设备支持)
        if(!NET_ECMS_StartPushRealStream(user_id, &struPushStreamIn, &struPushStreamOut)){
            printf("NET_ECMS_StartPushRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }
        printf("NET_ECMS_StartPushRealStream!\n");

        bb::Time::sleep(10);
        return 0;
    } */

    //登出
    /* int videoOut(){
        LONG lRealHandle = -1;
        int lTransHandle = -1;
        
        //释放CMS预览请求资源
        if(!NET_ECMS_StopGetRealStream(user_id, struPreviewOut.lSessionID)){
            printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        }

        //CMS停止监听
        if(!NET_ECMS_StopListen(lListen)){
            printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
        }

        //释放被 CMS 占用的资源
        NET_ECMS_Fini();

        //SMS 停止转发码流
        if(lRealHandle > -1) {
            if(!NET_ESTREAM_StopPreview(lRealHandle)){
                printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }

        //SMS 停止监听服务
        if(lHandle > -1) {
            if(!NET_ESTREAM_StopListenPreview(lHandle)){
                printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }

        //释放被 SMS 占用的资源
        NET_ESTREAM_Fini();

        //释放文件资源
        if(video_fp){
            fclose(video_fp);
            video_fp = {};
        }

        printf("Exit!\n");
    } */

    //流媒体服务器(VTDU)监听取流
    int videoStream(){
        //取流库初始化
        NET_ESTREAM_Init();
        //日志
        NET_ESTREAM_SetLogToFile(3, log_dir, FALSE);

        //预览监听参数
        NET_EHOME_LISTEN_PREVIEW_CFG struListen = { 0 };
        memcpy(struListen.struIPAdress.szIP, serve_l_ip, sizeof(serve_l_ip));
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
        printf("NET_ESTREAM_StartListenPreview ip:%s\n", struListen.struIPAdress.szIP);
        ///////////////////////////////
        //预览请求输入参数
        NET_EHOME_PREVIEWINFO_IN_V11 struPreviewIn = { 0 };
        struPreviewIn.iChannel = 1; //通道号
        struPreviewIn.dwLinkMode = 0; //0- TCP方式，1- UDP方式 
        struPreviewIn.dwStreamType = 0; //码流类型：0- 主码流，1- 子码流, 2- 第三码流
        memcpy(struPreviewIn.struStreamSever.szIP, serve_w_ip, sizeof(serve_w_ip));//流媒体服务器IP地址
        struPreviewIn.struStreamSever.wPort = 8003; //流媒体服务器端口，需要跟服务器启动监听端口一致

        //预览请求输出参数
        NET_EHOME_PREVIEWINFO_OUT struPreviewOut = { 0 };

        //预览请求
        if(!NET_ECMS_StartGetRealStreamV11(user_id, &struPreviewIn, &struPreviewOut)){
            printf("NET_ECMS_StartGetRealStreamV11 failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }

        printf("NET_ECMS_StartGetRealStreamV11!\n");

        //预览请求推流输入参数 
        NET_EHOME_PUSHSTREAM_IN struPushStreamIn = { 0 };
        struPushStreamIn.dwSize = sizeof(struPushStreamIn);
        struPushStreamIn.lSessionID = struPreviewOut.lSessionID; //SessionID，预览请求会话ID

        //码流传输请求的输出参数
        NET_EHOME_PUSHSTREAM_OUT struPushStreamOut = { 0 };

        //发送请求给设备并开始传输实时码流(向设备发送命令请求开始发送实时码流，EHOME协议版本大于等于4.0的设备支持)
        if(!NET_ECMS_StartPushRealStream(user_id, &struPushStreamIn, &struPushStreamOut)){
            printf("NET_ECMS_StartPushRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
            NET_ECMS_Fini();
            return -1;
        }
        printf("NET_ECMS_StartPushRealStream!\n");

        bb::Time::sleep(10);

        /////////////////////
        LONG lRealHandle = -1;
        int lTransHandle = -1;
        
        //释放CMS预览请求资源
        if(!NET_ECMS_StopGetRealStream(user_id, struPreviewOut.lSessionID)){
            printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        }

        //CMS停止监听
        if(!NET_ECMS_StopListen(monitor_state)){
            printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
        }

        //释放被 CMS 占用的资源
        NET_ECMS_Fini();

        //SMS 停止转发码流
        if(lRealHandle > -1) {
            if(!NET_ESTREAM_StopPreview(lRealHandle)){
                printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }

        //SMS 停止监听服务
        if(lHandle > -1) {
            if(!NET_ESTREAM_StopListenPreview(lHandle)){
                printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }

        //释放被 SMS 占用的资源
        NET_ESTREAM_Fini();

        //释放文件资源
        if(video_fp){
            fclose(video_fp);
            video_fp = {};
        }

        printf("Exit!\n");
        return 0;








        //释放被 CMS 预览请求占用的资源
        if(!NET_ECMS_StopGetRealStream(user_id, struPreviewOut.lSessionID)) {
            printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        //CMS 停止监听服务
        if(!NET_ECMS_StopListen(user_id)){
            printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        //释放被 CMS 占用的资源
        NET_ECMS_Fini();
        //SMS 停止转发码流
        if(lRealHandle >= 0) {
            if(!NET_ESTREAM_StopPreview(lRealHandle)){
                printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }
        //SMS 停止监听服务
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

        printf("Exit!\n");





        /* 停止 SMS 的实时流转发 */
        if(lRealHandle >= 0){
            if(!NET_ESTREAM_StopPreview(lRealHandle)){
                printf("NET_ESTREAM_StopPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }
        /* 将预览停止请求从 CMS 发送给设备 */
        if(!NET_ECMS_StopGetRealStream(user_id, struPreviewOut.lSessionID)){
            printf("NET_ECMS_StopGetRealStream failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        /* 停止 SMS 监听服务并断开其与设备的连接 */
        if(lHandle > -1) {
            if(!NET_ESTREAM_StopListenPreview(lHandle)){
                printf("NET_ESTREAM_StopListenPreview failed, error code: %d\n", NET_ECMS_GetLastError());
            }
        }
        /* 强制注销设备 */
        //NET_ECMS_ForceLogout

        /* 停止CMS监听服务 */
        if(!NET_ECMS_StopListen(monitor_state)){
            printf("NET_ECMS_StopListen failed, error code: %d\n", NET_ECMS_GetLastError());
        }
        /* 释放被CMS和SMS占用的资源 */
        NET_ECMS_Fini();
        NET_ESTREAM_Fini();

        /* 释放文件资源 */
        if(video_fp){
            fclose(video_fp);
            video_fp = {};
        }

        printf("Exit!\n");
    }
}