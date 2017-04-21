#include "controlcmd.h"
#include "ui_controlcmd.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlCmd::ControlCmd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlCmd)
{
    ui->setupUi(this);
}

ControlCmd::ControlCmd(VarDesc v, _disDesc dis, bool isDispaly, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ControlCmd)
{
    ui->setupUi(this);
    varDesc = v;
    if(isDispaly)
    {
        ui->switchButton->setText(dis.disEnum->disEnumList.at(1)->string, dis.disEnum->disEnumList.at(0)->string);
    }
    else
    {
        ui->switchButton->setText("关闭", "打开");
    }
    connect(ui->switchButton, SIGNAL(checkedChanged(bool)), this, SLOT(on_horizontalSlider_valueChanged(bool)));
}

uint8_t ControlCmd::getStatus()
{
    return ui->switchButton->getChecked();
}

void ControlCmd::setStatus(uint8_t v)
{
    ui->switchButton->setChecked((bool)v);
}

ControlCmd::~ControlCmd()
{
    delete ui;
}

void ControlCmd::on_horizontalSlider_valueChanged(bool)
{
    emit signalStateChanged(VARCMD);
}
