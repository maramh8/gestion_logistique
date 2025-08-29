#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Commande::Commande() {}

Commande::Commande(int id, int clientId, double montant, QString statut, QDate dateCreation)
    : id(id), clientId(clientId), montant(montant), statut(statut), dateCreation(dateCreation) {}

Commande::Commande(int clientId, double montant, QString statut, QDate dateCreation)
    : clientId(clientId), montant(montant), statut(statut), dateCreation(dateCreation) {}

// Getters
int     Commande::getId()            { return id; }
int     Commande::getClientId()      { return clientId; }
double  Commande::getMontant()       { return montant; }
QString Commande::getStatut()        { return statut; }
QDate   Commande::getDateCreation()  { return dateCreation; }

// Ajouter (OK per your message)
bool Commande::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDE (ID_CLIENT, MONTANT, ETAT, DATE_COMMANDE) "
                  "VALUES (:client_id, :montant, :statut, TO_DATE(:date_creation, 'YYYY-MM-DD'))");
    query.bindValue(":client_id",     clientId);
    query.bindValue(":montant",       montant);
    query.bindValue(":statut",        statut);
    query.bindValue(":date_creation", dateCreation.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur ajout commande:" << query.lastError().text();
        return false;
    }
    return true;
}

// Afficher
QSqlQueryModel* Commande::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT c.ID_COMMANDE, c.DATE_COMMANDE, c.ETAT, c.MONTANT, "
        "cl.ID_CLIENT, "
        "cl.NOM || ' ' || cl.PRENOM AS CLIENT "
        "FROM COMMANDE c "
        "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
        "ORDER BY c.DATE_COMMANDE DESC"
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_COMMANDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_CLIENT")); // hidden later
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CLIENT"));

    return model;
}


// Supprimer
bool Commande::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDE WHERE ID_COMMANDE = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur suppression commande:" << query.lastError().text();
        return false;
    }
    return true;
}

// Modifier
bool Commande::modifier(int id) {
    QSqlQuery query;
    query.prepare(
        "UPDATE COMMANDE "
        "   SET ID_CLIENT     = :id_client, "
        "       MONTANT       = :montant, "
        "       ETAT          = :statut, "
        "       DATE_COMMANDE = TO_DATE(:date_commande, 'YYYY-MM-DD') "
        " WHERE ID_COMMANDE   = :id"
        );
    query.bindValue(":id_client",     clientId);
    query.bindValue(":montant",       montant);
    query.bindValue(":statut",        statut);
    query.bindValue(":date_commande", dateCreation.toString("yyyy-MM-dd"));
    query.bindValue(":id",            id);

    if (!query.exec()) {
        qDebug() << "Erreur modification commande:" << query.lastError().text();
        return false;
    }
    return true;
}

// Recherche par client (ID_CLIENT)
QSqlQueryModel* Commande::rechercherParClientId(int clientId) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(
        "SELECT ID_COMMANDE, DATE_COMMANDE, ETAT, MONTANT, ID_CLIENT "
        "FROM COMMANDE "
        "WHERE ID_CLIENT = :id_client "
        "ORDER BY DATE_COMMANDE DESC"
        );
    query.bindValue(":id_client", clientId);

    if (!query.exec()) {
        qDebug() << "Erreur recherche commande (client):" << query.lastError().text();
        delete model; return nullptr;
    }
    model->setQuery(query);
    return model;
}

// Recherche par date (jour exact, Oracle DATE inclut l'heure → TRUNC)
QSqlQueryModel* Commande::rechercherParDate(QDate dateCreation) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(
        "SELECT ID_COMMANDE, DATE_COMMANDE, ETAT, MONTANT, ID_CLIENT "
        "FROM COMMANDE "
        "WHERE TRUNC(DATE_COMMANDE) = TO_DATE(:d, 'YYYY-MM-DD') "
        "ORDER BY DATE_COMMANDE DESC"
        );
    query.bindValue(":d", dateCreation.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur recherche commande (date):" << query.lastError().text();
        delete model; return nullptr;
    }
    model->setQuery(query);
    return model;
}

// Statistiques commandes par jour (Oracle)
QBarSeries* Commande::getCommandesByEtat() {
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Nombre de commandes");

    QSqlQuery query;
    query.prepare("SELECT ETAT, COUNT(*) as count "
                  "FROM commande "
                  "GROUP BY ETAT "
                  "ORDER BY count DESC");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError();
        delete series;
        return nullptr;
    }

    QStringList categories;

    while (query.next()) {
        QString etat = query.value("ETAT").toString();
        int count = query.value("count").toInt();

        categories << etat;
        *set << count;
    }

    series->append(set);

    // Store categories in chart later
    series->setName("Commandes");
    return series;
}




QString Commande::getClientEmail(int idClient) {
    QSqlQuery query;
    query.prepare("SELECT email FROM client WHERE id_client = :id_client");
    query.bindValue(":id", idClient);

    if (query.exec() && query.next()) {
        return query.value("email").toString();
    } else {
        qDebug() << "Error retrieving email:" << query.lastError().text();
        return QString();
    }
}

// commande.cpp - Add this method to your Commande class

QSqlQueryModel* Commande::trierCommandes(const QString& critere, const QString& ordre)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Map criteria to SQL columns
    QString colonne;
    if (critere == "etat") {
        colonne = "ETAT";
    } else if (critere == "montant") {
        colonne = "MONTANT";
    } else if (critere == "date_commande") {
        colonne = "DATE_COMMANDE";
    } else {
        colonne = "ID_COMMANDE"; // default
    }

    // Map order
    QString ordreSQL = (ordre == "descendant") ? "DESC" : "ASC";

    // SQL Query
    QString queryString = QString(
                              "SELECT ID_COMMANDE, DATE_COMMANDE, ETAT, MONTANT, ID_CLIENT "
                              "FROM COMMANDE "
                              "ORDER BY %1 %2"
                              ).arg(colonne, ordreSQL);

    model->setQuery(queryString);

    return model;
}

// Option 1: Search by text only (recommended for text input) - Oracle Compatible
QSqlQueryModel* Commande::rechercher(QString searchText) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Search in both etat and montant (converted to string using Oracle syntax)
    query.prepare(
        "SELECT * FROM commande "
        "WHERE UPPER(etat) LIKE UPPER(:searchText) "
        "OR TO_CHAR(montant) LIKE :searchText"
        );
    query.bindValue(":searchText", "%" + searchText + "%");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Failed to execute search query:" << query.lastError().text();
    }
    return model;
}
