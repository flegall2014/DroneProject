// Qt
#include <QDebug>
#include <QTextToSpeech>

// Application
#include "mastercontroller.h"
#include "pluginloader.h"
#include "dronemodel.h"
#include "settingcontroller.h"
#include "drone.h"
#include "comstation.h"
#include "waypointmodel.h"
#include "exclusionareamodel.h"
#include <defs.h>
#include <waypoint.h>
#include <serializehelper.h>
#include <helper.h>

//-------------------------------------------------------------------------------------------------

MasterController::MasterController(QObject *pParent) : QObject(pParent)
{
    // Application main title
    m_sApplicationTitle = tr("Welcome to Spy'C ground station");

    // Setup setting controller
    m_pSettingController = new SettingController(this);

    // Com station
    m_pComStation = new ComStation();
    m_pComStation->moveToThread(&m_comStationThread);

    //
    // Handle communication with com station
    //

    // Connect thread started to comStation run
    connect(&m_comStationThread, &QThread::started, m_pComStation, &ComStation::run, Qt::QueuedConnection);

    // Listen to com station incoming messages
    connect(this, &MasterController::outGoingMessage, m_pComStation, &ComStation::onSendMessage, Qt::QueuedConnection);
    connect(m_pComStation, &ComStation::incomingMessage, this, &MasterController::onIncomingMessage, Qt::QueuedConnection);

    // Main drone model
    m_pDroneModel = new DroneModel(this);

    // Handle requests
    connect(this, &MasterController::validateSafetyPlanReq, this, &MasterController::onValidateSafetyPlan, Qt::QueuedConnection);
    connect(this, &MasterController::validateMissionPlanReq, this, &MasterController::onValidateMissionPlan, Qt::QueuedConnection);
    connect(this, &MasterController::validateLandingPlanReq, this, &MasterController::onValidateLandingPlan, Qt::QueuedConnection);
    connect(this, &MasterController::validateExclusionAreaReq, this, &MasterController::onValidateExclusionArea, Qt::QueuedConnection);
    connect(this, &MasterController::takeOffRequest, this, &MasterController::onTakeOffRequest, Qt::QueuedConnection);
    connect(this, &MasterController::goHomeRequest, this, &MasterController::onGoHomeRequest, Qt::QueuedConnection);
    connect(this, &MasterController::failSafeRequest, this, &MasterController::onFailSafeRequest, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

MasterController::~MasterController()
{
}

//-------------------------------------------------------------------------------------------------

bool MasterController::startup(const QStringList &lArgs)
{
    if (!m_pSettingController->startup(lArgs))
        return false;
    return true;
}

//-------------------------------------------------------------------------------------------------

void MasterController::shutdown()
{
    m_comStationThread.terminate();
    m_pSettingController->shutdown();
}

//-------------------------------------------------------------------------------------------------

void MasterController::sendMessage(const QString &sMessage)
{
    emit outGoingMessage(sMessage);
}

//-------------------------------------------------------------------------------------------------

void MasterController::startComStation()
{
    m_comStationThread.start();
}

//-------------------------------------------------------------------------------------------------

DroneModel *MasterController::droneModel() const
{
    return m_pDroneModel;
}

//-------------------------------------------------------------------------------------------------

SettingController *MasterController::settingController() const
{
    return m_pSettingController;
}

//-------------------------------------------------------------------------------------------------

Drone *MasterController::getDrone(const QString &sDroneUID) const
{
    foreach (Drone *pDrone, m_vDrones)
        if ((pDrone != nullptr) && (pDrone->uid() == sDroneUID))
            return pDrone;
    return nullptr;
}

//-------------------------------------------------------------------------------------------------

void MasterController::onIncomingMessage(const QString &sMessage)
{
    // Retrieve message type
    QString sMessageType = Core::SerializeHelper::messageType(sMessage);

    // Retrieve drone UID
    QString sDroneUID = Core::SerializeHelper::droneUID(sMessage);

    // Drone already registered?
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone == nullptr)
    {
        pDrone = new Drone(sDroneUID, this);
        pDrone->initialize(m_pSettingController->allSettings());
        connect(pDrone, &Drone::globalStatusChanged, this, &MasterController::onDroneGlobalStatusChanged, Qt::QueuedConnection);
        m_vDrones << pDrone;
    }

    // Did we get a drone?
    if (pDrone == nullptr)
        return;

    // Process drone status
    if (sMessageType == TAG_DRONE_STATUS)
    {
        pDrone->deserializeGlobalStatus(sMessage);
        pDrone->exclusionAreaModel()->setExclusionArea(pDrone->exclusionArea());
    }
    else
    // Safety plan
    if (sMessageType == TAG_SAFETY_PLAN)
        pDrone->deserializeSafetyPlan(sMessage);
    else
    // Mission plan
    if (sMessageType == TAG_MISSION_PLAN)
        pDrone->deserializeMissionPlan(sMessage);
    else
    // Landing plan
    if (sMessageType == TAG_LANDING_PLAN)
        pDrone->deserializeLandingPlan(sMessage);
    else
    // Exclusion area
    if (sMessageType == TAG_EXCLUSION_AREA)
    {
        pDrone->deserializeExclusionArea(sMessage);
        pDrone->exclusionAreaModel()->setExclusionArea(pDrone->exclusionArea());
    }
    else
    // Position
    if (sMessageType == TAG_POSITION)
        pDrone->deserializePosition(sMessage);
    else
    if (sMessageType == TAG_BATTERY)
        pDrone->deserializeBatteryLevel(sMessage);
    else
    if (sMessageType == TAG_RETURN)
        pDrone->deserializeReturnLevel(sMessage);
    else
    // Process drone error
    if (sMessageType == TAG_DRONE_ERROR)
    {
        QString sDroneUID;
        SpyCore::DroneError eDroneError;
        Core::SerializeHelper::deSerializeDroneError(sMessage, eDroneError, sDroneUID);
        emit missionPlanError(eDroneError, sDroneUID);
    }
    else
    {
        qDebug() << "UNKNOWN MESSAGE " << sMessageType << sMessage;
    }

    // Update canTakeOff state
    pDrone->setCanTakeOff(pDrone->hasSafetyPlan() && pDrone->hasMissionPlan() && pDrone->hasLandingPlan());

    // Add drone
    m_pDroneModel->addDrone(pDrone);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onDroneGlobalStatusChanged()
{
    qDebug() << "MasterController::onDroneGlobalStatusChanged()";
    Drone *pSender = dynamic_cast<Drone *>(sender());
    if (pSender != nullptr)
    {
        if (pSender->globalStatus() != SpyCore::NOMINAL)
        {
            QString sVoiceMsg = "";
            if (pSender->globalStatus() == SpyCore::WARNING)
            {
                sVoiceMsg = QString("%1 is in warning state").arg(pSender->uid());
            }
            else
            if (pSender->globalStatus() == SpyCore::CRITICAL)
            {
                sVoiceMsg = QString("%1 is in critical state").arg(pSender->uid());
            }
            if (!sVoiceMsg.isEmpty())
                m_pSettingController->say(sVoiceMsg);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::onTakeOffRequest(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        sendMessage(Core::SerializeHelper::serializeTakeOffRequest(sDroneUID));
}


//-------------------------------------------------------------------------------------------------

void MasterController::onGoHomeRequest(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        if (pDrone->flightStatus() != SpyCore::FLYING)
            emit missionPlanError(SpyCore::GOHOME_INFLYINGMODE_ONLY, sDroneUID);
        else
        sendMessage(Core::SerializeHelper::serializeGoHomeRequest(sDroneUID));
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::onFailSafeRequest(const QString &sDroneUID)
{
    sendMessage(Core::SerializeHelper::serializeFailSafeRequest(sDroneUID));
}

//-------------------------------------------------------------------------------------------------

void MasterController::uploadSafetyPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        sendMessage(pDrone->serializeSafetyPlan());
}

//-------------------------------------------------------------------------------------------------

void MasterController::uploadMissionPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        sendMessage(pDrone->serializeMissionPlan());
}

//-------------------------------------------------------------------------------------------------

void MasterController::uploadLandingPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        sendMessage(pDrone->serializeLandingPlan());
}

//-------------------------------------------------------------------------------------------------

void MasterController::uploadExclusionArea(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        sendMessage(pDrone->serializeExclusionArea());
}

//-------------------------------------------------------------------------------------------------

bool MasterController::loadSafetyPlan(const QString &sFilePath)
{
    if (m_pCurrentDrone != nullptr)
    {
        QString sSafetyPlan = "";
        if (Core::Helper::load(Core::Helper::toLocalFile(sFilePath), sSafetyPlan))
        {
            QString sCurrentDroneUID = m_pCurrentDrone->uid();
            m_pCurrentDrone->deserializeSafetyPlan(sSafetyPlan);
            m_pCurrentDrone->setUid(sCurrentDroneUID);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::saveSafetyPlan(const QString &sFilePath, const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        Core::Helper::save(pDrone->serializeSafetyPlan(), Core::Helper::toLocalFile(sFilePath));
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::loadMissionPlan(const QString &sFilePath)
{
    if (m_pCurrentDrone != nullptr)
    {
        QString sMissionPlan = "";
        if (Core::Helper::load(Core::Helper::toLocalFile(sFilePath), sMissionPlan))
        {
            QString sCurrentDroneUID = m_pCurrentDrone->uid();
            m_pCurrentDrone->deserializeMissionPlan(sMissionPlan);
            m_pCurrentDrone->setUid(sCurrentDroneUID);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::saveMissionPlan(const QString &sFilePath, const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        Core::Helper::save(pDrone->serializeMissionPlan(), Core::Helper::toLocalFile(sFilePath));
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::loadLandingPlan(const QString &sFilePath)
{
    if (m_pCurrentDrone != nullptr)
    {
        QString sLandingPlan = "";
        if (Core::Helper::load(Core::Helper::toLocalFile(sFilePath), sLandingPlan))
        {
            QString sCurrentDroneUID = m_pCurrentDrone->uid();
            m_pCurrentDrone->deserializeLandingPlan(sLandingPlan);
            m_pCurrentDrone->setUid(sCurrentDroneUID);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::saveLandingPlan(const QString &sFilePath, const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        Core::Helper::save(pDrone->serializeLandingPlan(), Core::Helper::toLocalFile(sFilePath));
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::loadExclusionArea(const QString &sFilePath)
{
    if (m_pCurrentDrone != nullptr)
    {
        QString sExclusionArea = "";
        if (Core::Helper::load(Core::Helper::toLocalFile(sFilePath), sExclusionArea))
        {
            QString sCurrentDroneUID = m_pCurrentDrone->uid();
            m_pCurrentDrone->deserializeExclusionArea(sExclusionArea);
            m_pCurrentDrone->setUid(sCurrentDroneUID);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

bool MasterController::saveExclusionArea(const QString &sFilePath, const QString &sDroneUID)
{
    qDebug() << "SAVE XCLS" << sDroneUID;

    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        Core::Helper::save(pDrone->serializeExclusionArea(), Core::Helper::toLocalFile(sFilePath));
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

void MasterController::setCurrentDrone(Drone *pCurrentDrone)
{
    m_pCurrentDrone = pCurrentDrone;
    emit currentDroneChanged();
}

//-------------------------------------------------------------------------------------------------

Drone *MasterController::currentDrone() const
{
    return m_pCurrentDrone;
}

//-------------------------------------------------------------------------------------------------

void MasterController::setApplicationTitle(const QString &sApplicationTitle)
{
    m_sApplicationTitle = sApplicationTitle;
    emit applicationTitleChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &MasterController::applicationTitle() const
{
    return m_sApplicationTitle;
}

//-------------------------------------------------------------------------------------------------

void MasterController::takeOff(const QString &sDroneUID)
{
    emit takeOffRequest(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::goHome(const QString &sDroneUID)
{
    emit goHomeRequest(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::failSafe(const QString &sDroneUID)
{
    emit failSafeRequest(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::validateSafetyPlanRequest(const QString &sDroneUID)
{
    emit validateSafetyPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onValidateSafetyPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        // Retrieve safety area
        QGeoPath safety = pDrone->safetyModel()->path();
        if (!safety.isEmpty())
        {
            if (safety.size() > 2)
            {
                pDrone->closeSafety();
                uploadSafetyPlan(pDrone->uid());
            }
            else emit missionPlanError(SpyCore::NOT_ENOUGH_POINTS_IN_SAFETY, pDrone->uid());
        }
        else emit missionPlanError(SpyCore::EMPTY_SAFETY_PLAN, pDrone->uid());
    }
}


//-------------------------------------------------------------------------------------------------

void MasterController::validateMissionPlanRequest(const QString &sDroneUID)
{
    emit validateMissionPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onValidateMissionPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        // Retrieve safety area
        QGeoPath missionPlan = pDrone->missionPlanModel()->path();
        if (!missionPlan.isEmpty())
        {
            if (missionPlan.size() > 2)
            {
                // Add current position
                pDrone->addCoordinateToMissionPlan(pDrone->position(), 0);
                uploadMissionPlan(pDrone->uid());
            }
            else
                emit missionPlanError(SpyCore::NOT_ENOUGH_POINTS_IN_MISSION_PLAN, pDrone->uid());
        }
        else emit missionPlanError(SpyCore::EMPTY_MISSION_PLAN, pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::validateLandingPlanRequest(const QString &sDroneUID)
{
    emit validateLandingPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onValidateLandingPlan(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        // Retrieve landing plan
        QGeoPath landingPlan = pDrone->landingPlanModel()->path();
        if (!landingPlan.isEmpty())
        {
            if (landingPlan.size() == 3)
                uploadLandingPlan(pDrone->uid());
            else
                emit missionPlanError(SpyCore::UNEXPECTED_LANDING_PLAN_COUNT, pDrone->uid());
        }
        else emit missionPlanError(SpyCore::EMPTY_LANDING_PLAN, pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::validateExclusionAreaRequest(const QString &sDroneUID)
{
    emit validateExclusionAreaReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onValidateExclusionArea(const QString &sDroneUID)
{
    Drone *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        // Retrieve landing plan
        const QVector<Core::BaseShape *> &vShapes = pDrone->exclusionAreaModel()->shapes();
        if (vShapes.isEmpty())
            emit missionPlanError(SpyCore::EMPTY_EXCLUSION_AREA, pDrone->uid());
        else
            uploadExclusionArea(pDrone->uid());
    }
}
