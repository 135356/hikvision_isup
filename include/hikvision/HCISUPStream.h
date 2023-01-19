#ifndef _HC_EHOME_STREAM_H_
#define _HC_EHOME_STREAM_H_

#include "HCISUPPublic.h"


typedef struct tagNET_EHOME_PREVIEW_CB_MSG
{
    BYTE    byDataType;    //NET_DVR_SYSHEAD(1)-����ͷ��NET_DVR_STREAMDATA(2)-��������
    BYTE    byRes1[3];
    void*   pRecvdata;     //����ͷ��������
    DWORD   dwDataLen;     //���ݳ���
    BYTE    byRes2[128];
}NET_EHOME_PREVIEW_CB_MSG, *LPNET_EHOME_PREVIEW_CB_MSG;

typedef void(CALLBACK *PREVIEW_DATA_CB)(LONG iPreviewHandle, NET_EHOME_PREVIEW_CB_MSG* pPreviewCBMsg, void* pUserData);

typedef struct tagNET_EHOME_NEWLINK_CB_MSG
{
    BYTE    szDeviceID[MAX_DEVICE_ID_LEN];      //�豸��ʾ��(����)
    LONG    iSessionID;                         //�豸�������ȡ���Ự��ID(����)
    DWORD   dwChannelNo;                        //�豸ͨ����(����)
    BYTE    byStreamType;                       //0-��������1-������(����)
    BYTE    byRes1[2];
    BYTE    byStreamFormat;                     //��װ��ʽ��0- PS,1-��׼��(���)
    char   sDeviceSerial[NET_EHOME_SERIAL_LEN]; //�豸���кţ��������к�(����)
#if (defined(OS_WINDOWS64) || defined(OS_POSIX64))//win64��linux64��ָ��Ϊ8�ֽ�
    PREVIEW_DATA_CB    fnPreviewDataCB;    //���ݻص�����(���)
    void               *pUserData;         //�û�����, ��fnPreviewDataCB�ص�����(���)
#else
    PREVIEW_DATA_CB    fnPreviewDataCB;    //���ݻص�����(���)
    BYTE               byRes2[4];
    void               *pUserData;         //�û�����, ��fnPreviewDataCB�ص�����(���)
    BYTE               byRes3[4];
#endif 
    BYTE               byRes[96];
}NET_EHOME_NEWLINK_CB_MSG, *LPNET_EHOME_NEWLINK_CB_MSG;

typedef BOOL (CALLBACK *PREVIEW_NEWLINK_CB)(LONG lLinkHandle, NET_EHOME_NEWLINK_CB_MSG* pNewLinkCBMsg, void* pUserData);

typedef struct tagNET_EHOME_LISTEN_PREVIEW_CFG
{
    NET_EHOME_IPADDRESS struIPAdress;   //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ���������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
    PREVIEW_NEWLINK_CB  fnNewLinkCB;    //Ԥ������ص����������յ�Ԥ�����������SDK��ص��ûص�������
    void*               pUser;          // �û���������fnNewLinkCB�з��س���
    BYTE                byLinkMode;     //0��TCP��1��UDP 2: HRUDP��ʽ 8��NPQ��ʽ
	BYTE                byLinkEncrypt;  //�Ƿ�������·����,TCPͨ��TLS���䣬UDP(����NPQ)ʹ��DTLS���䣬0-�����ã�1-����
    BYTE                byRes[126];
}NET_EHOME_LISTEN_PREVIEW_CFG, *LPNET_EHOME_LISTEN_PREVIEW_CFG;

typedef struct tagNET_EHOME_PREVIEW_DATA_CB_PARAM
{
    PREVIEW_DATA_CB fnPreviewDataCB;    //���ݻص�����
    void*           pUserData;          //�û�����, ��fnPreviewDataCB�ص�����
    BYTE            byStreamFormat;     //��װ��ʽ��0- PS
    BYTE            byRes[127];         //����
}NET_EHOME_PREVIEW_DATA_CB_PARAM, *LPNET_EHOME_PREVIEW_DATA_CB_PARAM;

