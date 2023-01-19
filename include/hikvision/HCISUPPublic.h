#ifndef _HC_EHOME_PUBLIC_H_
#define _HC_EHOME_PUBLIC_H_ 

//��SDK�������壬Ϊ�����HCNetSDK����ʹ��ʱ�������ض�������
#ifndef _HC_NET_SDK_H_

//-------------ƽ̨��ص��������Ͷ��� begin----------------------------

#if (defined(_WIN32)) //windows
    #define NET_DVR_API  extern "C" __declspec(dllimport)
    typedef  unsigned __int64 UINT64;
#elif defined(__linux__) || defined(__APPLE__) //linux
    typedef    unsigned int         DWORD;
    typedef    unsigned short       WORD;
    typedef    unsigned short       USHORT;
    typedef    short                SHORT;
    typedef    int                  LONG;
    typedef    unsigned char        BYTE;
    #define    BOOL                 int
    typedef    unsigned int         UINT;
    typedef    void*                LPVOID;
    typedef    void*                HANDLE;
    typedef    unsigned int*        LPDWORD;
    typedef    unsigned long long   UINT64;

    #ifndef    TRUE
        #define    TRUE     1
    #endif
    #ifndef    FALSE
        #define    FALSE    0
    #endif
    #ifndef    NULL
        #define    NULL     0
    #endif

    #define __stdcall
    #define CALLBACK

    #define NET_DVR_API extern "C"
#endif //linux

#if defined(_WIN64)
    #define OS_WINDOWS64    1
#endif

#if defined(__LP64__)
    #define OS_POSIX64    1 
#endif


//-------------ƽ̨��ص��������Ͷ��� end----------------------------

//-------------����/���͵Ⱥ궨�壨����HCNetSDK�еĶ��壩 Begin--------
#define MAX_DEVNAME_LEN         32      //�豸���Ƴ��ȣ���HCNetSDK��ͷ�ļ���Ҳ�ж��壩
#define MAX_DEVNAME_LEN_EX      64      //�豸���Ƴ�����չ����HCNetSDK��ͷ�ļ���Ҳ�ж��壩
#define NAME_LEN                32      //�û������ȣ���HCNetSDK��ͷ�ļ���Ҳ�ж��壩
#define MAX_TIME_LEN            32      //ʱ���ַ������ȣ���HCNetSDK��ͷ�ļ���Ҳ�ж��壩
//-------------����/���͵Ⱥ궨�壨����HCNetSDK�еĶ��壩 End---------

//-------------�����붨�壨����HCNetSDK�еĴ����룩Begin-------------
#define NET_DVR_NOERROR                 0   //û�д���
#define NET_DVR_PASSWORD_ERROR          1   //�û����������
#define NET_DVR_NOENOUGHPRI             2   //Ȩ�޲���
#define NET_DVR_NOINIT                  3   //û�г�ʼ��
#define NET_DVR_CHANNEL_ERROR           4   //ͨ���Ŵ���
#define NET_DVR_OVER_MAXLINK            5   //���ӵ�DVR�Ŀͻ��˸����������
#define NET_DVR_VERSIONNOMATCH          6   //�汾��ƥ��
#define NET_DVR_NETWORK_FAIL_CONNECT    7   //���ӷ�����ʧ��
#define NET_DVR_NETWORK_SEND_ERROR      8   //�����������ʧ��
#define NET_DVR_NETWORK_RECV_ERROR      9   //�ӷ�������������ʧ��
#define NET_DVR_NETWORK_RECV_TIMEOUT    10  //�ӷ������������ݳ�ʱ
#define NET_DVR_NETWORK_ERRORDATA       11  //���͵���������
#define NET_DVR_ORDER_ERROR             12  //���ô������
#define NET_DVR_OPERNOPERMIT            13  //�޴�Ȩ��
#define NET_DVR_COMMANDTIMEOUT          14  //DVR����ִ�г�ʱc

#define NET_DVR_PARAMETER_ERROR         17  //��������

#define NET_DVR_NOSUPPORT               23  //��������֧��

#define NET_DVR_DVROPRATEFAILED         29  //DVR����ʧ��

