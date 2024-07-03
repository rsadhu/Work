#ifndef UDPPEER_H
#define UDPPEER_H

#include <QUdpSocket>

class UdpPeer : public QUdpSocket
{
    Q_OBJECT
public:
    UdpPeer(QString local_ip, size_t local_port, QString remote_ip, size_t remote_port, QObject *parent = nullptr);
    void sendMessage(const QString &message);

    size_t remote_port() const{
        return remote_port_;
    }

    QString  remote_ip() const{
        return remote_ip_;
    }


    size_t local_port() const{
        return local_port_;
    }

    QString  local_ip() const{
        return local_ip_;
    }

private slots:
    void onReadyRead();
signals:
    void dataReceived(QString, size_t portnum);
private:

    QString remote_ip_;
    int remote_port_;

    QString local_ip_;
    int local_port_;
};

#endif // UDPPEER_H
