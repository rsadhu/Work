#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatclient.h"
#include <vector>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>



class ChatClientGui;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initGui();
private slots:
    void onItemClicked(QListWidgetItem *item);
private:
    std::vector<std::pair<std::string, int>> parse_data_string(QString data);
    ChatClient client_;
    std::vector<std::pair<std::string, int>> list_of_clients_;

    // graphical elements
private:
    QWidget *centralWidget_= nullptr;
    QVBoxLayout *verticalLayout_ = nullptr;
    QHBoxLayout *horizontalLayout_ = nullptr;
    QListWidget *rightListWidget_ = nullptr;
    QLabel *leftLabel_ = nullptr;
    std::map<std::string, QWidget*> hash_client_windows_;
    QWidget *chat_window_=nullptr;
};
#endif // MAINWINDOW_H
