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
// NOTE: This will change when the RFID login is implemented in the future.
void UserLogin::on_buttonLogin_clicked()
{
	loginFunc();
}

// Main login function
// NOTE: Might add a logout function in the near future
void UserLogin::loginFunc()
{
    // Get the current date and time
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("dd-MM-yy");
	QString time = dateTime.toString("HH:mm");
	QString userID = ui->lineID->text();
	QString name = ui->lineName->text();

	QSqlQuery query,slct;
    // This query just returns the value of which type the user is for use in the next query
	slct.prepare("SELECT * FROM users WHERE UserID='" + userID +"'");
	slct.exec();
	QString type = slct.value(4).toString();
    // This query writes the log into the database
    QString qry = "insert into logbook (ID,Name,Time,Date,Type,Action) values ('"+userID+"', '"+name+"', '"+time+"', '"+date+"', '"+type+"', 'Login')";
	qDebug() << qry;
	query.prepare(qry);
	if (query.exec()){
		QMessageBox::about(this, "Login", "Login Successful.");
		ui->lineID->setText("");
	}
}

// Checks the input for a matching user ID.
// NOTE: Potentially dangerous as any user can find out the ID of another user
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
