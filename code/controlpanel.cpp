#include "controlpanel.h"
#include <QtEndian>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlPanel::ControlPanel(QList<FunctionItem *> &l)
{
    this->setLayout(&mainLayout);
    this->list = l;
    this->isNeedPrintRF = false;
    this->isNeedPrintQueryState = false;

    constructComandList();
    for(int i=0;i<l.size();i++)
    {
        FunctionItemWidget *pw = new FunctionItemWidget(l.at(i), statemachine);
        connect(pw, SIGNAL(signalALarm(uint16_t)), this, SLOT(slotAlarm(uint16_t)));
        connect(pw, SIGNAL(signalLog(QString,uint8_t)), this, SIGNAL(signallog(QString, uint8_t)));
        connect(pw, SIGNAL(signalStatusChanged()), this, SLOT(slotReportState()));

        controlList.append(pw);
        mainLayout.addWidget(pw, i/4, i%4);
        mainLayout.setRowStretch(i/4, 1);
        mainLayout.setColumnStretch(i%4, 1);
    }

    mainLayout.setContentsMargins(0,0,0,0);
    connect(&reportTimer,SIGNAL(timeout()),this,SLOT(slotReportState()));

    reportTimer.start(10000);
}

void ControlPanel::slotReceivedFrame(QByteArray receivedData)
{
    bool uartsuccess = UserUartLinkUnpack((uchar *)receivedData.data(), receivedData.length());
    if(uartsuccess)
    {
        uint8_t buf[255];
        uchar len = getUserUartLinkMsg(buf);
        //处理 帧类型+数据区域
        QDEBUG()<<QByteArray((char *)buf,len).toHex();
        uint8_t frameType = buf[0];
        if(frameType == 0x01) //控制帧
        {
            receivedControlFrame(buf+1,len-1);
        }
        else if(frameType == 0x05)
        {
            //确认帧
            if(isNeedPrintRF)
            {
                emit signallog(QString(receivedData.toHex()),1);
                emit signallog("确认帧",2);
            }
        }
        else if(frameType == 0x09)
        {
            emit signallog("停止报警帧",2);
            for(int i = 0; i<commandTypeList.size(); i++)
            {
                if(commandTypeList.at(i) == 0x04)
                {
                    this->controlList.at(i)->stopAlarm();
                }
            }
        }
        else
        {
            slotInvalid();
        }
    }
}

void ControlPanel::slotReportState()
{
    uint8_t srcData[250];

    srcData[0] = 0x07;//汇报帧
    memcpy((uint8_t *)(srcData+1), statemachine, stateLength);

    uint8_t len = UserUartLinkPack(sendFrame, srcData, stateLength+1, 0);
    QDEBUG()<< stateLength;
    QDEBUG()<< QByteArray((char *)sendFrame);
    //通知mainwindow将数据发送出去;

    emit signalSendReport(sendFrame,len);
    if(isNeedPrintRF)
    {
        emit signallog(QByteArray((char *)sendFrame,len).toHex().toUpper(),4);
    }
}

void ControlPanel::slotQueryState(bool b)
{
    uint8_t srcData[250];

    srcData[0] = 0x02;//状态帧
    memcpy((uint8_t *)(srcData+1),statemachine,stateLength);

    uint8_t len = UserUartLinkPack(sendFrame, srcData, stateLength+1,0);
    QDEBUG()<< stateLength;
    QDEBUG()<< QByteArray((char *)sendFrame);

    //通知mainwindow将数据发送出去;
    emit signalSendReport(sendFrame,len);
    if(b)
    {
        emit signallog(QByteArray((char *)sendFrame,len).toHex().toUpper(),4);
    }
}

void ControlPanel::slotInvalid()
{
    QDEBUG()<< "回复无效帧";
    uchar invalid[] = {0x03,0x00,0x00,0x00,0x01};

    uint8_t len =UserUartLinkPack(sendFrame, invalid,5,0);
    emit signalSendReport(sendFrame,len);
}

void ControlPanel::slotAlarm(uint16_t alarmCode)
{
    uchar alarmData[]={0x04,0x00,0x00,0x00,0x00,0x00,0x00};
    *((uint16_t *)(alarmData+1)) = qToBigEndian(alarmCode);

    uint8_t len = UserUartLinkPack(sendFrame, alarmData, 7, 0);
    QDEBUG()<< len;
    emit signalSendReport(sendFrame,len);
    emit signallog(QByteArray((char *)sendFrame, len).toHex().toUpper(), len);
}

void ControlPanel::slotIsNeedPrintRF(bool i)
{
    this->isNeedPrintRF = i;
}

void ControlPanel::slotIsNeedPrintQueryState(bool i)
{
    this->isNeedPrintQueryState = i;
}

void ControlPanel::slotReportTimeChanged(int s)
{
    this->reportTimer.stop();
    this->reportTimer.start(s*1000);
}

void ControlPanel::receivedControlFrame(uint8_t * frame, int len)
{
    QDEBUG()<<QByteArray((char *)frame,len).toHex();
    uint16_t cmd = qFromBigEndian(*((uint16_t *)frame));

    QDEBUG()<< cmd;
    if(cmd == 11) //公共指令
    {
        if(this->isNeedPrintQueryState)
        {
            emit signallog(QByteArray((char *)frame,len).toHex(),1);
            emit signallog("查询指令",2);
        }
        slotQueryState(isNeedPrintQueryState);
        QDEBUG()<<"收到一个查询指令";
    }
    else
    {
        for(int i=0; i<list.size(); i++)
        {
            if(cmd == list.at(i)->getVarIndex())
            {
                emit signallog(QByteArray((char *)frame,len).toHex().toUpper(),1);
                bool isSuccess =  controlList.at(i)->dealWithCommand(frame);
                if(isSuccess)
                {
                    slotQueryState(true);
                }
                else
                {
                    slotInvalid();
                }
                return;
            }
        }
    }
    QDEBUG()<<"不存在指令";
    emit signallog("指令("+QString::number(cmd)+"---0x"+QString::number(cmd,16)+")"+"不存在",3);
    slotInvalid();
}

void ControlPanel::constructComandList()
{
    this->stateLength = list.last()->getDataPos()+list.last()->getDatalength();
    for(int i=0;i<list.size();i++ )
    {
        commandList.append(list.at(i)->getVarIndex());
        commandTypeList.append(list.at(i)->getVarType());
    }
    this->statemachine = new uint8_t [stateLength +1];
    memset(statemachine,0,stateLength+1);
    this->sendFrame = new uint8_t [255];
}
