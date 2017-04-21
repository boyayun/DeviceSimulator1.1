#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->spinBox->setValue(10);
    this->setWindowTitle("设备模拟器V1.2");
    controlPanel = NULL;
    slotUpdateSerialInfo();
    this->setGeometry(100,100,800,600);
    connect(&s, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(this->ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(slotOpenXmlFile(bool)));
    connect(this->ui->actionVersion,SIGNAL(triggered(bool)),this,SLOT(slotAbout(bool)));
    connect(this->ui->actionHelp,SIGNAL(triggered(bool)),this,SLOT(slotHelp(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenXmlFile(bool)
{
    QDEBUG()<<QString::fromUtf8("打开设备描述文件");
    QString filePath = QFileDialog::getOpenFileName(this,"打开设备描述文件",QDir::currentPath(),"Xml(*.xml)");
    QDEBUG()<< filePath;
    if(!filePath.isEmpty())
    {
        DetectXml d(filePath);
        this->setWindowTitle(d.getDeviceName());
        QList<FunctionItem*>list = d.getFunList();
        this->controlPanel = new ControlPanel(list);
        connect(this, SIGNAL(signaReadyRead(QByteArray)), controlPanel, SLOT(slotReceivedFrame(QByteArray)));
        connect(controlPanel,SIGNAL(signalSendReport(uchar*, uint8_t)),this,SLOT(slotSendReport(uchar*, uint8_t)));
        connect(controlPanel,SIGNAL(signallog(QString,uint8_t)),this,SLOT(slotPrintLog(QString,uint8_t)));
        connect(this,SIGNAL(signalReportTimeChanged(int)),controlPanel,SLOT(slotReportTimeChanged(int)));
        connect(this,SIGNAL(signalIsNeedPrintRF(bool)),controlPanel,SLOT(slotIsNeedPrintRF(bool)));
        connect(this,SIGNAL(signalIsNeedPrintQueryState(bool)),controlPanel,SLOT(slotIsNeedPrintQueryState(bool)));
        this->ui->scrollArea->setWidget(controlPanel);
    }
}

void MainWindow::slotSendReport(uchar *add, uint8_t len)
{
   QDEBUG()<<len;
   s.write((char*)add, len);
}

void MainWindow::slotPrintReceiveLog(QString log)
{

    this->ui->receiveDisplay->append(log);
}

void MainWindow::slotPrintLog(QString log, uint8_t type)
{
   this->ui->receiveDisplay->textCursor().movePosition(QTextCursor::End);
   if(type == 1)
   {
       this->ui->receiveDisplay->append(RECEIVEDFRAME(log));
   }
   else if(type ==2)
   {
       this->ui->receiveDisplay->append(CORRECTINSTRUCT(log));
   }
   else if(type == 3)
   {
       this->ui->receiveDisplay->append(INCORRECTINSTRUCT(log));
   }
   else if(type == 4)
   {
       this->ui->receiveDisplay->append(SENDFRAME(log));
   }
   else if(type == 5)
   {
       this->ui->receiveDisplay->append(ALARMFRAME(log));
   }
   else if(type == 6)
   {
       this->ui->receiveDisplay->append(QTime::currentTime().toString()+":"+log);
   }
}

void MainWindow::on_pushButton_clicked()
{
   this->ui->receiveDisplay->clear();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
   qDebug()<<arg1;
   emit signalReportTimeChanged(arg1);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    emit signalIsNeedPrintRF(checked);
}

void MainWindow::slotAbout(bool)
{
    About a;
    a.setEnabled(true);
    a.exec();
}

void MainWindow::slotUpdateSerialInfo()
{
    this->ui->serialCombox->clear();
    this->ui->serialCombox->addItem("请选择串口");
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        if(!info.isBusy())
        {
            this->ui->serialCombox->addItem(info.portName());
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    slotUpdateSerialInfo();
}

void MainWindow::on_serialCombox_activated()
{
    s.close();
    if(ui->serialCombox->currentText() != "请选择串口")
    {
        s.setPortName(ui->serialCombox->currentText());
        if(!s.open(QSerialPort::ReadWrite))
        {
            QMessageBox::information(this,"串口","打开失败",0);
            ui->serialCombox->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    emit signalIsNeedPrintQueryState(checked);
}

void MainWindow::slotHelp(bool)
{
    qDebug()<<"xxx";
     QDesktopServices::openUrl(QUrl("help.html"));
}

void MainWindow::on_ResetpushButton_clicked()
{
    const char * str2 = "个"; //ssssssssa
    QString b = QString::fromLatin1(str2);
    const char * str = "复位";
    QString a= QString::fromUtf8(str);
    int ret = QMessageBox::warning(this, a, b, QMessageBox::Yes|QMessageBox::Cancel);
    if(ret == QMessageBox::Yes)
    {
        uint8_t  resetCommand[] = {0xf5,0xf5,0x00,0x03,0xac,0x2a,0xf7};
        s.write((char *)resetCommand, 7);
    }
}

void MainWindow::slotReadyRead()
{
    QByteArray receive = s.readAll();
    emit signaReadyRead(receive);
}
