#include "mainwindow.h"
#include <QApplication>
#include "alarm.h"
#include "telegram.h"
#include "telegram2.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    alarm envio;
    //envio.Demo_Alarm();
    //envio.Demo_AlarmFortify();
    //envio.Demo_AlarmListen();
    envio.Demo_Capture();
    telegram2 img;
    img.imagen();

    return a.exec();
}
