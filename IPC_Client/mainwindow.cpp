#include "mainwindow.h"
#include "thread1.h"
#include "worker2.h"

#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    line_input = new QLineEdit(this);
    line_output = new QLineEdit(this);
    QFormLayout *layout = new QFormLayout;
    layout->addRow("Input numbers",line_input);
    layout->addRow("Result",line_output);
    auto w = new QWidget(this);
    w->setLayout(layout);
    setCentralWidget(w);
    line_input->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d{0,64}"),this));
    thread1 = new Thread1(this);

    thread2 = new QThread(this);

    worker2 = new Worker2();

    worker2->moveToThread(thread2);

    connect(line_input,&QLineEdit::textEdited,thread1, &Thread1::setData);

    connect(thread1, SIGNAL(dataReady()), thread2, SLOT(start()));
    connect(thread2, &QThread::started, worker2, &Worker2::readData);

    connect(worker2, &Worker2::finished, thread2, &QThread::quit);

    connect(worker2, &Worker2::dataRead, line_output, &QLineEdit::setText);
}

MainWindow::~MainWindow()
{
    thread1->quit();
    thread1->deleteLater();

    thread2->quit();
    thread2->deleteLater();
}

