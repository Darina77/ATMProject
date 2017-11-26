#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

#include <QMap>
#include <QDate>

#include "integer.h"

class UserData {
public:
    UserData(QString cardNum, QString pin, QString owner, QDate date, QString daemons, QMap<QString, Integer> money)
        :_cardNum(cardNum), _pin(pin), _owner(owner), _date(date), _daemons(daemons), _money(money)
    {

        if (!_money.contains("UAH"))
            _money["UAH"].setVal("0");

    }
    ~UserData(){}

    const QString& cardNum() const {return _cardNum;}
    const QString& pin() const {return _pin;}
    const QString& owner() const {return _owner;}
    const QDate& date() const {return _date;}
    const QString& daemons() const {return _daemons;}
    const QMap<QString, Integer>& money() const {return _money;}

    void setPin(QString in) { _pin = in;}
    void setOwner(QString in) {_owner = in;}
    void setDate(QDate in) {_date = in;}
    void setDaemons(QString in) {_daemons = in;}
    void setMoney(QString key, QString val) {/*if (_money.contains(key)) */_money[key].setVal(val);}

    QString toJson()
    {
        return QJsonDocument(toJsonObject()).toJson();
    }
    QJsonObject toJsonObject()
    {
        QJsonObject jo;
        jo["cardNum"]=cardNum();
        jo["pin"]=pin();
        jo["owner"]=owner();
        jo["date"]=date().toString();
        jo["daemons"]=daemons();
        QJsonObject jmoney;
        foreach (const QString& key, money().keys()) {
            jmoney[key]=Integer(_money[key].toString()).toString();
        }
        jo["money"]=jmoney;
        return jo;
    }

private:
    UserData(const UserData&);
    operator=(UserData);

    QString _cardNum;
    QString _pin;
    QString _owner;
    QDate _date;
    QString _daemons;
    QMap<QString,Integer> _money;

};


/*
какая информация завязана на карточку?
-номер
-пин
-владелец
-дата получения

вместе с тем, и оддельно
- демоны

подобно же
- остаток на счету
*/
#endif // USERDATA_H
