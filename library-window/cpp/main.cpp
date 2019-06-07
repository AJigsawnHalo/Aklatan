#include "library-window/headers/loginform.h"
#include "common/headers/dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm w;
    a.setApplicationName("Aklatan");
    a.setOrganizationName("Aklatan-project");
    a.setOrganizationDomain("https://github.com/ajigsawnhalo/aklatan");
    w.show();
    return a.exec();
}
