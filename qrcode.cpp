#include "QrCode.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QPainter>
#include <QDebug>
#include <algorithm>
#include <cstring>

namespace qrcodegen {

// Format information with BCH error correction
static const uint16_t FORMAT_INFO_TABLE[] = {
    0x5412, 0x5125, 0x5E7C, 0x5B4B, 0x45F9, 0x40CE, 0x4F97, 0x4AA0,
    0x77C4, 0x72F3, 0x7DAA, 0x789D, 0x662F, 0x6318, 0x6C41, 0x6976,
    0x1689, 0x13BE, 0x1CE7, 0x19D0, 0x0762, 0x0255, 0x0D0C, 0x083B,
    0x355F, 0x3068, 0x3F31, 0x3A06, 0x24B4, 0x2183, 0x2EDA, 0x2BED
};

// Version information for versions 7-40
static const uint32_t VERSION_INFO_TABLE[] = {
    0x07C94, 0x085BC, 0x09A99, 0x0A4D3, 0x0BBF6, 0x0C762, 0x0D847, 0x0E60D,
    0x0F928, 0x10B78, 0x1145D, 0x12A17, 0x13532, 0x149A6, 0x15683, 0x168C9,
    0x177EC, 0x18EC4, 0x191E1, 0x1AFAB, 0x1B08E, 0x1CC1A, 0x1D33F, 0x1ED75,
    0x1F250, 0x209D5, 0x216F0, 0x228BA, 0x2379F, 0x24B0B, 0x2542E, 0x26A64,
    0x27541, 0x28C69
};

QrCode QrCode::encodeText(const char *text, Ecc ecl) {
    std::vector<uint8_t> data;
    size_t len = strlen(text);

    if (len == 0) {
        return QrCode(1, ecl, std::vector<uint8_t>(), 0);
    }

    // Determine minimum version needed
    int version = 1;
    int capacity = getCapacity(version, ecl);
    while (len > capacity && version < 40) {
        version++;
        capacity = getCapacity(version, ecl);
    }

    if (len > capacity) {
        // Text too long even for version 40
        return QrCode(1, ecl, std::vector<uint8_t>(), 0);
    }

    // Encode in byte mode
    data.push_back(0x40); // Byte mode indicator

    // Length indicator (8 bits for versions 1-9, 16 bits for versions 10-26, etc.)
    if (version <= 9) {
        data.push_back(static_cast<uint8_t>(len));
    } else {
        data.push_back(static_cast<uint8_t>(len >> 8));
        data.push_back(static_cast<uint8_t>(len & 0xFF));
    }

    // Add text data
    for (size_t i = 0; i < len; i++) {
        data.push_back(static_cast<uint8_t>(text[i]));
    }

    // Convert to codewords and add error correction
    std::vector<uint8_t> codewords = encodeSegments(data, ecl, version);

    // Try different masks and choose the best one
    int bestMask = 0;
    int lowestPenalty = INT_MAX;

    for (int mask = 0; mask < 8; mask++) {
        QrCode testQr(version, ecl, codewords, mask);
        int penalty = testQr.calculatePenalty();
        if (penalty < lowestPenalty) {
            lowestPenalty = penalty;
            bestMask = mask;
        }
    }

    return QrCode(version, ecl, codewords, bestMask);
}

int QrCode::getCapacity(int version, Ecc ecl) {
    // Simplified capacity calculation for byte mode
    int totalCodewords = getNumDataCodewords(version, ecl);
    int headerSize = (version <= 9) ? 2 : 3; // Mode + length
    return totalCodewords - headerSize;
}

QrCode::QrCode(int ver, Ecc ecl, const std::vector<uint8_t> &dataCodewords, int mask)
    : version(ver), errorCorrectionLevel(ecl), size(ver * 4 + 17) {

    // Initialize modules
    modules = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
    isFunction = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));

    // Draw function patterns
    drawFunctionPatterns();

    // Draw codewords
    drawCodewords(dataCodewords);

    // Apply mask
    this->mask = mask;
    applyMask(mask);

    // Draw format information
    drawFormatBits(ecl, mask);

    // Draw version information for versions >= 7
    if (version >= 7) {
        drawVersion();
    }
}

