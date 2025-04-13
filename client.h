#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
class Client
{
private:
    int id;
    QString first_name;  // New field for the first name
    QString name;        // Existing field for the last name
    int phone_number;
    QDate age;           // Use QDate instead of QDateTime for birthdate
    QString address;
    QString region;      // New field for the region
    QString email;

public:
    // Constructors
    Client() = default;
    Client(int id, const QString& first_name, const QString& name,
           const QDate& age, const QString& address, const QString& region,
           const QString& email, int phone_number);


    // Getters
    int getId() const { return id; }
    QString getFirstName() const { return first_name; }
    QString getName() const { return name; }
    int getPhoneNumber() const { return phone_number; }
    QDate getAge() const { return age; }
    QString getAddress() const { return address; }
    QString getRegion() const { return region; }
    QString getEmail() const { return email; }

    // Setters
    void setId(int id) { this->id = id; }
    void setFirstName(const QString& first_name) { this->first_name = first_name; }
    void setName(const QString& name) { this->name = name; }
    void setPhoneNumber(int phone) { this->phone_number = phone; }
    void setAge(const QDate& age) { this->age = age; }
    void setAddress(const QString& address) { this->address = address; }
    void setRegion(const QString& region) { this->region = region; }
    void setEmail(const QString& email) { this->email = email; }

    // Database operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* search(int);
};


#endif // CLIENT_H
