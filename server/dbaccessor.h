#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QString>
#include <QMap>
#include <QJsonObject>
class UserData;

class DBAccessor
{
public:
    DBAccessor();
    ~DBAccessor();

    UserData* takeUD(QString& cardNum);
    void putUD(UserData*);
private:
    QJsonObject dbGet(QString cardNum);
    void dbPut(const QJsonObject &jsonObj);

    QMap <QString, QJsonObject> _cardsCash;
};

#endif // DBACCESSOR_H
