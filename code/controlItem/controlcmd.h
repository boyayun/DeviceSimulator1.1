#ifndef CONTROLCMD_H
#define CONTROLCMD_H

#include <QWidget>
#include "define.h"
#include "customControl/switchbutton.h"

namespace Ui {
class ControlCmd;
}

class ControlCmd : public QWidget
{
    Q_OBJECT

public:
    explicit ControlCmd(QWidget *parent = 0);
    ControlCmd(VarDesc v, _disDesc dis, bool isDispaly, QWidget *parent=0);
    ~ControlCmd();

    uint8_t  getStatus();
    void setStatus(uint8_t v);

private slots:
    void on_horizontalSlider_valueChanged(bool);

private:
    Ui::ControlCmd *ui;
    FunctionItem *function;
    VarDesc varDesc;
signals:
    void signalStateChanged(uint8_t);
};
#endif // CONTROLCMD_H
