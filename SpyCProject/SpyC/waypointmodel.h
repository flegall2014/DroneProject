#ifndef WAYPOINTMODEL_H
#define WAYPOINTMODEL_H

// Qt
#include <QAbstractListModel>
#include <QVector>
#include <QGeoCoordinate>
#include <QGeoPath>

// Application
#include <waypoint.h>

class WayPointModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QGeoPath path READ path NOTIFY pathChanged)
    Q_PROPERTY(int pointCount READ pointCount NOTIFY pathChanged)
    Q_PROPERTY(int currentPointIndex READ currentPointIndex WRITE setCurrentPointIndex NOTIFY currentPointIndexChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    WayPointModel(QObject *pParent=nullptr);

    //! Destructor
    ~WayPointModel();

    //-------------------------------------------------------------------------------------------------
    // QAbstractListModel interface
    //-------------------------------------------------------------------------------------------------

    //! Return row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return data
    virtual QVariant data(const QModelIndex &index, int role) const;

    //! Set point position
    void setPointPosition(int iIndex, const QGeoCoordinate &geoCoord);

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return path
    QGeoPath path();

    //! Return point count
    int pointCount() const;

    //! Return current point index
    int currentPointIndex() const;

    //! Set current point index
    void setCurrentPointIndex(int iIndex);

    //! Return plan
    const WayPointList &plan() const;

    //! Return geopath
    QGeoPath geoPath() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set plan
    void setPlan(const WayPointList &vWayPointList);

    //! Set plan
    void setPlan(const QGeoPath &geoPath);

    //! Add coordinate
    void addCoordinate(const QGeoCoordinate &coordinate, int iPosition=-1);

    //! Remove coordinate at index
    void removeCoordinateAtIndex(int iCoordIndex);

    //! Clear mission plan
    void clear();

    //! Close path
    void closePath();

private:
    //! Way points
    WayPointList m_vWayPoints;

    //! Current point index
    int m_iCurrentPointIndex = 0;

signals:
    //! Path changed
    void pathChanged();

    //! Current point index changed
    void currentPointIndexChanged();
};

#endif // WAYPOINTMODEL_H
