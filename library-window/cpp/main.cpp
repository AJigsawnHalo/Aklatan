#include "library-window/headers/loginform.h"
#include "common/settings/settingsmanager.h"
#include "common/setup/setupmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Aklatan");
    a.setOrganizationName("Aklatan-project");
    a.setOrganizationDomain("https://github.com/ajigsawnhalo/aklatan");
    SettingsManager setMan;
	QString firstrun = setMan.loadSettings("FirstRun", "Settings", "true").toString(); 
	qDebug() << firstrun;
	if (firstrun == "true"){
		SetupManager setup;
		setup.show();	
		return a.exec();
	}
	else {
		setMan.setConf();
		LoginForm w;
		w.show();
		return a.exec();
	}
}
