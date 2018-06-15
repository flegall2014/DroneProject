#ifndef EXCLUSIONAREAMODEL_H
#define EXCLUSIONAREAMODEL_H

// Qt
#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QGeoPath>

// Application
namespace Core {
class BaseShape;
}

class ExclusionAreaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int shapeCount READ shapeCount NOTIFY exclusionAreaCountChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    ExclusionAreaModel(QObject *pParent=nullptr);

    //! Destructor
    ~ExclusionAreaModel();

    //-------------------------------------------------------------------------------------------------
    // QAbstractListModel interface
    //-------------------------------------------------------------------------------------------------

    //! Return data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add shape
    void addExclusionArea(Core::BaseShape *pShape);

    //! Remove shape
    void removeExclusionArea(int iShapeIndex);

    //! Clear
    void clear();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return exclusion area list
    const QVector<Core::BaseShape *> &shapes() const;

    //! Set shapes
    void setExclusionArea(const QVector<Core::BaseShape *> &vShapes);

private:
    //! Return shape count
    int shapeCount() const;

private:
    //! Shapes
    QVector<Core::BaseShape *> m_vExclusionArea;

signals:
    //! Shape count changed
    void exclusionAreaCountChanged();
};

#endif // EXCLUSIONAREAMODEL_H
