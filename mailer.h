#ifndef MAILER_H
#define MAILER_H

#include <QtNetwork/QSslSocket>
#include <QTextStream>
#include <QString>

class Mailer
{
public:
    Mailer();
    Mailer(QString, QString, QString);

    void sendEmail(const QString &recipient, const QString &subject, const QString &body);
private:
    QString destinataire;
    QString object,body;
};
#endif // MAILER_H
