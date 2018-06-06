#ifndef COMSTATION_H
#define COMSTATION_H

// Qt
#include <QObject>
#include <QTimer>
#include <QThread>

// Application
#include "iservice.h"
namespace Core {
class TCPClient;
}

class ComStation : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    ComStation(QObject *pParent=nullptr);

    //! Destructor
    virtual ~ComStation();

private:
    //! TCP client
    Core::TCPClient *m_pClient = nullptr;

public slots:
    //! Data ready
    void onDataReady(const QByteArray &ba);

    //! Run
    void run();

    //! Attempt new connection
    void attemptNewConnection();

    //! Send message
    void onSendMessage(const QString &sMessage);

signals:
    //! New message
    void outGoingMessage(const QString &sMessage);

    //! Incoming message
    void incomingMessage(const QString &sMessage);
};

#endif // COMSTATION_H
