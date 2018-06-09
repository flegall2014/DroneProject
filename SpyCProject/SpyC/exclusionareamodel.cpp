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
        emit shapeCountChanged();
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

void ExclusionAreaModel::setShapes(const QVector<Core::BaseShape *> &vShapes)
{
    beginResetModel();
    qDeleteAll(m_vShapes);
    m_vShapes.clear();
    m_vShapes = vShapes;
    foreach (Core::BaseShape *pShape, vShapes) {
        qDebug() << "LOLO ! " << pShape;
        Core::RectangleShape *p = dynamic_cast<Core::RectangleShape *>(pShape);
        if (p!=nullptr)
            qDebug() << p->topLeft().latitude() << p->topLeft().longitude() << p->bottomRight().latitude() << p->bottomRight().longitude();
    }
    endResetModel();
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::shapeCount() const
{
    return rowCount();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addRectangle(const QGeoCoordinate &center)
{
    QGeoCoordinate topLeft = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 135);
    QGeoCoordinate bottomRight = center.atDistanceAndAzimuth(DEFAULT_RADIUS, -45);
    Core::RectangleShape *pShape = new Core::RectangleShape(topLeft, bottomRight, this);
    setCurrentShape(pShape);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addCircle(const QGeoCoordinate &center)
{
    Core::CircleShape *pShape = new Core::CircleShape(center, DEFAULT_RADIUS, this);
    setCurrentShape(pShape);
    addShape(pShape);
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
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::clear()
{
    beginResetModel();
    qDeleteAll(m_vShapes);
    m_vShapes.clear();
    endResetModel();
    emit shapeCountChanged();
}

//-------------------------------------------------------------------------------------------------

const QVector<Core::BaseShape *> &ExclusionAreaModel::shapes() const
{
    return m_vShapes;
}
