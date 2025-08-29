// qtsmtpclient.cpp
#include "QtSMTPClient.h"
#include <QThread>

QtSMTPClient::QtSMTPClient(QObject *parent)
    : QObject(parent), port(465), useSsl(true)
{
}

void QtSMTPClient::setServer(const QString &host, int port, bool useSsl) {
    this->host = host;
    this->port = port;
    this->useSsl = useSsl;
}

void QtSMTPClient::setAuth(const QString &username, const QString &password) {
    this->username = username;
    this->password = password;
}

bool QtSMTPClient::waitForResponse(QSslSocket &socket, const QString &expectedCode) {
    if (!socket.waitForReadyRead(10000)) { // Increased timeout to 10 seconds
        qDebug() << "❌ No response from server";
        return false;
    }

    QByteArray response = socket.readAll();
    QString responseStr = QString::fromUtf8(response).trimmed();
    qDebug() << "SMTP:" << responseStr;

    if (!expectedCode.isEmpty()) {
        return responseStr.startsWith(expectedCode);
    }

    // Check for error codes (4xx, 5xx)
    if (responseStr.startsWith("4") || responseStr.startsWith("5")) {
        qDebug() << "❌ SMTP Error:" << responseStr;
        return false;
    }

    return true;
}

bool QtSMTPClient::sendCommand(QTextStream &t, QSslSocket &socket, const QString &cmd, const QString &expectedCode) {
    if (!cmd.isEmpty()) {
        qDebug() << "→ Sending:" << cmd.left(50) + (cmd.length() > 50 ? "..." : ""); // Log first 50 chars
        t << cmd << "\r\n";
        t.flush();
    }

    return waitForResponse(socket, expectedCode);
}

bool QtSMTPClient::sendEmail(const QString &from, const QString &to,
                             const QString &subject, const QString &body) {

    qDebug() << "🔌 Connecting to" << host << ":" << port << (useSsl ? "(SSL)" : "(STARTTLS)");

    QSslSocket socket;
    socket.setPeerVerifyMode(QSslSocket::VerifyNone); // For Gmail compatibility

    if (useSsl) {
        // Direct SSL connection (port 465)
        socket.connectToHostEncrypted(host, port);
        if (!socket.waitForEncrypted(10000)) {
            qDebug() << "❌ SSL connection failed:" << socket.errorString();
            return false;
        }
        qDebug() << "✅ SSL connected";
    } else {
        // Plain connection then STARTTLS (port 587)
        socket.connectToHost(host, port);
        if (!socket.waitForConnected(10000)) {
            qDebug() << "❌ Connection failed:" << socket.errorString();
            return false;
        }
        qDebug() << "✅ Connected";
    }

    QTextStream t(&socket);

    // 1. Wait for server greeting (220)
    if (!waitForResponse(socket, "220")) {
        qDebug() << "❌ No server greeting";
        return false;
    }

    // 2. Send EHLO
    if (!sendCommand(t, socket, "EHLO localhost", "250")) {
        qDebug() << "❌ EHLO failed";
        return false;
    }

    // 3. STARTTLS if not using direct SSL
    if (!useSsl) {
        if (!sendCommand(t, socket, "STARTTLS", "220")) {
            qDebug() << "❌ STARTTLS command failed";
            return false;
        }

        qDebug() << "🔐 Upgrading to TLS...";
        socket.startClientEncryption();
        if (!socket.waitForEncrypted(10000)) {
            qDebug() << "❌ TLS upgrade failed:" << socket.errorString();
            return false;
        }
        qDebug() << "✅ TLS upgraded";

        // Send EHLO again after TLS upgrade
        if (!sendCommand(t, socket, "EHLO localhost", "250")) {
            qDebug() << "❌ EHLO after TLS failed";
            return false;
        }
    }

    // 4. Authentication
    qDebug() << "🔐 Starting authentication...";
    if (!sendCommand(t, socket, "AUTH LOGIN", "334")) {
        qDebug() << "❌ AUTH LOGIN failed";
        return false;
    }

    // Send username (base64 encoded)
    QString usernameB64 = username.toUtf8().toBase64();
    if (!sendCommand(t, socket, usernameB64, "334")) {
        qDebug() << "❌ Username authentication failed";
        return false;
    }

    // Send password (base64 encoded)
    QString passwordB64 = password.toUtf8().toBase64();
    if (!sendCommand(t, socket, passwordB64, "235")) {
        qDebug() << "❌ Password authentication failed";
        return false;
    }
    qDebug() << "✅ Authentication successful";

    // 5. Send email
    if (!sendCommand(t, socket, "MAIL FROM:<" + from + ">", "250")) {
        qDebug() << "❌ MAIL FROM failed";
        return false;
    }

    if (!sendCommand(t, socket, "RCPT TO:<" + to + ">", "250")) {
        qDebug() << "❌ RCPT TO failed";
        return false;
    }

    if (!sendCommand(t, socket, "DATA", "354")) {
        qDebug() << "❌ DATA command failed";
        return false;
    }

    // Send email headers and body
    QString message;
    message += "From: " + from + "\r\n";
    message += "To: " + to + "\r\n";
    message += "Subject: " + subject + "\r\n";
    message += "MIME-Version: 1.0\r\n";
    message += "Content-Type: text/html; charset=UTF-8\r\n";
    message += "\r\n";
    message += body + "\r\n";
    message += "."; // End of message marker

    if (!sendCommand(t, socket, message, "250")) {
        qDebug() << "❌ Message sending failed";
        return false;
    }

    // 6. Quit
    sendCommand(t, socket, "QUIT", "221");
    socket.disconnectFromHost();

    qDebug() << "✅ Email sent successfully";
    return true;
}
