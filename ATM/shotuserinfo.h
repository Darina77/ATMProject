#ifndef SHOTUSERINFO_H
#define SHOTUSERINFO_H
class ShotUserInfo
{
    private :
        QString _cardNumber;
        QString _balance;
    public :
        explicit ShotUserInfo(const QString& cardNumber)
            :_cardNumber(cardNumber), _balance("0")
        {}
        ~ShotUserInfo(){}
        const QString& cardNumber() const{ return _cardNumber;}
        ShotUserInfo& operator = (const ShotUserInfo& inf)
        {
            _cardNumber = inf.cardNumber();
            return *this;
        }
        QString& balance(){return _balance;}
};
#endif // SHOTUSERINFO_H
