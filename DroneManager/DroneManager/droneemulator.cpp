// Qt
#include <QTime>

// Application
#include "droneemulator.h"
#include <flightsimulator.h>
#include <batterysimulator.h>

//-------------------------------------------------------------------------------------------------

DroneEmulator::DroneEmulator(QObject *pParent) : DroneBase(pParent)
{

}

//-------------------------------------------------------------------------------------------------

DroneEmulator::DroneEmulator(const QString &sDroneUID, QObject *pParent) : Core::DroneBase(sDroneUID, pParent)
{
    // Listen to flight simulator stimulation
    m_pFlightSimulator = new Core::FlightSimulator(this);
    connect(m_pFlightSimulator, &Core::FlightSimulator::positionChanged, this, &DroneEmulator::onPositionChanged, Qt::QueuedConnection);

    // Listen to battery simulator simulation
    m_pBatterySimulator = new Core::BatterySimulator(this);
    connect(m_pBatterySimulator, &Core::BatterySimulator::batteryLevelChanged, this, &DroneEmulator::onBatteryLevelChanged, Qt::QueuedConnection);

    // Timer
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    m_droneTimer.setInterval(250);
    connect(&m_droneTimer, &QTimer::timeout, this, &DroneEmulator::timeOut, Qt::QueuedConnection);
    m_droneTimer.start();
}

//-------------------------------------------------------------------------------------------------

DroneEmulator::DroneEmulator(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent) : DroneBase(sDroneUID, sVideoUrl, initialPos, pParent)
{
    // Listen to flight simulator stimulation
    m_pFlightSimulator = new Core::FlightSimulator(this);
    connect(m_pFlightSimulator, &Core::FlightSimulator::positionChanged, this, &DroneEmulator::onPositionChanged, Qt::QueuedConnection);

    // Listen to battery simulator simulation
    m_pBatterySimulator = new Core::BatterySimulator(this);
    connect(m_pBatterySimulator, &Core::BatterySimulator::batteryLevelChanged, this, &DroneEmulator::onBatteryLevelChanged, Qt::QueuedConnection);

    // Timer
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    m_droneTimer.setInterval(250);
    connect(&m_droneTimer, &QTimer::timeout, this, &DroneEmulator::timeOut, Qt::QueuedConnection);
    m_droneTimer.start();
}

//-------------------------------------------------------------------------------------------------

DroneEmulator::~DroneEmulator()
{

}

//-------------------------------------------------------------------------------------------------

void DroneEmulator::onPositionChanged(const QGeoCoordinate &geoCoord, double dHeading)
{
    setPosition(geoCoord);
    setHeading(dHeading);
}

//-------------------------------------------------------------------------------------------------

void DroneEmulator::onBatteryLevelChanged(int iLevel, int iReturn)
{
    setBatteryLevel(iLevel);
    setReturnLevel(iReturn);
}

//-------------------------------------------------------------------------------------------------

void DroneEmulator::takeOff()
{
    if (missionPlan().isEmpty())
        emit droneError(SpyCore::NO_SAFETY, uid());
    else
    if (landingPlan().isEmpty())
        emit droneError(SpyCore::NO_LANDING_PLAN, uid());
    else
    if (missionPlan().isEmpty())
        emit droneError(SpyCore::NO_MISSION_PLAN, uid());
    else
    {
        m_pFlightSimulator->computeFlightPath(missionPlan());
        m_pFlightSimulator->start();
        m_pBatterySimulator->start();
        setFlightStatus(SpyCore::FlightStatus::FLYING);
    }
}

//-------------------------------------------------------------------------------------------------

void DroneEmulator::failSafe()
{
    m_pFlightSimulator->stop();
    m_pBatterySimulator->stop();
    setFlightStatus(SpyCore::FlightStatus::IDLE);
}
