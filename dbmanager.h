#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QtSql>
#include <QMainWindow>

class dbManager : public QMainWindow
{
    Q_OBJECT

public:
    dbManager(QWidget *parent = nullptr);

public:
    QSqlDatabase db;
    bool connOpen();
    void connClose();

};

#endif // DBMANAGER_H
