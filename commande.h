#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

class Commande {
public:
    Commande();
    Commande(int id, int clientId, double montant, QString statut, QDate dateCreation = QDate::currentDate());
    Commande(int clientId, double montant, QString statut, QDate dateCreation = QDate::currentDate());

    // Getters
    int getId();
    int getClientId();
    double getMontant();
    QString getStatut();
    QDate getDateCreation();

    // CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool modifier(int id);

    // Search
    static QSqlQueryModel* rechercherParClientId(int clientId);
    static QSqlQueryModel* rechercherParDate(QDate dateCreation);
    static QSqlQuery listerClientsAvecCommandes();
    QSqlQueryModel* trierCommandes(const QString& critere, const QString& ordre);

    // Stats
    QBarSeries* getCommandesParJour();
    QString getClientEmail(int idClient);
   static QSqlQueryModel* rechercher(QString searchText);
    QBarSeries* getCommandesByEtat();

private:
    int id;
    int clientId;
    double montant;
    QString statut;
    QDate dateCreation;
};

#endif // COMMANDE_H
