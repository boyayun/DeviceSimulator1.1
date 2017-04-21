#ifndef FUNCTIONITEMWIDGET_H
#define FUNCTIONITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>

#include "define.h"
#include "controlItem/controlcmd.h"
#include "controlItem/controlnumber.h"
#include "controlItem/controldate.h"
#include "controlItem/controlenumberate.h"
#include "controlItem/controltime.h"
#include "controlItem/controlalarm.h"
#include "controlItem/controldatetime.h"

typedef struct _pdate
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
} *pDate;

typedef struct _ptime
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}*pTime;

typedef struct _pdatetime
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}*pDatetime;

union ControlWidget
{
    ControlCmd *controlCmd;
    ControlNumber *controlNumber;
    ControlEnumberate *controlEnumberate;
    ControlAlarm *controlAlarm;
    ControlDate *controlDate;
    ControlTime *controlTime;
    ControlDateTime *controlDatetime;
};

class FunctionItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FunctionItemWidget(FunctionItem *f, uchar *baseAddr);
    bool dealWithCommand(void *);
    void stopAlarm();

signals:
    void signalALarm(uint16_t alarmCode);
    void signalStatusChanged();
    void signalLog(QString log,uint8_t type);

public slots:
   void slotStateChanged(uint8_t dataType);
   void slotAlarm(uint16_t AlarmCode);

private:
    QLabel functionNameLabel;
    QVBoxLayout mainLayout;
    ControlWidget controlWidget;
    FunctionItem *functionItem;
    uchar *baseAddress;



    void init();

};

#endif // FUNCTIONITEMWIDGET_H
