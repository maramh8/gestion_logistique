/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_pushButton_ajoutC_clicked",
    "",
    "on_pushButton_modifC_clicked",
    "on_pushButton_suppC_clicked",
    "on_tableView_client_doubleClicked",
    "QModelIndex",
    "index",
    "on_lineEdit_rechC_textChanged",
    "arg1",
    "on_dateEdit_search_dateChanged",
    "date",
    "on_pushButton_pdfC_clicked",
    "generatePDF",
    "filePath",
    "displayClientsByCity",
    "on_pushButton_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_ajoutCm_clicked",
    "on_pushButton_modifCm_clicked",
    "on_pushButton_suppCm_clicked",
    "on_tableView_commande_doubleClicked",
    "chargerClientsDansComboBox",
    "envoyerEmailCommandeComplete",
    "idClient",
    "idCommande",
    "on_pushButton_tricommande_clicked",
    "on_pushButton_triclient_clicked",
    "on_lineEdit_rechCom_textChanged",
    "on_pushButton_pdfCm_clicked",
    "generatePDFCm",
    "displayCommandesByEtat",
    "on_dateEdit_search_cm_dateChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[66];
    char stringdata0[11];
    char stringdata1[29];
    char stringdata2[1];
    char stringdata3[29];
    char stringdata4[28];
    char stringdata5[34];
    char stringdata6[12];
    char stringdata7[6];
    char stringdata8[30];
    char stringdata9[5];
    char stringdata10[31];
    char stringdata11[5];
    char stringdata12[27];
    char stringdata13[12];
    char stringdata14[9];
    char stringdata15[21];
    char stringdata16[22];
    char stringdata17[24];
    char stringdata18[30];
    char stringdata19[30];
    char stringdata20[29];
    char stringdata21[36];
    char stringdata22[27];
    char stringdata23[29];
    char stringdata24[9];
    char stringdata25[11];
    char stringdata26[34];
    char stringdata27[32];
    char stringdata28[32];
    char stringdata29[28];
    char stringdata30[14];
    char stringdata31[23];
    char stringdata32[34];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 28),  // "on_pushButton_ajoutC_clicked"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 28),  // "on_pushButton_modifC_clicked"
        QT_MOC_LITERAL(70, 27),  // "on_pushButton_suppC_clicked"
        QT_MOC_LITERAL(98, 33),  // "on_tableView_client_doubleCli..."
        QT_MOC_LITERAL(132, 11),  // "QModelIndex"
        QT_MOC_LITERAL(144, 5),  // "index"
        QT_MOC_LITERAL(150, 29),  // "on_lineEdit_rechC_textChanged"
        QT_MOC_LITERAL(180, 4),  // "arg1"
        QT_MOC_LITERAL(185, 30),  // "on_dateEdit_search_dateChanged"
        QT_MOC_LITERAL(216, 4),  // "date"
        QT_MOC_LITERAL(221, 26),  // "on_pushButton_pdfC_clicked"
        QT_MOC_LITERAL(248, 11),  // "generatePDF"
        QT_MOC_LITERAL(260, 8),  // "filePath"
        QT_MOC_LITERAL(269, 20),  // "displayClientsByCity"
        QT_MOC_LITERAL(290, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(312, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(336, 29),  // "on_pushButton_ajoutCm_clicked"
        QT_MOC_LITERAL(366, 29),  // "on_pushButton_modifCm_clicked"
        QT_MOC_LITERAL(396, 28),  // "on_pushButton_suppCm_clicked"
        QT_MOC_LITERAL(425, 35),  // "on_tableView_commande_doubleC..."
        QT_MOC_LITERAL(461, 26),  // "chargerClientsDansComboBox"
        QT_MOC_LITERAL(488, 28),  // "envoyerEmailCommandeComplete"
        QT_MOC_LITERAL(517, 8),  // "idClient"
        QT_MOC_LITERAL(526, 10),  // "idCommande"
        QT_MOC_LITERAL(537, 33),  // "on_pushButton_tricommande_cli..."
        QT_MOC_LITERAL(571, 31),  // "on_pushButton_triclient_clicked"
        QT_MOC_LITERAL(603, 31),  // "on_lineEdit_rechCom_textChanged"
        QT_MOC_LITERAL(635, 27),  // "on_pushButton_pdfCm_clicked"
        QT_MOC_LITERAL(663, 13),  // "generatePDFCm"
        QT_MOC_LITERAL(677, 22),  // "displayCommandesByEtat"
        QT_MOC_LITERAL(700, 33)   // "on_dateEdit_search_cm_dateCha..."
    },
    "MainWindow",
    "on_pushButton_ajoutC_clicked",
    "",
    "on_pushButton_modifC_clicked",
    "on_pushButton_suppC_clicked",
    "on_tableView_client_doubleClicked",
    "QModelIndex",
    "index",
    "on_lineEdit_rechC_textChanged",
    "arg1",
    "on_dateEdit_search_dateChanged",
    "date",
    "on_pushButton_pdfC_clicked",
    "generatePDF",
    "filePath",
    "displayClientsByCity",
    "on_pushButton_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_ajoutCm_clicked",
    "on_pushButton_modifCm_clicked",
    "on_pushButton_suppCm_clicked",
    "on_tableView_commande_doubleClicked",
    "chargerClientsDansComboBox",
    "envoyerEmailCommandeComplete",
    "idClient",
    "idCommande",
    "on_pushButton_tricommande_clicked",
    "on_pushButton_triclient_clicked",
    "on_lineEdit_rechCom_textChanged",
    "on_pushButton_pdfCm_clicked",
    "generatePDFCm",
    "displayCommandesByEtat",
    "on_dateEdit_search_cm_dateChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  158,    2, 0x08,    1 /* Private */,
       3,    0,  159,    2, 0x08,    2 /* Private */,
       4,    0,  160,    2, 0x08,    3 /* Private */,
       5,    1,  161,    2, 0x08,    4 /* Private */,
       8,    1,  164,    2, 0x08,    6 /* Private */,
      10,    1,  167,    2, 0x08,    8 /* Private */,
      12,    0,  170,    2, 0x08,   10 /* Private */,
      13,    1,  171,    2, 0x08,   11 /* Private */,
      15,    0,  174,    2, 0x08,   13 /* Private */,
      16,    0,  175,    2, 0x08,   14 /* Private */,
      17,    0,  176,    2, 0x08,   15 /* Private */,
      18,    0,  177,    2, 0x08,   16 /* Private */,
      19,    0,  178,    2, 0x08,   17 /* Private */,
      20,    0,  179,    2, 0x08,   18 /* Private */,
      21,    1,  180,    2, 0x08,   19 /* Private */,
      22,    0,  183,    2, 0x08,   21 /* Private */,
      23,    2,  184,    2, 0x08,   22 /* Private */,
      26,    0,  189,    2, 0x08,   25 /* Private */,
      27,    0,  190,    2, 0x08,   26 /* Private */,
      28,    1,  191,    2, 0x08,   27 /* Private */,
      29,    0,  194,    2, 0x08,   29 /* Private */,
      30,    1,  195,    2, 0x08,   30 /* Private */,
      31,    0,  198,    2, 0x08,   32 /* Private */,
      32,    1,  199,    2, 0x08,   33 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QDate,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_pushButton_ajoutC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_modifC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_suppC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableView_client_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_lineEdit_rechC_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_dateEdit_search_dateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'on_pushButton_pdfC_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generatePDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'displayClientsByCity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_ajoutCm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_modifCm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_suppCm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableView_commande_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'chargerClientsDansComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'envoyerEmailCommandeComplete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_tricommande_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_triclient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_lineEdit_rechCom_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_pushButton_pdfCm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generatePDFCm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'displayCommandesByEtat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_dateEdit_search_cm_dateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_ajoutC_clicked(); break;
        case 1: _t->on_pushButton_modifC_clicked(); break;
        case 2: _t->on_pushButton_suppC_clicked(); break;
        case 3: _t->on_tableView_client_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 4: _t->on_lineEdit_rechC_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_dateEdit_search_dateChanged((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 6: _t->on_pushButton_pdfC_clicked(); break;
        case 7: _t->generatePDF((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->displayClientsByCity(); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->on_pushButton_ajoutCm_clicked(); break;
        case 12: _t->on_pushButton_modifCm_clicked(); break;
        case 13: _t->on_pushButton_suppCm_clicked(); break;
        case 14: _t->on_tableView_commande_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 15: _t->chargerClientsDansComboBox(); break;
        case 16: _t->envoyerEmailCommandeComplete((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 17: _t->on_pushButton_tricommande_clicked(); break;
        case 18: _t->on_pushButton_triclient_clicked(); break;
        case 19: _t->on_lineEdit_rechCom_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->on_pushButton_pdfCm_clicked(); break;
        case 21: _t->generatePDFCm((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->displayCommandesByEtat(); break;
        case 23: _t->on_dateEdit_search_cm_dateChanged((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    return _id;
}
QT_WARNING_POP
