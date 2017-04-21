#include "functionitemwidget.h"
#include <QtEndian>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

FunctionItemWidget::FunctionItemWidget(FunctionItem *f, uchar *baseAddr)
{
    this->functionItem = f;
    this->baseAddress = baseAddr;
    init();
    functionNameLabel.setAlignment(Qt::AlignCenter);
    mainLayout.addWidget(&functionNameLabel);
    functionNameLabel.setStyleSheet("font: 45 16pt");
    if(f->getDisName() != "")
    {
        this->functionNameLabel.setText(f->getDisName());
    }
    else
    {
//        functionNameLabel.setText("开关");
    }

    this->setLayout(&mainLayout);
    QDEBUG()<<"初始化状态";
    slotStateChanged(f->getVarType());
}

bool FunctionItemWidget::dealWithCommand(void * parameter)
{
    //parameter
    uint8_t varType = functionItem->getVarType();
    if((varType == VARCMD) || (varType == VARSINGLE) || (varType == VAROUT) || (varType == VARINPUT))
    {
        uint8_t *cmd = (uint8_t *)parameter;
        QMap<int, QByteArray> comdlist = functionItem->getVarDesc().pVarDescEnumberate->getItem();
        QString itemList;// = functionItem->getVarDesc().pVarDescCmd->getDisItem();
        if(comdlist.keys().contains(*cmd))
        {
            *((uint8_t *)(baseAddress + functionItem->getDataPos())) = *cmd;
            this->controlWidget.controlCmd->setStatus(*cmd);
            emit signalLog(functionItem->getDisName()+":"+itemList.at(comdlist.keys().indexOf(*cmd)),2);
        }
        else
        {
            QDEBUG()<<"指令错误";
            QDEBUG()<<comdlist.keys().at(0);
            int tmp1, tmp2;
            tmp1 = comdlist.keys().at(0);
            tmp2 = comdlist.keys().at(1);
            emit signalLog(functionItem->getDisName()+
                           ":"+QString::number(*cmd)+" "+"("+QString::number(tmp1)+","+QString::number(tmp2)+") 参数错误",3);
            return false;
            //发送错误帧
        }
    }
    else if(varType == VARNUMBER) //数字型
    {
        int16_t cmdSrc = *(int16_t *)parameter; //从网络中来的数据

        int16_t max = functionItem->getVarDesc().pVarDescNumber->getMax();
        int16_t min = functionItem->getVarDesc().pVarDescNumber->getMin();
        int16_t cmdLitter = qFromBigEndian(cmdSrc);
        if((cmdLitter) >= min && (cmdLitter <= max))
        {
            QDEBUG()<< cmdLitter;
            QDEBUG()<< functionItem->getDataPos();
            *((int16_t *)((uint8_t *)(baseAddress + functionItem->getDataPos()))) = cmdSrc;//写入状态机

            QDEBUG()<<*((int16_t *)((uint8_t *)(baseAddress + functionItem->getDataPos())));
            this->controlWidget.controlNumber->setNumber(cmdLitter);
            emit signalLog(functionItem->getDisName()+":"+QString::number(cmdLitter),2);
        }
        else
        {
            QDEBUG()<<"数字型参数错误！";
            emit signalLog(functionItem->getDisName()+":"+QString::number(cmdLitter)+" "+
                           "["+QString::number(max)+"-"+QString::number(min)+"] 参数错误"
                           ,3);
            return false;
        }
    }
    else if(varType ==VARENUMBERATE) //枚举型
    {
        uint8_t *cmd = (uint8_t *)parameter;
        QMap<int, QByteArray> itemlist = functionItem->getVarDesc().pVarDescEnumberate->getItem();
        if(itemlist.contains(*cmd))
        {
            uint8_t index = itemlist.keys().indexOf(*cmd);
            QDEBUG()<< "第"<<index<<"个";
            *((uint8_t *)(baseAddress + functionItem->getDataPos())) = *cmd;
            this->controlWidget.controlEnumberate->setCurrentStatus(index);
            emit signalLog(functionItem->getDisName()+":"+functionItem->getDisDesc().disEnum->disEnumList.at(index)->string,2);
        }
        else
        {
            QString log;
            log = functionItem->getDisName()+":"+QString::number(*cmd)+" "+"[";

            for(int i=0;i<itemlist.size();i++)
            {
                log += QString::number(itemlist.keys().at(i))+"," ;
            }
            log +="] 参数错误";
            emit signalLog(log,3);
            QDEBUG()<<"枚举型参数不在范围之内";
            return false;
        }
    }
    else if(varType == VARDATE) //日期型
    {
        pDate pdate = (pDate)parameter;

        //写入状态机
        QDEBUG()<<"日期型指令";
        QDEBUG()<< pdate->year << pdate->month << pdate->day;
        QDate dateMax = functionItem->getVarDesc().pVarDescDatetime->getMaxDate();
        QDate dateMin = functionItem->getVarDesc().pVarDescDatetime->getMinDate();

        //从网络端得到的year为大端，需要转换成小端
        uint16_t yearLittle = qFromBigEndian(pdate->year);
        QDate date(yearLittle, pdate->month,pdate->day);
        QDEBUG()<< date.toString();
        QDEBUG()<< QDate(2016,12,2).toString();

        if(date >= dateMin && date <= dateMax)
        {
            pDate pStateMachine = (pDate)((uint8_t *)(baseAddress + functionItem->getDataPos()));
            *pStateMachine = *pdate;
            this->controlWidget.controlDate->setDate(QDate(yearLittle, pdate->month,pdate->day));
            emit signalLog(functionItem->getDisName()+":"+date.toString(), 2);
        }
        else
        {
            emit signalLog(functionItem->getDisName()+":"+date.toString()+" ["+
                           dateMin.toString()+"-"+dateMax.toString()+"] 参数错误",3);
            QDEBUG()<<"不在范围之内";
            return false;
        }
    }
    else if(varType == VARTIME) //时间型
    {
        pTime ptime = (pTime)parameter;
        QTime timeMax = functionItem->getVarDesc().pVarDescDatetime->getMaxTime();
        QTime timeMin = functionItem->getVarDesc().pVarDescDatetime->getMinTime();
        QTime time(ptime->hour,ptime->minute,ptime->second);
        if((time >= timeMin) && (time <= timeMax))
        {
            pTime pStateMachine = (pTime)((uint8_t *)(baseAddress + functionItem->getDataPos()));
            *pStateMachine = *ptime;
            this->controlWidget.controlTime->setTime(time);
            emit signalLog(functionItem->getDisName()+":"+time.toString(),2);
        }
        else
        {
            emit signalLog(functionItem->getDisName()+":"+time.toString()+" ["+
                           timeMin.toString()+"-"+timeMax.toString()+"] 参数错误",3);
            QDEBUG()<<"不在范围之内";
            return false;
        }
    }
    else if(varType == VARDATETIME) //时间日期型
    {
        pDatetime pdatetime = (pDatetime)parameter;

        QDate dateMax = functionItem->getVarDesc().pVarDescDatetime->getMaxDate();
        QDate dateMin = functionItem->getVarDesc().pVarDescDatetime->getMinDate();
        QTime timeMax = functionItem->getVarDesc().pVarDescDatetime->getMaxTime();
        QTime timeMin = functionItem->getVarDesc().pVarDescDatetime->getMinTime();

        //从网络端得到的year为大端，需要转换成小端
        uint16_t yearLittle = qFromBigEndian(pdatetime->year);
        QDate date(yearLittle, pdatetime->month,pdatetime->day);
        QTime time(pdatetime->hour,pdatetime->minute,pdatetime->second);

        QDateTime datetime(date, time);
        QDateTime datetimeMax(dateMax, timeMax);
        QDateTime datetimeMin(dateMin, timeMin);

        if((datetime >= datetimeMin) && (datetime <= datetimeMax))
        {
            pDatetime pStateMachine = (pDatetime)((uint8_t *)(baseAddress + functionItem->getDataPos()));
            *pStateMachine = *pdatetime;
            this->controlWidget.controlDatetime->setUiDatetime(datetime);
            emit signalLog(functionItem->getDisName()+":"+datetime.toString(),2);
        }
        else
        {
            emit signalLog(functionItem->getDisName()+":"+datetime.toString()+" ["+
                           datetimeMin.toString()+"-"+datetimeMax.toString()+"] 参数错误",3);
            QDEBUG()<<"不在范围之内";
            return false;
        }
    }
    else
    {
        QDEBUG()<< "无效命令";
        return false;
    }
    return true;
}