typedef enum tagNET_EHOME_ESTREAM_INIT_CFG_TYPE
{
    NET_EHOME_ESTREAM_INIT_CFG_LIBEAY_PATH = 0, //����OpenSSL��libeay32.dll/libcrypto.so����·��
    NET_EHOME_ESTREAM_INIT_CFG_SSLEAY_PATH = 1,  //����OpenSSL��ssleay32.dll/libssl.so����·��
	NET_EHOME_ESTREAM_INIT_CFG_USERCERTIFICATE_PATH = 2, //����TLS������DTLS�����ķ�����֤��·����TLS��DTLS����ͬһ��֤��
	NET_EHOME_ESTREAM_INIT_CFG_USERPRIVATEKEY_PATH = 3 //����TLS������DTLS������˽Կ֤��·����TLS��DTLS����ͬһ��֤��
}NET_EHOME_ESTREAM_INIT_CFG_TYPE;

typedef struct tagNET_EHOME_LOCAL_PLAYBACK_PARAM
{
    DWORD dwSize;
    BYTE  byPlayBackSync;    //�Ƿ����ط�ͬ�����գ�0-��ʾʹ���첽��ʽ��1-��ʾʹ��ͬ����ʽ;
    BYTE  byRes[131];
}NET_EHOME_LOCAL_PLAYBACK_PARAM, *LPNET_EHOME_LOCAL_PLAYBACK_PARAM;

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_Init();

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_Fini();

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_SetSDKInitCfg(NET_EHOME_ESTREAM_INIT_CFG_TYPE enumType, void* const lpInBuff);

NET_DVR_API DWORD CALLBACK NET_ESTREAM_GetLastError();

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_SetExceptionCallBack(DWORD dwMessage, HANDLE hWnd, void (CALLBACK* fExceptionCallBack)(DWORD dwType, LONG iUserID, LONG iHandle, void* pUser), void* pUser);

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_SetLogToFile(LONG iLogLevel, char *strLogDir, BOOL bAutoDel);

//��ȡ�汾��
NET_DVR_API DWORD CALLBACK NET_ESTREAM_GetBuildVersion();

NET_DVR_API LONG  CALLBACK NET_ESTREAM_StartListenPreview(LPNET_EHOME_LISTEN_PREVIEW_CFG pListenParam);

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_StopListenPreview(LONG iListenHandle);

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_StopPreview(LONG iPreviewHandle);

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_SetPreviewDataCB(LONG iHandle, LPNET_EHOME_PREVIEW_DATA_CB_PARAM pStruCBParam);

NET_DVR_API BOOL  CALLBACK NET_ESTREAM_SetStandardPreviewDataCB(LONG iHandle, LPNET_EHOME_PREVIEW_DATA_CB_PARAM pStruCBParam);

#define NET_EHOME_DEVICEID_LEN        256 //�豸ID����

typedef struct tagNET_EHOME_PLAYBACK_DATA_CB_INFO
{
    DWORD   dwType;     //���� 0-ͷ��Ϣ 1-�������� 15-HLS�����ط�
    BYTE*   pData;      //����ָ��
    DWORD   dwDataLen;  //���ݳ���
    BYTE    byRes[128]; //����
}NET_EHOME_PLAYBACK_DATA_CB_INFO, *LPNET_EHOME_PLAYBACK_DATA_CB_INFO;

typedef BOOL(CALLBACK *PLAYBACK_DATA_CB)(LONG iPlayBackLinkHandle, NET_EHOME_PLAYBACK_DATA_CB_INFO* pDataCBInfo, void* pUserData);

typedef struct tagNET_EHOME_PLAYBACK_NEWLINK_CB_INFO
{
    char         szDeviceID[NET_EHOME_DEVICEID_LEN];   //�豸��ʾ��(����)
    LONG         lSessionID;     //�豸������ûطŻỰ��ID��0��ʾ��Ч(����)
    DWORD        dwChannelNo;    //�豸ͨ���ţ�0��ʾ��Ч(����)
    char         sDeviceSerial[NET_EHOME_SERIAL_LEN/*12*/]; //�豸���кţ��������к�(����)
    BYTE         byStreamFormat;         //������װ��ʽ��0-PS 1-RTP(���) 
    BYTE         byRes1[3];
#if (defined(OS_WINDOWS64) || defined(OS_POSIX64))//win64��linux64��ָ��Ϊ8�ֽ�
    PLAYBACK_DATA_CB   fnPlayBackDataCB;   //���ݻص�����(���)
    void*              pUserData;         //�û�����, ��fnPlayBackDataCB�ص�����(���)
#else
    PLAYBACK_DATA_CB   fnPlayBackDataCB;   //���ݻص�����(���)
    BYTE               byRes2[4];
    void*              pUserData;         //�û�����, ��fnPlayBackDataCB�ص�����(���)
    BYTE               byRes3[4];
#endif
    BYTE               byRes[88];
}NET_EHOME_PLAYBACK_NEWLINK_CB_INFO, *LPNET_EHOME_PLAYBACK_NEWLINK_CB_INFO;

