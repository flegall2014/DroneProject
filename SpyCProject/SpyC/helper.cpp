// Qt
#include <QCoreApplication>
#include <QUrl>

// Application
#include "helper.h"

//-------------------------------------------------------------------------------------------------

Helper::Helper(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

Helper::~Helper()
{

}

//-------------------------------------------------------------------------------------------------

QDir Helper::applicationDir()
{
    return QCoreApplication::applicationDirPath();
}

//-------------------------------------------------------------------------------------------------

QDir Helper::i18nDir()
{
    QDir appDir = applicationDir();
    if (appDir.cdUp())
    {
        if (appDir.cd("SpyC"))
        {
            if (appDir.cd("i18n"))
                return appDir;
        }
    }
    return appDir;
}

//-------------------------------------------------------------------------------------------------

QString Helper::toLocalFile(const QString &sInput)
{
    QUrl url(sInput);
    return url.toLocalFile();
}

//-------------------------------------------------------------------------------------------------

QString Helper::fromLocalFile(const QString &sInput)
{
    return QUrl::fromLocalFile(sInput).toString();
}
