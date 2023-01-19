#ifndef _HC_ISUP_SS_H_
#define _HC_ISUP_SS_H_

#include "HCISUPPublic.h"

#define MAX_URL_LEN_SS                  4096    //ͼƬ�������ص�URL����
#define MAX_KMS_USER_LEN                512     //KMS�û�����󳤶�
#define MAX_KMS_PWD_LEN                 512     //KMS������󳤶�
#define MAX_CLOUD_AK_SK_LEN             64      //EHome5.0�洢Э��AK SK��󳤶�

#define SS_CLIENT_FILE_PATH_PARAM_NAME  "File-Path"
#define SS_CLIENT_VRB_FILENAME_CODE     "Filename-Code"
#define SS_CLIENT_KMS_USER_NAME         "KMS-Username"
#define SS_CLIENT_KMS_PASSWIRD          "KMS-Password"
#define SS_CLIENT_CLOUD_AK_NAME         "Access-Key"
#define SS_CLIENT_CLOUD_SK_NAME         "Secret-Key"
#define SS_CLIENT_CLOUD_POOL_ID         "Pool-Id"
#define SS_CLIENT_CLOUD_SERIAL_ID       "Serial-Id"
#define SS_CLIENT_CENTRAL_AK_NAME       "Central-Access-Key"
#define SS_CLIENT_CENTRAL_SK_NAME       "Central-Secret-Key"
#define SS_CLIENT_CENTRAL_POOL_ID       "Central-Pool-Id"

#ifndef MAX_PATH
    #define MAX_PATH 260
#endif

enum NET_EHOME_SS_MSG_TYPE
{
    NET_EHOME_SS_MSG_TOMCAT = 1,       //Tomcat�ص�����
    NET_EHOME_SS_MSG_KMS_USER_PWD,     //KMS�û�������У��
    NET_EHOME_SS_MSG_CLOUD_AK          //EHome5.0�洢Э��AK�ص�
};

enum NET_EHOME_SS_CLIENT_TYPE
{
    NET_EHOME_SS_CLIENT_TYPE_TOMCAT = 1,       //TomcatͼƬ�ϴ��ͻ���
    NET_EHOME_SS_CLIENT_TYPE_VRB,              //VRBͼƬ�ϴ��ͻ���
    NET_EHOME_SS_CLIENT_TYPE_KMS,              //KMSͼƬ�ϴ��ͻ���
    NET_EHOME_SS_CLIENT_TYPE_CLOUD,            //EHome5.0�洢Э��ͻ���
    NET_EHOME_SS_CLIENT_TYPE_CENTRAL           //���Ĵ洢��ʽ�洢Э��
};

//TomcatͼƬ�������ص���Ϣ
typedef struct tagNET_EHOME_SS_TOMCAT_MSG
{
    char    szDevUri[MAX_URL_LEN_SS/*4096*/];         //�豸�����URI
    DWORD   dwPicNum;                         //ͼƬ��
    char*   pPicURLs;                         //ͼƬURL,ÿ��URL MAX_URL_LEN_SS����
    BYTE    byRes[64];
}NET_EHOME_SS_TOMCAT_MSG, *LPNET_EHOME_SS_TOMCAT_MSG;

typedef struct tagNET_EHOME_SS_KMS_MSG
{
    char* strUserName;                      
    char* strPassword;                   
    BYTE  byRes[64];
}NET_EHOME_SS_KMS_MSG, *LPNET_EHOME_SS_KMS_MSG;

//��д��չ�ص������ṹ��
typedef struct tagNET_EHOME_SS_RW_PARAM
{
    const char* pFileName;   //�ļ���
    void* pFileBuf;          //�ļ�����
    DWORD* dwFileLen;   //�ļ���С
    const char* pFileUrl;    //�ļ�url
    void* pUser;             //
    BYTE byAct;         //��д������0-д�ļ���1-���ļ�
    BYTE byUseRetIndex;  //�Ƿ�ʹ���ϲ㷵�ص�pRetIndex��0-��ʹ�ã�1-ʹ��
    BYTE  byRes1[2];
    char *pRetIndex;     //�ϲ����õ�������pRetIndexΪ0ʱ���ɲ����ã�pRetIndexΪ1ʱ������
    BYTE  byRes[56];
}NET_EHOME_SS_RW_PARAM, *LPNET_EHOME_SS_RW_PARAM;