typedef BOOL (CALLBACK *PLAYBACK_NEWLINK_CB)(LONG lPlayBackLinkHandle, NET_EHOME_PLAYBACK_NEWLINK_CB_INFO* pNewLinkCBInfo, void* pUserData);

typedef struct tagNET_EHOME_PLAYBACK_LISTEN_PARAM
{
    NET_EHOME_IPADDRESS struIPAdress;   //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ��
    //�������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
    PLAYBACK_NEWLINK_CB fnNewLinkCB;    //�ط������ӻص�����
    void*               pUserData;      //�û���������fnNewLinkCB�з��س���
    BYTE                byLinkMode;     //0��TCP��1��UDP (UDP����)
	BYTE                byLinkEncrypt;  //�Ƿ�������·����,TCPͨ��TLS���䣬UDP(����NPQ)ʹ��DTLS���䣬0-�����ã�1-����
    BYTE                byRes[126];
}NET_EHOME_PLAYBACK_LISTEN_PARAM, *LPNET_EHOME_PLAYBACK_LISTEN_PARAM;


typedef struct tagNET_EHOME_PLAYBACK_DATA_CB_PARAM
{
    PLAYBACK_DATA_CB    fnPlayBackDataCB;   //���ݻص�����
    void*               pUserData;          //�û�����, ��fnPlayBackDataCB�ص�����
    BYTE                byStreamFormat;     //������װ��ʽ��0-PS 1-RTP 
    BYTE                byRes[127];         //����
}NET_EHOME_PLAYBACK_DATA_CB_PARAM, *LPNET_EHOME_PLAYBACK_DATA_CB_PARAM;

#define EHOME_PREVIEW_EXCEPTION     0x102    //Ԥ��ȡ���쳣
#define EHOME_PLAYBACK_EXCEPTION    0x103    //�ط�ȡ���쳣
#define EHOME_AUDIOTALK_EXCEPTION   0x104    //�����Խ�ȡ���쳣

#define NET_EHOME_SYSHEAD           1    //ϵͳͷ����
#define NET_EHOME_STREAMDATA        2    //��Ƶ������
#define NET_EHOME_STREAMEND         3    //��Ƶ���������
#define NET_EHOME_HLS               15   //HLS�ط�����

NET_DVR_API LONG CALLBACK NET_ESTREAM_StartListenPlayBack(LPNET_EHOME_PLAYBACK_LISTEN_PARAM pListenParam);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_SetPlayBackDataCB(LONG iPlayBackLinkHandle, NET_EHOME_PLAYBACK_DATA_CB_PARAM* pDataCBParam);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_StopPlayBack(LONG iPlayBackLinkHandle);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_StopListenPlayBack(LONG iPlaybackListenHandle);

//--------------------------------------------------------------------------------------------------------------
#define NET_EHOME_DEVICEID_LEN      256 //�豸ID����
#define NET_EHOME_SERIAL_LEN        12

typedef struct tagNET_EHOME_VOICETALK_DATA_CB_INFO
{
    BYTE*   pData;          //����ָ��
    DWORD   dwDataLen;      //���ݳ���
    BYTE    byRes[128];     //����
}NET_EHOME_VOICETALK_DATA_CB_INFO, *LPNET_EHOME_VOICETALK_DATA_CB_INFO;

typedef BOOL(CALLBACK *VOICETALK_DATA_CB)(LONG lHandle, NET_EHOME_VOICETALK_DATA_CB_INFO* pDataCBInfo, void* pUserData);