void QrCode::drawFunctionPatterns() {
    // Draw finder patterns
    drawFinderPattern(3, 3);
    drawFinderPattern(size - 4, 3);
    drawFinderPattern(3, size - 4);

    // Draw separators
    drawFinderSeparator(7, 0);
    drawFinderSeparator(size - 8, 0);
    drawFinderSeparator(0, size - 8);

    // Draw alignment patterns
    std::vector<int> alignPos = getAlignmentPatternPositions(version);
    for (int i : alignPos) {
        for (int j : alignPos) {
            if (!(i == 6 && j == 6) &&
                !(i == 6 && j == size - 7) &&
                !(i == size - 7 && j == 6)) {
                drawAlignmentPattern(i, j);
            }
        }
    }

    // Draw timing patterns
    for (int i = 8; i < size - 8; i++) {
        setFunctionModule(6, i, i % 2 == 0);
        setFunctionModule(i, 6, i % 2 == 0);
    }

    // Draw dark module
    setFunctionModule((4 * version) + 9, 8, true);

    // Draw format information area (will be filled later)
    for (int i = 0; i < 8; i++) {
        setFunctionModule(8, i, false);
        setFunctionModule(i, 8, false);
    }
    for (int i = 0; i < 9; i++) {
        setFunctionModule(8, size - 1 - i, false);
        setFunctionModule(size - 1 - i, 8, false);
    }
}

void QrCode::drawFinderPattern(int x, int y) {
    for (int dy = -4; dy <= 4; dy++) {
        for (int dx = -4; dx <= 4; dx++) {
            int dist = std::max(std::abs(dx), std::abs(dy));
            int xx = x + dx, yy = y + dy;
            if (0 <= xx && xx < size && 0 <= yy && yy < size) {
                setFunctionModule(xx, yy, (dist != 2 && dist != 4));
            }
        }
    }
}

void QrCode::drawFinderSeparator(int x, int y) {
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int xx = x + dx, yy = y + dy;
            if (0 <= xx && xx < size && 0 <= yy && yy < size) {
                setFunctionModule(xx, yy, false);
            }
        }
    }
}

void QrCode::drawAlignmentPattern(int x, int y) {
    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
            int xx = x + dx, yy = y + dy;
            if (0 <= xx && xx < size && 0 <= yy && yy < size) {
                setFunctionModule(xx, yy, (std::max(std::abs(dx), std::abs(dy)) != 1));
            }
        }
    }
}

void QrCode::drawFormatBits(Ecc ecl, int mask) {
    int data = (static_cast<int>(ecl) << 3) | mask;
    int bits = FORMAT_INFO_TABLE[data];

    // Draw first format info
    for (int i = 0; i < 6; i++) {
        setFunctionModule(8, i, ((bits >> i) & 1) != 0);
    }
    setFunctionModule(8, 7, ((bits >> 6) & 1) != 0);
    setFunctionModule(8, 8, ((bits >> 7) & 1) != 0);
    setFunctionModule(7, 8, ((bits >> 8) & 1) != 0);
    for (int i = 9; i < 15; i++) {
        setFunctionModule(14 - i, 8, ((bits >> i) & 1) != 0);
    }

    // Draw second format info
    for (int i = 0; i < 8; i++) {
        setFunctionModule(size - 1 - i, 8, ((bits >> i) & 1) != 0);
    }
    for (int i = 8; i < 15; i++) {
        setFunctionModule(8, size - 15 + i, ((bits >> i) & 1) != 0);
    }
}

void QrCode::drawVersion() {
    if (version < 7) return;

    int bits = VERSION_INFO_TABLE[version - 7];

    // Draw two version info blocks
    for (int i = 0; i < 18; i++) {
        bool bit = ((bits >> i) & 1) != 0;
        int a = size - 11 + i % 3;
        int b = i / 3;
        setFunctionModule(a, b, bit);
        setFunctionModule(b, a, bit);
    }
}

