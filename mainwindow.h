#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comserial.h"
#include "dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_send_clicked();

    void WriteData(const QByteArray data);

    void ReadData();
 //   void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_action_thoat_triggered();

    void on_action_beca_triggered();

    void on_action_trogiup_triggered();

private:
    Ui::MainWindow *ui;
    QSerialPort *devSerial;
    comserial *procSerial;
    Dialog *dialog;
};
#endif // MAINWINDOW_H
