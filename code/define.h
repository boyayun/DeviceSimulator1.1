#ifndef DEFINE
#define DEFINE
#include<QString>
#include<QDebug>
#include<QtSerialPort/QSerialPort>
#include<QQueue>
#include<stdint.h>
#include<QDate>
#include<QTime>

#define VERDION "V1.0"
#define AUTHOR "JiaQi.chen"

//#define QDEBUG qDebug()<<__FILE__<<__LINE__

#define VARCMD 1
#define VARNUMBER 2
#define VARENUMBERATE 3
#define VARALARM 4
#define VARDATE 5
#define VARTIME 6
#define VARDATETIME 7
#define VARSINGLE 8
#define VAROUT  9
#define VARINPUT  10
#define VAREVENT  11

#define DISSTRING 1
#define DISPICTURE 2
#define DISDATE 3
#define DISTIME 4
#define DISNUMBER 5
#define DISCMD 6
#define DISENUMBERATE 7
#define DISSCROL 8
#define DISDATETIME 9

#define DATATYPENULL "未知类型"
#define DATATYPEUINT8 "无符号字符型"
#define DATATYPEINT8 "有符号字符型"
#define DATATYPEUINT16 "无符号SHORT型"
#define DATATYPEINT16 "有符号SHORT型"
#define DATATYPEUINT32 "无符号LONG型"
#define DATATYPEINT32 "有符号LONG型"

#define VALUEBIGEND "1"     // 大端
#define VALUELITTLEEND "2"  // 小端

#define RETURNBYTE 0        //返回状态域
#define RETURNBIT  1        //返回状态位
#define RETURNNULL 2       //空

#define DIRWR 1
#define DIRRD 2
#define DIRWD 3

#define STATUSFIELD    "StatusField"         // 状态域
#define STATUSBIT      "StatusBit"           // 状态位

#define ROOT "DeviceDescription"    //根节点
#define HEADINFORMATION "DeviceInformation"         //设备头标记
#define DDVERSION "DD_Version"             //描述文件标准本号
#define DDFILEVER "DD_FileVer"             //描述文件版本号
#define DDDEVICETYPE "DD_Devictype"       //文件使用者类型
#define MANUFACTURERCODE "Manufacturer_Code" // 厂商编码
#define DDSTANDBY       "DD_Standby"        //支持睡眠
#define DEVICETYPEID "Device_TypeID"         //设备大小类
#define MODELID      "Model_ID"              // 设备型号代码
#define DEVICENAME "Device_Name"             //设备名称
#define DDURLLENGTH   "DD_URL_Length"       //URL长度
#define DDURL   "DD_URL"                   //描述文件地址
#define UPDATE       "Update"               //具备在线升级能力
#define SYNCHRONOUS  "Synchronous"          //具备时间同步能力

#define FUNCTIONLIST "FunctionList"         //功能列表标识
#define FUNCTION     "Function"             //功能描述标识
#define VARINDEX       "VarIndex"           //功能控制码
#define USERLEVELLIMIT "UserLevelLimit"     //功能使用权限
#define DISPLAY        "Display"            //是否显示
#define DIRECTION      "Direction"          //操作权限，1，只写：2：只读，3：读写

#define VARTYPEDESC    "VarTypeDesc"        //类型描述标识
#define VARTYPE        "VarType"            //功能类型
#define VARLENGTH      "VarLength"          //参数长度
#define DATAPOS        "DataPos"        //位置
#define DATATYPE       "DataType"           //数据类型

#define VARPARAMETERS  "VarParameters"      //类型参数标识

#define ITEM           "Item"               //
#define DEFAULTVALUE   "DefaultValue"       //
#define OTHER         "ThirdVarParameters"   //变量值0对应的操作指令

#define MAX             "Max"               //最大值
#define MIN             "Min"               //最小值
#define SCALLING        "Scalling"          //分辨率
#define UNIT            "Unit"              //单位
#define ITEMNUM         "ItemNum"           //子项数量
#define ALARMITEM        "AlarmItem"
#define ALARMCLASS      "AlarmClass"        //报警级别
#define ALARMCODE        "AlarmCode"
#define ALARMSTRING      "AlarmString"
#define ALARMBYTEPOS     "BytePos"
#define ALARMBITPOS      "BitPos"