typedef struct tagNET_EHOME_VOICETALK_NEWLINK_CB_INFO
{
    BYTE    szDeviceID[NET_EHOME_DEVICEID_LEN/*256*/];   //�豸��ʾ��(����)
    DWORD   dwEncodeType; // //SDK��ֵ,��ǰ�Խ��豸��������������,0- G722_1��1-G711U��2-G711A��3-G726��4-AAC��5-MP2L2��6-PCM, 7-MP3, 8-G723, 9-MP1L2, 10-ADPCM, 99-RAW(δʶ������)(����)
    char    sDeviceSerial[NET_EHOME_SERIAL_LEN/*12*/];    //�豸���кţ��������к�(����)
    DWORD   dwAudioChan; //�Խ�ͨ��(����)
    LONG    lSessionID;  //�豸������ûطŻỰ��ID��0��ʾ��Ч(����)
    BYTE    byToken[64];
#if (defined(OS_WINDOWS64) || defined(OS_POSIX64))//win64��linux64��ָ��Ϊ8�ֽ�
    VOICETALK_DATA_CB  fnVoiceTalkDataCB;   //���ݻص�����(���)
    void               *pUserData;         //�û�����, ��fnVoiceTalkDataCB�ص�����(���)
#else
    VOICETALK_DATA_CB  fnVoiceTalkDataCB;   //���ݻص�����(���)
    BYTE               byRes1[4];
    void               *pUserData;         //�û�����, ��fnVoiceTalkDataCB�ص�����(���)
    BYTE               byRes2[4];
#endif 
    BYTE               byRes[48];
} NET_EHOME_VOICETALK_NEWLINK_CB_INFO, *LPNET_EHOME_VOICETALK_NEWLINK_CB_INFO;

typedef BOOL (CALLBACK *VOICETALK_NEWLINK_CB)(LONG lHandle, NET_EHOME_VOICETALK_NEWLINK_CB_INFO* pNewLinkCBInfo, void* pUserData);

typedef struct tagNET_EHOME_LISTEN_VOICETALK_CFG
{
    NET_EHOME_IPADDRESS struIPAdress;       //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ��
    //�������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
    VOICETALK_NEWLINK_CB     fnNewLinkCB;   //�����ӻص�����
    void*          pUser;                   //�û���������fnNewLinkCB�з��س���
	BYTE           byLinkMode;     //0��TCP��1��UDP (UDP����)
	BYTE           byLinkEncrypt;  //�Ƿ�������·����,TCPͨ��TLS���䣬UDP(����NPQ)ʹ��DTLS���䣬0-�����ã�1-����
    BYTE           byRes[126];
}NET_EHOME_LISTEN_VOICETALK_CFG, *LPNET_EHOME_LISTEN_VOICETALK_CFG;

typedef struct tagNET_EHOME_VOICETALK_DATA_CB_PARAM
{
    VOICETALK_DATA_CB   fnVoiceTalkDataCB;  //���ݻص�����
    void*   pUserData;  //�û�����, ��fnVoiceTalkDataCB�ص�����
    BYTE    byRes[128]; //����
}NET_EHOME_VOICETALK_DATA_CB_PARAM, *LPNET_EHOME_VOICETALK_DATA_CB_PARAM;

typedef struct tagNET_EHOME_VOICETALK_DATA
{
    BYTE*   pSendBuf;       //��Ƶ���ݻ�����
    DWORD   dwDataLen;      //��Ƶ���ݳ���
    BYTE    byRes[128];     //����
}NET_EHOME_VOICETALK_DATA, *LPNET_EHOME_VOICETALK_DATA;

NET_DVR_API LONG CALLBACK NET_ESTREAM_StartListenVoiceTalk(LPNET_EHOME_LISTEN_VOICETALK_CFG pListenParam);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_StopListenVoiceTalk(LONG lListenHandle);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_SetVoiceTalkDataCB(LONG lHandle, LPNET_EHOME_VOICETALK_DATA_CB_PARAM pStruCBParam);
NET_DVR_API LONG CALLBACK NET_ESTREAM_SendVoiceTalkData (LONG lHandle, LPNET_EHOME_VOICETALK_DATA pVoicTalkData);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_StopVoiceTalk(LONG lHandle);

NET_DVR_API BOOL CALLBACK NET_ESTREAM_SetSDKLocalCfg(NET_EHOME_LOCAL_CFG_TYPE enumType, void* const lpInBuff);
NET_DVR_API BOOL CALLBACK NET_ESTREAM_GetSDKLocalCfg(NET_EHOME_LOCAL_CFG_TYPE enumType, void* lpOutBuff);


#endif //_HC_EHOME_STREAM_H_