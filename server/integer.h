#ifndef INTEGER_H
#define INTEGER_H

#include <QObject>
#include <QVector>
#include <QString>

class Integer
{
public:
    explicit Integer(QString in= "0");
    Integer(const Integer& in);

    Integer& operator+=(const Integer& that);
    Integer& operator*=(const Integer& that);
    Integer& operator -=(const Integer& that);
    //Integer& operator = (const Integer& that);
    Integer& setVal(const QString& that);

    QString toString() const;
    operator QString() const;

    bool operator < (const Integer& that) const;
    bool operator > (const Integer& that) const;
    bool operator ==(const Integer& that) const;
    bool operator !=(const Integer& that) const;
    bool operator <=(const Integer& that) const;
    bool operator >=(const Integer& that) const;
private:

    static void fit(QVector<quint8> &);
    static void fit_len(QVector<quint8> &);
    mutable QVector<quint8> _v;
};

#endif // INTEGER_H
