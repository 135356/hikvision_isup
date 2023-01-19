/**	@File   AUDIOINTERCOM.H
 *
 *	@Note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *
 *	@Brief  ��Ƶ�Խ���
 *
 *	@Author zhangxinyf3 ����
 *
 *	@Date   2012/4/9
 *
 *  @Remark 
 */

#ifndef _AUDIO_INTERCOM_H_
#define _AUDIO_INTERCOM_H_

#ifdef WIN32
    #if defined(_WINDLL)
        #define AUDIOCOM_API  __declspec(dllexport) 
    #else 
        #define AUDIOCOM_API  __declspec(dllimport) 
    #endif
#else
    #ifndef __stdcall
        #define __stdcall
    #endif

    #ifndef AUDIOCOM_API
        #define AUDIOCOM_API
    #endif
#endif

///<������
#define ERROR_NO            1      ///<�޴���
#define ERROR_ALLOC_MEMORY  2      ///<�ڴ�������
#define ERROR_PARAMETER     3      ///<���ò�������
#define ERROR_CALL_ORDER    4      ///<����˳�����
#define ERROR_FIND_DEVICE   5      ///<�����ҵ������豸
#define ERROR_OPEN_DEVICE   6      ///<���ܴ������豸
#define ERROR_NO_CONTEXT    7      ///<�豸��Ƶ���������ĳ���
#define ERROR_NO_WAVEFILE   8      ///<WAV�ļ�����
#define ERROR_INVALID_TYPE  9      ///<��Ч��WAV��������
#define ERROR_ENCODE_FAIL   10     ///<��Ƶ����ʧ��
#define ERROR_DECODE_FAIL   11     ///<��Ƶ����ʧ��
#define ERROR_NO_PLAYBACK   12     ///<��Ƶ����ʧ��
#define ERROR_DENOISE_FAIL  13     ///<����ʧ��
#define ERROR_SUPPORT       14     ///<���Ͳ�֧��
#define ERROR_UNKNOWN       99     ///<δ֪����

///<�����豸��Ϣ�ṹ��
typedef struct _SOUND_CARD_INFO
{
    char           byDeviceName[128];///<�豸����
    unsigned int   dwFrequency;      ///<�ɼ�Ƶ��
    unsigned int   dwRefresh;        ///<ˢ��Ƶ��
    unsigned int   dwSync;           ///<ͬ��
    unsigned int   dwMonoSources;    ///<������Դ����
    unsigned int   dwStereoSources;  ///<������Դ����
    unsigned int   dwMajorVersion;   ///<���汾��
    unsigned int   dwMinorVersion;   ///<�ΰ汾��
    unsigned int   dwReserved[16];   ///<��������
}SoundCardInfo;

///<pcm ������
typedef enum _CHANNEL_PCM_
{
    CHANNEL_1 = 1,                  ///<������
    CHANNEL_2 = 2                   ///<˫����
}ChannelPcm;

///<λ��
typedef enum _BITWIDTH_PCM_
{
    BITS_08 = 8,                    ///<�����ⲻ֧��
    BITS_16 = 16                    ///<16λ
}BitsPcm;

///<pcm������
typedef enum _SAMPLERATE_PCM_
{
    SAMPLERATE_08K  =  8000,         ///<8k������
    SAMPLERATE_16K  = 16000,         ///<16k������
    SAMPLERATE_32K  = 32000,         ///<32k������
    SAMPLERATE_44K1 = 44100,         ///<44.1k������
    SAMPLERATE_48K  = 48000          ///<48k������
}SampleratePcm;

///<���������
typedef enum _BITRATE_ENCODE_
{
    BITRATE_ENCODE_08k = 8000,      ///<8k������
    BITRATE_ENCODE_16k = 16000,     ///<16k������
    BITRATE_ENCODE_32k = 32000,     ///<32k������
	BITRATE_ENCODE_64k = 64000,     ///<64k������
	BITRATE_ENCODE_128k = 128000    ///<128k������
	
}BitRateEncode;

///<��Ƶ��������
typedef enum _AUDIO_ENCODE_TYPE_EX
{
    AUDIO_TYPE_PCM    = 0x00,
    AUDIO_TYPE_G711A  = 0x01,
    AUDIO_TYPE_G711U  = 0x02,
    AUDIO_TYPE_G722   = 0x03,
    AUDIO_TYPE_G726   = 0x04,
    AUDIO_TYPE_MPEG2  = 0x05,
    AUDIO_TYPE_AAC    = 0x06,
    AUDIO_TYPE_G729   = 0x07,
    AUDIO_TYPE_ADPCM  = 0x08,
    AUDIO_TYPE_G722c  = 0x09,
    AUDIO_TYPE_MP3    = 0x0A
}AudioEncodeTypeEx;