#define YEAR            "Year"              //年
#define YEARMAX         "YearMax"           //年最大值
#define YEARMIN         "YearMin"           //年最小值
#define YEARSTEP        "YearStep"          //年步长
#define MONTH           "Month"             //y月
#define MONTHMAX        "MonthMax"          //月最大值
#define MONTHMIN        "MonthMin"          //月最小值
#define MONTHSTEP       "MonthStep"         //月步长
#define DAY             "Day"               //日
#define DAYMAX          "DayMax"            //日最大值
#define DAYMIN          "DayMin"            //日最小值
#define DAYSTEP         "DayStep"           //日步长
#define HOUR            "Hour"              //时
#define HOURMAX         "HourMax"           //时最大值
#define HOURMIN         "HourMin"           //时最小值
#define HOURSTEP        "HourStep"          //时步长
#define MINUTE          "Minute"            //分
#define MINUTEMAX       "MinuteMax"         //分最大值
#define MINUTEMIN       "MinuteMin"         //分最小值
#define MINUTESTEP      "MinuteStep"        //分步长
#define SECOND          "Second"            //分
#define SECONDMAX       "SecondMax"         //分最大值
#define SECONDMIN       "SecondMin"         //分最小值
#define SECONDSTEP      "SecondStep"        //分步长

#define DISTYPEDESC    "DisTypeDesc"       //显示描述标识
#define DISTYPE        "DisType"           //显示类型
#define DISPLAYTEXT    "DisplayText"       //显示字符串
#define DISPLAYICONINDEX "DisplayIconIndex"//显示图标编号
#define DISPARAMETERS "DisParameters"      //显示参数集合

#define DISPLAYSTRING "DisplayString"     //显示字符串
#define DISPLAYPICTUREINDEX "DisplayPictureIndex"//显示图标编号
#define DISPLAYYEAR    "DisplayYear"      //年显示
#define DISPLAYMONTH   "DisplayMonth"     //月显示
#define DISPLAYDAY      "DisplayDay"      //日显示

#define DISPLAYHOUR    "DisplayHour"     // 时显示
#define DISPLAYMINUTE  "DisplayMinute"   //分显示
#define DISPLAYSECOND  "DisplaySecond"   //秒显示
#define DISPLAYITEM    "DisplayItem"     //显示
#define DISPLAYITEMSTRING "DisplayItemString" //显示字符串
#define DISPLAYITEMPICTUREINDEX "DisplayPictureIndex" //显示图片索引

#define DISPLAYMAX     "DisplayMax"      //显示最大值
#define DISPLAYMIN     "DisplayMin"      //显示最小值
#define DISPLAYSTEP     "DisplayStep"    //显示步长
#define DISPLAYUNIT     "DisplayUnit"    //显示单位序号
#define DISPLAYDEFAULT  "DisplayDefault" //默认显示

#define DATAPOS         "DataPos"        //位置
#define DATATYPE        "DataType"       //数据类型

#define REPORTSTATE      "ReportState"  //上报状态标识
#define STATESTRUCT      "StateStruct"  //上报结构

typedef struct
{
    int valuePos;
    int valueLength;
}_otherPara;

class VarDescNumber                    //数字描述参数
{
public:
    VarDescNumber();
//    VarDescNumber(const VarDescNumber &v);
    int16_t getMax() const;
    void setMax(const int16_t &value);

    int16_t getMin() const;
    void setMin(const int16_t &value);

    int16_t getScalling() const;
    void setScalling(const int16_t &value);

    uint8_t getUnit() const;
    void setUnit(const uint8_t &value);

    int getDefaultValue() const;
    void setDefaultValue(const int &value);

    double getKfactor() const;
    void setKfactor(const double &value);

    double getCfactor() const;
    void setCfactor(const double &value);

    int getEndian() const;
    void setEndian(const int &value);

    QByteArray getOther() const;
    void setOther(const QByteArray &value);

    _otherPara getOtherValue() const;
    void setOtherValue(const _otherPara &value);

private:
    int16_t Max;
    int16_t Min;
    int16_t Scalling;
    uint8_t Unit;
    int defauleValue;
    double kFactor;
    double cFactor;
    int endian;
    QByteArray other;
    _otherPara otherValue;
};

class VarDescEnumberate               //枚举描述参数
{
public:
    VarDescEnumberate();
//    VarDescEnumberate(const VarDescEnumberate &v);

    int getDefaultValue() const;
    void setDefaultValue(const int &value);

    QMap<int, QByteArray> getItem() const;
    void setItem(const QMap<int, QByteArray> &value);

    QMap<int, QByteArray> getItemReturn() const;
    void setItemReturn(const QMap<int, QByteArray> &value);
private:
    int defauleValue;
    QStringList DisItem;
    QMap<int, QByteArray> Item;
    QMap<int, QByteArray> itemReturn;
};

class VarDescAlarm                    //报警描述参数
{
public:
    VarDescAlarm();
//    VarDescAlarm(const VarDescAlarm &v);

    QByteArray getBytePos() const;
    void setBytePos(const QByteArray &value);

    QByteArray getBitPos() const;
    void setBitPos(const QByteArray &value);

    QList<uint16_t> getAlarmCode() const;
    void setAlarmCode(const QList<uint16_t> &value);

    QByteArray getAlarmClass() const;
    void setAlarmClass(const QByteArray &value);

    QStringList getAlarmString() const;
    void setAlarmString(const QStringList &value);
private:
    QByteArray BytePos;
    QByteArray BitPos;
    QList<uint16_t> AlarmCode;
    QByteArray AlarmClass;
    QStringList AlarmString;
};

