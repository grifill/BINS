#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTextBlock>
#include <QSystemTrayIcon>
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QtDebug>
#include <QPaintDevice>
#include <math.h>

#include "QStandardItemModel"
#include "QStandardItem"
#include <QTableWidgetItem>

#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/qserialportglobal.h>

#include <QTime>

#include <stdint.h>

#include "glwidget.h"

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
    void on_refresh_port_button_clicked();
    void delay(int millisecondsToWait);

    void on_open_port_button_clicked();

    void on_close_port_button_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *COM_PORT;
    QByteArray Rxb;
};

#endif // MAINWINDOW_H
