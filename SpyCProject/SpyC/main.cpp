// Qt
#include <QApplication>
#include <QSettings>

// Application
#include "spyc.h"

void createSettings()
{
    QCoreApplication::setOrganizationName("TOSA");
    QCoreApplication::setOrganizationDomain("DRONE");
    QCoreApplication::setApplicationName("SpyC");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create settings
    createSettings();

    // Build SpyC instance
    SpyC *pSpyC = SpyC::instance();

    // Startup
    pSpyC->startup();

    // Event loop
    int res = app.exec();

    // Shutdown
    pSpyC->shutdown();

    // Release
    delete pSpyC;

    return res;
}
