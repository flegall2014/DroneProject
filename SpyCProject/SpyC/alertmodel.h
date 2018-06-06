#ifndef ALERTMODEL_H
#define ALERTMODEL_H

// Qt
#include <QAbstractListModel>

// Application
#include <alert.h>
class DroneBase;

class AlertModel : public QAbstractListModel
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    AlertModel(QObject *pParent=nullptr);

    //! Destructor
    ~AlertModel();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add alert
    void addAlert(const Alert &alert);

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
    //! Alerts
    QVector<Alert> m_vAlerts;
};

#endif // ALERTMODEL_H
