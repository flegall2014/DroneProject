#ifndef ALERT_H
#define ALERT_H

// Qt
#include <QVector>
#include <QObject>
#include <QTime>

// Application
#include "dronebase.h"

class Alert
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors & destructors
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Alert();

    //! Constructor
    Alert(const SpyCore::AlertType &eAlertType, const SpyCore::Status &eAlertLevel, const QString &sWhat);

    //! Destructor
    ~Alert();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return type
    const SpyCore::AlertType &type() const;

    //! Return level
    const SpyCore::Status &level() const;

    //! Return message
    const QString &what() const;

    //! Return date time
    QString dateTime() const;

private:
    //! Type
    SpyCore::AlertType m_eType = SpyCore::NO_ALERT;

    //! Level
    SpyCore::Status m_eLevel = SpyCore::NOMINAL;

    //! Message
    QString m_sWhat = "";

    //! Date
    QTime m_dateTime = QTime::currentTime();
};

#endif // ALERT_H
