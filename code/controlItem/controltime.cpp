#include "controltime.h"
#include "ui_controltime.h"

#define QDEBUG() qDebug()<<__FILE__<<__LINE__

ControlTime::ControlTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlTime)
{
    ui->setupUi(this);
}

ControlTime::ControlTime(VarDesc v, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ControlTime)
{
    ui->setupUi(this);

    const QColor knobColor = QColor( Qt::gray ).light( 130 );

    for (int i = 0; i < QwtAnalogClock::NHands; i++)
    {
        QColor handColor = QColor( Qt::red ).light( 150 );
        int width = 8;

        if ( i == QwtAnalogClock::SecondHand )
        {
            handColor = Qt::gray;
            width = 5;
        }

        QwtDialSimpleNeedle *hand = new QwtDialSimpleNeedle(
            QwtDialSimpleNeedle::Arrow, true, handColor, knobColor );
        hand->setWidth( width );

        ui->AnalogClock->setHand( static_cast<QwtAnalogClock::Hand>( i ), hand );
    }
    ui->AnalogClock->setReadOnly(true);
    ui->AnalogClock->setLineWidth(4);
    ui->AnalogClock->setFrameShadow(QwtDial::Sunken);

    varDescDatetime = v.pVarDescDatetime;
    QDEBUG()<<v.pVarDescDatetime->getTime();
    this->ui->timeEdit->setTime(varDescDatetime->getTime());
    connect(ui->timeEdit, SIGNAL(timeChanged(QTime)), ui->AnalogClock, SLOT(setTime(QTime)));
}

ControlTime::~ControlTime()
{
    delete ui;
}

QTime ControlTime::getTime()
{
    return this->ui->timeEdit->time();
}

void ControlTime::setTime(QTime t)
{
   this->ui->timeEdit->setTime(t);
}

void ControlTime::on_timeEdit_timeChanged(const QTime)
{
   emit signalStateChanged(VARTIME);
}
