#ifndef ALARM_H
#define ALARM_H

#define  HPR_OK 0
#define  HPR_ERROR -1

#include "HCNetSDK.h"
#include "telegram2.h"
#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QProcess>



class alarm
{
public:
    alarm();
    int Demo_Alarm();
    int Demo_AlarmListen();
    int Demo_AlarmFortify();
    int Demo_Capture();
    static QString getTime2();

};

#endif // ALARM_H
