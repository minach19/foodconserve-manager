#include "mailer.h"

Mailer::Mailer() {

}

void Mailer::sendEmail(const QString &recipient, const QString &subject, const QString &body) {

    QString smtpServer = "smtp.gmail.com";
    int port = 465;  // or 587 for TLS
    QString username = "our.bankpi@gmail.com";
    QString password = "eebt juxz fcmn zngm";

    QSslSocket socket;
    socket.connectToHostEncrypted(smtpServer, port);
    if (!socket.waitForConnected(30000)) {
        qDebug() << "Failed to connect:" << socket.errorString();
        return;
    }

    QTextStream stream(&socket);

    // Communicate with the SMTP server
    stream << "HELO " << smtpServer << "\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    stream << "AUTH LOGIN\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    // Send base64 encoded username and password
    stream << QByteArray(username.toUtf8().toBase64()) << "\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    stream << QByteArray(password.toUtf8().toBase64()) << "\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    // Send email headers and body
    stream << "MAIL FROM: <" << username << ">\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    stream << "RCPT TO: <" << recipient << ">\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    stream << "DATA\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    stream << "Subject: " << subject << "\r\n\r\n"
           << body << "\r\n.\r\n";
    stream.flush();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    // Close the connection
    stream << "QUIT\r\n";
    stream.flush();
    socket.waitForDisconnected();
}
