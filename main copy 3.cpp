#include "aaa.h"

int main(){
    //异常回调函数
    //NET_ESTREAM_SetExceptionCallBack(0, 0, isup::StreamExceptionCallback, NULL);
    if(isup::logOn() < 0){
        std::cout<<"设备监听，注册失败"<<std::endl;
        return -1;
    }else{
        std::cout<<"设备监听，注册成功"<<std::endl;
    }
    isup::videoStream();
    return 0;
}