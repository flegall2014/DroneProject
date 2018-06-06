// Qt
#include <QDebug>

// Application
#include "waypointmodel.h"
#include <spycore.h>

//-------------------------------------------------------------------------------------------------

WayPointModel::WayPointModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

WayPointModel::~WayPointModel()
{

}

//-------------------------------------------------------------------------------------------------

int WayPointModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vWayPoints.size();
}

//-------------------------------------------------------------------------------------------------

QVariant WayPointModel::data(const QModelIndex &index, int iRole) const
{
    // Check index
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > rowCount()-1))
        return QVariant();

    // Return way point index
    if (iRole == SpyCore::WayPointIndex)
        return index.row();

    // Return way point at index
    if (iRole == SpyCore::WayPointCoordinate)
        return QVariant::fromValue(m_vWayPoints[index.row()].geoCoord());

    // Return way point latitude
    if (iRole == SpyCore::WayPointLatitude)
        return m_vWayPoints[index.row()].geoCoord().latitude();

    // Return way point longitude
    if (iRole == SpyCore::WayPointLongitude)
        return m_vWayPoints[index.row()].geoCoord().longitude();

    // Return way point altitude
    if (iRole == SpyCore::WayPointAltitude)
        return m_vWayPoints[index.row()].geoCoord().altitude();

    // Return way point type
    if (iRole == SpyCore::WayPointType)
        return (int)m_vWayPoints[index.row()].type();

    // Return way point speed
    if (iRole == SpyCore::WayPointSpeed)
        return (int)m_vWayPoints[index.row()].speed();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setPointPosition(int iIndex, const QGeoCoordinate &geoCoord)
{
    QModelIndex srcIndex = index(iIndex, 0, QModelIndex());
    if (srcIndex.isValid())
    {
        Core::WayPoint currentWayPoint = m_vWayPoints[iIndex];
        currentWayPoint.setGeoCoord(geoCoord);
        m_vWayPoints.replace(iIndex, currentWayPoint);
        emit dataChanged(srcIndex, srcIndex);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> WayPointModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[SpyCore::WayPointIndex] = "wayPointIndex";
    hRoleNames[SpyCore::WayPointCoordinate] = "wayPointCoordinate";
    hRoleNames[SpyCore::WayPointLatitude] = "wayPointLatitude";
    hRoleNames[SpyCore::WayPointAltitude] = "wayPointAltitude";
    hRoleNames[SpyCore::WayPointLongitude] = "wayPointLongitude";
    hRoleNames[SpyCore::WayPointType] = "wayPointType";
    hRoleNames[SpyCore::WayPointType] = "wayPointSpeed";

    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

QGeoPath WayPointModel::path()
{
    QGeoPath geoPath;
    foreach (Core::WayPoint wayPoint, m_vWayPoints)
        geoPath.addCoordinate(wayPoint.geoCoord());
    return geoPath;
}

//-------------------------------------------------------------------------------------------------

int WayPointModel::pointCount() const
{
    return m_vWayPoints.size();
}

//-------------------------------------------------------------------------------------------------

int WayPointModel::currentPointIndex() const
{
    return m_iCurrentPointIndex;
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setCurrentPointIndex(int iIndex)
{
    m_iCurrentPointIndex = iIndex;
    emit currentPointIndexChanged();
}

//-------------------------------------------------------------------------------------------------

const WayPointList &WayPointModel::plan() const
{
    return m_vWayPoints;
}

//-------------------------------------------------------------------------------------------------

QGeoPath WayPointModel::geoPath() const
{
    QGeoPath geoPath;
    foreach (Core::WayPoint wayPoint, m_vWayPoints)
        geoPath.addCoordinate(wayPoint.geoCoord());
    return geoPath;
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setPlan(const WayPointList &vWayPointList)
{
    beginResetModel();
    m_vWayPoints = vWayPointList;
    endResetModel();
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setPlan(const QGeoPath &geoPath)
{
    m_vWayPoints.clear();
    beginResetModel();
    int iPathSize = geoPath.size();
    for (int i=0; i<iPathSize; i++)
        m_vWayPoints << Core::WayPoint(geoPath.coordinateAt(i));
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::addCoordinate(const QGeoCoordinate &coordinate)
{
    beginResetModel();
    m_vWayPoints << Core::WayPoint(coordinate);
    endResetModel();
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::removeCoordinateAtIndex(int iCoordIndex)
{
    if ((iCoordIndex >= 0) && (iCoordIndex < rowCount()))
    {
        beginResetModel();
        m_vWayPoints.removeAt(iCoordIndex);
        endResetModel();
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::clear()
{
    beginResetModel();
    m_vWayPoints.clear();
    endResetModel();
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::closePath()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_vWayPoints << m_vWayPoints.first();
    endInsertRows();
    emit pathChanged();
}
