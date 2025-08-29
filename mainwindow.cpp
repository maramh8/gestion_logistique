#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "QMessageBox"
#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <qerrormessage.h>




#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include <QPdfWriter>
#include <QVBoxLayout>



#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>



#include "QtSMTPClient.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QEventLoop>
#include <QDebug>



#include "QrCode.h"      // our minimal QR generator
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPrintDialog>
#include <QStandardPaths>
using namespace qrcodegen; // Namespace from QrCode.h


Client client;
Commande commande;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_ajoutCm->setIcon(QIcon(":/images/images/tabler--square-rounded-plus.png"));
    ui->pushButton_ajoutCm->setIconSize(QSize(30,30));
    ui->pushButton_ajoutCm->setStyleSheet("text-align: left; padding-left: 5px;");
    ui->pushButton_modifCm->setIcon(QIcon(":/images/images/tabler--edit.png"));
    ui->pushButton_modifCm->setIconSize(QSize(30,30));
    ui->pushButton_modifCm->setStyleSheet("text-align: left; padding-left: 5px;");










    ui->tableView_client->setModel(client.afficher());


    ui->tableView_commande->setModel(commande.afficher());

    chargerClientsDansComboBox();
    displayCommandesByEtat();
    displayClientsByCity();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajoutC_clicked()
{
    QString nom = ui->lineEdit_nom->text().trimmed();
    QString prenom = ui->lineEdit_prenom->text().trimmed();
    QString adresse = ui->lineEdit_adresse->text().trimmed();
    QString ville = ui->lineEdit_ville->text().trimmed();
    QString telephone = ui->lineEdit_tel->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QDate datecreation = ui->dateEdit->date();

    // ---------- Validation ----------
    static QRegularExpression reAlpha("^[A-Za-zÀ-ÖØ-öø-ÿ\\s-]+$"); // letters + accents
     static QRegularExpression reTel("^\\d{8}$");                   // exactly 8 digits
    static const QRegularExpression reEmail(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$",
        QRegularExpression::CaseInsensitiveOption
        );

    if(nom.isEmpty() || !reAlpha.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Nom invalide !");
        return;
    }
    if(prenom.isEmpty() || !reAlpha.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Prénom invalide !");
        return;
    }
    if(adresse.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Adresse ne peut pas être vide !");
        return;
    }
    if(ville.isEmpty() || !reAlpha.match(ville).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Ville invalide !");
        return;
    }
    if(!reTel.match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Téléphone invalide (8 chiffres) !");
        return;
    }
    if(!reEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Email invalide !");
        return;
    }
    if(datecreation > QDate::currentDate()) {
        QMessageBox::warning(this, "Validation", "La date ne peut pas être dans le futur !");
        return;
    }

    // ---------- Ajout ----------
    Client c(nom, prenom, adresse, ville, telephone, email, datecreation);
    bool success = c.ajouter();

    if(success) {
        ui->tableView_client->setModel(c.afficher());
         displayClientsByCity();

        // Clear inputs
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_ville->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_email->clear();
        ui->dateEdit->setDate(QDate::currentDate());

        QMessageBox::information(this, "Ajout", "Ajout réussi !");
    }
    else {
        QMessageBox::critical(this, "Échec", "L'ajout a échoué !");
    }
}


void MainWindow::on_pushButton_modifC_clicked()
{
    // Get selected row from the client table
    QModelIndexList sel = ui->tableView_client->selectionModel()
                              ? ui->tableView_client->selectionModel()->selectedIndexes()
                              : QModelIndexList();

    if (sel.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune sélection"),
                             tr("Veuillez sélectionner un client à modifier dans le tableau."));
        return;
    }

    // ID is column 0 of the first selected row
    const int row = sel.first().row();
    const int id  = ui->tableView_client->model()
                       ->index(row, 0).data().toInt();

    // Read form fields
    const QString nom       = ui->lineEdit_nom->text();
    const QString prenom    = ui->lineEdit_prenom->text();
    const QString adresse   = ui->lineEdit_adresse->text();
    const QString ville     = ui->lineEdit_ville->text();
    const QString telephone = ui->lineEdit_tel->text();
    const QString email     = ui->lineEdit_email->text();
    const QDate   datecre   = ui->dateEdit->date();

    // Build object and update
    Client c(nom, prenom, adresse, ville, telephone, email, datecre);
    const bool ok = c.modifier(id);

    if (ok) {
         displayClientsByCity();

        ui->tableView_client->setModel(c.afficher());
        // Clear inputs
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_ville->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_email->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        QMessageBox::information(this, tr("Modification"),
                                 tr("Client modifié avec succès."));
    } else {
        QMessageBox::critical(this, tr("Échec"),
                              tr("La modification a échoué."));
    }
}






