#include "networkmanager.h"
#include "ui_networkmanager.h"

NetworkManager::NetworkManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NetworkManager)
    , server(new QTcpServer(this)){
    ui->setupUi(this);

    // Start the server and listen for incoming connections on port 8080
    if (server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server started on port 8080.";
    } else {
        qDebug() << "Server failed to start.";
    }

    // Connect to the new connection signal
    connect(server, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);
}

NetworkManager::~NetworkManager()
{
    delete ui;
}

void NetworkManager::onNewConnection()
{
    // Accept the incoming connection
    QTcpSocket *clientConnection = server->nextPendingConnection();

    connect(clientConnection, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);
    connect(clientConnection, &QTcpSocket::disconnected, this, &NetworkManager::onDisconnected);

    // Send a basic response (HTTP header)
    QByteArray response;
    response.append("HTTP/1.1 200 OK\r\n");
    response.append("Content-Type: text/html; charset=UTF-8\r\n");
    response.append("\r\n");

    // Send the HTML content for the page
    response.append("<html><body><h1>Welcome to My Local Network Server</h1><p>This page is served locally on your network!</p></body></html>");
    clientConnection->write(response);
    clientConnection->flush();
}

void NetworkManager::onReadyRead()
{
    QTcpSocket *clientConnection = qobject_cast<QTcpSocket*>(sender());

    // Read the incoming request
    QByteArray requestData = clientConnection->readAll();
    qDebug() << "Request received:" << requestData;
}

void NetworkManager::onDisconnected()
{
    QTcpSocket *clientConnection = qobject_cast<QTcpSocket*>(sender());
    clientConnection->deleteLater();
}
