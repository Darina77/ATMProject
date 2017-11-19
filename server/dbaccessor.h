#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QString>
#include <QMap>
class UserData;

class DBAccessor
{
public:
    DBAccessor();
    ~DBAccessor();

    UserData* takeUD(QString& cardNum);
    void putUD(UserData*);

    QMap <QString, QString> _cardsCash;
};

#endif // DBACCESSOR_H
