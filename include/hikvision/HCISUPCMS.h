#ifndef _HC_EHOME_CMS_H_
#define _HC_EHOME_CMS_H_

#include "HCISUPPublic.h"

typedef enum tagNET_EHOME_CMS_INIT_CFG_TYPE
{
    NET_EHOME_CMS_INIT_CFG_LIBEAY_PATH = 0, //����OpenSSL��libeay32.dll/libcrypto.so����·��
    NET_EHOME_CMS_INIT_CFG_SSLEAY_PATH = 1  //����OpenSSL��ssleay32.dll/libssl.so����·��
}NET_EHOME_CMS_INIT_CFG_TYPE;

#define EHOME_PROTOCOL_LEN  (8*1024) //8KB

//��ʼ��������ʼ��
NET_DVR_API BOOL  CALLBACK NET_ECMS_Init();
NET_DVR_API BOOL  CALLBACK NET_ECMS_Fini();

//��ʼ��֮ǰ�����ã���ʼ��֮�󲻿ɵ���
NET_DVR_API BOOL  CALLBACK NET_ECMS_SetSDKInitCfg(NET_EHOME_CMS_INIT_CFG_TYPE enumType, void* const lpInBuff);

//��ȡ������
NET_DVR_API DWORD CALLBACK NET_ECMS_GetLastError();

//��ȡ�汾��
NET_DVR_API DWORD CALLBACK NET_ECMS_GetBuildVersion();

//�����رռ���
typedef enum tagNET_EHOME_REGISTER_TYPE
{
    ENUM_UNKNOWN                = -1,
    ENUM_DEV_ON                 = 0,    //�豸���߻ص�
    ENUM_DEV_OFF,                       //�豸���߻ص�
    ENUM_DEV_ADDRESS_CHANGED,           //�豸��ַ�����仯
    ENUM_DEV_AUTH,                      //Ehome5.0�豸��֤�ص�
    ENUM_DEV_SESSIONKEY,                //Ehome5.0�豸Sessionkey�ص�
    ENUM_DEV_DAS_REQ,                   //Ehome5.0�豸�ض�������ص�
    ENUM_DEV_SESSIONKEY_REQ,            //EHome5.0�豸sessionkey����ص�
    ENUM_DEV_DAS_REREGISTER,            //�豸��ע��ص�
    ENUM_DEV_DAS_PINGREO,               //�豸ע������
    ENUM_DEV_DAS_EHOMEKEY_ERROR,        //У������ʧ��
    ENUM_DEV_SESSIONKEY_ERROR,           //Sessionkey�����쳣
    ENUM_DEV_SLEEP = 11           //�豸��������״̬��ע������״̬�£��豸�޷���Ԥ�����طš������Խ������õ�CMS�е���������Ӧ���豸��ͨ��NET_ECMS_WakeUp�ӿڽ��л��ѣ�
}NET_EHOME_REGISTER_TYPE;

//�����Խ���������
typedef enum tagNET_EHOME_TALK_ENCODING_TYPE
{
    ENUM_ENCODING_START     = 0,        //�������Ϳ�ʼ
    ENUM_ENCODING_G722_1,               //G722_1
    ENUM_ENCODING_G711_MU,              //G711_MU
    ENUM_ENCODING_G711_A,               //G711_A
    ENUM_ENCODING_G723,                 //G723
    ENUM_ENCODING_MP1L2,                //MP1L2
    ENUM_ENCODING_MP2L2,                //MP2L2
    ENUM_ENCODING_G726,                 //G726
    ENUM_ENCODING_AAC,                  //AAC
    ENUM_ENCODING_RAW       = 100       //RAW
}NET_EHOME_TALK_ENCODING_TYPE;

typedef BOOL (CALLBACK * DEVICE_REGISTER_CB)(LONG lUserID, DWORD dwDataType, void* pOutBuffer, DWORD dwOutLen,
                                             void* pInBuffer, DWORD dwInLen, void* pUser);

typedef struct tagNET_EHOME_CMS_LISTEN_PARAM
{
    NET_EHOME_IPADDRESS struAddress;    //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ���������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
    DEVICE_REGISTER_CB  fnCB;           //������Ϣ�ص�����
    void*               pUserData;      //�û�����
    DWORD               dwKeepAliveSec; //�����������λ����,0:Ĭ��Ϊ30S��
    DWORD               dwTimeOutCount; //������ʱ������0��Ĭ��Ϊ3��
    BYTE                byRes[24];
}NET_EHOME_CMS_LISTEN_PARAM, *LPNET_EHOME_CMS_LISTEN_PARAM;

typedef struct tagNET_EHOME_REGISTER_LISTEN_MODE
{
    DWORD dwSize;
    DWORD dwRegisterListenMode;    //0-��ʾ����TCP��UDP��1��ʾ����UDP��2��ʾ����TCP;
    BYTE  byRes[128];
}NET_EHOME_REGISTER_LISTEN_MODE, *LPNET_EHOME_REGISTER_LISTEN_MODE;

typedef struct tagNET_EHOME_SET_REREGISTER_MODE
{
    DWORD dwSize;
    DWORD dwReRegisterMode;    //�����豸�ظ�ע��ģʽ�������EHome2.0Э�飬��Ϊ0����ʾ�ڱ���ʱ�����豸�ظ�ע�ᣬEHomeSDK���ܣ�Ĭ��Ϊ�˷�ʽ����Ϊ1����ʾ�ڱ���ʱ���ڣ��豸�ظ�ע�ᣬ�����ܣ��ظ��豸403�ظ�ע�������
}NET_EHOME_SET_REREGISTER_MODE, *LPNET_EHOME_SET_REREGISTER_MODE;

//�����رռ���
NET_DVR_API LONG CALLBACK NET_ECMS_StartListen(LPNET_EHOME_CMS_LISTEN_PARAM lpCMSListenPara);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopListen(LONG iHandle);
//ע���豸
NET_DVR_API BOOL CALLBACK NET_ECMS_ForceLogout(LONG lUserID);
NET_DVR_API BOOL CALLBACK NET_ECMS_SetLogToFile(DWORD iLogLevel, char* strLogDir, BOOL bAutoDel);

typedef enum tagNET_EHOME_CALLBACK_TYPE
{
    NET_EHOME_REALSTREAM_CB = 0, //ȡ���첽�ص�
    NET_EHOME_PLAYBACK_CB,       //�ط��첽�ص�
    NET_EHOME_VOICETALK_CB,       //�����Խ��ص�
    NET_EHOME_PASSTHROUGH_CB,    //ISAPI͸���첽�ص�
    NET_EHOME_V2_VOICETALK_CB     //2.0�����Խ��첽�ص�
} NET_EHOME_CALLBACK_TYPE;

typedef struct tagNET_EHOME_CMSCB_DATA
{
    LONG   lUserID;      //�û�ID
    DWORD  dwType;       //�ص�����
    DWORD  dwHandle;     //��Ϣ�����Ψһ��ʶ
    BOOL   bSucc;        //��Ӧͬ���µĽӿڷ���ֵ
    void*  pOutBuffer;   //�豸��Ӧ����
    DWORD  dwOutLen;     //�豸��Ӧ���ݳ���
    DWORD  dwErrorNo;    //SDK������
    BYTE   byRes[32];    //�����ֽڣ�������չ
} NET_EHOME_CMSCB_DATA;

#define ECMS_CB_TYPE_UNDEFINE                  0
#define ECMS_CB_TYPE_START_GET_REALSTREAM      1
#define ECMS_CB_TYPE_START_PUSH_REALSTREAM     3
#define ECMS_CB_TYPE_STOP_GET_REALSTREAM_EX    4
#define ECMS_CB_TYPE_START_PLAYBACK            5
#define ECMS_CB_TYPE_START_PUSH_PLAYBACK       6
#define ECMS_CB_TYPE_STOP_PLAYBACK_EX          7
#define ECMS_CB_STOP_VOICETALK_EX              9
#define ECMS_CB_TYPE_START_VOICETALK_STM       10
#define ECMS_CB_TYPE_START_PUSH_VOICE_STREAM   11
#define ECMS_CB_TYPE_STOP_VOICE_TALK_STM_EX    12
#define ECMS_CB_TYPE_ISAPI_PASSTHROUGH         13
#define ECMS_CB_TYPE_START_V2_VOICETALK        14
#define ECMS_CB_TYPE_PAUSE_PLAYBACK            15
#define ECMS_CB_TYPE_RESTART_PLAYBACK          16

typedef void(CALLBACK *ECMSCallback)(NET_EHOME_CMSCB_DATA *pData, void* pUser);

NET_DVR_API BOOL CALLBACK NET_ECMS_SetCallback(NET_EHOME_CALLBACK_TYPE enumCallbackType, ECMSCallback fnCallback, void* pUser);

typedef struct tagNET_EHOME_DEV_REG_INFO
{
    DWORD  dwSize;
    DWORD  dwNetUnitType;                   //����EHomeSDKЭ��Ԥ����Ŀǰû������
    BYTE   byDeviceID[MAX_DEVICE_ID_LEN];   //�豸ID
    BYTE   byFirmwareVersion[24];           //�̼��汾
    NET_EHOME_IPADDRESS struDevAdd;         //�豸ע�������ǣ��豸�ı��ص�ַ
    DWORD  dwDevType;                       //�豸����
    DWORD  dwManufacture;                   //�豸���Ҵ���
    BYTE   byPassWord[32];                  //�豸��½CMS�����룬���û����и������������֤
    BYTE   sDeviceSerial[NET_EHOME_SERIAL_LEN/*12*/];   //�豸���кţ��������к�
    BYTE   byReliableTransmission;
    BYTE   byWebSocketTransmission;
    BYTE   bySupportRedirect;               //�豸֧���ض���ע�� 0-��֧�� 1-֧��
    BYTE   byDevProtocolVersion[6];         //�豸Э��汾
    BYTE   bySessionKey[MAX_MASTER_KEY_LEN];//Ehome5.0�豸SessionKey
    BYTE   byMarketType; //0-��Ч��δ֪���ͣ�,1-�����ͣ�2-��ҵ��
	BYTE   byRes1;  //����λ
	BYTE   bySupport; //�豸֧�ֵĹ��������֧��"��"���������ҵ���
    //��һλΪ1��ʾ֧��NPQԤ��(0b00000001)
    //�ڶ�λΪ1��ʾ֧��NPQ�ط�(0b00000010)
    //����λΪ1��ʾ֧��Ԥ�����طź������Խ���·���ܴ���(0b00000100)
    //����λΪ1��ʾ֧��HLS�ط�(0b00001000)
    //����λΪ1��ʾ֧�������Խ���·���㲥���䡪��ֻ��������������������(0b00010000)
	BYTE   byRes[24];
}NET_EHOME_DEV_REG_INFO, *LPNET_EHOME_DEV_REG_INFO;

typedef struct tagNET_EHOME_DEV_REG_INFO_V12
{
    NET_EHOME_DEV_REG_INFO struRegInfo;
    NET_EHOME_IPADDRESS struRegAddr;         //�豸ע��ķ�������ַ
    BYTE   sDevName[MAX_DEVNAME_LEN_EX];     //�豸����
    BYTE   byDeviceFullSerial[MAX_FULL_SERIAL_NUM_LEN];   //�豸�������кţ��豸�ͺ�+����+�����+��չ
    BYTE   byRes[128];
}NET_EHOME_DEV_REG_INFO_V12, *LPNET_EHOME_DEV_REG_INFO_V12;

typedef struct tagNET_EHOME_BLACKLIST_SEVER
{
    NET_EHOME_IPADDRESS struAdd;            //��������ַ
    BYTE    byServerName[NAME_LEN/*32*/];   //����������
    BYTE    byUserName[NAME_LEN/*32*/];     //�û���
    BYTE    byPassWord[NAME_LEN/*32*/];     //����
    BYTE    byRes[64];
}NET_EHOME_BLACKLIST_SEVER, *LPNET_EHOME_BLACKLIST_SEVER;

typedef struct tagNET_EHOME_SERVER_INFO
{
    DWORD               dwSize;
    DWORD               dwKeepAliveSec;         //�����������λ����,0:Ĭ��Ϊ15S��
    DWORD               dwTimeOutCount;         //������ʱ������0��Ĭ��Ϊ6��
    NET_EHOME_IPADDRESS struTCPAlarmSever;      //������������ַ��TCPЭ�飩
    NET_EHOME_IPADDRESS struUDPAlarmSever;      //������������ַ��UDPЭ�飩
    DWORD               dwAlarmServerType;      //��������������0-ֻ֧��UDPЭ���ϱ���1-֧��UDP��TCP����Э���ϱ���2 - ����MQTTЭ�鷽ʽ�ϱ�����ʱ��������ַΪTCPЭ������ַ��
    NET_EHOME_IPADDRESS struNTPSever;           //NTP��������ַ
    DWORD               dwNTPInterval;          //NTPУʱ�������λ���룩
    NET_EHOME_IPADDRESS struPictureSever;       //ͼƬ��������ַ
    DWORD               dwPicServerType;        //ͼƬ����������ͼƬ���������ͣ�1-VRBͼƬ��������0-TomcatͼƬ����,2-�ƴ洢3,3-KMS,4-EHome5.0�洢Э��
    NET_EHOME_BLACKLIST_SEVER   struBlackListServer;    //������������
    BYTE                        byRes[128];
}NET_EHOME_SERVER_INFO, *LPNET_EHOME_SERVER_INFO;

typedef struct tagNET_EHOME_SERVER_INFO_V50
{
    DWORD                   dwSize;
    DWORD                   dwKeepAliveSec;         //�����������λ����,0:Ĭ��Ϊ15S��
    DWORD                   dwTimeOutCount;         //������ʱ������0��Ĭ��Ϊ6��
    NET_EHOME_IPADDRESS     struTCPAlarmSever;      //������������ַ��TCPЭ�飩
    NET_EHOME_IPADDRESS     struUDPAlarmSever;      //������������ַ��UDPЭ�飩
    DWORD                   dwAlarmServerType;      //��������������0-ֻ֧��UDPЭ���ϱ���1-֧��UDP��TCP����Э���ϱ�
    NET_EHOME_IPADDRESS     struNTPSever;           //NTP��������ַ
    DWORD                   dwNTPInterval;          //NTPУʱ�������λ���룩
    NET_EHOME_IPADDRESS     struPictureSever;       //ͼƬ��������ַ
    DWORD                   dwPicServerType;        //ͼƬ����������ͼƬ���������ͣ�1-VRBͼƬ��������0-TomcatͼƬ����,2-�ƴ洢3,3-KMS
    NET_EHOME_BLACKLIST_SEVER   struBlackListServer;//������������
    NET_EHOME_IPADDRESS     struRedirectSever;      //Redirect Server
    BYTE                    byClouldAccessKey[64];  //�ƴ洢AK
    BYTE                    byClouldSecretKey[64];  //�ƴ洢SK
    BYTE                    byClouldHttps;          //�ƴ洢HTTPSʹ�� 1-HTTPS 0-HTTP
    BYTE                    byRes1[3];
    DWORD                   dwAlarmKeepAliveSec;    //���������������λ����,0:Ĭ��Ϊ30s��
    DWORD                   dwAlarmTimeOutCount;    //����������ʱ������0��Ĭ��Ϊ3��
    DWORD                   dwClouldPoolId;         //�ƴ洢PoolId
    BYTE                    byRes[368];
}NET_EHOME_SERVER_INFO_V50, *LPNET_EHOME_SERVER_INFO_V50;

//-----------------------------------------------------------------------------------------------------------
//�����Խ�

typedef void(CALLBACK *fVoiceDataCallBack)(LONG iVoiceHandle, char* pRecvDataBuffer, DWORD dwBufSize, DWORD dwEncodeType, BYTE byAudioFlag, void* pUser);

typedef struct tagNET_EHOME_VOICETALK_PARA
{
    BOOL           bNeedCBNoEncData; //��Ҫ�ص����������ͣ�0-�����������1-����ǰ����������ת��ʱ��֧�֣�
    fVoiceDataCallBack  cbVoiceDataCallBack; //���ڻص���Ƶ���ݵĻص�����
    DWORD          dwEncodeType;    //SDK��ֵ,SDK��������������,0- OggVorbis��1-G711U��2-G711A��3-G726��4-AAC��5-MP2L2��6-PCM,7-MP3
    void*          pUser;           //�û�����
    BYTE           byVoiceTalk;     //0-�����Խ�,1-����ת��,2-�����㲥
    BYTE           byDevAudioEnc;   //����������豸����Ƶ���뷽ʽ 0- OggVorbis��1-G711U��2-G711A��3-G726��4-AAC��5-MP2L2��6-PCM,7-MP3
    BYTE           byRes1[2];
    LONG           lHandle;         //����������������˻ط��첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ
    BYTE           byRes[56];       //Reserved, set as 0. 0
} NET_EHOME_VOICETALK_PARA,*LPNET_EHOME_VOICETALK_PARA;

typedef struct tagNET_EHOME_VOICE_TALK_IN
{
    DWORD dwVoiceChan;                                  //ͨ����
    NET_EHOME_IPADDRESS struStreamSever;                //��ý���ַ
    NET_EHOME_TALK_ENCODING_TYPE  byEncodingType[9];    //�����Խ���������
    BYTE  byLinkEncrypt;  //
    BYTE  byBroadcast;  //�����㲥��ʶ,�豸���յ�����ʶΪ1�󲻽�����Ƶ�ɼ����͸��Զ�
    BYTE  byBroadLevel;//�����㲥���ȼ���ʶ,0~15���ȼ��ӵ͵���,������byBroadcastΪ1ʱ,0��ʶ������ȼ���������byBroadcastΪ0ʱ�����ڵ�������Ϊ�����ֽ�
    BYTE  byBroadVolume; //�����㲥����,0~15�����ӵ͵���,������byBroadcastΪ1ʱ,0��ʶ���������������byBroadcastΪ0ʱ�����ڵ�������Ϊ�����ֽ�
    BYTE  byAudioSamplingRate; //��Ƶ������ 0-Ĭ��, 1-16kHZ, 2-32kHZ, 3-48kHZ, 4-44.1kHZ, 5-8kHZ
    BYTE  byRes[114];
}NET_EHOME_VOICE_TALK_IN, *LPNET_EHOME_VOICE_TALK_IN;

typedef struct tagNET_EHOME_VOICE_TALK_OUT
{
    LONG  lSessionID;
    LONG  lHandle;
    BYTE  byRes[124];
}NET_EHOME_VOICE_TALK_OUT, *LPNET_EHOME_VOICE_TALK_OUT;

typedef struct tagNET_EHOME_PUSHVOICE_IN
{
    DWORD dwSize;
    LONG  lSessionID; 
    BYTE  byToken[64];
    BYTE  byRes[64];
}NET_EHOME_PUSHVOICE_IN, *LPNET_EHOME_PUSHVOICE_IN;

typedef struct tagNET_EHOME_PUSHVOICE_OUT
{
    DWORD dwSize;
    LONG  lHandle;
    BYTE  byRes[124];
}NET_EHOME_PUSHVOICE_OUT, *LPNET_EHOME_PUSHVOICE_OUT;

typedef struct tagNET_EHOME_STOPVOICETALK_STM_PARAM
{
    LONG lSessionID;
    LONG lHandle;
    BYTE  byRes[120];
}NET_EHOME_STOPVOICETALK_STM_PARAM, *LPNET_EHOME_STOPVOICETALK_STM_PARAM;

NET_DVR_API LONG CALLBACK  NET_ECMS_StartVoiceTalk(LONG lUserID, DWORD dwVoiceChan,
                                                   const NET_EHOME_VOICETALK_PARA* pVoiceTalkPara);

NET_DVR_API BOOL CALLBACK  NET_ECMS_StartVoiceWithStmServer(LONG lUserID, NET_EHOME_VOICE_TALK_IN* lpVoiceTalkIn, NET_EHOME_VOICE_TALK_OUT* lpVoiceTalkOut);
NET_DVR_API BOOL CALLBACK  NET_ECMS_StartPushVoiceStream(LONG lUserID, LPNET_EHOME_PUSHVOICE_IN lpPushParamIn, LPNET_EHOME_PUSHVOICE_OUT lpPushParamOut);
NET_DVR_API BOOL CALLBACK  NET_ECMS_StopVoiceTalk(LONG iVoiceHandle);
NET_DVR_API BOOL CALLBACK  NET_ECMS_StopVoiceTalkWithStmServer(LONG lUserID, LONG lSessionID);
NET_DVR_API BOOL CALLBACK  NET_ECMS_StopVoiceTalkWithStmServerEx(LONG lUserID, LPNET_EHOME_STOPVOICETALK_STM_PARAM pStopParam);
NET_DVR_API BOOL CALLBACK  NET_ECMS_SendVoiceTransData(LONG iVoiceHandle, const char *pSendBuf, DWORD dwBufSize);

//---------------------------------------------------------------------------------------------------------

typedef    struct    tagNET_EHOME_CONFIG
{
    void*        pCondBuf;      //[in]����������ָ�룬���ʾͨ���ŵ�
    DWORD        dwCondSize;    //[in]��pCondBufָ������ݴ�С
    void*        pInBuf;        //[in]������ʱ��Ҫ�õ���ָ��ṹ���ָ��
    DWORD        dwInSize;      //[in], pInBufָ������ݴ�С
    void*        pOutBuf;       //[out]����ȡʱ��Ҫ�õ���ָ��ṹ���ָ�룬�ڴ����ϲ����
    DWORD        dwOutSize;     //[in]����ȡʱ��Ҫ�õ�����ʾpOutBufָ����ڴ��С�� 
    BYTE         byRes[40];     //����
}NET_EHOME_CONFIG, *LPNET_EHOME_CONFIG;

