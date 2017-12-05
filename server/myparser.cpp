#include "myparser.h"
#include "dbaccessor.h"
#include "userdata.h"


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <stdexcept>

#include <QDebug>
/*
форматы запроса атм

chk (номер)(пин) - сверить номер и пин с тем что в базе(check)
ada (desu) добавить демона(add daemon, daemon as string)
uda (desu) (desu) изменить демону (update daemon)
kda (desu) убить демона (kill daemon,  salve the prist)
wdw (Type-amount) снять деньгу (withdraw)
pmo (Type-amount) начилить деньги(put money)
chb проверить баланс.
chb (Type)
crt (Type1-Amount) (Type2) развратить (convert, Т1- скажем, доллар, Т2 - грн)


inf вся инфа
*/
#define CHECK_LUD \
    \
    if(_lud==0) return errMess("ExecutionError: u need to {chc (some card)} first");\
    if (_lud->isBlocked()) return errMess("Card is blocked");\
    if (!_rigthPin) return errMess ("Wrong pin");



MyParser::MyParser(DBAccessor *db, QObject *parent) : QObject(parent), _db (db), _lud(0)
{

}

MyParser::~MyParser()
{
    if (_lud!=0)
        _db->freeUD(_lud);
}

QString MyParser ::parse(QString in)
{
    QJsonObject jo;
    QJsonDocument jd;
    jo["res"]=false;

    if (in.size()< 3)
    {
        jo["reason"]="Parsing error(1): too short";
        jd.setObject(jo);
        return jd.toJson();
    }
    QStringList slist= in.split(" ");

    try {
        QString comp = slist[0];
        if (comp == "che")
        {
            if (slist.length()>1)
                return checkExistence(slist[1]);
            else throw std::length_error("calling check existence");
        }
        else if (comp == "blk")
        {
            if (slist.length()>1)
                return blockCard(slist[1]);
            else throw std::length_error("calling block card");
        }else if (comp == "chc")
        {
            if (slist.length()>1)
            {
                if (!slist[1].isEmpty())
                    return checkCard(slist[1]);
            }else throw std::length_error("calling check card");
        } else if (comp == "chp")
        {
            if (slist.length()>1)
                return checkPin(slist[1]);
            else throw std::length_error("calling check pin");
        }else if (comp == "inf")
            return info();
        else if (comp == "chb"){
            return checkBalance();
        }else if (comp=="wdw"){
            if (slist.length()>2)
                return withdrow(slist[1], slist[2]);
            else throw std::length_error("calling withdrow");
        }else if (comp=="pmo"){
        if (slist.length()>2)
            return putMoney(slist[1], slist[2]);
            else throw std::length_error("calling putMoney");
        }else if (comp=="tfr"){
            if (slist.length()>3)
                return transfer(slist[1], slist[2], slist[3]);
                else throw std::length_error("calling transfer");
        }else if (comp=="help")
        {
            return
"форматы запроса атм\n\
\n\
(+)blk (true/false) заблокировать/разблокировать карточку\n\
(+)che (номер) проверить существование карточки не запоминая(check existence)\n\
(+)chc (номер) существует ли карточка № номер (check card)\n\
(+)chp (pin)  проверить подходит ли пин(check pin)\n\
(-)ada (desu) добавить демона(add daemon, daemon as string)\n\
(-)uda (desu) (desu) изменить демону (update daemon)\n\
(-)kda (desu) убить демона (kill daemon,  salve the prist)\n\
(+)wdw (Type) (amount) снять деньгу (withdraw)\n\
(+)pmo (Type) (amount) начилить деньги(put money)\n\
(+)tfr (card) (type) (amount) transfer to $card\n\
(+)chb проверить баланс.\n\
(-)chb (Type)\n\
(-)crt (Type1-Amount) (Type2) развратить (convert, Т1- скажем, доллар, Т2 - грн)\n\
\n\
\n\
(+)inf вся инфа\n\
(+)help справка";
        }

    } catch (...) {
        return errMess("Parsing error(2)");
    }
    return errMess("Parsing error(3) : undef operation");
}

QString MyParser::blockCard(QString in)
{
    QJsonObject jo;
    jo["res"]=true;

    if (_lud==0)
        return errMess("Plz, `chc` the card first");

    if (in=="false")
    {
        if (_lud->isBlocked())
        {
            _lud->setBlocked(false);
            _db->updateUD(_lud);
        }
        return QJsonDocument(jo).toJson();
    }
    if (!_lud->isBlocked())
    {
        _lud->setBlocked(true);
        _db->updateUD(_lud);

        _db->freeUD(_lud);
        _lud=0;
    }
    return QJsonDocument(jo).toJson();
}

