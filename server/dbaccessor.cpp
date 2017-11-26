#include "dbaccessor.h"

#include "userdata.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QVariantMap>

#include <stdexcept>

#define DB_FILE_PATH "D:/db/"
#define LOG_FILE "D:/db/log.txt"

DBAccessor::DBAccessor()
{
}
DBAccessor::~DBAccessor()
{
    if (!_mutexMap.isEmpty())
    {
        QFile f(LOG_FILE);
        if (f.open(QFile::Append))
        {
            f.write("Memory leak: not all UserData are free\n");
            f.close();
        }
    }
}

UserData* DBAccessor::takeUD(QString &cardNum, void *borrower)
{
    if(_mutexMap.contains(cardNum))
    {
        qDebug() <<"Trying get access to allready using card";
        return 0;
    }
    bool flag = false;
    flag =_cardsCash.keys().contains(cardNum);

    if(!flag)
    {
        QJsonObject jo = dbGet(cardNum);
        if (!jo.isEmpty())
        {
            _cardsCash[cardNum] = jo;
            flag = true;
        }
    }

    if (flag)
    {

        const QJsonObject& jo = _cardsCash[cardNum];
        QMap<QString, Integer> moneyMap;
        const QMap<QString, QVariant>& varMap = jo["money"].toObject().toVariantMap();
        foreach (const QString& key, varMap.keys())
        {
            moneyMap[key].setVal(varMap[key].toString());
        }
        UserData* ud = new UserData(
                    jo["cardNum"].toString(),
                    jo["pin"].toString(),
                    jo["owner"].toString(),
                    QDate::fromString(jo["date"].toString()),
                    jo["daemons"].toString(),
                    moneyMap
                    );
        _mutexMap[ud->cardNum()]=borrower;
        return ud;
    }

    return 0;
}
void DBAccessor::updateUD(UserData* ud)
{
    QJsonObject jo = ud->toJsonObject();
    _cardsCash[jo["cardNum"].toString()]=jo;
    dbPut(jo);
    return;
}

void DBAccessor::freeUD(UserData *ud)
{
    _mutexMap.remove(ud->cardNum());
    delete ud;
}

bool DBAccessor::isBeingUsed(const QString &cardNum)
{
    return _mutexMap.contains(cardNum);
}

QJsonObject DBAccessor::dbGet(QString cardNum)
{
    QString filename(DB_FILE_PATH);
    filename.append(cardNum);
    QFile file(filename);
    if (file.exists())
    {
        file.open(QFile::ReadOnly);
        QJsonObject jo = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
        return jo;
    };
    QJsonObject empty;
    return empty;
}
void DBAccessor::dbPut(const QJsonObject& jsonObj)
{
    if (jsonObj["cardNum"].isUndefined())
    {
        qDebug()<<"dbPut error(1)";
        return;
    }

    QString filename(DB_FILE_PATH);
    filename.append(jsonObj["cardNum"].toString());

    QFile file (filename);
    if (!file.open(QFile::WriteOnly)){
        qDebug() <<"dbPut file openning error";
    }
    file.write(QJsonDocument(jsonObj).toJson());
    file.flush();
    file.close();
}
