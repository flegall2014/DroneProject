// Qt
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

// Application
#include "helper.h"
using namespace Core;

//-------------------------------------------------------------------------------------------------


bool Helper::save(const QString &sInputString, const QString &sFilePath)
{
    QFile file(sFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << sInputString;
        file.close();
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------


bool Helper::load(const QString &sFilePath, QString &sOutputString)
{
    QFile file(sFilePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream out(&file);
        out >> sOutputString;
        file.close();
        return true;
    }
    return false;
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

QDir Helper::applicationDir()
{
    return QCoreApplication::applicationDirPath();
}
