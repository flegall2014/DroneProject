// Qt
#include <QDebug>

// Application
#include "alertmodel.h"

//-------------------------------------------------------------------------------------------------

AlertModel::AlertModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

AlertModel::~AlertModel()
{

}

//-------------------------------------------------------------------------------------------------

void AlertModel::addAlert(const Alert &alert)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_vAlerts << alert;
    endInsertRows();
}

//-------------------------------------------------------------------------------------------------

QVariant AlertModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (m_vAlerts.size()-1)))
        return QVariant();
    if (iRole == SpyCore::AlertIdentification)
        return m_vAlerts[index.row()].type();
    if (iRole == SpyCore::AlertLevel)
        return m_vAlerts[index.row()].level();
    if (iRole == SpyCore::AlertMsg)
        return m_vAlerts[index.row()].what();
    if (iRole == SpyCore::AlertDate)
        return m_vAlerts[index.row()].dateTime();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int AlertModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vAlerts.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> AlertModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[SpyCore::AlertIdentification] = "type";
    hRoleNames[SpyCore::AlertLevel] = "level";
    hRoleNames[SpyCore::AlertMsg] = "what";
    hRoleNames[SpyCore::AlertDate] = "date";

    return hRoleNames;
}
