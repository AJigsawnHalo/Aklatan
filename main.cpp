#include "user-window/userwindow/userwindow.h"
#include "library-window/loginform/loginform.h"
#include "common/settings/settingsmanager.h"
#include "common/setup/setupmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Aklatan");
    a.setOrganizationName("Aklatan-project");
    a.setOrganizationDomain("https://github.com/ajigsawnhalo/aklatan");
    // Read from the .ini file for a setting called FirstRun
    // This also returns a default value of 'true' if there is no .ini file found
    SettingsManager setMan;
	QString firstrun = setMan.loadSettings("FirstRun", "Settings", "true").toString(); 
	qDebug() << firstrun;

    // If the value returned is "true", run the setup
	if (firstrun == "true"){
		SetupManager setup;
		setup.show();	
		return a.exec();
	}

	// If the value returned is "User", open the User Window as default.
	else if (firstrun == "User"){
		UserWindow u;
		u.show();
		return a.exec();
	}

    // Else, run the admin login
	else {
		setMan.setConf();
		LoginForm w;
		w.show();
		w.dbCheck();
		return a.exec();
	}
}
