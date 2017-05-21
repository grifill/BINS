#include "mainwindow.h"
#include "ui_mainwindow.h"

//VAR
bool com_state = false;
bool com_already = false;


QStandardItemModel *table_proto = new QStandardItemModel;
QStandardItem *item,*item2;
QStringList horizontalHeader;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Ico.ico"));
    //ui->model->setAccels(ui->x_sb->value(), ui->y_sb->value(), ui->z_sb->value());
    ui->model->setPlateRotations(ui->pitch_sb->value(), ui->pitch_sb_2->value());
    /******************************************************
    *              INIT INTERFACE
    * *****************************************************/
    ui->console_com->setText(">>> COM-Порт не выбран");
    // COM search part --------------------------------------
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString com = QObject::tr("")+info.portName();
        QString string_info =
                QObject::tr(" ") + info.portName()
                + QObject::tr(" ")+ info.description()
                + QObject::tr(" ") + info.manufacturer()
                + "\n";
        ui->com_text->append(string_info);
        ui->com_box->addItem(com);
        ui->console_com->setText(">>> COM-Порт закрыт");
    }
    // Protocol Table part ------------------------------------
    table_proto->setColumnCount(2);
    table_proto->setRowCount(10);
    // Horizontal
    horizontalHeader.append("Параметры");
    horizontalHeader.append("Текущее значение");
    table_proto->setHorizontalHeaderLabels(horizontalHeader);
    // Vertical
    //QStringList verticalHeader;
    //verticalHeader.
    //verticalHeader.append("Время,с");
    //verticalHeader.append("Угол тангажа,град");
    //verticalHeader.append("Угол крена,град");
    //table_proto->setVerticalHeaderLabels(verticalHeader);

    // Text
    //table_proto->index(2,2)->setText("Время, c");
    //table_proto->setItem(1,);

    item = new QStandardItem(QString("Время, c"));
    item2 = new QStandardItem(QString("Время, c"));
    table_proto->setItem(0, 0, item);

    // View
    ui->table_proto->setModel(table_proto);
    ui->table_proto->resizeColumnsToContents();
    ui->table_proto->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table_proto->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);




    // COM
    COM_PORT = new QSerialPort(this);
}

// delay
void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Refresh button ---------------------------------------------------------------------
void MainWindow::on_refresh_port_button_clicked()
{
    ui->com_text->clear();
    ui->com_box->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString com = QObject::tr("")+info.portName();
        QString string_info =
                QObject::tr(" ") + info.portName()
                + QObject::tr(" ")+ info.description()
                + QObject::tr(" ") + info.manufacturer()
                + "\n";
        ui->com_text->append(string_info);
        ui->com_box->addItem(com);
    }
}
// Open button ------------------------------------------------------------------------
void MainWindow::on_open_port_button_clicked()
{
    if (com_already==false)
    {
        QString com_name=ui->com_box->currentText();
        COM_PORT->setPortName(com_name);
        COM_PORT->setBaudRate(115200);
        COM_PORT->setDataBits(QSerialPort::Data8)  ;
        COM_PORT->setParity(QSerialPort::NoParity);
        COM_PORT->setStopBits(QSerialPort::OneStop);
        COM_PORT->setFlowControl(QSerialPort::NoFlowControl) ;
        COM_PORT->open(QIODevice::ReadWrite);
        connect(COM_PORT,SIGNAL(readyRead()), this, SLOT(serialReceived()));//***** Handler work? if need (=@_@=)
        /*connect(ui->listWidget->model(),
                SIGNAL(rowsInserted ( const QModelIndex &, int, int ) ),
                ui->listWidget,
                SLOT(scrollToBottom ())
                );*/
        com_state = COM_PORT->isOpen();
        com_state = COM_PORT->clear();
        if (com_state==true)
        {
            ui->console_com->setText(">>> COM-Порт открыт");
        }
        else
        {
            ui->console_com->setText(">>> COM-Порт закрыт");
            com_already=true;
        }
    }
}
// Close button ------------------------------------------------------------------------
void MainWindow::on_close_port_button_clicked()
{
    com_already=false;
    COM_PORT->close();
    com_state = COM_PORT->isOpen();
    //table_proto->setItem(3, 1, item2);
    //table_proto->set
}
