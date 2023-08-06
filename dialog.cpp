#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>
//#include <QtCharts>
//#include <QChartViews>
//#include <QBarSet>
//#include <QBarSeries>
#include <QApplication>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    secprocSerial = new comserial(serial);

    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer->setInterval(1000);
    timer2->setInterval(1000);timer2->start();
    timer3->setInterval(1000);

    connect (timer, SIGNAL(timeout()), this, SLOT(timecount()));
    connect (timer, SIGNAL(timeout()), this, SLOT(prgbar()));

    connect (timer3, SIGNAL(timeout()), this, SLOT(timecount2()));

    connect (timer2, SIGNAL(timeout()), this, SLOT(datetime()));

    ui->spinBox  ->setMinimum(0);   ui->spinBox  ->setMaximum(60);
    ui->spinBox_2->setMinimum(0);   ui->spinBox_2->setMaximum(60);
    ui->spinBox_3->setMinimum(0);   ui->spinBox_3->setMaximum(24);
    ui->spinBox_6->setMinimum(0);   ui->spinBox_6->setMaximum(60);
    ui->spinBox_5->setMinimum(0);   ui->spinBox_5->setMaximum(60);
    ui->spinBox_4->setMinimum(0);   ui->spinBox_4->setMaximum(24);

    ui->groupBox_denled->hide();
    ui->groupBox_maybom->hide();
}


void Dialog::timecount()                                    //  Đồng hồ bấm giờ cho động cơ
{
    int a=ui->spinBox->value();//giây
    int b=ui->spinBox_2->value();//phút
    int c=ui->spinBox_3->value();//giờ
    int A=ui->label_time->text().toInt();//giờ
    int B=ui->label_time_3->text().toInt();//phút
    int C=ui->label_time_5->text().toInt();//giây
    int d=a+60*b+60*60*c;
    int D=C+60*B+60*60*A;
    if(D<d)
    {
    ui->lcdNumber->display(d-D);
    ui->textEdit->setText(QString("-Đã bật động cơ"
                                "\n-Động cơ sẽ tắt sau %1 giây").arg(d-D));
    }
    else
    {
        timer->stop();
        ui->lcdNumber->display(0);
        ui->progressBar->setValue(ui->progressBar->maximum());
        ui->textEdit->setText("-Đã tắt động cơ.");
    }
}


void Dialog::on_pushButton_xoa_clicked()                    // Xoá giá trị thời gian nhập vào máy bơm
{
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
}


void Dialog::on_pushButton_tatdongco_clicked()              // Tắt động cơ
{
    ui->lcdNumber->display(0);
    ui->progressBar->setValue(0);
    timer->stop();
    ui->textEdit->setText("-Đã tắt động cơ.");
}


void Dialog::on_pushButton_batdongco_clicked()              // Bật động cơ (kèm hẹn giờ)
{
    int A=ui->label_time->text().toInt();//giờ
    int B=ui->label_time_3->text().toInt();//phút
    int C=ui->label_time_5->text().toInt();//giây
    D=60*60*A+60*B+C;
    if(timer->isActive())
    {
        timer->stop();
        timer2->stop();
        ui->textEdit->setText("-Tạm dừng động cơ.");
        ui->pushButton_batdongco->setText("Bật động cơ");
    }
    else
    {
        timer->start();
        timer2->start();
        ui->pushButton_batdongco->setText("Dừng động cơ");
    }
}


void Dialog::on_pushButton_batdongco2_clicked()             // Bật động cơ (không hẹn giờ)
{
    ui->progressBar->setMinimum(0);ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);
    ui->textEdit->setText("-Đã bật động cơ.");
}


void Dialog::prgbar()                                       //  progress bar
{
    int a=ui->spinBox->value();//giây
    int b=ui->spinBox_2->value();//phút
    int c=ui->spinBox_3->value();//giờ
    int d=a+60*b+60*60*c;
    int e=d-D;
    ui->progressBar->setMinimum(0);ui->progressBar->setMaximum(e);
    int q;
    q=ui->progressBar->value();
    q++;
    ui->progressBar->setValue(q);
}


Dialog::~Dialog()                                           // Hàm huỷ
{
    delete ui;
}


void Dialog::datetime()                                     // Thời gian thực
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext1 = dateTime.toString("HH");
    QString datetimetext2 = dateTime.toString("mm");
    QString datetimetext3 = dateTime.toString("ss");
    ui->label_time->setText(datetimetext1);
    ui->label_time_2->setText(":");
    ui->label_time_3->setText(datetimetext2);
    ui->label_time_4->setText(":");
    ui->label_time_5->setText(datetimetext3);
}