void FunctionItemWidget::stopAlarm()
{
    this->controlWidget.controlAlarm->stopAlarm();
}

void FunctionItemWidget::slotStateChanged(uint8_t dataType)
{
    uchar *address = (uint8_t *)(baseAddress + functionItem->getDataPos());
    QDEBUG()<<"数据偏移："<<functionItem->getDataPos();
    if(dataType == VARCMD)
    {
        uint8_t *v = (uint8_t *)address;
        uint8_t status = this->controlWidget.controlCmd->getStatus();
        QDEBUG()<<"**********"<<status;
        *v =  status;
        QDEBUG()<<*v;
    }
    else if(dataType == VARNUMBER)
    {
        QDEBUG()<<"数字改变"<<controlWidget.controlNumber->getNumber();
        int16_t *v = (int16_t *)(address);
        int16_t vBig = controlWidget.controlNumber->getNumber();

        *v = qToBigEndian(vBig);
        QDEBUG()<<*v;
    }
    else if(dataType == VARENUMBERATE)
    {
        QDEBUG()<<"枚举改变"<<functionItem->getDisDesc().disEnum->disEnumList.at(controlWidget.controlEnumberate->getCurrentStatus())->string;
        uint8_t *v = (uint8_t *)(address);
        *v = functionItem->getVarDesc().pVarDescEnumberate->getItem().keys().at(controlWidget.controlEnumberate->getCurrentStatus());
        QDEBUG()<<*v;
    }
    else if(dataType == VARALARM)
    {
        QDEBUG()<<"报警变量改变"<<controlWidget.controlAlarm->getHasBytepos();

        if(this->controlWidget.controlAlarm->getHasBytepos())
        {
            QDEBUG()<<"报警变量改变2";
            QByteArray allBytepos = functionItem->getVarDesc().pVarDescAlarm->getBytePos();
            QByteArray allBitpos = functionItem->getVarDesc().pVarDescAlarm->getBitPos();
            QList<uint16_t> alarmCodeList = functionItem->getVarDesc().pVarDescAlarm->getAlarmCode();
            QList<uint16_t> alarmCurrentCodeList = this->controlWidget.controlAlarm->getCurrentAlarmCodelist();
            QDEBUG()<<alarmCurrentCodeList;

            for(int i=0; i < allBytepos.size(); i++)
            {
                uint8_t *p = (uint8_t *)baseAddress+allBytepos.at(i);
                if(alarmCurrentCodeList.contains(alarmCodeList.at(i)))
                {
                    (*p) |= (0x01 << allBitpos.at(i));
                }
                else
                {
                    (*p) &= (~(0x01<<allBitpos.at(i)));
                }
            }
        }
    }
    else if(dataType == VARDATE)
    {
        QDate date = controlWidget.controlDate->getDate();
        uint16_t *year = (uint16_t *)address; //定义一个指正指向地址
        uint8_t *month = (uint8_t *)(address +2);
        uint8_t *day = (uint8_t *)(address + 3);
        uint16_t yearBig = qToBigEndian((uint16_t)date.year());
        *year  = yearBig;
        *month = date.month();
        *day = date.day();
    }
    else if(dataType == VARTIME)
    {
        QDEBUG()<<"时间改变";
        QTime time = controlWidget.controlTime->getTime();
        uint8_t *hour = (uint8_t *)address;
        uint8_t *minute = (uint8_t *)(address+1);
        uint8_t *second = (uint8_t *)(address + 2);

        *hour = time.hour();
        *minute = time.minute();
        *second = time.second();
    }
    else if(dataType == VARDATETIME)
    {
        QDateTime datetime = controlWidget.controlDatetime->getDatetime();
        uint16_t *year = (uint16_t *)address; //定义一个指正指向地址
        uint8_t *month = (uint8_t *)(address +2);
        uint8_t *day = (uint8_t *)(address + 3);
        uint8_t *hour = (uint8_t *)(address+4);
        uint8_t *minute = (uint8_t *)(address+5);
        uint8_t *second = (uint8_t *)(address + 6);
        *year  = qToBigEndian((uint16_t)datetime.date().year());
        *month = datetime.date().month();
        *day = datetime.date().day();
        *hour = datetime.time().hour();
        *minute = datetime.time().minute();
        *second = datetime.time().second();
    }
    else
    {
        QDEBUG()<< "错误";
    }
    emit signalStatusChanged(); //通知发送状态改变帧
}