typedef struct tagNET_EHOME_XML_CFG 
{
    void*      pCmdBuf;    //�ַ�����ʽ����
    DWORD      dwCmdLen;   //pCmdBuf����
    void*      pInBuf;     //��������
    DWORD      dwInSize;   //�������ݳ���
    void*      pOutBuf;    //�������
    DWORD      dwOutSize;  //�������������
    DWORD      dwSendTimeOut;  //���ݷ��ͳ�ʱʱ��,��λms��Ĭ��5s
    DWORD      dwRecvTimeOut;  //���ݽ��ճ�ʱʱ��,��λms��Ĭ��5s
    void*      pStatusBuf;     //���ص�״̬����(XML��ʽ),�������Ҫ,������NULL
    DWORD      dwStatusSize;   //״̬��������С(�ڴ��С)
    BYTE       byRes[24];
}NET_EHOME_XML_CFG, *LPNET_EHOME_XML_CFG;

#define    MAX_SERIALNO_LEN        128    //���к���󳤶�
#define    MAX_PHOMENUM_LEN        32    //�ֻ�������󳤶�
#define    MAX_DEVICE_NAME_LEN     32//�豸���Ƴ���

typedef struct tagNET_DVR_DVR_TYPE_NAME
{
    DWORD dwDVRType;
    char byDevName[24];  
}NET_DVR_TYPE_NAME;

static const NET_DVR_TYPE_NAME DVRTypeName[] = 
{
    {0,"UNKNOWN TYPE"},         /*����δ�����dvr���ͷ���NETRET_DVR*/
    {1,"DVR"},                    /*DVR*/    
    {2,"ATMDVR"},                /*atm dvr*/
    {3,"DVS"},                /*DVS*/
    {4,"DEC"},                /* 6001D */
    {5,"ENC_DEC"},                /* 6001F */
    {6,"DVR_HC"},                /*8000HC*/
    {7,"DVR_HT"},                /*8000HT*/
    {8,"DVR_HF"},                /*8000HF*/
    {9,"DVR_HS"},                /* 8000HS DVR(no audio) */
    {10,"DVR_HTS"},              /* 8016HTS DVR(no audio) */
    {11,"DVR_HB"},              /* HB DVR(SATA HD) */
    {12,"DVR_HCS"},              /* 8000HCS DVR */
    {13,"DVS_A"},              /* ��ATAӲ�̵�DVS */
    {14,"DVR_HC_S"},              /* 8000HC-S */
    {15,"DVR_HT_S"},              /* 8000HT-S */
    {16,"DVR_HF_S"},              /* 8000HF-S */
    {17,"DVR_HS_S"},              /* 8000HS-S */
    {18,"ATMDVR_S"},              /* ATM-S */
    {19,"DVR_7000H"},                /*7000Hϵ��*/
    {20,"DEC_MAT"},              /*��·������*/
    {21,"DVR_MOBILE"},                /* mobile DVR */                 
    {22,"DVR_HD_S"},              /* 8000HD-S */
    {23,"DVR_HD_SL"},                /* 8000HD-SL */
    {24,"DVR_HC_SL"},                /* 8000HC-SL */
    {25,"DVR_HS_ST"},                /* 8000HS_ST */
    {26,"DVS_HW"},              /* 6000HW */
    {27,"DS630X_D"},             /* ��·������ */
    {28,"DS640X_HD"},                /*640X���������*/
    {29,"DS610X_D"},              /*610X������*/
    {30,"IPCAM"},                /*IP �����*/
    {31,"MEGA_IPCAM"},                /*����IP����� 852F&852MF*/
    {32,"IPCAM_862MF"},                /*862MF���Խ���9000�豸*/
    {35,"ITCCAM"},                /*���ܸ������������*/
    {36,"IVS_IPCAM"},          /*���ܷ����������������*/
    {38,"ZOOMCAM"},            /*һ���*/
    {40,"IPDOME"},              /*IP �������*/
    {41,"IPDOME_MEGA200"},              /*IP 200��������*/
    {42,"IPDOME_MEGA130"},              /*IP 130��������*/
    {43,"IPDOME_AI"},              /*IP �������ܿ���*/ 
    {44,"TII_IPCAM"},          /*�����ȳ��������*/
    {50,"IPMOD"},                /*IP ģ��*/
    {59,"DS64XXHD_T"},                //64-T���������
    {60,"IDS6501_HF_P"},    // 6501 ����
    {61,"IDS6101_HF_A"},              //����ATM
    {62,"IDS6002_HF_B"},          //˫�����٣�DS6002-HF/B
    {63,"IDS6101_HF_B"},          //��Ϊ������DS6101-HF/B
    {64,"IDS52XX"},          //���ܷ�����IVMS
    {65,"IDS90XX"},                // 9000����
    {67,"IDS8104_AHL_S_H"},              // ��������ʶ�� ATM
    {68,"IDS91XX"},                // 9100����
    {69,"IIP_CAM_B"},  //������ΪIP�����
    {70,"IIP_CAM_F"},  //��������IP�����
    {71,"DS71XX_H"},                /* DS71XXH_S */
    {72,"DS72XX_H_S"},                /* DS72XXH_S */
    {73,"DS73XX_H_S"},                /* DS73XXH_S */
    {74,"DS72XX_HF_S"},              //DS72XX_HF_S
    {75,"DS73XX_HFI_S"},              //DS73XX_HFI_S
    {75,"DS73XX_HF_S"},              //DS73XX_HF_S
    {76,"DS76XX_H_S"},                /* DVR,e.g. DS7604_HI_S */
    {77,"DS76XX_N_S"},                /* NVR,e.g. DS7604_NI_S */
    {81,"DS81XX_HS_S"},                /* DS81XX_HS_S */
    {82,"DS81XX_HL_S"},                /* DS81XX_HL_S */
    {83,"DS81XX_HC_S"},                /* DS81XX_HC_S */
    {84,"DS81XX_HD_S"},                /* DS81XX_HD_S */
    {85,"DS81XX_HE_S"},                /* DS81XX_HE_S */
    {86,"DS81XX_HF_S"},                /* DS81XX_HF_S */
    {87,"DS81XX_AH_S"},                /* DS81XX_AH_S */
    {88,"DS81XX_AHF_S"},                /* DS81XX_AHF_S */
    {90,"DS90XX_HF_S"},              /*DS90XX_HF_S*/
    {91,"DS91XX_HF_S"},              /*DS91XX_HF_S*/
    {92,"DS91XX_HD_S"},              /*91XXHD-S(MD)*/
    {93,"IDS90XX_A"},                // 9000���� ATM
    {94,"IDS91XX_A"},                // 9100���� ATM
    {95,"DS95XX_N_S"},              /*DS95XX_N_S NVR �����κ����*/
    {96,"DS96XX_N_SH"},              /*DS96XX_N_SH NVR*/
    {97,"DS90XX_HF_SH"},              /*DS90XX_HF_SH */   
    {98,"DS91XX_HF_SH"},              /*DS91XX_HF_SH */
    {100,"DS_B10_XY"},             /*��Ƶ�ۺ�ƽ̨�豸�ͺ�(X:�����Ƭ����Y:�����Ƭ��)*/
    {101,"DS_6504HF_B10"},             /*��Ƶ�ۺ�ƽ̨�ڲ�������*/
    {102,"DS_6504D_B10"},             /*��Ƶ�ۺ�ƽ̨�ڲ�������*/
    {103,"DS_1832_B10"},             /*��Ƶ�ۺ�ƽ̨�ڲ������*/
    {104,"DS_6401HFH_B10"},             /*��Ƶ�ۺ�ƽ̨�ڲ����˰�*/
    {105,"DS_65XXHC"},                //65XXHC DVS
    {106,"DS_65XXHC_S"},                //65XXHC-SATA DVS
    {107,"DS_65XXHF"},                //65XXHF DVS
    {108,"DS_65XXHF_S"},                //65XXHF-SATA DVS
    {109,"DS_6500HF_B"},             //65 rack DVS
    {110,"IVMS_6200_C"},            // iVMS-6200(/C)  
    {111,"IVMS_6200_B"},             // iVMS-6200(/B)
    {112,"DS_72XXHV_ST"},                //72XXHV_ST15 DVR
    {113,"DS_72XXHV_ST"},                //72XXHV_ST20 DVR,�������豸��ʾһ������
    {114,"IVMS_6200_T"},             // IVMS-6200(/T)
    {115,"IVMS_6200_BP"},             // IVMS-6200(/BP)
    {116,"DS_81XXHC_ST"},                //DS_81XXHC_ST
    {117,"DS_81XXHS_ST"},                //DS_81XXHS_ST
    {118,"DS_81XXAH_ST"},                //DS_81XXAH_ST
    {119,"DS_81XXAHF_ST"},                //DS_81XXAHF_ST
    {120,"DS_66XXDVS"},                //66XX DVS
    {121,"DS_1964_B10"},             /*��Ƶ�ۺ�ƽ̨�ڲ�������*/
    {122,"DS_B10N04_IN"},             /*��Ƶ�ۺ�ƽ̨�ڲ���������*/
    {123,"DS_B10N04_OUT"},             /*��Ƶ�ۺ�ƽ̨�ڲ��������*/
    {124,"DS_B10N04_INTEL"},             /*��Ƶ�ۺ�ƽ̨�ڲ�����*/
    {125,"DS_6408HFH_B10E_RM"},             //V6����
    {126,"DS_B10N64F1_RTM"},             //V6��������DSP
    {127,"DS_B10N64F1D_RTM"},             //V6������DSP
    {128,"DS_B10_SDS"},             //��Ƶ�ۺ�ƽ̨���������
    {129,"DS_B10_DS"},             //��Ƶ�ۺ�ƽ̨�������
    {130,"DS_6401HFH_B10V"},             //VGA���������
    {131,"DS_6504D_B10B"},             /*��Ƶ�ۺ�ƽ̨�ڲ����������*/
    {132,"DS_6504D_B10H"},             /*��Ƶ�ۺ�ƽ̨�ڲ����������*/
    {133,"DS_6504D_B10V"},             /*��Ƶ�ۺ�ƽ̨�ڲ�VGA������*/
    {134,"DS_6408HFH_B10S"},             //��Ƶ�ۺ�ƽ̨SDI�Ӱ� 
    {135,"DS_18XX_N"},             /* �����������*/ 
    //ע��121��140Ԥ������Ƶ�ۺ�ƽ̨ϵ�в�Ʒʹ��,141~160��������豸�ͱ����豸����
    {141,"DS_18XX_PTZ"},                /*����������Ʒ*/
    {142,"DS_19AXX"},                /*ͨ�ñ����������Ʒ*/
    {143,"DS_19BXX"},                /*���ñ�������*/
    {144,"DS_19CXX"},                /*�������б�������*/
    {145,"DS_19DXX"},                /*������ر�������*/    
    {146,"DS_19XX"},             /*1900ϵ�б�������*/ 
    {147,"DS_19SXX"},                /*��Ƶ��������*/
    {148, "DS_1HXX"},            /*CS���Ʒ*/ //������
    /**********************�豸���� end***********************/
    //2011-11-03 161~170����������豸ʹ��
    {161,"DS_C10H"},           /*����������*/
    {162,"DS_C10N_BI"},            //BNC������
    {163,"DS_C10N_DI"},            //rbg������
    {164,"DS_C10N_SI"},            //����������
    {165,"DS_C10N_DO"},            //��ʾ������
    {166,"DS_C10N_SERVER"},        //�ֲ�ʽ������
    // 171- 180  ��������ʹ��
    {171,"IDS_8104_AHFL_S_H"},             // 8104ATM 
    {172,"IDS_65XX_HF_A"},             // 65 ATM
    {173,"IDS90XX_HF_RH"},             // 9000 ����RH
    {174,"IDS91XX_HF_RH"},             // 9100 ����RH�豸
    {175,"IDS_65XX_HF_B"},             // 65 ��Ϊ����
    {176,"IDS_65XX_HF_P"},             // 65 ����ʶ��
    {177,"IVMS_6200_F"},     // IVMS-6200(/F)
    {178,"IVMS_6200_A"},             //iVMS-6200(/A)
    {179,"IVMS_6200_F_S"},   //iVMS-6200(/F_S)
    {181,"DS90XX_HF_RH"},             // 9000 RH
    {182,"DS91XX_HF_RH"},             // 9100 RH�豸
    {183,"DS78XX_S"},             // 78ϵ���豸
    {185,"DS81XXHW_S"},                // 81 Resolution 960 
    {186,"DS81XXHW_ST"},             // DS81XXHW_ST
    {187,"DS91XXHW_ST"},             // DS91XXHW_ST
    {188,"DS91XX_ST"},             // DS91XX_ST
    {189,"DS81XX_ST"},             // DS81XX_ST
    {190,"DS81XXH_ST"},             // DS81XXHDI_ST,DS81XXHE_ST ky2012
    {191,"DS73XXH_ST"},             // DS73XXHI_ST ky2012
    {192,"DS81XX_SH"},             // ��Ѷ81SH,81SHF
    {193,"DS81XX_SN"},             // ��Ѷ81SNL
    {194,"DS96XXN_ST"},             //NVR:DS96xxN_ST
    {195,"DS86XXN_ST"},             //NVR:DS86xxN_ST
    {196,"DS80XXHF_ST"},             //DVR:DS80xxHF_ST
    {197,"DS90XXHF_ST"},             //DVR:DS90xxHF_ST
    {198,"DS76XXN_ST"},             //NVR:DS76xxN_ST
    {199,"DS_9664N_RX"},         //Ƕ��ʽNVR(64·IPͨ������ģ��ͨ��)�����һ��X��T/H    
    {200,"ENCODER_SERVER"},            // ���뿨������
    {201,"DECODER_SERVER"},         // ���뿨������
    {202,"PCNVR_SERVER"},         // PCNVR�洢������
    {203,"CVR_SERVER"},         // ��ŵCVR�������Լ���������ΪDVR_S-1
    {204,"DS_91XXHFH_ST"},         // 91ϵ��HD-SDI����DVR
    {205,"DS_66XXHFH"},         // 66���������
    {210,"TRAFFIC_TS_SERVER"},         //�ն˷�����
    {211,"TRAFFIC_VAR"},         //��Ƶ������¼��
    {212,"IPCALL"},              //IP���ӶԽ��ֻ�

    //2012-03-21 ����ֵ255�Ժ���豸��Ҫ������������У��������������Ϊ��ʹ��չЭ���ܻ�ȡ����ֵ255�����豸������
    //{2001, "DS90XXHW_ST"}        // DS90XXHW_ST���DVR
};


/**********************�豸���� begin**********************/

/* dvr��� 1-50 */
#define DEV_CLASS_DVR               1   //��ͨdvr����
#define DEV_CLASS_INTERROGATION     2   //��Ѷ��
#define DEV_CLASS_SIMPLE_TRAIL      3   //����ͥ������
#define DEV_CLASS_TRAIL             4   //��׼ͥ������
#define DEV_CLASS_RECORD_PLAY       5   //¼������
#define DEV_CLASS_ATM               6   //ATM��

/* dvs��� 51-100 */
#define DEV_CLASS_DVS               51  //��ͨdvs

/* nvr��� 101-150 */
#define DEV_CLASS_NVR               101 //��ͨnvr

/* ipc��� 151-200 */
#define DEV_CLASS_GUN               151 //ipcǹ��
#define DEV_CLASS_BALL              152 //ipc���
#define DEV_CLASS_SNAP              153 //ץ�Ļ�
#define DEV_CLASS_INTELLI_TILT      154 //������̨
#define DEV_CLASS_FISH_EYE          155 //����
#define DEV_CLASS_2DP_Z             156 //��ӥ��
#define DEV_CLASS_2DP               157 //Сӥ��
#define DEV_CLASS_PT                158 //ȫ��ϸ�����
#define DEV_CLASS_TRI               159 //����Ƶ�̶�ʽ������

/* CVR��� 201 - 250*/
#define DEV_CLASS_CVR               201 //CVR

/* ������� 251 - 300*/
#define DEV_CLASS_B20                   251 //����B20ϵ��
#define DEV_CLASS_B10                   252 //����B10ϵ��
#define DEV_CLASS_DECODER               253 //������
#define DEV_CLASS_MATRIXMANAGEDEVICE    254 //�����������
#define DEV_CLASS_OTICAL                255 //��˻�
#define DEV_CLASS_CODESPITTER           256 //�����
#define DEV_CLASS_ALARMHOST             257 //��ҵ��������
#define DEV_CLASS_MOVING_RING           258 //�����豸
#define DEV_CLASS_CVCS                  259 //����ʽ����������
#define DEV_CLASS_DVCS                  260 //�ֲ�ʽ����������
#define DEV_CLASS_TRANSCODER            261 //ת����
#define DEV_CLASS_LCD_SCREEN            262 //LCD��Ļ
#define DEV_CLASS_LED_SCREEN            263 //LED��Ļ
#define DEV_CLASS_MATRIX                264 //����
#define DEV_CLASS_CONFERENCE_SYSTEM     265 //��Ƶ�����豸
#define DEV_CLASS_INFORMATION_RELEASE_EQUIPMENT 266 //��Ϣ�����豸
#define DEV_CLASS_NET_GAP               267 //��բ
#define DEV_CLASS_MERGE                 268 //������
#define DEV_CLASS_REAR_PROJECTION       269 //��Ͷ��ʾ�豸
#define DEV_CLASS_SWITCH                270 //������
#define DEV_CLASS_FIBER_CONVERTER       271 //�����շ���
#define DEV_CLASS_SCREEN_SERVER         272 //��Ļ������
#define DEV_CLASS_SCE_SERVER            273 //ץ��������
#define DEV_CLASS_WIRELESS_TRANS        274 //���ߴ����豸
#define DEV_CLASS_Y10_SERIES            275 //Y10ϵ��
#define DEV_CLASS_SAFETY_MAVHINE        276 //����һ���
#define DEV_CLASS_IOTGATEWAY            277 //����������
/* ����������� 301 - 350*/
#define DEV_CLASS_VIDEO_ALARM_HOST      301 //��Ƶ��������
#define DEV_CLASS_NET_ALARM_HOST        302 //���籨������
#define DEV_CLASS_ONE_KEY_ALARM         303 //һ��ʽ������Ʒ
#define DEV_CLASS_WIRELESS_ALARM_HOST   304 //���߱�������
#define DEV_CLASS_ALARM_MODULE          305 //����ģ��
#define DEV_CLASS_HOME_ALARM_HOST       306 //���ñ�������

/* �Ž���� 351 - 400*/
#define DEV_CLASS_ACCESS_CONTROL        351 //�Ž���Ʒ

/* ���ӶԽ� 401 - 450*/
#define DEV_CLASS_VIDEO_INTERCOM        401 //���ӶԽ�

/* ���˻� 451 - 500*/
#define DEV_CLASS_UMMANNED_AERIAL_VEHICLE   451 //���˻���Ʒ

/* �ƶ���Ʒ: 501-550*/
#define DEV_CLASS_MOBILE                501 //�ƶ���Ʒ

/* �ƶ������豸: 551-600*/
#define DEV_CLASS_MOBILE_VEHICLE        551 //�ƶ������豸

//���ܷ����ǣ�601-650
#define DEV_CLASS_INTELLIGENT_ANALYZER  601 //���ܷ�����

//���ܽ�ͨ��������651-700
#define DEV_CLASS_INTELLIGENT_TRAFFIC_SERVER    651 //���ܽ�ͨ������
#define DS_TP2200_EC                            652 //�����ͻ�������

/* nvs��� 701-750 */
#define DEV_CLASS_NVS           701 //��ͨnvs

/*��ԴRFIDϵ�� 751-800*/
#define DS_TRI21A_1_P           751 //��ԴRFID��ȡ��

/* ���������豸801-850 */
#define DS_CLASS_FA             801 //���׵���
#define DS_CLASS_PURE           802 //���״�����
#define DS_CLASS_FS             803 //������̬���ݷ�����
#define DS_CLASS_FD             804 //ץ�ļ�������
#define DS_CLASS_HAWK           805 //��ӥ������
#define DS_CLASS_BLADE          806 //����
#define DS_CLASS_HMCP           807 //ģ�ͶԱȷ�����

/* ��������� 851 - 900*/
#define DEV_CLASS_SMART_LOCK    851 //����������

/* �״���� 901 - 950*/
#define DEV_CLASS_RADAR         901 //�״��Ʒ

/* �ǻ�������� 951 - 1000*/
#define DEV_CLASS_FIRE_CONTROL   951 //������Ʒ

/*ȫ��ϸ������� 8451-8470*/
#define iDS_PT                  8451    //ȫ��ϸ�����

/* �����豸���� 65534 */
#define DEV_CLASS_DEFAULT       65534   //Ĭ���豸����
/**********************�豸���� end**********************/

