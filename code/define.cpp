#include<define.h>

VarDescNumber::VarDescNumber()
{
   this->Max = 100;
   this->Min = 0;
    this->Scalling = 1;
}

//VarDescNumber::VarDescNumber(const VarDescNumber &v)
//{
//   this->Max = v.getMax();
//    this->Min = v.getMin();
//    this->Scalling = v.getScalling();
//    this->Unit = v.getUnit();
//}

int16_t VarDescNumber::getMax() const
{
    return Max;
}

void VarDescNumber::setMax(const int16_t &value)
{
    Max = value;
}

int16_t VarDescNumber::getMin() const
{
    return Min;
}

void VarDescNumber::setMin(const int16_t &value)
{
    Min = value;
}

int16_t VarDescNumber::getScalling() const
{
    return Scalling;
}

void VarDescNumber::setScalling(const int16_t &value)
{
    Scalling = value;
}

uint8_t VarDescNumber::getUnit() const
{
    return Unit;
}

void VarDescNumber::setUnit(const uint8_t &value)
{
    Unit = value;
}

int VarDescNumber::getDefaultValue() const
{
    return defauleValue;
}

void VarDescNumber::setDefaultValue(const int &value)
{
    defauleValue = value;
}

double VarDescNumber::getKfactor() const
{
    return kFactor;
}

void VarDescNumber::setKfactor(const double &value)
{
    kFactor = value;
}

double VarDescNumber::getCfactor() const
{
    return cFactor;
}

void VarDescNumber::setCfactor(const double &value)
{
    cFactor = value;
}

int VarDescNumber::getEndian() const
{
    return endian;
}

void VarDescNumber::setEndian(const int &value)
{
    endian = value;
}

QByteArray VarDescNumber::getOther() const
{
    return other;
}

void VarDescNumber::setOther(const QByteArray &value)
{
    other = value;
}

_otherPara VarDescNumber::getOtherValue() const
{
    return otherValue;
}

void VarDescNumber::setOtherValue(const _otherPara &value)
{
    otherValue = value;
}

VarDescEnumberate::VarDescEnumberate()
{

}

//VarDescEnumberate::VarDescEnumberate(const VarDescEnumberate &v)
//{
//   this->Item = v.getItem();
//   this->DisItem = v.getDisItem();
//}

int VarDescEnumberate::getDefaultValue() const
{
    return defauleValue;
}

void VarDescEnumberate::setDefaultValue(const int &value)
{
    defauleValue = value;
}

QMap<int, QByteArray> VarDescEnumberate::getItem() const
{
    return Item;
}

void VarDescEnumberate::setItem(const QMap<int, QByteArray> &value)
{
    Item = value;
}

QMap<int, QByteArray> VarDescEnumberate::getItemReturn() const
{
    return itemReturn;
}

void VarDescEnumberate::setItemReturn(const QMap<int, QByteArray> &value)
{
    itemReturn = value;
}

VarDescAlarm::VarDescAlarm()
{

}

//VarDescAlarm::VarDescAlarm(const VarDescAlarm &v)
//{

//    this->AlarmString = v.getAlarmString();
//    this->AlarmCode = v.getAlarmCode();
//    this->AlarmClass = v.getAlarmClass();
//    this->BytePos = v.getBytePos();
//    this->BitPos = v.getBitPos();
//}

QStringList VarDescAlarm::getAlarmString() const
{
    return AlarmString;
}

void VarDescAlarm::setAlarmString(const QStringList &value)
{
    AlarmString = value;
}
QList<uint16_t> VarDescAlarm::getAlarmCode() const
{
    return AlarmCode;
}

void VarDescAlarm::setAlarmCode(const QList<uint16_t> &value)
{
    AlarmCode = value;
}
QByteArray VarDescAlarm::getAlarmClass() const
{
    return AlarmClass;
}

void VarDescAlarm::setAlarmClass(const QByteArray &value)
{
    AlarmClass = value;
}

QByteArray VarDescAlarm::getBytePos() const
{
    return BytePos;
}

void VarDescAlarm::setBytePos(const QByteArray &value)
{
    BytePos = value;
}

QByteArray VarDescAlarm::getBitPos() const
{
    return BitPos;
}

void VarDescAlarm::setBitPos(const QByteArray &value)
{
    BitPos = value;
}

//VarDescTime::VarDescTime(const VarDescTime &v)
//{
//    this->Time  = v.getTime();
//    this->MinTime = v.getMinTime();
//    this->MaxTime = v.getMaxTime();
//}

VarDescDatetime::VarDescDatetime()
{

}

QDate VarDescDatetime::getDate() const
{
    return Date;
}

void VarDescDatetime::setDate(const QDate &value)
{
    Date = value;
}

QDate VarDescDatetime::getMaxDate() const
{
    return MaxDate;
}

void VarDescDatetime::setMaxDate(const QDate &value)
{
    MaxDate = value;
}

QDate VarDescDatetime::getMinDate() const
{
    return MinDate;
}

void VarDescDatetime::setMinDate(const QDate &value)
{
    MinDate = value;
}

