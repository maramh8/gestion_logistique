#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QRadioButton>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile styleFile( "C:/Users/maram/OneDrive/bureau/gestion_logistique/style.qss.txt" );
    styleFile.open( QFile::ReadOnly );


    //Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    a.setStyleSheet( style );


    Connection c;
    bool test=c.createconnect();
    MainWindow w;

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