class VarDescDatetime                   //日期时间描述参数
{
    QDate Date;
    QDate MaxDate;
    QDate MinDate;
    QTime Time;
    QTime MaxTime;
    QTime MinTime;

    int yearC;
    int endian;
    QByteArray step;
    QByteArray other;
    QList<_otherPara>otherValue;
public:
//    VarDescTime(const VarDescTime &v);
    VarDescDatetime();

    QDate getDate() const;
    void setDate(const QDate &value);

    QDate getMaxDate() const;
    void setMaxDate(const QDate &value);

    QDate getMinDate() const;
    void setMinDate(const QDate &value);

    QTime getTime() const;
    void setTime(const QTime &value);

    QTime getMaxTime() const;
    void setMaxTime(const QTime &value);

    QTime getMinTime() const;
    void setMinTime(const QTime &value);

    QByteArray getStep() const;
    void setStep(const QByteArray &value);

    int getYearC() const;
    void setYearC(const int &value);

    int getEndian() const;
    void setEndian(const int &value);

    QByteArray getOther() const;
    void setOther(const QByteArray &value);

    QList<_otherPara> getOtherValue() const;
    void setOtherValue(const QList<_otherPara> &value);
};

union VarDesc
{
    VarDescNumber *pVarDescNumber;
    VarDescEnumberate *pVarDescEnumberate;
    VarDescAlarm *pVarDescAlarm;
    VarDescDatetime *pVarDescDatetime;
};

typedef struct
{
    QString String;
}_disString;

typedef struct
{
    QString PicIndex;
}_disPictrue;

typedef struct
{
    int disPara;
    int disScaling;
}_disNumber;

typedef struct
{
    QString value;
    QString string;
    QString pic;
}_disEnumPara;

typedef struct
{
    QList<_disEnumPara*>disEnumList;
}_disEnum;

typedef struct
{
    int disMax;
    int disMin;
    int disStep;
    int disDefault;
}_disScroll;

typedef struct
{
    QString disYear;
    QString disMonth;
    QString disDay;
    QString disHour;
    QString disMin;
    QString disSec;
}_disDatetime;

union _disDesc
{
    _disString *disStr;
    _disPictrue *disPic;
    _disNumber *disNum;
    _disEnum *disEnum;
    _disScroll *disScroll;
    _disDatetime *disDatetime;
};

class FunctionItem
{
    uint16_t varIndex;          //变量类型
    uint8_t funLimit;           //功能使用权限
    bool isDisplay;             //是否显示
    uint8_t direction;          //操作权限 1

    int cmdType;
    uint8_t varType;
    int returnType;
    uint8_t datalength;
    uint8_t dataPos;          //位置
    int varLength;
    uint8_t dataType;
    VarDesc vardesc;

    int disType;
    QString disName;
    int disUnit;
    _disDesc disDesc;

public:
    FunctionItem();

    uint16_t getVarIndex() const;
    void setVarIndex(const uint16_t &value);

    int getFunLimit() const;
    void setFunLimit(const int &value);

    bool getIsdisplay() const;
    void setIsdisplay(const bool &value);

    uint8_t getDirection() const;
    void setDirection(const uint8_t &value);

    int getCmdType() const;
    void setCmdType(const int &value);

    uint8_t getVarType() const;
    void setVarType(const uint8_t &value);

    int getReturnType() const;
    void setReturnType(const int &value);

    uint8_t getDataPos() const;
    void setDataPos(const uint8_t &value);

    uint8_t getDatalength() const;
    void setDatalength(const uint8_t &value);

    int getVarLength() const;
    void setVarLength(const int &value);

    uint8_t getDataType() const;
    void setDataType(const uint8_t &value);

    VarDesc getVarDesc() const;
    void setVarDesc(const VarDesc &v);
//    void setVarDesc(const VarDescCmd &v);
//    void setVarDesc(const VarDescNumber &v);
//    void setVarDesc(const VarDescEnumberate &v);
//    void setVarDesc(const VarDescAlarm &v);
//    void setVarDesc(const VarDescDate &v);
//    void setVarDesc(const VarDescTime &v);

    int getDisType() const;
    void setDisType(const int &value);

    QString getDisName() const;
    void setDisName(const QString &value);

    int getDisUnit() const;
    void SetDisUnit(const int &value);

    _disDesc getDisDesc() const;
    void setDisDesc(const _disDesc &v);
//    void setDisDesc(const _disString &v);
//    void setDisDesc(const _disPictrue &v);
//    void setDisDesc(const _disNumber &v);
//    void setDisDesc(const _disCmd &v);
//    void setDisDesc(const _disEnum &v);
//    void setDisDesc(const _disScroll &v);
//    void setDisDesc(const _disDatetime &v);
};

#endif // DEFINE
