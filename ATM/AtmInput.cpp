#include "AtmInput.h"

AtmInput::AtmInput(QWidget *parent)
   : QStackedWidget(parent), _userInfo("")
{
    QWidget* login = new Login(parent, this);
    QWidget* pin = new Pin(parent, this);
    QWidget* menu = new Menu(parent, this);
    QWidget* getMoney = new GetMoney(parent, this);
    QWidget* balance = new Balance(parent, this);
    QWidget* putMoney = new PutMoney(parent, this);
    QWidget* other = new Other(parent, this);
    QWidget* sma = new SendMoneyAccount(parent, this);
    QWidget* sma2 = new SendMoneyAmount(parent, this);
    QWidget* pa = new PaymentAccount(parent, this);
    QWidget* pa2 = new PaymentAmount(parent, this);
    addWidget(login);
    addWidget(pin);
    addWidget(menu);
    addWidget(getMoney);
    addWidget(balance);
    addWidget(putMoney);
    addWidget(other);
    addWidget(sma);
    addWidget(sma2);
    addWidget(pa);
    addWidget(pa2);
    setCurrentIndex(0);
    setFixedSize(login->size());
}

void AtmInput::setUser(const QString& cardNum)
{
    _userInfo = ShotUserInfo(cardNum);
    //TODO get from server is it blocked
}

void AtmInput::blockUser()
{
    _userInfo.makeBlocked();
}

bool AtmInput::isBlocked() const
{
    return _userInfo.isBlocked();
}




