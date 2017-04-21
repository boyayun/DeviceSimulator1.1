#ifndef CONTROLDATE_H
#define CONTROLDATE_H

#include <QWidget>
#include "define.h"
#include "qwt_date.h"

namespace Ui {
class ControlDate;
}

class ControlDate : public QWidget
{
    Q_OBJECT

public:
    explicit ControlDate(QWidget *parent = 0);
    ControlDate(VarDesc v,QWidget *parent = 0);
    ~ControlDate();
    QDate getDate();
    void setDate(QDate d);

private:
    Ui::ControlDate *ui;
    VarDescDatetime *varDescDatetime;
    QwtDate *date;

signals:
    void signalStateChanged(uint8_t);

private slots:
    void on_dateEdit_dateChanged(const QDate &date);
};

#endif // CONTROLDATE_H
