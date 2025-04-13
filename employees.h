#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QDate>

using namespace std;
class Employees {
    int Id_E;
    QString Nom_E;
    QString Prenom_E;
    QString Sexe_E;
    QDate Date_Nais_E;
    QString Adresse_E;
    QString Email_E;
    QString Tel_E;
    QString Poste_E;
    QString Mdp_E;
    QString Answ1_E;
    QString Answ2_E;
    QString RFID_E;
    int Attempts_E;

public:

    Employees() {}
    Employees(int, QString, QString, QString, QDate, QString, QString, QString, QString, QString, QString, QString,QString,int);

    int getId_E() {
        return Id_E;
    }
    QString getNom_E() {
        return Nom_E;
    }
    QString getPrenom_E() {
        return Prenom_E;
    }
    QString getSexe_E() {
        return Sexe_E;
    }
    QDate getDate_Nais_E() {
        return Date_Nais_E;
    }
    QString getAdresse_E() {
        return Adresse_E;
    }
    QString getEmail_E() {
        return Email_E;
    }
    QString getTel_E() {
        return Tel_E;
    }
    QString getPoste_E() {
        return Poste_E;
    }
    QString getAnsw1_E() {
        return Answ1_E;
    }
    QString getAnsw2_E() {
        return Answ2_E;
    }
    QString getMdp_E() {
        return Mdp_E;
    }
    QString getRFID_E() {
        return RFID_E;
    }
    int getAttempts_E() {
        return Attempts_E;
    }
    void setId_E(int id) {
        Id_E = id;
    }

    void setNom_E(QString nom) {
        Nom_E = nom;
    }
    void setPrenom_E(QString prenom) {
        Prenom_E = prenom;
    }
    void setSexe_E(QString gender) {
        Sexe_E = gender;
    }
    void setDate_Nais_E(QDate date_naiss) {
        Date_Nais_E = date_naiss;
    }
    void setAdresse_E(QString adresse) {
        Adresse_E = adresse;
    }
    void setEmail_E(QString email) {
        Email_E = email;
    }
    void setTel_E(QString tel) {
        Tel_E = tel;
    }
    void setPoste_E(QString poste) {
        Poste_E = poste;
    }
    void setMdp_E(QString mdp) {
        Mdp_E = mdp;
    }

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* search(int);
    bool authenticate(int id, const QString &password, QString &poste);
    string encryptPassword(const string& password);
    static string decryptPassword(const string& encrypted);
    bool update_password(int id , const QString &upd_pw);
    int getNextId();
};

#endif // EMPLOYEES_H
