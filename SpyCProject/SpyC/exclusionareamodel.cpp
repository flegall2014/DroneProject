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
        return QVariant::fromValue(m_vExclusionArea[index.row()]);
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vExclusionArea.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> ExclusionAreaModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[SpyCore::Shape] = "shape";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addExclusionArea(Core::BaseShape *pShape)
{
    if (pShape != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vExclusionArea << pShape;
        endInsertRows();
        emit exclusionAreaCountChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::setExclusionArea(const QVector<Core::BaseShape *> &vShapes)
{
    if (vShapes != m_vExclusionArea)
    {
        beginResetModel();
        m_vExclusionArea = vShapes;
        endResetModel();
        emit exclusionAreaCountChanged();
    }
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::shapeCount() const
{
    return rowCount();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::removeExclusionArea(int iShapeIndex)
{
    beginResetModel();
    Core::BaseShape *pShape = m_vExclusionArea.takeAt(iShapeIndex);
    if (pShape != nullptr)
        delete pShape;
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::clear()
{
    beginResetModel();
    m_vExclusionArea.clear();
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

const QVector<Core::BaseShape *> &ExclusionAreaModel::shapes() const
{
    return m_vExclusionArea;
}
