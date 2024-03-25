#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTimer* m_timer = nullptr;
};

#endif // MAINWINDOW_H
