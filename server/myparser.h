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

*/


#ifndef MYPARSER_H
#define MYPARSER_H

#include <QObject>
class DBAccessor;
class UserData;

class MyParser : public QObject
{
    Q_OBJECT
public:
    explicit MyParser(DBAccessor* db,QObject *parent = nullptr);
    virtual ~MyParser();
    QString parse(QString);
signals:
    //void parsed(QString);

public slots:
    //void parseIt(QString);

private:
    DBAccessor* _db;
    UserData* _lud;
    QString check(QString number, QString pin);
    QString info();
};

#endif // MYPARSER_H
