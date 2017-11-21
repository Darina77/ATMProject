#include "dbaccessor.h"

#include "userdata.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#define DB_FILE_PATH "D:/db/"


DBAccessor::DBAccessor()
{
}
DBAccessor::~DBAccessor()
{
}

UserData* DBAccessor::takeUD(QString &cardNum)
{
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
        return new UserData(
                jo["cardNum"].toString(),
                jo["pin"].toString(),
                jo["owner"].toString(),
                jo["date"].toString(),
                jo["daemons"].toString(),
                jo["money"].toString()
                    );
    }

    return 0;
}
void DBAccessor::putUD(UserData* ud)
{
    QJsonObject jo = ud->toJsonObject();
    _cardsCash[jo["cardNum"].toString()]=jo;
    dbPut(jo);
    return;
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
