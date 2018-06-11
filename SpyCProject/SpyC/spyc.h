#ifndef SPYC_H
#define SPYC_H

// Qt
#include <QObject>
#include <QQmlApplicationEngine>
class QQuickItem;

// Application
#include "iservice.h"
#include <spycore.h>
class MasterController;
namespace Core {
class QMLHelper;
}

class SpyC : public QObject, public IService
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SpyC(QObject *parent=nullptr);

    //! Destructor
    virtual ~SpyC();

    //! Return instance
    static SpyC *instance();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Start server
    virtual bool startup(const QStringList &lArgs=QStringList());

    //! Stop server
    virtual void shutdown();

private:
    //! Register types
    void registerTypes();

    //! Set context properties
    void setContextProperties();

private:
    //! Launch UI
    void launchUI();

private:
    //! Drone controller
    MasterController *m_pMasterController = nullptr;

    //! Helper
    Core::QMLHelper *m_pHelper = nullptr;

    //! Main view
    QQmlApplicationEngine m_engine;

    //! SpyC instance
    static SpyC *sInstance;
};

#endif // SPYC_H
