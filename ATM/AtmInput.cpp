#include "AtmInput.h"

AtmInput::AtmInput(const QUrl url, QWidget *parent)
   : QStackedWidget(parent), _userInfo(""),  m_url(url), _sendNum(),
     _login(new Login(this)),
     _pin(new Pin(this)),
     _menu(new Menu(this)),
     _getMoney(new GetMoney(this)),
     _balance(new Balance(this)),
     _putMoney(new PutMoney(this)),
     _other(new Other(this)),
     _sma(new SendMoneyAccount(this)),
     _sma2(new SendMoneyAmount(this)),
     _pa(new PaymentAccount(this)),
     _pa2(new PaymentAmount(this))
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &AtmInput::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &AtmInput::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &AtmInput::onTextMessageReceived);
    m_webSocket.open(QUrl(url));

    connect(_login, &Login::userChoosed, this, &AtmInput::setUser);
    connect(_login, &Login::nextPageIndex, this, &AtmInput::setCurrentIndex);

    connect(_pin, &Pin::tryBlocked, this, &AtmInput::tryUserBlocked);
    connect(this, &AtmInput::userIsBlocked, _pin, &Pin::catchBlocked);

    connect(_pin, &Pin::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_menu, &Menu::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_getMoney, &GetMoney::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_getMoney, &GetMoney::tryBanknotesValue, this, &AtmInput::tryBanknotesValue);
    connect(this, &AtmInput::banknotesValue, _getMoney, &GetMoney::catchBanknotesValue);
    connect(_balance, &Balance::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_putMoney, &PutMoney::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_other, &Other::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_sma, &SendMoneyAccount::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_sma2, &SendMoneyAmount::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_pa, &PaymentAccount::nextPageIndex, this, &AtmInput::setCurrentIndex);
    connect(_pa2, &PaymentAmount::nextPageIndex, this, &AtmInput::setCurrentIndex);

    connect(_balance, &Balance::getBalance, this, &AtmInput::tryGetBalance);
    connect(this, &AtmInput::endOperation, _balance, &Balance::catchBalance);
    connect(_login, &Login::getLogin, this, &AtmInput::tryCheckLogin);
    connect(this, &AtmInput::endOperation, _login, &Login::catchLoginOk);
    connect(_pin, &Pin::getPin, this, &AtmInput::tryCheckPin);
    connect(this, &AtmInput::endOperation, _pin, &Pin::catchRightPin);
    connect(_putMoney, &PutMoney::putMoney, this, &AtmInput::tryPutMoney);
    connect(this, &AtmInput::endOperation, _putMoney, &PutMoney::catchPutMoney);
    connect(_getMoney, &GetMoney::getMoney, this, &AtmInput::tryGetMoney);
    connect(this, &AtmInput::endOperation, _getMoney, &GetMoney::catchGetMoney);
    connect(_sma, &SendMoneyAccount::sendMoneyAcc, this, &AtmInput::trySendMoneyAcc);
    connect(this, &AtmInput::endOperation, _sma, &SendMoneyAccount::catchSendMoneyAcc);
    connect(_sma2, &SendMoneyAmount::sendMoney, this, &AtmInput::trySendMoney);
    connect(this, &AtmInput::endOperation, _sma2, &SendMoneyAmount::catchSendMoney);

    connect(_login, &Login::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_pin, &Pin::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_menu, &Menu::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_getMoney, &GetMoney::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_balance, &Balance::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_putMoney, &PutMoney::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_other,  &Other::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_sma, &SendMoneyAccount::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_sma2, &SendMoneyAmount::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_pa, &PaymentAccount::currentPageIndex, this, &AtmInput::currentIndex);
    connect(_pa2, &PaymentAmount::currentPageIndex, this, &AtmInput::currentIndex);


    addWidget(_login);
    addWidget(_pin);
    addWidget(_menu);
    addWidget(_getMoney);
    addWidget(_balance);
    addWidget(_putMoney);
    addWidget(_other);
    addWidget(_sma);
    addWidget(_sma2);
    addWidget(_pa);
    addWidget(_pa2);
    setCurrentIndex(0);
    setFixedSize(_login->size());
}

void AtmInput::trySendMoney(const int money)
{
    QString comm("tfr " +_sendNum + " UAH "+ money);
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::trySendMoneyAcc(const QString& login)
{
    QString comm("chc " + login); //не так
    _sendNum = login;
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::tryGetMoney(const int money)
{
    QString comm("wdw UAH " + QString::number(money));
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::tryPutMoney(const int money)
{
    QString comm("pmo UAH " + QString::number(money));
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::tryCheckLogin(const QString& login)
{
    QString comm("chc " + login);
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::tryCheckPin(const QString& pin)
{
    QString comm("chp " + pin);
    m_webSocket.sendTextMessage(comm);
}

void AtmInput::tryGetBalance()
{
    m_webSocket.sendTextMessage(QStringLiteral("chb"));
}

void AtmInput::tryUserBlocked()
{
    emit userIsBlocked(_userInfo.isBlocked());
}
void AtmInput::tryBanknotesValue()
{
    emit banknotesValue(getBanknotesValue());
}

AtmInput::~AtmInput(){ m_webSocket.close();}

void AtmInput::onConnected()
{
    m_webSocket.sendTextMessage(QStringLiteral("help"));
    qDebug() << "WebSocket connected";
}

void AtmInput::onTextMessageReceived(const QString& message)
{
    qDebug() << "Message received:" << message;
    FromJson reader(message);
    last_resp_res = reader.getBool("res");
    if (last_resp_res)
    {
        if (reader.hasField("values"))
        {
            QJsonObject balObj = reader.getObject("values");
            _userInfo.balance() = reader.getString(balObj, "UAH");
            qDebug() << "Balance:" << _userInfo.balance();
        }
    }
    emit endOperation(last_resp_res, _userInfo.balance());
}

void AtmInput::setUser(const QString& cardNum)
{
    _userInfo = ShotUserInfo(cardNum);
}

void AtmInput::blockUser()
{
    _userInfo.makeBlocked();
    m_webSocket.sendTextMessage(QStringLiteral("blk true"));
}

bool AtmInput::isBlocked() const
{
    return _userInfo.isBlocked();
}


