#include "employees.h"
#include <QSqlError>
#include <iostream>
#include <typeinfo>
#include <string>
#include <QMessageBox>
#include <QString>
using namespace std;



Employees::Employees(int id, QString nom, QString prenom, QString gender, QDate date, QString adresse, QString email, QString tel, QString poste, QString mdp, QString Answ1, QString Answ2, QString RFID, int Attempts) {
    Id_E = id;
    Nom_E = nom;
    Prenom_E = prenom;
    Sexe_E = gender;
    Date_Nais_E = date;
    Adresse_E = adresse;
    Email_E = email;
    Tel_E = tel;
    Poste_E = poste;
    Mdp_E = mdp;
    Answ1_E = Answ1;
    Answ2_E = Answ2;
    RFID_E= RFID;
    Attempts_E= Attempts;
}

string Employees::encryptPassword(const string &password) {
    string encrypted = password;
    for (size_t i = 0; i < password.size(); ++i) {
        if (!(i % 2)) {
            encrypted[i] = static_cast<char>(encrypted[i] + 2);
        } else {
            encrypted[i] = static_cast<char>(encrypted[i] - 2);
        }
    }
    return encrypted;
}

string Employees::decryptPassword(const string &password) {
    string decrypted = password;
    for (size_t i = 0; i < password.size(); ++i) {
        if (!(i % 2)) {
            decrypted[i] = static_cast<char>(decrypted[i] - 2);
        } else {
            decrypted[i] = static_cast<char>(decrypted[i] + 2);
        }
    }
    return decrypted;
}

int Employees::getNextId() {
    QSqlQuery query;
    query.prepare("SELECT MAX(ID_E) FROM MAYSSEM.EMPLOYEES;");
    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() + 1;  // Incrémente l'ID de 1
        }
    }
    return 1;  // Si la table est vide, commence à 1
}

/*bool Employees::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO MAYSSEM.EMPLOYEES VALUES(:id_emp,:nom_emp,:prenom_emp,TO_DATE(:date_nais,'yyyy-MM-dd'),:add_emp,:email_emp,:tel_emp,:poste_emp,:mdp_emp,:sexe_emp,:Answ1_emp,:Answ2_emp,:rfid_emp,:attempts_emp);");

    query.bindValue(":id_emp", Id_E);
    query.bindValue(":nom_emp", Nom_E);
    query.bindValue(":prenom_emp", Prenom_E);
    query.bindValue(":date_nais", Date_Nais_E.toString("yyyy-MM-dd"));
    query.bindValue(":add_emp", Adresse_E);
    query.bindValue(":email_emp", Email_E);
    query.bindValue(":tel_emp", Tel_E);
    query.bindValue(":poste_emp", Poste_E);
    query.bindValue(":Answ1_emp", Answ1_E);
    query.bindValue(":Answ2_emp", Answ2_E);
    query.bindValue(":mdp_emp", Mdp_E);

    QString mdp = QString();
    mdp = QString::fromStdString(encryptPassword(Mdp_E.toStdString()));

    query.bindValue(":mdp_emp", mdp);
    query.bindValue(":sexe_emp", Sexe_E);
    query.bindValue(":rfid_emp", RFID_E);
    query.bindValue(":attempts_emp",3);
    qDebug() << "Query: " << query.lastQuery();
    bool res = query.exec();

    if (!res) {
        qDebug() << "Error adding employee:" << query.lastError().text();
    }

    return res;
}*/

QSqlQueryModel* Employees::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select *from MAYSSEM.EMPLOYEES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_E"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_E"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_E"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE_E"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL_E"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("TEL_E"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("POSTE_E"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("MDP_E"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("SEXE_E"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Answ1_E"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Answ2_E"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("RFID_E"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Attempts_E"));


    return model;
}
bool Employees::ajouter() {
    // Récupérer l'ID suivant
    int nextId = getNextId();

    // Préparer la requête d'insertion sans inclure l'ID
    QSqlQuery query;
    query.prepare("INSERT INTO MAYSSEM.EMPLOYEES (id_e, nom_e, prenom_e, date_naissance, adresse_e, email_e, tel_e, poste_e, mdp_e, sexe_e, Answ1_e, Answ2_e, rfid_e, attempts_e) "
                  "VALUES (:id_emp, :nom_emp, :prenom_emp, TO_DATE(:date_nais, 'yyyy-MM-dd'), :add_emp, :email_emp, :tel_emp, :poste_emp, :mdp_emp, :sexe_emp, :Answ1_emp, :Answ2_emp, :rfid_emp, :attempts_emp);");

    query.bindValue(":id_emp", nextId);  // Utiliser l'ID généré
    query.bindValue(":nom_emp", Nom_E);
    query.bindValue(":prenom_emp", Prenom_E);
    query.bindValue(":date_nais", Date_Nais_E.toString("yyyy-MM-dd"));
    query.bindValue(":add_emp", Adresse_E);
    query.bindValue(":email_emp", Email_E);
    query.bindValue(":tel_emp", Tel_E);
    query.bindValue(":poste_emp", Poste_E);
    query.bindValue(":Answ1_emp", Answ1_E);
    query.bindValue(":Answ2_emp", Answ2_E);
    query.bindValue(":mdp_emp", Mdp_E);
    query.bindValue(":sexe_emp", Sexe_E);
    query.bindValue(":rfid_emp", RFID_E);
    query.bindValue(":attempts_emp", 3);

    bool res = query.exec();
    if (!res) {
        qDebug() << "Error adding employee:" << query.lastError().text();
    }
    return res;
}

