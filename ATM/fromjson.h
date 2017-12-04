#ifndef FROMJSON_H
#define FROMJSON_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QJsonValue>
#include <QDebug>

class FromJson : public QObject
{
    Q_OBJECT
public:

    explicit FromJson(const QString& resp, QObject *parent = nullptr);
    bool getBool(const QString& str);
    QString getString(const QString& str);
    QString getString(const QJsonObject& ob, const QString& str);
    bool hasField(const QString& str);
    QJsonObject getObject(const QString& str);

private:

    QJsonDocument doc;
    QJsonObject jsOb;
};

#endif // FROMJSON_H
