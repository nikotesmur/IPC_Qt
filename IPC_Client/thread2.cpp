#include "thread2.h"
#include <QtCore>
#include <QLocalSocket>



void Thread2::printError(QLocalSocket::LocalSocketError error)
{
    qDebug () << error;
}

Thread2::Thread2(QObject *parent) : QThread(parent), memory("thread")
{


}

void Thread2::readData()
{
    if(!this->isRunning())
        start();
}

void Thread2::run()
{

}
