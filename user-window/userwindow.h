#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "common/search/searchwindow.h"
#include "user-window/userlogin.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private slots:
	void on_buttonSearch_clicked();
	void on_actionExit_triggered();
	void on_buttonLogin_clicked();

private:
    Ui::UserWindow *ui;
	searchwindow searchWin;
	UserLogin uLog;
};

#endif // USERWINDOW_H
