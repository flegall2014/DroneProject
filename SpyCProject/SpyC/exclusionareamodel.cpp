// Qt
#include <QDebug>
#include <QGeoCoordinate>

// Application
#include "exclusionareamodel.h"
#include <baseshape.h>

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::ExclusionAreaModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::~ExclusionAreaModel()
{

}

//-------------------------------------------------------------------------------------------------

QVariant ExclusionAreaModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > rowCount()-1))
        return QVariant();
    if (iRole == SpyCore::Shape)
        return QVariant::fromValue(m_vShapes[index.row()]);
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vShapes.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> ExclusionAreaModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[SpyCore::Shape] = "shape";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addShape(Core::BaseShape *pShape)
{
    if (pShape != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vShapes << pShape;
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

Core::BaseShape *ExclusionAreaModel::currentShape() const
{
    return m_pCurrentShape;
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::setCurrentShape(Core::BaseShape *pShape)
{
    m_pCurrentShape = pShape;
    emit currentShapeChanged();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::shapeCount() const
{
    return rowCount();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addRectangle(const QGeoCoordinate &center)
{
    qDebug() << "ADD RECTANGLE " << center.latitude() << center.longitude();
    QGeoCoordinate topLeft = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 135);
    QGeoCoordinate bottomRight = center.atDistanceAndAzimuth(DEFAULT_RADIUS, -45);
    qDebug() << topLeft.latitude() << topLeft.longitude();
    qDebug() << bottomRight.latitude() << bottomRight.longitude();

    Core::RectangleShape *pShape = new Core::RectangleShape(topLeft, bottomRight, this);
    setCurrentShape(pShape);
    addShape(pShape);
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addCircle(const QGeoCoordinate &center)
{
    Core::CircleShape *pShape = new Core::CircleShape(center, DEFAULT_RADIUS, this);
    setCurrentShape(pShape);
    addShape(pShape);
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addTriangle(const QGeoCoordinate &center)
{
    QGeoCoordinate point1 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 90);
    QGeoCoordinate point2 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 210);
    QGeoCoordinate point3 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 330);
    Core::TriangleShape *pShape = new Core::TriangleShape(point1, point2, point3, this);
    setCurrentShape(pShape);
    addShape(pShape);
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::removeShape(int iShapeIndex)
{
    beginResetModel();
    Core::BaseShape *pShape = m_vShapes.takeAt(iShapeIndex);
    if (pShape != nullptr)
        delete pShape;
    endResetModel();
    setCurrentShape(nullptr);
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::clear()
{
    beginResetModel();
    qDeleteAll(m_vShapes);
    m_vShapes.clear();
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

const QVector<Core::BaseShape *> &ExclusionAreaModel::shapes() const
{
    return m_vShapes;
}