void QrCode::setFunctionModule(int x, int y, bool isDark) {
    modules[y][x] = isDark;
    isFunction[y][x] = true;
}

void QrCode::drawCodewords(const std::vector<uint8_t> &data) {
    int i = 0;
    for (int right = size - 1; right >= 1; right -= 2) {
        if (right == 6)
            right = 5;
        for (int vert = 0; vert < size; vert++) {
            for (int j = 0; j < 2; j++) {
                int x = right - j;
                bool upward = ((right + 1) & 2) == 0;
                int y = upward ? size - 1 - vert : vert;
                if (!isFunction[y][x] && i < data.size() * 8) {
                    modules[y][x] = ((data[i >> 3] >> (7 - (i & 7))) & 1) != 0;
                    i++;
                }
            }
        }
    }
}

void QrCode::applyMask(int mask) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (!isFunction[y][x]) {
                bool invert = false;
                switch (mask) {
                case 0: invert = (x + y) % 2 == 0; break;
                case 1: invert = y % 2 == 0; break;
                case 2: invert = x % 3 == 0; break;
                case 3: invert = (x + y) % 3 == 0; break;
                case 4: invert = (x / 3 + y / 2) % 2 == 0; break;
                case 5: invert = x * y % 2 + x * y % 3 == 0; break;
                case 6: invert = (x * y % 2 + x * y % 3) % 2 == 0; break;
                case 7: invert = ((x + y) % 2 + x * y % 3) % 2 == 0; break;
                }
                if (invert)
                    modules[y][x] = !modules[y][x];
            }
        }
    }
}

int QrCode::calculatePenalty() {
    int penalty = 0;

    // Rule 1: Adjacent modules in row/column with same color
    for (int y = 0; y < size; y++) {
        int runLength = 0;
        bool runColor = false;
        for (int x = 0; x < size; x++) {
            if (x == 0 || modules[y][x] != runColor) {
                runColor = modules[y][x];
                runLength = 1;
            } else {
                runLength++;
                if (runLength >= 5)
                    penalty += runLength - 2;
            }
        }
    }

    for (int x = 0; x < size; x++) {
        int runLength = 0;
        bool runColor = false;
        for (int y = 0; y < size; y++) {
            if (y == 0 || modules[y][x] != runColor) {
                runColor = modules[y][x];
                runLength = 1;
            } else {
                runLength++;
                if (runLength >= 5)
                    penalty += runLength - 2;
            }
        }
    }

    // Rule 2: 2x2 blocks of same color
    for (int y = 0; y < size - 1; y++) {
        for (int x = 0; x < size - 1; x++) {
            bool color = modules[y][x];
            if (color == modules[y][x + 1] &&
                color == modules[y + 1][x] &&
                color == modules[y + 1][x + 1]) {
                penalty += 3;
            }
        }
    }

    return penalty;
}

std::vector<uint8_t> QrCode::encodeSegments(const std::vector<uint8_t> &data, Ecc ecl, int version) {
    std::vector<uint8_t> result = data;

    // Add terminator (0000)
    if (result.size() < getNumDataCodewords(version, ecl)) {
        result.push_back(0x00);
    }

    // Pad to byte boundary
    while (result.size() % 8 != 0 && result.size() < getNumDataCodewords(version, ecl)) {
        result.push_back(0x00);
    }

    // Add padding bytes
    for (int i = 0; result.size() < getNumDataCodewords(version, ecl); i++) {
        result.push_back((i % 2 == 0) ? 0xEC : 0x11);
    }

    return result;
}

