#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
class Thread1;
class Thread2;
class Worker2;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QLineEdit *line_input;
    QLineEdit *line_output;
    Thread1 *thread1;
    QThread *thread2;
    Worker2 *worker2;

private:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
