#include "notifier.h"

Notifier::Notifier() {

}

int Notifier::sendEmail() {
  auto server = new SimpleMail::Server;

  // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)
  server->setHost("smtp.gmail.com");
  server->setPort(465);
  server->setConnectionType(SimpleMail::Server::SslConnection);

  // We need to set the username (your email address) and the password for smtp authentification.
  server->setUsername("our.bankpi@gmail.com");
  server->setPassword("eebt juxz fcmn zngm");

  // Now we create a MimeMessage object. This will be the email.
  SimpleMail::MimeMessage message;
  message.setSender(SimpleMail::EmailAddress("housslahbib@gmail.com", "Ali"));
  message.addTo(SimpleMail::EmailAddress("Ali <housslahbib@gmail.com>"));
  message.setSubject("Testing Subject");

  // First we create a MimeText object.
  auto text = std::make_shared<SimpleMail::MimeText>();

  // Now add some text to the email.
  text->setText("Hi,\nThis is a simple email message.\n");

  // Now add it to the mail
  message.addPart(text);

  // Now we can send the mail
  SimpleMail::ServerReply *reply = server->sendMail(message);
  QObject::connect(reply, &SimpleMail::ServerReply::finished, [reply] {
    qDebug() << "ServerReply finished" << reply->error() << reply->responseText();
    reply->deleteLater();// Don't forget to delete it
  });
  return 0;
}


