#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"controlpanel.h"
#include"define.h"
#include "detectxml.h"
#include <QFileDialog>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include"about.h"
#include<QMessageBox>
#include<QDesktopServices>

#define CORRECTINSTRUCT(l) "<font color=\"blue\">"+QString("÷°∫¨“Â£∫")+":"+l+"</font>"
#define INCORRECTINSTRUCT(l) "<font color=\"red\">"+QTime::currentTime().toString()+":"+l+"</font>"
#define RECEIVEDFRAME(l) "<font color=\"black\"><b>"+QString(" ’µΩ÷°£∫")+QTime::currentTime().toString()+":"+l+"</b></font>"
#define SENDFRAME(l) "<font color=\"blue\"><b>"+QString("∑¢ÀÕ÷°£∫")+QTime::currentTime().toString()+":"+l+"</b></font>"
#define ALARMFRAME(l) "<font color=\"gray\"><b>"+QString("±®æØ÷°£∫")+QTime::currentTime().toString()+":"+l+"</b></font>"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ControlPanel *controlPanel;
    QSerialPort s;
private slots:
    void slotOpenXmlFile(bool);
    void slotUpdateSerialInfo();
    void slotSendReport(uchar *add, uint8_t len);
    void slotPrintReceiveLog(QString log);
    void slotPrintLog(QString log,uint8_t type);
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_clicked(bool checked);
    void slotAbout(bool);

    void on_pushButton_2_clicked();

    void on_serialCombox_activated();

    void on_checkBox_2_clicked(bool checked);

    void slotHelp(bool);

    void on_ResetpushButton_clicked();
    void slotReadyRead();

signals:
    void signaReadyRead(QByteArray);
    void signalLog(QString log);
    void signalReportTimeChanged(int);
    void signalIsNeedPrintRF(bool); //ª„±®÷°
    void signalIsNeedPrintQueryState(bool); //≤È—Ø◊¥Ã¨÷°

};

#endif // MAINWINDOW_H
