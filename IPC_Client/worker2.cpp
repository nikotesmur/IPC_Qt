#include "worker2.h"

#include <QtCore>

int getSum(const QString &txt)
{
    int sum = 0;
    for(auto c:txt)
        sum+=QString(c).toInt();
    return sum;

}

void Worker2::printError(QLocalSocket::LocalSocketError error)
{
    qDebug () << error;
}

void Worker2::writeToSocket(int num)
{
    socket = new QLocalSocket(this);
    connect(socket,SIGNAL(errorOccurred(QLocalSocket::LocalSocketError)), this,
            SLOT(printError(QLocalSocket::LocalSocketError)));
    socket->connectToServer("socketserver");

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << num;
    socket->write(data);
}

Worker2::Worker2(QObject *parent) : QObject(parent), memory("thread")
{

}

void Worker2::readData()
{
    if(!memory.isAttached()) {
        if (!memory.attach()) {
            qDebug()<<"Unable to attach to shared memory";
            emit finished();
            return;
        }
    }

    QString text;

    QBuffer buf;
    QDataStream stream(&buf);

    memory.lock();
    buf.setData(static_cast<const char*>(memory.constData()),memory.size());
    buf.open(QBuffer::ReadOnly);
    stream >> text;
    memory.unlock();

    memory.detach();
    emit dataRead(text);


    int num = getSum(text);
    writeToSocket(num);

    emit finished();
}
