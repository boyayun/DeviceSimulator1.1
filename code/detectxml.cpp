#include "detectxml.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

DetectXml::DetectXml(QString path)
{
    QDEBUG()<<path;
    listItem.clear();
    QFile f(path);
    QDomDocument doc;
    QDEBUG()<<doc.setContent(&f);

    QDomNodeList domList = doc.childNodes();
    QDEBUG()<<"总节点数"<<domList.size();
    detectDeviceDescribe(domList.at(1));
    QDEBUG()<<"解析完成";
}

void DetectXml::detectDeviceDescribe(QDomNode n)
{
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"文件节点数"<<domList.size();

    detectHeadInformation(domList.at(0));    //解析头部信息
    detectFunctionList(domList.at(1));       //解析功能列表
}

void DetectXml::detectHeadInformation(QDomNode n)
{
    QDEBUG()<< "解析头部" ;
    QDEBUG()<<n.nodeName();
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"头部节点数"<<domList.size();

    this->deviceName = domList.at(7).toElement().text();
}

void DetectXml::detectFunctionList(QDomNode n)
{
    QDEBUG()<<"解析功能列表";
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"功能列表节点数"<<domList.size();
    for(int i=0;i<domList.size();i++)
    {
        detectFunction(domList.at(i));      //解析功能
    }
}

void DetectXml::detectFunction(QDomNode n)
{
    FunctionItem *f = new FunctionItem();
    listItem.append(f);
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"功能节点数"<<domList.size();

    int i = 0;
    f->setVarIndex(domList.at(i++).toElement().text().toInt());
    f->setFunLimit(domList.at(i++).toElement().text().toInt());
    f->setIsdisplay(domList.at(i++).toElement().text().toInt());
    f->setDirection(domList.at(i++).toElement().text().toInt());

    detectVarTypeDesc(domList.at(i++),f);              // 解析变量
    return;
    detectDisTypeDesc(domList.at(i++),f);              // 解析显示变量
}

void DetectXml::detectVarTypeDesc(QDomNode n, FunctionItem *f)
{
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"变量节点数"<<domList.size();

    int i = 0;
    f->setCmdType(domList.at(i++).toElement().text().toInt());
    f->setVarType(domList.at(i++).toElement().text().toInt());
    if(domList.at(i).nodeName().toStdString() == STATUSFIELD)
    {
        f->setReturnType(RETURNBYTE);
    }
    else if(domList.at(i).nodeName().toStdString() == STATUSBIT)
    {
        f->setReturnType(RETURNBIT);
    }
    else
    {
        QDEBUG()<<"returntypeError";
    }
    f->setDataPos(domList.at(i).childNodes().at(0).toElement().text().toInt());
    f->setDatalength(domList.at(i++).childNodes().at(0).toElement().text().toInt());
    f->setVarLength(domList.at(i++).toElement().text().toInt());
    f->setDataType(domList.at(i++).toElement().text().toInt());
    detectVarParameters(domList.at(i++), f);         //解析变量参数
}

