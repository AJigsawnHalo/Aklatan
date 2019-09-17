#include "userlogin.h"
#include "ui_userlogin.h"

UserLogin::UserLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
}

UserLogin::~UserLogin()
{
    delete ui;
}

// Closes the window
void UserLogin::on_buttonCancel_clicked()
{
	this->hide();
}


// Initialize the window
void UserLogin::loadUserLogWin()
{
	ui->lineID->setText("");
}

// Logs the user in using the ID and the current time
// This will change when the RFID login is implemented in the future.
void UserLogin::on_buttonLogin_clicked()
{
	loginFunc();
}

void UserLogin::loginFunc()
{
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("dd-MM-yy");
	QString time = dateTime.toString("HH:mm");
	QString userID = ui->lineID->text();
	QString name = ui->lineName->text();
	QSqlQuery query,slct;
	slct.prepare("SELECT * FROM users WHERE UserID='" + userID +"'");
	slct.exec();
	QString type = slct.value(4).toString();
    QString qry = "insert into logbook (ID,Name,Time,Date,Type,Action) values ('"+userID+"', '"+name+"', '"+time+"', '"+date+"', '"+type+"', 'Login')";
	qDebug() << qry;
	query.prepare(qry);
	if (query.exec()){
		QMessageBox::about(this, "Login", "Login Successful.");
		ui->lineID->setText("");
	}
}

void UserLogin::on_lineID_textChanged(const QString &arg1)
{
	QString ID = arg1;
	QSqlQuery query;
	query.prepare("SELECT * FROM USERS WHERE USERID='" + ID + "' ");
	if (query.exec()){
		if (ID != ""){
			while (query.next()){
				QString name = query.value(1).toString();
				ui->lineName->setText(name);
			}
		}
		else {
			ui->lineName->setText("");
		}
	}

}	
