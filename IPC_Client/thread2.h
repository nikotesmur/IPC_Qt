#ifndef THREAD2_H
#define THREAD2_H

#include <QThread>
#include <QMutex>
#include <QSharedMemory>
#include <QLocalSocket>


class Thread2 : public QThread
{
    Q_OBJECT

    QMutex mutex;
    QSharedMemory memory;

private slots:
   void printError(QLocalSocket::LocalSocketError);
public:
    explicit Thread2(QObject *parent = nullptr);
    void readData();
protected:
    virtual void run() override;
signals:
    void dataRead(const QString &);

};

#endif // THREAD2_H
