// Qt
#include <QImage>
#include <QDir>
#include <QDebug>

// Application
#include "gallerymodel.h"
#include <spycore.h>

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(const QString &sSnapShotDir, QObject *pParent) : QAbstractListModel(pParent),
    m_sSnapShotDir(sSnapShotDir)
{

}

//-------------------------------------------------------------------------------------------------

GalleryModel::~GalleryModel()
{

}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> GalleryModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[SpyCore::FileNameRole] = "fileName";
    hRoleNames[SpyCore::FilePathRole] = "filePath";
    hRoleNames[SpyCore::PositionRole] = "position";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

QVariant GalleryModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();
    SnapShot snapShot = m_vSnaps[index.row()];
    QFileInfo fi(snapShot._filePath);

    if (iRole == SpyCore::FileNameRole)
        return fi.baseName();
    if (iRole == SpyCore::FilePathRole)
        return fi.absoluteFilePath();
    if (iRole == SpyCore::PositionRole)
        return qVariantFromValue(snapShot._geoCoord);

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int GalleryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vSnaps.size();
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::addSnapShot(const QString &sSnapShotPath, const QGeoCoordinate &position)
{
    QImage img(sSnapShotPath);
    if (!img.isNull())
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vSnaps << SnapShot(sSnapShotPath, position);
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

QString GalleryModel::getNextSnapShotName(const QString &sDroneUID)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int iYear = currentDateTime.date().year();
    int iMonth = currentDateTime.date().month();
    int iDay = currentDateTime.date().day();
    int iHour = currentDateTime.time().hour();
    int iMin = currentDateTime.time().minute();
    int iSec = currentDateTime.time().second();
    QString sUniqueName = QString("%1_%2_%3_%4_%5_%6_%7.jpg").arg(sDroneUID).arg(iYear).arg(iMonth).arg(iDay).arg(iHour).arg(iMin).arg(iSec);
    sUniqueName.replace(" ", "_");
    return QDir(m_sSnapShotDir).absoluteFilePath(sUniqueName);
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::initialize()
{
    beginResetModel();
    m_vSnaps.clear();
    QStringList lImages = QDir(m_sSnapShotDir).entryList(QStringList() << "*", QDir::Files);
    foreach (QString sImagePath, lImages)
    {
        QString sFullImagePath = QDir(m_sSnapShotDir).absoluteFilePath(sImagePath);
        QImage img(sFullImagePath);
        if (!img.isNull())
            m_vSnaps << SnapShot(sFullImagePath);
    }
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::removeCurrentScreenCap()
{
    if ((m_iCurrentScreenCapIndex >= 0) && (m_iCurrentScreenCapIndex < rowCount()))
    {
        QString sSnapShotPath = m_vSnaps[m_iCurrentScreenCapIndex]._filePath;
        beginRemoveRows(QModelIndex(), m_iCurrentScreenCapIndex, m_iCurrentScreenCapIndex);
        m_vSnaps.takeAt(m_iCurrentScreenCapIndex);
        endRemoveRows();
        QFile file(sSnapShotPath);
        file.remove();
    }
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::clear()
{
    foreach (SnapShot snapShot, m_vSnaps)
    {
        QFile file(snapShot._filePath);
        file.remove();
    }
    beginResetModel();
    m_vSnaps.clear();
    endResetModel();
}

//-------------------------------------------------------------------------------------------------

int GalleryModel::currentScreenCapIndex() const
{
    return m_iCurrentScreenCapIndex;
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::setCurrentScreenCapIndex(int iIndex)
{
    m_iCurrentScreenCapIndex = iIndex;
    emit currentScreenCapIndexChanged();
}

//-------------------------------------------------------------------------------------------------

QString GalleryModel::currentScreenCapPath() const
{
    if ((m_iCurrentScreenCapIndex >= 0) && (m_iCurrentScreenCapIndex < rowCount()))
        return m_vSnaps[m_iCurrentScreenCapIndex]._filePath;
    return QString("");
}
