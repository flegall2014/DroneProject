#ifndef DRONE_H
#define DRONE_H

// Qt
#include <QObject>
#include <QGeoCoordinate>
#include <QGeoPath>

// Application
#include "settingcontroller.h"
#include <waypoint.h>
#include <dronebase.h>
class WayPointModel;
class AlertModel;
class GalleryModel;
class ExclusionAreaModel;

class Drone : public Core::DroneBase
{
    Q_OBJECT

    // State, edit mode, work mode and global status
    Q_PROPERTY(QString flightStatusText READ flightStatusText NOTIFY flightStatusChanged)
    Q_PROPERTY(int workMode READ workMode WRITE setWorkMode NOTIFY workModeChanged)
    Q_PROPERTY(int defaultWorkMode READ defaultWorkMode NOTIFY defaultWorkModeChanged)
    Q_PROPERTY(int currentExclusionShape READ currentExclusionShape WRITE setCurrentExclusionShape NOTIFY currentExclusionShapeChanged)
    Q_PROPERTY(int globalStatus READ globalStatus NOTIFY globalStatusChanged)

    // Battery status
    Q_PROPERTY(int batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)

    // Mission plan model and safety model
    Q_PROPERTY(WayPointModel *missionPlanModel READ missionPlanModel NOTIFY missionPlanModelChanged)
    Q_PROPERTY(WayPointModel *safetyModel READ safetyModel NOTIFY safetyModelChanged)
    Q_PROPERTY(WayPointModel *landingPlanModel READ landingPlanModel NOTIFY landingPlanModelChanged)
    Q_PROPERTY(ExclusionAreaModel *exclusionAreaModel READ exclusionAreaModel NOTIFY exclusionAreaModelChanged)
    Q_PROPERTY(AlertModel *alertModel READ alertModel NOTIFY alertModelChanged)
    Q_PROPERTY(GalleryModel *galleryModel READ galleryModel NOTIFY galleryModelChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Drone(QObject *pParent=nullptr);

    //! Constructor
    Drone(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Constructor
    Drone(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent=nullptr);

    //! Destructor
    virtual ~Drone();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return battery status
    int batteryStatus() const;

    //! Set battery status
    void setBatteryStatus(int iBatteryStatus);

    //! Set global status
    void setGlobalStatus(const SpyCore::Status &eStatus);

    //! Return global status
    int globalStatus() const;

    //! Return flight status text
    QString flightStatusText() const;

    //! Return work mode
    int workMode() const;

    //! Set work mode
    void setWorkMode(int iMode);

    //! Return default work mode
    int defaultWorkMode() const;

    //! Return current exclusion shape
    int currentExclusionShape() const;

    //! Set current exclusion shape
    void setCurrentExclusionShape(int iExclusionShape);

    //! Set default work mode
    Q_INVOKABLE void setDefaultWorkMode();

    //! Return mission plan model
    WayPointModel *missionPlanModel() const;

    //! Set mission plan
    virtual void setMissionPlan(const WayPointList &missionPlan);

    //! Return safety model
    WayPointModel *safetyModel() const;

    //! Set safety
    virtual void setSafetyPlan(const QGeoPath &geoPath);

    //! Return landing plan model
    WayPointModel *landingPlanModel() const;

    //! Set landing plan
    virtual void setLandingPlan(const WayPointList &landingPlan);

    //! Return alert model
    AlertModel *alertModel() const;

    //! Gallery model
    GalleryModel *galleryModel() const;

    //! Exclusion area model
    ExclusionAreaModel *exclusionAreaModel() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Initialize
    void initialize(const QMap<int, QVariant> &mSettings);

    //! Clear mission plan
    Q_INVOKABLE virtual void clearMissionPlan();

    //! Clear safety
    Q_INVOKABLE virtual void clearSafetyPlan();

    //! Clear landing plan
    Q_INVOKABLE virtual void clearLandingPlan();

    //! Add coordinate to mission plan
    Q_INVOKABLE void addCoordinateToMissionPlan(const QGeoCoordinate &geoCoordinate);

    //! Add coordinate to safety
    Q_INVOKABLE void addCoordinateToSafety(const QGeoCoordinate &geoCoordinate);

    //! Add coordinate to landing plan
    Q_INVOKABLE void addCoordinateToLandingPlan(const QGeoCoordinate &geoCoordinate);

    //! Set mission plan point position
    Q_INVOKABLE void setMissionPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Set safety point position
    Q_INVOKABLE void setSafetyPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Set landing plan point position
    Q_INVOKABLE void setLandingPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Remove coordinate from safety at index
    Q_INVOKABLE void removeCoordinateFromSafetyPlanAtIndex(int iPointIndex);

    //! Remove coordinate from mission plan at index
    Q_INVOKABLE void removeCoordinateFromMissionPlanAtIndex(int iPointIndex);

    //! Remove coordinate from landing plan at index
    Q_INVOKABLE void removeCoordinateFromLandingPlanAtIndex(int iPointIndex);

    //! Clear exclusion areas
    Q_INVOKABLE void clearExclusionAreas();

    //! Close safety
    void closeSafety();

private:
    //! Update battery status
    void updateBatteryStatus();

private:
    //! Settings
    QMap<int, QVariant> m_mSettings;

    //! Battery status
    SpyCore::Status m_eBatteryStatus = SpyCore::NOMINAL;

    //! Work mode
    SpyCore::WorkMode m_eWorkMode = SpyCore::PAYLOAD_EDIT;

    //! Default work mode
    SpyCore::WorkMode m_eDefaultWorkMode = SpyCore::PAYLOAD_EDIT;

    //! Current exclusion shape
    SpyCore::ExclusionShape m_eExclusionShape = SpyCore::CIRCLE;

    //! Global status
    SpyCore::Status m_eGlobalStatus = SpyCore::NOMINAL;

    //! Mission plan model
    WayPointModel *m_pMissionPlanModel = nullptr;

    //! Safety model
    WayPointModel *m_pSafetyModel = nullptr;

    //! Landing plan model
    WayPointModel *m_pLandingPlanModel = nullptr;

    //! Alert model
    AlertModel *m_pAlertModel = nullptr;

    //! Gallery model
    GalleryModel *m_pGalleryModel = nullptr;

    //! Exclusion area model
    ExclusionAreaModel *m_pExclusionAreaModel = nullptr;

public slots:
    //! Global status changed
    void onGlobalStatusChanged();

signals:
    //! UID changed
    void uidChanged();

    //! Video url changed
    void videoUrlChanged();

    //! Global status changed
    void globalStatusChanged();

    //! Mode changed
    void flightStatusChanged();

    //! Battery level changed
    void batteryLevelChanged();

    //! Return level changed
    void returnLevelChanged();

    //! Battery status changed
    void batteryStatusChanged();

    //! Position changed
    void positionChanged();

    //! Heading changed
    void headingChanged();

    //! Position status changed
    void positionStatusChanged();

    //! Mission plan model changed
    void missionPlanModelChanged();

    //! Safety model changed
    void safetyModelChanged();

    //! Landing plan model changed
    void landingPlanModelChanged();

    //! Exclusion area model changed
    void exclusionAreaModelChanged();

    //! Alert model changed
    void alertModelChanged();

    //! Gallery model changed
    void galleryModelChanged();

    //! Edit mode changed
    void workModeChanged();

    //! Default work mode changed
    void defaultWorkModeChanged();

    //! Current exclusion shape changed
    void currentExclusionShapeChanged();
};

#endif // DRONE_H
