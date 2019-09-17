#ifndef MAINLIBRARYWINDOW_H
#define MAINLIBRARYWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlRecord>
#include "common/dbmanager/dbmanager.h"
#include "common/settings/settingsmanager.h"
#include "common/search/searchwindow.h"
#include "user-window/userwindow/userwindow.h"
#include "library-window/logbook/logbook.h"

namespace Ui {
class MainLibraryWindow;
}

class MainLibraryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainLibraryWindow(QWidget *parent = nullptr);
    ~MainLibraryWindow();
    void loadStatus();


private slots:
    void on_lineBookID_textChanged(const QString &arg1);
    void on_lineBookID2_textChanged(const QString &arg1);
    void loadIssuePage();
    void loadReturnPage();
    void loadHomePage();
    void loadReportPage(const int &arg);
    void loadRegisterPage(const int &arg);
    void passRegisterBook();
    void passRegisterUser();
    void passReportLoadAll();
    void passReportLoadIss();
    void on_actionExit_triggered();
    void on_pushButton_clicked();
    void on_checkBox_toggled(bool checked);
    void on_refreshButton_2_clicked();
    void on_refreshButton_clicked();
    void on_lineUserID_textChanged(const QString &arg1);
    void on_issueButton_clicked();
    void on_returnButton_clicked();
    void on_lineUserID2_textChanged(const QString &arg1);
    void on_spinQuantity_valueChanged(int arg1);
    void on_regRegButton_clicked();
    void on_regClear_clicked();
	void on_actionLog_Book_triggered();
	void on_actionSearch_triggered();
    void on_actionPreferences_triggered();
	void on_actionOpen_User_Window_triggered();

private:
    Ui::MainLibraryWindow *ui;
    SettingsManager setMan;
	searchwindow searchWin;
	UserWindow userWin;
	LogBook lB;
};

#endif // MAINLIBRARYWINDOW_H
