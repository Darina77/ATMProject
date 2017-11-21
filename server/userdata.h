#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class UserData {
public:
    UserData(QString cardNum, QString pin, QString owner, QString date, QString daemons, QString money)
        :_cardNum(cardNum), _pin(pin), _owner(owner), _date(date), _daemons(daemons), _money(money)
    {}
    ~UserData(){}

    const QString& cardNum() const {return _cardNum;}
    const QString& pin() const {return _pin;}
    const QString& owner() const {return _owner;}
    const QString& date() const {return _date;}
    const QString& daemons() const {return _daemons;}
    const QString& money() const {return _money;}

    void setPin(QString in) { _pin = in;}
    void setOwner(QString in) {_owner = in;}
    void setDate(QString in) {_date = in;}
    void setDaemons(QString in) {_daemons = in;}
    void setMoney(QString in) {_money = in;}

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
        jo["date"]=date();
        jo["daemons"]=daemons();
        jo["money"]=money();
        return jo;
    }

private:
    UserData(const UserData&);
    operator=(UserData);

    QString _cardNum;
    QString _pin;
    QString _owner;
    QString _date;
    QString _daemons;
    QString _money;

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
