#include "user-window/userwindow/userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}

// Open the search window
void UserWindow::on_buttonSearch_clicked()
{
	searchWin.show();
	searchWin.loadWindow();
}

// Exits the User Window
// NOTE: Add a way to open the Admin Window from the User Window
void UserWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Quit", "Would You like to exit?", QMessageBox::Yes|QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			QApplication::quit();
		}
}

// Open the User Login window
void UserWindow::on_buttonLogin_clicked()
{
	uLog.show();
}