void DetectXml::detectVarParameters(QDomNode n, FunctionItem *f)
{
    uint8_t VarType = f->getVarType();
    QDomNodeList domList = n.childNodes();
    QDEBUG()<<"参数节点数"<<domList.size();
    QDEBUG()<<"vartype"<<VarType;
    if(VarType == VARCMD)
    {
        varDesc.pVarDescEnumberate = new VarDescEnumberate();
        QMap<int, QByteArray> item, itemReturn;
        int key;
        int i = 0;
        for(int j=0; j<2; j++, i++)
        {
            QByteArray value, returnValue;
            key = domList.at(i++).toElement().text().toInt();
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                value.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            i++;
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                returnValue.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            item.insert(key, value);
            itemReturn.insert(key, returnValue);
        }
        varDesc.pVarDescEnumberate->setItem(item);
        varDesc.pVarDescEnumberate->setItemReturn(itemReturn);
        varDesc.pVarDescEnumberate->setDefaultValue(domList.at(i).toElement().text().toInt());
        f->setVarDesc(varDesc);

        for(int i=0; i<f->getVarDesc().pVarDescEnumberate->getItem().size(); i++)
        {
            QDEBUG()<<"value"<<f->getVarDesc().pVarDescEnumberate->getItem().keys().at(i);
            QDEBUG()<<"other"<<f->getVarDesc().pVarDescEnumberate->getItem().values().at(i).toHex().toUpper();
            QDEBUG()<<"return"<<f->getVarDesc().pVarDescEnumberate->getItemReturn().values().at(i).toHex().toUpper();
        }
        QDEBUG()<<"default"<<f->getVarDesc().pVarDescEnumberate->getDefaultValue();
    }
    else if(VarType == VARENUMBERATE)
    {
        varDesc.pVarDescEnumberate = new VarDescEnumberate();
        int i = 1;          //number没用到
        varDesc.pVarDescEnumberate->setDefaultValue(domList.at(i++).toElement().text().toInt());
        QMap<int, QByteArray> item, itemReturn;
        int key;
        for(int j=0; j<domList.at(0).toElement().text().toInt(); j++, i++)
        {
            QByteArray other, returnValue;
            key = domList.at(i++).toElement().text().toInt();
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            i++;
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                returnValue.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            item.insert(key, other);
            itemReturn.insert(key, returnValue);
        }
        varDesc.pVarDescEnumberate->setItem(item);
        varDesc.pVarDescEnumberate->setItemReturn(itemReturn);
        f->setVarDesc(varDesc);

        QDEBUG()<<"default"<<f->getVarDesc().pVarDescEnumberate->getDefaultValue();
        for(int i=0; i<f->getVarDesc().pVarDescEnumberate->getItem().size(); i++)
        {
            QDEBUG()<<"value"<<f->getVarDesc().pVarDescEnumberate->getItem().keys().at(i);
            QDEBUG()<<"otherorder"<<f->getVarDesc().pVarDescEnumberate->getItem().values().at(i).toHex().toUpper();
            QDEBUG()<<"return"<<f->getVarDesc().pVarDescEnumberate->getItemReturn().values().at(i).toHex().toUpper();
        }
    }
    else if(VarType == VARNUMBER)//数字型
    {
        varDesc.pVarDescNumber = new VarDescNumber();
        int i = 0;
        varDesc.pVarDescNumber->setMax(domList.at(i++).toElement().text().toInt());
        varDesc.pVarDescNumber->setMin(domList.at(i++).toElement().text().toInt());
        varDesc.pVarDescNumber->setScalling(domList.at(i++).toElement().text().toInt());
        varDesc.pVarDescNumber->setUnit(domList.at(i++).toElement().text().toInt());
        varDesc.pVarDescNumber->setDefaultValue(domList.at(i++).toElement().text().toInt());

        _otherPara otherPara;
        otherPara.valuePos = domList.at(i++).toElement().text().toInt();
        otherPara.valueLength = domList.at(i++).toElement().text().toInt();
        varDesc.pVarDescNumber->setOtherValue(otherPara);

        varDesc.pVarDescNumber->setKfactor(domList.at(i++).toElement().text().toDouble());
        varDesc.pVarDescNumber->setCfactor(domList.at(i++).toElement().text().toDouble());
        varDesc.pVarDescNumber->setEndian(domList.at(i++).toElement().text().toInt());
        QByteArray other;
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        other.append(domList.at(i++).toElement().text());
        varDesc.pVarDescNumber->setOther(other);
        f->setVarDesc(varDesc);

        QDEBUG()<<"max"<<f->getVarDesc().pVarDescNumber->getMax();
        QDEBUG()<<"min"<<f->getVarDesc().pVarDescNumber->getMin();
        QDEBUG()<<"scall"<<f->getVarDesc().pVarDescNumber->getScalling();
        QDEBUG()<<"unit"<<f->getVarDesc().pVarDescNumber->getUnit();
        QDEBUG()<<"default"<<f->getVarDesc().pVarDescNumber->getDefaultValue();
        QDEBUG()<<"valuePos"<<f->getVarDesc().pVarDescNumber->getOtherValue().valuePos;
        QDEBUG()<<"valueLength"<<f->getVarDesc().pVarDescNumber->getOtherValue().valueLength;
        QDEBUG()<<"kfactor"<<f->getVarDesc().pVarDescNumber->getKfactor();
        QDEBUG()<<"cfactor"<<f->getVarDesc().pVarDescNumber->getCfactor();
        QDEBUG()<<"valueEndian"<<f->getVarDesc().pVarDescNumber->getEndian();
        QDEBUG()<<"otherorder"<<f->getVarDesc().pVarDescNumber->getOther().toHex().toUpper();

    }
    else if(VarType == VARALARM)
    {
        varDesc.pVarDescAlarm = new VarDescAlarm();

        QByteArray alarmBytepos;
        QByteArray alarmBitpos;
        QList<uint16_t>alarmCode;
        QByteArray alarmClass;
        QList<QString>alarmString;

        for(int i=0; i<domList.size(); i++)
        {
            int j=0;
            QDomNodeList l = domList.at(i).childNodes();
            alarmBytepos.append(l.at(j++).toElement().text().toInt());
            alarmBitpos.append(l.at(j++).toElement().text().toInt());
            alarmCode.append(l.at(j++).toElement().text().toUShort());
            alarmClass.append(l.at(j++).toElement().text().toInt());
            alarmString.append(l.at(j++).toElement().text());
        }
        varDesc.pVarDescAlarm->setAlarmClass(alarmClass);
        varDesc.pVarDescAlarm->setAlarmCode(alarmCode);
        varDesc.pVarDescAlarm->setAlarmString(alarmString);
        varDesc.pVarDescAlarm->setBytePos(alarmBytepos);
        varDesc.pVarDescAlarm->setBitPos(alarmBitpos);
        f->setVarDesc(varDesc);

        QDEBUG()<<"bytepos"<<f->getVarDesc().pVarDescAlarm->getBytePos().toHex().toUpper();
        QDEBUG()<<"bitpos"<<f->getVarDesc().pVarDescAlarm->getBitPos().toHex().toUpper();
        QDEBUG()<<"alarmcode"<<f->getVarDesc().pVarDescAlarm->getAlarmCode();
        QDEBUG()<<"alarmclass"<<f->getVarDesc().pVarDescAlarm->getAlarmClass().toHex().toUpper();
        QDEBUG()<<"alarmname"<<f->getVarDesc().pVarDescAlarm->getAlarmString();
    }
    else if(VarType == VARDATE)
    {
        varDesc.pVarDescDatetime = new VarDescDatetime();
        int i = 0;
        int maxyear, minyear, valueyear, endian, yearC;
        QByteArray step, max, min, value;
        QList<_otherPara>otherValue;
        for(int j=0; j<3; j++)
        {
            if(j == 0)          //year 两字节
            {
                maxyear = domList.at(i++).toElement().text().toInt();
                minyear = domList.at(i++).toElement().text().toInt();
//                valueyear = domList.at(i++).toElement().text().toInt();
            }
            else
            {
                max.append(domList.at(i++).toElement().text().toInt());
                min.append(domList.at(i++).toElement().text().toInt());
//                value.append(domList.at(i++).toElement().text().toInt());
            }
            step.append(domList.at(i++).toElement().text().toInt());
            if(j == 0)
            {
                yearC = domList.at(i++).toElement().text().toInt();
            }
            _otherPara *otherPara = new _otherPara;
            otherPara->valuePos = domList.at(i++).toElement().text().toInt();
            otherPara->valueLength = domList.at(i++).toElement().text().toInt();
            otherValue.append(*otherPara);
        }
        endian = domList.at(i++).toElement().text().toInt();
        QByteArray other;
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        varDesc.pVarDescDatetime->setMaxDate(QDate(maxyear, max.at(0), max.at(1)));
        varDesc.pVarDescDatetime->setMinDate(QDate(minyear, min.at(0), min.at(1)));
//        varDesc.pVarDescDatetime->setDate(QDate(valueyear, value.at(0), value.at(1)));
        varDesc.pVarDescDatetime->setStep(step);
        varDesc.pVarDescDatetime->setYearC(yearC);
        varDesc.pVarDescDatetime->setEndian(endian);
        varDesc.pVarDescDatetime->setOtherValue(otherValue);
        varDesc.pVarDescDatetime->setOther(other);

        f->setVarDesc(varDesc);

        QDEBUG()<<"other"<< f->getVarDesc().pVarDescDatetime->getOther().toHex().toUpper();
        QDEBUG()<<"maxdate"<<f->getVarDesc().pVarDescDatetime->getMaxDate();
        QDEBUG()<<"mindate"<<f->getVarDesc().pVarDescDatetime->getMinDate();
        QDEBUG()<<"date"<<f->getVarDesc().pVarDescDatetime->getDate();
        QDEBUG()<<"step"<<f->getVarDesc().pVarDescDatetime->getStep().toHex().toUpper();
        QDEBUG()<<"yearC"<<f->getVarDesc().pVarDescDatetime->getYearC();
        QDEBUG()<<"endian"<<f->getVarDesc().pVarDescDatetime->getEndian();
        for(int i=0; i<f->getVarDesc().pVarDescDatetime->getOtherValue().size(); i++)
        {
            QDEBUG()<<"valuepos"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valuePos;
            QDEBUG()<<"valuelength"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valueLength;
        }
    }
    else if(VarType == VARTIME)
    {
        varDesc.pVarDescDatetime = new VarDescDatetime();
        int i = 0;
        int endian;
        QByteArray step, max, min, value;
        QList<_otherPara>otherValue;
        for(int j=0; j<3; j++)
        {
            max.append(domList.at(i++).toElement().text().toInt());
            min.append(domList.at(i++).toElement().text().toInt());
//            value.append(domList.at(i++).toElement().text().toInt());
            step.append(domList.at(i++).toElement().text().toInt());
            _otherPara *otherPara = new _otherPara;
            otherPara->valuePos = domList.at(i++).toElement().text().toInt();
            otherPara->valueLength = domList.at(i++).toElement().text().toInt();
            otherValue.append(*otherPara);
        }
        endian = domList.at(i).toElement().text().toInt();
        QByteArray other;
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }

        varDesc.pVarDescDatetime->setMaxTime(QTime(max.at(0), max.at(1), max.at(2)));
        varDesc.pVarDescDatetime->setMinTime(QTime(min.at(0), min.at(1), min.at(2)));
        varDesc.pVarDescDatetime->setTime(QTime(value.at(0), value.at(1), value.at(2)));
        varDesc.pVarDescDatetime->setStep(step);
        varDesc.pVarDescDatetime->setOtherValue(otherValue);
        varDesc.pVarDescDatetime->setEndian(endian);
        varDesc.pVarDescDatetime->setOther(other);

        f->setVarDesc(varDesc);

        QDEBUG()<<"maxtime"<< f->getVarDesc().pVarDescDatetime->getMaxTime();
        QDEBUG()<<"mintime"<< f->getVarDesc().pVarDescDatetime->getMinTime();
//        QDEBUG()<<"time"<< f->getVarDesc().pVarDescDatetime->getTime();
        QDEBUG()<<"step"<< f->getVarDesc().pVarDescDatetime->getStep().toHex().toUpper();
        QDEBUG()<<"endian"<<f->getVarDesc().pVarDescDatetime->getEndian();
        QDEBUG()<<"other"<< f->getVarDesc().pVarDescDatetime->getOther().toHex().toUpper();
        for(int i=0; i<f->getVarDesc().pVarDescDatetime->getOtherValue().size(); i++)
        {
            QDEBUG()<<"valuepos"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valuePos;
            QDEBUG()<<"valuelength"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valueLength;
        }
    }
    else if(VarType == VARDATETIME)
    {
        varDesc.pVarDescDatetime = new VarDescDatetime();
        int i = 0;
        int maxyear, minyear, valueyear, endian, yearC;
        QByteArray step, max, min, value;
        QList<_otherPara>otherValue;
        for(int j=0; j<6; j++)
        {
            if(j == 0)          //year 两字节
            {
                maxyear = domList.at(i++).toElement().text().toInt();
                minyear = domList.at(i++).toElement().text().toInt();
//                valueyear = domList.at(i++).toElement().text().toInt();
            }
            else
            {
                max.append(domList.at(i++).toElement().text().toInt());
                min.append(domList.at(i++).toElement().text().toInt());
//                value.append(domList.at(i++).toElement().text().toInt());
            }
            step.append(domList.at(i++).toElement().text().toInt());
            if(j == 0)
            {
                yearC = domList.at(i++).toElement().text().toInt();
            }
            _otherPara *otherPara = new _otherPara;
            otherPara->valuePos = domList.at(i++).toElement().text().toInt();
            otherPara->valueLength = domList.at(i++).toElement().text().toInt();
            otherValue.append(*otherPara);
        }

        endian = domList.at(i).toElement().text().toInt();
        QByteArray other;
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        varDesc.pVarDescDatetime->setMaxDate(QDate(maxyear, max.at(0), max.at(1)));
        varDesc.pVarDescDatetime->setMinDate(QDate(minyear, min.at(0), min.at(1)));
        varDesc.pVarDescDatetime->setDate(QDate(valueyear, value.at(0), value.at(1)));
        varDesc.pVarDescDatetime->setMaxTime(QTime(max.at(2), max.at(3), max.at(4)));
        varDesc.pVarDescDatetime->setMinTime(QTime(min.at(2), min.at(3), min.at(4)));
        varDesc.pVarDescDatetime->setTime(QTime(value.at(2), value.at(3), value.at(4)));
        varDesc.pVarDescDatetime->setStep(step);
        varDesc.pVarDescDatetime->setOtherValue(otherValue);
        varDesc.pVarDescDatetime->setOther(other);

        f->setVarDesc(varDesc);

        QDEBUG()<<"maxdate"<< f->getVarDesc().pVarDescDatetime->getMaxDate();
        QDEBUG()<<"mindate"<< f->getVarDesc().pVarDescDatetime->getMinDate();
//        QDEBUG()<<"date"<< f->getVarDesc().pVarDescDatetime->getDate();
        QDEBUG()<<"maxtime"<< f->getVarDesc().pVarDescDatetime->getMaxTime();
        QDEBUG()<<"mintime"<< f->getVarDesc().pVarDescDatetime->getMinTime();
//        QDEBUG()<<"time"<< f->getVarDesc().pVarDescDatetime->getTime();
        QDEBUG()<<"step"<< f->getVarDesc().pVarDescDatetime->getStep().toHex().toUpper();
        QDEBUG()<<"yearC"<<f->getVarDesc().pVarDescDatetime->getYearC();
        QDEBUG()<<"endian"<<f->getVarDesc().pVarDescDatetime->getEndian();
        QDEBUG()<<"other"<< f->getVarDesc().pVarDescDatetime->getOther().toHex().toUpper();
        for(int i=0; i<f->getVarDesc().pVarDescDatetime->getOtherValue().size(); i++)
        {
            QDEBUG()<<"valuepos"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valuePos;
            QDEBUG()<<"valuelength"<< f->getVarDesc().pVarDescDatetime->getOtherValue().at(i).valueLength;
        }
    }
    else if(VarType == VARSINGLE)
    {
        varDesc.pVarDescEnumberate = new VarDescEnumberate();
        int i = 0;
        varDesc.pVarDescEnumberate->setDefaultValue(domList.at(i++).toElement().text().toInt());

        QMap<int, QByteArray> item, itemReturn;
        int key = 0;
        QByteArray other, returnValue;
        key = domList.at(i++).toElement().text().toInt();
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        i++;
        for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
        {
            returnValue.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        item.insert(key, other);
        itemReturn.insert(key, returnValue);

        varDesc.pVarDescEnumberate->setItem(item);
        varDesc.pVarDescEnumberate->setItemReturn(itemReturn);
        f->setVarDesc(varDesc);

        QDEBUG()<<"default"<<f->getVarDesc().pVarDescEnumberate->getDefaultValue();
        for(int i=0; i<f->getVarDesc().pVarDescEnumberate->getItem().size(); i++)
        {
            QDEBUG()<<"value"<<f->getVarDesc().pVarDescEnumberate->getItem().keys().at(i);
            QDEBUG()<<"other"<<f->getVarDesc().pVarDescEnumberate->getItem().values().at(i).toHex().toUpper();
            QDEBUG()<<"return"<<f->getVarDesc().pVarDescEnumberate->getItemReturn().values().at(i).toHex().toUpper();
        }
    }
    else if(VarType == VAROUT)
    {
        varDesc.pVarDescEnumberate = new VarDescEnumberate();
        int i = 1;          //number没用到
        QMap<int, QByteArray> item, itemReturn;
        int key;
        for(int j=0; j<domList.at(0).toElement().text().toInt(); j++, i++)
        {
            QByteArray other, returnValue;
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                other.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            i++;
            for(int k=0; k<domList.at(i).toElement().text().length(); k+=2)
            {
                returnValue.append(domList.at(i).toElement().text().mid(k, 2).toInt(NULL, 16));
            }
            item.insert(key, other);
            itemReturn.insert(key, returnValue);
        }
        varDesc.pVarDescEnumberate->setItem(item);
        varDesc.pVarDescEnumberate->setItemReturn(itemReturn);
        f->setVarDesc(varDesc);

        for(int i=0; i<f->getVarDesc().pVarDescEnumberate->getItem().size(); i++)
        {
            QDEBUG()<<"value"<<f->getVarDesc().pVarDescEnumberate->getItem().keys().at(i);
            QDEBUG()<<"otherorder"<<f->getVarDesc().pVarDescEnumberate->getItem().values().at(i).toHex().toUpper();
            QDEBUG()<<"return"<<f->getVarDesc().pVarDescEnumberate->getItemReturn().values().at(i).toHex().toUpper();
        }
    }
    else if(VarType == VARINPUT)
    {
        QDEBUG()<<"输入变量";
    }
    else if(VarType == VAREVENT)
    {
        varDesc.pVarDescEnumberate = new VarDescEnumberate();
        QMap<int, QByteArray> itemReturn;
        QByteArray returnValue;
        for(int k=0; k<domList.at(0).toElement().text().length(); k+=2)
        {
            returnValue.append(domList.at(0).toElement().text().mid(k, 2).toInt(NULL, 16));
        }
        itemReturn.insert(0, returnValue);
        varDesc.pVarDescEnumberate->setItemReturn(itemReturn);
        f->setVarDesc(varDesc);

        for(int i=0; i<f->getVarDesc().pVarDescEnumberate->getItemReturn().size(); i++)
        {
            QDEBUG()<<"return"<<f->getVarDesc().pVarDescEnumberate->getItemReturn().values().at(i).toHex().toUpper();
        }
    }
    else
    {
        QDEBUG()<<"ERROR";
    }
}