void MainWindow::on_pushButton_suppC_clicked()
{
    // Récupérer les indices sélectionnés depuis le tableau
    QModelIndexList selectedIndexes = ui->tableView_client->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        // Récupérer l'ID depuis la première colonne de la première ligne sélectionnée
        int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        // Appeler la fonction supprimer de votre classe Fournisseur
        bool supprime = client.supprimer(id);

        if (supprime) {
             displayClientsByCity();
            // Rafraîchir le tableau après la suppression
            ui->tableView_client->setModel(client.afficher());
            QMessageBox::information(this, "Suppression réussie", "Fournisseur supprimé avec succès.");
        } else {
            QMessageBox::warning(this, "Échec de la suppression", "Échec de la suppression du fournisseur.");
        }
    } else {
        QMessageBox::warning(this, "Aucun fournisseur sélectionné", "Veuillez sélectionner un fournisseur à supprimer.");
    }
}


void MainWindow::on_tableView_client_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    const int row = index.row();
    QAbstractItemModel* m = ui->tableView_client->model();


    ui->lineEdit_nom->setText(       m->index(row, 1).data().toString());
    ui->lineEdit_prenom->setText(    m->index(row, 2).data().toString());
    ui->lineEdit_adresse->setText(   m->index(row, 3).data().toString());
    ui->lineEdit_ville->setText(     m->index(row, 4).data().toString());
    ui->lineEdit_tel->setText(       m->index(row, 5).data().toString());
    ui->lineEdit_email->setText(     m->index(row, 6).data().toString());


    QVariant vdate = m->index(row, 7).data();
    QDate d = vdate.typeId() == QMetaType::QDate
                  ? vdate.toDate()
                  : QDate::fromString(vdate.toString(), Qt::ISODate);
    if (!d.isValid()) d = QDate::currentDate();
    ui->dateEdit->setDate(d);


}





void MainWindow::on_lineEdit_rechC_textChanged(const QString &arg1)
{
    // Live search on both name fields
    QSqlQueryModel* model = Client::rechercher(arg1 , arg1 );
    ui->tableView_client->setModel(model);
}


void MainWindow::on_dateEdit_search_dateChanged(const QDate &date)
{
    QSqlQueryModel* model = Client::rechercherParDate(date);
    ui->tableView_client->setModel(model);
}


void MainWindow::on_pushButton_pdfC_clicked()
{
    generatePDF("");
}

void MainWindow::generatePDF( QString filePath)
{
    // Get the file path using QFileDialog
    QString fileName = filePath;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");
    }

    // Check if the user canceled the dialog or didn't provide a file name
    if (fileName.isNull()) {
        qDebug() << "PDF generation canceled by the user.";
        return;
    }

    // Create a PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A1));

    // Create a painter for the PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Retrieve data from the table view model and write it to the PDF
    int rowCount = ui->tableView_client->model()->rowCount();
    int colCount = ui->tableView_client->model()->columnCount();
    int cellWidth = pdfWriter.width() / colCount;
    int cellHeight = 500;
    int margin = 100;


    QFont font = painter.font();
    font.setPixelSize(200);
    painter.setFont(font);

    // Draw headers
    for (int col = 0; col < colCount; ++col) {
        QString headerData = ui->tableView_client->model()->headerData(col, Qt::Horizontal).toString();
        int x = col * cellWidth + margin;
        int y = 0;
        QRect headerRect(x, y, cellWidth - margin, cellHeight - margin);
        painter.drawText(headerRect, Qt::AlignLeft | Qt::AlignVCenter, headerData);
    }

    // Draw cell data
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QModelIndex index = ui->tableView_client->model()->index(row, col);
            QString cellData = ui->tableView_client->model()->data(index, Qt::DisplayRole).toString();

            // Calculate cell position with padding
            int x = col * cellWidth + margin;
            int y = (row + 1) * cellHeight + margin;

            // Draw cell data with padding
            QRect cellRect(x, y, cellWidth - margin, cellHeight - margin);
            painter.drawText(cellRect, Qt::AlignLeft | Qt::AlignVCenter, cellData);
        }
    }

    // Finish painting
    painter.end();

    QMessageBox::information(this, "PDF Generated", "PDF generated successfully at:\n" + fileName);
}


