#include "integer.h"

#include <QDebug>

Integer::Integer(QString in)
    : _v(in.size(), 0)
{
    int len = in.size();

    for (int i=0; i<len; ++i)
    {
        _v[len-i-1]= quint8( in[i].toLatin1() - '0' );
    }

    fit(_v);
    fit_len(_v);
}

Integer::Integer(const Integer &in)
    :_v(in._v)
{}

/*Integer Integer::fromString(const QString &in)
{
    Integer out(in);
    out.fit();
    out.fit_len();
    return out;
}
*/
Integer& Integer::operator+=(const Integer& that)
{
    int size=(_v.size()>that._v.size())?that._v.size():_v.size();

    for (int i=0; i<size; ++i)
        _v[i]+=that._v[i];

    if (size<that._v.size())
    {
        _v.resize(that._v.size());
        for (int i=size; i<that._v.size(); ++i)
            _v[i]=that._v[i];
    }

    Integer::fit(_v);
    return *this;
}
Integer& Integer::operator*=(const Integer& that)
{
    QVector<quint8>vc(_v);
    _v.resize(_v.size()+that._v.size());
    _v.fill(0);

    for (int j=0; j<that._v.size(); ++j)
    {

        for (int i=0; i<vc.size(); ++i)
            _v[i+j]+=vc[i]*that._v[j];
        fit(_v);
    }

    fit_len(_v);
    return *this;
}
Integer& Integer::operator -=(const Integer& that)
{
    if (*this<that)
    {
        this->setVal("0");
        return *this;
    }


    //
    int i=_v.size()-1;
    _v[i--]-=1;
    if (that._v.size()==this->_v.size())
    {
        that._v[that._v.size()-1]-=1;
        that._v[that._v.size()-2]+=10;
    }
    while (i)
    {
        _v[i--]+=9;
    }
    _v[0]+=10;

    //i==0;
    while(i<that._v.size())
    {
        _v[i]-=that._v[i];
        ++i;
    }
    fit(_v);
    fit_len(_v);
    fit(that._v);
    return *this;
}

/*Integer &Integer::operator =(const Integer &that)
{
    setVal(that.toString());

    return *this;
}*/
Integer& Integer::setVal(const QString& that)
{
    Integer in(that);
    _v.resize(in._v.size());
    for (int i=0; i<_v.size(); ++i)
    {
        _v[i]=in._v[i];
    }
    return *this;
}
void Integer::fit(QVector<quint8>& _v)
{
    for(int i = 0; i<_v.size()-1; ++i)
    {
        _v[i+1]+=_v[i]/10;
        _v[i]=_v[i]%10;
    }
    if (_v.last()>9)
    {
        int size =_v.size();
        _v.resize(size+1);
        _v[size]= _v[size-1]/10;
        _v[size-1]=_v[size-1]%10;
    }
}
void Integer::fit_len(QVector<quint8> &_v)
{
    int i=_v.size()-1;
    //bool needed = false;
    while (i)
        if (_v[i]) break;
        else --i;

    _v.resize(i+1);
}
QString Integer::toString() const
{
    QString str;
    for (int i=0; i<_v.size(); ++i)
        str.prepend(QChar('0'+_v[i]));

    return str;
}
Integer::operator QString() const
{
    return toString();
}
bool Integer::operator <(const Integer& in) const
{
    if (_v.length()< in._v.length())
        return true;
    else if (_v.length()>in._v.length())
        return false;
    int i=0;
    while((i<_v.length()))
        if (_v[i]==in._v[i]) ++i;
        else break;
    if (i!=_v.length())
        if (_v[i]<in._v[i])
            return true;
    return false;
}
bool Integer::operator >(const Integer& in) const
{
    if (_v.length()> in._v.length())
        return true;
    else if (_v.length()< in._v.length())
        return false;

    int i=0;
    while((i<_v.length()))
        if (_v[i]==in._v[i]) ++i;
        else break;
    if (i!=_v.length())
        if (_v[i]>in._v[i])
            return true;
    return false;
}
bool Integer::operator ==(const Integer& in) const
{
    if (_v.length()!=in._v.length())
        return false;
    int i = 0;//_v.length();

    while((i<_v.length()))
        if (_v[i]==in._v[i]) ++i;
        else break;

    if (i==_v.length())
        return true;
    return false;
}
bool Integer::operator !=(const Integer& that) const
{
    return !(*this==that);
}
bool Integer::operator <=(const Integer& that) const
{
    return !(*this>that);
}
bool Integer::operator >=(const Integer& that) const
{
    return !(*this<that);
}
