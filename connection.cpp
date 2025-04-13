#include "connection.h"
#include <QMessageBox>
#include <iostream>
Connection::Connection() {

}

bool Connection::createconnect() {
  bool test = false;
  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("cannect");                              //  inserer le nom de la source de données
  db.setUserName("Mayssem");                                  //  inserer nom de l'utilisateur
  db.setPassword("Aspirine2314019");                          //  inserer mot de passe de cet utilisateur

  if (db.open())
    test = true;
  std::cout << (test ? "Connected To Database Successfully." : "Error while connecting to Database.") << std::endl;
  return  test;
}