#define NET_DVR_DIR_ERROR               40  //·������
#define NET_DVR_ALLOC_RESOURCE_ERROR    41  //��Դ�������
#define NET_DVR_AUDIO_MODE_ERROR        42  //����ģʽ����
#define NET_DVR_NOENOUGH_BUF            43  //������̫С
#define NET_DVR_CREATESOCKET_ERROR      44  //����SOCKET����
#define NET_DVR_SETSOCKET_ERROR         45  //����SOCKET����
#define NET_DVR_MAX_NUM                 46  //�����ﵽ���
#define NET_DVR_USERNOTEXIST            47  //�û�������

#define NET_DVR_GETLOCALIPANDMACFAIL    53  //��ñ��ص�IP��ַ�������ַʧ��

#define NET_DVR_VOICEMONOPOLIZE         69  //��������ռ

#define NET_DVR_CREATEDIR_ERROR         71  //������־�ļ�Ŀ¼ʧ��
#define NET_DVR_BINDSOCKET_ERROR        72  //���׽���ʧ��
#define NET_DVR_SOCKETCLOSE_ERROR       73  //socket�����жϣ��˴���ͨ�������������жϻ�Ŀ�ĵز��ɴ�
#define NET_DVR_USERID_ISUSING          74  //ע��ʱ�û�ID���ڽ���ĳ����
#define NET_DVR_SOCKETLISTEN_ERROR      75  //����ʧ��

#define NET_DVR_CONVERT_SDK_ERROR       85  //����ת���ʧ��

#define NET_DVR_FUNCTION_NOT_SUPPORT_OS 98  //�˹��ܲ�֧�ָò���ϵͳ

#define NET_DVR_USE_LOG_SWITCH_FILE         103 //����ʹ����־�����ļ�

#define NET_DVR_PACKET_TYPE_NOT_SUPPORT     105 //������װ��ʽ����

#define NET_DVR_STREAM_ENCRYPT_CHECK_FAIL   130 //��������У��ʧ��
#define NET_DVR_CERTIFICATE_FILE_ERROR      147
#define NET_DVR_LOAD_SSL_LIB_ERROR          148
#define NET_DVR_SSL_VERSION_NOT_MATCH       149
#define NET_DVR_LOAD_LIBEAY32_DLL_ERROR     156
#define NET_DVR_LOAD_SSLEAY32_DLL_ERROR     157
#define NET_ERR_LOAD_LIBICONV               158
#define NET_ERR_SSL_CONNECT_FAILED          159
#define NET_ERR_LOAD_ZLIB                   161
#define NET_ERR_OPENSSL_NO_INIT             162

#define  NET_PREVIEW_ERR_CHANNEL_BUSY               165
#define  NET_PREVIEW_ERR_CLIENT_BYSY                166
#define  NET_PREVIEW_ERR_STREAM_UNSUPPORT           167
#define  NET_PREVIEW_ERR_TRANSPORT_UNSUPPORT        168
#define  NET_PREVIEW_ERR_CONNECT_SERVER_FAIL        169
#define  NET_PREVIEW_ERR_QUERY_WLAN_INFO_FAIL       170
#define  NET_PREVIEW_ERR_NO_VIDEO_FAIL              171
#define  NET_PREVIEW_ERR_SET_ENCODE_PARAM_FAIL      172
#define  NET_PREVIEW_ERR_SET_PACK_TYPE_FAIL         173
#define  NET_PREVIEW_ERR_NOW_IN_PREVIEW_FAIL        174
#define  NET_PREVIEW_ERR_NOW_IN_PRESTREAM_FAIL      175
#define  NET_PREVIEW_ERR_BREAKOFF_PRESTREAM_FAIL    176
#define  NET_PREVIEW_ERR_P2P_NOT_FOUND              177

#define NET_SDK_ERR_CREATE_PORT_MULTIPLEX       184
#define NET_SDK_ERR_MAX_PORT_MULTIPLEX          187

