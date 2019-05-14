#include "loginform.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm w;
    w.show();
    return a.exec();
}
