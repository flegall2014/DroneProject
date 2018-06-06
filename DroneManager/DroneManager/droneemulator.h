#ifndef DRONEEMULATOR_H
#define DRONEEMULATOR_H

// Application
#include <dronebase.h>
#include <flightsimulator.h>
#include <batterysimulator.h>

class DroneEmulator : public Core::DroneBase
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    DroneEmulator(QObject *pParent=nullptr);

    //! Constructor
    DroneEmulator(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Constructor
    DroneEmulator(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent=nullptr);

    //! Destructor
    virtual ~DroneEmulator();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Take off
    void takeOff();

    //! Fail safe
    void failSafe();

private:
    //! Flight simulator
    Core::FlightSimulator *m_pFlightSimulator = nullptr;

    //! Battery simulator
    Core::BatterySimulator *m_pBatterySimulator = nullptr;

    //! Drone timer
    QTimer m_droneTimer;

public slots:
    //! Position changed
    void onPositionChanged(const QGeoCoordinate &geoCoord, double dHeading);

    //! Battery level changed
    void onBatteryLevelChanged(int iLevel, int iReturn);

signals:
    //! Time out
    void timeOut();
};

#endif // DRONEEMULATOR_H