//���Ĵ洢������
typedef struct tagNET_EHOME_SS_CENTRAL_PARAM
{
    const char*  pPoolId;             //poolId ��Դ��id����󳤶�32
    const char*  pSerialID;           //SerialID �豸ID,��󳤶�64
    const char*  pSerialIDUUID;       //SerialID+UUID ��ʾ��Ƶ�ļ�key,��󳤶�64���豸ID���ȣ�+32��UUID����)
    const char*  pBeginTime;          //��ʼʱ��
    const char*  pEndTime;            //����ʱ��
    BYTE         byPoolIdLength;      //poolid ���ȣ����ϴ��ļ�ʱ��Ч
    BYTE         bySerialIDLength;    //SerialID ���ȣ����ϴ��ļ�ʱ��Ч
    BYTE         bySerialIDUUIDLength;//SerialID+UUID ���ȣ�����Ƶ����Ϊ��Ƶ�ļ�ʱ��Ч
    BYTE         byBeginTimeLength;   //��ʼʱ�䳤��
    BYTE         byEndTimeLength;     //����ʱ�䳤��
    BYTE         byTransform;         //�Ƿ���Ҫת��װ��0 - ����Ҫ��1-��Ҫ��Ĭ��Ϊ 0
    BYTE         byRes1[2];
    DWORD        dwRecordType;        //¼�����ͣ�͸�����û��Զ���
    DWORD        dwSourceDataType;    //��Ƶ�ļ����� 4��������Ƶ�ļ����洢�ڲ�����֡��������������������Ƶ�ļ�
    DWORD        dwHeadSize;           //¼��ͷ����
    DWORD        dwErrorCode;         //���Ĵ洢������
    BYTE         byRes[468];
}NET_EHOME_SS_CENTRAL_PARAM, *LPNET_EHOME_SS_CENTRAL_PARAM;

//�ƴ洢�ṹ��
typedef struct tagNET_EHOME_SS_CLOUD_PARAM
{
    const char*  pPoolId;          //poolId ��Դ��id
    BYTE  byPoolIdLength;   //poolid ����
    BYTE  byRes1[3];
    DWORD dwErrorCode;     //�ƴ洢������
    BYTE  byRes[500];
}NET_EHOME_SS_CLOUD_PARAM, *LPNET_EHOME_SS_CLOUD_PARAM;

//KMS�ṹ��
typedef struct tagNET_EHOME_SS_KMS_PARAM
{
    BYTE  byRes[512];
}NET_EHOME_SS_KMS_PARAM, *LPNET_EHOME_SS_KMS_PARAM;

//TOMCAT�ṹ��
typedef struct tagNET_EHOME_SS_TOMCAT_PARAM
{
    BYTE  byRes[512];
}NET_EHOME_SS_TOMCAT_PARAM, *LPNET_EHOME_SS_TOMCAT_PARAM;

//VRB�ṹ��
typedef struct tagNET_EHOME_SS_VRB_PARAM
{
    BYTE  byRes[512];
}NET_EHOME_SS_VRB_PARAM, *LPNET_EHOME_SS_VRB_PARAM;

