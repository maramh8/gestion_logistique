/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_pdfC;
    QTableView *tableView_client;
    QGroupBox *groupBox_5;
    QComboBox *comboBox_critere_client;
    QComboBox *comboBox_order_client;
    QPushButton *pushButton_triclient;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_ville;
    QLineEdit *lineEdit_prenom;
    QLineEdit *lineEdit_adresse;
    QLineEdit *lineEdit_tel;
    QLineEdit *lineEdit_email;
    QDateEdit *dateEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_ajoutC;
    QPushButton *pushButton_modifC;
    QPushButton *pushButton_suppC;
    QFrame *frame_client;
    QGroupBox *groupBox_6;
    QDateEdit *dateEdit_search;
    QLineEdit *lineEdit_rechC;
    QLabel *label_13;
    QWidget *page_2;
    QFrame *frame_commande;
    QGroupBox *groupBox_4;
    QComboBox *comboBox_critere;
    QComboBox *comboBox_order;
    QPushButton *pushButton_tricommande;
    QPushButton *pushButton_suppCm;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_rechCom;
    QDateEdit *dateEdit_search_cm;
    QLabel *label_14;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_montant;
    QDateEdit *dateEdit_Commande;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButton_modifCm;
    QComboBox *comboBox_client;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_idCommande;
    QComboBox *comboBox_etat;
    QPushButton *pushButton_ajoutCm;
    QTableView *tableView_commande;
    QPushButton *pushButton_pdfCm;
    QLabel *label_qrcode;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1751, 1109);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(150, 10, 1341, 871));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName("page");
        pushButton_pdfC = new QPushButton(page);
        pushButton_pdfC->setObjectName("pushButton_pdfC");
        pushButton_pdfC->setGeometry(QRect(1010, 440, 93, 29));
        tableView_client = new QTableView(page);
        tableView_client->setObjectName("tableView_client");
        tableView_client->setGeometry(QRect(520, 160, 571, 271));
        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(1110, 180, 151, 191));
        comboBox_critere_client = new QComboBox(groupBox_5);
        comboBox_critere_client->addItem(QString());
        comboBox_critere_client->addItem(QString());
        comboBox_critere_client->addItem(QString());
        comboBox_critere_client->setObjectName("comboBox_critere_client");
        comboBox_critere_client->setGeometry(QRect(10, 35, 111, 31));
        comboBox_order_client = new QComboBox(groupBox_5);
        comboBox_order_client->addItem(QString());
        comboBox_order_client->addItem(QString());
        comboBox_order_client->setObjectName("comboBox_order_client");
        comboBox_order_client->setGeometry(QRect(10, 80, 111, 31));
        pushButton_triclient = new QPushButton(groupBox_5);
        pushButton_triclient->setObjectName("pushButton_triclient");
        pushButton_triclient->setGeometry(QRect(30, 140, 93, 29));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 30, 391, 641));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(180, 80, 171, 41));
        lineEdit_ville = new QLineEdit(groupBox);
        lineEdit_ville->setObjectName("lineEdit_ville");
        lineEdit_ville->setGeometry(QRect(180, 280, 171, 41));
        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(180, 140, 171, 41));
        lineEdit_adresse = new QLineEdit(groupBox);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(180, 210, 171, 41));
        lineEdit_tel = new QLineEdit(groupBox);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(180, 340, 171, 41));
        lineEdit_email = new QLineEdit(groupBox);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(180, 400, 171, 41));
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(180, 480, 171, 41));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 80, 121, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 480, 121, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 121, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 210, 121, 31));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 290, 121, 31));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 340, 121, 31));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(50, 410, 121, 31));
        pushButton_ajoutC = new QPushButton(groupBox);
        pushButton_ajoutC->setObjectName("pushButton_ajoutC");
        pushButton_ajoutC->setGeometry(QRect(60, 560, 121, 41));
        pushButton_modifC = new QPushButton(groupBox);
        pushButton_modifC->setObjectName("pushButton_modifC");
        pushButton_modifC->setGeometry(QRect(220, 560, 131, 41));
        pushButton_suppC = new QPushButton(page);
        pushButton_suppC->setObjectName("pushButton_suppC");
        pushButton_suppC->setGeometry(QRect(520, 440, 93, 31));
        frame_client = new QFrame(page);
        frame_client->setObjectName("frame_client");
        frame_client->setGeometry(QRect(520, 490, 781, 281));
        frame_client->setFrameShape(QFrame::StyledPanel);
        frame_client->setFrameShadow(QFrame::Raised);
        groupBox_6 = new QGroupBox(page);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(520, 70, 571, 80));
        dateEdit_search = new QDateEdit(groupBox_6);
        dateEdit_search->setObjectName("dateEdit_search");
        dateEdit_search->setGeometry(QRect(330, 30, 171, 41));
        lineEdit_rechC = new QLineEdit(groupBox_6);
        lineEdit_rechC->setObjectName("lineEdit_rechC");
        lineEdit_rechC->setGeometry(QRect(10, 30, 191, 41));
        label_13 = new QLabel(page);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(0, 630, 471, 241));
        label_13->setStyleSheet(QString::fromUtf8("image: url(:/images/images/livraison.png);\n"
"border: none;"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        frame_commande = new QFrame(page_2);
        frame_commande->setObjectName("frame_commande");
        frame_commande->setGeometry(QRect(460, 530, 661, 271));
        frame_commande->setFrameShape(QFrame::StyledPanel);
        frame_commande->setFrameShadow(QFrame::Raised);
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(1100, 180, 141, 191));
        comboBox_critere = new QComboBox(groupBox_4);
        comboBox_critere->addItem(QString());
        comboBox_critere->addItem(QString());
        comboBox_critere->addItem(QString());
        comboBox_critere->setObjectName("comboBox_critere");
        comboBox_critere->setGeometry(QRect(10, 35, 111, 31));
        comboBox_order = new QComboBox(groupBox_4);
        comboBox_order->addItem(QString());
        comboBox_order->addItem(QString());
        comboBox_order->setObjectName("comboBox_order");
        comboBox_order->setGeometry(QRect(10, 80, 111, 31));
        pushButton_tricommande = new QPushButton(groupBox_4);
        pushButton_tricommande->setObjectName("pushButton_tricommande");
        pushButton_tricommande->setGeometry(QRect(30, 140, 93, 29));
        pushButton_suppCm = new QPushButton(page_2);
        pushButton_suppCm->setObjectName("pushButton_suppCm");
        pushButton_suppCm->setGeometry(QRect(470, 430, 61, 41));
        pushButton_suppCm->setAutoFillBackground(false);
        pushButton_suppCm->setStyleSheet(QString::fromUtf8("image: url(:/images/images/tabler--trash.png);"));
        pushButton_suppCm->setCheckable(false);
        pushButton_suppCm->setFlat(false);
        groupBox_3 = new QGroupBox(page_2);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(480, 50, 601, 81));
        lineEdit_rechCom = new QLineEdit(groupBox_3);
        lineEdit_rechCom->setObjectName("lineEdit_rechCom");
        lineEdit_rechCom->setGeometry(QRect(70, 30, 191, 41));
        dateEdit_search_cm = new QDateEdit(groupBox_3);
        dateEdit_search_cm->setObjectName("dateEdit_search_cm");
        dateEdit_search_cm->setGeometry(QRect(410, 30, 171, 41));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(0, 20, 63, 51));
        label_14->setStyleSheet(QString::fromUtf8("image: url(:/images/images/tabler--device-ipad-horizontal-search.png);"));
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 20, 411, 561));
        lineEdit_montant = new QLineEdit(groupBox_2);
        lineEdit_montant->setObjectName("lineEdit_montant");
        lineEdit_montant->setGeometry(QRect(220, 300, 171, 41));
        dateEdit_Commande = new QDateEdit(groupBox_2);
        dateEdit_Commande->setObjectName("dateEdit_Commande");
        dateEdit_Commande->setGeometry(QRect(220, 160, 171, 41));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(50, 230, 112, 31));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 170, 112, 31));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(50, 310, 112, 31));
        pushButton_modifCm = new QPushButton(groupBox_2);
        pushButton_modifCm->setObjectName("pushButton_modifCm");
        pushButton_modifCm->setGeometry(QRect(230, 480, 111, 41));
        comboBox_client = new QComboBox(groupBox_2);
        comboBox_client->setObjectName("comboBox_client");
        comboBox_client->setGeometry(QRect(220, 370, 171, 41));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(50, 380, 112, 31));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 100, 112, 31));
        lineEdit_idCommande = new QLineEdit(groupBox_2);
        lineEdit_idCommande->setObjectName("lineEdit_idCommande");
        lineEdit_idCommande->setGeometry(QRect(220, 90, 171, 41));
        comboBox_etat = new QComboBox(groupBox_2);
        comboBox_etat->addItem(QString());
        comboBox_etat->addItem(QString());
        comboBox_etat->addItem(QString());
        comboBox_etat->setObjectName("comboBox_etat");
        comboBox_etat->setGeometry(QRect(220, 230, 161, 41));
        pushButton_ajoutCm = new QPushButton(groupBox_2);
        pushButton_ajoutCm->setObjectName("pushButton_ajoutCm");
        pushButton_ajoutCm->setGeometry(QRect(50, 480, 111, 41));
        QFont font;
        font.setPointSize(13);
        pushButton_ajoutCm->setFont(font);
        pushButton_ajoutCm->setStyleSheet(QString::fromUtf8(""));
        tableView_commande = new QTableView(page_2);
        tableView_commande->setObjectName("tableView_commande");
        tableView_commande->setGeometry(QRect(470, 140, 611, 281));
        pushButton_pdfCm = new QPushButton(page_2);
        pushButton_pdfCm->setObjectName("pushButton_pdfCm");
        pushButton_pdfCm->setGeometry(QRect(990, 430, 91, 41));
        pushButton_pdfCm->setStyleSheet(QString::fromUtf8("image: url(:/images/images/tabler--file-type-pdf.png);"));
        label_qrcode = new QLabel(page_2);
        label_qrcode->setObjectName("label_qrcode");
        label_qrcode->setGeometry(QRect(60, 590, 331, 251));
        stackedWidget->addWidget(page_2);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 240, 131, 51));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 150, 131, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1751, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_pdfC->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Tri", nullptr));
        comboBox_critere_client->setItemText(0, QCoreApplication::translate("MainWindow", "nom", nullptr));
        comboBox_critere_client->setItemText(1, QCoreApplication::translate("MainWindow", "prenom", nullptr));
        comboBox_critere_client->setItemText(2, QCoreApplication::translate("MainWindow", "datecreation", nullptr));

        comboBox_order_client->setItemText(0, QCoreApplication::translate("MainWindow", "ascendant", nullptr));
        comboBox_order_client->setItemText(1, QCoreApplication::translate("MainWindow", "descendant", nullptr));

        pushButton_triclient->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "DateCreation", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Ville", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        pushButton_ajoutC->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modifC->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_suppC->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "rechercher client ", nullptr));
        label_13->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Tri", nullptr));
        comboBox_critere->setItemText(0, QCoreApplication::translate("MainWindow", "etat", nullptr));
        comboBox_critere->setItemText(1, QCoreApplication::translate("MainWindow", "montant", nullptr));
        comboBox_critere->setItemText(2, QCoreApplication::translate("MainWindow", "date_commande", nullptr));

        comboBox_order->setItemText(0, QCoreApplication::translate("MainWindow", "ascendant", nullptr));
        comboBox_order->setItemText(1, QCoreApplication::translate("MainWindow", "descendant", nullptr));

        pushButton_tricommande->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        pushButton_suppCm->setText(QString());
        groupBox_3->setTitle(QString());
        label_14->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "etat", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Date commande", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        pushButton_modifCm->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "id_commande", nullptr));
        comboBox_etat->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboBox_etat->setItemText(1, QCoreApplication::translate("MainWindow", "Complete", nullptr));
        comboBox_etat->setItemText(2, QCoreApplication::translate("MainWindow", "Annule", nullptr));

        pushButton_ajoutCm->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_pdfCm->setText(QString());
        label_qrcode->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Commande", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