typedef struct tagNET_EHOME_DEVICE_INFO
{
    DWORD   dwSize;             //�ṹ���С
    DWORD   dwChannelNumber;    //ģ����Ƶͨ������
    DWORD   dwChannelAmount;    //����Ƶͨ������ģ��+IP��
    DWORD   dwDevType;          //�豸���ͣ�1-DVR��3-DVS��30-IPC��40-IPDOME������ֵ�ο�����NetSdk�豸���ͺŶ���ֵ
    DWORD   dwDiskNumber;       //�豸��ǰӲ����
    BYTE    sSerialNumber[MAX_SERIALNO_LEN];    //�豸���к�
    DWORD   dwAlarmInPortNum;   //ģ��ͨ�������������
    DWORD   dwAlarmInAmount;    //�豸�ܱ����������
    DWORD   dwAlarmOutPortNum;  //ģ��ͨ�������������
    DWORD   dwAlarmOutAmount;   //�豸�ܱ����������
    DWORD   dwStartChannel;     //��Ƶ��ʼͨ����
    DWORD   dwAudioChanNum;     //�����Խ�ͨ���������豸ͨ��+IPͨ����byStartDTalkChan����
    DWORD   dwMaxDigitChannelNum;   //�豸֧�ֵ��������ͨ��·��
    DWORD   dwAudioEncType;     //�����Խ���Ƶ��ʽ��0-G722��1-G711U��2-G711A��3-G726��4-AAC��5-MP2L2,6-PCM,7-MP3
    BYTE    sSIMCardSN[MAX_SERIALNO_LEN];       //�����豸��չ��SIM�����к�
    BYTE    sSIMCardPhoneNum[MAX_PHOMENUM_LEN]; //������չ��SIM���ֻ�����
    DWORD   dwSupportZeroChan;  // SupportZeroChan:֧����ͨ���ĸ�����0-��֧�֣�1-֧��1·��2-֧��2·���Դ�����
    DWORD   dwStartZeroChan;    //��ͨ����ʼ��ţ�Ĭ��10000
    DWORD   dwSmartType;        //�������ͣ�0-smart��1-רҵ���ܣ�Ĭ��0-smart
    WORD    wDevClass;          //�豸����
    BYTE     byStartDTalkChan;    //��ʼ���ֶԽ�ͨ���ţ�������ģ��Խ�ͨ���ţ�0��ʾ�����ֶԽ�ͨ��
    BYTE    byRes[157];         //����
}NET_EHOME_DEVICE_INFO,*LPNET_EHOME_DEVICE_INFO;

#define MAX_VERSION_LEN     32   //�汾��������

typedef struct tagNET_EHOME_VERSION_INFO
{
    DWORD   dwSize; //�ṹ���С
    BYTE    sSoftwareVersion[MAX_VERSION_LEN];      //���ذ汾
    BYTE    sDSPSoftwareVersion[MAX_VERSION_LEN];   //����汾
    BYTE    sPanelVersion[MAX_VERSION_LEN];         //���汾
    BYTE    sHardwareVersion[MAX_VERSION_LEN];      //Ӳ���汾
    BYTE    byRes[124];
}NET_EHOME_VERSION_INFO,*LPNET_EHOME_VERSION_INFO;

typedef struct tagNET_EHOME_DEVICE_CFG
{
    DWORD        dwSize;            //�ṹ���С
    BYTE         sServerName[MAX_DEVICE_NAME_LEN];  //�豸����
    DWORD        dwServerID;        //�豸�ţ�ң�������:0~255��
    DWORD        dwRecycleRecord;   //�Ƿ�ѭ��¼��0����ѭ����1����ѭ��
    DWORD        dwServerType;      //�豸���ͣ�ͬDevType�����ڹ�˾�豸�ͺ��м��ٸ�����Э����ֻʹ��ͨ���ͺţ�1-DVR��3-DVS��30-IPC��40-IPDOME
    DWORD        dwChannelNum;      //ͨ������������ģ��+IPͨ����ֻ����
    DWORD        dwHardDiskNum;     //Ӳ�̸�����ֻ����
    DWORD        dwAlarmInNum;      //�������������ģ��ͨ������ֻ����
    DWORD        dwAlarmOutNum;     //�������������ģ��ͨ������ֻ����
    DWORD        dwRS232Num;        //232���ڸ�����ֻ����
    DWORD        dwRS485Num;        //485���ڸ�����ֻ����
    DWORD        dwNetworkPortNum;  //����ڸ�����ֻ����
    DWORD        dwAuxoutNum;       //���ڸ�����ֻ����
    DWORD        dwAudioNum;        //�����ڸ�����ֻ����
    BYTE         sSerialNumber[MAX_SERIALNO_LEN];   //�豸���кţ�ֻ����
    DWORD        dwMajorScale;      //�������ţ�0�������ţ�1��������
    DWORD        dwMinorScale;      //�������ţ�0�������ţ�1��������
    BYTE         byRes[292];        //����
}NET_EHOME_DEVICE_CFG,*LPNET_EHOME_DEVICE_CFG;

#define NET_EHOME_GET_DEVICE_INFO       1   //��ȡ�豸��Ϣ
#define NET_EHOME_GET_VERSION_INFO      2   //��ȡ�汾��Ϣ
#define NET_EHOME_GET_DEVICE_CFG        3   //��ȡ�豸��������
#define NET_EHOME_SET_DEVICE_CFG        4   //�����豸��������

#define NET_EHOME_GET_GPS_CFG           20  //��ȡGPS����
#define NET_EHOME_SET_GPS_CFG           21  //����GPS����
#define NET_EHOME_GET_PIC_CFG           22  //��ȡOSD��ʾ����
#define NET_EHOME_SET_PIC_CFG           23  //����OSD��ʾ����
#define NET_EHOME_GET_WIRELESSINFO_CFG  24  //��ȡ����������Ϣ����
#define NET_EHOME_SET_WIRELESSINFO_CFG  25  //��������������Ϣ����

#define MAX_EHOME_PROTOCOL_LEN          1500

typedef struct tagNET_EHOME_REMOTE_CTRL_PARAM
{
    DWORD   dwSize;
    void*   lpCondBuffer;        //��������������
    DWORD   dwCondBufferSize;    //������������������
    void*   lpInbuffer;          //���Ʋ���������
    DWORD   dwInBufferSize;      //���Ʋ�������������
    BYTE    byRes[32];
}NET_EHOME_REMOTE_CTRL_PARAM, *LPNET_EHOME_REMOTE_CTRL_PARAM;

//GPS����
typedef struct tagNET_EHOME_GPS_CFG
{
    DWORD        dwSize;
    DWORD        dwTransInterval;   //GPS�ϴ�ʱ�䣬��λ����
    DWORD        dwMaxSpeed;        //��������ֵ����λ������/Сʱ
    DWORD        dwMinSpeed;        //��������ֵ����λ������/Сʱ
    BYTE         bEnable;           //ʹ��,1-�����ã�2-����
    BYTE         byRes[63];         //����
}NET_EHOME_GPS_CFG, *LPNET_EHOME_GPS_CFG;

//OSD��ʾ����
typedef struct tagNET_EHOME_PIC_CFG
{
    DWORD           dwSize;
    BYTE            byChannelName[NAME_LEN];    //ͨ�����ƣ�GB2312���룬 V30�Ժ�汾ʹ��UTF-8���룩�����Ȳ�����31�ֽ�
    BOOL            bIsShowChanName;            //�Ƿ���ʾͨ�����ƣ�0������ʾ��1����ʾ
    WORD            wChanNameXPos;              //ͨ��������ʾX���꣬����704x576������
    WORD            wChanNameYPos;              //ͨ��������ʾY���꣬����704x576�����ã�����ֵΪ16�ı���
    BOOL            bIsShowOSD;                 //�Ƿ���ʾOSD��0������ʾ��1����ʾ
    WORD            wOSDXPos;                   //OSD��ʾX����
    WORD            wOSDYPos;                   //OSD��ʾY����
    BYTE            byOSDType;                  /**OSD���� 0:XXXX-XX-XX(������) 1:XX-XX-XXXX(������) 2:XXXX��XX��XX��
                                                    3:XX��XX��XXXX�� 4:XX-XX-XXXX(������) 5:XX��XX��XXXX��
                                                */
    BYTE            byOSDAtrib;                 //OSD���� 0������ʾOSD 1��͸������˸ 2��͸��������˸ 3����˸����͸�� 4����͸��������˸
    BYTE            byRes1[2];                  //����1
    BOOL            bIsShowWeek;                //�Ƿ���ʾ���ڣ�0������ʾ��1����ʾ
    BYTE            byRes2[64];                 //����2
}NET_EHOME_PIC_CFG, *LPNET_EHOME_PIC_CFG;

typedef struct tagNET_EHOME_WIRELESS_INFO_CFG
{
    DWORD        dwSize;
    DWORD        dwInfoTransInterval;   //�ϴ����,��λ����
    BYTE         byEnable;              //ʹ�ܣ�0-������ 1-����
    BYTE         byRes[47];
}NET_EHOME_WIRELESS_INFO_CFG, *LPNET_EHOME_WIRELESS_INFO_CFG;

#define STREAM_KEY_LEN  32

typedef struct tagNET_EHOME_STREAM_PASSWORD
{
    BYTE byEnable;                  // ���ܲ�����0- �����ã�1- ����, 2- �޸�����
    BYTE byRes1[3];
    BYTE byNewKey[STREAM_KEY_LEN];  // ����
    BYTE byOldKey[STREAM_KEY_LEN];  //ԭ����
    BYTE byRes[12];
}NET_EHOME_STREAM_PASSWORD, *LPNET_EHOME_STREAM_PASSWORD;

NET_DVR_API BOOL CALLBACK NET_ECMS_GetDevConfig(LONG lUserID, DWORD dwCommand, LPNET_EHOME_CONFIG lpConfig, DWORD dwConfigSize);

NET_DVR_API BOOL CALLBACK NET_ECMS_SetDevConfig(LONG lUserID, DWORD dwCommand, LPNET_EHOME_CONFIG lpConfig, DWORD dwConfigSize);

NET_DVR_API BOOL CALLBACK NET_ECMS_XMLConfig(LONG lUserID, LPNET_EHOME_XML_CFG pXmlCfg, DWORD dwConfigSize);

NET_DVR_API BOOL CALLBACK NET_ECMS_RemoteControl(LONG lUserID, DWORD dwCommand, LPNET_EHOME_REMOTE_CTRL_PARAM lpCtrlParam);

NET_DVR_API BOOL CALLBACK NET_ECMS_CheckStreamEncrypt(LONG lUserID, const char* pStreamEncrypt);

//�����豸SessionKey��Ϣ
NET_DVR_API BOOL CALLBACK NET_ECMS_SetDeviceSessionKey(NET_EHOME_DEV_SESSIONKEY* pDeviceKey);
//��ȡ�豸EhomeKey��Ϣ
NET_DVR_API BOOL CALLBACK NET_ECMS_GetDeviceSessionKey(NET_EHOME_DEV_SESSIONKEY* pDeviceKey);
//����5.0�豸ע��״̬
NET_DVR_API BOOL CALLBACK NET_ECMS_ResetDevRegisterState(const char* sDeviceID);

//Ԥ������
typedef struct tagNET_EHOME_PREVIEWINFO_IN
{
    int     iChannel;     //ͨ���� 
    DWORD   dwStreamType; // �������ͣ�0-��������1-������, 2-��������,3- ��������
    DWORD   dwLinkMode;   // 0��TCP��ʽ,1��UDP��ʽ,2: HRUDP��ʽ  
    NET_EHOME_IPADDRESS struStreamSever;    //��ý���ַ
}NET_EHOME_PREVIEWINFO_IN, *LPNET_EHOME_PREVIEWINFO_IN;

typedef struct tagNET_EHOME_PREVIEWINFO_IN_V11
{
    int     iChannel;
    DWORD   dwStreamType; // �������ͣ�0-��������1-������, 2-��������,3- ��������
    DWORD   dwLinkMode;
    NET_EHOME_IPADDRESS struStreamSever;
    BYTE    byDelayPreview;
    BYTE    byEncrypt;    //0-�����ܣ�1-����
    BYTE    byRes[30];
}NET_EHOME_PREVIEWINFO_IN_V11, *LPNET_EHOME_PREVIEWINFO_IN_V11;

typedef struct tagNET_EHOME_MAKE_I_FRAME
{
    int     iChannel;       // ͨ����
    DWORD   dwStreamType;   // �������ͣ�0- ��������1- ������, 2- Ԥ�� 
    BYTE    byRes[40];
}NET_EHOME_MAKE_I_FRAME, *LPNET_EHOME_MAKE_I_FRAME;


typedef struct tagNET_EHOME_PREVIEWINFO_OUT
{
    LONG  lSessionID;
    LONG  lHandle;      //������ȡ���첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ
    BYTE  byRes[124];
}NET_EHOME_PREVIEWINFO_OUT, *LPNET_EHOME_PREVIEWINFO_OUT;

typedef struct tagNET_EHOME_PUSHSTREAM_IN
{
    DWORD dwSize;
    LONG  lSessionID; 
    BYTE  byRes[128];
}NET_EHOME_PUSHSTREAM_IN, *LPNET_EHOME_PUSHSTREAM_IN;

typedef struct tagNET_EHOME_PUSHSTREAM_INFO_OUT
{
    DWORD dwSize;
    LONG  lHandle;  //������ȡ���첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ
    BYTE  byRes[124];
}NET_EHOME_PUSHSTREAM_OUT, *LPNET_EHOME_PUSHSTREAM_OUT;

typedef struct tagNET_EHOME_STOPSTREAM_PARAM
{
    LONG  lSessionID;
    LONG  lHandle;
    BYTE  byRes[120];
}NET_EHOME_STOPSTREAM_PARAM, *LPNET_EHOME_STOPSTREAM_PARAM;

NET_DVR_API BOOL CALLBACK NET_ECMS_StartGetRealStream(LONG lUserID, LPNET_EHOME_PREVIEWINFO_IN pPreviewInfoIn, LPNET_EHOME_PREVIEWINFO_OUT pPreviewInfoOut ); //lUserID��SDK������û�ID�����豸ע��ص�ʱfDeviceRegisterCallBack����
NET_DVR_API BOOL CALLBACK NET_ECMS_StartGetRealStreamV11(LONG lUserID, LPNET_EHOME_PREVIEWINFO_IN_V11 pPreviewInfoIn, LPNET_EHOME_PREVIEWINFO_OUT pPreviewInfoOut);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopGetRealStream(LONG lUserID, LONG lSessionID);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopGetRealStreamEx(LONG lUserID, LPNET_EHOME_STOPSTREAM_PARAM pStopParam);

NET_DVR_API BOOL CALLBACK NET_ECMS_StartPushRealStream(LONG lUserID, LPNET_EHOME_PUSHSTREAM_IN pPushInfoIn, LPNET_EHOME_PUSHSTREAM_OUT pPushInfoOut);
NET_DVR_API BOOL CALLBACK NET_ECMS_MakeIFrame(LONG lUserID, LPNET_EHOME_MAKE_I_FRAME pIFrameParma);
NET_DVR_API BOOL CALLBACK NET_ECMS_SetStreamEncrypt(LONG lUserID, LPNET_EHOME_STREAM_PASSWORD pStreamPassword);
NET_DVR_API BOOL CALLBACK NET_ECMS_WakeUp(LONG lUserID);

//��ѯ�ӿ�
#define MAX_FILE_NAME_LEN  100
#define LEN_32             32

typedef enum tagSEARCH_TYPE
{
    ENUM_SEARCH_TYPE_ERR        = -1,
    ENUM_SEARCH_RECORD_FILE     = 0,    //����¼���ļ�
    ENUM_SEARCH_PICTURE_FILE    = 1,    //����ͼƬ�ļ�
    ENUM_SEARCH_FLOW_INFO       = 2,    //������ѯ
    ENUM_SEARCH_DEV_LOG         = 3,    //�豸��־��ѯ
    ENUM_SEARCH_ALARM_HOST_LOG  = 4,    //����������־��ѯ
}SEARCH_TYPE_ENUM;

typedef enum
{
    ENUM_GET_NEXT_STATUS_SUCCESS    = 1000, //�ɹ���ȡ��һ�����ݣ������걾�����ݺ���Ҫ�ٴε���FindNext��ȡ��һ������
    ENUM_GET_NETX_STATUS_NO_FILE,           //û���ҵ�һ������
    ENUM_GET_NETX_STATUS_NEED_WAIT,         //���ݻ�δ��������ȴ�����������FindNext����
    ENUM_GET_NEXT_STATUS_FINISH,            //����ȫ��ȡ��
    ENUM_GET_NEXT_STATUS_FAILED,            //�����쳣
    ENUM_GET_NEXT_STATUS_NOT_SUPPORT        //�豸��֧�ָò�������֧�ֵĲ�ѯ����
}SEARCH_GET_NEXT_STATUS_ENUM;

//ʱ�����
typedef struct tagNET_EHOME_TIME
{
    WORD    wYear;      //��
    BYTE    byMonth;    //��
    BYTE    byDay;      //��
    BYTE    byHour;     //ʱ
    BYTE    byMinute;   //��
    BYTE    bySecond;   //��
    BYTE    byRes1;
    WORD    wMSecond;   //����
    BYTE    byRes2[2];
}NET_EHOME_TIME, *LPNET_EHOME_TIME;

typedef struct tagNET_EHOME_FINDCOND
{
    DWORD               dwSize;
    LONG                iChannel;           //ͨ���ţ���1��ʼ
    DWORD               dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    NET_EHOME_TIME      struStartTime;      //��ʼʱ��
    NET_EHOME_TIME      struStopTime;       //����ʱ��
    SEARCH_TYPE_ENUM    enumSearchType;     //�������� 0-¼���ļ����ң���ӦstruRecordFileParam  1-ͼƬ�ļ����ң���ӦstruPicFileParam 2-������ѯ����ӦstruFlowParam
    union
    {
        BYTE           byLen[64];
        struct
        {
            DWORD       dwFileType;         /**�ļ����ͣ��ֽ�����������
                                            0xff-ȫ������¼�񣨲�����ͼƬ���ͣ� 
                                            0-��ʱ¼��
                                            1-�ƶ�����
                                            2-��������
                                            3-����|����
                                            4-����&����
                                            5-�����
                                            6-�ֶ�¼��
                                            7-�𶯱���
                                            8-��������
                                            9-���ܱ���������ȡ֤¼��
                                            10��0x0a��-PIR����
                                            11��0x0b��-���߱���
                                            12��0x0c��-���ȱ���
                                            13��0x0d��ȫ������
                                            100-ȫ������ͼƬ
                                            101-����ʶ��ͼƬ
                                            102-���鱨��ͼƬ
                                            103-�ֶ�ץ��ͼƬ
                                            104-�ط�ץ��ͼƬ
                                            **/

       }struRecordFileParam;
        struct
        {
            DWORD       dwFileType;         /*255��0xff��-ȫ�����ͣ�
                                            0��0x00��-��ʱץͼ
                                            1��0x01��-�ƶ����ץͼ
                                            2��0x02��-����ץͼ
                                            3��0x03��-����|�ƶ����ץͼ
                                            4��0x04��-����&�ƶ����ץͼ
                                            5��0x05��-�����ץͼ
                                            6��0x06��-�ֶ�ץͼ
                                            7��0x07��-�𶯱���ץͼ
                                            8��0x08��-������������ץͼ
                                            9��0x09��-���ܱ���ͼƬ
                                            10��0x0a��-PIR����ͼƬ
                                            11��0x0b��-���߱���ͼƬ
                                            12��0x0c��-���ȱ���ͼƬ
                                            13��0x0d��-�������ͼƬ
                                            14��0x0e��-Խ�����ͼƬ
                                            15��0x0f��-�����������ͼƬ
                                            16��0x10��-����������ͼƬ
                                            17��0x11��-�豸���ػط�ʱ��ͼ
                                            18��0x12��-�������ͼƬ
                                            19��0x13��-�����������ͼƬ
                                            20��0x14��-�뿪�������ͼƬ
                                            21��0x15��-�ǻ����ͼƬ
                                            22��0x16��-��Ա�ۼ����ͼƬ
                                            23��0x17��-�����˶����ͼƬ
                                            24��0x18��-ͣ�����ͼƬ
                                            25��0x19��-��Ʒ�������ͼƬ
                                            26��0x1a��-��Ʒ��ȡ���ͼƬ
                                            27��0x1b��-�������ͼƬ
                                            28��0x1c��-�ͻ����ϴ�ͼƬ
                                            */
        }struPicFileParam;
        struct
        {
            BYTE        bySearchMode;       //��ѯģʽ��1-��year��ѯ��2-��month��ѯ��3-��day��ѯ
        }struFlowParam;
    }unionSearchParam;
	BYTE                byStartIndex;       //��ѯ��ʼλ�ã������ϰ汾���°汾�в�����ʹ��
	BYTE                byRes1[3];
	DWORD               dwStartIndexEx;     //��չ��Ĳ�ѯ��ʼλ�ã� ���ӶԼ�¼���������֧��
	BYTE                byRes[124];
}NET_EHOME_FINDCOND, *LPNET_EHOME_FINDCOND;