//�ص��������ص���չ�ṹ��
typedef struct tagNET_EHOME_SS_EX_PARAM
{
    BYTE byProtoType;  //�洢Э������ 1-�ƴ洢��2-tomcat��3-kms��4-vrb, 5-���Ĵ洢Э��
    BYTE byRes[23];
    union
    {
        NET_EHOME_SS_CLOUD_PARAM struCloud;
        NET_EHOME_SS_TOMCAT_PARAM struTomcat;
        NET_EHOME_SS_KMS_PARAM struKms;
        NET_EHOME_SS_VRB_PARAM struVrb;
        NET_EHOME_SS_CENTRAL_PARAM struCentral;
    }unionStoreInfo;
}NET_EHOME_SS_EX_PARAM, *LPNET_EHOME_SS_EX_PARAM;

//��Ϣ�ص�����
typedef BOOL(CALLBACK *EHomeSSMsgCallBack)(LONG iHandle, NET_EHOME_SS_MSG_TYPE enumType
    , void *pOutBuffer, DWORD dwOutLen, void *pInBuffer, DWORD dwInLen, void *pUser);

//�洢�ص�����
typedef BOOL(CALLBACK *EHomeSSStorageCallBack)(LONG iHandle, const char* pFileName, void *pFileBuf, DWORD dwFileLen, char *pFilePath, void *pUser);


//��д�ص����� byAct 0-д 1-�� 2-ɾ
typedef BOOL(CALLBACK *EHomeSSRWCallBack)(LONG iHandle, BYTE byAct, const char* pFileName
    , void *pFileBuf, LONG* dwFileLen, const char* pFileUrl, void *pUser);

//��д�ص�������չ byAct 0-д 1-�� 2-ɾ  pRwParam�������ڴ������ִ洢Э�鹲���ֶΣ�pExStruct���ڴ��ݴ洢Э�������ֶ�
typedef BOOL(CALLBACK *EHomeSSRWCallBackEx)(LONG iHandle, NET_EHOME_SS_RW_PARAM* pRwParam, NET_EHOME_SS_EX_PARAM* pExStruct);

//��������
typedef struct tagNET_EHOME_SS_LISTEN_PARAM
{
    NET_EHOME_IPADDRESS struAddress;        //���ؼ�����Ϣ��IPΪ0.0.0.0������£�Ĭ��Ϊ���ص�ַ���������������£�Ĭ��Ϊ�Ӳ���ϵͳ��ȡ���ĵ�һ��
    char szKMS_UserName[MAX_KMS_USER_LEN];  //KMS�û���
    char szKMS_Password[MAX_KMS_PWD_LEN];   //KMS����
    EHomeSSStorageCallBack fnSStorageCb;    //ͼƬ��������Ϣ�洢�ص�����
    EHomeSSMsgCallBack     fnSSMsgCb;       //ͼƬ��������Ϣ�ص�����
    char  szAccessKey[MAX_CLOUD_AK_SK_LEN]; //EHome5.0�洢Э��AK
    char  szSecretKey[MAX_CLOUD_AK_SK_LEN]; //EHome5.0�洢Э��SK
    void* pUserData;    //�û�����
    BYTE  byHttps;      //�Ƿ�����HTTPs
    BYTE  byRes1[3];
    EHomeSSRWCallBack   fnSSRWCb;   //��д�ص�����
    EHomeSSRWCallBackEx fnSSRWCbEx; //��д�ص�������չ
    BYTE  bySecurityMode;           //[add] by yangzheng 2020/03/13 �洢������������ȫģʽ���أ�Ĭ�Ͽ�����0-������1-�ر�
    BYTE  byRes[51];
}NET_EHOME_SS_LISTEN_PARAM, *LPNET_EHOME_SS_LISTEN_PARAM;


