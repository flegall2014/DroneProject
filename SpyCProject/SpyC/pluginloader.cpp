// Qt
#include <QDir>
#include <QLibraryInfo>
#include <QPluginLoader>
#include <QDebug>

// Application
#include "pluginloader.h"

//-------------------------------------------------------------------------------------------------

PluginLoader::PluginLoader(QObject *pParent) : QObject(pParent)
{
}

//-------------------------------------------------------------------------------------------------

PluginLoader::~PluginLoader()
{

}

//-------------------------------------------------------------------------------------------------

bool PluginLoader::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);
    loadPlugins();
    return true;
}

//-------------------------------------------------------------------------------------------------

void PluginLoader::shutdown()
{
    releasePlugins();
}

//-------------------------------------------------------------------------------------------------

bool PluginLoader::loadPlugins()
{
    m_vPluginLoaders.clear();
    QDir pluginsDir("D:/projects/SpycProject/bin/plugins");
    foreach (QString sFileName, pluginsDir.entryList(QDir::Files))
    {
        // Create plugin loader
        qDebug() << "LOADING :" << pluginsDir.absoluteFilePath(sFileName);
        QPluginLoader *pPluginLoader = new QPluginLoader(pluginsDir.absoluteFilePath(sFileName));

        // Load plugin
        bool bLoad = pPluginLoader->load();
        if (!bLoad)
            qDebug() << QString("Could not load plugin %1").arg(sFileName);
        else
            // Store loader to array
            m_vPluginLoaders.append(pPluginLoader);
    }

    // Did we found any plugins?
    if (!m_vPluginLoaders.isEmpty())
    {
        for (int i=0; i<m_vPluginLoaders.size(); i++)
        {
            QPluginLoader *pPluginLoader = m_vPluginLoaders[i];
            if (pPluginLoader != nullptr)
            {
                // Create plugin instance
                QObject *pPlugin = pPluginLoader->instance();
                if (pPlugin != nullptr)
                    m_vPlugins << pPlugin;
                else
                {
                    // Could not create plugin instance, delete pluginloader
                    delete pPluginLoader;
                    m_vPluginLoaders.removeAt(i);
                    i--;
                }
            }
        }
    }

    return !m_vPluginLoaders.isEmpty();
}

//-------------------------------------------------------------------------------------------------

const QVector<QObject *> &PluginLoader::getPlugins() const
{
    return m_vPlugins;
}

//-------------------------------------------------------------------------------------------------

void PluginLoader::releasePlugins()
{
    qDeleteAll(m_vPluginLoaders);
    m_vPluginLoaders.clear();
    qDeleteAll(m_vPlugins);
    m_vPlugins.clear();
}
