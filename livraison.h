#ifndef LIVRAISON_H
#define LIVRAISON_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlError>

class Livraison {
private:
    int ID_LIV;                // ID de la livraison
    QString NOM_CLIENT;        // Nom du client
    QString PRENOM_CLIENT;     // Prénom du client
    QString NUM_CLIENT;        // Numéro de téléphone du client
    QString ADR_LIV;           // Adresse de livraison
    QString ETAT_LIV;          // État de la livraison (livré, en attente, etc.)
    float PRIX_LIV;            // Prix de la livraison
    QDate DATE_LIV;            // Date de la livraison

public:
    // Constructeurs
    Livraison();
    Livraison(int idLiv, const QString& prenomClient, const QString& nomClient, const QString& numClient,
              const QString& adresseLiv, float prixLiv, const QString& etatLiv, const QDate& dateLiv);

    // Getters
    int getId() const { return ID_LIV; }
    QDate getDate() const { return DATE_LIV; }
    QString getAdresse() const { return ADR_LIV; }
    QString getEtat() const { return ETAT_LIV; }
    QString getNomClient() const { return NOM_CLIENT; }
    QString getPrenomClient() const { return PRENOM_CLIENT; }
    QString getNumClient() const { return NUM_CLIENT; }
    float getPrix() const { return PRIX_LIV; }

    // Setters
    void setId(int newId) { ID_LIV = newId; }
    void setDate(const QDate& newDate) { DATE_LIV = newDate; }
    void setAdresse(const QString& newAdresse) { ADR_LIV = newAdresse; }
    void setEtat(const QString& newEtat) { ETAT_LIV = newEtat; }
    void setNomClient(const QString& newNomClient) { NOM_CLIENT = newNomClient; }
    void setPrenomClient(const QString& newPrenomClient) { PRENOM_CLIENT = newPrenomClient; }
    void setNumClient(const QString& newNumClient) { NUM_CLIENT = newNumClient; }
    void setPrix(float newPrix) { PRIX_LIV = newPrix; }

    // CRUD Functions
    bool ajouter();
    bool supprimer(int id);   // Supprime par ID
    bool modifier(int id);    // Modifie la livraison par ID
    QSqlQueryModel* afficher(); // Affiche les enregistrements

    // Fonction supplémentaire pour vérifier l'unicité de l'ID
    bool idExists(int id);     // Vérifie si l'ID existe déjà
    void enregistrerAction(const QString &actionDescription); // Pour l'historique
};

#endif // LIVRAISON_H
