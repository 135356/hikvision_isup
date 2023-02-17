# hikvision
海康威视

SDK监听接口中传入的IP和端口需要设置成服务器内网的IP地址和端口，接口中发送给设备的IP和端口需要设置成公网的IP和端口，具体说明如下：
    内网IP地址和端口:
        NET_ECMS_StartListen
        NET_ESTREAM_StartListenPreview
        NET_ESTREAM_StartListenPlayBack
        NET_ESTREAM_StartListenVoiceTalk
        NET_EALARM_StartListen
        NET_ESS_Startlisten
    公网IP地址和端口：
        NET_ECMS_StartGetRealStreamV11
        NET_ECMS_StartPlayBack
        NET_ECMS_StartVoiceWithStmServer
        NET_ECMS_StartListen监听设置的回调函数(DEVICE_REGISTER_CB)中回传给设备的服务器信息(NET_EHOME_SERVER_INFO)