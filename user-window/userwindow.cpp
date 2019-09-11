#include "userwindow.h"
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

void UserWindow::on_buttonSearch_clicked()
{
	searchWin.show();
	searchWin.loadWindow();
}

void UserWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Quit", "Would You like to exit?", QMessageBox::Yes|QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			this->hide();
		}
}

void UserWindow::on_buttonLogin_clicked()
{
	uLog.show();
}
