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
    void on_lineBookID_textChanged(const QString &arg1);
    void on_lineBookID2_textChanged(const QString &arg1);
    void loadIssuePage();
    void loadReturnPage();
    void loadHomePage();

    void on_actionExit_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainLibraryWindow *ui;
};

#endif // MAINLIBRARYWINDOW_H
