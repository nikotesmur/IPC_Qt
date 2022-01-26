#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLocalServer>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPlainTextEdit *text;
    QLocalServer *server;

private slots:
    void getSocket();
    void readSocket();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
