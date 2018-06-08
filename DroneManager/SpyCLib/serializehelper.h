#ifndef SERIALIZEHELPER_H
#define SERIALIZEHELPER_H

// Application
#include "dronebase.h"
#include "waypoint.h"
#include <cxmlnode.h>
#include "spyclib_global.h"

namespace Core {
class SPYCLIBSHARED_EXPORT SerializeHelper
{
public:
    //! Serialize drone error
    static QString serializeDroneError(const SpyCore::DroneError &eDroneError, const QString &sDroneUID);

    //! Serialize drone error
    static void deSerializeDroneError(const QString &sMessage, SpyCore::DroneError &eDroneError, QString &sDroneUID);

    //! Serialize take off request
    static QString serializeTakeOffRequest(const QString &sDroneUID);

    //! Deserialize take off request
    static void deserializeTakeOffRequest(const QString &sMessage, QString &sDroneUID);

    //! Serialize fail safe
    static QString serializeFailSafeRequest(const QString &sDroneUID);

    //! Deserialize fail safe request
    static void deserializeFailSafeRequest(const QString &sMessage, QString &sDroneUID);

    //! Return message type
    static QString messageType(const QString &sMessage);

    //! Drone uid
    static QString droneUID(const QString &sMessage);
};
}

#endif // SERIALIZEHELPER_H
