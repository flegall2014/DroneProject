#ifndef DRONEMODEL_H
#define DRONEMODEL_H

// Qt
#include <QAbstractListModel>

// Application
#include <alert.h>
namespace Core {
class DroneBase;
}

class DroneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int droneCount READ droneCount NOTIFY droneCountChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    DroneModel(QObject *pParent=nullptr);

    //! Destructor
    ~DroneModel();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add drone
    void addDrone(Core::DroneBase *pDrone);

    //-------------------------------------------------------------------------------------------------
    // QAbstractItemModel methods
    //-------------------------------------------------------------------------------------------------

    //! Data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Return row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

private:
    //! Return drone count
    int droneCount() const;

private:
    //! Drones
    QVector<Core::DroneBase *> m_vDrones;

public slots:
    //! Update view
    void onUpdateView();

signals:
    //! Drone count changed
    void droneCountChanged();
};

#endif // DRONEMODEL_H
