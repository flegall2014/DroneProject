#ifndef ISERVICE_H
#define ISERVICE_H

// Qt
#include <QStringList>

class IService
{
public:
    virtual bool startup(const QStringList &lArgs=QStringList()) = 0;
    virtual void shutdown() = 0;
    virtual ~IService() {
    }
};

#endif // ISERVICE_H
