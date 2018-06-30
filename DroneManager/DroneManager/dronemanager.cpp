// Qt
#include <QTime>
#include <QDebug>

// Application
#include "dronemanager.h"
#include "droneemulator.h"
#include "waypoint.h"
#include <defs.h>
#include <cxmlnode.h>
#include "serializehelper.h"
#include <tcpserver.h>
using namespace Model;

//-------------------------------------------------------------------------------------------------

DroneManager::DroneManager(QObject *pParent) : QObject(pParent)
{
    // Build server
    m_pServer = new Core::TCPServer(this);
    connect(m_pServer, &Core::TCPServer::newConnectionFromGroundStation, this, &DroneManager::onNewConnectionFromGroundStation, Qt::DirectConnection);
    connect(m_pServer, &Core::TCPServer::dataReady, this, &DroneManager::onIncomingMessage, Qt::DirectConnection);

    // Video url
    QStringList lVideos;
    lVideos << "D:/projects/DroneProject/SpyCProject/SpyC/video/video1.mp4" <<
               "D:/projects/DroneProject/SpyCProject/SpyC/video/video2.mp4" <<
               "D:/projects/DroneProject/SpyCProject/SpyC/video/video3.mp4";

    // Initial position
    QVector<double> vLatitudes = QVector<double>() << 48.856614 << 40.7127753 << 9.641185499999999;
    QVector<double> vLongitudes = QVector<double>() << 2.3522219000000177 << -74.0059728 << -13.57840120000003;

    // Create enw drone
    for (int i=0; i<3; i++)
    {
        // Set initial position
        double dLatitude = vLatitudes[i];
        double dLongitude = vLongitudes[i];
        QGeoCoordinate initialPos(dLatitude, dLongitude);

        // Build drone emulators
        QString sDroneUID = QString("DRONE %1").arg(i);
        DroneEmulator *pDrone = new DroneEmulator(sDroneUID, lVideos[i], initialPos, this);
        connect(pDrone, &DroneEmulator::safetyPlanChanged, this, &DroneManager::onSafetyPlanChanged);
        connect(pDrone, &DroneEmulator::missionPlanChanged, this, &DroneManager::onMissionPlanChanged);
        connect(pDrone, &DroneEmulator::landingPlanChanged, this, &DroneManager::onLandingPlanChanged);
        connect(pDrone, &DroneEmulator::positionTimeOut, this, &DroneManager::onPositionTimeOut, Qt::QueuedConnection);
        connect(pDrone, &DroneEmulator::batteryTimeOut, this, &DroneManager::onBatteryTimeOut, Qt::QueuedConnection);
        connect(pDrone, &DroneEmulator::returnTimeOut, this, &DroneManager::onReturnTimeOut, Qt::QueuedConnection);
        connect(pDrone, &DroneEmulator::droneError, this, &DroneManager::onDroneError, Qt::QueuedConnection);
        m_vDrones << pDrone;
    }
}

//-------------------------------------------------------------------------------------------------

DroneManager::~DroneManager()
{

}

//-------------------------------------------------------------------------------------------------

void DroneManager::sendMessage(const QString &sMessage)
{
    if (m_pServer != nullptr)
        m_pServer->sendMessage(sMessage);
}

//-------------------------------------------------------------------------------------------------

DroneEmulator *DroneManager::getDrone(const QString &sDroneUID) const
{
    foreach (DroneEmulator *pDrone, m_vDrones)
        if (pDrone->uid() == sDroneUID)
            return pDrone;
    return nullptr;
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onPositionTimeOut()
{
    DroneEmulator *pSender = dynamic_cast<DroneEmulator *>(sender());
    if (pSender != nullptr)
        sendMessage(pSender->serializePosition());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onBatteryTimeOut()
{
    DroneEmulator *pSender = dynamic_cast<DroneEmulator *>(sender());
    if (pSender != nullptr)
        sendMessage(pSender->serializeBatteryLevel());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onReturnTimeOut()
{
    DroneEmulator *pSender = dynamic_cast<DroneEmulator *>(sender());
    if (pSender != nullptr)
        sendMessage(pSender->serializeReturnLevel());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onTakeOffRequest(const QString &sDroneUID)
{
    DroneEmulator *pTargetDrone = getDrone(sDroneUID);
    if (pTargetDrone != nullptr)
        pTargetDrone->takeOff();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onFailSafeRequest(const QString &sDroneUID)
{
    DroneEmulator *pTargetDrone = getDrone(sDroneUID);
    if (pTargetDrone != nullptr)
        pTargetDrone->failSafe();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onMissionPlanChanged()
{
    DroneEmulator *pTargetDrone = dynamic_cast<DroneEmulator *>(sender());
    if (pTargetDrone != nullptr)
        sendMessage(pTargetDrone->serializeMissionPlan());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onSafetyPlanChanged()
{
    DroneEmulator *pTargetDrone = dynamic_cast<DroneEmulator *>(sender());
    if (pTargetDrone != nullptr)
        sendMessage(pTargetDrone->serializeSafetyPlan());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onLandingPlanChanged()
{
    DroneEmulator *pTargetDrone = dynamic_cast<DroneEmulator *>(sender());
    if (pTargetDrone != nullptr)
        sendMessage(pTargetDrone->serializeLandingPlan());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onDroneError(const SpyCore::DroneError &eDroneError, const QString &sDroneUID)
{
    sendMessage(Core::SerializeHelper::serializeDroneError(eDroneError, sDroneUID));
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onNewConnectionFromGroundStation()
{
    // Send safety/mission/landing plans
    foreach (DroneEmulator *pDrone, m_vDrones)
        if (pDrone != nullptr)
            sendMessage(pDrone->serializeGlobalStatus());
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onIncomingMessage(const QString &sMessage)
{
    // Retrieve message type
    QString sMessageType = Core::SerializeHelper::messageType(sMessage);

    // Retrieve drone uid
    QString sDroneUID = Core::SerializeHelper::droneUID(sMessage);

    // Retrieve drone
    DroneEmulator *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
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
            pDrone->deserializeExclusionArea(sMessage);
        // Go home
        else
        if (sMessageType == TAG_GO_HOME)
            pDrone->goHome();
        else
        // Take off
        if (sMessageType == TAG_TAKE_OFF)
            pDrone->takeOff();
        else
        // Fail safe
        if (sMessageType == TAG_FAIL_SAFE)
            pDrone->failSafe();

        // Update canTakeOff state
        qDebug() << "HAS SAFETY : " << pDrone->hasSafetyPlan();
        qDebug() << "HAS MISSION : " << pDrone->hasMissionPlan();
        qDebug() << "HAS LANDING : " << pDrone->hasLandingPlan();
        pDrone->setCanTakeOff(pDrone->hasSafetyPlan() && pDrone->hasMissionPlan() && pDrone->hasLandingPlan());
    }
}

