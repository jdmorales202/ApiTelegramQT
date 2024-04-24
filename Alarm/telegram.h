#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include <QEventLoop>
#include <QDir>
#include <QHttpMultiPart>
#include <QImage>


class Telegram
{
public:
    Telegram();
    void llamadoTele();
};

#endif // TELEGRAM_H
