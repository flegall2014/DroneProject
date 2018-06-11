#ifndef HELPER_H
#define HELPER_H

// Qt
#include <QDir>

// Application
#include "spyclib_global.h"

namespace Core {
class SPYCLIBSHARED_EXPORT Helper
{
public:
    //! Save input string to file
    static bool save(const QString &sInputString, const QString &sFilePath);

    //! Load input file to string
    static bool load(const QString &sFilePath, QString &sOutputString);

    //! Return i18n dir
    static QDir i18nDir();

    //! Return application dir
    static QDir applicationDir();
};
}

#endif // HELPER_H
