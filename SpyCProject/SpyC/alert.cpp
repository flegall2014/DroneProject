// Qt
#include <QDebug>

// Application
#include "alert.h"

//-------------------------------------------------------------------------------------------------

Alert::Alert()
{

}

//-------------------------------------------------------------------------------------------------

Alert::Alert(const SpyCore::AlertType &eType, const SpyCore::Status &eLevel, const QString &sWhat) :
    m_eType(eType), m_eLevel(eLevel), m_sWhat(sWhat), m_dateTime(QTime::currentTime())
{

}

//-------------------------------------------------------------------------------------------------

Alert::~Alert()
{

}

//-------------------------------------------------------------------------------------------------

const SpyCore::AlertType &Alert::type() const
{
    return m_eType;
}

//-------------------------------------------------------------------------------------------------

const SpyCore::Status &Alert::level() const
{
    return m_eLevel;
}

//-------------------------------------------------------------------------------------------------

const QString &Alert::what() const
{
    return m_sWhat;
}

//-------------------------------------------------------------------------------------------------

QString Alert::dateTime() const
{
    return m_dateTime.toString();
}
