#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QDebug>
#include "./simple-mail-3.1.0/src/SimpleMail"

using namespace std;

class Notifier {
 public:
  Notifier();
  int sendEmail();
};

#endif // NOTIFIER_H
