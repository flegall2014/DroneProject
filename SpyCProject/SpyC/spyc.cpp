// Qt
#include <qqml.h>
#include <QQmlContext>
#include <QQuickItem>
#include <QDebug>

// Application
#include "spyc.h"
#include "pluginloader.h"
#include "mastercontroller.h"
#include "settingcontroller.h"
#include "dronemodel.h"
#include "drone.h"
#include "waypointmodel.h"
#include "alertmodel.h"
#include "gallerymodel.h"
#include "exclusionareamodel.h"
#include <baseshape.h>
#include "translator.h"
#include "helper.h"
#include <qmlhelper.h>
SpyC *SpyC::sInstance = nullptr;

//-------------------------------------------------------------------------------------------------

SpyC::SpyC(QObject *parent) : QObject(parent)
{    
    // Register types
    registerTypes();

    // Drone controller
    m_pMasterController = new MasterController(this);

    // Helper
    m_pHelper = new Core::QMLHelper(this);

    // Set context properties
    setContextProperties();
}

//-------------------------------------------------------------------------------------------------

SpyC::~SpyC()
{
    qDebug() << "DESTROYING SPYC";
}

//-------------------------------------------------------------------------------------------------

SpyC *SpyC::instance()
{
    if (sInstance == nullptr)
        sInstance = new SpyC;
    return sInstance;
}

//-------------------------------------------------------------------------------------------------

bool SpyC::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);

    // Start controller
    if (!m_pMasterController->startup())
        return false;

    // Launch UI
    launchUI();

    return true;
}

//-------------------------------------------------------------------------------------------------

void SpyC::shutdown()
{
    m_pMasterController->shutdown();
}

//-------------------------------------------------------------------------------------------------

void SpyC::launchUI()
{
    m_engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
}

//-------------------------------------------------------------------------------------------------

void SpyC::registerTypes()
{
    // Register types
    qRegisterMetaType<WayPointList>("WayPointList");
    qmlRegisterType<SpyCore>("Components", 1, 0, "SpyC");
    qmlRegisterType<SettingController>("Components", 1, 0, "SettingController");
    qmlRegisterType<Drone>("Components", 1, 0, "Drone");
    qmlRegisterType<MasterController>("Components", 1, 0, "MasterController");
    qmlRegisterType<DroneModel>("Components", 1, 0, "DroneModel");
    qmlRegisterType<WayPointModel>("Components", 1, 0, "WayPointModel");
    qmlRegisterType<AlertModel>("Components", 1, 0, "AlertModel");
    qmlRegisterType<GalleryModel>("Components", 1, 0, "GalleryModel");
    qmlRegisterType<ExclusionAreaModel>("Components", 1, 0, "ExclusionAreaModel");
    qmlRegisterType<Core::BaseShape>("Components", 1, 0, "BaseShape");
}

//-------------------------------------------------------------------------------------------------

void SpyC::setContextProperties()
{
    m_engine.rootContext()->setContextProperty("SPYC", this);
    m_engine.rootContext()->setContextProperty("MASTERCONTROLLER", m_pMasterController);
    m_engine.rootContext()->setContextProperty("TRANSLATOR", m_pMasterController->settingController()->translator());
    m_engine.rootContext()->setContextProperty("HELPER", m_pHelper);
}
