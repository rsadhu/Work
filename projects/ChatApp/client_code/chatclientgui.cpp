#include "chatclientgui.h"

ChatClientGui::ChatClientGui(QString local_ip, size_t local_port, QString remote_ip, size_t remote_port,QWidget *parent)
    : QWidget{parent}, chat_client_(local_ip, local_port, remote_ip, remote_port)
{

    connect(&chat_client_, &UdpPeer::dataReceived, [this](QString data, size_t port)
    {
        if (this->hash_[chat_client_.remote_port()])
        {
            QString prev  = this->hash_[chat_client_.remote_port()]->toPlainText();
            this->hash_[chat_client_.remote_port()]->setText(prev+"\n"+data);
        }
    });
    initGui();

}


void ChatClientGui::initGui()
{

    verticalLayout_ = new QVBoxLayout;

    common_chat_area_ = new QTextEdit(this);
    common_chat_area_->setReadOnly(true);
    sender_chat_area_ = new QTextEdit(this);

    hash_[chat_client_.remote_port()] = common_chat_area_;


    // send button
    send_button_ = new QPushButton("send", this);

    connect(send_button_, &QPushButton::clicked, [this]()
    {
        this->chat_client_.sendMessage(sender_chat_area_->toPlainText());
        sender_chat_area_->clear();
    });

    // Add labels to the horizontal layout
    verticalLayout_->addWidget(common_chat_area_,5);
    verticalLayout_->addWidget(sender_chat_area_,1);
    verticalLayout_->addWidget(send_button_);

    // Set the horizontal layout as the layout for the central widget
    this->setLayout(verticalLayout_);
   // this->show();
}