//����Https����
typedef struct tagNET_EHOME_SS_LISTEN_HTTPS_PARAM
{
    BYTE byHttps;      //0-������HTTPS 1-����HTTPS
    BYTE byVerifyMode; //0-������֤(��ֻ֧�ֵ�����֤)
    BYTE byCertificateFileType; //֤������0-pem, 1-ANS1
    BYTE byPrivateKeyFileType;  //˽Կ����0-pem, 1-ANS1
    char szUserCertificateFile[MAX_PATH]; //��Կ֤���ļ�·��
    char szUserPrivateKeyFile[MAX_PATH];  //˽Կ֤���ļ�·��

    DWORD dwSSLVersion; //SSL Method�汾
    //0 - SSL23, 1 - SSL2, 2 - SSL3, 3 - TLS1.0, 4 - TLS1.1, 5 - TLS1.2
    //SSL23�Ǽ���ģʽ����Э�̿ͻ��˺ͷ����ʹ�õ���߰汾

    BYTE byRes3[360];
}NET_EHOME_SS_LISTEN_HTTPS_PARAM, *LPNET_EHOME_SS_LISTEN_HTTPS_PARAM;

//ͼƬ�ϴ��ͻ��˲���
typedef struct tagNET_EHOME_SS_CLIENT_PARAM
{
    NET_EHOME_SS_CLIENT_TYPE enumType; //ͼƬ�ϴ��ͻ�������
    NET_EHOME_IPADDRESS struAddress;    //ͼƬ��������ַ
    BYTE  byHttps;                 //�Ƿ�����HTTPs
    BYTE  byRes[63];
}NET_EHOME_SS_CLIENT_PARAM, *LPNET_EHOME_SS_CLIENT_PARAM;

enum NET_EHOME_SS_INIT_CFG_TYPE
{
    NET_EHOME_SS_INIT_CFG_SDK_PATH = 1,    //����SS�������·������Linux�汾֧�֣�
    NET_EHOME_SS_INIT_CFG_CLOUD_TIME_DIFF = 2,    //�����˴洢������ʱ���ֵ,Ĭ��15����,��С5����,���60����
    NET_EHOME_SS_INIT_CFG_PUBLIC_IP_PORT = 3,    //���ù�����ַ(������������ӳ��ʱ)
    NET_EHOME_SS_INIT_CFG_LIBEAY_PATH = 4,    //����OpenSSL��libeay32.dll��·��
    NET_EHOME_SS_INIT_CFG_SSLEAY_PATH = 5,    //����OpenSSL��ssleay32.dll��·��
    NET_EHOME_SS_INIT_CFG_SQLITE3_PATH = 6    //����sqlite3���·��
};

typedef struct tagNET_EHOME_SS_LOCAL_SDK_PATH{
    char    sPath[MAX_PATH];
    BYTE    byRes[128];
}NET_EHOME_SS_LOCAL_SDK_PATH, *LPNET_EHOME_SS_LOCAL_SDK_PATH;

enum NET_EHOME_SS_TYPE
{
    NET_EHOME_SS_TYPE_TOMCAT = 1,       //Tomcat
    NET_EHOME_SS_TYPE_VRB,              //VRB
    NET_EHOME_SS_TYPE_KMS,              //KMS
    NET_EHOME_SS_TYPE_CLOUD,             //EHome5.0�洢Э��
    NET_EHOME_SS_TYPE_CENTRAL           //���Ĵ洢��ʽ�洢Э��
};

//ͼƬURI
typedef struct tagNET_EHOME_SS_STORAGE_URI
{
    NET_EHOME_SS_TYPE enumType;             //[in]ͼƬ����
    char  szFilename[256];                  // [in]������ļ���ʶ
    char  szUri[MAX_URL_LEN_SS/*4096*/];    // [out]���ɵ�URL
    BYTE  byRes[64];
}NET_EHOME_SS_STORAGE_URI, *LPNET_EHOME_SS_STORAGE_URI;

#define SS_DB_KEY_MAX_LEN 32

typedef struct tagNET_EHOME_SS_INIT_PARAM
{
    char        szKey[SS_DB_KEY_MAX_LEN/*32*/]; //���ݿ���Կ���ַ������ͣ�
    BYTE        byRes[224]; //�����ֽ�
}NET_EHOME_SS_INIT_PARAM, *LPNET_EHOME_SS_INIT_PARAM;


