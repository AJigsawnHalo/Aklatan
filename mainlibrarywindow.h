#ifndef MAINLIBRARYWINDOW_H
#define MAINLIBRARYWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "dbmanager.h"
namespace Ui {
class MainLibraryWindow;
}

class MainLibraryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainLibraryWindow(QWidget *parent = nullptr);
    ~MainLibraryWindow();

private slots:
    void on_homeIssueButton_clicked();

    void on_issueHomeButton_clicked();

    void on_actionIssue_Book_triggered();

    //void on_actionAdd_Book_triggered();

    void on_returnHomeButton_clicked();

    void on_homeReturnButton_clicked();

    void on_actionReturn_Book_triggered();

private:
    Ui::MainLibraryWindow *ui;
    dbManager db;
};

#endif // MAINLIBRARYWINDOW_H
