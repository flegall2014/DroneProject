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
    Q_PROPERTY(Core::BaseShape *currentShape READ currentShape WRITE setCurrentShape NOTIFY currentShapeChanged)
    Q_PROPERTY(int shapeCount READ shapeCount NOTIFY shapeCountChanged)

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

    //! Add rect
    Q_INVOKABLE void addRectangle(const QGeoCoordinate &center);

    //! Add circle
    Q_INVOKABLE void addCircle(const QGeoCoordinate &center);

    //! Add triangle
    Q_INVOKABLE void addTriangle(const QGeoCoordinate &center);

    //! Remove shape
    Q_INVOKABLE void removeShape(int iShapeIndex);

    //! Clear
    void clear();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return exclusion area list
    const QVector<Core::BaseShape *> &shapes() const;

    //! Return current shape
    Core::BaseShape *currentShape() const;

    //! Set current shape
    void setCurrentShape(Core::BaseShape *pShape);

    //! Set shapes
    void setShapes(const QVector<Core::BaseShape *> &vShapes);

private:
    //! Add shape
    void addShape(Core::BaseShape *pShape);

    //! Return shape count
    int shapeCount() const;

private:
    //! Shapes
    QVector<Core::BaseShape *> m_vShapes;

    //! Current shape
    Core::BaseShape *m_pCurrentShape = nullptr;

signals:
    //! Current shape changed
    void currentShapeChanged();

    //! Shape count changed
    void shapeCountChanged();
};

#endif // EXCLUSIONAREAMODEL_H