void FunctionItemWidget::slotAlarm(uint16_t AlarmCode)
{
   QDEBUG()<< AlarmCode;
   QDEBUG()<< this->functionItem->getVarDesc().pVarDescAlarm->getAlarmString().at(controlWidget.controlAlarm->getAlarm());
   QDEBUG()<< this->controlWidget.controlAlarm->getAlarm();
   emit signalALarm(AlarmCode);
   emit signalLog(functionItem->getVarDesc().pVarDescAlarm->getAlarmString().at(controlWidget.controlAlarm->getAlarm()),5);
}

void FunctionItemWidget::init()
{
    QDEBUG()<<"变量类型"<<functionItem->getVarType();
    switch (functionItem->getVarType())
    {
    case VARCMD:
    case VARSINGLE:
    case VARINPUT:
        this->controlWidget.controlCmd = new ControlCmd(functionItem->getVarDesc(), functionItem->getDisDesc(), functionItem->getIsdisplay());
        connect(this->controlWidget.controlCmd, SIGNAL(signalStateChanged(uint8_t)), this, SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlCmd);
        break;

    case VAROUT:
        this->controlWidget.controlCmd = new ControlCmd(functionItem->getVarDesc(), functionItem->getDisDesc(), functionItem->getIsdisplay());
        connect(this->controlWidget.controlCmd, SIGNAL(signalStateChanged(uint8_t)), this, SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlCmd);
        break;

    case VARNUMBER://数字型//
        this->controlWidget.controlNumber = new ControlNumber(functionItem->getVarDesc());
        connect(controlWidget.controlNumber,SIGNAL(signalStateChanged(uint8_t)),this,SLOT(slotStateChanged(uint8_t)));

        mainLayout.addWidget(controlWidget.controlNumber);
        break;

    case VARENUMBERATE : //枚举型
        this->controlWidget.controlEnumberate = new ControlEnumberate(functionItem->getVarDesc(), functionItem->getDisDesc());
        connect(controlWidget.controlEnumberate,SIGNAL(signalStateChanged(uint8_t)),this,SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlEnumberate);
        break;

    case VARALARM:
        this->controlWidget.controlAlarm = new ControlAlarm(functionItem->getVarDesc());
        connect(controlWidget.controlAlarm,SIGNAL(signalAlarms(uint16_t)),this,SLOT(slotAlarm(uint16_t)));
        connect(controlWidget.controlAlarm,SIGNAL(signalStatusChanged(uint8_t)),this,SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlAlarm);
        break;

    case VARDATE:  //日期型
        this->controlWidget.controlDate = new ControlDate(functionItem->getVarDesc());
        connect(controlWidget.controlDate,SIGNAL(signalStateChanged(uint8_t)),this,SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlDate);
        break;

    case  VARTIME: //时间型
        this->controlWidget.controlTime = new ControlTime(functionItem->getVarDesc());
        connect(controlWidget.controlTime,SIGNAL(signalStateChanged(uint8_t)),this,SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlTime);
        break;

    case VARDATETIME: //日期时间型
        this->controlWidget.controlDatetime = new ControlDateTime(functionItem->getVarDesc());
        connect(controlWidget.controlDatetime, SIGNAL(signalStateChanged(uint8_t)), this, SLOT(slotStateChanged(uint8_t)));
        mainLayout.addWidget(controlWidget.controlDatetime);
        break;
    default:
        break;
    }
}