//¼���ļ���������
typedef struct tagNET_EHOME_REC_FILE_COND
{
    DWORD           dwChannel;          //ͨ���ţ���1��ʼ
    DWORD           dwRecType;          /*0xff-ȫ������¼�񣨲�����ͼƬ���ͣ�
                                        0-��ʱ¼��
                                        1-�ƶ�����
                                        2-��������
                                        3-����|����
                                        4-����&����
                                        5-�����
                                        6-�ֶ�¼��
                                        7-�𶯱���
                                        8-��������
                                        9-���ܱ���������ȡ֤¼��
                                        10��0x0a��-PIR����
                                        11��0x0b��-���߱���
                                        12��0x0c��-���ȱ���
                                        13��0x0d��ȫ������
                                        100-ȫ������ͼƬ
                                        101-����ʶ��ͼƬ
                                        102-���鱨��ͼƬ
                                        103-�ֶ�ץ��ͼƬ
                                        104-�ط�ץ��ͼƬ
                                        */
    NET_EHOME_TIME  struStartTime;      //��ʼʱ��
    NET_EHOME_TIME  struStopTime;       //����ʱ��
    DWORD           dwStartIndex;       //��ѯ��ʼλ��
    DWORD           dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    BYTE            byLocalOrUTC;       //0-struStartTime��struStopTime�У���ʾ�����豸����ʱ�䣬���豸OSDʱ��  1-struStartTime��struStopTime�У���ʾ����UTCʱ��
    BYTE            byRes[63];
}NET_EHOME_REC_FILE_COND, *LPNET_EHOME_REC_FILE_COND;

//ͼƬ�ļ���������
typedef struct tagNET_EHOME_PIC_FILE_COND
{
    DWORD           dwChannel;          //ͨ���ţ���1��ʼ
    DWORD           dwPicType;          /*255��0xff��-ȫ������
                                        0��0x00��-��ʱץͼ
                                        1��0x01��-�ƶ����ץͼ
                                        2��0x02��-����ץͼ
                                        3��0x03��-����|�ƶ����ץͼ
                                        4��0x04��-����&�ƶ����ץͼ
                                        5��0x05��-�����ץͼ
                                        6��0x06��-�ֶ�ץͼ
                                        7��0x07��-�𶯱���ץͼ
                                        8��0x08��-������������ץͼ
                                        9��0x09��-���ܱ���ͼƬ
                                        10��0x0a��-PIR����ͼƬ
                                        11��0x0b��-���߱���ͼƬ
                                        12��0x0c��-���ȱ���ͼƬ
                                        13��0x0d��-�������ͼƬ
                                        14��0x0e��-Խ�����ͼƬ
                                        15��0x0f��-�����������ͼƬ
                                        16��0x10��-����������ͼƬ
                                        17��0x11��-�豸���ػط�ʱ��ͼ
                                        18��0x12��-�������ͼƬ
                                        19��0x13��-�����������ͼƬ
                                        20��0x14��-�뿪�������ͼƬ
                                        21��0x15��-�ǻ����ͼƬ
                                        22��0x16��-��Ա�ۼ����ͼƬ
                                        23��0x17��-�����˶����ͼƬ
                                        24��0x18��-ͣ�����ͼƬ
                                        25��0x19��-��Ʒ�������ͼƬ
                                        26��0x1a��-��Ʒ��ȡ���ͼƬ
                                        27��0x1b��-�������ͼƬ
                                        28��0x1c��-�ͻ����ϴ�ͼƬ
                                        */
    NET_EHOME_TIME  struStartTime;      //��ʼʱ��
    NET_EHOME_TIME  struStopTime;       //����ʱ��
    DWORD           dwStartIndex;       //��ѯ��ʼλ��
    DWORD           dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    BYTE            byLocalOrUTC;       //0-struStartTime��struStopTime�У���ʾ�����豸����ʱ�䣬���豸OSDʱ��  1-struStartTime��struStopTime�У���ʾ����UTCʱ��
    BYTE            byRes[63];
}NET_EHOME_PIC_FILE_COND, *LPNET_EHOME_PIC_FILE_COND;

//������ѯ����
typedef struct tagNET_EHOME_FLOW_COND
{
    BYTE            bySearchMode;       //��ѯģʽ��1-��year��ѯ��2-��month��ѯ��3-��day��ѯ
    BYTE            byRes[3];
    NET_EHOME_TIME  struStartTime;      //��ʼʱ��
    NET_EHOME_TIME  struStopTime;       //����ʱ��
    DWORD           dwStartIndex;       //��ѯ��ʼλ��
    DWORD           dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    BYTE            byLocalOrUTC;       //0-struStartTime��struStopTime�У���ʾ�����豸����ʱ�䣬���豸OSDʱ��  1-struStartTime��struStopTime�У���ʾ����UTCʱ��
    BYTE            byRes1[63];
}NET_EHOME_FLOW_COND, *LPNET_EHOME_FLOW_COND;

//�豸��־��ѯ����
typedef struct tagNET_EHOME_DEV_LOG_COND
{
    DWORD           dwMajorType;        //��־�����ͣ�1-������2-�쳣��3-������0xffff-ȫ��
    DWORD           dwMinorType;        //��־�����ͣ����豸���ߴ��붨����ͬ
    NET_EHOME_TIME  struStartTime;      //��ʼʱ��
    NET_EHOME_TIME  struStopTime;       //����ʱ��
    DWORD           dwStartIndex;       //��ѯ��ʼλ��
    DWORD           dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    BYTE            byLocalOrUTC;       //0-struStartTime��struStopTime�У���ʾ�����豸����ʱ�䣬���豸OSDʱ��  1-struStartTime��struStopTime�У���ʾ����UTCʱ��
    BYTE            byRes[63];
}NET_EHOME_DEV_LOG_COND, *LPNET_EHOME_DEV_LOG_COND;

//����������־��ѯ����
typedef struct tagNET_EHOME_ALARM_HOST_LOG_COND
{
    DWORD           dwMajorType;        //��־�����ͣ�1-������2-�쳣��3-������4-�¼���0xffff-ȫ��
    DWORD           dwMinorType;        //��־�����ͣ����豸���ߴ��붨����ͬ
    NET_EHOME_TIME  struStartTime;      //��ʼʱ��
    NET_EHOME_TIME  struStopTime;       //����ʱ��
    DWORD           dwStartIndex;       //��ѯ��ʼλ��
    DWORD           dwMaxFileCountPer;  //������������ļ�����������ļ���������Ҫȷ��ʵ�����绷��������������Ϊ8
    BYTE            byLocalOrUTC;       //0-struStartTime��struStopTime�У���ʾ�����豸����ʱ�䣬���豸OSDʱ��  1-struStartTime��struStopTime�У���ʾ����UTCʱ��
    BYTE            byRes1[63];
}NET_EHOME_ALARM_HOST_LOG_COND, *LPNET_EHOME_ALARM_HOST_LOG_COND;

//�ϰ��¼���ļ���Ϣ
typedef struct tagNET_EHOME_FINDDATA
{
    DWORD           dwSize;
    char            szFileName[MAX_FILE_NAME_LEN];  //�ļ���
    NET_EHOME_TIME  struStartTime;                  //�ļ��Ŀ�ʼʱ��
    NET_EHOME_TIME  struStopTime;                   //�ļ��Ľ���ʱ��
    DWORD           dwFileSize;                     //�ļ��Ĵ�С
    DWORD           dwFileMainType;                 //¼���ļ�������
    DWORD           dwFileSubType;                  //¼���ļ�������
    DWORD           dwFileIndex;                    //¼���ļ�����
    BYTE            byRes[128];
}NET_EHOME_FINDDATA, *LPNET_EHOME_FINDDATA;

//¼���ļ���Ϣ
typedef struct tagNET_EHOME_REC_FILE
{
    DWORD           dwSize;
    char            sFileName[MAX_FILE_NAME_LEN];   //�ļ���
    NET_EHOME_TIME  struStartTime;                  //�ļ��Ŀ�ʼʱ��
    NET_EHOME_TIME  struStopTime;                   //�ļ��Ľ���ʱ��
    DWORD           dwFileSize;                     //�ļ��Ĵ�С
    DWORD           dwFileMainType;                 //¼���ļ�������
    DWORD           dwFileSubType;                  //¼���ļ�������
    DWORD           dwFileIndex;                    //¼���ļ�����
    BYTE            byTimeDiffH;                    //struStartTime��struStopTime����ʱ�׼ʱ�䣨UTC����ʱ�Сʱ����-12 ... +14,0xff��ʾ��Ч
    BYTE            byTimeDiffM;                    //struStartTime��struStopTime����ʱ�׼ʱ�䣨UTC����ʱ����ӣ���-30,0, 30, 45, 0xff��ʾ��Ч
    BYTE            byRes[126];
}NET_EHOME_REC_FILE, *LPNET_EHOME_REC_FILE;

//ͼƬ�ļ���Ϣ
typedef struct tagNET_EHOME_PIC_FILE
{
    DWORD           dwSize;
    char            sFileName[MAX_FILE_NAME_LEN];   //�ļ���
    NET_EHOME_TIME  struPicTime;                    //ͼƬ����ʱ��
    DWORD           dwFileSize;                     //�ļ��Ĵ�С
    DWORD           dwFileMainType;                 //ͼƬ�ļ�������
    DWORD           dwFileIndex;                    //ͼƬ�ļ�����
    BYTE            byTimeDiffH;                    //struPicTime����ʱ�׼ʱ�䣨UTC����ʱ�Сʱ����-12 ... +14,0xff��ʾ��Ч
    BYTE            byTimeDiffM;                    //struPicTime����ʱ�׼ʱ�䣨UTC����ʱ����ӣ���-30,0, 30, 45, 0xff��ʾ��Ч
    BYTE            byRes[126];
}NET_EHOME_PIC_FILE, *LPNET_EHOME_PIC_FILE;

//������Ϣ
typedef struct tagNET_EHOME_FLOW_INFO
{
    DWORD   dwSize;
    DWORD   dwFlowValue;    //����ֵ
    DWORD   dwFlowIndex;    //��������
    BYTE    byRes[128];
}NET_EHOME_FLOW_INFO, *LPNET_EHOME_FLOW_INFO;

//�豸��־��Ϣ
#define MAX_LOG_INFO_LEN    8*1024   //��־������Ϣ����

typedef struct tagNET_EHOME_DEV_LOG
{
    NET_EHOME_TIME  struLogTime;                    //��־ʱ��
    DWORD           dwMajorType;                    //��־�����ͣ�1-������2-�쳣��3-����
    DWORD           dwMinorType;                    //��־�����ͣ����豸���ߴ��붨����ͬ
    DWORD           dwParamType;                    //�����Ͳ������ͣ��󲿷ֱ�ʾ�����ţ����û����ֵΪ0
    char            sLocalUser[NAME_LEN];           //�����û�
    char            sRemoteUser[NAME_LEN];          //Զ���û�
    char            sIPAddress[128];                //Զ������IP��ַ
    DWORD           dwChannelNo;                    //ͨ����
    DWORD           dwHardDiskNo;                   //Ӳ�̺�
    DWORD           dwAlarmInputChanNo;             //��������ͨ����
    DWORD           dwAlarmOutputChanNo;            //�������ͨ����
    char            sLogContext[MAX_LOG_INFO_LEN];  //��־����
    BYTE            byTimeDiffH;                    //struLogTime����ʱ�׼ʱ�䣨UTC����ʱ�Сʱ����-12 ... +14,0xff��ʾ��Ч
    BYTE            byTimeDiffM;                    //struLogTime����ʱ�׼ʱ�䣨UTC����ʱ����ӣ���-30,0, 30, 45, 0xff��ʾ��Ч
    BYTE            byRes[62];
}NET_EHOME_DEV_LOG, *LPNET_EHOME_DEV_LOG;

//����������־��Ϣ
typedef struct tagNET_EHOME_ALARM_HOST_LOG
{
    NET_EHOME_TIME  struLogTime;                    //��־ʱ��
    DWORD           dwMajorType;                    //��־�����ͣ�1-������2-�쳣��3-������4-�¼�
    DWORD           dwMinorType;                    //��־�����ͣ����豸���ߴ��붨����ͬ
    DWORD           dwParamType;                    //�����Ͳ������ͣ��󲿷ֱ�ʾ�����ţ����û����ֵΪ0
    char            sUserName[NAME_LEN];            //�û���
    char            sIPAddress[128];                //Զ������IP��ַ
    char            sLogContext[MAX_LOG_INFO_LEN];  //��־����
    BYTE            byTimeDiffH;                    //struLogTime����ʱ�׼ʱ�䣨UTC����ʱ�Сʱ����-12 ... +14,0xff��ʾ��Ч
    BYTE            byTimeDiffM;                    //struLogTime����ʱ�׼ʱ�䣨UTC����ʱ����ӣ���-30,0, 30, 45, 0xff��ʾ��Ч
    BYTE            byRes[62];
}NET_EHOME_ALARM_HOST_LOG, *LPNET_EHOME_ALARM_HOST_LOG;

NET_DVR_API LONG CALLBACK NET_ECMS_StartFindFile(LONG lUserID, LPNET_EHOME_FINDCOND pFindCond); //��֧��¼���ļ���ͼƬ�ļ���������ѯ
NET_DVR_API LONG CALLBACK NET_ECMS_FindNextFile(LONG lHandle, LPNET_EHOME_FINDDATA pFindData); //��֧��¼���ļ���ѯ

NET_DVR_API LONG CALLBACK NET_ECMS_StartFindFile_V11(LONG lUserID, LONG lSearchType, LPVOID pFindCond, DWORD dwCondSize);
NET_DVR_API LONG CALLBACK NET_ECMS_FindNextFile_V11(LONG lHandle, LPVOID pFindData, DWORD dwDataSize);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopFindFile(LONG lHandle);


typedef struct tagNET_EHOME_PLAYBACK_INFO_IN
{
    DWORD       dwSize;
    DWORD       dwChannel;                    //�طŵ�ͨ����
    BYTE        byPlayBackMode;               //�ط�����ģʽ 0�������� 1����ʱ��
    BYTE        byStreamPackage;              //�ط��������ͣ��豸�˷�����������ʽ 0��PS��Ĭ�ϣ� 1��RTP
    BYTE        byLinkMode;     				//0��TCP��1��UDP, 8-NPQ
    BYTE		byLinkEncrypt;
    union
    {
        BYTE    byLen[512];
        struct
        {
            char   szFileName[MAX_FILE_NAME_LEN];   //�طŵ��ļ���
            DWORD  dwSeekType;                      //0-���ֽڳ��ȼ���ƫ����  1-��ʱ�䣨����������ƫ����
            DWORD  dwFileOffset;                    //�ļ�ƫ���������ĸ�λ�ÿ�ʼ���أ����dwSeekTypeΪ0��ƫ�������ֽڼ��㣬Ϊ1������������
            DWORD  dwFileSpan;                      //���ص��ļ���С��Ϊ0ʱ����ʾ����ֱ�����ļ�����Ϊֹ�����dwSeekTypeΪ0����С�����ֽڼ��㣬Ϊ1������������
            BYTE   byStreamType;                    //1 - ��������2 - ������, 0ΪĬ���豸��ʲô������ʲô��
        }struPlayBackbyName;
        struct 
        {
            NET_EHOME_TIME  struStartTime;  // ��ʱ��طŵĿ�ʼʱ��
            NET_EHOME_TIME  struStopTime;   // ��ʱ��طŵĽ���ʱ��
            BYTE    byLocalOrUTC;           //0-�豸����ʱ�䣬���豸OSDʱ��  1-UTCʱ��
            BYTE    byDuplicateSegment;     //byLocalOrUTCΪ1ʱ��Ч 0-�ظ�ʱ��ε�ǰ�� 1-�ظ�ʱ��κ��
            BYTE    byStreamType;           //1 - ��������2 - ������, 0ΪĬ���豸��ʲô������ʲô��
            BYTE    byHls;                  //HLS�طţ�0-��1-��
        }struPlayBackbyTime;
    }unionPlayBackMode;
    NET_EHOME_IPADDRESS struStreamSever;    //��ý���ַ
}NET_EHOME_PLAYBACK_INFO_IN, *LPNET_EHOME_PLAYBACK_INFO_IN;

typedef struct tagNET_EHOME_PLAYBACK_INFO_OUT
{
    LONG   lSessionID;     //ĿǰЭ�鲻֧�֣�����-1
    LONG   lHandle;  //�����˻ط��첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ
    BYTE   byRes[124];
}NET_EHOME_PLAYBACK_INFO_OUT, *LPNET_EHOME_PLAYBACK_INFO_OUT;

typedef struct tagNET_EHOME_PUSHPLAYBACK_IN
{
    DWORD dwSize;
    LONG lSessionID; 
    BYTE byKeyMD5[32];//����������Կ,����MD5
    BYTE  byRes[96];
} NET_EHOME_PUSHPLAYBACK_IN, *LPNET_EHOME_PUSHPLAYBACK_IN;

typedef struct tagNET_EHOME_PUSHPLAYBACK_OUT
{
    DWORD dwSize;
    LONG  lHandle;
    BYTE  byRes[124];
} NET_EHOME_PUSHPLAYBACK_OUT, *LPNET_EHOME_PUSHPLAYBACK_OUT;

typedef struct tagNET_EHOME_STOPPLAYBACK_PARAM
{
    LONG  lSessionID;
    LONG  lHandle;
    BYTE  byRes[120];
}NET_EHOME_STOPPLAYBACK_PARAM, *LPNET_EHOME_STOPPLAYBACK_PARAM;

typedef struct tagNET_EHOME_PLAYBACK_PAUSE_RESTART_PARAM
{
    LONG lSessionID;
    LONG lHandle;  //����������������˻ط��첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ��������
    BYTE byRes[120];
}NET_EHOME_PLAYBACK_PAUSE_RESTART_PARAM, *LPNET_EHOME_PLAYBACK_PAUSE_RESTART_PARAM;

typedef enum tagENUM_NET_EHOME_PLAYBACK_OPERATE_MODE
{
    PLAYBACK_OPERATE_UNKNOW     = -1,   //��Ч����
    PLAYBACK_OPERATE_PAUSE      = 0,    //��ͣ�ط�,��ӦpOperateParam�ṹ��NET_EHOME_PLAYBACK_PAUSE_RESTART_PARAM
    PLAYBACK_OPERATE_RESTART    = 1,     //�ָ��طţ���ӦpOperateParam�ṹ��NET_EHOME_PLAYBACK_PAUSE_RESTART_PARAM
    PLAYBACK_OPERATE_FAST = 2,
    PLAYBACK_OPERATE_SLOW = 3
}ENUM_NET_EHOME_PLAYBACK_OPERATE_MODE;

