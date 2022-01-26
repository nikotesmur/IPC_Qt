#ifndef THREAD1_H
#define THREAD1_H

#include <QThread>
#include <QMutex>
#include <QSharedMemory>

class Thread1 : public QThread
{
    Q_OBJECT
private:
    QString data;
    QMutex mutex;
    QSharedMemory memory;
public:
    explicit Thread1(QObject *parent = nullptr);
    void setData(const QString &text);

    // QThread interface
protected:
    virtual void run() override;
signals:
    void dataReady();
};

#endif // THREAD1_H
