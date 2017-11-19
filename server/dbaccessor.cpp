#include "dbaccessor.h"

#include "userdata.h"

DBAccessor::DBAccessor()
{
    _cardsCash["1234"] = "1234<$>1111<$>Volodimir<$>19.11.2017<$><$>UA-0.01";
    _cardsCash["0000"] = "0000<$><$>everyone<$>19.11.2017<$><$>UA-0.01";
}
DBAccessor::~DBAccessor()
{
}

UserData* DBAccessor::takeUD(QString &cardNum)
{
    if (_cardsCash.keys().contains(cardNum))
    {
        QStringList sl= _cardsCash[cardNum].split("<$>");
        return new UserData(sl[0], sl[1],sl[2],sl[3], sl[4], sl[5]);
    }

    return 0;
}
void DBAccessor::putUD(UserData* ud)
{
    QString newUd;

    newUd.append(ud->cardNum());
    newUd.append("<$>");
    newUd.append(ud->pin());
    newUd.append("<$>");
    newUd.append(ud->owner());
    newUd.append("<$>");
    newUd.append(ud->date());
    newUd.append("<$>");
    newUd.append(ud->daemons());
    newUd.append("<$>");
    newUd.append(ud->money());

    _cardsCash[ud->cardNum()] = newUd;
    return;
}
