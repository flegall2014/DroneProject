#ifndef QMLHELPER_H
#define QMLHELPER_H

// Qt
#include <QDir>
#include <QObject>

// Application
#include "spyclib_global.h"

namespace Core {
class SPYCLIBSHARED_EXPORT QMLHelper : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    QMLHelper(QObject *pParent=nullptr);

    //! Destructor
    ~QMLHelper();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! To local file
    Q_INVOKABLE QString toLocalFile(const QString &sInput);

    //! From local file
    Q_INVOKABLE QString fromLocalFile(const QString &sInput);
};
}

#endif // QMLHELPER_H
