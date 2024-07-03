#include "mainwindow.h"
#include "chatclientgui.h"


std::vector<std::string> tokenizer(std::string str, std::string delimiter)
{
    std::vector<std::string> res;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        res.push_back(token);
    }
    if (!str.empty())
        res.push_back(str);
    return res;
}

std::vector<std::pair<std::string, int>> MainWindow::parse_data_string(QString data)
{
    std::vector<std::pair<std::string, int>> res;

    std::vector<std::string> res_ip_port = tokenizer(data.toStdString(), "\n");

    for(auto &ele: res_ip_port)
    {
        std::vector<std::string> s_ip_port = tokenizer(ele, ",");
        std::pair<std::string, int> ip_port {s_ip_port[0], std::stoi(s_ip_port[1])};
        res.push_back(ip_port);
    }
    return res;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    initGui();
    client_.connectToServer("127.0.0.1", 1234);

    connect(&client_, &ChatClient::availableClientData, [this](QString data)
    {

        list_of_clients_ = parse_data_string(data);
        initGui();
    });
}


void MainWindow::initGui()
{

    if (centralWidget_)
    {
        delete centralWidget_;
    }

    centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);

    // Create vertical layout
    verticalLayout_ = new QVBoxLayout;

    // Create horizontal layout for the two widgets
    horizontalLayout_ = new QHBoxLayout;

    // Create left widget (QLabel)
    leftLabel_ = new QLabel("List Of Login Users", this);

    // Create right widget (QListWidget)
    rightListWidget_ = new QListWidget(this);

    connect(rightListWidget_, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);

    for (auto &client :list_of_clients_)
    {
        rightListWidget_->addItem(client.first.c_str() + QString("  ") + std::to_string(client.second).c_str());

    }

    // Add widgets to the horizontal layout
    horizontalLayout_->addWidget(leftLabel_);
    horizontalLayout_->addWidget(rightListWidget_);
    // Add the horizontal layout to the vertical layout
    verticalLayout_->addLayout(horizontalLayout_);

    // Set the vertical layout as the layout for the central widget
    centralWidget_->setLayout(verticalLayout_);

}

void MainWindow::onItemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::onItemClicked";
    if (item)
    {
        std::string str = item->text().toStdString();
        if (hash_client_windows_.find(str) != hash_client_windows_.end())
        {
            hash_client_windows_[str]->show();
            return;
        }


        auto ret = tokenizer(str, "  ");

        QString ip = ret[0].c_str();

        ChatClientGui *local_chat_client_gui =  new ChatClientGui("127.0.0.1", std::stoi(ret[1])+1, ip, std::stoi(ret[1]));
        ChatClientGui *remote_chat_client_gui =  new ChatClientGui(ip, std::stoi(ret[1]), "127.0.0.1", std::stoi(ret[1])+1);

        chat_window_ = new QWidget();

        QHBoxLayout *layout =  new QHBoxLayout();
        chat_window_->setLayout(layout);
        layout->addWidget(local_chat_client_gui);
        layout->addWidget(remote_chat_client_gui);
        chat_window_->show();
        hash_client_windows_[str] =  chat_window_;
    }
}

MainWindow::~MainWindow() {

    for (auto &[name, gui_client]: hash_client_windows_) {
        delete gui_client;
    }
}