//�����Խ��������
#define NET_AUDIOINTERCOM_OK                   600 //�޴���
#define NET_AUDIOINTECOM_ERR_NOTSUPORT         601 //��֧��
#define NET_AUDIOINTECOM_ERR_ALLOC_MEMERY      602 //�ڴ��������
#define NET_AUDIOINTECOM_ERR_PARAMETER         603 //��������
#define NET_AUDIOINTECOM_ERR_CALL_ORDER        604 //���ô������
#define NET_AUDIOINTECOM_ERR_FIND_DEVICE       605 //δ�����豸
#define NET_AUDIOINTECOM_ERR_OPEN_DEVICE       606 //���ܴ��豸��
#define NET_AUDIOINTECOM_ERR_NO_CONTEXT        607 //�豸�����ĳ���
#define NET_AUDIOINTECOM_ERR_NO_WAVFILE        608 //WAV�ļ�����
#define NET_AUDIOINTECOM_ERR_INVALID_TYPE      609 //��Ч��WAV��������
#define NET_AUDIOINTECOM_ERR_ENCODE_FAIL       610 //����ʧ��
#define NET_AUDIOINTECOM_ERR_DECODE_FAIL       611 //����ʧ��
#define NET_AUDIOINTECOM_ERR_NO_PLAYBACK       612 //����ʧ��
#define NET_AUDIOINTECOM_ERR_DENOISE_FAIL      613 //����ʧ��
#define NET_AUDIOINTECOM_ERR_UNKOWN            619 //δ֪����

//-------------�����붨�壨����HCNetSDK�еĴ����룩End-------------

#endif //_HC_NET_SDK_H_

//-------------����/���͵Ⱥ궨�壨ISUPSDK���У� Begin---------------
#define MAX_DEVICE_ID_LEN           256     //�豸ID����
#define NET_EHOME_SERIAL_LEN        12
#define MAX_FULL_SERIAL_NUM_LEN     64
#define MAX_MASTER_KEY_LEN          16

#define REGISTER_LISTEN_MODE_ALL    0      //Ĭ��Ϊ���ַ�ʽ������TCP��UDP���ַ�ʽ
#define REGISTER_LISTEN_MODE_UDP    1      //ע��ֻ��UDP���м���
#define REGISTER_LISTEN_MODE_TCP    2      //ע��ֻ��TCP���м���

//-------------����/���͵Ⱥ궨�壨ISUPSDK���У� End---------------

//-------------�����붨�壨ISUPSDK���У� Begin-------
#define NET_ERR_INFOPUBLISH_APP_NOTRUN          1065 //��Ϣ����Ӧ��δ����
#define NET_ERR_ATTENDANCE_APP_NOTRUN           1066 //����Ӧ��δ����

#define NET_ERR_TERM_NAME_REPEAT                1313 //�ն������ظ�
#define NET_ERR_TERM_SERIAL_REPEAT              1314 //�ն����к��ظ�

#define NET_ERR_FILE_NOT_EXIST                  1352 //�ļ�������

//���ļ����������
#define NET_DVR_LF_INTERFACE_REPEAT_CALL               2400  //�ӿ��ظ�����
#define NET_DVR_LF_INTERFACE_REPEAT_FIRST_PACK         2401  //�ظ���ǵ�һ��
#define NET_DVR_LF_INTERFACE_NO_FIRST_PACK             2402  //δ��ǵ�һ��
#define NET_DVR_READFILE_FAILED                        2403  //���ļ�ʧ��
#define NET_DVR_FILE_TOO_LARGE                         2404  //�ļ�����
#define NET_DVR_FILE_ILLEGAL                           2405  //�Ƿ��ļ�
#define NET_DVR_INVALID_URL                            2406  //��ЧURL

#define NET_DVR_LOAD_SQLITE_ERROR               254  //����sqlite.dll��ʧ��
#define NET_DVR_SQLITE_VERSION_NOT_MATCH        255  //sqlite�汾��ƥ��

#define NET_SS_CLIENT_ERR_KMS_TOKEN_FAIL        3601 //KMSͼƬ�ϴ�Э��,��ȡTokenʧ��
#define NET_SS_CLIENT_ERR_KMS_UPLOAD_FAIL       3602 //KMSͼƬ�ϴ�Э��,�ϴ�ʧ��
#define NET_SS_CLIENT_ERR_CLOUD_POOLIST_FAIL    3603 //�ƴ洢Э��,��ȡ��Դ��ʧ��
#define NET_SS_CLIENT_ERR_CLOUD_BESTNODE_FAIL   3604 //�ƴ洢Э��,��ȡ���Žڵ�ʧ��
#define NET_SS_CLIENT_ERR_DOWNLOAD_PIC_FAIL     3605 //EHome5.0�洢Э��,����ͼƬʧ��
#define NET_SS_CLIENT_ERR_DELETE_PIC_FAIL       3606 //EHome5.0�洢Э��,ɾ��ͼƬʧ��
#define NET_SS_CLIENT_ERR_PROTO_UNSAFE          3607 // [add] by yangzheng 2020/03/13 EHome5.0, storage server in security mode, nonsupport unsafe protocol VRB/Tomcat 
#define NET_SS_CLIENT_ERR_FILE_INEXISTED        3608 // [add] by yangzheng 2020/03/13 EHome5.0, delete or download file not existed
#define NET_SS_CLIENT_ERR_AUTH_FAILED           3609 // [add] by yangzheng 2020/03/13 authentication failed
#define NET_SS_CLIENT_ERR_UPLOAD_FAIL           3610 // picture upload failed, Clound\VRB\Tomcat
#define NET_SS_CLIENT_ERR_MAX_FILE_LEN          3611 //picture upload failed, exceed max file len 50M

#define NET_SS_CLIENT_ERR_DOWNLOAD_VIDEOFILE_FAIL     3612 //���Ĵ洢Э��,������Ƶ�ļ�ʧ��
#define NET_SS_CLIENT_ERR_DELETE_VIDEOFILE_FAIL       3613 //���Ĵ洢Э��,ɾ����Ƶ�ļ�ʧ��
//EHome5.0Э�������
#define NET_DVR_ERR_GENERAL_UNKNOW_ERROR                                3701  //δ֪����
#define NET_DVR_ERR_GENERAL_PARSE_FAILED                                3702  //���Ľ�������
#define NET_DVR_ERR_GENERAL_SYSTEM_ERROR                                3703  //ϵͳ�ڲ����󣨱����豸ϵͳ���ó���
#define NET_DVR_ERR_GENERAL_COMMAND_UNKNOW                              3704  //�Ƿ�����
#define NET_DVR_ERR_GENERAL_COMMAND_NO_LONGER_SUPPORTED                 3705  //��ʱ����
#define NET_DVR_ERR_GENERAL_COMMAND_NOT_SUITABLE                        3706  //��������
#define NET_DVR_ERR_GENERAL_COMMAND_NOT_ALLOW                           3707  //δ��Ȩ����
#define NET_DVR_ERR_GENERAL_CHECKSUM_ERROR                              3708  //У�������
#define NET_DVR_ERR_GENERAL_HEADER_INVALID                              3709  //��Ϣͷ�Ƿ�
#define NET_DVR_ERR_GENERAL_LENGTH_INVALID                              3710  //��Ϣ���ȷǷ�
#define NET_DVR_ERR_GENERAL_PU_BUSY                                     3711  //�豸�޷���Ӧ
#define NET_DVR_ERR_GENERAL_OPERATION_FAILED                            3712  //���������
#define NET_DVR_ERR_GENERAL_PU_NO_CRYPTO_FOUND                          3713  //�豸��ƽ̨δ�ҵ���Ӧ�ļ����㷨
#define NET_DVR_ERR_GENERAL_PU_REFUSED                                  3714  //�ܾ�
#define NET_DVR_ERR_GENERAL_PU_NO_RESOURCE                              3715  //û�п�����Դ
#define NET_DVR_ERR_GENERAL_PU_CHANNEL_ERROR                            3716  //ͨ������
#define NET_DVR_ERR_GENERAL_SYSTEM_COMMAND_PU_COMMAND_UNSUPPORTED       3717  //��֧�ֵ�����
#define NET_DVR_ERR_GENERAL_SYSTEM_COMMAND_PU_NO_RIGHTS_TO_DO_COMMAND   3718  //û��Ȩ��
#define NET_DVR_ERR_GENERAL_NO_SESSION_FOUND                            3719  //û���ҵ��Ự
#define NET_DVR_ERR_GENERAL_PU_NO_VALID_PRELINK                         3720  //û�п��õ�P2PԤ������Դ
#define NET_DVR_ERR_GENERAL_PU_NO_INNER_RESOURCE                        3721  //û�п��õ�ֱ����Դ
#define NET_DVR_ERR_GENERAL_PU_NO_P2P_RESOURCE                          3722  //û�п��õ�P2P��Դ
#define NET_DVR_ERR_GENERAL_PU_NO_UESR                                  3723  //�豸δ���û�
#define NET_DVR_ERR_GENERAL_TICKET_EXPIRED                              3724  //����ƾ֤����
#define NET_DVR_ERR_GENERAL_TICKET_INVALID                              3725  //����ƾ֤��Ч
#define NET_DVR_ERR_GENERAL_NO_P2PSERVER_RESOURCE                       3726  //�޿���P2P����
#define NET_DVR_ERR_GENERAL_PU_NOT_FOUND                                3727  //δ�ҵ��豸���豸��P2PServer��������
#define NET_DVR_ERR_GENERAL_SESSION_FREED                               3728  //�Ự���ͷ�
#define NET_DVR_ERR_RECORD_SEARCH_START_TIME_ERROR                      3729  //����¼��ʼʱ���
#define NET_DVR_ERR_RECORD_SEARCH_STOP_TIME_ERROR                       3730  //����¼�����ʱ���
#define NET_DVR_ERR_RECORD_SEARCH_FAIL                                  3731  //����¼��ʧ��
#define NET_DVR_ERR_RECORD_NO_RESOURCE                                  3732  //¼��ʧ�ܣ��޿��ô洢��Դ
#define NET_DVR_ERR_CAPTURE_PIC_LOCAL_FAILED                            3733  //�豸����ץͼʧ��
#define NET_DVR_ERR_CAPTURE_PIC_APPLY_CACHE_FAILED                      3734  //ͼƬ��������ʧ��
#define NET_DVR_ERR_CAPTURE_PIC_PARSE_PMS_DOMAIN_FAILED                 3735  //PMS������������
#define NET_DVR_ERR_CAPTURE_PIC_CONNECT_PMS_FAILED                      3736  //PMS����ʧ��
#define NET_DVR_ERR_CAPTURE_PIC_CREATE_PMS_PACKET_FAILED                3737  //����PMS���Ĵ���
#define NET_DVR_ERR_CAPTURE_PIC_SEND_PMS_FAILED                         3738  //PMS�������ݴ���
#define NET_DVR_ERR_CAPTURE_PIC_RECV_PMS_FAILED                         3739  //PMS�������ݴ���
#define NET_DVR_ERR_CAPTURE_PIC_PARSE_PMS_RESPONSE_FAILED               3740  //PMSӦ���Ľ�������
#define NET_DVR_ERR_CAPTURE_PIC_GET_URL_FAILED                          3741  //��ȡURLʧ��

