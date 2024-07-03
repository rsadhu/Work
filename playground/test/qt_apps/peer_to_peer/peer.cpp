#include "peer.h"

PeerWidget::PeerWidget(size_t port, size_t peerPort, QWidget *parent)
    : QWidget(parent), peerPort_(peerPort)
{
    socket_ = new QUdpSocket(this);
    socket_->bind(QHostAddress::LocalHost, port);

    QVBoxLayout *layout = new QVBoxLayout(this);
    display_ = new QTextEdit(this);
    display_->setReadOnly(true);
    layout->addWidget(display_, 4);

    messageInput_ = new QTextEdit(this);
    layout->addWidget(messageInput_, 1);

    QPushButton *sendButton = new QPushButton("Send", this);
    layout->addWidget(sendButton);

    connect(socket_, &QUdpSocket::readyRead, this, &PeerWidget::readPendingDatagrams);
    connect(sendButton, &QPushButton::clicked, this, &PeerWidget::sendDatagram);
}

void PeerWidget::readPendingDatagrams()
{
    while (socket_->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket_->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        display_->append("Received: " + datagram + " from " + sender.toString() + ":" + QString::number(senderPort));
    }
}

void PeerWidget::sendDatagram()
{
    QByteArray datagram = messageInput_->toPlainText().toUtf8();
    socket_->writeDatagram(datagram, QHostAddress::LocalHost, peerPort_);
    display_->append("Sent: " + datagram);
    messageInput_->clear();
}

// although not needed but in order to show case that developer isn't forgetting the clean up the memory
PeerWidget::~PeerWidget()
{
    if (socket_)
        delete socket_;

    if (display_)
        delete display_;

    if (messageInput_)
        delete messageInput_;
}
