#ifndef WORKER2_H
#define WORKER2_H

#include <QObject>
#include <QMutex>
#include <QSharedMemory>
#include <QLocalSocket>

class Worker2 : public QObject
{
    Q_OBJECT

    QMutex mutex;
    QSharedMemory memory;
    QLocalSocket *socket = nullptr;
private slots:
   void printError(QLocalSocket::LocalSocketError);
   void writeToSocket(int num);
public:
    explicit Worker2(QObject *parent = nullptr);
    void readData();
signals:
    void dataRead(const QString &);
    void finished();
};

#endif // WORKER2_H
