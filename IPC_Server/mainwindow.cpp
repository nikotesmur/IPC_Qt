#include "mainwindow.h"
#include <QLocalSocket>

void MainWindow::getSocket()
{
    QLocalSocket *socket = server->nextPendingConnection();
    if(!socket) {
        qDebug()<<"unable retrieve socket from next pending connection";
        return;
    }

    connect(socket,SIGNAL(readyRead()), this, SLOT(readSocket()));

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    connect(socket, &QLocalSocket::stateChanged,
            [=](QLocalSocket::LocalSocketState state){qDebug()<<socket<<state;});
    connect(socket, &QLocalSocket::errorOccurred,
            [=](QLocalSocket::LocalSocketError error){qDebug()<<socket<<error;});
}

void MainWindow::readSocket()
{
    QLocalSocket *socket = dynamic_cast<QLocalSocket *>(sender());
    if(!socket)
        return;

    QDataStream stream(socket);
    int num;

    if(socket->bytesAvailable() < sizeof(int)) return;

    stream >> num;

    if(num>99 && num%32==0)
        text->appendPlainText("Wrong data");
    else
        text->appendPlainText(QString::number(num));

    socket->disconnectFromServer();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    text = new QPlainTextEdit(this);
    setCentralWidget(text);
    server = new QLocalServer(this);
    server->listen("socketserver");
    connect(server, SIGNAL(newConnection()),this, SLOT(getSocket()));

}

MainWindow::~MainWindow()
{
}