typedef enum _AUDIO_ENCODE_TYPE
{
    AUDIO_TYPE_PCM_S16K    = 0x00,
    AUDIO_TYPE_G711A_S8K   = 0x01,
    AUDIO_TYPE_G711U_S8K   = 0x02,
    AUDIO_TYPE_G722_S16K   = 0x03,
    AUDIO_TYPE_G726_S8K    = 0x04,
    AUDIO_TYPE_MPEG2_S16K  = 0x05,
    AUDIO_TYPE_AAC_S32K    = 0x06,
    AUDIO_TYPE_PCM_S8K	   = 0x07,
    AUDIO_TYPE_PCM_S32K    = 0x08,
    AUDIO_TYPE_AAC_S16K	   = 0x09,
	AUDIO_TYPE_MP3_S16K  = 0x0A
}AudioEncodeType;

///<��Ƶ������ʽ(ע��pcm������ֵ����������ʡ�����������������϶����Ե�)
typedef struct _AUDIO_PARAM_
{
    unsigned short    nChannel;           ///<PCM������
    unsigned short    nBitWidth;          ///<PCMλ��
    unsigned int      nSampleRate;        ///<PCM������
    unsigned int      nBitRate;           ///<���������
    AudioEncodeTypeEx enAudioEncodeTypeEx;///<��������
}AudioParam;

///<ԭ��Ƶ������ʽ
/*****************************************************************
ԭ��Ƶö������            ����, λ��, ������, ���������, �������  
AUDIO_TYPE_MPEG2_S16K <����> {1, 16, 16000, 64000, AUDIO_TYPE_MPEG2}
AUDIO_TYPE_MP3_S16K    <����> {1, 16, 16000, 64000, AUDIO_TYPE_MP3}
AUDIO_TYPE_G726_S8K   <����> {1, 16,  8000, 16000,  AUDIO_TYPE_G726}
AUDIO_TYPE_G722_S16K  <����> {1, 16, 16000, 16000,  AUDIO_TYPE_G722}
AUDIO_TYPE_G711U_S8K  <����> {1, 16,  8000, 64000, AUDIO_TYPE_G711U}
AUDIO_TYPE_G711A_S8K  <����> {1, 16,  8000, 64000, AUDIO_TYPE_G711A}
AUDIO_TYPE_PCM_S32K   <����> {1, 16, 32000, xxxxx,   AUDIO_TYPE_PCM}
AUDIO_TYPE_PCM_S8K    <����> {1, 16,  8000, xxxxx,   AUDIO_TYPE_PCM}
AUDIO_TYPE_AAC_S16K   <����> {1, 16, 16000, 32000,   AUDIO_TYPE_AAC}
AUDIO_TYPE_AAC_S32K   <����> {1, 16, 32000, 32000,   AUDIO_TYPE_AAC}
*****************************************************************/

///<�ص��������������Ϣ�ṹ��
typedef struct _OUTPUT_DATA_INFO_EX_ 
{
    unsigned char*    pData;
    unsigned int      dwDataLen;
    AudioEncodeTypeEx enDataTypeEx;
}OutputDataInfoEx;

typedef struct _OUTPUT_DATA_INFO_
{
    unsigned char*    pData;
    unsigned int      dwDataLen;
    AudioEncodeType   enDataType;
}OutputDataInfo;

typedef void (__stdcall* OutputDataCallBack)(OutputDataInfo* pstDataInfo,void* pUser);
typedef void (__stdcall* OutputDataCallBackEx)(OutputDataInfoEx* pstDataInfo,void* pUser);


