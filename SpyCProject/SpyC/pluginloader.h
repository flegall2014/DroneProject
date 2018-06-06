#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

// Qt
#include <QObject>
#include <QVector>

// Application
#include "iservice.h"
class QPluginLoader;

class PluginLoader : public QObject, public IService
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    PluginLoader(QObject *pParent=nullptr);

    //! Destructor
    ~PluginLoader();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs);

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return plugins
    const QVector<QObject *> &getPlugins() const;

private:
    //! Load plugins
    bool loadPlugins();

    //! Release plugins
    void releasePlugins();

private:
    //! Plugin loaders
    QVector<QPluginLoader *> m_vPluginLoaders;

    //! Plugins
    QVector<QObject *> m_vPlugins;
};

#endif // PLUGINLOADER_H
