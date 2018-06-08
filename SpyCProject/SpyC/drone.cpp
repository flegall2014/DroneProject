// Qt
#include <QDebug>

// Application
#include "drone.h"
#include "waypointmodel.h"
#include "alertmodel.h"
#include "gallerymodel.h"
#include "exclusionareamodel.h"
#include "settingcontroller.h"

//-------------------------------------------------------------------------------------------------

Drone::Drone(QObject *pParent) : DroneBase(pParent)
{

}

//-------------------------------------------------------------------------------------------------

Drone::Drone(const QString &sDroneUID, QObject *pParent) : Core::DroneBase(sDroneUID, pParent),
    m_eWorkMode(m_eDefaultWorkMode)
{

}

//-------------------------------------------------------------------------------------------------

Drone::Drone(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent) : Core::DroneBase(sDroneUID, sVideoUrl, initialPos, pParent),
    m_eWorkMode(m_eDefaultWorkMode)
{

}

//-------------------------------------------------------------------------------------------------

Drone::~Drone()
{

}

//-------------------------------------------------------------------------------------------------

void Drone::initialize(const QMap<int, QVariant> &mSettings)
{
    // Set settings
    m_mSettings = mSettings;

    // Mission plan model
    m_pMissionPlanModel = new WayPointModel(this);
    m_pSafetyModel = new WayPointModel(this);
    m_pLandingPlanModel = new WayPointModel(this);
    m_pAlertModel = new AlertModel(this);
    m_pGalleryModel = new GalleryModel(m_mSettings[SpyCore::GALLERY_PATH].toString(), this);
    m_pExclusionAreaModel = new ExclusionAreaModel(this);
    connect(this, &Drone::batteryStatusChanged, this, &Drone::onGlobalStatusChanged, Qt::QueuedConnection);;
}

//-------------------------------------------------------------------------------------------------

int Drone::batteryStatus() const
{
    return m_eBatteryStatus;
}

//-------------------------------------------------------------------------------------------------

void Drone::setBatteryStatus(int iBatteryStatus)
{
    m_eBatteryStatus = (SpyCore::Status)iBatteryStatus;
    if ((m_eBatteryStatus == SpyCore::WARNING) || (m_eBatteryStatus == SpyCore::CRITICAL))
        m_pAlertModel->addAlert(Alert(SpyCore::BATTERY, m_eBatteryStatus, m_eBatteryStatus == SpyCore::WARNING ? tr("Low battery level") : tr("Critical battery level")));
    emit batteryStatusChanged();
}

//-------------------------------------------------------------------------------------------------

void Drone::setGlobalStatus(const SpyCore::Status &eStatus)
{
    m_eGlobalStatus = eStatus;
    emit globalStatusChanged();
}

//-------------------------------------------------------------------------------------------------

int Drone::globalStatus() const
{
    return m_eGlobalStatus;
}

//-------------------------------------------------------------------------------------------------

QString Drone::flightStatusText() const
{
    if (flightStatus() == SpyCore::FLYING)
        return tr("Flying");
    return tr("IDLE");
}

//-------------------------------------------------------------------------------------------------

int Drone::workMode() const
{
    return (int)m_eWorkMode;
}

//-------------------------------------------------------------------------------------------------

void Drone::setWorkMode(int iMode)
{
    m_eWorkMode = (SpyCore::WorkMode)iMode;
    emit workModeChanged();
}

//-------------------------------------------------------------------------------------------------

int Drone::defaultWorkMode() const
{
    return (int)m_eDefaultWorkMode;
}

//-------------------------------------------------------------------------------------------------

int Drone::currentExclusionShape() const
{
    return (int)m_eExclusionShape;
}

//-------------------------------------------------------------------------------------------------

void Drone::setCurrentExclusionShape(int iExclusionShape)
{
    m_eExclusionShape = (SpyCore::ExclusionShape)iExclusionShape;
    emit currentExclusionShapeChanged();
}

//-------------------------------------------------------------------------------------------------

void Drone::setDefaultWorkMode()
{
    m_eWorkMode = m_eDefaultWorkMode;
    emit workModeChanged();
}

//-------------------------------------------------------------------------------------------------

WayPointModel *Drone::missionPlanModel() const
{
    return m_pMissionPlanModel;
}

//-------------------------------------------------------------------------------------------------

void Drone::setMissionPlan(const WayPointList &missionPlan)
{
    DroneBase::setMissionPlan(missionPlan);
    m_pMissionPlanModel->setPlan(missionPlan);
}

//-------------------------------------------------------------------------------------------------

WayPointModel *Drone::safetyModel() const
{
    return m_pSafetyModel;
}

//-------------------------------------------------------------------------------------------------

void Drone::setSafetyPlan(const QGeoPath &geoPath)
{
    DroneBase::setSafetyPlan(geoPath);
    m_pSafetyModel->setPlan(geoPath);
}

//-------------------------------------------------------------------------------------------------

WayPointModel *Drone::landingPlanModel() const
{
    return m_pLandingPlanModel;
}