QTime VarDescDatetime::getTime() const
{
    return Time;
}

void VarDescDatetime::setTime(const QTime &value)
{
    Time = value;
}

QTime VarDescDatetime::getMaxTime() const
{
    return MaxTime;
}

void VarDescDatetime::setMaxTime(const QTime &value)
{
    MaxTime = value;
}

QTime VarDescDatetime::getMinTime() const
{
    return MinTime;
}

void VarDescDatetime::setMinTime(const QTime &value)
{
    MinTime = value;
}

QByteArray VarDescDatetime::getStep() const
{
    return step;
}

void VarDescDatetime::setStep(const QByteArray &value)
{
    step = value;
}

int VarDescDatetime::getYearC() const
{
    return yearC;
}

void VarDescDatetime::setYearC(const int &value)
{
    yearC = value;
}

int VarDescDatetime::getEndian() const
{
    return endian;
}

void VarDescDatetime::setEndian(const int &value)
{
    endian = value;
}

QByteArray VarDescDatetime::getOther() const
{
    return other;
}

void VarDescDatetime::setOther(const QByteArray &value)
{
    other = value;
}

QList<_otherPara> VarDescDatetime::getOtherValue() const
{
    return otherValue;
}

void VarDescDatetime::setOtherValue(const QList<_otherPara> &value)
{
    otherValue = value;
}

FunctionItem::FunctionItem()
{
    this->datalength = 0; //报警变量
    this->dataPos = 255;
}

uint16_t FunctionItem::getVarIndex() const
{
    return varIndex;
}

void FunctionItem::setVarIndex(const uint16_t &value)
{
    varIndex = value;
}

int FunctionItem::getFunLimit() const
{
    return funLimit;
}

void FunctionItem::setFunLimit(const int &value)
{
    funLimit = value;
}

bool FunctionItem::getIsdisplay() const
{
    return isDisplay;
}

void FunctionItem::setIsdisplay(const bool &value)
{
    isDisplay = value;
}

uint8_t FunctionItem::getDirection() const
{
    return direction;
}

void FunctionItem::setDirection(const uint8_t &value)
{
    direction = value;
}

int FunctionItem::getCmdType() const
{
    return cmdType;
}

void FunctionItem::setCmdType(const int &value)
{
    cmdType = value;
}

uint8_t FunctionItem::getVarType() const
{
    return varType;
}

void FunctionItem::setVarType(const uint8_t &value)
{
    varType = value;
}

int FunctionItem::getReturnType() const
{
    return returnType;
}

void FunctionItem::setReturnType(const int &value)
{
    returnType = value;
}

uint8_t FunctionItem::getDataPos() const
{
    return dataPos;
}

void FunctionItem::setDataPos(const uint8_t &value)
{
    dataPos = value;
}

uint8_t FunctionItem::getDatalength() const
{
    return datalength;
}

void FunctionItem::setDatalength(const uint8_t &value)
{
    datalength = value;
}

int FunctionItem::getVarLength() const
{
    return varLength;
}

void FunctionItem::setVarLength(const int &value)
{
    varLength = value;
}

void FunctionItem::setDataType(const uint8_t &value)
{
    dataType = value;
}

uint8_t FunctionItem::getDataType() const
{
    return dataType;
}

VarDesc FunctionItem::getVarDesc() const
{
   return this->vardesc;
}

void FunctionItem::setVarDesc(const VarDesc &v)
{
    vardesc = v;
}

//void FunctionItem::setVarDesc(const VarDescCmd &v)
//{
//    this->vardesc.pVarDescCmd = new VarDescCmd(v);
//}

//void FunctionItem::setVarDesc(const VarDescNumber &v)
//{
//    this->vardesc.pVarDescNumber  =new VarDescNumber(v);
//    qDebug()<<__FUNCTION__<<vardesc.pVarDescNumber->getMax();
//}

//void FunctionItem::setVarDesc(const VarDescEnumberate &v)
//{
//    this->vardesc.pVarDescEnumberate = new VarDescEnumberate(v);
//}

//void FunctionItem::setVarDesc(const VarDescAlarm &v)
//{
//    this->vardesc.pVarDescAlarm = new VarDescAlarm(v);
//}

//void FunctionItem::setVarDesc(const VarDescDate &v)
//{
//    this->vardesc.pVarDescDate = new VarDescDate(v);
//}

//void FunctionItem::setVarDesc(const VarDescTime &v)
//{
//    this->vardesc.pVarDescTime = new VarDescTime(v);
//}

int FunctionItem::getDisType() const
{
    return disType;
}

void FunctionItem::setDisType(const int &value)
{
    disType = value;
}

QString FunctionItem::getDisName() const
{
    return disName;
}

void FunctionItem::setDisName(const QString &value)
{
    disName = value;
}

int FunctionItem::getDisUnit() const
{
    return disUnit;
}

void FunctionItem::SetDisUnit(const int &value)
{
    disUnit = value;
}

_disDesc FunctionItem::getDisDesc() const
{
    return disDesc;
}

void FunctionItem::setDisDesc(const _disDesc &v)
{
    disDesc = v;
}
