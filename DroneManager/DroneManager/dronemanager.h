#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

// Qt
#include <QObject>
#include <QVector>
#include <QHash>
#include <QTimer>

// Application
#include <spycore.h>
namespace Core {
    class FlightSimulator;
    class BatterySimulator;
    class TCPServer;
}
class DroneEmulator;

namespace Model {
class DroneManager : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    DroneManager(QObject *pParent=nullptr);

    //! Destructor
    ~DroneManager();

    //! Send message
    void sendMessage(const QString &sMessage);

private:
    //! Get drone by UID
    DroneEmulator *getDrone(const QString &sDroneUID) const;

private:
    //! Drones
    QVector<DroneEmulator *> m_vDrones;

    //! Flight simulator
    QHash<QString, Core::FlightSimulator *> m_vFlightSimulators;

    //! Flight simulator
    QHash<QString, Core::BatterySimulator *> m_vBatterySimulators;

    //! TCPServer
    Core::TCPServer *m_pServer = nullptr;

public slots:
    //! Drone position time out
    void onPositionTimeOut();

    //! Drone battery time out
    void onBatteryTimeOut();

    //! Return time out
    void onReturnTimeOut();

    //! Take off drone
    void onTakeOffRequest(const QString &DroneUID);

    //! Fail safe
    void onFailSafeRequest(const QString &DroneUID);

    //! Mission plan changed
    void onMissionPlanChanged();

    //! Safety plan changed
    void onSafetyPlanChanged();

    //! Landing plan changed
    void onLandingPlanChanged();

    //! Drone error
    void onDroneError(const SpyCore::DroneError &eDroneError, const QString &sDroneUID);

    //! New connection from ground station
    void onNewConnectionFromGroundStation();

    //! Process incoming message
    void onIncomingMessage(const QString &sIcominMessage);
};
}

#endif // DRONEMANAGER_H
