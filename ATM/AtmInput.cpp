#include "AtmInput.h"

AtmInput::AtmInput(const QUrl url, QWidget *parent)
   : QStackedWidget(parent), _userInfo(""),  m_url(url)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &AtmInput::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &AtmInput::closed);
    m_webSocket.open(QUrl(url));

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

AtmInput::~AtmInput(){ m_webSocket.close(); }

void AtmInput::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &AtmInput::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("chk 1234123412341234 1111"));
}

const bool AtmInput::isRightLogin(QString& str)
{
    return true;
}

const bool AtmInput::isRightPin(QString& pin)
{
    return true;
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
}

void AtmInput::setUser(const QString& cardNum, const QString& balance)
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

const QString AtmInput::getBalance()
{
    m_webSocket.sendTextMessage(QStringLiteral("chb"));
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &AtmInput::onTextMessageReceived);
    m_webSocket.readChannelFinished();
    qDebug() << "Balance:" << _userInfo.balance();
    return _userInfo.balance();
}