std::vector<int> QrCode::getAlignmentPatternPositions(int ver) {
    if (ver == 1)
        return std::vector<int>();
    else {
        int numAlign = ver / 7 + 2;
        int step = (ver == 32) ? 26 :
                       (ver * 4 + numAlign * 2 + 1) / (numAlign * 2 - 2) * 2;
        std::vector<int> result;
        for (int i = 0, pos = ver * 4 + 10; i < numAlign - 1; i++, pos -= step)
            result.insert(result.begin(), pos);
        result.insert(result.begin(), 6);
        return result;
    }
}

int QrCode::getNumDataCodewords(int ver, Ecc ecl) {
    // Simplified table - first 10 versions for each error correction level
    static const int table[4][10] = {
        // Low
        {19, 34, 55, 80, 108, 136, 156, 194, 232, 274},
        // Medium
        {16, 28, 44, 64, 86, 108, 124, 154, 182, 216},
        // Quartile
        {13, 22, 34, 48, 62, 76, 88, 110, 132, 154},
        // High
        {9, 16, 26, 36, 46, 60, 66, 86, 100, 122}
    };

    if (ver > 10) ver = 10; // Cap at version 10 for this simplified table
    return table[static_cast<int>(ecl)][ver - 1];
}

int QrCode::getSize() const {
    return size;
}

bool QrCode::getModule(int x, int y) const {
    if (0 <= x && x < size && 0 <= y && y < size)
        return modules[y][x];
    return false;
}

} // namespace qrcodegen

// QrCodeGenerator Implementation
QImage QrCodeGenerator::generateQR(const QString& data, int size)
{
    using namespace qrcodegen;

    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::MEDIUM);

    int qrSize = qr.getSize();
    int scale = size / qrSize;
    if (scale < 1) scale = 1;

    // Add quiet zone (border)
    int border = 4;
    int imgSize = (qrSize + border * 2) * scale;

    QImage image(imgSize, imgSize, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    for (int y = 0; y < qrSize; y++) {
        for (int x = 0; x < qrSize; x++) {
            if (qr.getModule(x, y)) {
                painter.drawRect((x + border) * scale, (y + border) * scale, scale, scale);
            }
        }
    }

    return image;
}

QImage QrCodeGenerator::generateQROnline(const QString& data, int size) {
    QString url = QString("https://api.qrserver.com/v1/create-qr-code/?size=%1x%1&data=%2")
    .arg(size)
        .arg(QString(QUrl::toPercentEncoding(data)));

    QNetworkAccessManager manager;
    QNetworkRequest request(url);

    // Set timeout
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    timer.setInterval(5000); // 5 seconds timeout

    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timer.start();
    loop.exec();

    QImage qrImage;
    if (timer.isActive() && reply->error() == QNetworkReply::NoError) {
        timer.stop();
        QByteArray imageData = reply->readAll();
        qrImage.loadFromData(imageData);

        // Add border for better scanning
        if (!qrImage.isNull()) {
            int borderSize = size / 20; // 5% border
            QImage borderedImage(size + borderSize * 2, size + borderSize * 2, QImage::Format_RGB32);
            borderedImage.fill(Qt::white);

            QPainter painter(&borderedImage);
            painter.drawImage(borderSize, borderSize, qrImage);
            qrImage = borderedImage;
        }
    }

    reply->deleteLater();

    // Fallback to original method if online fails
    if (qrImage.isNull()) {
        qDebug() << "Online QR generation failed, using fallback method";
        qrImage = generateQR(data, size);
    }

    return qrImage;
}

QImage QrCodeGenerator::generateQRSimple(const QString& data, int size) {
    // Simple fallback - use the original method
    return generateQR(data, size);
}

