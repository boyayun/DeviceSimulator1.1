#include "controlnumber.h"
#include "ui_controlnumber.h"
#include <qwt_color_map.h>
#include <QtCore/qmath.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlNumber::ControlNumber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlNumber)
{
    ui->setupUi(this);
}

ControlNumber::ControlNumber(VarDesc v, QWidget *parent):
    QWidget(parent),ui(new Ui::ControlNumber)
{
    ui->setupUi(this);
    this->varDescNumber = v.pVarDescNumber;

    connect(ui->d_wheel, SIGNAL(valueChanged(double)), this, SLOT(setNum( double )));
    connect(ui->d_wheel, SIGNAL(wheelReleased()), this, SLOT(on_dial_sliderReleased()));

    QwtLinearColorMap *colorMap = new QwtLinearColorMap();
    colorMap->setColorInterval( Qt::blue, Qt::red );
    ui->Thermo->setColorMap( colorMap );
    ui->d_wheel->setWheelWidth(10);

    QStringList strList;

    strList.clear();
    strList.append("");
    strList.append("℃");
    strList.append("百分比");
    strList.append("千克");
    strList.append("伏特");
    strList.append("安培");
    strList.append("赫兹");
    strList.append("千瓦");
    strList.append("千瓦时");
    strList.append("小时");
    strList.append("分钟");
    strList.append("秒");
    strList.append("微克每立方米");
    strList.append("毫克每立方米");
    strList.append("千米每小时");
    strList.append("米");
    strList.append("毫米");
    strList.append("华氏度");
    strList.append("度");

    ui->label_2->setText(strList.at(varDescNumber->getUnit()));
    ui->d_wheel->setValue(varDescNumber->getDefaultValue()/varDescNumber->getScalling());
    ui->d_wheel->setSingleStep((double)1/varDescNumber->getScalling());
    QDEBUG()<<ui->d_wheel->singleStep();
    ui->d_wheel->setRange(varDescNumber->getMin()/varDescNumber->getScalling(), varDescNumber->getMax()/varDescNumber->getScalling());
    ui->Thermo->setScale(varDescNumber->getMin()/varDescNumber->getScalling(), varDescNumber->getMax()/varDescNumber->getScalling());
    qDebug()<<"This is the parameter of number:";
    qDebug()<<__FUNCTION__<<"max"<<varDescNumber->getMax();
    qDebug()<<varDescNumber->getMin();
    qDebug()<<varDescNumber->getScalling();
    qDebug()<<varDescNumber->getUnit();
}

ControlNumber::~ControlNumber()
{
    delete ui;
}

int16_t ControlNumber::getNumber()
{
    return this->ui->d_wheel->value()*varDescNumber->getScalling();
}

void ControlNumber::setNumber(int16_t number)
{
    this->ui->d_wheel->setValue(number/varDescNumber->getScalling());
}

void ControlNumber::on_dial_sliderReleased()
{
    QDEBUG()<<b;
    b = false;
    emit signalStateChanged(VARNUMBER);
}

void ControlNumber::setNum(double v)
{
    QString text;
    text.setNum(v, 'f', qLn(varDescNumber->getScalling())/qLn(10));

    ui->Thermo->setValue(v);
    ui->label->setText(text);
}