bool Employees::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE MAYSSEM.EMPLOYEES SET NOM_E=:nom_emp,PRENOM_E=:prenom_emp,DATE_NAISSANCE=TO_DATE(:date_nais,'yyyy-MM-dd'),ADRESSE_E=:add_emp,EMAIL_E=:email_emp,TEL_E=:tel_emp,POSTE_E=:poste_emp,MDP_E=:mdp_emp,SEXE_E=:sexe_emp, Answ1_E=:Answ1_emp,Answ2_E=:Answ2_emp where ID_E= :id_emp");
    query.bindValue(":id_emp", Id_E);
    query.bindValue(":nom_emp", Nom_E);
    query.bindValue(":prenom_emp", Prenom_E);
    query.bindValue(":sexe_emp", Sexe_E);
    query.bindValue(":date_nais", Date_Nais_E.toString("yyyy-MM-dd"));
    query.bindValue(":add_emp", Adresse_E);
    query.bindValue(":email_emp", Email_E);
    query.bindValue(":tel_emp", Tel_E);
    query.bindValue(":poste_emp", Poste_E);
    query.bindValue(":Answ1_emp", Answ1_E);
    query.bindValue(":Answ2_emp", Answ2_E);

    QString mdp = QString();
    mdp = QString::fromStdString(encryptPassword(Mdp_E.toStdString()));

    query.bindValue(":mdp_emp", mdp);
    qDebug() << "Query: " << query.lastQuery();

    bool res = query.exec();
    // Execute the query and check for success
    if (!res) {
        qDebug() << "Error EDITING employee:" << query.lastError().text();
    }

    return res;

}
bool Employees::update_password(int id , const QString &upd_pw)
{
    QSqlQuery query;

    query.prepare("UPDATE MAYSSEM.EMPLOYEES SET MDP_E=:mdp where ID_E= :id_emp");
    query.bindValue(":id_emp", id);
    std::cout<<"id_here:"<<id<<endl;
    std::cout<<"pw_here:"<<upd_pw.toStdString();
    query.bindValue(":mdp", upd_pw);
    qDebug() << "Query: " << query.lastQuery();

    bool res = query.exec();
    // Execute the query and check for success
    if (!res) {
        qDebug() << "Error updating_pw employee:" << query.lastError().text();
    }
    return res;
}

bool Employees::supprimer(int Id_E) {

    QSqlQuery query;
    //QString num_string =QString::number(num);
    query.prepare("Delete from MAYSSEM.EMPLOYEES where ID_E= :id_emp ");
    query.bindValue(":id_emp", Id_E);
    return query.exec();

}

// Function to search an employee by ID in the database
QSqlQueryModel* Employees::search(int id) {
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();

    // Prepare the SQL query to fetch employee data based on the provided ID
    query.prepare("SELECT * FROM MAYSSEM.EMPLOYEES WHERE ID_E = :id_emp");
    query.bindValue(":id_emp", id);

    // Execute the query
    if (query.exec()) {
        if (query.next()) {
            model->setQuery(query);  // Set the result of the query to the model
        } else {
            // No employee found with the given ID
            QMessageBox::warning(nullptr, "No Result", "No employee found with the entered ID.");
        }
    } else {
        // Handle query execution failure
        QMessageBox::critical(nullptr, "Database Error", "Failed to execute query.");
    }

    return model; // Return the model (it can be set to the table view)
}
bool Employees::authenticate(int id, const QString &password, QString &poste) {
    QSqlQuery query;

    // Préparer une requête SQL pour vérifier l'ID et le mot de passe
    query.prepare("SELECT POSTE_E FROM MAYSSEM.EMPLOYEES WHERE ID_E = :id AND MDP_E = :password");
    query.bindValue(":id", id);
    string encrypted_password = Employees::encryptPassword(password.toStdString());
    QString q_encrypted_password;
    q_encrypted_password = QString::fromStdString(encrypted_password);
    query.bindValue(":password", q_encrypted_password);

    // Exécuter la requête
    if (query.exec()) {
        // Vérifier si un résultat existe
        if (query.next()) {
            poste = query.value(0).toString();    // Récupérer le poste de l'employé
            return true;                          // Authentification réussie
        }
    } else {
        qDebug() << "Erreur SQL : " << query.lastError().text();
    }

    return false; // Échec de l'authentification
}


