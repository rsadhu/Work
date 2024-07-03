#ifndef ChatClient_H
#define ChatClient_H

#include <QTcpSocket>

class ChatClient : public QTcpSocket {
    Q_OBJECT

public:
    ChatClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);
signals:
    void availableClientData(QString data);
private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
};

#endif // ChatClient_H
