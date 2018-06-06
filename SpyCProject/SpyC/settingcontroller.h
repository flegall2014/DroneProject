#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

// Qt
#include <QObject>
#include <QLocale>
class QTextToSpeech;

// Application
#include <spycore.h>
class MasterController;
class Translator;

class SettingController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString army READ army WRITE setArmy NOTIFY fullMissionNameChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY fullMissionNameChanged)
    Q_PROPERTY(QString mission READ mission WRITE setMission NOTIFY fullMissionNameChanged)
    Q_PROPERTY(QString operatorName READ operatorName WRITE setOperatorName NOTIFY fullMissionNameChanged)
    Q_PROPERTY(QString fullMissionName READ fullMissionName NOTIFY fullMissionNameChanged)
    Q_PROPERTY(int language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString mapPath READ mapPath WRITE setMapPath NOTIFY mapPathChanged)
    Q_PROPERTY(QString missionPath READ missionPath WRITE setMissionPath NOTIFY missionPathChanged)
    Q_PROPERTY(QString logPath READ logPath WRITE setLogPath NOTIFY logPathChanged)
    Q_PROPERTY(QString alertPath READ alertPath WRITE setAlertPath NOTIFY alertPathChanged)
    Q_PROPERTY(QString galleryPath READ galleryPath WRITE setGalleryPath NOTIFY galleryPathChanged)
    Q_PROPERTY(int hand READ hand WRITE setHand NOTIFY handChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SettingController(QObject *pParent=nullptr);

    //! Destructor
    ~SettingController();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs);

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Return a gallery path given a drone UID
    Q_INVOKABLE QString snapShotPath(const QString &sDroneUID) const;

    //! Say
    Q_INVOKABLE void say(const QString &sSpeech);

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return army
    const QString &army() const;

    //! Set army
    void setArmy(const QString &sArmy);

    //! Return unit
    const QString &unit() const;

    //! Set unit
    void setUnit(const QString &sUnit);

    //! Return mission
    const QString &mission() const;

    //! Set mission
    void setMission(const QString &sMission);

    //! Return operator
    const QString &operatorName() const;

    //! Set operator
    void setOperatorName(const QString &sName);

    //! Return full mission name
    QString fullMissionName() const;

    //! Return language
    int language() const;

    //! Set language
    void setLanguage(int iLanguage);

    //! Return map path
    const QString &mapPath() const;

    //! Set map path
    void setMapPath(const QString &sMapPath);

    //! Return mission path
    const QString &missionPath() const;

    //! Set mission path
    void setMissionPath(const QString &sMissionPath);

    //! Return log path
    const QString &logPath() const;

    //! Set log path
    void setLogPath(const QString &sLogPath);

    //! Return alert path
    const QString &alertPath() const;

    //! Set alert path
    void setAlertPath(const QString &sAlertPath);

    //! Return gallery path
    const QString &galleryPath() const;

    //! Set gallery path
    void setGalleryPath(const QString &sGalleryPath);

    //! Return hand
    int hand() const;

    //! Set hand
    void setHand(int iHand);

    //! Return all settings
    QMap<int, QVariant> allSettings();

    //! Return translator
    Translator *translator() const;

private:
    //! Load settings
    void loadSettings();

    //! Save settings
    void saveSettings();

    //! Create dir
    void createDir(const QString &sDirPath);

    //! Setup translator and speech
    void setupTranslatorAndSpeech();

private:
    //! Master controller
    MasterController *m_pMasterController = nullptr;

    //! Army
    QString m_sArmy = "";

    //! Unit
    QString m_sUnit = "";

    //! Mission
    QString m_sMission = "";

    //! Operator
    QString m_sOperator = "";

    //! Language string
    SpyCore::Language m_eLanguage = SpyCore::ENGLISH;

    //! Map path
    QString m_sMapPath = "";

    //! Mission path
    QString m_sMissionPath = "";

    //! Log path
    QString m_sLogPath = "";

    //! Alert path
    QString m_sAlertPath = "";

    //! Gallery path
    QString m_sGalleryPath = "";

    //! UI orientation
    SpyCore::UIOrientation m_eHand = SpyCore::RIGHT_HAND;

    //! Translator
    Translator *m_pTranslator = nullptr;

    //! Text to speech
    QTextToSpeech *m_pSpeech = nullptr;

public slots:
    //! Language changed
    void onLanguageChanged();

signals:
    //! Full mission name changed
    void fullMissionNameChanged();

    //! Language changed
    void languageChanged();

    //! Map path changed
    void mapPathChanged();

    //! Mission path changed
    void missionPathChanged();

    //! Log path changed
    void logPathChanged();

    //! Alert path changed
    void alertPathChanged();

    //! Gallery path changed
    void galleryPathChanged();

    //! Hand changed
    void handChanged();
};

#endif // SETTINGCONTROLLER_H
