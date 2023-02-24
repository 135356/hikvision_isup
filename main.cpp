#include "VideoStream.h"

int main(){
    //cms注册
    if(isup::logOnF() < 0){
        std::cout<<"设备监听，注册失败"<<std::endl;
        return -1;
    }else{
        std::cout<<"设备监听，注册成功"<<std::endl;
    }
    //实时视频流
    if(isup::video::streamF() < 0){
        std::cout<<"实时视频流，失败"<<std::endl;
        return -1;
    }else{
        std::cout<<"实时视频流，成功"<<std::endl;
    }
    //n秒后停止 SMS 的实时流转发
    bb::Time::sleep(50);
    isup::logOutF();
    isup::video::streamOutF();
    return 0;
}