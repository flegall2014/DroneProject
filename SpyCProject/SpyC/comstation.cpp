// Application
#include "comstation.h"
#include <tcpclient.h>
#define LOCAL_HOST "127.0.0.1"

//-------------------------------------------------------------------------------------------------

ComStation::ComStation(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

ComStation::~ComStation()
{
    m_pClient->disconnectFromHost();
    m_pClient->deleteLater();
}

//-------------------------------------------------------------------------------------------------

void ComStation::onSendMessage(const QString &sMessage)
{
    emit outGoingMessage(sMessage);
}

//-------------------------------------------------------------------------------------------------

void ComStation::onDataReady(const QByteArray &ba)
{
    emit incomingMessage(QString(ba));
}

//-------------------------------------------------------------------------------------------------

void ComStation::run()
{
    m_pClient = new Core::TCPClient();
    connect(m_pClient, &Core::TCPClient::dataReady, this, &ComStation::onDataReady, Qt::DirectConnection);
    connect(this, &ComStation::outGoingMessage, m_pClient, &Core::TCPClient::onSendMessage, Qt::DirectConnection);
    attemptNewConnection();
}

//-------------------------------------------------------------------------------------------------

void ComStation::attemptNewConnection()
{
    while (!m_pClient->isConnected())
        m_pClient->connectToHost(LOCAL_HOST);
}

