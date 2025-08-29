// qtsmtpclient.h
#ifndef QTSMTPCLIENT_H
#define QTSMTPCLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QTextStream>
#include <QDebug>

class QtSMTPClient : public QObject {
    Q_OBJECT
public:
    explicit QtSMTPClient(QObject *parent = nullptr);
    void setServer(const QString &host, int port, bool useSsl);
    void setAuth(const QString &username, const QString &password);
    bool sendEmail(const QString &from, const QString &to,
                   const QString &subject, const QString &body);

private:
    QString host;
    int port;
    bool useSsl;
    QString username;
    QString password;

    bool sendCommand(QTextStream &t, QSslSocket &socket, const QString &cmd, const QString &expectedCode = QString());
    bool waitForResponse(QSslSocket &socket, const QString &expectedCode = QString());
};

#endif // QTSMTPCLIENT_H
