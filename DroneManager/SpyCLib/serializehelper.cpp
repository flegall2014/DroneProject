// Qt
#include <QGeoCoordinate>
#include <QDebug>
#include <QFile>

// Application
#include "serializehelper.h"
#include "waypoint.h"
#include "defs.h"
using namespace Core;

//-------------------------------------------------------------------------------------------------

QString SerializeHelper::serializeDroneError(const SpyCore::DroneError &eDroneError, const QString &sDroneUID)
{
    CXMLNode errorNode(TAG_DRONE_ERROR);
    errorNode.attributes()[ATTR_NODE_TYPE] = TAG_DRONE_ERROR;
    errorNode.attributes()[ATTR_DRONE_UID] = sDroneUID;
    errorNode.attributes()[ATTR_ERROR] = QString::number((int)eDroneError);
    return errorNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void SerializeHelper::deSerializeDroneError(const QString &sMessage, SpyCore::DroneError &eDroneError, QString &sDroneUID)
{
    CXMLNode rootNode = CXMLNode::parseJSON(sMessage);
    QString sNodeType = rootNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_DRONE_ERROR)
    {
        sDroneUID = rootNode.attributes()[ATTR_DRONE_UID];
        eDroneError = (SpyCore::DroneError)rootNode.attributes()[ATTR_ERROR].toInt();
    }
}

//-------------------------------------------------------------------------------------------------

QString SerializeHelper::serializeTakeOffRequest(const QString &sDroneUID)
{
    CXMLNode takeOffNode(TAG_TAKE_OFF);
    takeOffNode.attributes()[ATTR_NODE_TYPE] = TAG_TAKE_OFF;
    takeOffNode.attributes()[ATTR_DRONE_UID] = sDroneUID;
    return takeOffNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void SerializeHelper::deserializeTakeOffRequest(const QString &sMessage, QString &sDroneUID)
{
    CXMLNode rootNode = CXMLNode::parseJSON(sMessage);
    QString sNodeType = rootNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_TAKE_OFF)
        sDroneUID = rootNode.attributes()[ATTR_DRONE_UID];
}

//-------------------------------------------------------------------------------------------------

QString SerializeHelper::serializeFailSafeRequest(const QString &sDroneUID)
{
    CXMLNode failSafeNode(TAG_FAIL_SAFE);
    failSafeNode.attributes()[ATTR_NODE_TYPE] = TAG_FAIL_SAFE;
    failSafeNode.attributes()[ATTR_DRONE_UID] = sDroneUID;
    return failSafeNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void SerializeHelper::deserializeFailSafeRequest(const QString &sMessage, QString &sDroneUID)
{
    CXMLNode rootNode = CXMLNode::parseJSON(sMessage);
    QString sNodeType = rootNode.attributes()[ATTR_NODE_TYPE];
    if (sNodeType == TAG_FAIL_SAFE)
        sDroneUID = rootNode.attributes()[ATTR_DRONE_UID];
}

//-------------------------------------------------------------------------------------------------

QString SerializeHelper::messageType(const QString &sMessage)
{
    CXMLNode rootNode = CXMLNode::parseJSON(sMessage);
    return rootNode.attributes()[ATTR_NODE_TYPE];
}

//-------------------------------------------------------------------------------------------------

QString SerializeHelper::droneUID(const QString &sMessage)
{
    CXMLNode rootNode = CXMLNode::parseJSON(sMessage);
    return rootNode.attributes()[ATTR_DRONE_UID];
}
