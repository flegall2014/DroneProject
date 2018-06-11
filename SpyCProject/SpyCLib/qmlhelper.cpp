// Qt
#include <QCoreApplication>
#include <QUrl>

// Application
#include "qmlhelper.h"
using namespace Core;

//-------------------------------------------------------------------------------------------------

QMLHelper::QMLHelper(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

QMLHelper::~QMLHelper()
{

}

//-------------------------------------------------------------------------------------------------

QString QMLHelper::toLocalFile(const QString &sInput)
{
    QUrl url(sInput);
    return url.toLocalFile();
}

//-------------------------------------------------------------------------------------------------

QString QMLHelper::fromLocalFile(const QString &sInput)
{
    return QUrl::fromLocalFile(sInput).toString();
}
