#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include "comserial.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
//    void datetime();

private slots:
    void datetime();

    void updateRGB(QString command);

    void timecount();

    void timecount2();

    void prgbar();

    void on_pushButton_batled_clicked();

    void on_pushButton_batdongco_clicked();

    void on_pushButton_10_clicked();

    void on_radioButton_maybom_clicked();

    void on_radioButton_denled_clicked();

    void on_pushButton_xoa_clicked();

    void on_pushButton_tatdongco_clicked();

    void on_pushButton_clicked();

    void on_radioButton_tat_clicked();

    void on_pushButton_batdongco2_clicked();

    void on_pushButton_thoat_clicked();

    void on_pushButton_tat_clicked();

    void on_pushButton_batled_2_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *serial;
    comserial *secprocSerial;
    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    int D;
};

#endif // DIALOG_H
