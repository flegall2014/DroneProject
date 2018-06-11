// Qt
#include <QGuiApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

// Application
#include "translator.h"
#include "helper.h"
#include "settingcontroller.h"

//-------------------------------------------------------------------------------------------------

Translator::Translator(QObject *pParent) : QObject(pParent)
{
    m_pTranslator = new QTranslator(this);
}

//-------------------------------------------------------------------------------------------------

Translator::~Translator()
{

}

//-------------------------------------------------------------------------------------------------

QString Translator::getEmptyString()
{
    return QString();
}

//-------------------------------------------------------------------------------------------------

void Translator::setLanguage(int iLanguage)
{
    // working folder
    if ((SpyCore::Language)iLanguage == SpyCore::FRENCH)
    {
        // Setup translator
        if (!m_pTranslator->load(Core::Helper::i18nDir().absoluteFilePath("french.qm")))
            qDebug() << "Failed to load: " << iLanguage;
        else
            qDebug() << iLanguage << " successfully loaded";
        qApp->installTranslator(m_pTranslator);
    }
    else
    {
        qDebug() << "Removing translator";
        qApp->removeTranslator(m_pTranslator);
    }

    emit languageChanged();
}
