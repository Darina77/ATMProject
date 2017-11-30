#ifndef SHOTUSERINFO_H
#define SHOTUSERINFO_H
class ShotUserInfo
{
    private :
        QString _cardNumber;
        bool _isBlocked;
        QString _balance;
    public :
        explicit ShotUserInfo(const QString& cardNumber, bool isBlocked = false)
            :_cardNumber(cardNumber), _isBlocked(isBlocked), _balance("0")
        {}
        ~ShotUserInfo(){}
        const QString& cardNumber() const{ return _cardNumber;}
        const bool isBlocked() const {return _isBlocked;}
        void makeBlocked() {_isBlocked = false;}
        ShotUserInfo& operator = (const ShotUserInfo& inf)
        {
            _cardNumber = inf.cardNumber();
            _isBlocked = inf.isBlocked();
            return *this;
        }
        QString& balance(){return _balance;}
};
#endif // SHOTUSERINFO_H
