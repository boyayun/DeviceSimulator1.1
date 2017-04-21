#include "controlenumberate.h"
#include "ui_controlenumberate.h"

ControlEnumberate::ControlEnumberate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlEnumberate)
{
    ui->setupUi(this);
}

ControlEnumberate::ControlEnumberate(VarDesc v, _disDesc dis, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ControlEnumberate)
{
    ui->setupUi(this);
    qDebug()<<__FUNCTION__<<__LINE__;
    qDebug()<<v.pVarDescEnumberate->getItem();
    for(int i=0; i<dis.disEnum->disEnumList.size(); i++)
    {
        this->ui->comboBox->addItem(dis.disEnum->disEnumList.at(i)->string);
    }
}

ControlEnumberate::~ControlEnumberate()
{
    delete ui;
}

uint8_t ControlEnumberate::getCurrentStatus()
{
    return this->ui->comboBox->currentIndex();
}

void ControlEnumberate::setCurrentStatus(uint8_t index)
{
   this->ui->comboBox->setCurrentIndex(index);
}

void ControlEnumberate::on_comboBox_currentIndexChanged(int)
{
   emit signalStateChanged(VARENUMBERATE);
}
