#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include "bb/Time.h"
#include "hikvision/HCISUPCMS.h"
#include "hikvision/HCISUPStream.h"
#include "hikvision/HCISUPAlarm.h"

namespace isup{
    char log_dir[] = "./record/"; //日志文件目录
    char video_path[] = "./record/test.mp4"; //视频文件路径
    char home_key[32] = "abc123456\0"; //设备isup设置的密钥
    char serve_w_ip[128] = "39.96.177.4"; //服务器外网ip
    char serve_l_ip[128] = "172.26.118.120"; //服务器内网ip

    //异常回调
    void CALLBACK StreamExceptionCallback(DWORD dwType, LONG iUserID, LONG iHandle, void* pUser){
        if(EHOME_PREVIEW_EXCEPTION == dwType){ //预览异常
            printf("Preview exception, handle=%d, Error:%d", iHandle, NET_ECMS_GetLastError());
        }else if(EHOME_PLAYBACK_EXCEPTION == dwType){ //回放异常
            printf("Playback exception, handle=%d, Error:%d", iHandle, NET_ECMS_GetLastError());
        }else if(EHOME_AUDIOTALK_EXCEPTION == dwType){ //语音对讲(转发)异常
            printf("Stream VoiceTalk exception, handle=%d, Error:%d", iHandle, NET_ECMS_GetLastError());
        }
    }
}