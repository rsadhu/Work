#include "chatclient.h"
#include <QDebug>


ChatClient::ChatClient(QObject *parent) : QTcpSocket(parent) {
    connect(this, &QTcpSocket::connected, this, &ChatClient::onConnected);
    connect(this, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &ChatClient::onDisconnected);
    connect(this, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), this, &ChatClient::onError);
}

void ChatClient::connectToServer(const QString &host, quint16 port) {
    qDebug() << "Connecting to server...";
    this->connectToHost(host, port);
}

void ChatClient::sendMessage(const QString &message) {
    if (this->state() == QAbstractSocket::ConnectedState) {
        this->write(message.toUtf8());
        this->flush();
    } else {
        qWarning() << "Not connected to server.";
    }
}

void ChatClient::onConnected() {
    qDebug() << "Connected to server.";
}

void ChatClient::onReadyRead() {
    QByteArray data = this->readAll();
    emit availableClientData(data);
}

void ChatClient::onDisconnected() {
    qDebug() << "Disconnected from server.";
}

void ChatClient::onError(QAbstractSocket::SocketError socketError) {
    qCritical() << "Socket error:" << socketError << this->errorString();
}
