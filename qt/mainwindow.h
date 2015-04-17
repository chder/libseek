#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <QDebug>

#include "seek.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void doSomething();

private:
    Ui::MainWindow *ui;

    LibSeek::Imager thermal;
    LibSeek::Frame frame;

    QImage image;
    QPixmap pixmap;

    QTimer timer;
    bool liveMode;
};

#endif // MAINWINDOW_H
