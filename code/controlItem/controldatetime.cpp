#include "controldatetime.h"
//#include "ui_controldatetime.h"
#include <QGridLayout>

#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlDateTime::ControlDateTime(VarDesc v, QWidget *parent) :
    QWidget(parent)//,
//    ui(new Ui::ControlDateTime)
{
//    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(this);
    datetime = new QDateTimeEdit(this);
    datetime->setDisplayFormat("yyyy/M/d H:mm:ss");
    connect(datetime, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(datetimeChanged(QDateTime)));

    gridLayout->addWidget(datetime);
    datetime->setDate(v.pVarDescDatetime->getDate());
    datetime->setTime(v.pVarDescDatetime->getTime());
}

ControlDateTime::~ControlDateTime()
{
//    delete ui;
}

QDateTime ControlDateTime::getDatetime() const
{
    return datetime->dateTime();
}

void ControlDateTime::setUiDatetime(const QDateTime &v)
{
    datetime->setDateTime(v);
}

void ControlDateTime::datetimeChanged(const QDateTime &datetime)
{
    QDEBUG()<<datetime;
    emit signalStateChanged(VARDATETIME);
}