NET_DVR_API BOOL CALLBACK NET_ECMS_StartPlayBack(LONG lUserID, LPNET_EHOME_PLAYBACK_INFO_IN pPlayBackInfoIn, LPNET_EHOME_PLAYBACK_INFO_OUT pPlayBackInfoOut);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopPlayBack(LONG lUserID, LONG lSessionID);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopPlayBackEx(LONG iUserID, LPNET_EHOME_STOPPLAYBACK_PARAM pStopParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_StartPushPlayBack(LONG lUserID, LPNET_EHOME_PUSHPLAYBACK_IN pPushInfoIn, LPNET_EHOME_PUSHPLAYBACK_OUT pPushInfoOut);
NET_DVR_API BOOL CALLBACK NET_ECMS_PlayBackOperate(LONG iUserID, ENUM_NET_EHOME_PLAYBACK_OPERATE_MODE enumMode, void* pOperateParam);

//��̨��ؽṹ��
#define NET_EHOME_PTZ_CTRL      1000    //�ƾ�����
#define NET_EHOME_PRESET_CTRL   1001    //Ԥ�õ����
#define NET_EHOME_PZIN          1002    //3D��ѡ�Ŵ���С
#define NET_EHOME_PTRACK        1003    //3D�������

typedef enum
{
    PTZ_UP              = 0,    //����
    PTZ_DOWN,                   //����
    PTZ_LEFT,                   //����
    PTZ_RIGHT,                  //����
    PTZ_UPLEFT,                 //������
    PTZ_DOWNLEFT,               //������
    PTZ_UPRIGHT,                //������
    PTZ_DOWNRIGHT,              //������
    PTZ_ZOOMIN,                 //�佹��
    PTZ_ZOOMOUT,                //�佹��
    PTZ_FOCUSNEAR,              //�۽���
    PTZ_FOCUSFAR,               //�۽���
    PTZ_IRISSTARTUP,            //��Ȧ���
    PTZ_IRISSTOPDOWN,           //��Ȧ��С
    PTZ_LIGHT,                  //�����
    PTZ_WIPER,                  //��ˢ
    PTZ_AUTO                    //�Զ�
}EN_PTZ_CMD;

typedef struct tagNET_EHOME_PTZ_PARAM
{
    DWORD dwSize;
    BYTE  byPTZCmd; //��̨����μ�EN_PTZ_CMD
    BYTE  byAction; //��̨������0-��ʼ��̨������1-ֹͣ��̨����
    BYTE  bySpeed;  //��̨�ٶȣ�0-7����ֵԽ���ٶ�Խ��
    BYTE  byRes[29];
}NET_EHOME_PTZ_PARAM, *LPNET_EHOME_PTZ_PARAM;

typedef struct tagNET_EHOME_PRESET_PARAM
{
    DWORD dwSize;
    BYTE  byPresetCmd;      //Ԥ�õ�������1-����Ԥ�õ㣬2-���Ԥ�õ㣬3-ת��Ԥ�õ�
    BYTE  byRes1[3];
    DWORD dwPresetIndex;    //Ԥ�õ���
    BYTE  byRes2[32];
}NET_EHOME_PRESET_PARAM, *LPNET_EHOME_PRESET_PARAM;

typedef struct tagNET_EHOME_PZIN_PARAM
{
    DWORD           dwSize;
    BYTE            byAction;   //������0��С������->���£�����->���ϣ� 1�Ŵ�����->���£�����->���ϣ�
    BYTE            byRes1[3];
    NET_EHOME_ZONE  struArea;   //��ѡ��Χ
    BYTE            byRes2[32];
}NET_EHOME_PZIN_PARAM, *LPNET_EHOME_PZIN_PARAM;

typedef struct tagNET_EHOME_POINT
{
    DWORD dwX;
    DWORD dwY;
    BYTE  byRes[4];
}NET_EHOME_POINT, *LPNET_EHOME_POINT;

typedef struct tagNET_EHOME_IPADDR
{
    char    sIpV4[16];
    char    sIpV6[128];
}NET_EHOME_IPADDR, *LPNET_EHOME_IPADDR;

#define MACADDR_LEN     6   //mac��ַ����

typedef struct tagNET_EHOME_ETHERNET
{
    NET_EHOME_IPADDR    struDevIP;      //�豸IP��ַ
    NET_EHOME_IPADDR    struDevIPMask;  //�����ַ
    DWORD               dwNetInterface; // ��������1:10M��˫�� 2:10Mȫ˫�� 3:100M��˫�� 4:100Mȫ˫�� 6:1000Mȫ˫�� 5:10M/100M/1000M����Ӧ
    WORD                wDevPort;       //�豸SDK�˿ںţ�8000
    WORD                wMTU;           // MTU����
    BYTE                byMACAddr[MACADDR_LEN]; //mac��ַ
    BYTE                byRes[2];
}NET_EHOME_ETHERNET,*LPNET_EHOME_ETHERNET;

#define PASSWD_LEN      16  //���볤��

typedef struct tagNET_EHOME_PPPOECFG
{
    DWORD   dwPPPoE;                    //�Ƿ�����PPPOE��1����ʹ�ã�0����ʹ��
    char    sPPPoEUser[NAME_LEN];       //PPPoE�û���
    char    sPPPoEPassword[PASSWD_LEN]; //PPPoE����
    NET_EHOME_IPADDR    struPPPoEIP;    //PPPoE IP��ַ
}NET_EHOME_PPPOECFG,*LPNET_EHOME_PPPOECFG;

typedef struct tagNET_EHOME_NETWORK_CFG
{
    DWORD               dwSize;             //�ṹ���С
    NET_EHOME_ETHERNET  struEtherNet;       //��̫����
    NET_EHOME_IPADDR    struGateWayIP;      //���ص�ַ
    NET_EHOME_IPADDR    struMultiCastIP;    //�ಥ��ַ
    NET_EHOME_IPADDR    struDDNSServer1IP;  //DDNS1������IP
    NET_EHOME_IPADDR    struDDNSServer2IP;  //DDNS2������IP
    NET_EHOME_IPADDR    struAlarmHostIP;    //��������IP
    WORD                wAlarmHostPort;     //���������˿ں�
    WORD                wIPResolverPort;    //�����������˿�
    NET_EHOME_IPADDR    struIPResolver;     //������������ַ
    NET_EHOME_PPPOECFG  struPPPoE;          //PPPoE����
    WORD                wHTTPPort;;         //Http�˿�
    BYTE                byRes[674];         //����
}NET_EHOME_NETWORK_CFG,*LPNET_EHOME_NETWORK_CFG;

typedef struct tagNET_EHOME_COMPRESSION_COND
{
    DWORD   dwSize;             //�ṹ���С
    DWORD   dwChannelNum;       //ͨ���ţ���1��ʼ
    BYTE    byCompressionType;  //�������ͣ�1-��������2-��������3-������
    BYTE    byRes[23];
}NET_EHOME_COMPRESSION_COND,*LPNET_EHOME_COMPRESSION_COND;

typedef struct tagNET_EHOME_COMPRESSION_CFG
{
    DWORD       dwSize;         //�ṹ���С
    BYTE        byStreamType;   //��������
    BYTE        byPicQuality;   //ͼ������0:��� 1:�ϸ� 2:�е� 3:�� 4:�ϵ� 5:���
    BYTE        byBitRateType;  //��������0:������ 1:������
    BYTE        byRes1;         //����
    DWORD       dwResolution;   //�ֱ��ʣ�0:DCIF 1:CIF 2:QCIF 3:4CIF 4:2CIF 6:QVGA��320x240�� 16:VGA 17:UXGA 18:SVGA 19:HD720p 20:hd900 21:XVGA    22:SXGAp(1360*1024)
    //27:1080P(1920*1080)    28:2560x1920 /*500W*/    29:1600x304    30:2048x1536 /*300W*/
    //31:2448x2048/*500W*/        32:2448x1200        33:2448x800    34:XGA/*(1024*768)*/
    //35:SXGA/*(1280*1024)*/    36:WD1/*(960*576/960*480)*/    37:HD1080I    38-WXGA(1440*900)��
    //39-HD_F(1920*1080/1280*720)��40-HD_H(1920*540/1280*360)��  41-HD_Q(960*540/630*360)��
    //42-2336*1744��    43-1920*1456��44-2592*2048��    45-3296*2472��46-1376*768��47-1366*768,
    //48-1360*768,  49-WSXGA+��50-720*720��51-1280*1280��52-2048*768��53-2048*2048
    //54-2560x2048,  55-3072x2048 ,  56-2304*1296  57-WXGA(1280*800),  58-1600*600
    //59-2592*1944  60-2752*2208,    61-384*288,    62-4000*3000,  63-4096*2160,  64-3840*2160,
    //65-4000*2250, 66-3072*1728,
    DWORD       dwVideoBitRate;     //0-32K 1-48k 2-64K 3-80K 4-96K 5-128K 6-160k 7-192K 8-224K 9-256K 10-320K 11-384K 12-448K 13-512K 14-640K 15-768K 16-896K 17-1024K 18-1280K 19-1536K 20-1792K 21-2048K 22-�Զ���
    DWORD       dwMaxBitRate;       //�Զ�������
    DWORD       dwVideoFrameRate;   //��Ƶ֡�ʣ�4�ֽ�������0:ȫ֡�� 1:1/16 2:1/8 3:1/4 4:1/2 5:1 6:2 7:4 8:6 9:8 10:10 11:12 12:16 13:20 14:15 15:18 16:22
    WORD        wIntervalFrameI;    // I֡�������Χ1~400
    BYTE        byIntervalBPFrame;  //֡���� 0:BBP 1��BP 2:P
    BYTE        byRes[41];          //����
}NET_EHOME_COMPRESSION_CFG,*LPNET_EHOME_COMPRESSION_CFG;

#define MAX_TIME_SEGMENT        8   //ʱ���,ehomeЭ��ֻ֧��4��
#define MAX_ANALOG_ALARMOUT     32  //���32·ģ�ⱨ�����
#define MAX_ANALOG_CHANNUM      32  //���32��ģ��ͨ��
#define MAX_DIGIT_CHANNUM       480 //���480������ͨ��,������Ᵽ��

typedef struct tagNET_EHOME_ALARM_TIME_COND
{
    DWORD       dwSize;         //�ṹ���С
    BYTE        byAlarmType;    //�������ͣ�0-�ƶ���⣬1-��Ƶ��ʧ��2-�ڵ�������3-�������룬4-���������9-������
    BYTE        byWeekday;      //0-Mon��1-Tues��2-Wed��3-Thur��4-Fri��5-Sat��6-Sun
    BYTE        byRes1[2];
    DWORD       dwChannel;      //ͨ���ţ���1��ʼ
    BYTE        byRes2[20];
}NET_EHOME_ALARM_TIME_COND,*LPNET_EHOME_ALARM_TIME_COND;

typedef struct tagNET_EHOME_SCHEDTIME
{
    BYTE        byStartHour;    //��ʼʱ�䣺ʱ
    BYTE        byStartMin;     //��ʼʱ�䣺��
    BYTE        byStopHour;     //����ʱ�䣺ʱ
    BYTE        byStopMin;      //����ʱ�䣺��
}NET_EHOME_SCHEDTIME,*LPNET_EHOME_SCHEDTIME;

typedef struct tagNET_EHOME_ALARM_TIME_CFG
{
    DWORD       dwSize;             //�ṹ���С
    NET_EHOME_SCHEDTIME struSchedTime[MAX_TIME_SEGMENT];//����ʱ���
    BYTE        bySchedTimeCount;   //ֻ��������ʱ�����
    BYTE        byRes[43];
}NET_EHOME_ALARM_TIME_CFG,*LPNET_EHOME_ALARM_TIME_CFG;

typedef struct tagNET_EHOME_ALARMOUT_CFG
{
    DWORD       dwSize;                 //�ṹ���С
    BYTE        sAlarmOutName[NAME_LEN];//�����������
    WORD        wAlarmOutDelay;         //�����ʱ��0��5�룻1��10�룻 2��30�룻 3��1�֣� 4��2�֣� 5��5�֣� 6��10�֣� 7�����
    BYTE        byRes[26];              //����
}NET_EHOME_ALARMOUT_CFG,*LPNET_EHOME_ALARMOUT_CFG;

typedef struct tagNET_EHOME_ALARMOUT_STATUS_CFG
{
    DWORD       dwSize;             //�ṹ���С
    BYTE        byAlarmOutStatus;   //1-�������������0-�رձ������
    BYTE        byRes[11];
}NET_EHOME_ALARMOUT_STATUS_CFG,*LPNET_EHOME_ALARMOUT_STATUS_CFG;

typedef struct tagNET_EHOME_ALARMIN_COND
{
    DWORD       dwSize;         //�ṹ���С
    DWORD       dwAlarmInNum;   //������ţ���1��ʼ
    DWORD       dwPTZChan;      // PTZ������Ƶͨ�����,��1��ʼ
    BYTE        byRes[20];
}NET_EHOME_ALARMIN_COND,*LPNET_EHOME_ALARMIN_COND;

typedef struct tagNET_EHOME_LINKAGE_ALARMOUT
{
    DWORD       dwAnalogAlarmOutNum;                    //ֻ����ģ�ⱨ������
    BYTE        byAnalogAlarmOut[MAX_ANALOG_ALARMOUT];  //ģ�ⱨ�������0����ʹ�ã�1��ʹ��
    BYTE        byRes[5000];                            //������Э������û��IP��������������ӿ���λ��������
}NET_EHOME_LINKAGE_ALARMOUT,*LPNET_EHOME_LINKAGE_ALARMOUT;

typedef struct tagNET_EHOME_LINKAGE_PTZ
{
    BYTE    byUsePreset;    //�Ƿ����Ԥ�õ㣬0����ʹ�ã�1��ʹ��
    BYTE    byUseCurise;    //�Ƿ����Ѳ����0����ʹ�ã�1��ʹ��
    BYTE    byUseTrack;     //�Ƿ���ù켣��0����ʹ�ã�1��ʹ��
    BYTE    byRes1;         //����
    WORD    wPresetNo;      //Ԥ�õ�ţ���Χ��1~256��Э���й涨��1��256��ʵ�������豸֧��300
    WORD    wCuriseNo;      //Ѳ��·���ţ���Χ��1~16
    WORD    wTrackNo;       //�켣�ţ���Χ��1~16
    BYTE    byRes2[6];      //����
}NET_EHOME_LINKAGE_PTZ,*LPNET_EHOME_LINKAGE_PTZ;

typedef struct tagNET_EHOME_ALARMIN_LINKAGE_TYPE
{
    BYTE    byMonitorAlarm;     //�������Ͼ��棬0����ʹ�ã�1��ʹ��
    BYTE    bySoundAlarm;       //����������0����ʹ�ã�1��ʹ��
    BYTE    byUpload;           //�ϴ����ģ�0����ʹ�ã�1��ʹ��
    BYTE    byAlarmout;         //�������������0����ʹ�ã�1��ʹ��-
    BYTE    byEmail;            //�ʼ�������0����ʹ�ã�1��ʹ��
    BYTE    byRes1[3];          //����
    NET_EHOME_LINKAGE_PTZ    struPTZLinkage;    //PTZ����
    NET_EHOME_LINKAGE_ALARMOUT    struAlarmOut;    //�����������
    BYTE    byRes[128];
}NET_EHOME_ALARMIN_LINKAGE_TYPE,*LPNET_EHOME_ALARMIN_LINKAGE_TYPE;

typedef struct tagNET_EHOME_RECORD_CHAN
{
    BYTE    byAnalogChanNum;                    //ֻ����ģ��ͨ����
    BYTE    byAnalogChan[MAX_ANALOG_CHANNUM];   //ģ��ͨ����0����ʹ�ã�1��ʹ��
    BYTE    byRes1[3];                          //����
    WORD    wDigitChanNum;                      //ֻ��������ͨ����
    BYTE    byDigitChan[MAX_DIGIT_CHANNUM];     //����ͨ����0����ʹ�ã�1��ʹ��
    BYTE    byRes2[62];                         //����
}NET_EHOME_RECORD_CHAN,*LPNET_EHOME_RECORD_CHAN;

typedef struct tagNET_EHOME_ALARMIN_CFG
{
    DWORD       dwSize;                     //�ṹ���С
    BYTE        sAlarmInName[NAME_LEN];     //������������
    BYTE        byAlarmInType;              //���������ͣ�0��������1������
    BYTE        byUseAlarmIn;               //�Ƿ���0����ʹ�ã�1��ʹ��
    BYTE        byRes1[2];                  //����
    NET_EHOME_ALARMIN_LINKAGE_TYPE    struLinkageType;    //����ģʽ
    NET_EHOME_RECORD_CHAN    struRecordChan;//����¼��ͨ��
    BYTE        byRes2[128];                //����
}NET_EHOME_ALARMIN_CFG,*LPNET_EHOME_ALARMIN_CFG;

typedef struct tagNET_EHOME_MANUAL_IOOUT_CTRL
{
    DWORD       dwSize;        //�ṹ���С
    DWORD       dwChan;        //IO�����ţ���1��ʼ
    DWORD       dwDelayTime;   //�����������ʱ�䣨�룩��ֵΪ0��ʾһֱ���������ָ��ʱ�䳤�Ƚ��������
    BYTE        byAction;      //0-�رձ������,1-�����������
    BYTE        byRes[19];
}NET_EHOME_MANUAL_IOOUT_CTRL,*LPNET_EHOME_MANUAL_IOOUT_CTRL;

typedef struct tagNET_EHOME_IMAGE_CFG
{
    DWORD       dwSize;         //�ṹ���С
    BYTE        byHue;          //ɫ����0��255
    BYTE        byContrast;     //�Աȶ�,0~255
    BYTE        byBright;       //���ȣ�0��255
    BYTE        bySaturation;   //���Ͷ�
    BYTE        byRes[24];
}NET_EHOME_IMAGE_CFG,*LPNET_EHOME_IMAGE_CFG;

#define NET_EHOME_GET_NETWORK_CFG           5   //��ȡ�������
#define NET_EHOME_SET_NETWORK_CFG           6   //�����������
#define NET_EHOME_GET_COMPRESSION_CFG       7   //��ȡѹ������
#define NET_EHOME_SET_COMPRESSION_CFG       8   //����ѹ������
#define NET_EHOME_GET_IMAGE_CFG             9   //��ȡͼ�����
#define NET_EHOME_SET_IMAGE_CFG             10  //����ͼ�����
#define NET_EHOME_GET_ALARMIN_CFG           11  //��ȡ�����������
#define NET_EHOME_SET_ALARMIN_CFG           12  //���ñ����������
#define NET_EHOME_GET_ALARM_TIME_CFG        13  //��ȡ��������ʱ�����
#define NET_EHOME_SET_ALARM_TIME_CFG        14  //���ñ�������ʱ�����
#define NET_EHOME_GET_ALARMOUT_CFG          15  //��ȡ�����������
#define NET_EHOME_SET_ALARMOUT_CFG          16  //���ñ����������
#define NET_EHOME_GET_ALARMOUT_STATUS_CFG   17  //��ȡ�������״̬����
#define NET_EHOME_SET_ALARMOUT_STATUS_CFG   18  //���ñ������״̬����
#define NET_EHOME_MANUAL_IOOUT              19  //�ֶ�����IO���

typedef enum tagNET_CMS_ENUM_PROXY_TYPE
{
    ENUM_PROXY_TYPE_NETSDK = 0, //NetSDK����
    ENUM_PROXY_TYPE_HTTP        //HTTP����
}NET_CMS_ENUM_PROXY_TYPE;

typedef struct tagNET_EHOME_PT_PARAM
{
    NET_EHOME_IPADDRESS struIP; //������IP�Ͷ˿�
    BYTE    byProtocolType;     //Э�����ͣ�0-TCP
    BYTE    byProxyType;        //�������ͣ�0-NetSDK����1-HTTP����
    BYTE    byRes[2];
}NET_EHOME_PT_PARAM, *LPNET_EHOME_Proxy_PARAM;

typedef LPNET_EHOME_Proxy_PARAM LPNET_EHOME_PT_PARAM;

typedef struct tagNET_EHOME_PASSTHROUGH_PARAM
{
    DWORD   dwSequence; //�������
    DWORD   dwUUID;     //�ỰID
    BYTE    byRes[64];
}NET_EHOME_PASSTHROUGH_PARAM, *LPNET_EHOME_PASSTHROUGH_PARAM;

typedef struct tagNET_EHOME_PTXML_PARAM
{
    void*   pRequestUrl;        //����URL
    DWORD   dwRequestUrlLen;    //����URL����
    void*   pCondBuffer;        //������������XML��ʽ���ݣ�
    DWORD   dwCondSize;         //������������С
    void*   pInBuffer;          //���뻺������XML��ʽ���ݣ�
    DWORD   dwInSize;           //���뻺������С
    void*   pOutBuffer;         //�����������XML��ʽ���ݣ�
    DWORD   dwOutSize;          //�����������С
    DWORD   dwReturnedXMLLen;   //ʵ�ʴ��豸���յ���XML���ݵĳ���
    DWORD   dwRecvTimeOut;      //Ĭ��5000ms
    DWORD   dwHandle;           //����������������˻ط��첽�ص�֮�󣬸�ֵΪ��Ϣ������ص������ڱ�ʶ��������
    BYTE    byRes[24];          //����
}NET_EHOME_PTXML_PARAM, *LPNET_EHOME_PTXML_PARAM;

typedef struct tagNET_EHOME_HTTP_PARAM
{
    void*   pInBuffer;          //���뻺������XML��ʽ���ݣ�
    DWORD   dwInSize;           //���뻺������С
    void*   pOutBuffer;         //�����������XML��ʽ���ݣ�
    DWORD   dwOutSize;          //�����������С
    DWORD   dwReturnedXMLLen;   //ʵ�ʴ��豸���յ���XML���ݵĳ���
    DWORD   dwRecvTimeOut;      //���ճ�ʱ����λms
    BYTE    byRes[28];          //����
}NET_EHOME_HTTP_PARAM, *LPNET_EHOME_HTTP_PARAM;

NET_DVR_API LONG CALLBACK NET_ECMS_StartListenProxy(LPNET_EHOME_PT_PARAM lpStru);
NET_DVR_API BOOL CALLBACK NET_ECMS_StopListenProxy(LONG lListenHandle, DWORD dwProxyType = 0);
NET_DVR_API LONG CALLBACK NET_ECMS_ConvertProtocolHttpToPassthrough(void* pSrcBuffer, DWORD dwSrcBufLen, void* pDestBuffer, DWORD dwDestBufLen, LPNET_EHOME_PASSTHROUGH_PARAM lpParam, BOOL bToPassthrough = TRUE);
typedef void (CALLBACK* PASSTHROUGHDATACALLBACK)(DWORD dwProxyType, LONG lListenHandle, void* pDeviceID, DWORD dwDevIDLen, void* pDataBuffer, DWORD dwDataLen, void* pUser);
NET_DVR_API BOOL CALLBACK NET_ECMS_SetPassthroughDataCallback(PASSTHROUGHDATACALLBACK fnPassthroughDataCb, void* pUser, DWORD dwProxyType = 0);
NET_DVR_API BOOL CALLBACK NET_ECMS_SendPassthroughData(void* pDataBuffer, DWORD dDataLen, DWORD dwProxyType = 0);
NET_DVR_API BOOL CALLBACK NET_ECMS_GetPTXMLConfig(LONG iUserID, LPNET_EHOME_PTXML_PARAM lpPTXMLParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_PutPTXMLConfig(LONG iUserID, LPNET_EHOME_PTXML_PARAM lpPTXMLParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_PostPTXMLConfig(LONG iUserID, LPNET_EHOME_PTXML_PARAM lpPTXMLParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_DeletePTXMLConfig(LONG lUserID, LPNET_EHOME_PTXML_PARAM lpPTXMLParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_ISAPIPassThrough(LONG lUserID, LPNET_EHOME_PTXML_PARAM lpParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_HTTPConfig(LONG iUserID, LPNET_EHOME_HTTP_PARAM lpParam);
NET_DVR_API BOOL CALLBACK NET_ECMS_SetSDKLocalCfg(NET_EHOME_LOCAL_CFG_TYPE enumType, void* const lpInBuff);
NET_DVR_API BOOL CALLBACK NET_ECMS_GetSDKLocalCfg(NET_EHOME_LOCAL_CFG_TYPE enumType,void* lpOutBuff);

typedef struct tagNET_EHOME_XML_REMOTE_CTRL_PARAM
{
    DWORD dwSize;
    void* lpInbuffer;           //���Ʋ���������
    DWORD dwInBufferSize;       //���Ʋ�������������
    DWORD dwSendTimeOut;        //���ݷ��ͳ�ʱʱ��,��λms��Ĭ��5s
    DWORD dwRecvTimeOut;        //���ݽ��ճ�ʱʱ��,��λms��Ĭ��5s
    void* lpOutBuffer;          //���������
    DWORD dwOutBufferSize;      //�����������С
    void* lpStatusBuffer;       //״̬������,������Ҫ����ΪNULL
    DWORD dwStatusBufferSize;   //״̬��������С
    BYTE  byRes[16];
}NET_EHOME_XML_REMOTE_CTRL_PARAM, *LPNET_EHOME_XML_REMOTE_CTRL_PARAM;
NET_DVR_API BOOL CALLBACK NET_ECMS_XMLRemoteControl(LONG lUserID, LPNET_EHOME_XML_REMOTE_CTRL_PARAM lpCtrlParam, DWORD dwCtrlSize);


#define EHOME_CMSALARM_EXCEPTION      0x105  //CMS���ձ����쳣

NET_DVR_API BOOL CALLBACK NET_ECMS_SetExceptionCallBack(DWORD dwMessage, HANDLE hWnd, void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG iUserID, LONG iHandle, void* pUser), void* pUser);

NET_DVR_API BOOL CALLBACK NET_ECMS_TranBuf(LONG lUserID, DWORD dwLength, void* pBuf);

typedef enum
{
    LONG_CFG_CREATED = 0,   //�����ӽ����ɹ�
    LONG_CFG_CREATE_FAIL,   //�����ӽ���ʧ��
    LONG_CFG_DATA,          //��������ͨ����
    LONG_CFG_TERMINATE      //������������Ϣ
}LONG_LINK_MSG;

typedef BOOL(CALLBACK *LongConfigCallBack)(LONG iHandle, LONG_LINK_MSG enMsg, void* pOutBuffer, DWORD dwOutLen, void* pUser);

typedef struct tagNET_EHOME_LONG_CFG_INPUT
{
    LongConfigCallBack fnDataCallBack;
    void*   pUser;
    BYTE    byRes[32];
}NET_EHOME_LONG_CFG_INPUT, *LPNET_EHOME_LONG_CFG_INPUT;

typedef struct tagNET_EHOME_LONG_CFG_SEND
{
    void*   pDataBuffer;
    DWORD   dwDataLen;
    BYTE    byRes[32];
}NET_EHOME_LONG_CFG_SEND, *LPNET_EHOME_LONG_CFG_SEND;

//������Ϣ����˽��Э�� begin

#define NET_EHOME_S2C_TIME_ADJUST                   0x9             //�ն�Уʱ
#define NET_EHOME_S2C_SEND_ERRCODE                  0xD             //���ʹ�����

#define NET_EHOME_S2C_SET_SERVER_INFO               0x18            //���÷�������Ϣ���ն�
#define NET_EHOME_S2C_GET_TERMINAL_INFO             0x19            //��ȡ�ն���Ϣ

#define NET_EHOME_S2C_LOGOUT                        0x20            //֪ͨ�ն˵ǳ�������

#define NET_EHOME_S2C_POST_SCHEDULE                 0x50            //�ճ��·�
#define NET_EHOME_S2C_TERMINALCONTROL_V20           0x51            //�ն��豸����V20
#define NET_EHOME_S2C_GET_CAP_SUPPORTEDCMD          0x52            //��ȡ�ն�֧�ֵ������������
#define NET_EHOME_S2C_TERMINALCONTROL               0x53            //�ն��豸����
#define NET_EHOME_S2C_PLAYCONTROL                   0x54            //�ն˲��ſ���
#define NET_EHOME_S2C_SET_IPCINFO                   0x55            //����IPC��Ϣ
#define NET_EHOME_S2C_GET_WORKSTATUS                0x56            //��ȡ�豸����״̬
#define NET_EHOME_S2C_VERSIONUPGRADE                0x57            //�豸����
#define NET_EHOME_S2C_SETPLAYERPARAM                0x58            //�����ն˲��Ų���
#define NET_EHOME_S2C_SETSERVERADDR                 0x5B            //�����ն�ע��ķ�������Ϣ
#define NET_EHOME_S2C_VERSIONUPGRADE_V20            0x5C            //�豸����V20

#define NET_EHOME_S2C_SET_WEATHERINFO               0x61            //����������Ϣ����     
#define NET_EHOME_S2C_GET_SCREENSHOT                0x62            //��ȡ�ն˵���Ļ��ͼ
#define NET_EHOME_S2C_GET_DEFAULTPARAM              0x63            //��ȡ�ָ�Ĭ�ϲ������ֵ
#define NET_EHOME_S2C_REPLACE_MATERIAL              0x64            //�ز��滻
#define NET_EHOME_S2C_CANCEL_SCHEDULE               0x65            //ȡ���ճ̷���
#define NET_EHOME_S2C_SET_QUEUE_INFO                0x66            //�кŹ�����Ϣ
#define NET_EHOME_S2C_PUBLISH_SHOT_PIC              0x67            //�·���ͼͼƬ
#define NET_EHOME_S2C_GET_IPCINFO                   0x68            //��ȡIPC��Ϣ
#define NET_EHOME_S2C_SET_TERMINAL_IP               0x69            //�����ն˵�ip
#define NET_EHOME_S2C_GET_TERMINAL_IP               0x70            //��ȡ�ն˵�ip
#define NET_EHOME_S2C_SET_TERMINAL_NAME             0x71            //�����ն˵�����
#define NET_EHOME_S2C_PUBLISH_BIG_DATA              0x72            //�·������ݣ�����8K����

#define NET_EHOME_S2C_SET_SWITCHPLAN                0x100           //��ʱ���ػ��ƻ��·�
#define NET_EHOME_S2C_GET_SWITCHPLAN                0x101           //��ȡ��ʱ���ػ��ƻ�
#define NET_EHOME_S2C_SET_VOLUMEPLAN                0x102           //���ö�ʱ�����ƻ�
#define NET_EHOME_S2C_GET_VOLUMEPLAN                0x103           //��ȡ�������Ƽƻ�
#define NET_EHOME_S2C_SET_INPUTPLAN                 0x104           //��ʱ��ο���HDMI����Ϣ�����л�
#define NET_EHOME_S2C_GET_INPUTPLAN                 0x105           //��ȡHDMI����Ϣ�����л��л��ƻ�
#define NET_EHOME_S2C_SET_CHARACTER                 0x106           //���ն˲岥������Ϣ
#define NET_EHOME_S2C_GET_CHARACTER                 0x107           //��ȡ�ն����ڲ岥��������Ϣ
#define NET_EHOME_S2C_RETRANSMIT_TO_TERM            0x108           //����������͸�����ն�
#define NET_EHOME_S2C_TRANS_WITH_RET                0x10A           //����������͸�����ն˲������ն�͸����������������
#define NET_EHOME_S2C_SET_ADB_CFG                   0x110           //����ADB����    
#define NET_EHOME_S2C_GET_ADB_CFG                   0x111           //��ȡADB����
#define NET_EHOME_S2C_SET_TIEM_ZONE                 0x112           //�����ն˵�ʱ����Ϣ
#define NET_EHOME_S2C_GET_TIME_ZONE                 0x113           //��ȡ�ն˵�ʱ����Ϣ
#define NET_EHOME_S2C_SET_SADP                      0x114           //�����ն˵�SADP��Ϣ
#define NET_EHOME_S2C_GET_SADP                      0x115           //��ȡ�ն˵�SADP��Ϣ
#define NET_EHOME_S2C_GET_COMPONENT		            0x116 	        //��ȡ�ն������Ϣ

#define NET_EHOME_S2C_PUBLISH_XML                   0x200           //�ճ̡��岥������XML͸��������ƽ̨ר�ã�
#define NET_EHOME_S2C_SCREEN_SHOT                   0x201           //�ն˽���������ƽ̨ר�ã����Ϊ˫�����նˣ���ʾ��������
#define NET_EHOME_S2C_SCREEN_SHOT_SECOND                   0x202           //�ն˽�����˫�����ն˽������ظ�����

#define NET_EHOME_S2C_GET_VCA_VERSION               0x100034        //��ȡ���ܿ�汾��

#define NET_EHOME_S2C_GET_VCA_MASK_REGION           0x100054        //��ȡ����������������
#define NET_EHOME_S2C_SET_VCA_MASK_REGION           0x100055        //��������������������

#define NET_EHOME_S2C_SET_CALIBRATION               0x100080        //���ñ궨����
#define NET_EHOME_S2C_GET_CALIBRATION               0x100081        //��ȡ�궨����

#define NET_EHOME_S2C_GET_PDC_RULECFG_V42           0x113427        //��ȡ������ͳ�ƹ������
#define NET_EHOME_S2C_SET_PDC_RULECFG_V42           0x113428        //���ÿ�����ͳ�ƹ������

#define NET_EHOME_S2C_GET_CAMERA_SETUPCFG           0x11350d        //��ȡ�����װλ��
#define NET_EHOME_S2C_SET_CAMERA_SETUPCFG           0x11350e        //���������װλ��

#define NET_EHOME_S2C_GET_FACESNAPCFG               0x115001        //��ȡ����ץ�Ĳ���
#define NET_EHOME_S2C_SET_FACESNAPCFG               0x115002        //��������ץ�Ĳ���

#define NET_EHOME_S2C_GET_VCA_CTRLINFO_CFG          0x11503e        //������ȡ���ܿ��Ʋ���
#define NET_EHOME_S2C_SET_VCA_CTRLINFO_CFG          0x11503f        //�����������ܿ��Ʋ���

#define NET_EHOME_MAX_TYPE_LEN          32      //ͨ�ó���
#define NET_EHOME_MAX_NAME_LEN          64      //���Ƴ���
#define NET_EHOME_MAX_TERM_NAME_LEN     100     //�ն˵����ֳ���
#define NET_EHOME_MAX_TEXT_MESSAGE_NUM  5       //�ն�һ���������֧�ֵ�������Ϣ����
#define NET_EHOME_MAX_TEXT_CONTENT_NUM  1024    //�岥��������Ϣ���ݵĳ���
#define NET_EHOME_MAX_PLATFROM_URL_LEN  256     //KMS���������ļ���URL��ַ����󳤶�
#define NET_EHOME_MAX_WEATHERINFO_LEN   4*1024  //������Ϣ����󳤶�

//���������ݵķ��ͽṹ
typedef struct tagNET_EHOME_BINARY_SEND_DATA
{
    DWORD   dwSize;
    void*   lpInBuffer;
    DWORD   dwInBufferSize;
    DWORD   dwRecvTimeOut; //���ճ�ʱʱ��
    BYTE    byRes[64];
}NET_EHOME_BINARY_SEND_DATA, *LPNET_EHOME_BINARY_SEND_DATA;

//���������ݵĽ��սṹ
typedef struct tagNET_EHOME_BINARY_RECV_DATA
{
    DWORD   dwSize;
    void*   lpOutBuffer;
    DWORD   dwOutBufferSize;
    BYTE    byRes[64];
}NET_EHOME_BINARY_RECV_DATA, *LPNET_EHOME_BINARY_RECV_DATA;

//�ճ��·�
typedef struct tagNET_EHOME_POST_SCHEDULE
{
    BYTE    byServerIP[32];         //������ip
    DWORD   dwServerPort;           //�������Ķ˿ں�
    DWORD   dwScheduleID;           //�ճ̵�ID���½��ճ�ʱ�����Ψһ����
    DWORD   dwScheduleSeq;          //�ϵ�������ʱ��ʹ�ã�������ʾ�ճ��Ƿ��޸ģ��ܷ��������
    BOOL    byIsDefaultSchedual;    //������ʾ����ճ��Ƿ��ǵ�Ƭ�ճ�
    BYTE    byRes[2];
    DWORD   dwTimingSchedualID;     //��ʱ�ճ̼ƻ���ID����ʾ�ն���Ҫ��ȡ�����ĸ���ʱ�ƻ�
    BYTE    byEffectiveTime[32];    //�ճ̿�ʼ���ŵ�ʱ��
}NET_EHOME_POST_SCHEDULE, *LPNET_EHOME_POST_SCHEDULE;

//������ʾ���͵��ǽк����ݻ�������
typedef enum
{
    NET_EHOME_DATA_INFO_TYPE    = 1,    //�к�����
    NET_EHOME_COMMAND_INFO_TYPE = 2,    //�кſ�������
    NET_EHOME_CANCEL_SHOT_PIC,          //ȡ����̬��ͼ
    NET_EHOME_START_CAPTURE_PIC,        //��ʼץ��
    NET_EHOME_STOP_CAPTURE_PIC,         //ȡ����ʾץ��ͼƬ
}NET_EHOME_THIRD_PARTY_DATA_TYPE;

typedef enum
{
    NET_EHOME_SINGLE_REFRESH_TYPE   = 1, //��������
    NET_EHOME_WHOLE_REFRESH_TYPE    = 2, //ȫ������
    NET_EHOME_OTHER_REFRESH_TYPE,
}NET_EHOME_REFRESH_TYPE;

typedef struct
{
    char    szQueueDataValue[32];
    DWORD   dwQueueDataId;
}NET_EHOME_QUEUE_DATA;

typedef struct
{
    NET_EHOME_QUEUE_DATA queueData[20];
}NET_EHOME_QUEUE_DATALIST;

typedef struct
{
    DWORD   dwQueueDataListCnt; //��
    DWORD   dwQueueDataCnt;     //��
    NET_EHOME_QUEUE_DATALIST struQueueDatalist[4];
}NET_EHOME_QUEUE_ITEM_DATALIST;

//�кŹ�����Ϣ
typedef struct tagNET_EHOME_QUEUE_INFO
{
    DWORD   dwMaterialId;       //�ز�ID
    DWORD   dwQueueId;          //�к�ID
    NET_EHOME_THIRD_PARTY_DATA_TYPE enumDataType;       //��������
    NET_EHOME_REFRESH_TYPE          enumRefreshType;    //���ݸ��·�ʽ
    NET_EHOME_QUEUE_ITEM_DATALIST   struItemDataList;   //�к������б�
}NET_EHOME_QUEUE_INFO, *LPNET_EHOME_QUEUE_INFO;

//��ͼ����
typedef struct tagNET_EHOME_SHOT_PIC
{
    BYTE    byServerIP[32]; //������IP��ַ
    DWORD   dwServerPort;   //�������˿ں�
    DWORD   dwShotPicID;    //��ͼ��ͼƬID
}NET_EHOME_SHOT_PIC, *LPNET_EHOME_SHOT_PIC;

//�����Ӧ
typedef struct tagNET_EHOME_ERRCODE_RET
{
    DWORD dwCmd;        //�����Ӧ�Ĵ�����
    DWORD dwErrCode;    //��Ӧ��NET_EHOME_ERROR_CODE��ֵ
}NET_EHOME_ERRCODE_RET, *LPNET_EHOME_ERRCODE_RET;

//���������ն�֮�䶨��Ĵ����루2.0�����ϰ汾���ã�
enum NET_EHOME_ERROR_CODE
{
    EHOME_OK = 0,
    EHOME_PASSERWORD_ERROR = 1, //�������	
    EHOME_NOT_SUPPORT = 2, //�ն˲�֧��
    EHOME_USERNAME_ERROR = 3, //�û�������
    EHOME_USERNAME_PASSWORD_ERROR = 4, //�û��������������
    EHOME_TERM_RNAME_REPEAT = 5, //�ն������ظ�
    EHOME_TERM_SERIAL_REPEAT = 6, //�ն����к��ظ�
    EHOME_PARAM_ERROR = 7, //��������
    EHOME_TERM_RECEIVING = 8//�ն����ڽ�������
};

//���������Ӧ��������
enum NET_EHOME_CONTROL_TYPE
{
    NET_EHOME_CONTROL_STARTPLAY     = 1,    //��ʼ����
    NET_EHOME_CONTROL_STOPPLAY,             //ֹͣ����
    NET_EHOME_CONTROL_INSERT,               //�岥
    NET_EHOME_CONTROL_STOPINSERT,           //ֹͣ�岥
    NET_EHOME_CONTROL_POWERON,              //����
    NET_EHOME_CONTROL_POWEROFF,             //�ػ�
    NET_EHOME_CONTROL_REBOOT,               //����
    NET_EHOME_CONTROL_RESTORECONFIG,        //�ָ�Ĭ�ϲ���
    NET_EHOME_CONTROL_SCREENOPEN,           //��Ļ��
    NET_EHOME_CONTROL_SCREENCLOSE,          //��Ļ��
    NET_EHOME_CONTROL_PLANCTRL,             //�����Ͷ�ʱ���ػ��ƻ�
    NET_EHOME_CONTROL_CANCELINSERT,         //ȡ���岥
    NET_EHOME_CONTROL_PUBLISH_STATE_SHOW,   //�ն˷���������ʾ
    NET_EHOME_CONTROL_PUBLISH_STATE_HIDE,   //�ն˷�����������
};

//�岥�����ͣ��岥�زĻ��߽�Ŀ
enum NET_EHOME_PROGRAM_INSERT_TYPE
{
    NET_EHOME_INSERT_TYPE_MATERIAL = 1,
    NET_EHOME_INSERT_TYPE_PROGRAM,
};

//λ������
typedef struct tagNET_EHOME_POSITION_INFO
{
    DWORD dwPositionX;
    DWORD dwPositionY;
    DWORD dwHeight;
    DWORD dwWidth;
}NET_EHOME_POSITION_INFO, *LPNET_EHOME_POSITION_INFO;

//�ַ�Ч��
typedef struct
{
    DWORD   dwFontSize;             //�����С
    DWORD   dwFontColor;            //������ɫ
    DWORD   dwBackColor;            //������ɫ
    DWORD   dwBackTransparent;      //͸����
    BOOL    bSubtitlesEnabled;      //ʹ���ַ���ʾģʽ
    BYTE    szScrollDirection[32];  //��������left,right,up,down
    DWORD   dwScrollSpeed;          //�����ٶ�
}NET_EHOME_CHAR_EFFECT;

//�岥Ч��
typedef struct
{
    NET_EHOME_CHAR_EFFECT struCharEffect;   //�ַ�Ч��
    DWORD   dwPageTime;                     //ҳ��ʱ��
    DWORD   dwScrollSpeedWeb;               //ҳ������ٶ�
}NET_EHOME_INSERT_EFFECT;

//�岥�زĻ��߽�Ŀ����Ϣ
typedef struct tagNET_EHOME_INSERT_TEXT_INFO
{
    DWORD   dwTextNo;       //�岥���ļ��������ز�ID���߽�ĿID
    BYTE    szPlayMode[32]; //����ģʽ��byTime��byEndTime
    DWORD   dwCountNum;     //���Ŵ�������ʱ��֧��
    DWORD   dwPlayDuration; //����ʱ��
    BYTE    playEndTime[32];//���ս���ʱ����в岥
    DWORD   dwTextSeq;      //�����ж��ļ�ID��Ӧ���ļ��Ƿ�һ��
}NET_EHOME_INSERT_TEXT_INFO, *LPNET_EHOME_INSERT_TEXT_INFO;

//����ģʽ
enum NET_EHOME_POS_MODE
{
    NET_EHOME_POS_MODE_ILLEGAL      = 0,
    NET_EHOME_POS_MODE_STANDARD     = 1,    //��׼����1920*1920
    NET_EHOME_POS_MODE_RESOLUTION   = 2,    //�ֱ�������
};

//�岥����
typedef struct tagNET_EHOME_INSERT_INFO
{
    DWORD   dwInsertType;       //NET_EHOME_PROGRAM_INSERT_TYPE
    NET_EHOME_INSERT_TEXT_INFO  struMaterialInfo;
    NET_EHOME_INSERT_TEXT_INFO  struProgramInfo;
    NET_EHOME_POSITION_INFO     struPosInfo;
    NET_EHOME_INSERT_EFFECT     struInsertEffect;
}NET_EHOME_INSERT_INFO, *LPNET_EHOME_INSERT_INFO;

//�岥����V20
typedef struct tagNET_EHOME_INSERT_INFO_V20
{
    DWORD   dwInsertType;       //NET_EHOME_PROGRAM_INSERT_TYPE
    NET_EHOME_INSERT_TEXT_INFO  struMaterialInfo;
    NET_EHOME_INSERT_TEXT_INFO  struProgramInfo;
    NET_EHOME_POSITION_INFO     struPosInfo;
    NET_EHOME_INSERT_EFFECT     struInsertEffect;
    DWORD   dwPosMode;          //����ģʽ���μ�ö��NET_EHOME_POS_MODE
    BYTE    byRes[64];
}NET_EHOME_INSERT_INFO_V20, *LPNET_EHOME_INSERT_INFO_V20;

enum NET_EHOME_PLANCTRL_TYPE
{
    NET_EHOME_CONTROL_SWITCHPLAY = 1,   //��ʱ���ػ���Ӧ��EHome����
    NET_EHOME_CONTROL_VOLUMEPLAY,       //������Ӧ��EHome����
    NET_EHOME_CONTROL_INPUTPLAY,        //��ʱ����ƻ��Ƿ����ö�Ӧ�ĵ�EHome����
};

//��ʱ�ƻ�����
typedef struct tagNET_EHOME_PLAY_CTRLPARAM
{
    NET_EHOME_PLANCTRL_TYPE enumPlanType;   //���Ƶ�����
    BOOL    bEnable;                        //�Ƿ�ʹ��
}NET_EHOME_PLAN_CTRLPARAM, *LPNET_EHOME_PLAY_CTRLPARAM;

//�ն˿���
typedef struct tagNET_EHOME_TERMINAL_CONTROL
{
    DWORD   dwControlType;                  //NET_EHOME_CONTROL_TYPE �������������
    NET_EHOME_INSERT_INFO struInsertInfo;   //�岥��صĲ���
    NET_EHOME_PLAN_CTRLPARAM struPlanCtrl;  //��Ϣ�����ն˵Ķ�ʱ�ƻ�����
    DWORD   dwConnPort;                     //���ݴ���˿ڣ���ʱûʹ��
}NET_EHOME_TERMINAL_CONTROL, *LPNET_EHOME_TERMINAL_CONTROL;

//�ն˿���V20
typedef struct tagNET_EHOME_TERMINAL_CONTROL_V20
{
    DWORD   dwControlType;                      //NET_EHOME_CONTROL_TYPE �������������
    NET_EHOME_INSERT_INFO_V20 struInsertInfo;   //�岥��صĲ���
    NET_EHOME_PLAN_CTRLPARAM struPlanCtrl;      //��Ϣ�����ն˵Ķ�ʱ�ƻ�����
    DWORD   dwConnPort;                         //���ݴ���˿ڣ���ʱûʹ��
    BYTE    byRes[64];
}NET_EHOME_TERMINAL_CONTROL_V20, *LPNET_EHOME_TERMINAL_CONTROL_V20;

//������Ϣ������
typedef struct tagNET_EHOME_TEXT_MESSAGE
{
    DWORD   dwId;                                       //������ϢΨһ����
    BYTE    szMsgName[NET_EHOME_MAX_NAME_LEN];          //��Ϣ����
    BYTE    szContent[NET_EHOME_MAX_TEXT_CONTENT_NUM];  //��Ϣ����
    BYTE    szBeginTime[NET_EHOME_MAX_TYPE_LEN];        //��Ϣ��ʼ�岥ʱ��
    BYTE    szEndTime[NET_EHOME_MAX_TYPE_LEN];          //��Ϣ�岥����ʱ��
}NET_EHOME_TEXT_MESSAGE, *LPNET_EHOME_TEXT_MESSAGE;

//�岥������Ϣ
typedef struct tagNET_EHOME_INSERT_CHARACTER
{
    DWORD   dwMessageCnt;
    NET_EHOME_TEXT_MESSAGE struTextMessage[NET_EHOME_MAX_TEXT_MESSAGE_NUM];
    BYTE    szMsgPos[NET_EHOME_MAX_TYPE_LEN];   //��Ϣλ�ã��������в����ײ����Զ���
    NET_EHOME_POSITION_INFO struPosition;       //��Ϣ�Զ���λ�ã�ֻ��msgPosΪ�Զ���ʱ��Ч
    NET_EHOME_CHAR_EFFECT struCharEffect;       //�ַ�Ч��
}NET_EHOME_INSERT_CHARACTER, *LPNET_EHOME_INSERT_CHARACTER;

typedef enum
{
    POWER_ON    = 1,   //����
    POWER_OFF,          //�ػ�
}NET_EHOME_POWER_ONOFF;

typedef enum
{
    INVALID_PLAN    = 0,
    DAYLY_PLAN,         //�ռƻ�
    WEEKLY_PLAN,        //�ܼƻ�
    SELF_DEF_PLAN,      //�Զ���ƻ�
    CIRCLE_PLAN,        //�ֲ�
}NET_EHOME_PLAY_SCHEDULE_TYPE1;

typedef enum
{
    INVALID_DAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
}NET_EHOME_DAY_OF_WEEK1;

//�����������Ϣ
typedef struct
{
    DWORD   dwId;           //��ʾ�ڼ������ػ����ýڵ�
    DWORD   dwSwitchType;   //���ػ����ͣ��������ǹػ���1������2�ػ�
    DWORD   dwSwitchDate;   //�������߹ػ�������
    DWORD   dwSwitchTime;   //�������߹ػ���ʱ�䣬235959 �ȼ���23:59:59
}NET_EHOME_SWITCH_PLAN, *LPNET_EHOME_SWITCHE_PLAN;

//��ʱ���ػ��ռƻ�
typedef struct
{
    DWORD   dwDayPlanCnt; //һ���м������ػ��ڵ�
    NET_EHOME_SWITCH_PLAN struDayPlan[16];
}NET_EHOME_SWITCH_DAILY_PLAN, *LPNET_EHOME_SWITCH_DAILY_PLAN;

typedef struct
{
    DWORD  dwId;                                    //��ʾ�ڼ���
    NET_EHOME_DAY_OF_WEEK1 enumDayOfWeek;           //��ʾ����һ���е���һ��
    NET_EHOME_SWITCH_DAILY_PLAN struDayOfWeekPlan;  //�ռƻ�
}NET_EHOME_SWITCHE_DAY_OF_WEEK_PLAN, *LPNET_EHOME_SWITCH_DAY_OF_WEEK_PLAN;

//�ܼƻ�
typedef struct
{
    DWORD   dwWeekPlanCnt; //һ���м���Ķ�ʱ�ƻ�
    NET_EHOME_SWITCHE_DAY_OF_WEEK_PLAN struWeekPlan[7];
}NET_EHOME_SWITCH_WEEKLY_PLAN, *LPNET_EHOME_SWITCH_WEEKLY_PLAN;

//���͸��ն˵Ķ�ʱ���ػ������ṹ
typedef struct
{
    NET_EHOME_PLAY_SCHEDULE_TYPE1 enumPlanType;         //�ƻ����ͣ��ܼƻ������ռƻ�
    union
    {
        NET_EHOME_SWITCH_DAILY_PLAN struDailyPlan;      //ÿ��Ķ�ʱ�ƻ�
        NET_EHOME_SWITCH_WEEKLY_PLAN struWeeklyPlan;    //ÿ�ܵĶ�ʱ�ƻ�
    }unionSwitchPlan;
}NET_EHOME_SWITCH_PLAN_PARAM, *LPNET_EHOME_SWITCH_PLAN_PARAM;

//�������������
typedef struct
{
    DWORD   dwId;               //������ʾ�ڼ�����������
    DWORD   dwVolumeValue;      //��������ֵ
    DWORD   dwVolumeBeginDate;  //�����Ŀ�ʼ����
    DWORD   dwVolumeBeginTime;  //�����Ŀ�ʼʱ��235959�ȼ���23:59:59
    DWORD   dwVolumeEndDate;    //��������������
    DWORD   dwVolumeEndTime;    //��������ʱ��
}NET_EHOME_VOLUME_PLAN, *LPNET_EHOME_VOLUME_PLAN;

//������ƻ�
typedef struct
{
    DWORD   dwDayPlanCnt;
    NET_EHOME_VOLUME_PLAN struDayPlan[8]; //ÿһ��������ƻ�
}NET_EHOME_VOLUME_DAILY_PLAN, *LPNET_EHOME_VOLUME_DAILY_PLAN;

typedef struct
{
    DWORD   dwId;
    NET_EHOME_DAY_OF_WEEK1 enumDayOfWeek; //һ���е���һ��
    NET_EHOME_VOLUME_DAILY_PLAN struDayOfWeekPlan;
}NET_EHOME_VOLUME_DAY_OF_WEEK_PLAN, *LPNET_EHOME_VOLUME_DAY_OF_WEEK_PLAN;

//�����ܼƻ�
typedef struct
{
    DWORD   dwWeekPlanCnt;
    NET_EHOME_VOLUME_DAY_OF_WEEK_PLAN struWeekPlan[7];
}NET_EHOME_VOLUME_WEEKLY_PLAN, *LPNET_EHOME_VOLUME_WEEKLY_PLAN;

//���͸��ն˵Ķ�ʱ�������������ṹ
typedef struct
{
    NET_EHOME_PLAY_SCHEDULE_TYPE1 enumPlanType;
    union
    {
        NET_EHOME_VOLUME_DAILY_PLAN struDailyPlan;      //ÿ��Ķ�ʱ�ƻ�
        NET_EHOME_VOLUME_WEEKLY_PLAN struWeeklyPlan;    //ÿ�ܵĶ�ʱ�ƻ�
    }unionVolumePlan;

}NET_EHOME_VOLUME_PLAN_PARAM, *LPNET_EHOME_VOLUME_PLAN_PARAM;

//��ʱ�����л���ĳ��ʱ��Σ�����ļƻ�����
typedef struct tagNET_EHOME_INPUT_DAY_PLAN
{
    DWORD   dwId;
    BYTE    byInputType[32];    //�������ͣ�HDMI,InfoPublish,VGA
    DWORD   dwBeginDate;        //������ת����ʮ����
    DWORD   dwBeginTime;        //235959 �ȼ���23:59:59
    DWORD   dwEndDate;          //��ʱ�����л���ʼʱ��
    DWORD   dwEndTime;          //��ʱ�����л�����ʱ��
}NET_EHOME_INPUT_DAY_PLAN, *LPNET_EHOME_INPUT_DAY_PLAN;

//��Ϣ����ƽ̨HDMI����Ϣ�����л��ռƻ�
typedef struct tagNET_EHOME_INPUT_DAILY_PLAN
{
    DWORD   dwDayPlanCnt;                       //һ����ٸ���ʱ�����л�
    NET_EHOME_INPUT_DAY_PLAN struDayPlan[8];    //���֧��8��
}NET_EHOME_INPUT_DAILY_PLAN, *LPNET_EHOME_INPUT_DAILY_PLAN;

//HDMI����Ϣ�����л�һ����ĳһ��ļƻ�
typedef struct tagNET_EHOME_INPUT_DAY_OF_WEEK_PLAN
{
    DWORD   dwId;
    NET_EHOME_DAY_OF_WEEK1 enumDayOfWeek; //��
    NET_EHOME_INPUT_DAILY_PLAN struDayOfWeekPlan;
}NET_EHOME_INPUT_DAY_OF_WEEK_PLAN, *LPNET_EHOME_INPUT_DAY_OF_WEEK_PLAN;

//��Ϣ����ƽ̨HDMI����Ϣ�����л��ܼƻ�
typedef struct tagNET_EHOME_INPUT_WEEKLY_PLAN
{
    DWORD   dwWeekPlanCnt;
    NET_EHOME_INPUT_DAY_OF_WEEK_PLAN struWeekPlan[7]; //7��
}NET_EHOME_INPUT_WEEKLY_PLAN, *LPNET_EHOME_INPUT_WEEKLY_PLAN;

//��Ϣ����ƽ̨HDMI����Ϣ�����л��Զ���ƻ�
typedef struct tagNET_EHOME_INPUT_SELF_PLAN
{
    DWORD   dwSelfPlanCnt;
    NET_EHOME_INPUT_DAY_PLAN struSelfPlan[8];
}NET_EHOME_INPUT_SELF_PLAN, *LPNET_EHOME_INPUT_SELF_PLAN;

//HDMI����Ϣ�����л��ƻ�
typedef struct tagNET_EHOME_INPUT_PLAN
{
    DWORD   dwId;
    BYTE    byPlanType[32];
    union
    {
        NET_EHOME_INPUT_DAILY_PLAN struDailyPlan;
        NET_EHOME_INPUT_WEEKLY_PLAN struWeeklyPlan;
    }unionInputPlan;
}NET_EHOME_INPUT_PLAN, *LPNET_EHOME_INPUT_PLAN;

//�ն˵Ĳ��Ų���
typedef struct tagNET_EHOME_DISPLAY_PARAM
{
    DWORD   dwR;        //��ʾ����ɫ����
    DWORD   dwG;
    DWORD   dwB;
    DWORD   dwOffsetR;  //��ƫ��
    DWORD   dwOffsetG;
    DWORD   dwOffsetB;
    DWORD   dwBrightnessLevel;  //����
    DWORD   dwContrastLevel;    //�Աȶ�
    DWORD   dwSharpnessLevel;   //���
    DWORD   dwSaturationLevel;  //���Ͷ�
    DWORD   dwHueLevel;         //ɫ�����ϱߵĲ�����ʱ��֧�֣����Բ��ø�ֵ
    //�Զ����ȵ���
    BOOL    bAutoLightEnable;   //�Զ����ȵ��ڣ�2.0������
    DWORD   dwLightMode;        //�Զ����ȵ�ֵ��2.0�������и���Χ�ģ�
    DWORD   dwBackLightLevel;   //�������
    BOOL    bBootLogoEnabled;   //����Logo
    DWORD   dwScreenVolume;     //��Ļ��������ʱ��֧��
    //��Ƭ��Ϣ
    BOOL    bDefaultScheduleEnable;     //��Ƭ�ճ��Ƿ�ʹ��
    DWORD   dwDefaultScheduleId;        //��Ƭ�ճ̵�ID
    BYTE    byDefaultScheduleName[32];  //��Ƭ�ճ̵�����
    BOOL    bTemperaturenable;          //�¶Ȱ�ȫ�Ƿ����ã�2.0������
    DWORD   bSecurity;                  //�¶ȵİ�ȫֵ
    DWORD   bProtectValue;              //�¶ȵı���ֵ
}NET_EHOME_DISPLAY_PARAM, *LPNET_EHOME_DISPLAY_PARAM;

//�ն��������
typedef struct tagNET_EHOME_PASSWORD_CFG
{
    BYTE    szOldPwd[32]; //�ϵ�����
    BYTE    szNewPwd[32]; //������
}NET_EHOME_PASSWORD_CFG, *LPNET_EHOME_PASSWORD_CFG;

//�ն˵Ĳ���
typedef struct tagNET_EHOME_PLAYER_PARAM
{
    BYTE    szCfgType[32];  //volume,light,logo,defaultSchedule,password,temperature,allParam
    DWORD   dwplayerVolume; //��������
    NET_EHOME_DISPLAY_PARAM struDisplayParam;   //�ն˵Ĳ��Ų���
    NET_EHOME_PASSWORD_CFG struPasswordCfg;     //�ն˵�����
}NET_EHOME_PLAYER_PARAM, *LPNET_EHOME_PLAYER_PARAM;

/*�ն��豸�Ļ�������*/
typedef struct tagNET_EHOME_DEV_DEFAULT_PARAM
{
    BOOL    bAutoLightEnable;       //�Զ����ȵ��ڣ�������
    DWORD   dwLightMode;            //����ֵ��������
    DWORD   dwBackLightLevel;       //�������
    DWORD   dwVolume;               //����
    BOOL    bEnableStartLogo;       //����LOGO�Ƿ�ʹ��
    BOOL    bEnableVolumeTiming;    //��ʱ�����ƻ��Ƿ�ʹ��
    BOOL    bEnablePowerTiming;     //��ʱ���ػ��ƻ��Ƿ�ʹ��
    BOOL    bDefaultScheduleEnable; //��Ƭ�Ƿ�ʹ��
    DWORD   dwDefaultScheduleId;    //��Ƭ�ճ̵�id
    BYTE    szDefaultScheduleName[32]; //��Ƭ�ճ̵�����
    BOOL    bTemperaturenable;      //�¶Ȱ�ȫ�Ƿ����ã�2.0������
    DWORD   dwSecurity;             //�¶ȵİ�ȫֵ
    DWORD   dwProtectValue;         //�¶ȵı���ֵ
}NET_EHOME_DEV_DEFAULT_PARAM, *LPNET_EHOME_DEV_DEFAULT_PARAM;

//�ն˵�IP��Ӧ������
typedef struct tagNET_EHOME_TERM_DEFAULT_GATEWAY
{
    BYTE    szIpAddress[32];    //Ipv4������
    BYTE    szIpv6Address[32];  //Ipv6������
}NET_EHOME_TERM_DEFAULT_GATEWAY, *LPNET_EHOME_TERM_DEFAULT_GATEWAY;

//�ն˵�ip��ַ��Ϣ
typedef struct tagNET_EHOME_TERM_IP_ADDRESS
{
    BYTE    szIpVersion[32];    //v4,v6
    BYTE    szIpAddress[32];    //IP��ַ
    BYTE    szSubnetMask[32];   //��������
    BYTE    szIpv6Address[32];  //Ipv6��ַ����ʱ��֧��
    BYTE    szBitMask[32];      //Ipv6����
    NET_EHOME_TERM_DEFAULT_GATEWAY strDefaultGateway;
}NET_EHOME_TERM_IP_ADDRESS, *LPNET_EHOME_TERM_IP_ADDRESS;

enum NET_EHOME_TIME_ZONE
{
    NET_EHOME_ZONE_GMT_LOCAL,       // ʹ�õ�ǰʱ������
    NET_EHOME_ZONE_GMT_MINUS_12,
    NET_EHOME_ZONE_GMT_MINUS_11,
    NET_EHOME_ZONE_GMT_MINUS_10,
    NET_EHOME_ZONE_GMT_MINUS_9,
    NET_EHOME_ZONE_GMT_MINUS_8,
    NET_EHOME_ZONE_GMT_MINUS_7,
    NET_EHOME_ZONE_GMT_MINUS_6,
    NET_EHOME_ZONE_GMT_MINUS_5,
    NET_EHOME_ZONE_GMT_MINUS_430,
    NET_EHOME_ZONE_GMT_MINUS_4,
    NET_EHOME_ZONE_GMT_MINUS_330,
    NET_EHOME_ZONE_GMT_MINUS_3,
    NET_EHOME_ZONE_GMT_MINUS_2,
    NET_EHOME_ZONE_GMT_MINUS_1,
    NET_EHOME_ZONE_GMT_0,           //UTC ʱ��
    NET_EHOME_ZONE_GMT_PLUS_1,
    NET_EHOME_ZONE_GMT_PLUS_2,
    NET_EHOME_ZONE_GMT_PLUS_3,
    NET_EHOME_ZONE_GMT_PLUS_330,
    NET_EHOME_ZONE_GMT_PLUS_4,
    NET_EHOME_ZONE_GMT_PLUS_430,
    NET_EHOME_ZONE_GMT_PLUS_5,
    NET_EHOME_ZONE_GMT_PLUS_530,
    NET_EHOME_ZONE_GMT_PLUS_545,
    NET_EHOME_ZONE_GMT_PLUS_6,
    NET_EHOME_ZONE_GMT_PLUS_630,
    NET_EHOME_ZONE_GMT_PLUS_7,
    NET_EHOME_ZONE_GMT_PLUS_8,      //������
    NET_EHOME_ZONE_GMT_PLUS_9,
    NET_EHOME_ZONE_GMT_PLUS_930,
    NET_EHOME_ZONE_GMT_PLUS_10,
    NET_EHOME_ZONE_GMT_PLUS_11,
    NET_EHOME_ZONE_GMT_PLUS_12,
    NET_EHOME_ZONE_GMT_PLUS_13,
};

//ʱ��ͬ������
typedef struct tagNET_EHOME_TIME_ADJUST_PARAM
{
    DWORD   dwTimeZone; //�ο�NET_EHOME_TIME_ZONE
    BYTE    szTime[32]; // YYYY-MM-DD HH:MM:SS
}NET_EHOME_TIME_ADJUST_PARAM, *LPNET_EHOME_TIME_ADJUST_PARAM;

//�ն�ADB������Ϣ
typedef struct tagNET_EHOME_ADB_DEBUG
{
    BOOL    bAdbEnable;
    BYTE    bySecreKey[128];
}NET_EHOME_ADB_DEBUG, *LPNET_EHOME_ADB_DEBUG;

//�ն�ʱ����Ϣ
typedef struct tagNET_EHOME_TERM_TIME_ZONE
{
    BYTE    szTimeZone[32]; //ʱ����Ϣ��GMT+08
}NET_EHOME_TERM_TIME_ZONE, *LPNET_EHOME_TERM_TIME_ZONE;

//�ն˵�discoveryģʽ������SADP�Ƿ�ʹ��
typedef struct tagNET_EHOME_DISCOVERY_MODE
{
    BOOL    bSadpMode;
}NET_EHOME_DISCOVERY_MODE, *LPNET_EHOME_DISCOVERY_MODE;

typedef enum
{
    ADDRTYPE_IPV4 = 0,
    ADDRTYPE_IPV6,
    HOSTNAME,
}NET_EHOME_ADDRFORMAT_CMD;

typedef struct tagNET_EHOME_PUBLISH_SERVERADDR
{
    NET_EHOME_ADDRFORMAT_CMD enumAddressingFormatType;
    BYTE    szIpAddress[NET_EHOME_MAX_TYPE_LEN];
    BYTE    szIpv6Address[NET_EHOME_MAX_TYPE_LEN];
    BYTE    szHostName[NET_EHOME_MAX_TYPE_LEN];
    DWORD   dwPortNo;
    BYTE    szUserName[NET_EHOME_MAX_TYPE_LEN];
    BYTE    szPassword[NET_EHOME_MAX_TYPE_LEN];
    BOOL    bRegStatus;
}NET_EHOME_PUBLISH_SERVERADDR, *LPNET_EHOME_PUBLISH_SERVERADDR;

typedef enum
{
    NET_EHOME_NORMAL_IPC,                   //��ͨIPC
    NET_EHOME_SMART_PASSENGER_IPC,          //������IPC
    NET_EHOME_SMART_VALID_PASSENGER_IPC,    //��Ч������IPC������ʶ��
}NET_EHOME_IPC_TYPE;

typedef enum
{
    NET_EHOME_HOST_MODE,    //������
    NET_EHOME_IP_MODE,      //IP��ַ
}NET_EHOME_ADDRESS_TYPE;

//ȡ��Э��
typedef enum
{
    NET_EHOME_TCP = 1,
    NET_EHOME_UDP,
    NET_EHOME_MCAST,
}NET_EHOME_TRANSMINT_PROTOCAL;

//��������
typedef enum
{
    NET_EHOME_MAIN  = 1,    //������
    NET_EHOME_SUB,          //������
    NET_EHOME_THIRD,
}NET_EHOME_STREAM_TYPE;

//����IPC��Ϣ
typedef struct tagNET_EHOME_IPC_INFO
{
    NET_EHOME_IPC_TYPE enumIPCType; //�ο�NET_EHOME_IPC_TYPE
    DWORD   dwId;
    DWORD   chanNum;                //ipc�����Ľ�Ŀ�е�ͨ����
    NET_EHOME_ADDRESS_TYPE enumAddressType; //IP��ַ���ͣ��ο�NET_EHOME_ADDRESS_TYPE
    BYTE    szIpcState[32];         //online��offline����״̬
    BYTE    szHostName[32];         //������
    BYTE    szIpVersion[16];        //v4����v6
    BYTE    szIpAddress[32];        //ipv4��ַ
    BYTE    szIpv6Address[32];      //ipV6��ַ
    DWORD   dwPortNo;               //ipc�Ķ˿ں�
    DWORD   dwIpcChanNum;           //ipcͨ����
    BYTE    szUserName[52];         //ipc��½�û���
    BYTE    szPassWord[32];         //ipc��½����
    NET_EHOME_TRANSMINT_PROTOCAL enumTransmitProtocol;//ȡ��Э�飬�ο�NET_EHOME_TRANSMINT_PROTOCAL
    NET_EHOME_STREAM_TYPE enumStreamType; //�������ͣ��ο�NET_EHOME_STREAM_TYPE
}NET_EHOME_IPC_INFO, *LPNET_EHOME_IPC_INFO;

//�ն˹���IPC��Ϣ
typedef struct tagNET_EHOME_RELATE_IPC_INFO
{
    DWORD               dwIpcNum;       //IPC����������˼���IPC
    NET_EHOME_IPC_INFO  struIpcInfo[6];
}NET_EHOME_RELATE_IPC_INFO, *LPNET_EHOME_RELATE_IPC_INFO;

//��ȡ�豸����״̬
typedef struct tagNET_EHOME_DEV_WORK_STATUS
{
    BYTE    byIdentifyCode[32];     //�ն����к�
    DWORD   dwCpuUsage;             //cpu������
    DWORD   dwMemTotal;             //�ڴ��ܴ�С
    DWORD   dwMemUsed;
    DWORD   dwDiskTotal;            //����������
    DWORD   dwDiskUsed;             //����������
    DWORD   dwTemperature;          //�ն��¶�
    BYTE    bySoftwareVersion[32];  //����汾��
    BYTE    byDspwareVersion[32];   //DSP�汾��
    BYTE    byHardwareVersion[32];  //Ӳ���汾��
    BYTE    bySystemVersion[32];    //ϵͳ�汾��
    BYTE    byMacAddress[2][32];    //���֧��2������
    BOOL    bySwitchEnable;         //��ʱ���ػ��Ƿ�ʹ��
    BOOL    byVolumeEnable;         //��ʱ�����Ƿ�ʹ��
    DWORD   dwRelateScheNo;         //�ճ�id
    BYTE    byScheName[100];        //�ն����ڲ��ŵ��ճ�����
    BYTE    byInstallType[32];      //vertical or horizontal������or����
    DWORD   byResWidth;             //�ֱ���
    DWORD   byResHeight;            //�ֱ���
}NET_EHOME_DEV_WORK_STATUS, *LPNET_EHOME_DEV_WORK_STATUS;

//�ն˽���
typedef struct tagNET_EHOME_SCREEN_SHOT
{
    DWORD   dwServerPort;       //�������˿ں�
    DWORD   dwClientFdIndex;    //�ͻ���fd����
}NET_EHOME_SCREEN_SHOT, *LPNET_EHOME_SCREEN_SHOT;

//��������tcp��·Э��
typedef struct tagNET_EHOME_UPGRADE_CONN_PARAM
{
    BYTE    szServerIP[32]; //������IP��ַ
    DWORD   dwServerPort;   //�������˿ں�
}NET_EHOME_UPGRADE_CONN_PARAM, *LPNET_EHOME_UPGRADE_CONN_PARAM;

//�ն˻�Ӧ����״̬�ṹ��
typedef struct tagNET_EHOME_TERMINAL_UPG_ST_REPORT
{
    DWORD   dwLength;   //�ṹ���ܳ���
    DWORD   dwCheckSum; //У���
    DWORD   dwRetVal;   //1000�����ɹ���1001����������1002����ʧ��1003��ѹ��ʧ�ܣ�1004 APK�汾��ƥ�䣬1005 ROM�汾��ƥ��
    DWORD   dwUpgradPercent;
}NET_EHOME_TERMINAL_UPG_ST_REPORT, *LPNET_EHOME_TERMINAL_UPG_ST_REPORT;

//�ն�����
typedef struct tagNET_EHOME_TERMINAL_NAME
{
    BYTE    szTermName[NET_EHOME_MAX_TERM_NAME_LEN];
}NET_EHOME_TERMINAL_NAME, *LPNET_EHOME_TERMINAL_NAME;

//�ն������Ϣ
typedef struct tagNET_EHOME_SYSCOMPONENT_REDUCED_ADDR
{
    BYTE    szComponentName[32];    //������ƣ����磺SDK    
    BYTE    szComponentPkgName[32]; //������������磺com.hikvision.sdk������Ҫ�ڿͻ�����ʾ
    BYTE    szComponentVersion[32]; //����汾�����磺V2.0.2 build 20180705
    DWORD   dwIsEnableAutoStart;    //�Ƿ񿪻�����������ʱ����Ҫ�ڿͻ�����ʾ
    DWORD   dwIsSupportUpgrade;     //�Ƿ�֧��Զ������  
    BYTE    byRes[20];
}NET_EHOME_SYSCOMPONENT_REDUCED_ADDR, *LPNET_EHOME_SYSCOMPONENT_REDUCED_ADDR;

typedef struct tagNET_EHOME_COMPONENT_GROUP_INFO
{
    DWORD   dwComponentNum; //ϵͳ�������
    NET_EHOME_SYSCOMPONENT_REDUCED_ADDR struSysComponentAddr[6]; //�����Ϣ
    BYTE    byRes[20];
}NET_EHOME_COMPONENT_GROUP_INFO, *LPNET_EHOME_COMPONENT_GROUP_INFO;

//�ز��滻
typedef struct tagNET_EHOME_REPLACE_MATERIAL
{
    BYTE    szServerIP[NET_EHOME_MAX_TYPE_LEN]; //������IP
    DWORD   dwServerPort;   //�������˿�
    DWORD   dwMaterialId;   //�ز�ID
    DWORD   dwMaterialSeq;  //�ز�Seq
}NET_EHOME_REPLACE_MATERIAL, *LPNET_EHOME_REPLACE_MATERIAL;

//IPAG�ճ̡��岥������XML͸��
typedef struct tagNET_EHOME_POST_PUBLISH_XML
{
    BYTE    szServerIP[32];     //������IP
    DWORD   szServerPort;       //�������Ķ˿ں�
    DWORD   dwTerminalID;       //�ն�ID�����ؽ���ʱ������  
    DWORD   dwXmlUniqueSeq;     //Ψһxml��ʾ
    DWORD   dwXmlSizeH;         //xml��С��32λ
    DWORD   dwXmlSizeL;         //xml��С��32λ
    BYTE    byStorageId[128];   //xml�ļ����λ��
    BYTE	byRes[16];          //�����ֶ�
}NET_EHOME_POST_PUBLISH_XML, *LPNET_EHOME_POST_PUBLISH_XML;

//����������Ϣ
typedef struct tagNET_EHOME_WEATHER_INFO
{
    BYTE   byCityCode[32];          //���б���
    BYTE   byWeatherData[4 * 1024]; //��������
}NET_EHOME_WEATHER_INFO, *LPNET_EHOME_WEATHER_INFO;

//�ն˵����к�
typedef struct tagNET_EHOME_IDENTIFICATION
{
    BYTE bySerialNumber[32]; //����ֶ���ʱû��
    BYTE byIdentifyCode[32]; //�ն˵����кţ���������
}NET_EHOME_IDENTIFICATION, *LPNET_EHOME_IDENTIFICATION;

//�ն���Ϣ
typedef struct tagNET_EHOME_TERMINAL_INFO
{
    NET_EHOME_IDENTIFICATION struDevIdentify;
    DWORD   dwNetUintType;
    BYTE    byDeviceID[NET_EHOME_MAX_TYPE_LEN];
    BYTE    byPassWord[NET_EHOME_MAX_TYPE_LEN];
    BYTE    byFirmWareVersion[NET_EHOME_MAX_TYPE_LEN];
    BYTE    byLocalIP[NET_EHOME_MAX_TYPE_LEN]; //�ն�ͨ��IP
    DWORD   dwLocalPort;
    DWORD   dwDevType;
    DWORD   dwManufacture;  //0-hikvision
    BOOL    bDetectPackage; //1-̽�����0-ע���
    BOOL    bReliableTrans; //1-֧�ֿɿ����䣬0-��֧�ֿɿ�����
    BYTE    byServerUserName[NET_EHOME_MAX_NAME_LEN]; //�������û���
    BYTE    byServerUserPassword[NET_EHOME_MAX_NAME_LEN]; //����������
    BYTE    byTerminalName[NET_EHOME_MAX_NAME_LEN]; //��ע����ն˵�����
}NET_EHOME_TERMINAL_INFO, *LPNET_EHOME_TERMINAL_INFO;

//��Ϣ������������Ϣ
typedef struct tagNET_EHOME_RELEASE_SERVER_INFO
{
    DWORD   dwKeepAliveSeconds;     //����ʱ�䣬Ĭ��50s
    BYTE    byAlarmServerIP[32];
    DWORD   dwAlarmServerPort;
    DWORD   dwAlarmServerType;      //ͨ�����ͣ�0-TCP, 1-UDP��Ĭ��Ϊ0
    DWORD   dwAlarmServerTcpPort;   //������Ϊ�ն�����ı����˿�
    BYTE    byNtpServerIP[32];
    DWORD   dwNtpServerPort;
    DWORD   dwNtpInterval;
    BYTE    byPicServerIP[32];
    DWORD   dwPicServerPort;
    DWORD   dwPicServerType;
    BYTE    byBlackListAddr[32];
    BYTE    byBlackListName[32];
    DWORD   dwBlackListPort;
    BYTE    byBlackListUser[32];
    BYTE    byBlackListPasswd[32];
    DWORD   dwTranserialSvrPort;
    BOOL    bReliableTransmission;
}NET_EHOME_RELEASE_SERVER_INFO, *LPNET_EHOME_RELEASE_SERVER_INFO;

//�ն˽���������ƽ̨ר�ã�
typedef struct tagNET_EHOME_SCREEN_SHOT_EX
{
    DWORD  dwServerPort;    //�������˿ں�
    DWORD  dwClientFdIndex; //�ͻ���fd����
    BYTE   szKmsURL[256];   //�ն�Ҫ�ϴ���KMS��URL��ַ
}NET_EHOME_SCREEN_SHOT_EX, *LPNET_EHOME_SCREEN_SHOT_EX;

//�ն˽������ؽṹ
typedef struct tagNET_EHOME_SCREEN_SHOT_RET
{
    unsigned int    dwConnfd;       //�ն˺ͷ������첽ͨ���׽���
    unsigned int    dwSeq;          //�ն˺ͷ������첽�����ı�ʶ
    char            szUUID[64];     //����ͼƬ��uuidΨһ��ʾ
    char            szPicURL[256];  //��ͼ��KMS�������ϵ�URL��ַ
}NET_EHOME_SCREEN_SHOT_RET, *LPNET_EHOME_SCREEN_SHOT_RET;

NET_DVR_API BOOL CALLBACK NET_ECMS_STDBinaryCfg(LONG lUserID, LONG dwCommand, NET_EHOME_BINARY_SEND_DATA* pSendData, NET_EHOME_BINARY_RECV_DATA* pRecvData);

NET_DVR_API BOOL CALLBACK NET_ECMS_STDBinaryCtrl(LONG lUserID, LONG dwCommand, NET_EHOME_BINARY_SEND_DATA* pSendData);

/** ������Ϣ����˽��Э�� end */

NET_DVR_API LONG CALLBACK NET_ECMS_LongConfigCreate(LONG lUserlD, LPNET_EHOME_LONG_CFG_INPUT pLongCfgInput);

NET_DVR_API BOOL CALLBACK NET_ECMS_LongConfigSend(LONG lHandle, LPNET_EHOME_LONG_CFG_SEND pSend);

NET_DVR_API BOOL CALLBACK NET_ECMS_LongConfigDestory(LONG lHandle);

NET_DVR_API BOOL CALLBACK NET_ECMS_LongConfigGetSessionId(LONG iHandle, LONG* pSessionId);

typedef struct tagNET_EHOME_ASYNC_RESP_CB_DATA
{
    void*   pOutBuffer;     //�豸��Ӧ����
    DWORD   dwOutLen;       //�豸��Ӧ���ݳ���
    DWORD   dwErrorNo;      //SDK������
    DWORD   dwHandle;       //��Ϣ�����Ψһ��ʶ��ƥ���������Ӧ
    LONG    lUserID;        //�û�ID
    char    byRes[32];
}NET_EHOME_ASYNC_RESP_CB_DATA, *LPNET_EHOME_ASYNC_RESP_CB_DATA;

typedef BOOL(CALLBACK * ASYNC_RESPONSE_CB)(LPNET_EHOME_ASYNC_RESP_CB_DATA lpData, void* pUser);

NET_DVR_API BOOL CALLBACK NET_ECMS_SetXmlConfigResponseCB(ASYNC_RESPONSE_CB fnCB, void* pUser);

NET_DVR_API BOOL CALLBACK NET_ECMS_XMLConfigEx(LONG lUserID, NET_EHOME_XML_CFG* pXmlCfg, DWORD* dwHandle);

NET_DVR_API BOOL CALLBACK NET_ECMS_SetAliveTimeout(LONG lUserID, DWORD dwKeepAliveSec, DWORD dwTimeOutCount);

//���ļ�����ӿ� Ŀǰ�в������ṩ
// typedef enum tagNET_ISUP_CMS_LF_CB_TYPE
// {
//     DATETYPE_UNKNOW = 0,        //δ֪����,               ClassType(pOutBuffer) = NULL
//     DATETYPE_EXPECTION = 1,     //�����쳣,               ClassType(pOutBuffer) = DWORD *,��ʾ������
//     DATETYPE_LINK_INFO,         //�豸������ļ�����������Ϣ�ص���  ClassType(pOutBuffer) = LPNET_ISUP_CMS_LF_LINK_INFO
//     DATETYPE_UPLOAD_RSP,        //�ļ��ϴ���Ӧ���        ClassType(pOutBuffer) = LPNET_ISUP_CMS_LARGEFILETRANS__UPLOAD_RSP_PARAM
//     DATETYPE_DOWNLOAD,          //�ļ�����                ClassType(pOutBuffer) = LPNET_ISUP_CMS_LF_DOWNLOAD_PARAM
//     DATETYPE_DOWNLOAD_END,      //�ļ����ؽ���            ClassType(pOutBuffer) = HPR_UINT32 *״ֵ̬���ɹ�=0������ֵ��������
// }NET_ISUP_CMS_LF_CB_TYPE;
// 
// //dwDataType�����Լ�pOutBufferת����NET_ISUP_CMS_LF_CB_TYPE��pInBuffer�����ã�����
// typedef BOOL(CALLBACK * LF_CB)(LONG lLinkHandle, DWORD dwDataType, void* pOutBuffer, DWORD dwOutLen, void* pInBuffer, DWORD dwInLen, void* pUser);
// 
// typedef struct tagNET_ISUP_CMS_LF_LISTEN_PARAM
// {
//     NET_EHOME_IPADDRESS struAddress;    //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ���������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
//     LF_CB               fnCB;           //�����ݴ���ص�����
//     void *              pUserData;      //�û�����
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_LISTEN_PARAM, *LPNET_ISUP_CMS_LF_LISTEN_PARAM;
// 
// //������Ϣ�ص��ṹ��
// typedef struct tagNET_ISUP_CMS_LF_LINK_INFO
// {
//     BYTE                szDeviceID[MAX_DEVICE_ID_LEN];
//     BYTE                szDeviceSerial[NET_EHOME_SERIAL_LEN];
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_LINK_INFO, *LPNET_ISUP_CMS_LF_LINK_INFO;
// 
// typedef struct tagNET_ISUP_CMS_LF_UPLOAD_PARAM
// {
//     char *               pbuf;            //�ļ����ݣ����ļ�ѭ�����ô˽ӿڷ�������
//     DWORD               dwbufLen;        //buf����
//     BOOL                bFileFirst;      //��һ�����ݱ��
//     BOOL                bFileEnd;        //���һ�����ݱ��
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_UPLOAD_PARAM, *LPNET_ISUP_CMS_LF_UPLOAD_PARAM;
// 
// typedef struct tagNET_ISUP_CMS_LF_UPLOAD_RSP_PARAM
// {
//     DWORD               dwResult;        //�ļ��ϴ����
//     char *              pFileURI;        //�ļ��ϴ��豸��Ӧ�ļ���λ��
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_UPLOAD_RSP_PARAM, *LPNET_ISUP_CMS_LF_UPLOAD_RSP_PARAM;
// 
// typedef struct tagNET_ISUP_CMS_LF_DOWNLOAD_PARAM
// {
//     void*               pbuf;
//     DWORD               dwbufLen;        //buf����
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_DOWNLOAD_PARAM, *LPNET_ISUP_CMS_LF_DOWNLOAD_PARAM;
// 
// typedef enum tagNET_ISUP_CMS_LF_SET_BUSINESS_PARAM
// {
//     DATETYPE_URL = 0,                  //URL                 ClassType(pBuffer) = LPNET_ISUP_CMS_LF_PARAM, bufΪURL
//     DATETYPE_INTERACT_BY_BUF,          //��buf���뽻������        ClassType(pBuffer) = NULL
//     DATETYPE_INTERACT_BY_FILE,         //���ļ�·���������ݣ���Ҫ���õ��ļ��� ·����󳤶Ȳ��ܳ���260��ClassType(pBuffer) = LPNET_ISUP_CMS_LF_PARAM, bufΪ�ļ�·��
// }NET_ISUP_CMS_LF_SET_BUSINESS_PARAM;
// 
// typedef struct tagNET_ISUP_CMS_LF_PARAM
// {
//     char *              pBuf;        //Buf���ݲμ�ö��NET_ISUP_CMS_LF_SET_BUSINESS_PARAM
//     DWORD               dwBufLen;
//     BYTE                byRes[128];
// }NET_ISUP_CMS_LF_PARAM, *LPNET_ISUP_CMS_LF_PARAM;
// 
// #define FUN_UPLOAD_SET_PARAM 0  //�ϴ��ӿڲ�������
// #define FUN_DOWNLOAD_SET_PARAM 1 //���ؽӿڲ�������
// 
// NET_DVR_API LONG CALLBACK NET_ISUP_CMS_LFStartListen(LPNET_ISUP_CMS_LF_LISTEN_PARAM lpListenParam);
// NET_DVR_API BOOL CALLBACK NET_ISUP_CMS_LFStopListen(LONG lListenHandle);
// //dwFunType����FUN_UPLOAD_SET_PARAM��FUN_DOWNLOAD_SET_PARAM�� dwBusinessType�μ�ö��ֵNET_ISUP_CMS_LF_SET_BUSINESS_PARAM
// NET_DVR_API BOOL CALLBACK NET_ISUP_CMS_LFSetParam(LONG lLinkHandle, DWORD dwFunType, DWORD dwBusinessType, void* pBuffer);
// //��ѡ����·����ʽ�����ݴ���SDK��lpUploadParam����ΪNULL
// NET_DVR_API BOOL CALLBACK NET_ISUP_CMS_LFUpload(LONG lLinkHandle, LPNET_ISUP_CMS_LF_UPLOAD_PARAM lpUploadParam);
// NET_DVR_API BOOL CALLBACK NET_ISUP_CMS_LFDownload(LONG lLinkHandle);
// NET_DVR_API BOOL CALLBACK NET_ISUP_CMS_LFStopLink(LONG lLinkHandle);

#endif //_HC_EHOME_CMS_H_
