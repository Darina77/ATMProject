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

    UserData* takeUD(QString& cardNum, void* borrower);
    void updateUD(UserData*);
    void freeUD(UserData*);

    bool isBeingUsed(const QString& cardNum);
private:
    QJsonObject dbGet(QString cardNum);
    void dbPut(const QJsonObject &jsonObj);

    QMap <QString, QJsonObject> _cardsCash;
    QMap <QString, void*> _mutexMap;//map cardNum-borrower
};

#endif // DBACCESSOR_H
