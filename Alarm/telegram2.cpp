#include "telegram2.h"
#include "alarm.h"

telegram2::telegram2()
{

}

void telegram2::imagen()
{
       QNetworkAccessManager manager;
       QString imagePath = "/home/ingelect/Escritorio/Alarm/fotoControl/"+ alarm::getTime2()+".jpeg";

       QFileInfo fileInfo(imagePath);
       QString fileName = fileInfo.fileName();

       QString message = fileName;

       // Construir la URL de la API de Telegram
       QUrl url("https://api.telegram.org/keyBot/sendPhoto");

       // Construir el cuerpo de la solicitud
       QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

       // Agregar el token del bot y el chat_id al cuerpo de la solicitud
       QString chatId = "";
       QHttpPart tokenPart;
       tokenPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"chat_id\""));
       tokenPart.setBody(chatId.toUtf8());
       multiPart->append(tokenPart);

       //Agregar el texto al cuerpo de la solicitud

       QHttpPart textPart;
       textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"caption\""));
       textPart.setBody(message.toUtf8());
       multiPart->append(textPart);

       // Agregar la imagen al cuerpo de la solicitud
       QHttpPart imagePart;
       imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg")); // Cambia el tipo de contenido según el tipo de imagen
       imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\";filename=\"foto.jpeg\""));
       QFile *file = new QFile(imagePath);
       file->open(QIODevice::ReadOnly);
       imagePart.setBodyDevice(file);
       file->setParent(multiPart); // El archivo se eliminará automáticamente cuando se elimine el multiPart
       multiPart->append(imagePart);

       // Crear la solicitud
       QNetworkRequest request(url);

       // Enviar la solicitud
       QNetworkReply *reply = manager.post(request, multiPart);

       // Manejar la respuesta
       QObject::connect(reply, &QNetworkReply::finished, [=]() {
           if (reply->error() == QNetworkReply::NoError) {
               qDebug() << "Imagen enviada correctamente.";
               file->remove();
           } else {
               qDebug() << "Error al enviar la imagen:" << reply->errorString();
           }
           reply->deleteLater();
           multiPart->deleteLater();
       });
       // Iniciar el bucle de eventos
       QEventLoop eventLoop;
       QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
       eventLoop.exec();
}

