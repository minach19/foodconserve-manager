#include "client.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

// Constructor definition
Client::Client (int id, const QString& first_name, const QString& name,
               const QDate& age, const QString& address, const QString& region,
               const QString& email, int phone_number)
    : id(id), first_name(first_name), name(name), phone_number(phone_number),
    age(age), address(address), region(region), email(email) {}

// Function to add a client to the database
bool Client::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO MAYSSEM.CLIENTS (ID_C, NOM_C, FIRST_NAME_C, AGE_C, ADRESSE_C, REGION_C, E_MAIL_C, TEL_C) "
                  "VALUES (:id, :name, :first_name, TO_DATE(:age, 'yyyy-MM-dd'), :address, :region, :email, :phone_number)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":first_name", first_name);
    query.bindValue(":age", age.toString("yyyy-MM-dd"));
    query.bindValue(":address", address);
    query.bindValue(":region", region);
    query.bindValue(":email", email);
    query.bindValue(":phone_number", phone_number);

    if (!query.exec()) {
        qDebug() << "Error inserting client data:" << query.lastError();
        return false;
    }
    return true;
}

// Function to display all clients
QSqlQueryModel* Client::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MAYSSEM.CLIENTS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Region"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Phone Number"));

    return model;
}

// Function to modify an existing client in the database
bool Client::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE MAYSSEM.CLIENTS SET NOM_C = :name, FIRST_NAME_C = :first_name, AGE_C = TO_DATE(:age, 'yyyy-MM-dd'), "
                  "ADRESSE_C = :address, REGION_C = :region, E_MAIL_C = :email, TEL_C = :phone_number "
                  "WHERE ID_C = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":first_name", first_name);
    query.bindValue(":age", age.toString("yyyy-MM-dd"));
    query.bindValue(":address", address);
    query.bindValue(":region", region);
    query.bindValue(":email", email);
    query.bindValue(":phone_number", phone_number);

    if (!query.exec()) {
        qDebug() << "Error editing client:" << query.lastError();
        return false;
    }
    return true;
}

// Function to delete a client by ID
bool Client::supprimer(int clientId) {
    QSqlQuery query;
    query.prepare("DELETE FROM MAYSSEM.CLIENTS WHERE ID_C = :id");
    query.bindValue(":id", clientId);

    bool res = query.exec();
    if (!res) {
        qDebug() << "Error deleting client:" << query.lastError().text();
    }
    return res;
}

// Function to search for a client by ID
QSqlQueryModel* Client::search(int clientId) {
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    query.prepare("SELECT * FROM MAYSSEM.CLIENTS WHERE ID_C = :id");
    query.bindValue(":id", clientId);

    if (query.exec()) {
        model->setQuery(std::move(query));  // Use std::move to avoid copying
        if (model->rowCount() == 0) {
            // If no rows are returned, display a warning
            QMessageBox::warning(nullptr, "No Result", "No client found with the entered ID.");
        }
    } else {
        QMessageBox::critical(nullptr, "Database Error", "Failed to execute query.");
    }

    return model;
}
