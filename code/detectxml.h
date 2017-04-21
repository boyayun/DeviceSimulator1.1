#ifndef DETECTXML_H
#define DETECTXML_H
#include"define.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>



class DetectXml
{
public:
    DetectXml(QString path);
    void detectDeviceDescribe(QDomNode n);
    void detectHeadInformation(QDomNode n);
    void detectFunctionList(QDomNode n);
    void detectFunction(QDomNode n);
    void detectVarTypeDesc(QDomNode n,FunctionItem *f);
    void detectVarParameters(QDomNode n,FunctionItem *f);
    void detectDisTypeDesc(QDomNode n,FunctionItem *f);
    void detectDisPara(QDomNode n,FunctionItem *f);
    QString getDeviceName();

    QList<FunctionItem *> getFunList();
    QString getDeviceID();
private:
    QList<FunctionItem*>listItem;
    QString deviceName;
    VarDesc varDesc;
    _disDesc disDesc;
};

#endif // DETECTXML_H