#define NET_DVR_DATABASE_OPEN_ERROR             8001 //���ݿ��ʧ��
#define NET_DVR_DATABASE_INSERT_ERROR           8002 //���ݿ����ʧ��
#define NET_DVR_DATABASE_TABLE_ERROR            8003 //���ݿ������

//���߻��Ѵ������   8301~8330  
#define NET_ERR_DEV_SLEEP               8301    //�豸������
#define NET_ERR_DEV_GOINGTOSLEEP        8302    //��ǰ�豸����ִ�����߶����Ĺ����У�Ԥ��13S����������������״̬����ʱ�޷�����NET_ECMS_WakeUp�ӿڵĻ��Ѳ�����ֱ��ִ�����߶�����������ʽ��������״̬�ſ��������û��ѽӿ�

//-------------�����붨�壨ISUPSDK���У� End-------

typedef struct tagNET_EHOME_IPADDRESS
{
    char szIP[128]; 
    WORD wPort;     //�˿�
    char byRes[2];
}NET_EHOME_IPADDRESS, *LPNET_EHOME_IPADDRESS;

typedef struct tagNET_EHOME_ZONE
{
    DWORD dwX;          //X������
    DWORD dwY;          //Y������
    DWORD dwWidth;      //���
    DWORD dwHeight;     //�߶�
}NET_EHOME_ZONE, *LPNET_EHOME_ZONE;

