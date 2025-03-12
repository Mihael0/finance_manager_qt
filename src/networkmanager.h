#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class NetworkManager;
}

class NetworkManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetworkManager(QWidget *parent = nullptr);
    ~NetworkManager();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    Ui::NetworkManager *ui;
    QTcpServer *server;
};

#endif // NETWORKMANAGER_H
