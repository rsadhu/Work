#include "chatserver.h"

#include <QHostAddress>
#include <QDebug>


ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {}

bool ChatServer::startServer(quint16 port) {
    return listen(QHostAddress::Any, port);
}

void ChatServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        connect(clientSocket, &QTcpSocket::connected, this, &ChatServer::onClientConnected);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::onClientDisconnected);
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);

        logClientInfo(clientSocket);
    } else {
        delete clientSocket;
    }
}

void ChatServer::onClientConnected() {
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    logClientInfo(client);
}

void ChatServer::removeClient(QTcpSocket *client)
{
    list_of_clients_.erase(client);
}

void ChatServer::onClientDisconnected() {
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    removeClient(client);
    qDebug() << "Client disconnected:" << client->peerAddress().toString() << ":" << client->peerPort();
    client->deleteLater();

}

void ChatServer::onReadyRead() {
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = client->readAll();

    qDebug() << "Received data from" << client->peerAddress().toString() << ":" << client->peerPort() << ":" << data;

    // Echo the data back to the client
    client->write(data);
}

void ChatServer::logClientInfo(QTcpSocket *client) {

    if (list_of_clients_.find(client) != list_of_clients_.end())
        return ;

    qDebug() << "Client connected:" << client->peerAddress().toString() << ":" << client->peerPort();

    list_of_clients_.insert(client);

    qDebug()<<"number of clients are "<< list_of_clients_.size();

    QString data;
    for(auto client: list_of_clients_)
    {
        QString ip = client->peerAddress().toString();

        QString substr = "::ffff:";
        if (ip.contains(substr)) {
            ip =  ip.toStdString().substr(substr.length()).c_str();
        }

        data += ip;
        data += ",";
        data += std::to_string(client->peerPort()).c_str();
        data +="\n";
    }
    //send the list of clients to the newly connected client
    for (auto each_client: list_of_clients_)
    {
        each_client->write(data.toStdString().c_str());
    }
}


