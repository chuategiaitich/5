#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comserial.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    devSerial = new QSerialPort(this);
    procSerial = new comserial(devSerial);
    QStringList DispSerial = procSerial->ConnectedDevices();
    ui->comboBox_port->addItems(DispSerial);
    if(DispSerial.length() > 0)
    {
        ui->pushButton_Connect->setEnabled(true);
        ui->textEdit->append("Cổng port đang mở");
    }
    else
    {
        ui->textEdit->append("Không tìm thấy cổng nào");
    }
    connect(devSerial, SIGNAL(readyRead()), this, SLOT(ReadData()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Connect_clicked()
{

    bool statusOpenSerial;
    statusOpenSerial = procSerial ->Connect(ui->comboBox_port->currentText(), ui->comboBox_port->currentText().toInt());
    if(statusOpenSerial)
    {
        ui->pushButton_Connect->setEnabled(true);
        ui->pushButton_disconnect->setEnabled(false);
        ui->textEdit->append("Kết nối thành công");
    }
    else
    {
        ui->textEdit->append("Kết nối thất bại");
    }
}



void MainWindow::on_pushButton_disconnect_clicked()
{
    bool statusCloseSerial;
    statusCloseSerial = procSerial ->Disconnect();
    if(statusCloseSerial)
    {
        ui->pushButton_Connect->setEnabled(true);
        ui->pushButton_disconnect->setEnabled(false);
        ui->textEdit->append("Ngắt kết nối thành công");
    }
    else
    {
        ui->textEdit->append("Ngắt kết nối thất bại");
    }
}

void MainWindow::ReadData()
{
    QString data = procSerial -> Read();
    qDebug() <<"Input: "<<data<<"\n";
    ui->textEdit->append(data);
    ui->lcdNumber->display(data.toDouble()) ;
}

void MainWindow::WriteData(const QByteArray data){
    procSerial->Write(data);
}

void MainWindow::on_pushButton_send_clicked()
{
    QString cmd = ui->lineEdit->text();
    qDebug() << cmd << "\n";
    WriteData(cmd.toUtf8());
}


//void MainWindow::on_comboBox_currentIndexChanged(int index)
//{
//    procSerial->Connect("com8",index);
//    qDebug() <<index;
//}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)

{
    if(arg1 == ""){
        return;
    }
    int a = arg1.toUInt();
    procSerial->Connect("com8",a);
    qDebug() << a ;
}


void MainWindow::on_action_thoat_triggered()
{
    QApplication::quit();
}


void MainWindow::on_action_beca_triggered()
{
    dialog = new Dialog(this);
    dialog->show();
}


void MainWindow::on_action_trogiup_triggered()
{
    QFile file("C:\\Users\\Admin\\Desktop\\Help.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
//    QMessageBox::about(this, "Các lệnh cơ bản", " a: bật đèn RGB."
//                                                      "\n\n b: tắt đèn RGB."
//                                                      "\n\n o: bơm tự động đầy."
//                                                      "\n\n m: bật máy bơm."
//                                                      "\n\n n: tắt máy bơm.");
}

