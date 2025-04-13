#include "livraison.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

Livraison::Livraison() : ID_LIV(0), PRIX_LIV(0.0) {}

Livraison::Livraison(int idLiv, const QString& prenomClient, const QString& nomClient,
                     const QString& numClient, const QString& adresseLiv,
                     float prixLiv, const QString& etatLiv, const QDate& dateLiv)
    : ID_LIV(idLiv),
    NOM_CLIENT(nomClient),
    PRENOM_CLIENT(prenomClient),
    NUM_CLIENT(numClient),
    ADR_LIV(adresseLiv),
    ETAT_LIV(etatLiv),
    PRIX_LIV(prixLiv), // Mettez PRIX_LIV ici après le type dessus
    DATE_LIV(dateLiv) {}

bool Livraison::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO MAYSSEM.LIVRAISON (ID_LIV, DATE_LIV, ADR_LIV, ETAT_LIV, "
                  "NOM_CLIENT, PRENOM_CLIENT, NUM_CLIENT, PRIX_LIV) "
                  "VALUES (:idLiv, :dateLiv, :adresseLiv, :etatLiv, "
                  ":nomClient, :prenomClient, :numClient, :prixLiv)");

    query.bindValue(":idLiv", ID_LIV);
    query.bindValue(":dateLiv", DATE_LIV);
    query.bindValue(":adresseLiv", ADR_LIV);
    query.bindValue(":etatLiv", ETAT_LIV);
    query.bindValue(":nomClient", NOM_CLIENT);
    query.bindValue(":prenomClient", PRENOM_CLIENT);
    query.bindValue(":numClient", NUM_CLIENT);
    query.bindValue(":prixLiv", PRIX_LIV);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de l'ajout:" << query.lastError().text();
        return false;
    }

    // Enregistre l'action dans l'historique
    enregistrerAction("Ajout de la livraison avec ID: " + QString::number(ID_LIV)); return true;
    return true;
}

bool Livraison::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM MAYSSEM.LIVRAISON WHERE ID_LIV = :id");
    query.bindValue(":id", id); // Utilisation de l'ID passé en paramètre

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la suppression:" << query.lastError().text();
        return false;
    }

    // Enregistre l'action dans l'historique avec l'ID passé
    enregistrerAction("Suppression de la livraison avec ID: " + QString::number(id));
    return true;
}

bool Livraison::modifier(int oldId) {
    QSqlQuery query;

    // Mettez à jour l'ID et les autres champs directement
    query.prepare("UPDATE MAYSSEM.LIVRAISON SET "
                  "ID_LIV = :newId, "
                  "DATE_LIV = :dateLiv, "
                  "ADR_LIV = :adresseLiv, "
                  "ETAT_LIV = :etatLiv, "
                  "NOM_CLIENT = :nomClient, "
                  "PRENOM_CLIENT = :prenomClient, "
                  "NUM_CLIENT = :numClient, "
                  "PRIX_LIV = :prixLiv "
                  "WHERE ID_LIV = :oldId");
    query.bindValue(":newId", ID_LIV); // Nouvel ID
    query.bindValue(":dateLiv", DATE_LIV);
    query.bindValue(":adresseLiv", ADR_LIV);
    query.bindValue(":etatLiv", ETAT_LIV);
    query.bindValue(":nomClient", NOM_CLIENT);
    query.bindValue(":prenomClient", PRENOM_CLIENT);
    query.bindValue(":numClient", NUM_CLIENT);
    query.bindValue(":prixLiv", PRIX_LIV);
    query.bindValue(":oldId", oldId); // Ancien ID

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la modification:" << query.lastError().text();
        return false;
    }

    enregistrerAction("Modification de la livraison avec ID: " + QString::number(ID_LIV));
    return true;
}


QSqlQueryModel* Livraison::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Supprimer le tri par date
    query.prepare("SELECT ID_LIV, PRENOM_CLIENT, NOM_CLIENT, NUM_CLIENT, ADR_LIV, PRIX_LIV, ETAT_LIV, DATE_LIV FROM MAYSSEM.LIVRAISON");
    if (query.exec()) {
        model->setQuery(std::move(query));
    } else {
        qDebug() << "Erreur SQL lors de l'affichage:" << query.lastError().text();
    }

    return model;
}

bool Livraison::idExists(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM MAYSSEM.LIVRAISON WHERE ID_LIV = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }

    query.next();
    return query.value(0).toInt() > 0; // Retourne vrai si l'ID existe
}

void Livraison::enregistrerAction(const QString &actionDescription) {
    QFile file("C:/Users/merie/Documents/GS_Employees_versionfinale/GS_Employees_Clients_Livraisons/historique.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - "
            << actionDescription << "\n";
        file.close();
        qDebug() << "Écriture réussie: " << actionDescription; // Confirmation de l'écriture
    } else {
        qDebug() << "Erreur lors de l'ouverture du fichier pour écrire:" << file.errorString();
    }
}

