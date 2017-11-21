#ifndef SHOTUSERINFO_H
#define SHOTUSERINFO_H
class ShotUserInfo
{
    private :
        QString _cardNumber;
        bool _isBlocked;

    public :
        explicit ShotUserInfo(const QString& cardNumber, bool isBlocked = false)
            :_cardNumber(cardNumber), _isBlocked(isBlocked)
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
};
#endif // SHOTUSERINFO_H