void MainWindow::displayClientsByCity() {
    // Clear frame layout
    if (!ui->frame_client->layout()) {
        QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame_client);
        ui->frame_client->setLayout(frameLayout);
    } else {
        QLayoutItem *item;
        while ((item = ui->frame_client->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    // Get data
    Client c;
    QBarSeries *series = c.getClientsByCity();
    if (!series) return;

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de clients par ville");

    // Collect categories from the query
    QStringList categories;
    {
        QSqlQuery query("SELECT ville, COUNT(*) as count FROM client GROUP BY ville ORDER BY count DESC");
        while (query.next()) {
            categories << query.value("ville").toString();
        }
    }

    // Create X axis with city names
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y axis (numbers)
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de clients");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Put chart into a view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->frame_client->layout()->addWidget(chartView);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


////////////////////commande


void MainWindow::on_pushButton_ajoutCm_clicked()
{
    QDate   dateCommande = ui->dateEdit_Commande->date();
    QString etat         = ui->comboBox_etat->currentText().trimmed();
    double  montant      = ui->lineEdit_montant->text().trimmed().toDouble();
    int     idClient     = ui->comboBox_client->currentData().toInt();
    if (idClient == 0) idClient = ui->comboBox_client->currentText().toInt(); // fallback

    Commande c = Commande(idClient, montant, etat, dateCommande);
    bool success = c.ajouter();

    if (success)
    {
        displayCommandesByEtat();
        ui->tableView_commande->setModel(c.afficher());

        // Clear inputs
        ui->dateEdit_Commande->setDate(QDate::currentDate());
        ui->comboBox_etat->setCurrentIndex(0);
        ui->lineEdit_montant->clear();
        if (ui->comboBox_client->count() > 0) ui->comboBox_client->setCurrentIndex(0);

        QMessageBox::information(nullptr, QObject::tr("ajout"),
                                 QObject::tr("Commande ajoutée avec succès.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                              QObject::tr("L'ajout de la commande a échoué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_modifCm_clicked()
{
    int id = ui->lineEdit_idCommande->text().toInt();

    QDate   dateCommande = ui->dateEdit_Commande->date();
    QString etat         = ui->comboBox_etat->currentText().trimmed();
    double  montant      = ui->lineEdit_montant->text().trimmed().toDouble();
    int     idClient     = ui->comboBox_client->currentData().toInt();


    Commande c = Commande(id, idClient, montant, etat, dateCommande);



    bool test = c.modifier(id);

    if (test) {
        displayCommandesByEtat();





        // Update the table view with the modified fournisseur data
        ui->tableView_commande->setModel(commande.afficher());
         ui->lineEdit_idCommande->clear();

        ui->dateEdit_Commande->setDate(QDate::currentDate());
         ui->comboBox_etat->setCurrentIndex(0);
        ui->lineEdit_montant->clear();
        if (ui->comboBox_client->count() > 0) ui->comboBox_client->setCurrentIndex(0);
        if (etat.compare("Complete", Qt::CaseInsensitive) == 0) {
            envoyerEmailCommandeComplete(idClient, id);
        }



        // Display success message
        QMessageBox::information(nullptr, QObject::tr("Modifier un fournisseur"),
                                 QObject::tr("Fournisseur modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        // Display error message
        QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                 QObject::tr("ERREUR.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_suppCm_clicked()
{
    // at least one selected index
    QModelIndexList selectedIndexes = ui->tableView_commande->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        // get id from selected row
        int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        // Appele suppression
        bool supprime = commande.supprimer(id);

        if (supprime) {
            displayCommandesByEtat();

            ui->tableView_commande->setModel(commande.afficher());



            ui->dateEdit_Commande->clear();


            ui->comboBox_client->setCurrentIndex(0); // Assuming index 0 is a default value
            ui->lineEdit_montant->clear();

            QMessageBox::information(this, "Suppression réussie", "Fournisseur supprimé avec succès.");
        } else {
            QMessageBox::warning(this, "Échec de la suppression", "Échec de la suppression du fournisseur.");
        }
    } else {
        QMessageBox::warning(this, "Aucun fournisseur sélectionné", "Veuillez sélectionner un fournisseur à supprimer.");
    }
}


void MainWindow::on_tableView_commande_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int id = ui->tableView_commande->model()
                 ->data(ui->tableView_commande->model()->index(row, 0)).toInt();
    QDate dateCommande = ui->tableView_commande->model()
                             ->data(ui->tableView_commande->model()->index(row, 1)).toDate();
    QString etat = ui->tableView_commande->model()
                       ->data(ui->tableView_commande->model()->index(row, 2)).toString();
    double montant = ui->tableView_commande->model()
                         ->data(ui->tableView_commande->model()->index(row, 3)).toDouble();

    // Column 4 = ID_CLIENT (hidden in table)
    int idClient = ui->tableView_commande->model()
                       ->data(ui->tableView_commande->model()->index(row, 4)).toInt();

    // Column 5 = NOM + PRENOM (client full name)
    QString nomComplet = ui->tableView_commande->model()
                             ->data(ui->tableView_commande->model()->index(row, 5)).toString();

    // Fill the form fields
    ui->lineEdit_idCommande->setText(QString::number(id));
    ui->dateEdit_Commande->setDate(dateCommande.isValid() ? dateCommande : QDate::currentDate());

    // Set state combo box
    int idxEtat = ui->comboBox_etat->findText(etat);
    if (idxEtat >= 0) {
        ui->comboBox_etat->setCurrentIndex(idxEtat);
    } else {
        ui->comboBox_etat->setCurrentIndex(0);
    }

    ui->lineEdit_montant->setText(QString::number(montant, 'f', 2));

    // Set client combo box
    int idx = ui->comboBox_client->findText(nomComplet, Qt::MatchExactly);
    if (idx >= 0) {
        ui->comboBox_client->setCurrentIndex(idx);
    } else {
        ui->comboBox_client->setCurrentIndex(0);
    }

    // Fetch complete client details from database
    QString nomClient, prenomClient, emailClient, telephoneClient, adresseClient;
    QSqlQuery clientQuery;
    clientQuery.prepare("SELECT NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE FROM CLIENT WHERE ID_CLIENT = :id");
    clientQuery.bindValue(":id", idClient);

    if (clientQuery.exec() && clientQuery.next()) {
        nomClient = clientQuery.value(0).toString();
        prenomClient = clientQuery.value(1).toString();
        emailClient = clientQuery.value(2).toString();
        telephoneClient = clientQuery.value(3).toString();
        adresseClient = clientQuery.value(4).toString();
    }

    qDebug() << "👤 Client details:" << nomClient << prenomClient << emailClient;

    // --- QR Code Generation for completed orders ---
    if (etat.toLower() == "complete" || etat.toLower() == "completed") {

        // Create comprehensive receipt data using the updated method
        QString receiptData = QrCodeGenerator::createOrderReceipt(
            id,                    // Order ID
            dateCommande,          // Order date
            etat,                  // Status
            montant,               // Amount
            idClient,              // Client ID
            nomClient,             // Client first name
            prenomClient,          // Client last name
            emailClient,           // Client email
            telephoneClient,       // Client phone
            "receipt"              // Mode: full receipt format
            );

        qDebug().noquote() << "📝 Complete Receipt Data:";
        qDebug().noquote() << receiptData;

        // Generate QR code
        QImage qrImage = QrCodeGenerator::generateQROnline(receiptData, 400);

        // Fallback to offline if online fails
        if (qrImage.isNull()) {
            qDebug() << "🌐 Online method failed, trying offline...";
            qrImage = QrCodeGenerator::generateQR(receiptData, 400);
        }

        qDebug() << "🖼️ QR IMAGE size:" << qrImage.size() << "isNull:" << qrImage.isNull();

        if (!qrImage.isNull()) {
            QPixmap qrPixmap = QPixmap::fromImage(qrImage);

            // Scale to fit label
            int labelWidth = ui->label_qrcode->width();
            int labelHeight = ui->label_qrcode->height();

            if (labelWidth > 0 && labelHeight > 0) {
                qrPixmap = qrPixmap.scaled(labelWidth, labelHeight,
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
            }

            // Display QR code
            ui->label_qrcode->setPixmap(qrPixmap);
            ui->label_qrcode->setScaledContents(false);
            ui->label_qrcode->setAlignment(Qt::AlignCenter);
            ui->label_qrcode->setStyleSheet("");

            currentQrImage = qrImage;

            // Comprehensive tooltip
            ui->label_qrcode->setToolTip(
                QString("📱 CLIENT RECEIPT QR CODE\n\n"
                        "📋 Order #%1\n"
                        "📅 Date: %2\n"
                        "👤 Client: %3 %4\n"
                        "📧 Email: %5\n"
                        "📞 Phone: %6\n"
                        "🏠 Address: %7\n"
                        "💰 Amount: %8 EUR\n"
                        "✅ Status: %9\n\n"
                        "Scan with phone to view complete receipt")
                    .arg(id)
                    .arg(dateCommande.toString("dd/MM/yyyy"))
                    .arg(nomClient)
                    .arg(prenomClient)
                    .arg(emailClient)
                    .arg(telephoneClient)
                    .arg(adresseClient.isEmpty() ? "N/A" : adresseClient)
                    .arg(montant, 0, 'f', 2)
                    .arg(etat)
                );

            qDebug() << "✅ Complete client receipt QR code generated successfully!";

            // Save complete receipt to desktop for testing
            QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
            QString qrFilePath = desktopPath + QString("/client_receipt_%1.png").arg(id);
            QString textFilePath = desktopPath + QString("/client_receipt_%1.txt").arg(id);

            // Save QR image
            if (qrImage.save(qrFilePath)) {
                qDebug() << "💾 Client receipt QR saved to:" << qrFilePath;
            }

            // Save readable text version
            QFile textFile(textFilePath);
            if (textFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&textFile);
                out << receiptData;
                textFile.close();
                qDebug() << "📄 Readable receipt saved to:" << textFilePath;
            }

        } else {
            qDebug() << "❌ QR generation failed";
            ui->label_qrcode->clear();
            ui->label_qrcode->setText("❌ QR Code\ngeneration failed");
            ui->label_qrcode->setStyleSheet("color: red; font-weight: bold;");
            ui->label_qrcode->setAlignment(Qt::AlignCenter);
        }

    } else {
        qDebug() << "ℹ️ QR not generated - order status is:" << etat;
        ui->label_qrcode->clear();
        ui->label_qrcode->setText("QR Code available\nafter order completion");
        ui->label_qrcode->setStyleSheet("color: gray; font-style: italic;");
        ui->label_qrcode->setAlignment(Qt::AlignCenter);
        ui->label_qrcode->setToolTip("Complete the order to generate QR code");
    }



}


void MainWindow::chargerClientsDansComboBox()
{

        // Clear existing items
        ui->comboBox_client->clear();

        // Add default selection
        ui->comboBox_client->addItem("-- Sélectionner un client --", -1);

        // Create and execute query directly here
        QSqlQuery query;
        query.prepare("SELECT id_client, nom, prenom FROM client ORDER BY nom, prenom");

        if (!query.exec()) {
            qDebug() << "Erreur SQL:" << query.lastError().text();
            return;
        }

        // Iterate through results and populate combo box
        while (query.next()) {
            int idClient = query.value("id_client").toInt();
            QString nom = query.value("nom").toString();
            QString prenom = query.value("prenom").toString();

            // Create full name for display
            QString fullName = nom + " " + prenom;

            // Add to combo box: display full name, store client ID as user data
            ui->comboBox_client->addItem(fullName, idClient);
        }
}






void MainWindow::envoyerEmailCommandeComplete(int idClient, int idCommande)
{
    QSqlQuery query;
    query.prepare("SELECT EMAIL, NOM, PRENOM FROM client WHERE ID_CLIENT = :idClient");
    query.bindValue(":idClient", idClient);
    if (!query.exec() || !query.next()) {
        qDebug() << "❌ Database error";
        return;
    }
    QString emailClient = query.value("EMAIL").toString();
    QString nomClient   = query.value("NOM").toString();
    QString prenomClient= query.value("PRENOM").toString();
    if (emailClient.isEmpty()) {
        qDebug() << "❌ Empty email";
        return;
    }

    // --- 2. Sujet du mail ---
    QString subject = QString("🎉 Votre commande #%1 est prête !").arg(idCommande);

    // --- 3. Corps du mail en HTML moderne (compatible Qt 6.7.3) ---
    QString body = QString(R"(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Commande Prête</title>
  <style>
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background-color: #f0f2f5;
      margin: 0;
      padding: 20px;
      line-height: 1.6;
    }
    .email-wrapper {
      max-width: 600px;
      margin: 0 auto;
      background: #ffffff;
      border-radius: 12px;
      overflow: hidden;
      box-shadow: 0 8px 24px rgba(0,0,0,0.12);
    }
    .header {
      background: #00c851;
      background: -webkit-linear-gradient(135deg, #00c851 0%, #00a040 100%);
      background: linear-gradient(135deg, #00c851 0%, #00a040 100%);
      color: white;
      text-align: center;
      padding: 40px 20px;
    }
    .header h1 {
      margin: 0 0 10px 0;
      font-size: 28px;
      font-weight: 700;
    }
    .header .subtitle {
      margin: 0;
      font-size: 16px;
      opacity: 0.9;
    }
    .status-badge {
      display: inline-block;
      background: rgba(255, 255, 255, 0.25);
      padding: 10px 20px;
      border-radius: 25px;
      margin-top: 15px;
      font-weight: 600;
      font-size: 14px;
      border: 2px solid rgba(255, 255, 255, 0.3);
    }
    .content {
      padding: 40px 30px;
    }
    .greeting {
      font-size: 20px;
      color: #2c3e50;
      margin-bottom: 30px;
      font-weight: 500;
    }
    .order-card {
      background: #f8f9ff;
      border: 1px solid #e6f3ff;
      border-left: 5px solid #00c851;
      padding: 25px;
      border-radius: 8px;
      margin: 30px 0;
    }
    .order-number {
      font-size: 24px;
      font-weight: bold;
      color: #00a040;
      margin-bottom: 15px;
    }
    .order-status {
      margin-bottom: 20px;
    }
    .status-check {
      display: inline-block;
      width: 20px;
      height: 20px;
      background: #00c851;
      color: white;
      border-radius: 50%;
      text-align: center;
      line-height: 20px;
      font-weight: bold;
      font-size: 12px;
      margin-right: 10px;
      vertical-align: middle;
    }
    .message {
      color: #555;
      font-size: 16px;
      margin: 25px 0;
    }
    .cta-section {
      text-align: center;
      margin: 40px 0;
    }
    .cta-button {
      display: inline-block;
      background: #00c851;
      background: -webkit-linear-gradient(135deg, #00c851 0%, #00a040 100%);
      background: linear-gradient(135deg, #00c851 0%, #00a040 100%);
      color: white;
      text-decoration: none;
      padding: 18px 35px;
      border-radius: 25px;
      font-weight: 600;
      font-size: 16px;
      box-shadow: 0 6px 16px rgba(0, 200, 81, 0.3);
      border: none;
    }
    .cta-button:hover {
      transform: translateY(-2px);
      box-shadow: 0 8px 20px rgba(0, 200, 81, 0.4);
    }
    .features-section {
      margin: 40px 0;
    }
    .features-grid {
      display: table;
      width: 100%;
      margin: 20px 0;
    }
    .feature {
      display: table-cell;
      width: 50%;
      text-align: center;
      padding: 20px 10px;
      vertical-align: top;
    }
    .feature-icon {
      width: 60px;
      height: 60px;
      background: #667eea;
      background: -webkit-linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      border-radius: 50%;
      margin: 0 auto 15px;
      display: flex;
      align-items: center;
      justify-content: center;
      color: white;
      font-size: 24px;
    }
    .feature h3 {
      font-size: 18px;
      color: #2c3e50;
      margin-bottom: 8px;
    }
    .feature p {
      color: #6c757d;
      font-size: 14px;
      margin: 0;
    }
    .divider {
      height: 1px;
      background: #e9ecef;
      margin: 30px 0;
    }
    .footer {
      background: #2c3e50;
      color: #bdc3c7;
      text-align: center;
      padding: 30px;
    }
    .company-name {
      color: white;
      font-weight: 600;
      font-size: 20px;
      margin-bottom: 10px;
    }
    .company-tagline {
      margin-bottom: 25px;
      font-style: italic;
    }
    .contact-links {
      margin: 20px 0;
    }
    .contact-links a {
      display: inline-block;
      margin: 0 15px;
      color: #bdc3c7;
      text-decoration: none;
      font-size: 14px;
      padding: 8px 15px;
      border: 1px solid #4a5568;
      border-radius: 20px;
    }
    .contact-links a:hover {
      background: #4a5568;
      color: white;
    }
    .footer-text {
      font-size: 12px;
      opacity: 0.8;
      border-top: 1px solid #4a5568;
      padding-top: 20px;
      margin-top: 20px;
    }
    .highlight {
      background: #fff3cd;
      padding: 2px 6px;
      border-radius: 4px;
      color: #856404;
    }

    /* Responsive pour mobiles */
    @media only screen and (max-width: 600px) {
      .content {
        padding: 30px 20px;
      }
      .header {
        padding: 30px 15px;
      }
      .header h1 {
        font-size: 24px;
      }
      .features-grid {
        display: block;
      }
      .feature {
        display: block;
        width: 100%;
        margin-bottom: 20px;
      }
      .order-card {
        padding: 20px 15px;
      }
    }
  </style>
</head>
<body>
  <div class="email-wrapper">
    <!-- En-tête -->
    <div class="header">
      <h1>🎉 Commande Prête !</h1>
      <p class="subtitle">Votre commande est maintenant disponible</p>
      <div class="status-badge">✅ PRÊTE POUR RÉCUPÉRATION</div>
    </div>

    <!-- Contenu principal -->
    <div class="content">
      <div class="greeting">
        Bonjour <strong>%1 %2</strong> 👋
      </div>

      <div class="order-card">
        <div class="order-number">Commande #%3</div>
        <div class="order-status">
          <span class="status-check">✓</span>
          <strong>Statut :</strong> <span class="highlight">Complète et prête</span>
        </div>
        <p style="margin: 0; color: #666;">
          Votre commande a été préparée avec soin et est maintenant disponible pour récupération ou livraison.
        </p>
      </div>

      <div class="message">
        <p>Nous sommes ravis de vous informer que votre commande est prête ! Notre équipe a mis tout son savoir-faire pour préparer votre commande dans les meilleures conditions.</p>
      </div>

      <!-- Bouton d'action -->
      <div class="cta-section">
        <a href="https://votre-site.com/suivi/%3" class="cta-button">
          📱 Voir ma commande
        </a>
      </div>

      <!-- Section des fonctionnalités -->
      <div class="features-section">
        <div class="features-grid">
          <div class="feature">
            <div class="feature-icon">🏪</div>
            <h3>Récupération</h3>
            <p>Venez récupérer votre commande directement en magasin</p>
          </div>
          <div class="feature">
            <div class="feature-icon">🚚</div>
            <h3>Livraison</h3>
            <p>Suivi de livraison disponible en temps réel</p>
          </div>
        </div>
      </div>

      <div class="divider"></div>

      <div class="message">
        <p style="font-size: 18px; color: #2c3e50;">
          💝 Merci de votre confiance et de votre fidélité !
        </p>
        <p>Nous espérons que votre commande vous apportera entière satisfaction.</p>

        <p style="margin-top: 25px; text-align: right;">
          <strong>L'équipe Votre Société</strong><br>
          <em style="color: #666;">Toujours à votre service</em> ✨
        </p>
      </div>
    </div>

    <!-- Pied de page -->
    <div class="footer">
      <div class="company-name">Votre Société</div>
      <p class="company-tagline">Excellence et service client depuis toujours</p>

      <div class="contact-links">
        <a href="#" title="Site Web">🌐 Site Web</a>
        <a href="#" title="Support">📞 Support</a>
        <a href="#" title="Email">✉️ Contact</a>
      </div>

      <div class="footer-text">
        © 2025 Votre Société – Tous droits réservés<br>
        Cet email vous a été envoyé car vous avez passé une commande chez nous.
      </div>
    </div>
  </div>
</body>
</html>
)").arg(prenomClient, nomClient).arg(idCommande);

    // --- 4. Config SMTP ---
    QtSMTPClient mailer;
    qDebug() << "🔄 Trying STARTTLS...";
    mailer.setServer("smtp.gmail.com", 587, false); // STARTTLS
    mailer.setAuth("jery.wizin@gmail.com", "ahtb qwxe bbwc jstw");
    if (mailer.sendEmail("jery.wizin@gmail.com", emailClient, subject, body)) {
        qDebug() << "✅ Email sent with STARTTLS (HTML)";
        return;
    }
    qDebug() << "⚠️ STARTTLS failed, trying SSL...";
    mailer.setServer("smtp.gmail.com", 465, true); // SSL direct
    mailer.setAuth("jery.wizin@gmail.com", "ahtb qwxe bbwc jstw");
    if (mailer.sendEmail("jery.wizin@gmail.com", emailClient, subject, body)) {
        qDebug() << "✅ Email sent with SSL (HTML)";
        return;
    }
    qDebug() << "❌ All methods failed";
}

void MainWindow::on_pushButton_tricommande_clicked()
{
    // Get values from comboboxes
    QString critere = ui->comboBox_critere->currentText();
    QString ordre = ui->comboBox_order->currentText();

    // Create commande instance and call tri method
    Commande cmd;
    QSqlQueryModel* model = cmd.trierCommandes(critere, ordre);

    // Apply model to table view
    ui->tableView_commande->setModel(model);

    // Optional: Resize columns
    ui->tableView_commande->resizeColumnsToContents();
}


void MainWindow::on_pushButton_triclient_clicked()
{
    // Récupérer les valeurs depuis les combobox
    QString critere = ui->comboBox_critere_client->currentText();
    QString ordre = ui->comboBox_order_client->currentText();

    // Créer un client et appeler la méthode de tri
    Client cl;
    QSqlQueryModel* model = cl.trierClients(critere, ordre);

    // Appliquer le modèle au QTableView
    ui->tableView_client->setModel(model);

    // Ajuster la taille des colonnes
    ui->tableView_client->resizeColumnsToContents();
}


void MainWindow::on_lineEdit_rechCom_textChanged(const QString &arg1)
{
    // Live search on both name fields
    QSqlQueryModel* model = Commande::rechercher(arg1);
    ui->tableView_commande->setModel(model);
}



void MainWindow::generatePDFCm( QString filePath)
{
    // Get the file path using QFileDialog
    QString fileName = filePath;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");
    }

    // Check if the user canceled the dialog or didn't provide a file name
    if (fileName.isNull()) {
        qDebug() << "PDF generation canceled by the user.";
        return;
    }

    // Create a PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A1));

    // Create a painter for the PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Retrieve data from the table view model and write it to the PDF
    int rowCount = ui->tableView_commande->model()->rowCount();
    int colCount = ui->tableView_commande->model()->columnCount();
    int cellWidth = pdfWriter.width() / colCount;
    int cellHeight = 500;
    int margin = 100;


    QFont font = painter.font();
    font.setPixelSize(200);
    painter.setFont(font);

    // Draw headers
    for (int col = 0; col < colCount; ++col) {
        QString headerData = ui->tableView_commande->model()->headerData(col, Qt::Horizontal).toString();
        int x = col * cellWidth + margin;
        int y = 0;
        QRect headerRect(x, y, cellWidth - margin, cellHeight - margin);
        painter.drawText(headerRect, Qt::AlignLeft | Qt::AlignVCenter, headerData);
    }

    // Draw cell data
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QModelIndex index = ui->tableView_commande->model()->index(row, col);
            QString cellData = ui->tableView_commande->model()->data(index, Qt::DisplayRole).toString();

            // Calculate cell position with padding
            int x = col * cellWidth + margin;
            int y = (row + 1) * cellHeight + margin;

            // Draw cell data with padding
            QRect cellRect(x, y, cellWidth - margin, cellHeight - margin);
            painter.drawText(cellRect, Qt::AlignLeft | Qt::AlignVCenter, cellData);
        }
    }

    // Finish painting
    painter.end();

    QMessageBox::information(this, "PDF Generated", "PDF generated successfully at:\n" + fileName);
}

void MainWindow::on_pushButton_pdfCm_clicked()
{
    generatePDFCm( "");
}


void MainWindow::displayCommandesByEtat() {
    if (!ui->frame_commande->layout()) {
        QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame_commande);
        ui->frame_commande->setLayout(frameLayout);
    } else {
        QLayoutItem *item;
        while ((item = ui->frame_commande->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    // Get series
    Commande cmd;
    QBarSeries *series = cmd.getCommandesByEtat();
    if (!series) return;

    // Build chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de commandes par état");

    // Categories (etat values)
    QStringList categories;
    QSqlQuery query("SELECT ETAT, COUNT(*) FROM commande GROUP BY ETAT ORDER BY COUNT(*) DESC");
    while (query.next()) {
        categories << query.value(0).toString();
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de commandes");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->frame_commande->layout()->addWidget(chartView);
}














void MainWindow::on_dateEdit_search_cm_dateChanged(const QDate &date)
{
    QSqlQueryModel* model = Commande::rechercherParDate(date);
    ui->tableView_commande->setModel(model);
}

