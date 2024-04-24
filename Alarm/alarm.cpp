#include "alarm.h"

alarm::alarm()
{

}

void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
    int i;
    NET_DVR_ALARMINFO_V30 struAlarmInfo;
    memcpy(&struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO_V30));
    //printf("lCommand is %d, alarm type is %d\n", lCommand, struAlarmInfo.dwAlarmType);
    switch(lCommand)
    {
    case COMM_ALARM_V30:
        {
            switch (struAlarmInfo.dwAlarmType)
            {
            case 3: //�ƶ����ⱨ��
                for (i=0; i<16; i++)   //#define MAX_CHANNUM   16  //����ͨ����
                {
                    if (struAlarmInfo.byChannel[i] == 1)
                    {
                        printf("Motion detection %d\n", i+1);
                    }
                }
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
}


int alarm::Demo_Alarm()
{
    //     if (Demo_AlarmListen() == HPR_ERROR)
    //     {
    //         return HPR_ERROR;
    //     }

        if (Demo_AlarmFortify() == HPR_ERROR)
        {
            return HPR_ERROR;
        }

        return HPR_OK;

}

int alarm::Demo_AlarmFortify()
{
    LONG lUserID;
            NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
            NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
            struLoginInfo.bUseAsynLogin = false;

            struLoginInfo.wPort = 8000;
            memcpy(struLoginInfo.sDeviceAddress, "0.0.0.0", NET_DVR_DEV_ADDRESS_MAX_LEN);
            memcpy(struLoginInfo.sUserName, "", NAME_LEN);
            memcpy(struLoginInfo.sPassword, "", NAME_LEN);

            lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);


        if (lUserID < 0)
        {
            printf("Login error, %d\n", NET_DVR_GetLastError());
            NET_DVR_Cleanup();
            return HPR_ERROR;
        }

        //���ñ����ص�����
        //NET_DVR_SetDVRMessageCallBack_V30(MessageCallback, NULL);
        NET_DVR_SetDVRMessageCallBack_V51(0, MessageCallback, NULL);

        //���ò���
        LONG lHandle;
        NET_DVR_SETUPALARM_PARAM_V50 struSetupAlarmParam = { 0 };
        struSetupAlarmParam.dwSize = sizeof(struSetupAlarmParam);
        struSetupAlarmParam.byRetVQDAlarmType = TRUE; //Prefer VQD Alarm type of NET_DVR_VQD_ALARM
        struSetupAlarmParam.byRetAlarmTypeV40 = TRUE;
        struSetupAlarmParam.byFaceAlarmDetection = 1;//m_comFaceAlarmType.GetCurSel();

        struSetupAlarmParam.byRetDevInfoVersion = TRUE;
        struSetupAlarmParam.byAlarmInfoType = 1;
        struSetupAlarmParam.bySupport = 4;
        lHandle = NET_DVR_SetupAlarmChan_V50(lUserID, &struSetupAlarmParam, NULL, 0);

        if (lHandle < 0)
        {
            printf("NET_DVR_SetupAlarmChan_V50 error, %d\n", NET_DVR_GetLastError());
            NET_DVR_Logout(lUserID);
            NET_DVR_Cleanup();
            return HPR_ERROR;
        }

    #ifdef _WIN32
        Sleep(5000);  //millisecond
    #elif  defined(__linux__) || defined(__APPLE__)
       // sleep(500);   //second
    #endif

        //���������ϴ�ͨ��
        if (!NET_DVR_CloseAlarmChan_V30(lHandle))
        {
            printf("NET_DVR_CloseAlarmChan_V30 error, %d\n", NET_DVR_GetLastError());
            NET_DVR_Logout_V30(lUserID);
            NET_DVR_Cleanup();
            return HPR_ERROR;
        }

        //ע���û�
        NET_DVR_Logout_V30(lUserID);
        //�ͷ�SDK��Դ
        NET_DVR_Cleanup();
        return HPR_OK;
}

int alarm::Demo_AlarmListen()
{
    BOOL iRet;

       //Init
       iRet = NET_DVR_Init();
       if (!iRet)
       {
           printf("   pyd---Alarm. NET_DVR_Init fail!\n");
           return HPR_ERROR;
       }
       //open
       int iHandle = NET_DVR_StartListen_V30("0.0.0.0", 7200, MessageCallback, NULL);
       if (iHandle < 0)
       {
           printf("   pyd---Alarm. NET_DVR_StartListen_V30 fail!%d\n", NET_DVR_GetLastError());
           return HPR_ERROR;
       }
       //close
       iRet = NET_DVR_StopListen_V30(iHandle);
       if (!iRet)
       {
           printf("   pyd---Alarm. NET_DVR_StopListen fail!%d\n", NET_DVR_GetLastError());
           return HPR_ERROR;
       }

       //clean up
       NET_DVR_Cleanup();

       return HPR_ERROR;
}

int alarm::Demo_Capture()
{
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "0.0.0.0", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "", NAME_LEN);

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (lUserID < 0)
    {
        printf("pyd1---Login error, %d\n", NET_DVR_GetLastError());
        return HPR_ERROR;
    }

    //
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 0;
    int iRet;
    //iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, "./foto.jpeg");
    iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, "./foto.jpeg");
    if (!iRet)
    {
        printf("pyd1---NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
        return HPR_ERROR;
    }
    QString newFilename = getTime2() + ".jpeg";
    QString filePath = QDir("fotoControl").filePath(newFilename);
    // Renombra el archivo guardado anteriormente al nuevo nombre de archivo
    if (!QFile::rename("./foto.jpeg", filePath)) {
        qDebug() << "Error al renombrar o guardar el archivo.";
        return HPR_ERROR;
    }

    QStringList command;
    command <<"chmod" << "777" << filePath;

   QProcess process;
   process.start("sudo", command);
   process.waitForFinished(-1);

   if (process.exitCode() != 0) {
       qDebug() << "Error al establecer permisos para la carpeta:" << filePath;
       return HPR_ERROR;
   }

    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();


    return HPR_OK;
}

QString alarm::getTime2()
{
      QString fecha  = QDateTime::currentDateTime().toString("dd-MM-yyyy_hh:mm:ss");
      return fecha;
}
