#include "common/headers/dbmanager.h"

dbManager::dbManager(QWidget *parent) : QMainWindow(parent)
{

}

bool dbManager::connOpen(){

    //initialize the Database

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation); //Set default database location
    dbLocation = dbLocation + "/" + dbName;
    db.setDatabaseName(dbLocation); //sets the database name using the database location
    qDebug() << "Database location: " + dbLocation;

    //Check for database connection
    if (!db.open() == true){
        qDebug() << "Failed to connect to Database.";
        return false;
    }
    else{
        qDebug() << "Database Connected.";
        return true;
    }
}

void dbManager::connClose(){
    //close the database
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}