#ifdef __cplusplus
extern "C" {
#endif

/**********************************��ȡ������Ϣ*******************************************************************************/

///<��ȡ��������
AUDIOCOM_API int __stdcall AUDIOCOM_GetSoundCardNum(unsigned int* pdwDeviceNum);

///<��ȡָ���������豸��Ϣ
AUDIOCOM_API int __stdcall AUDIOCOM_GetOneSoundCardInfo(unsigned int dwDeviceIndex, SoundCardInfo* pstDeviceInfo);


///<��ȡ�ɼ��豸������
AUDIOCOM_API int __stdcall AUDIOCOM_GetCaptureDeviceNum(unsigned int* pCaptureDeviceNum);

///<��ȡ�ɼ��豸������
AUDIOCOM_API int __stdcall AUDIOCOM_GetOneCaptureDeviceName(unsigned int dwCaptureDeviceIndex, char* pCaptureDeviceName);


///<��ȡ�����豸������
AUDIOCOM_API int __stdcall AUDIOCOM_GetPlayDeviceNum(unsigned int* pPlayDeviceNum);

///<��ȡ�����豸������
AUDIOCOM_API int __stdcall AUDIOCOM_GetOnePlayDeviceName(unsigned int dwPlayDeviceIndex, char* pPlayDeviceName);


/**********************************�ɼ�����ģ��ӿ�***************************************************************************/

///<����ָ���豸���ƣ������ɼ�����ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_CreateCaptureHandle(int* pnCapturePort, const char* pDeviceName);


///<����ָ���ɼ��豸���ƣ������ɼ�����ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_CreateCaptureHandleEx(int* pnCapturePort, const char* pCapDeviceName);


///<ע��ص�����������ָ����ͬ��ʽ�ı������ݣ���ͨ���ص��������(�ɽӿ�)
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterOutputDataCallBack(int nCapturePort, 
                                                               AudioEncodeType enDataType, 
                                                               OutputDataCallBack pfnOutputDataCallBack, 
                                                               void* pUser);



///<ע��ص�����������ָ����ͬ��ʽ�ı������ݣ���ͨ���ص��������
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterOutputDataCallBackEx(int nCapturePort, 
                                                                 AudioParam *pstAudioParam, 
                                                                 OutputDataCallBackEx pfnOutputDataCallBack, 
                                                                 void* pUser);

///<��ʼ�ɼ�����
AUDIOCOM_API int __stdcall AUDIOCOM_StartCapture(int nCapturePort);

///<ֹͣ�ɼ�����
AUDIOCOM_API int __stdcall AUDIOCOM_StopCapture(int nCapturePort);

///<ע��ɼ�����ǰ�ص�����(�ɽӿ�)
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterCaptureDataCallBack(int nCapturePort, 
                                                                OutputDataCallBack pfnCaptureDataCallBack, 
                                                                void* pUser);

///<ע��ɼ�����ǰ�ص�����
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterCaptureDataCallBackEx(int nCapturePort, 
                                                                  OutputDataCallBackEx pfnCaptureDataCallBack, 
                                                                  void* pUser);

///<�ͷŲɼ�����ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_ReleaseCaptureHandle(int nCapturePort);

///<�ͷŲɼ�����ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_ReleaseCaptureHandleEx(int nCapturePort);

/**********************************���Ž���ģ��ӿ�**************************************************************************/

///<����ָ���豸���ƣ��������Ž���ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_CreatePlayHandle(int* pnPlayPort, const char* pDeviceName);


///<����ָ���豸���ƣ��������Ž���ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_CreatePlayHandleEx(int* pnPlayPort, const char* pDeviceName);
/*
///<ָ���ļ�·������WAV�ļ�
AUDIOCOM_API int __stdcall AUDIOCOM_OpenWaveFile(int nPlayPort, const char* pFilePath);
*/

///<ָ�������ͣ�����
AUDIOCOM_API int __stdcall AUDIOCOM_OpenStream(int nPlayPort, AudioEncodeType enDataType);

///<ָ�������ͣ�����
AUDIOCOM_API int __stdcall AUDIOCOM_OpenStreamEx(int nPlayPort, AudioParam *pstAudioParam);

///<����������
AUDIOCOM_API int __stdcall AUDIOCOM_InputStreamData(int nPlayPort, unsigned char* pData, unsigned int dwDataLen);

///<��ʼ���벥��
AUDIOCOM_API int __stdcall AUDIOCOM_StartPlay(int nPlayPort);

///<ֹͣ���벥��
AUDIOCOM_API int __stdcall AUDIOCOM_StopPlay(int nPlayPort);

///<��������ݻص�(�ɽӿ�)
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterDecodeDataCallBack(int nPlayPort, 
                                                               OutputDataCallBack pfnDecodeDataCallBack, 
                                                               void* pUser);

///<��������ݻص�
AUDIOCOM_API int __stdcall AUDIOCOM_RegisterDecodeDataCallBackEx(int nPlayPort, 
                                                                 OutputDataCallBackEx pfnDecodeDataCallBack, 
                                                                 void* pUser);

///<��������
AUDIOCOM_API int __stdcall AUDIOCOM_SetVolume(int nPlayPort, float fVolume);

///<��ȡ����
AUDIOCOM_API int __stdcall AUDIOCOM_GetVolume(int nPlayPort, float* fVolume);

///<�ͷŲ��Ž���ģ��˿ں�
AUDIOCOM_API int __stdcall AUDIOCOM_ReleasePlayHandle(int nPlayPort);

///<�ͷ�������Դ
//AUDIOCOM_API int __stdcall AUDIOCOM_Release

/******************************************************************************************************************************/

///<��ȡ������Ϣ
AUDIOCOM_API int __stdcall AUDIOCOM_GetLastError(int nPort);

///<��ȡ�汾��
AUDIOCOM_API unsigned int __stdcall AUDIOCOM_GetVersion();

///<�趨�ɼ�״̬
AUDIOCOM_API int __stdcall AUDIOCOM_SetCaptureStatus(int nCapturePort, bool isPlay);
///<��ȡʣ�ಥ�Ż���
AUDIOCOM_API int __stdcall AUDIOCOM_GetPlayBufferRemian(int nPlayPort, int *nBufferSize);
///<�趨����״̬
AUDIOCOM_API int __stdcall AUDIOCOM_SetPlayStatus(int nPlayPort, bool isPlay);



#ifdef __cplusplus
}
#endif


#endif//_AUDIO_INTERCOM_H_