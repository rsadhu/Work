#ifndef PEERWIDGET_H
#define PEERWIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class PeerWidget : public QWidget {
    Q_OBJECT

public:
    PeerWidget(size_t port, size_t peerPort, QWidget *parent = nullptr);
    ~PeerWidget();

public slots:
    void readPendingDatagrams();
    void sendDatagram();

private:
    QUdpSocket *socket_ = nullptr;
    QTextEdit *display_ =  nullptr;
    QTextEdit *messageInput_ = nullptr;
    size_t peerPort_;
};

#endif // PEERWIDGET_H
