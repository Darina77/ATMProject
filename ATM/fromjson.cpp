#include "fromjson.h"

FromJson::FromJson(const QString& resp, QObject *parent)
    : QObject(parent), doc(QJsonDocument::fromJson(resp.toUtf8())), jsOb()
{
    if(!doc.isNull())
      {
          if(doc.isObject())
          {
              jsOb = doc.object();
          }
          else
          {
              qDebug() << "Document is not an object";
          }
      }
    else
    {
       qDebug() << "Invalid JSON...\n" << resp;
    }
}

bool FromJson::getBool(const QString& str)
{
    if (jsOb[str].isUndefined())
    {
        qDebug()<<"Invalid JSON...\n";
        return false;
    } else {
       QJsonValue v = jsOb[str];
       if (v.isBool())
       {
          return v.toBool();
       } else {
          qDebug()<<"Invalid JSON...\n";
          return false;
       }
    }
}

QJsonObject FromJson::getObject(const QString& str)
{
    if (jsOb[str].isUndefined())
    {
        qDebug()<<"Invalid JSON...\n";
        return QJsonObject();
    } else {
       QJsonValue v = jsOb[str];

       if (v.isObject())
       {
          return v.toObject();
       } else {
          qDebug()<<"Invalid JSON...\n";
          return QJsonObject();
       }
    }
}

QString FromJson::getString(const QString& str)
{
    if (jsOb[str].isUndefined())
    {
        qDebug()<<"Invalid JSON...\n";
        return false;
    } else {
       QJsonValue v = jsOb[str];

       if (v.isString())
       {
          return v.toString();
       } else {
          qDebug()<<"Invalid JSON...\n";
          return "";
       }
    }
}

QString FromJson::getString(const QJsonObject& ob, const QString& str)
{
    if (ob[str].isUndefined())
    {
        qDebug()<<"Invalid JSON...\n";
        return false;
    } else {
       QJsonValue v = ob[str];

       if (v.isString())
       {
          return v.toString();
       } else {
          qDebug()<<"Invalid JSON...\n";
          return "";
       }
    }
}

bool FromJson::hasField(const QString& str)
{
   return jsOb.contains(str);
}

