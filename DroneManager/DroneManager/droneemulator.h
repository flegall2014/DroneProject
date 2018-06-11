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

    //! Go home
    void goHome();

    //! Fail safe
    void failSafe();

private:
    //! Flight simulator
    Core::FlightSimulator *m_pFlightSimulator = nullptr;

    //! Battery simulator
    Core::BatterySimulator *m_pBatterySimulator = nullptr;

    //! Position timer
    QTimer m_positionTimer;

    //! Battery timer
    QTimer m_batteryTimer;

    //! Return timer
    QTimer m_returnTimer;

public slots:
    //! Position changed
    void onPositionChanged(const QGeoCoordinate &geoCoord, double dHeading);

    //! Battery level changed
    void onBatteryLevelChanged(int iLevel, int iReturn);

signals:
    //! Position time out
    void positionTimeOut();

    //! Battery time out
    void batteryTimeOut();

    //! Return time out
    void returnTimeOut();
};

#endif // DRONEEMULATOR_H