QString MyParser::checkExistence(QString number)
{
    if (_db->isBeingUsed(number))
        return errMess("This card is currently being used. Wait, please, for a while.");

    UserData* ud = _db->takeUD(number, this);
    QString ans("");

    if (ud==0) ans= errMess("This card does not exist.");
    else if (ud->isBlocked()) ans= errMess("This card is blocked.");
    _db->freeUD(ud);
    if(ans.isEmpty())
    {
        QJsonObject jo;
        jo["res"] = true;
        return QJsonDocument(jo).toJson();
    }
    return ans;
}


QString MyParser::checkCard(QString number){
    _rigthPin=false;
    if (_lud == 0 || number!=_lud->cardNum()){
        if (_lud!=0)
            _db->freeUD(_lud);
        _lud = _db->takeUD(number, this);
    }

    if (_lud==0)
    {
        return errMess("Can't find such card number OR this card is currently using");
    } else if (_lud->isBlocked())
    {
        _db->freeUD(_lud);
        _lud=0;
        return errMess("This card is blocked");
    }

    QJsonObject jo;
    jo["res"]=true;
    return QJsonDocument(jo).toJson();
}

QString MyParser::checkPin(QString pin)
{
    if (_lud==0)
        return errMess("Check card first");

    if (pin == _lud->pin())
    {
        _rigthPin=true;
        QJsonObject jo;
        QJsonDocument jd;
        jo["res"]=true;
        jd.setObject(jo);
        return jd.toJson();
    }
    return errMess("Wrong pin");
}

QString MyParser::info()
{
    CHECK_LUD

    QJsonObject jo= (_lud->toJsonObject());
    jo["res"]=true;
    return QJsonDocument(jo).toJson();
}
QString MyParser::checkBalance()
{
    CHECK_LUD

    QJsonObject jo;
    jo["res"] = true;

    jo["values"]=_lud->toJsonObject()["money"];

    QJsonDocument jd(jo);
    return jd.toJson();
}
QString MyParser::withdrow(QString valueType, QString valueAmount)
{
    CHECK_LUD

    if (!_lud->money().contains(valueType))
            return errMess("It is no money of this type on this card");
    Integer curM(_lud->money()[valueType]);
    Integer aimedWdw(valueAmount);

    if (curM<aimedWdw)
        return errMess("Not enough money");

    curM-=aimedWdw;
    _lud->setMoney(valueType, curM);
    _db->updateUD(_lud);

    QJsonObject jo;
    jo["res"]=true;
    jo["balance"]=(_lud->toJsonObject()["money"]);
    return QJsonDocument(jo).toJson();
}

QString MyParser::putMoney(QString valueType, QString valueAmount)
{
    CHECK_LUD

    if(! _lud->money().contains(valueType))
    {
        _lud->setMoney(valueType, Integer(valueAmount));
        _db->updateUD(_lud);
        QJsonObject jo;
        jo["res"]=true;
        jo["balance"] = _lud->toJsonObject()["money"];
        return QJsonDocument(jo).toJson();
    }

    Integer was(_lud->money()[valueType]);
    //qDebug()<<"(putting money) was:"<<was;
    //qDebug()<<"adding "<<valueAmount;
    was+=Integer(valueAmount);
    //qDebug() <<"newSum:"<<was;
    _lud->setMoney(valueType, was);

    _db->updateUD(_lud);

    QJsonObject jo;
    jo["res"]=true;
    jo["balance"]=_lud->toJsonObject()["money"];

    return QJsonDocument(jo).toJson();
}

QString MyParser::transfer(QString card, QString valueType, QString valAmount)
{
    CHECK_LUD
    if (_db->isBeingUsed(card))
        return errMess("The card u want transfer to is being used now. Please, wait");
    {
        QString str = withdrow(valueType, valAmount);
        const QJsonObject& withrowed =
                QJsonDocument::fromJson(str.toLatin1()).object();
        if (! withrowed["res"].toBool())
        {
            QString ans("");
            ans.append(withrowed["reason"].toString());
            return errMess(ans);
        }
    }

    UserData* temp = _lud;
    _lud =_db->takeUD(card, this);
    QString ans = putMoney(valueType, valAmount);
    _db->freeUD(_lud);
    _lud=temp;

    QJsonObject jo;
    jo["res"]=true;
    return QJsonDocument(jo).toJson();
}

QString MyParser::errMess(QString mes)
{
    QJsonObject jo;
    jo["res"]=false;
    jo["reason"]=mes;
    return QJsonDocument(jo).toJson();
}

#undef CHECK_LUD
