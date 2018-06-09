// Qt
#include <QDebug>

// Application
#include "baseshape.h"
#include <cxmlnode.h>
#include <defs.h>
#define BASE_INCREMENT 100
using namespace Core;

//-------------------------------------------------------------------------------------------------

BaseShape::BaseShape(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

BaseShape::~BaseShape()
{

}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate BaseShape::computeCenter() const
{
    if (m_path.size() > 0)
    {
        double dTotalLat = 0, dTotalLon = 0;
        for (int i=0; i<m_path.size(); i++)
        {
            dTotalLat += m_path.coordinateAt(i).latitude();
            dTotalLon += m_path.coordinateAt(i).longitude();
        }
        return QGeoCoordinate(dTotalLat/m_path.size(), dTotalLon/m_path.size());
    }

    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::rotate(double dAngle)
{
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Increment by angle
        dAzimuth += dAngle;

        // New coord
        QGeoCoordinate newCoord = m_center.atDistanceAndAzimuth(dDistance, dAzimuth);

        // Update point
        m_path.replaceCoordinate(i, newCoord);
    }

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::moveTo(const QGeoCoordinate &pos)
{
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Update point
        m_path.replaceCoordinate(i, pos.atDistanceAndAzimuth(dDistance, dAzimuth));
    }

    // Update pos
    m_center = pos;

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::rescale(int iIncrement)
{
    bool bUpScale = iIncrement >= 0;
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Update point
        m_path.replaceCoordinate(i, m_center.atDistanceAndAzimuth(dDistance+(bUpScale ? BASE_INCREMENT : -BASE_INCREMENT), dAzimuth));
    }

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setLatitudeAtIndex(int iIndex, double dLatitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setLatitude(dLatitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setLongitudeAtIndex(int iIndex, double dLatitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setLongitude(dLatitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setAltitudeAtIndex(int iIndex, double dAltitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setAltitude(dAltitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QString BaseShape::serialize()
{
    Core::CXMLNode shapeNode;
    if (m_eType == SpyCore::RECTANGLE)
        shapeNode.setTag(TAG_RECTANGLE);
    else
    if (m_eType == SpyCore::TRIANGLE)
        shapeNode.setTag(TAG_TRIANGLE);
    else return QString("");
    shapeNode.attributes()[ATTR_NODE_TYPE] = QString::number(m_eType);
    QStringList lCenter;
    lCenter << QString::number(m_center.latitude()) << QString::number(m_center.longitude());
    shapeNode.attributes()[ATTR_CENTER] = lCenter.join(",");
    for (int i=0; i<m_path.size(); i++)
    {
        Core::CXMLNode coordNode(TAG_COORD);
        coordNode.attributes()[ATTR_LATITUDE] = m_path.coordinateAt(i).latitude();
        coordNode.attributes()[ATTR_LONGITUDE] = m_path.coordinateAt(i).longitude();
        shapeNode.nodes() << coordNode;
    }
    return shapeNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

const QGeoPath &BaseShape::path() const
{
    return m_path;
}

//-------------------------------------------------------------------------------------------------

int BaseShape::count() const
{
    return m_path.size();
}

//-------------------------------------------------------------------------------------------------

int BaseShape::type() const
{
    return (int)m_eType;
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &BaseShape::center() const
{
    return m_center;
}

//-------------------------------------------------------------------------------------------------

RectangleShape::RectangleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = SpyCore::RECTANGLE;
}

//-------------------------------------------------------------------------------------------------

RectangleShape::RectangleShape(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight, QObject *pParent) :
    BaseShape(pParent)
{
    m_eType = SpyCore::RECTANGLE;
    m_path.addCoordinate(topLeft);
    m_path.addCoordinate(QGeoCoordinate(bottomRight.latitude(), topLeft.longitude()));
    m_path.addCoordinate(bottomRight);
    m_path.addCoordinate(QGeoCoordinate(topLeft.latitude(), bottomRight.longitude()));
    m_center = computeCenter();
}

//-------------------------------------------------------------------------------------------------

RectangleShape::~RectangleShape()
{

}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate RectangleShape::topLeft() const
{
    if (!m_path.isEmpty())
        return m_path.coordinateAt(0);
    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate RectangleShape::bottomRight() const
{
    if (m_path.size() > 2)
        return m_path.coordinateAt(2);
    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

void RectangleShape::setPath(const QGeoPath &path)
{
    if (m_path.size() == 4)
    {
        m_path = path;
        m_center = computeCenter();
    }
}

//-------------------------------------------------------------------------------------------------

void RectangleShape::deserialize(const QString &sSerialized, QGeoCoordinate &center, QGeoPath &geoPath)
{
    Core::CXMLNode rootNode = Core::CXMLNode::parseJSON(sSerialized);
    SpyCore::ExclusionShape eShapeType = (SpyCore::ExclusionShape)rootNode.attributes()[ATTR_NODE_TYPE].toInt();
    if (eShapeType == SpyCore::RECTANGLE)
    {
        QString sCenter = rootNode.attributes()[ATTR_CENTER];
        QStringList lSplitted = sCenter.split(",");
        if (lSplitted.size() == 2)
        {
            double dLatitude = lSplitted.first().toDouble();
            double dLongitude = lSplitted[1].toDouble();
            center.setLatitude(dLatitude);
            center.setLongitude(dLongitude);
        }

        QVector<Core::CXMLNode> vCoordNodes = rootNode.getNodesByTagName(TAG_COORD);
        foreach (Core::CXMLNode coordNode, vCoordNodes)
        {
            double dLatitude = coordNode.attributes()[ATTR_LATITUDE].toDouble();
            double dLongitude = coordNode.attributes()[ATTR_LONGITUDE].toDouble();
            QGeoCoordinate geoCoord(dLatitude, dLongitude);
            geoPath.addCoordinate(geoCoord);
        }
    }
}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = SpyCore::CIRCLE;
}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(const QGeoCoordinate &center, double dRadius, QObject *pParent) : BaseShape(pParent),
    m_dRadius(dRadius)
{
    m_eType = SpyCore::CIRCLE;
    m_center = center;
}

//-------------------------------------------------------------------------------------------------

CircleShape::~CircleShape()
{

}

//-------------------------------------------------------------------------------------------------

double CircleShape::radius() const
{
    return m_dRadius;
}

//-------------------------------------------------------------------------------------------------

QString CircleShape::serialize()
{
    Core::CXMLNode circleNode(TAG_CIRCLE);
    circleNode.attributes()[ATTR_NODE_TYPE] = QString::number(SpyCore::CIRCLE);
    QStringList lCenter;
    lCenter << QString::number(m_center.latitude()) << QString::number(m_center.longitude());
    circleNode.attributes()[ATTR_CENTER] = lCenter.join(",");
    circleNode.attributes()[ATTR_RADIUS] = QString::number(m_dRadius);
    return circleNode.toJsonString();
}

//-------------------------------------------------------------------------------------------------

void CircleShape::deserialize(const QString &sSerialized, QGeoCoordinate &center, double &dRadius)
{
    Core::CXMLNode rootNode = Core::CXMLNode::parseJSON(sSerialized);
    SpyCore::ExclusionShape eShapeType = (SpyCore::ExclusionShape)rootNode.attributes()[ATTR_NODE_TYPE].toInt();
    if (eShapeType == SpyCore::CIRCLE)
    {
        Core::CXMLNode rootNode = Core::CXMLNode::parseJSON(sSerialized);
        QString sCenter = rootNode.attributes()[ATTR_CENTER];
        QStringList lSplitted = sCenter.split(",");
        if (lSplitted.size() == 2)
        {
            double dLatitude = lSplitted.first().toDouble();
            double dLongitude = lSplitted[1].toDouble();
            center.setLatitude(dLatitude);
            center.setLongitude(dLongitude);
        }
        dRadius = rootNode.attributes()[ATTR_RADIUS].toDouble();
    }
}

//-------------------------------------------------------------------------------------------------

void CircleShape::rotate(double dAngle)
{
    // No op
    Q_UNUSED(dAngle);
}

//-------------------------------------------------------------------------------------------------

void CircleShape::rescale(int iIncrement)
{
    bool bUpScale = iIncrement >= 0;
    m_dRadius += (bUpScale ? BASE_INCREMENT : -BASE_INCREMENT);
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = SpyCore::TRIANGLE;
}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3, QObject *pParent) :
    BaseShape(pParent)
{
    m_eType = SpyCore::TRIANGLE;
    m_path.addCoordinate(point1);
    m_path.addCoordinate(point2);
    m_path.addCoordinate(point3);
    m_center = computeCenter();
}

//-------------------------------------------------------------------------------------------------

TriangleShape::~TriangleShape()
{

}

//-------------------------------------------------------------------------------------------------

void TriangleShape::setPath(const QGeoPath &path)
{
    if (path.size() == 3)
    {
        m_path = path;
        m_center = computeCenter();
    }
}

//-------------------------------------------------------------------------------------------------

void TriangleShape::deserialize(const QString &sSerialized, QGeoCoordinate &center, QGeoPath &geoPath)
{
    Core::CXMLNode rootNode = Core::CXMLNode::parseJSON(sSerialized);
    SpyCore::ExclusionShape eShapeType = (SpyCore::ExclusionShape)rootNode.attributes()[ATTR_NODE_TYPE].toInt();
    if (eShapeType == SpyCore::TRIANGLE)
    {
        QString sCenter = rootNode.attributes()[ATTR_CENTER];
        QStringList lSplitted = sCenter.split(",");
        if (lSplitted.size() == 2)
        {
            double dLatitude = lSplitted.first().toDouble();
            double dLongitude = lSplitted[1].toDouble();
            center.setLatitude(dLatitude);
            center.setLongitude(dLongitude);
        }

        QVector<Core::CXMLNode> vCoordNodes = rootNode.getNodesByTagName(TAG_COORD);
        foreach (Core::CXMLNode coordNode, vCoordNodes)
        {
            double dLatitude = coordNode.attributes()[ATTR_LATITUDE].toDouble();
            double dLongitude = coordNode.attributes()[ATTR_LONGITUDE].toDouble();
            QGeoCoordinate geoCoord(dLatitude, dLongitude);
            geoPath.addCoordinate(geoCoord);
        }
    }
}

