#include "myparser.h"
#include "dbaccessor.h"
#include "userdata.h"


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <stdexcept>
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
    if(_lud==0) return errMess("ExecutionError: u need to chk smth first");\
    if (!_rigthPin) return errMess ("Wrong pin");


MyParser::MyParser(DBAccessor *db, QObject *parent) : QObject(parent), _db (db), _lud(0)
{

}

MyParser::~MyParser()
{
    if (_lud!=0)
        delete _lud;
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
        if (comp == "chk")
        {
            if (slist.length()>2)
            return check(slist[1], slist[2]);
            else throw std::length_error("calling check");
        }else if (comp == "inf")
            return info();
        else if (comp == "chb"){
            return checkBalance();
        } else if (comp=="help")
        {
            return
"форматы запроса атм\n\
\n\
chk (номер)(пин) - сверить номер и пин с тем что в базе(check)\n\
ada (desu) добавить демона(add daemon, daemon as string)\n\
uda (desu) (desu) изменить демону (update daemon)\n\
kda (desu) убить демона (kill daemon,  salve the prist)\n\
wdw (Type-amount) снять деньгу (withdraw)\n\
pmo (Type-amount) начилить деньги(put money)\n\
chb проверить баланс.\n\
chb (Type)\n\
crt (Type1-Amount) (Type2) развратить (convert, Т1- скажем, доллар, Т2 - грн)\n\
\n\
\n\
inf вся инфа\n\
help справка";
        }

    } catch (...) {
        jo["reason"]="Parsing error(2)";
        jd.setObject(jo);
        return jd.toJson();
    }
    jo["reason"]="Parsing error(3) : undef operation";
    jd.setObject(jo);
    return jd.toJson();
}


QString MyParser::check(QString number, QString pin){
    _rigthPin=false;
    if (_lud == 0 || number!=_lud->cardNum()){
        if (_lud!=0)
            delete _lud;
        _lud = _db->takeUD(number);
    }

    if (_lud==0)
    {
        return errMess("Can't find such card number");
    }
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

    QJsonArray ja;
    foreach(const QString val, _lud->money().split("_"))
    {
        ja.append(val);
    }

    jo["values"]=ja;

    QJsonDocument jd(jo);
    return jd.toJson();
}

QString MyParser::errMess(QString mes)
{
    QJsonObject jo;
    jo["res"]=false;
    jo["reason"]=mes;
    return QJsonDocument(jo).toJson();
}

#undef CHECK_LUD
