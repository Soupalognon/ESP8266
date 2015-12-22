#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qextserialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    BaudRateType getBaudRateFromString(QString baudRate);

public slots:
    void on_btnconnexion_clicked();
    void sendData();
    void readData();

protected:
    //void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::MainWindow *ui;
    QextSerialPort *port;
};

#endif // MAINWINDOW_H
