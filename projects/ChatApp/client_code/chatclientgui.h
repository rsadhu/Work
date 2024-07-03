#ifndef CHATCLIENTGUI_H
#define CHATCLIENTGUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

#include "udppeer.h"


class ChatClientGui : public QWidget
{
    Q_OBJECT
public:
    explicit ChatClientGui(QString local_ip, size_t local_port, QString remote_ip, size_t remote_port,QWidget *parent = nullptr);
    void initGui();

private:
    UdpPeer chat_client_;

private:
    QTextEdit *common_chat_area_ =  nullptr;
    QTextEdit *sender_chat_area_ =  nullptr;

    QVBoxLayout *verticalLayout_ = nullptr;
    QPushButton *send_button_ =  nullptr;
    std::map<size_t, QTextEdit*> hash_;
};

#endif // CHATCLIENTGUI_H
