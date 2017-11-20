#include "AtmInput.h"

AtmInput::AtmInput(QWidget *parent)
   : QStackedWidget(parent), _userInfo("")
{
    QWidget* login = new Login(parent, this);
    QWidget* pin = new Pin(parent, this);
    QWidget* menu = new Menu(parent, this);
    addWidget(login);
    addWidget(pin);
    addWidget(menu);
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




