#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QtSql>
#include "library-window/headers/mainlibrarywindow.h"
#include "common/headers/dbmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class LoginForm; }
QT_END_NAMESPACE

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginForm *ui;
    MainLibraryWindow lib;
    dbManager db;
};
#endif // LOGINFORM_H
