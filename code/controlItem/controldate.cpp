#include "controldate.h"
#include "ui_controldate.h"

#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlDate::ControlDate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlDate)
{
    ui->setupUi(this);
}

ControlDate::ControlDate(VarDesc v, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ControlDate)
{
    ui->setupUi(this);
    this->varDescDatetime = v.pVarDescDatetime;
    this->ui->dateEdit->setDate(v.pVarDescDatetime->getDate());
    qDebug()<<v.pVarDescDatetime->getDate();
}

ControlDate::~ControlDate()
{
    delete ui;
}

QDate ControlDate::getDate()
{
   QDEBUG()<<this->ui->dateEdit->date();
   return this->ui->dateEdit->date();
}

void ControlDate::setDate(QDate d)
{
    this->ui->dateEdit->setDate(d);
}

void ControlDate::on_dateEdit_dateChanged(const QDate &date)
{
    QDEBUG()<<date;
   emit signalStateChanged(VARDATE);
}
