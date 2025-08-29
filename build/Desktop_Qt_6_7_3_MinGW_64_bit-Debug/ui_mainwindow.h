/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTabWidget *tabWidget;
    QWidget *tab;
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
    QTableView *tableView_client;
    QPushButton *pushButton_suppC;
    QWidget *tab_2;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1315, 994);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(60, 40, 1231, 861));
        page = new QWidget();
        page->setObjectName("page");
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(40, 30, 1161, 791));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 331, 601));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(180, 80, 113, 26));
        lineEdit_ville = new QLineEdit(groupBox);
        lineEdit_ville->setObjectName("lineEdit_ville");
        lineEdit_ville->setGeometry(QRect(180, 280, 113, 26));
        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(180, 140, 113, 26));
        lineEdit_adresse = new QLineEdit(groupBox);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(180, 210, 113, 26));
        lineEdit_tel = new QLineEdit(groupBox);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(180, 340, 113, 26));
        lineEdit_email = new QLineEdit(groupBox);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(180, 400, 113, 26));
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(180, 470, 110, 26));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 80, 63, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(12, 470, 111, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 63, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 210, 63, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 290, 63, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 340, 81, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(50, 410, 63, 20));
        pushButton_ajoutC = new QPushButton(groupBox);
        pushButton_ajoutC->setObjectName("pushButton_ajoutC");
        pushButton_ajoutC->setGeometry(QRect(100, 540, 93, 29));
        pushButton_modifC = new QPushButton(groupBox);
        pushButton_modifC->setObjectName("pushButton_modifC");
        pushButton_modifC->setGeometry(QRect(210, 540, 93, 29));
        tableView_client = new QTableView(tab);
        tableView_client->setObjectName("tableView_client");
        tableView_client->setGeometry(QRect(410, 120, 701, 361));
        pushButton_suppC = new QPushButton(tab);
        pushButton_suppC->setObjectName("pushButton_suppC");
        pushButton_suppC->setGeometry(QRect(420, 500, 93, 29));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1315, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
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
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
