#include "thread1.h"
#include <QtCore>

void processText(QString &txt)
{
    std::sort(txt.begin(), txt.end(),std::greater<QChar>());
    for(int i=txt.size()-1; i>=0;i--)
    {
        if(i%2!=0)
            txt.replace(i,1,"KB");
    }
}

Thread1::Thread1(QObject *parent) : QThread(parent), memory("thread")
{

}

void Thread1::setData(const QString &text)
{
    mutex.lock();
    data = text;
    mutex.unlock();

    if(isRunning())
        quit();
    start();


}

void Thread1::run()
{
    mutex.lock();
    QString text = data;
    mutex.unlock();

    processText(text);

    if(memory.isAttached())
        memory.detach();

    QBuffer buf;
    buf.open(QBuffer::ReadWrite);
    QDataStream stream(&buf);

    stream << text;

    if (!memory.create(buf.size())) {
        qDebug()<<"Unable to create the memory in thread1";
        return;
    }

    memory.lock();
    memcpy(memory.data(),buf.data().data(),buf.size());
    memory.unlock();
    emit dataReady();

}
