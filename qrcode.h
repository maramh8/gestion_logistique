#ifndef QRCODE_H
#define QRCODE_H

#include <QString>
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDate>
#include <QDateTime>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QTimer>
#include <vector>
#include <cstdint>

// QR Code generator namespace
namespace qrcodegen {
class QrCode {
public:
    enum Ecc {
        LOW = 0,
        MEDIUM = 1,
        QUARTILE = 2,
        HIGH = 3
    };

    static QrCode encodeText(const char *text, Ecc ecl);
    int getSize() const;
    bool getModule(int x, int y) const;

private:
    std::vector<std::vector<bool>> modules;
    std::vector<std::vector<bool>> isFunction;
    int size;
    int version;
    Ecc errorCorrectionLevel;
    int mask;

    QrCode(int ver, Ecc ecl, const std::vector<uint8_t> &dataCodewords, int mask);

    static std::vector<uint8_t> encodeSegments(const std::vector<uint8_t> &data, Ecc ecl, int version);
    static int getCapacity(int version, Ecc ecl);
    static int getNumDataCodewords(int ver, Ecc ecl);
    static std::vector<int> getAlignmentPatternPositions(int ver);

    void drawFunctionPatterns();
    void drawFormatBits(Ecc ecl, int mask);
    void drawVersion();
    void drawFinderPattern(int x, int y);
    void drawFinderSeparator(int x, int y);
    void drawAlignmentPattern(int x, int y);
    void drawCodewords(const std::vector<uint8_t> &data);
    void applyMask(int mask);
    void setFunctionModule(int x, int y, bool isDark);
    int calculatePenalty();
};
}

class QrCodeGenerator {
public:
    // Original method (uses custom implementation)
    static QImage generateQR(const QString& data, int size = 300);

    // Online QR generation (reliable)
    static QImage generateQROnline(const QString& data, int size = 300);

    // Simple fallback method
    static QImage generateQRSimple(const QString& data, int size = 300);

    // Receipt creation method
    static QString createOrderReceipt(int idCommande,
                                      const QDate& dateCommande,
                                      const QString& etat,
                                      double montant,
                                      int idClient,
                                      const QString& nomClient,
                                      const QString& prenomClient,
                                      const QString& emailClient,
                                      const QString& telephoneClient,
                                      const QString& mode);

private:
    static QImage createQrImage(const qrcodegen::QrCode& qr, int scale, int border);
};

#endif // QRCODE_H
