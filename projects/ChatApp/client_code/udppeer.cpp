#include "udppeer.h"
#include <QHostAddress>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>

UdpPeer::UdpPeer(QString local_ip, size_t local_port, QString remote_ip, size_t remote_port, QObject *parent)
    : QUdpSocket(parent){

    local_ip_ = local_ip;
    local_port_ = local_port;

    remote_ip_ = remote_ip;
    remote_port_ = remote_port;


    this->bind(QHostAddress::Any, local_port_);
    connect(this, &QUdpSocket::readyRead, this, &UdpPeer::onReadyRead);
}

void UdpPeer::sendMessage(const QString &message) {
    QByteArray datagram;
    qDebug() << "Sent message from" << remote_ip_ << ":" << remote_port_ << " - " << message;

    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << message;
    this->writeDatagram(datagram, QHostAddress(remote_ip_), remote_port_);
}

void UdpPeer::onReadyRead() {
    while (this->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        this->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QDataStream in(&datagram, QIODevice::ReadOnly);
        QString message;
        in >> message;
        dataReceived(message, static_cast<size_t>(senderPort));
        qDebug() << "Received message from" << sender.toString() << ":" << senderPort << " - " << message;
    }
}