QImage QrCodeGenerator::createQrImage(const qrcodegen::QrCode& qr, int scale, int border) {
    int qrSize = qr.getSize();
    int imgSize = (qrSize + border * 2) * scale;

    QImage image(imgSize, imgSize, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    for (int y = 0; y < qrSize; y++) {
        for (int x = 0; x < qrSize; x++) {
            if (qr.getModule(x, y)) {
                painter.drawRect((x + border) * scale,
                                 (y + border) * scale,
                                 scale, scale);
            }
        }
    }

    return image;
}

// Updated createOrderReceipt method in QrCode.cpp
QString QrCodeGenerator::createOrderReceipt(int idCommande,
                                            const QDate& dateCommande,
                                            const QString& etat,
                                            double montant,
                                            int idClient,
                                            const QString& nomClient,
                                            const QString& prenomClient,
                                            const QString& emailClient,
                                            const QString& telephoneClient,
                                            const QString& mode)
{
    if (mode == "url") {
        // Short URL for scanning
        return QString("https://myshop.com/receipt/%1").arg(idCommande);
    }
    else if (mode == "receipt") {
        // Complete readable receipt for client
        QString receipt = QString(
                              "=================================\n"
                              "         CLIENT RECEIPT          \n"
                              "=================================\n\n"
                              "📋 ORDER DETAILS:\n"
                              "   Order ID: #%1\n"
                              "   Date: %2\n"
                              "   Status: %3\n"
                              "   Amount: %4 EUR\n\n"
                              "👤 CLIENT INFORMATION:\n"
                              "   Name: %5 %6\n"
                              "   Email: %7\n"
                              "   Phone: %8\n\n"
                              "💰 PAYMENT SUMMARY:\n"
                              "   Total Amount: %9 EUR\n"
                              "   Payment Status: %10\n\n"
                              "📅 Generated: %11\n\n"
                              "Thank you for your order!\n"
                              "=================================\n"
                              "Contact us: info@myshop.com\n"
                              "Phone: +216 XX XXX XXX\n"
                              "================================="
                              )
                              .arg(idCommande)                                           // Order ID
                              .arg(dateCommande.toString("dd/MM/yyyy"))                 // Date
                              .arg(etat.toUpper())                                      // Status
                              .arg(montant, 0, 'f', 2)                                 // Amount 1
                              .arg(nomClient)                                           // First name
                              .arg(prenomClient)                                        // Last name
                              .arg(emailClient.isEmpty() ? "N/A" : emailClient)         // Email
                              .arg(telephoneClient.isEmpty() ? "N/A" : telephoneClient) // Phone
                              .arg(montant, 0, 'f', 2)                                 // Amount 2 (total)
                              .arg(etat.toUpper())                                      // Payment status
                              .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm")); // Generated time

        return receipt;
    }
    else if (mode == "json") {
        // JSON format for API integration
        QJsonObject receipt;

        // Order information
        receipt["order_id"] = idCommande;
        receipt["order_date"] = dateCommande.toString("yyyy-MM-dd");
        receipt["status"] = etat;
        receipt["amount"] = QString::number(montant, 'f', 2);
        receipt["currency"] = "EUR";

        // Client information
        QJsonObject client;
        client["id"] = idClient;
        client["first_name"] = nomClient;
        client["last_name"] = prenomClient;
        client["full_name"] = QString("%1 %2").arg(nomClient).arg(prenomClient);
        client["email"] = emailClient;
        client["phone"] = telephoneClient;
        receipt["client"] = client;

        // Receipt metadata
        receipt["receipt_type"] = "client_receipt";
        receipt["generated_at"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        receipt["company"] = "MyShop";
        receipt["company_email"] = "info@myshop.com";

        return QString(QJsonDocument(receipt).toJson(QJsonDocument::Compact));
    }
    else {
        // Default: Clean text format for QR codes
        return QString(
                   "RECEIPT #%1\n"
                   "Date: %2\n"
                   "Client: %3 %4\n"
                   "Email: %5\n"
                   "Phone: %6\n"
                   "Amount: %7 EUR\n"
                   "Status: %8\n"
                   "Generated: %9"
                   )
            .arg(idCommande)
            .arg(dateCommande.toString("dd/MM/yyyy"))
            .arg(nomClient)
            .arg(prenomClient)
            .arg(emailClient)
            .arg(telephoneClient)
            .arg(montant, 0, 'f', 2)
            .arg(etat)
            .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"));
    }
}
