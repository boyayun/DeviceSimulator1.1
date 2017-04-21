﻿#include "switchbutton.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

SwitchButton::SwitchButton(QWidget *parent): QWidget(parent)
{
    qDebug()<<"width"<<width();
    qDebug()<<"h"<<height();
//    resize(20, 50);

    checked = false;
    buttonStyle = ButtonStyle_CircleIn;

    bgColorOff = QColor(79, 79, 79);
    bgColorOn = QColor(102, 205, 0);

    sliderColorOff = QColor(255, 255, 255);
    sliderColorOn = QColor(255, 255, 255);

    textColorOff = QColor(255, 255, 255);
    textColorOn = QColor(255, 255, 255);

    textOff = "";
    textOn = "";

    imageOff = ":/image/btncheckoff1.png";
    imageOn = ":/image/btncheckon1.png";

    space = 2;
    rectRadius = 5;

    step = width() / 50;
    startX = LEFT;
    endX = LEFT;

    timer = new QTimer(this);
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

//    setFont(QFont("Microsoft Yahei", 15));
    setFont(QFont("楷体", 15, 75));
}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::mousePressEvent(QMouseEvent *)
{
    checked = !checked;
    emit checkedChanged(checked);

    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //状态切换改变后自动计算终点坐标
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            endX = LEFT + width() - width() / 2;
        } else if (buttonStyle == ButtonStyle_CircleIn) {
            endX = LEFT + width() - height();
        } else if (buttonStyle == ButtonStyle_CircleOut) {
            endX = LEFT + width() - height() + space;
        }
    } else {
        endX = LEFT;
    }

    timer->start();
}

void SwitchButton::resizeEvent(QResizeEvent *)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //尺寸大小改变后自动设置起点坐标为终点
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            startX = LEFT + width() - width() / 2;
        } else if (buttonStyle == ButtonStyle_CircleIn) {
            startX = LEFT + width() - height();
        } else if (buttonStyle == ButtonStyle_CircleOut) {
            startX = LEFT + width() - height() + space;
        }
    } else {
        startX = LEFT;
    }
    update();
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (buttonStyle == ButtonStyle_Image) {
        //绘制图片
        drawImage(&painter);
    } else {
        //绘制背景
        drawBg(&painter);
        //绘制滑块
        drawSlider(&painter);
        //绘制文字
        drawText(&painter);
    }
}

void SwitchButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(bgColorOff);
    } else {
        painter->setBrush(bgColorOn);
    }

    if (buttonStyle == ButtonStyle_Rect) {
        painter->drawRoundedRect(LEFT + rect().left(), rect().top(), rect().width(), rect().height(), rectRadius, rectRadius);
    } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(LEFT, TOP, width(), height());
        //半径为高度的一半
        int radius = rect.height() / 2;
        //圆的宽度为高度
        int circleWidth = rect.height();

        QPainterPath path;
        path.moveTo(LEFT + radius, LEFT + rect.left());
        path.arcTo(QRectF(LEFT + rect.left(), rect.top(), circleWidth, circleWidth), 90, 180);
        path.lineTo(LEFT + rect.width() - radius, rect.height());
        path.arcTo(QRectF(LEFT + rect.width() - rect.height(), rect.top(), circleWidth, circleWidth), 270, 180);
        path.lineTo(LEFT + radius, rect.top());

        painter->drawPath(path);
    } else if (buttonStyle == ButtonStyle_CircleOut) {
//        QRect rect(LEFT + space, space, width() - space * 2, height() - space * 2);
        painter->drawRoundedRect(LEFT + rect().left(), rect().top(), rect().width(), rect().height(), rectRadius, rectRadius);
    }

    painter->restore();
}

void SwitchButton::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(sliderColorOff);
    } else {
        painter->setBrush(sliderColorOn);
    }

    if (buttonStyle == ButtonStyle_Rect) {
        int sliderWidth = width() / 2 - space * 2;
        int sliderHeight = height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth , sliderHeight);
        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
    } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(LEFT, TOP, width(), height());
        int sliderWidth = rect.height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    } else if (buttonStyle == ButtonStyle_CircleOut) {
        QRect rect(LEFT, TOP, width() - space, height() - space);
        int sliderWidth = rect.height();
        QRect sliderRect(startX, space / 2, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void SwitchButton::drawText(QPainter *painter)
{
    painter->save();

    if (!checked) {
        painter->setPen(textColorOff);
        painter->drawText(LEFT + width() / 2, 0, width() / 2 - space, height(), Qt::AlignCenter, textOff);
    } else {
        painter->setPen(textColorOn);
        painter->drawText(LEFT + space, 0, width() / 2 + space * 2, height(), Qt::AlignCenter, textOn);
    }

    painter->restore();
}

void SwitchButton::drawImage(QPainter *painter)
{
    painter->save();

    QPixmap pix;

    if (!checked) {
        pix = QPixmap(imageOff);
    } else {
        pix = QPixmap(imageOn);
    }

    //自动等比例平滑缩放居中显示
    int targetWidth = pix.width();
    int targetHeight = pix.height();
    pix = pix.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int pixX = rect().center().x() - targetWidth / 2;
    int pixY = rect().center().y() - targetHeight / 2;
    QPoint point(pixX, pixY);
    painter->drawPixmap(point, pix);

    painter->restore();
}

void SwitchButton::updateValue()
{
    if (checked) {
        if (startX < endX) {
            startX = startX + step;
        } else {
            startX = endX;
            timer->stop();
        }
    } else {
        if (startX > endX) {
            startX = startX - step;
        } else {
            startX = endX;
            timer->stop();
        }
    }

    update();
}

void SwitchButton::setChecked(bool checked)
{
    if (this->checked != checked) {
        this->checked = checked;
        emit checkedChanged(checked);
        update();
    }
}

void SwitchButton::setButtonStyle(SwitchButton::ButtonStyle buttonStyle)
{
    this->buttonStyle = buttonStyle;
    update();
}

void SwitchButton::setBgColor(QColor bgColorOff, QColor bgColorOn)
{
    this->bgColorOff = bgColorOff;
    this->bgColorOn = bgColorOn;
    update();
}

void SwitchButton::setSliderColor(QColor sliderColorOff, QColor sliderColorOn)
{
    this->sliderColorOff = sliderColorOff;
    this->sliderColorOn = sliderColorOn;
    update();
}

void SwitchButton::setTextColor(QColor textColorOff, QColor textColorOn)
{
    this->textColorOff = textColorOff;
    this->textColorOn = textColorOn;
    update();
}

void SwitchButton::setText(QString textOff, QString textOn)
{
    this->textOff = textOff;
    this->textOn = textOn;
    update();
}

void SwitchButton::setImage(QString imageOff, QString imageOn)
{
    this->imageOff = imageOff;
    this->imageOn = imageOn;
    update();
}

void SwitchButton::setSpace(int space)
{
    this->space = space;
    update();
}

void SwitchButton::setRectRadius(int rectRadius)
{
    this->rectRadius = rectRadius;
    update();
}