//-------------------------------------------------------------------------------------------------

void Drone::setLandingPlan(const WayPointList &landingPlan)
{
    DroneBase::setLandingPlan(landingPlan);
    m_pLandingPlanModel->setPlan(landingPlan);
}

//-------------------------------------------------------------------------------------------------

AlertModel *Drone::alertModel() const
{
    return m_pAlertModel;
}

//-------------------------------------------------------------------------------------------------

GalleryModel *Drone::galleryModel() const
{
    return m_pGalleryModel;
}

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel *Drone::exclusionAreaModel() const
{
    return m_pExclusionAreaModel;
}

//-------------------------------------------------------------------------------------------------

void Drone::clearMissionPlan()
{
    DroneBase::clearMissionPlan();
    if (m_pMissionPlanModel != nullptr)
        m_pMissionPlanModel->clear();
}

//-------------------------------------------------------------------------------------------------

void Drone::clearSafetyPlan()
{
    DroneBase::clearSafetyPlan();
    if (m_pSafetyModel != nullptr)
        m_pSafetyModel->clear();
}

//-------------------------------------------------------------------------------------------------

void Drone::clearLandingPlan()
{
    DroneBase::clearLandingPlan();
    if (m_pLandingPlanModel != nullptr)
        m_pLandingPlanModel->clear();
}

//-------------------------------------------------------------------------------------------------

void Drone::addCoordinateToMissionPlan(const QGeoCoordinate &geoCoordinate)
{
    if (m_pMissionPlanModel != nullptr)
    {
        m_pMissionPlanModel->addCoordinate(geoCoordinate);
        DroneBase::setMissionPlan(m_pMissionPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::addCoordinateToSafety(const QGeoCoordinate &geoCoordinate)
{
    if (m_pSafetyModel != nullptr)
    {
        m_pSafetyModel->addCoordinate(geoCoordinate);
        setSafetyPlan(m_pSafetyModel->geoPath());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::addCoordinateToLandingPlan(const QGeoCoordinate &geoCoordinate)
{
    if (m_pLandingPlanModel != nullptr)
    {
        m_pLandingPlanModel->addCoordinate(geoCoordinate);
        DroneBase::setLandingPlan(m_pLandingPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::setMissionPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord)
{
    if (m_pMissionPlanModel != nullptr)
    {
        m_pMissionPlanModel->setPointPosition(iPointIndex, geoCoord);
        DroneBase::setMissionPlan(m_pMissionPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::setSafetyPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord)
{
    if (m_pSafetyModel != nullptr)
    {
        m_pSafetyModel->setPointPosition(iPointIndex, geoCoord);
        DroneBase::setSafetyPlan(m_pSafetyModel->geoPath());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::setLandingPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord)
{
    if (m_pLandingPlanModel != nullptr)
    {
        m_pLandingPlanModel->setPointPosition(iPointIndex, geoCoord);
        DroneBase::setLandingPlan(m_pLandingPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::removeCoordinateFromSafetyPlanAtIndex(int iPointIndex)
{
    if (m_pSafetyModel != nullptr)
    {
        m_pSafetyModel->removeCoordinateAtIndex(iPointIndex);
        DroneBase::setSafetyPlan(m_pSafetyModel->geoPath());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::removeCoordinateFromMissionPlanAtIndex(int iPointIndex)
{
    if (m_pMissionPlanModel != nullptr)
    {
        m_pMissionPlanModel->removeCoordinateAtIndex(iPointIndex);
        DroneBase::setMissionPlan(m_pMissionPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::removeCoordinateFromLandingPlanAtIndex(int iPointIndex)
{
    if (m_pLandingPlanModel != nullptr)
    {
        m_pLandingPlanModel->removeCoordinateAtIndex(iPointIndex);
        DroneBase::setLandingPlan(m_pLandingPlanModel->plan());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::clearExclusionAreas()
{
    if (m_pExclusionAreaModel != nullptr)
        m_pExclusionAreaModel->clear();
}

//-------------------------------------------------------------------------------------------------

void Drone::closeSafety()
{
    if (m_pSafetyModel != nullptr)
    {
        m_pSafetyModel->closePath();
        DroneBase::setSafetyPlan(m_pSafetyModel->geoPath());
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::onGlobalStatusChanged()
{
    SpyCore::Status eNewGlobalStatus = (SpyCore::Status)batteryStatus();
    if (eNewGlobalStatus != m_eGlobalStatus)
        setGlobalStatus(eNewGlobalStatus);
}

//-------------------------------------------------------------------------------------------------

void Drone::updateBatteryStatus()
{
    SpyCore::Status eBatteryStatus = SpyCore::NOMINAL;
    if ((batteryLevel() > 33) && (batteryLevel() <= 66))
        eBatteryStatus = SpyCore::WARNING;
    else
    if (batteryLevel() <= 33)
        eBatteryStatus = SpyCore::CRITICAL;
    if (eBatteryStatus != m_eBatteryStatus)
        setBatteryStatus(eBatteryStatus);
}

