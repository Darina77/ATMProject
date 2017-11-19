#include "myparser.h"
#include "dbaccessor.h"
#include "userdata.h"

#include <stdexcept>
/*
форматы запроса атм

chk (номер)(пин) - сверить номер и пин с тем что в базе(check)
ada (desu) добавить демона(add daemon, daemon as string)
uda (desu) (desu) изменить демону (update daemon)
kda (desu) убить демона (kill daemon,  salve the prist)
wdw (amount) снять деньгу (withdraw)
chb проверить баланс.
chb (Type)
crt (Type1) (Type2) (Amount) развратить (convert, Т1- скажем, доллар, Т2 - грн)


inf вся инфа
*/

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
    if (in.size()< 3)
        return ("Parsing error(1): too short");

    QStringList slist= in.split(" ");

    try {
        QString comp = slist[0];
        if (comp == "chk")
        {
            if (slist.length()>2)
            return check(slist[1], slist[2]);
            else throw std::length_error("calling check");
        }
        if (comp == "inf")
            return info();

    } catch (...) {
        return "Parsing error(2): array out of bound";
    }

    return "Parsing error(3) : undef operation";
}


QString MyParser::check(QString number, QString pin){
    const char* True = "True";
    const char* False = "False";

    if (_lud == 0 || number!=_lud->cardNum()){
        if (_lud!=0)
            delete _lud;
        _lud = _db->takeUD(number);
    }

    if (_lud==0)
        //return False;
        return "ExecutionError: Can't find such card number";

    if (pin == _lud->pin())
    {
        return True;
    }

    return False;
}

QString MyParser::info()
{
    if (_lud==0)
        return "ExecutionError: u need to chk smth first";

    QString res;

    res.append("{cardNum:");
    res.append(_lud->cardNum());
    res.append(", pin:");
    res.append(_lud->pin());
    res.append(", owner:");
    res.append(_lud->owner());
    res.append(", regDate:");
    res.append(_lud->date());
    res.append(", daemons:");
    res.append(_lud->daemons());
    res.append(", money:");
    res.append(_lud->money());
    res.append("}");

    return res;
}
