#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include <QWidget>
#include"define.h"
#include"functionitemwidget.h"
#include"UserUartLink.h"
#include<QTimer>


typedef struct _frame_struct
{
    uint16_t frameHead;
    uint8_t frameControl;
    uint8_t frameLength;
    uint8_t frameType;
}*pFrameStruct;

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QList<FunctionItem *> &l);

    QString getDeviceId() const;
    void setDeviceId(const QString &value);

signals:
    void signalSendReport(uchar *,uint8_t length);
    void signallog(QString log,uint8_t type);

public slots:
    void slotReceivedFrame(QByteArray receive);

    void slotReportState(); //�㱨֡
    void slotQueryState(bool);
    void slotInvalid();
    void slotAlarm(uint16_t alarmCode);       //����֡
    void slotIsNeedPrintRF(bool i);
    void slotIsNeedPrintQueryState(bool i);
    void slotReportTimeChanged(int s);
private:
    QList<FunctionItemWidget *> controlList;
    QGridLayout mainLayout;
    QList<uint16_t>commandList;
    QList<uint8_t>commandTypeList;
    QList<FunctionItem *>list;
    uint8_t stateLength;
    QTimer reportTimer;
    
    void receivedControlFrame(uint8_t *,int len);    
    void constructComandList();

    uint8_t *statemachine;
    uchar *sendFrame;
    bool isNeedPrintRF;//�Ƿ���Ҫ��ӡ�㱨֡
    bool isNeedPrintQueryState;
};

#endif // CONTROLPANEL_H
