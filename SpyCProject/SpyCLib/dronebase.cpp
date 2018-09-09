// Qt
#include <QDebug>
#include <QTime>
#include <QFile>

// Application
#include <cxmlnode.h>
#include "dronebase.h"
#include <defs.h>
using namespace Core;

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(const QString &sDroneUID, QObject *pParent) : QObject(pParent), m_sDroneUID(sDroneUID)
{

}

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initalPosition, QObject *pParent) : QObject(pParent),
    m_sDroneUID(sDroneUID), m_sVideoUrl(sVideoUrl), m_position(initalPosition)
{
    // Register type
    qRegisterMetaType<SpyCore::DroneError>("SpyCore::DroneError");
}

//-------------------------------------------------------------------------------------------------

DroneBase::~DroneBase()
{

}

//-------------------------------------------------------------------------------------------------

const QString &DroneBase::uid() const
{
    return m_sDroneUID;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setUid(const QString &sUID)
{
    m_sDroneUID = sUID;
    emit uidChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::flightStatus() const
{
    return (int)m_eFlightStatus;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setFlightStatus(int iFlightStatus)
{
    if ((SpyCore::FlightStatus)iFlightStatus != m_eFlightStatus)
    {
        m_eFlightStatus = (SpyCore::FlightStatus)iFlightStatus;
        emit flightStatusChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::globalStatus()
{
    return serializeGlobalStatus();
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &DroneBase::position() const
{
    return m_position;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setPosition(const QGeoCoordinate &position)
{
    if (position != m_position)
    {
        m_position = position;
        emit positionChanged();
    }
}

//-------------------------------------------------------------------------------------------------

double DroneBase::heading() const
{
    return m_dHeading;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setHeading(double dHeading)
{
    if (dHeading != m_dHeading)
    {
        m_dHeading = dHeading;
        emit headingChanged();
    }
}

//-------------------------------------------------------------------------------------------------

int DroneBase::batteryLevel() const
{
    return m_iBatteryLevel;
}

void DroneBase::setBatteryLevel(int iBatteryLevel)
{
    if (iBatteryLevel != m_iBatteryLevel)
    {
        m_iBatteryLevel = iBatteryLevel;
        emit batteryLevelChanged();
    }
}

//-------------------------------------------------------------------------------------------------

int DroneBase::returnLevel() const
{
    return m_iReturnLevel;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setReturnLevel(int iReturnLevel)
{
    if (iReturnLevel != m_iReturnLevel)
    {
        m_iReturnLevel = iReturnLevel;
        emit returnLevelChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QGeoPath &DroneBase::safetyPlan() const
{
    return m_safetyPlan;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setSafetyPlan(const QGeoPath &geoPath)
{
    if (geoPath != m_safetyPlan)
    {
        m_safetyPlan = geoPath;
        emit safetyPlanChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const WayPointList &DroneBase::missionPlan() const
{
    return m_missionPlan;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setMissionPlan(const WayPointList &missionPlan)
{
    if (missionPlan != m_missionPlan)
    {
        m_missionPlan = missionPlan;
        emit missionPlanChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const WayPointList &DroneBase::landingPlan() const
{
    return m_landingPlan;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setLandingPlan(const WayPointList &landingPlan)
{
    if (landingPlan != m_landingPlan)
    {
        m_landingPlan = landingPlan;
        emit landingPlanChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &DroneBase::videoUrl() const
{
    return m_sVideoUrl;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setVideoUrl(const QString &sVideoUrl)
{
    if (sVideoUrl != m_sVideoUrl)
    {
        m_sVideoUrl = sVideoUrl;
        emit videoUrlChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QVector<BaseShape *> &DroneBase::exclusionArea() const
{
    return m_vExclusionArea;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setExclusionArea(const QVector<BaseShape *> &vExclusionArea)
{
    if (vExclusionArea != m_vExclusionArea)
    {
        clearExclusionArea();
        m_vExclusionArea = vExclusionArea;
        emit exclusionAreaChanged();
    }
}

//-------------------------------------------------------------------------------------------------

bool DroneBase::canTakeOff() const
{
    return m_bCanTakeOff;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setCanTakeOff(bool bCanTakeOff)
{
    m_bCanTakeOff = bCanTakeOff;
    emit canTakeOffChanged();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearSafetyPlan()
{
    while (!m_safetyPlan.isEmpty())
        m_safetyPlan.removeCoordinate(0);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearMissionPlan()
{
    m_missionPlan.clear();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearLandingPlan()
{
    m_landingPlan.clear();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearExclusionArea()
{
    if (!m_vExclusionArea.isEmpty())
    {
        qDeleteAll(m_vExclusionArea);
        m_vExclusionArea.clear();
    }
    emit exclusionAreaChanged();
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializeGlobalStatus()
{
    // Create status node
    CXMLNode statusNode(TAG_DRONE_STATUS);
    statusNode.attributes()[ATTR_NODE_TYPE] = TAG_DRONE_STATUS;
    statusNode.attributes()[ATTR_DRONE_UID] = m_sDroneUID;
    statusNode.attributes()[ATTR_FLIGHT_STATUS] = QString::number((int)m_eFlightStatus);
    statusNode.attributes()[ATTR_VIDEO_URL] = m_sVideoUrl;

    // Add position
    CXMLNode positionNode = CXMLNode::parseJSON(serializePosition());
    positionNode.setTag(TAG_POSITION);
    statusNode.nodes() << positionNode;

    // Add battery level
    CXMLNode batteryNode = CXMLNode::parseJSON(serializeBatteryLevel());
    batteryNode.setTag(TAG_BATTERY);
    statusNode.nodes() << batteryNode;

    // Add return level
    CXMLNode returnNode = CXMLNode::parseJSON(serializeReturnLevel());
    returnNode.setTag(TAG_RETURN);
    statusNode.nodes() << returnNode;

    // Add safety plan
    CXMLNode safetyPlanNode = CXMLNode::parseJSON(serializeSafetyPlan());
    safetyPlanNode.setTag(TAG_SAFETY_PLAN);
    statusNode.nodes() << safetyPlanNode;

    // Add mission plan
    CXMLNode missionPlanNode = CXMLNode::parseJSON(serializeMissionPlan());
    missionPlanNode.setTag(TAG_MISSION_PLAN);
    statusNode.nodes() << missionPlanNode;

    // Add landing plan
    CXMLNode landingPlanNode = CXMLNode::parseJSON(serializeLandingPlan());
    landingPlanNode.setTag(TAG_LANDING_PLAN);
    statusNode.nodes() << landingPlanNode;

    // Add exclusion area
    CXMLNode exclusionAreaNode = CXMLNode::parseJSON(serializeExclusionArea());
    exclusionAreaNode.setTag(TAG_EXCLUSION_AREA);
    statusNode.nodes() << exclusionAreaNode;

    return statusNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializeGlobalStatus(const QString &sGlobalStatus)
{
    CXMLNode statusNode = CXMLNode::parseJSON(sGlobalStatus);
    QString sNodeType = statusNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_DRONE_STATUS)
    {
        m_sDroneUID = statusNode.attributes()[ATTR_DRONE_UID];
        setFlightStatus((SpyCore::FlightStatus)statusNode.attributes()[ATTR_FLIGHT_STATUS].toInt());
        setVideoUrl(statusNode.attributes()[ATTR_VIDEO_URL]);

        // Deserialize position
        QVector<CXMLNode> vNodes = statusNode.getNodesByTagName(TAG_POSITION);
        if (vNodes.size() > 0)
            deserializePosition(vNodes.first().toJsonString());

        // Deserialize battery level
        vNodes = statusNode.getNodesByTagName(TAG_BATTERY);
        if (vNodes.size() > 0)
            deserializeBatteryLevel(vNodes.first().toJsonString());

        // Deserialize return level
        vNodes = statusNode.getNodesByTagName(TAG_RETURN);
        if (vNodes.size() > 0)
            deserializeReturnLevel(vNodes.first().toJsonString());

        vNodes = statusNode.getNodesByTagName(TAG_SAFETY_PLAN);
        if (vNodes.size() > 0)
            deserializeSafetyPlan(vNodes.first().toJsonString());

        vNodes = statusNode.getNodesByTagName(TAG_MISSION_PLAN);
        if (vNodes.size() > 0)
            deserializeMissionPlan(vNodes.first().toJsonString());

        vNodes = statusNode.getNodesByTagName(TAG_LANDING_PLAN);
        if (vNodes.size() > 0)
            deserializeLandingPlan(vNodes.first().toJsonString());

        vNodes = statusNode.getNodesByTagName(TAG_EXCLUSION_AREA);
        if (vNodes.size() > 0)
            deserializeExclusionArea(vNodes.first().toJsonString());
    }
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializePosition()
{
    CXMLNode positionNode(TAG_POSITION);
    positionNode.attributes()[ATTR_NODE_TYPE] = TAG_POSITION;
    positionNode.attributes()[ATTR_DRONE_UID] = m_sDroneUID;
    positionNode.attributes()[ATTR_LATITUDE] = QString::number(m_position.latitude());
    positionNode.attributes()[ATTR_LONGITUDE] = QString::number(m_position.longitude());
    positionNode.attributes()[ATTR_ALTITUDE] = QString::number(m_position.altitude());
    positionNode.attributes()[ATTR_HEADING] = QString::number(m_dHeading);
    positionNode.attributes()[ATTR_FLIGHT_STATUS] = QString::number(m_eFlightStatus);
    positionNode.attributes()[ATTR_CAN_TAKEOFF] = QString::number(m_bCanTakeOff);
    return positionNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializePosition(const QString &sPosition)
{
    CXMLNode positionNode = CXMLNode::parseJSON(sPosition);
    QString sNodeType = positionNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_POSITION)
    {
        m_sDroneUID = positionNode.attributes()[ATTR_DRONE_UID];
        double dLatitude = positionNode.attributes()[ATTR_LATITUDE].toDouble();
        double dLongitude = positionNode.attributes()[ATTR_LONGITUDE].toDouble();
        double dAltitude = positionNode.attributes()[ATTR_ALTITUDE].toDouble();
        QGeoCoordinate geoCoord;
        geoCoord.setLatitude(dLatitude);
        geoCoord.setLongitude(dLongitude);
        geoCoord.setAltitude(dAltitude);
        setPosition(geoCoord);
        setHeading(positionNode.attributes()[ATTR_HEADING].toDouble());
        setFlightStatus(positionNode.attributes()[ATTR_FLIGHT_STATUS].toInt());
        setCanTakeOff((bool)positionNode.attributes()[ATTR_CAN_TAKEOFF].toInt());
    }
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializeBatteryLevel()
{
    CXMLNode batteryNode(TAG_BATTERY);
    batteryNode.attributes()[ATTR_NODE_TYPE] = TAG_BATTERY;
    batteryNode.attributes()[ATTR_DRONE_UID] = m_sDroneUID;
    batteryNode.attributes()[ATTR_LEVEL] = QString::number(m_iBatteryLevel);
    return batteryNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializeBatteryLevel(const QString &sBatteryLevel)
{
    CXMLNode batteryNode = CXMLNode::parseJSON(sBatteryLevel);
    QString sNodeType = batteryNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_BATTERY)
    {
        m_sDroneUID = batteryNode.attributes()[ATTR_DRONE_UID];
        setBatteryLevel(batteryNode.attributes()[ATTR_LEVEL].toInt());
    }
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializeReturnLevel()
{
    CXMLNode returnNode(TAG_RETURN);
    returnNode.attributes()[ATTR_NODE_TYPE] = TAG_RETURN;
    returnNode.attributes()[ATTR_DRONE_UID] = m_sDroneUID;
    returnNode.attributes()[ATTR_LEVEL] = QString::number(m_iReturnLevel);
    return returnNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializeReturnLevel(const QString &sReturnLevel)
{
    CXMLNode returnNode = CXMLNode::parseJSON(sReturnLevel);
    QString sNodeType = returnNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_RETURN)
    {
        m_sDroneUID = returnNode.attributes()[ATTR_DRONE_UID];
        setReturnLevel(returnNode.attributes()[ATTR_LEVEL].toInt());
    }
}

//-------------------------------------------------------------------------------------------------


QString DroneBase::serializeSafetyPlan()
{
    return serializePlan(m_safetyPlan, TAG_SAFETY_PLAN, m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------


void DroneBase::deserializeSafetyPlan(const QString &sSafetyPlan)
{
    CXMLNode safetyPlanNode = CXMLNode::parseJSON(sSafetyPlan);
    QString sNodeType = safetyPlanNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_SAFETY_PLAN)
    {
        QGeoPath safetyPlan;
        deserializePlan(safetyPlanNode, safetyPlan, m_sDroneUID);
        setSafetyPlan(safetyPlan);
    }
}

//-------------------------------------------------------------------------------------------------


QString DroneBase::serializeMissionPlan()
{
    return serializePlan(m_missionPlan, TAG_MISSION_PLAN, m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------


void DroneBase::deserializeMissionPlan(const QString &sMissionPlan)
{
    CXMLNode missionPlanNode = CXMLNode::parseJSON(sMissionPlan);
    QString sNodeType = missionPlanNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_MISSION_PLAN)
    {
        WayPointList missionPlan;
        deserializePlan(missionPlanNode, missionPlan, m_sDroneUID);
        setMissionPlan(missionPlan);
    }
}

//-------------------------------------------------------------------------------------------------


QString DroneBase::serializeLandingPlan()
{
    return serializePlan(m_landingPlan, TAG_LANDING_PLAN, m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------


void DroneBase::deserializeLandingPlan(const QString &sLandingPlan)
{
    CXMLNode landingPlanNode = CXMLNode::parseJSON(sLandingPlan);
    QString sNodeType = landingPlanNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_LANDING_PLAN)
    {
        WayPointList landingPlan;
        deserializePlan(landingPlanNode, landingPlan, m_sDroneUID);
        setLandingPlan(landingPlan);
    }
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializePlan(const WayPointList &plan, const QString &sPlanType, const QString &sDroneUID)
{
    CXMLNode planNode(sPlanType);
    planNode.attributes()[ATTR_NODE_TYPE] = sPlanType;
    planNode.attributes()[ATTR_DRONE_UID] = sDroneUID;
    foreach (WayPoint wayPoint, plan)
    {
        // Static attributes
        CXMLNode wayPointNode(TAG_WAY_POINT);
        wayPointNode.attributes()[ATTR_LATITUDE] = QString::number(wayPoint.geoCoord().latitude());
        wayPointNode.attributes()[ATTR_LONGITUDE] = QString::number(wayPoint.geoCoord().longitude());
        wayPointNode.attributes()[ATTR_ALTITUDE] = QString::number( wayPoint.geoCoord().altitude());
        wayPointNode.attributes()[ATTR_WAY_POINT_TYPE] = QString::number((int)wayPoint.type());
        wayPointNode.attributes()[ATTR_WAY_POINT_SPEED] = QString::number((int)wayPoint.speed());
        wayPointNode.attributes()[ATTR_WAY_POINT_CLOCKWISE] = QString::number((int)wayPoint.clockWise());

        // Metadata
        if (!wayPoint.metaData().isEmpty())
        {
            CXMLNode wayPointMetaDataNode(TAG_WAY_POINT_METADATA);
            for (QHash<QString, double>::const_iterator it=wayPoint.metaData().begin(); it!=wayPoint.metaData().end(); ++it)
                wayPointMetaDataNode.attributes()[it.key()] = QString::number(it.value());
            wayPointNode.nodes() << wayPointMetaDataNode;
        }
        planNode.nodes() << wayPointNode;
    }
    return planNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializePlan(const QGeoPath &plan, const QString &sPlanType, const QString &sDroneUID)
{
    CXMLNode planNode(sPlanType);
    planNode.attributes()[ATTR_NODE_TYPE] = sPlanType;
    planNode.attributes()[ATTR_DRONE_UID] = sDroneUID;
    for (int i=0; i<plan.size(); i++)
    {
        // Get geocoord
        QGeoCoordinate geoCoord = plan.coordinateAt(i);

        // Static attributes
        CXMLNode wayPointNode(TAG_WAY_POINT);
        wayPointNode.attributes()[ATTR_LATITUDE] = QString::number(geoCoord.latitude());
        wayPointNode.attributes()[ATTR_LONGITUDE] = QString::number(geoCoord.longitude());
        wayPointNode.attributes()[ATTR_ALTITUDE] = QString::number( geoCoord.altitude());
        planNode.nodes() << wayPointNode;
    }
    return planNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializePlan(const CXMLNode &node, WayPointList &vWayPointList, QString &sDroneUID)
{
    sDroneUID = node.attributes()[ATTR_DRONE_UID];
    QVector<CXMLNode> vWayPointNodes = node.getNodesByTagName(TAG_WAY_POINT);
    foreach (CXMLNode wayPointNode, vWayPointNodes)
    {
        // Static attributes
        double dLatitude = wayPointNode.attributes()[ATTR_LATITUDE].toDouble();
        double dLongitude = wayPointNode.attributes()[ATTR_LONGITUDE].toDouble();
        double dAltitude = wayPointNode.attributes()[ATTR_ALTITUDE].toDouble();
        int iType = wayPointNode.attributes()[ATTR_WAY_POINT_TYPE].toInt();
        int iSpeed = wayPointNode.attributes()[ATTR_WAY_POINT_SPEED].toInt();
        bool bClockWise = (bool)wayPointNode.attributes()[ATTR_WAY_POINT_CLOCKWISE].toInt();

        QGeoCoordinate geoCoord(dLatitude, dLongitude, dAltitude);
        WayPoint wayPoint(geoCoord, (SpyCore::PointType)iType);
        wayPoint.setSpeed((SpyCore::PointSpeed)iSpeed);
        wayPoint.setClockWise(bClockWise);
        vWayPointList << wayPoint;
    }
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializePlan(const CXMLNode &node, QGeoPath &geoPath, QString &sDroneUID)
{
    sDroneUID = node.attributes()[ATTR_DRONE_UID];
    QVector<CXMLNode> vWayPointNodes = node.getNodesByTagName(TAG_WAY_POINT);
    foreach (CXMLNode wayPointNode, vWayPointNodes)
    {
        // Static attributes
        double dLatitude = wayPointNode.attributes()[ATTR_LATITUDE].toDouble();
        double dLongitude = wayPointNode.attributes()[ATTR_LONGITUDE].toDouble();
        double dAltitude = wayPointNode.attributes()[ATTR_ALTITUDE].toDouble();
        QGeoCoordinate geoCoord(dLatitude, dLongitude, dAltitude);
        geoPath.addCoordinate(geoCoord);
    }
}

//-------------------------------------------------------------------------------------------------

bool DroneBase::hasSafetyPlan() const
{
    return !m_safetyPlan.isEmpty();
}

//-------------------------------------------------------------------------------------------------

bool DroneBase::hasMissionPlan() const
{
    return !m_missionPlan.isEmpty();
}

//-------------------------------------------------------------------------------------------------

bool DroneBase::hasLandingPlan() const
{
    return !m_landingPlan.isEmpty();
}

//-------------------------------------------------------------------------------------------------

bool DroneBase::hasExclusionArea() const
{
    return !m_vExclusionArea.isEmpty();
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::serializeExclusionArea()
{
    CXMLNode exclAreaNode(TAG_EXCLUSION_AREA);
    exclAreaNode.attributes()[ATTR_NODE_TYPE] = TAG_EXCLUSION_AREA;
    exclAreaNode.attributes()[ATTR_DRONE_UID] = m_sDroneUID;
    for (int i=0; i<m_vExclusionArea.size(); i++)
    {
        BaseShape *pShape = m_vExclusionArea.at(i);
        if (pShape != nullptr)
        {
            qDebug() << "ADDING SHAPE";
            // Write shapes
            CXMLNode shapeNode = CXMLNode::parseJSON(pShape->serialize());
            shapeNode.setTag(TAG_SHAPES);
            exclAreaNode.nodes() << shapeNode;
        }
    }
    return exclAreaNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::deserializeExclusionArea(const QString &sExclusionArea)
{
    CXMLNode exclusionAreaNode = CXMLNode::parseJSON(sExclusionArea);
    QString sNodeType = exclusionAreaNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_EXCLUSION_AREA)
    {
        //! Exclusion area
        QVector<BaseShape *> vExclusionArea;

        m_sDroneUID = exclusionAreaNode.attributes()[ATTR_DRONE_UID];
        QVector<CXMLNode> vShapeNodes = exclusionAreaNode.getNodesByTagName(TAG_SHAPES);
        foreach (CXMLNode shapeNode, vShapeNodes)
        {
            SpyCore::ExclusionShape eShapeType = (SpyCore::ExclusionShape)shapeNode.attributes()[ATTR_NODE_TYPE].toInt();
            if (eShapeType == SpyCore::RECTANGLE)
            {
                QGeoCoordinate center;
                QGeoPath geoPath;
                RectangleShape::deserialize(shapeNode.toJsonString(), center, geoPath);
                if (geoPath.size() == 4)
                {
                    RectangleShape *pShape = new RectangleShape(this);
                    pShape->setPath(geoPath);
                    vExclusionArea << pShape;
                }
            }
            else
            if (eShapeType == SpyCore::TRIANGLE)
            {
                QGeoCoordinate center;
                QGeoPath geoPath;
                TriangleShape::deserialize(shapeNode.toJsonString(), center, geoPath);
                if (geoPath.size() == 3)
                {
                    TriangleShape *pShape = new TriangleShape(this);
                    pShape->setPath(geoPath);
                    vExclusionArea << pShape;
                }
            }
            else
            if (eShapeType == SpyCore::CIRCLE)
            {
                QGeoCoordinate center;
                double dRadius = 0;
                CircleShape::deserialize(shapeNode.toJsonString(), center, dRadius);
                CircleShape *pShape = new CircleShape(center, dRadius, this);
                vExclusionArea << pShape;
            }
        }

        setExclusionArea(vExclusionArea);
    }
}
