#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <set>


class ChatServer : public QTcpServer {
    Q_OBJECT

public:
    ChatServer(QObject *parent = nullptr);
    bool startServer(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onClientConnected();
    void onClientDisconnected();
    void onReadyRead();

private:
    void removeClient(QTcpSocket *client);
    void logClientInfo(QTcpSocket *client);
    std::set<QTcpSocket*> list_of_clients_;
};




#endif // CHATSERVER_H