void Dialog::updateRGB(QString command)                     // Viết kết quả vào serial
{
    if(serial->isWritable())
    {
        serial->write(command.toStdString().c_str());
    }
    else
    {
        qDebug() << "Coudn't write to serial!";
    }
}


void Dialog::on_pushButton_batled_2_clicked()               // Bật đèn led kèm hẹn giờ
{
    if(timer3->isActive())
    {
        timer3->stop();
        ui->textEdit->setText("-Tạm dừng bật đèn.");
        ui->pushButton_batdongco->setText("Bật đèn");
    }
    else
    {
        timer3->start();
        ui->pushButton_batdongco->setText("Tắt đèn");
    }
}


void Dialog:: timecount2()                                  // Đồng hồ bấm giờ cho đèn led
{
    int j= ui->red_slider->value();
    int k= ui->green_slider->value();
    int l= ui->blue_slider->value();
    int a=ui->spinBox_6->value();//giây
    int b=ui->spinBox_5->value();//phút
    int c=ui->spinBox_4->value();//giờ
    int A=ui->label_time->text().toInt();//giờ
    int B=ui->label_time_3->text().toInt();//phút
    int C=ui->label_time_5->text().toInt();//giây
    int d=a+60*b+60*60*c;
    int D=C+60*B+60*60*A;
    if(D<d)
    {
        Dialog::updateRGB(QString("Đỏ: %1"
                                "\nXanh lá: %2"
                                "\nXanh dương: %3").arg(j).arg(k).arg(l));
        ui->textEdit->setText(QString("-Đã bật đèn led."
                                    "\n-Đèn led sẽ tắt sau %4 giây"
                                    "\n-Màu sắc hiển thị:"
                                    "\nĐỏ: %1"
                                    "\nXanh lá: %2"
                                    "\nXanh dương: %3").arg(j).arg(k).arg(l).arg(d-D));
    }
    else
    {
        timer3->stop();
        Dialog::updateRGB("Đỏ: 0"
                        "\nXanh lá: 0"
                        "\nXanh dương: 0");
        ui->textEdit->setText("-Đã tắt đèn led.");
    }
}


void Dialog::on_pushButton_batled_clicked()                 // Bật đèn led
{
    int a= ui->red_slider->value();
    int b= ui->green_slider->value();
    int c= ui->blue_slider->value();
    Dialog::updateRGB(QString("Đỏ: %1"
                            "\nXanh lá: %2"
                            "\nXanh dương: %3").arg(a).arg(b).arg(c));
    ui->textEdit->setText(QString("-Đã bật đèn led."
                                "\n-Màu sắc hiển thị:"
                                "\nĐỏ: %1"
                                "\nXanh lá: %2"
                                "\nXanh dương: %3").arg(a).arg(b).arg(c));
}


void Dialog::on_pushButton_10_clicked()                     //Tắt đèn led
{
    timer3->stop();
    ui->textEdit->setText("-Đã tắt đèn led.");
}


void Dialog::on_pushButton_clicked()                        //xoá giá trị nhập đèn led
{
    ui->red_slider->setSliderPosition(0);
    ui->green_slider->setSliderPosition(0);
    ui->blue_slider->setSliderPosition(0);
    ui->spinBox_4->setValue(0);
    ui->spinBox_5->setValue(0);
    ui->spinBox_6->setValue(0);
}


void Dialog::on_radioButton_maybom_clicked()                //Mở menu động cơ
{
    ui->groupBox_denled->hide();
    ui->groupBox_maybom->show();
}


void Dialog::on_radioButton_denled_clicked()                //Mở menu đèn led
{
    ui->groupBox_maybom->hide();
    ui->groupBox_denled->show();
}


void Dialog::on_radioButton_tat_clicked()                   //Ẩn menu động cơ và đèn led
{
    ui->groupBox_maybom->hide();
    ui->groupBox_denled->hide();
}


void Dialog::on_pushButton_thoat_clicked()                  //Thoát
{
    QMessageBox::StandardButton reply = QMessageBox::question
        (this,"Thông báo","Bạn có muốn thoát không?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
    qApp->closeAllWindows();
    }
    else{}
}


void Dialog::on_pushButton_tat_clicked()                    // tắt chương trình
{
    timer->stop();
    timer2->stop();
    timer3->stop();
    ui->label_time->setText("HH");
    ui->label_time_3->setText("mm");
    ui->label_time_5->setText("ss");
    ui->textEdit->setText("-Đã tắt động cơ."
                        "\n-Đã tắt đèn led.");
    ui->radioButton_tat->setChecked(true);
    ui->groupBox_denled->hide();
    ui->groupBox_maybom->hide();
}
