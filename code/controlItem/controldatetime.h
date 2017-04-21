#ifndef CONTROLDATETIME_H
#define CONTROLDATETIME_H

#include <QWidget>
#include <QDateTimeEdit>
#include "define.h"

namespace Ui {
class ControlDateTime;
}

class ControlDateTime : public QWidget
{
    Q_OBJECT

public:
    explicit ControlDateTime(VarDesc v, QWidget *parent = 0);
    ~ControlDateTime();
    void setUiDatetime(const QDateTime &v);
    QDateTime getDatetime() const;

private:
    QDateTimeEdit *datetime;
signals:
    void signalStateChanged(uint8_t);

private slots:
    void datetimeChanged(const QDateTime &datetime);
};

#endif // CONTROLDATETIME_H