//��������
typedef enum tagNET_EHOME_LOCAL_CFG_TYPE
{
    UNDEFINE                = -1,   //��ʱû�о���Ķ���
    ACTIVE_ACCESS_SECURITY  = 0,    //�豸��������İ�ȫ��
    AMS_ADDRESS             = 1,    //�������������ػػ���ַ
    SEND_PARAM              = 2,    //���Ͳ�������
    SET_REREGISTER_MODE     = 3,    //�����豸�ظ�ע��ģʽ
    LOCAL_CFG_TYPE_GENERAL  = 4,    //ͨ�ò�������
    COM_PATH                = 5,    //COM·��
    SESSIONKEY_REQ_MOD      = 6,    //sessionkey�����Ƿ�ص���lpInBuff����ΪHPR_BOOL*,HPR_TRUE/HPR_FALSE���ص�/���ص�
    DEV_DAS_PINGREO_CALLBACK = 7,   //�豸����ע��ص�
    REGISTER_LISTEN_MODE    = 8,    //ע�����ģʽ ��Ӧ�ṹ��ΪNET_EHOME_REGISTER_LISTEN_MODE
    STREAM_PLAYBACK_PARAM   = 9     //�طű��ز�������
}NET_EHOME_LOCAL_CFG_TYPE, *LPNET_EHOME_LOCAL_CFG_TYPE;

typedef struct tagNET_EHOME_LOCAL_ACCESS_SECURITY
{
    DWORD   dwSize;
    BYTE    byAccessSecurity;    //0-����ģʽ����������汾��Э����룩��1-��ͨģʽ��ֻ֧��4.0���°汾����֧��Э�鰲ȫ�İ汾���룩 2-��ȫģʽ��ֻ����4.0���ϰ汾��֧��Э�鰲ȫ�İ汾���룩
    BYTE    byRes[127];
}NET_EHOME_LOCAL_ACCESS_SECURITY,*LPNET_EHOME_LOCAL_ACCESS_SECURITY;

typedef struct tagNET_EHOME_AMS_ADDRESS
{
    DWORD dwSize;
    BYTE  byEnable;  //0-�ر�CMS���ձ������ܣ�1-����CMS���ձ�������
    BYTE  byRes1[3];
    NET_EHOME_IPADDRESS  struAddress;   //AMS���ػػ���ַ
    BYTE byRes2[32];
}NET_EHOME_AMS_ADDRESS, *LPNET_EHOME_AMS_ADDRESS;

typedef struct tagNET_EHOME_SEND_PARAM
{
    DWORD dwSize;
    DWORD dwRecvTimeOut;    //���ճ�ʱʱ�䣬��λ����
    BYTE  bySendTimes;      //���ķ��ʹ�����Ϊ��Ӧ�����绷���ϲ������£������������Ĭ��һ�Σ����3��
    BYTE  byRes2[127];
}NET_EHOME_SEND_PARAM, *LPNET_EHOME_SEND_PARAM;

//Ehome5.0Э���豸EhomeKey��Ϣ
typedef struct tagNET_EHOME_DEV_SESSIONKEY
{
    BYTE   sDeviceID[MAX_DEVICE_ID_LEN];        //�豸ID/*256*/
    BYTE   sSessionKey[MAX_MASTER_KEY_LEN];     //�豸Sessionkey/*16*/
} NET_EHOME_DEV_SESSIONKEY, *LPNET_EHOME_DEV_SESSIONKEY;

typedef struct tagNET_EHOME_LOCAL_GENERAL_CFG
{
    BYTE byAlarmPictureSeparate;    //����͸��ISAPI�������ݺ�ͼƬ�Ƿ���룬0-�����룬1-���루�������EHOME_ISAPI_ALARM�ص����أ�
    BYTE byRes[127];                //����
}NET_EHOME_LOCAL_GENERAL_CFG, *LPNET_EHOME_LOCAL_GENERAL_CFG;

typedef struct tagNET_EHOME_LOCAL_DEV_PINGREO
{
    DWORD   dwSize;
    BYTE    byEnablePingReoCallback;    //0- ���ص���1-�ص�����, Ĭ��Ϊ0
    BYTE    byRes[63];
}NET_EHOME_LOCAL_DEV_PINGREO, *LPNET_EHOME_LOCAL_DEV_PINGREO;

#endif //_HC_EHOME_PUBLIC_H_

