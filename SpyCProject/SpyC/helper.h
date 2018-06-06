#ifndef HELPER_H
#define HELPER_H

// Qt
#include <QDir>
#include <QObject>

class Helper : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Helper(QObject *pParent=nullptr);

    //! Destructor
    ~Helper();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Return application dir
    Q_INVOKABLE QDir applicationDir();

    //! Return i18n dir
    Q_INVOKABLE QDir i18nDir();

    //! To local file
    Q_INVOKABLE QString toLocalFile(const QString &sInput);

    //! From local file
    Q_INVOKABLE QString fromLocalFile(const QString &sInput);
};

#endif // HELPER_H