//��ʼ��������ʼ��
NET_DVR_API BOOL  CALLBACK NET_ESS_Init();
NET_DVR_API BOOL  CALLBACK NET_ESS_Init_V11(NET_EHOME_SS_INIT_PARAM *pParam);
NET_DVR_API BOOL  CALLBACK NET_ESS_Fini();
//��ȡ������
NET_DVR_API DWORD CALLBACK NET_ESS_GetLastError();

//��־
NET_DVR_API BOOL CALLBACK NET_ESS_SetLogToFile(LONG iLogLevel, const char *strLogDir, BOOL bAutoDel);

//��ȡ�汾��
NET_DVR_API DWORD CALLBACK NET_ESS_GetBuildVersion();

//����HTTP������Https����
NET_DVR_API BOOL CALLBACK NET_ESS_SetListenHttpsParam(NET_EHOME_SS_LISTEN_HTTPS_PARAM* pSSHttpsParam);

//����ͼƬURI
NET_DVR_API BOOL CALLBACK NET_ESS_GenerateStorageUri(NET_EHOME_SS_STORAGE_URI* pSSStorageUri);

//��������
NET_DVR_API LONG CALLBACK NET_ESS_StartListen(NET_EHOME_SS_LISTEN_PARAM* pSSListenParam);
//�رռ���
NET_DVR_API BOOL  CALLBACK NET_ESS_StopListen(LONG lListenHandle);

//���ó�ʼ������
NET_DVR_API BOOL CALLBACK NET_ESS_SetSDKInitCfg(NET_EHOME_SS_INIT_CFG_TYPE enumType, void* const lpInBuff);

//����ͼƬ�ϴ�/���ؿͻ���
NET_DVR_API LONG CALLBACK NET_ESS_CreateClient(NET_EHOME_SS_CLIENT_PARAM* pClientParam);

//����ͼƬ�ϴ�/���ؿͻ��˳�ʱʱ��,��λms,Ĭ��Ϊ5s
NET_DVR_API BOOL CALLBACK NET_ESS_ClientSetTimeout(LONG lHandle, DWORD dwSendTimeout, DWORD dwRecvTimeout);

//����ͼƬ�ϴ�/���ؿͻ��˲���
NET_DVR_API BOOL CALLBACK NET_ESS_ClientSetParam(LONG lHandle, const char* strParamName, const char* strParamVal);

//ͼƬ�ϴ�/���ؿͻ���ִ���ϴ�
NET_DVR_API BOOL CALLBACK NET_ESS_ClientDoUpload(LONG lHandle, char* strUrl, LONG dwUrlLen);

//ͼƬ�ϴ�/���ؿͻ���ִ������
NET_DVR_API BOOL CALLBACK NET_ESS_ClientDoDownload(LONG lHandle, char* strUrl, void** pFileContent, DWORD& dwContentLen);

//���ٿͻ���
NET_DVR_API BOOL CALLBACK NET_ESS_DestroyClient(LONG lHandle);

//����HMAC-SHA256
NET_DVR_API BOOL CALLBACK NET_ESS_HAMSHA256(const char* pSrc, const char* pSecretKey, char* pSingatureOut, DWORD dwSingatureLen);

//���������Կ
NET_DVR_API BOOL CALLBACK NET_ESS_GENERATE_SECRETKEY(const char* pSrc, const char* pKey, char* pSecretKeyOut, DWORD dwSecretKeyLen);

//ͼƬ�ϴ��ͻ���ִ��ɾ��
NET_DVR_API BOOL CALLBACK NET_ESS_ClientDoDelete(LONG lHandle, char* strUrl);

//ͼƬ�ϴ��ͻ���ִ���ϴ�ʹ��ͼƬbuffer
NET_DVR_API BOOL CALLBACK NET_ESS_ClientDoUploadBuffer(LONG lHandle, char* strUrl, DWORD dwUrlLen, void*pFileContent, DWORD dwContentLen);

#endif //_HC_ISUP_SS_H_

