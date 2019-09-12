#include "library-window/headers/loginform.h"
#include "common/settings/settingsmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Aklatan");
    a.setOrganizationName("Aklatan-project");
    a.setOrganizationDomain("https://github.com/ajigsawnhalo/aklatan");
    SettingsManager setMan;
    setMan.setConf();
    LoginForm w;
    w.show();
    return a.exec();
}