void DetectXml::detectDisTypeDesc(QDomNode n, FunctionItem *f)
{
    QDEBUG()<< "解析显示";
    if(!f->getIsdisplay())
    {
        return;
    }

    int i = 0;
    QDomNodeList domListl = n.childNodes();
    f->setDisType(domListl.at(i++).toElement().text().toInt());
    f->setDisName(domListl.at(i++).toElement().text());
    i++;
    f->SetDisUnit(domListl.at(i++).toElement().text().toInt());
    detectDisPara(domListl.at(i++), f);     //解析显示参数
}

void DetectXml::detectDisPara(QDomNode n, FunctionItem *f)
{
    QDEBUG()<< "解析显示参数";
    int disType = f->getDisType();
    QDEBUG()<<"disType"<<disType;
    QDomNodeList domListl = n.childNodes();
    if(disType == DISSTRING)
    {
        int i = 0;
        disDesc.disStr = new _disString;
        disDesc.disStr->String = domListl.at(i++).toElement().text();
        f->setDisDesc(disDesc);
        QDEBUG()<<"string"<<f->getDisDesc().disStr->String;
    }
    else if(disType == DISPICTURE)
    {
        int i = 0;
        disDesc.disPic = new _disPictrue;
        disDesc.disPic->PicIndex = domListl.at(i++).toElement().text();
        f->setDisDesc(disDesc);
        QDEBUG()<<"picindex"<<f->getDisDesc().disPic->PicIndex;
    }
    else if(disType == DISDATE)
    {
        int i=0;
        disDesc.disDatetime = new _disDatetime;
        disDesc.disDatetime->disYear = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disMonth = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disDay = domListl.at(i++).toElement().text();
        f->setDisDesc(disDesc);
        QDEBUG()<<"year"<<f->getDisDesc().disDatetime->disYear;
        QDEBUG()<<"month"<<f->getDisDesc().disDatetime->disMonth;
        QDEBUG()<<"day"<<f->getDisDesc().disDatetime->disDay;
    }
    else if(disType == DISTIME)
    {
        int i=0;
        disDesc.disDatetime = new _disDatetime;
        disDesc.disDatetime->disHour = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disMin = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disSec = domListl.at(i++).toElement().text();
        f->setDisDesc(disDesc);
        QDEBUG()<<"hour"<<f->getDisDesc().disDatetime->disHour;
        QDEBUG()<<"min"<<f->getDisDesc().disDatetime->disMin;
        QDEBUG()<<"sec"<<f->getDisDesc().disDatetime->disSec;
    }
    else if(disType == DISNUMBER)
    {
        int i=0;
        disDesc.disNum = new _disNumber;
        disDesc.disNum->disPara = domListl.at(i++).toElement().text().toInt();
        disDesc.disNum->disScaling = domListl.at(i++).toElement().text().toInt();
        f->setDisDesc(disDesc);
        QDEBUG()<<"value"<<f->getDisDesc().disNum->disPara;
        QDEBUG()<<"scall"<<f->getDisDesc().disNum->disScaling;
    }
    else if((disType == DISCMD) || (disType == DISENUMBERATE))
    {
        disDesc.disEnum = new _disEnum;
        for(int j=0; j<domListl.size(); j++)
        {
            _disEnumPara *enumpara = new _disEnumPara;
            QDomNodeList domList2 = domListl.at(j).childNodes();

           enumpara->string = domList2.at(0).toElement().text();
           enumpara->pic = domList2.at(1).toElement().text();
           disDesc.disEnum->disEnumList.append(enumpara);
        }

        f->setDisDesc(disDesc);
        for(int i=0; i<f->getDisDesc().disEnum->disEnumList.size(); i++)
        {
            QDEBUG()<<"string"<<f->getDisDesc().disEnum->disEnumList.at(i)->string;
            QDEBUG()<<"picindex"<<f->getDisDesc().disEnum->disEnumList.at(i)->pic;
        }
    }
    else if(disType == DISSCROL)
    {
        int i=0;
        disDesc.disScroll = new _disScroll;
        disDesc.disScroll->disMax = domListl.at(i++).toElement().text().toInt();
        disDesc.disScroll->disMin = domListl.at(i++).toElement().text().toInt();
        disDesc.disScroll->disStep = domListl.at(i++).toElement().text().toInt();
        disDesc.disScroll->disDefault = domListl.at(i++).toElement().text().toInt();
        f->setDisDesc(disDesc);
        QDEBUG()<<"max"<<f->getDisDesc().disScroll->disMax;
        QDEBUG()<<"min"<<f->getDisDesc().disScroll->disMin;
        QDEBUG()<<"step"<<f->getDisDesc().disScroll->disStep;
        QDEBUG()<<"default"<<f->getDisDesc().disScroll->disDefault;
    }
    else if(disType == DISDATETIME)
    {
        int i=0;
        disDesc.disDatetime = new _disDatetime;
        disDesc.disDatetime->disYear = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disMonth = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disDay = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disHour = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disMin = domListl.at(i++).toElement().text();
        disDesc.disDatetime->disSec = domListl.at(i++).toElement().text();
        f->setDisDesc(disDesc);
        QDEBUG()<<"year"<<f->getDisDesc().disDatetime->disYear;
        QDEBUG()<<"month"<<f->getDisDesc().disDatetime->disMonth;
        QDEBUG()<<"day"<<f->getDisDesc().disDatetime->disDay;
        QDEBUG()<<"hour"<<f->getDisDesc().disDatetime->disHour;
        QDEBUG()<<"min"<<f->getDisDesc().disDatetime->disMin;
        QDEBUG()<<"sec"<<f->getDisDesc().disDatetime->disSec;
    }
    else
    {
        QDEBUG()<<"error";
    }
}

QString DetectXml::getDeviceName()
{
    return this->deviceName;
}

QList<FunctionItem*> DetectXml::getFunList()
{
    return listItem;
}
