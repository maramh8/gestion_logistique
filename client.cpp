// client.cpp

#include "client.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QErrorMessage>
#include <QSqlError>

Client::Client() {}

Client::Client(int id,  QString nom,  QString prenom,  QString adresse,
                QString ville,  QString telephone,  QString email,
                QDate dateCreation)
    : id(id),
    nom(nom),
    prenom(prenom),
    adresse(adresse),
    ville(ville),
    telephone(telephone),
    email(email),
    dateCreation(dateCreation) {}

Client::Client( QString nom,  QString prenom,  QString adresse,
                QString ville,  QString telephone,  QString email,
                QDate dateCreation)
    : nom(nom),
    prenom(prenom),
    adresse(adresse),
    ville(ville),
    telephone(telephone),
    email(email),
    dateCreation(dateCreation) {}

// Getters
int Client::getId()  { return id; }
QString Client::getNom()  { return nom; }
QString Client::getPrenom()  { return prenom; }
QString Client::getAdresse()  { return adresse; }
QString Client::getVille()  { return ville; }
QString Client::getTelephone()  { return telephone; }
QString Client::getEmail()  { return email; }
QDate Client::getDateCreation()  { return dateCreation; }

// Ajouter
bool Client::ajouter() {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO CLIENT (NOM, PRENOM, ADRESSE, VILLE, TELEPHONE, EMAIL, DATE_CREATION) "
        "VALUES (:nom, :prenom, :adresse, :ville, :telephone, :email, :dc)"
        );

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":ville", ville);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    // bind the selected date (from your object)
    query.bindValue(":dc", dateCreation);   // QDate → Oracle DATE via ODBC is fine

    return query.exec();
}
// Afficher
QSqlQueryModel* Client::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT ORDER BY ID_CLIENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_CREATION"));

    return model;
}

// Supprimer
bool Client::supprimer(int id) {
    qDebug() << id;
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);
    return query.exec();
}

// Modifier
bool Client::modifier(int id) {
    qDebug() << id;
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, ADRESSE = :adresse, "
                  "VILLE = :ville, TELEPHONE = :telephone, EMAIL = :email "
                  "WHERE ID_CLIENT = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":ville", ville);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    return query.exec();
}


QSqlQueryModel* Client::rechercher(QString nom, QString prenom ) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the SQL query with optional filters
    query.prepare(
        "SELECT * FROM client "
        "WHERE nom LIKE :nom "
        "OR prenom LIKE :prenom "

        );

    query.bindValue(":nom", "%" + nom + "%");
    query.bindValue(":prenom", "%" + prenom + "%");


    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Failed to execute search query:" << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* Client::rechercherParDate(QDate dateCreation) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Oracle-compatible query: Truncate time and convert string to DATE
    query.prepare(
        "SELECT * FROM client "
        "WHERE TRUNC(date_creation) = TO_DATE(:date_creation, 'YYYY-MM-DD')"
        );

    QString dateStr = dateCreation.toString("yyyy-MM-dd");
    query.bindValue(":date_creation", dateStr);

    qDebug() << "Searching for date:" << dateStr;

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        qDebug() << "Query executed:" << query.executedQuery();
        qDebug() << "Bound value:" << query.boundValue(":date_creation").toString();
    } else if (query.size() == 0) {
        qDebug() << "No results found for date:" << dateStr;
    } else {
        qDebug() << "Query successful, results found:" << query.size();
    }

    model->setQuery(query);
    return model;
}

QBarSeries* Client::getClientsByCity() {
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Nombre de clients");

    // Assuming you have a database connection
    QSqlQuery query;
    query.prepare("SELECT ville, COUNT(*) as count FROM client GROUP BY ville ORDER BY count DESC");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError();
        delete series;
        return nullptr;
    }

    QStringList categories;

    while (query.next()) {
        QString ville = query.value("ville").toString();
        int count = query.value("count").toInt();

        categories << ville;
        *set << count;
    }

    // Add the categories to the series
    series->append(set);



    return series;
}
QSqlQueryModel* Client::trierClients(const QString& critere, const QString& ordre)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Associer le critère au champ SQL
    QString colonne;
    if (critere == "nom") {
        colonne = "NOM";
    } else if (critere == "prenom") {
        colonne = "PRENOM";
    } else if (critere == "datecreation") {
        colonne = "DATE_CREATION";
    } else {
        colonne = "ID_CLIENT"; // défaut
    }

    // Ordre de tri
    QString ordreSQL = (ordre == "descendant") ? "DESC" : "ASC";

    // Requête SQL
    QString queryString = QString(
                              "SELECT ID_CLIENT, NOM, PRENOM, ADRESSE, VILLE, TELEPHONE, EMAIL, DATE_CREATION "
                              "FROM CLIENT "
                              "ORDER BY %1 %2"
                              ).arg(colonne, ordreSQL);

    model->setQuery(queryString);

    return model;
}
