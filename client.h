#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

class Client {
public:
    Client();
    Client(int id,  QString nom,  QString prenom,  QString adresse,
            QString ville,  QString telephone,  QString email,
            QDate dateCreation = QDate::currentDate());
    Client( QString nom,  QString prenom,  QString adresse,
            QString ville,  QString telephone,  QString email,
            QDate dateCreation = QDate::currentDate());

    // Getters
    int getId() ;
    QString getNom() ;
    QString getPrenom() ;
    QString getAdresse() ;
    QString getVille() ;
    QString getTelephone() ;
    QString getEmail() ;
    QDate getDateCreation() ;

    // CRUD operations
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
   static QSqlQueryModel* rechercher(QString nom, QString prenom);
   static  QSqlQueryModel* rechercherParDate(QDate dateCreation);
   QBarSeries* getClientsByCity();
   QSqlQueryModel* trierClients(const QString& critere, const QString& ordre);


private:
    int id;
    QString nom;
    QString prenom;
    QString adresse;
    QString ville;
    QString telephone;
    QString email;
    QDate dateCreation;
};

#endif // CLIENT_H
