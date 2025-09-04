#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QLabel>
#include <QPushButton>






QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajoutC_clicked();
    void on_pushButton_modifC_clicked();
    void on_pushButton_suppC_clicked();
    void on_tableView_client_doubleClicked(const QModelIndex &index);


    void on_lineEdit_rechC_textChanged(const QString &arg1);

    void on_dateEdit_search_dateChanged(const QDate &date);

    void on_pushButton_pdfC_clicked();
    void generatePDF( QString filePath);
    void displayClientsByCity();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_ajoutCm_clicked();

    void on_pushButton_modifCm_clicked();

    void on_pushButton_suppCm_clicked();

    void on_tableView_commande_doubleClicked(const QModelIndex &index);
    void chargerClientsDansComboBox();

    void envoyerEmailCommandeComplete(int idClient, int idCommande);



    void on_pushButton_tricommande_clicked();

    void on_pushButton_triclient_clicked();

    void on_lineEdit_rechCom_textChanged(const QString &arg1);



    void on_pushButton_pdfCm_clicked();
    void generatePDFCm( QString filePath);
    void displayCommandesByEtat();







    void on_dateEdit_search_cm_dateChanged(const QDate &date);



private:
    Ui::MainWindow *ui;


    QImage currentQrImage;

};
#endif // MAINWINDOW_H
