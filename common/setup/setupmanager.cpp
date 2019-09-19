#include "setupmanager.h"
#include "ui_setupmanager.h"

SetupManager::SetupManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupManager)
{
    ui->setupUi(this);
	this->setWindowTitle("Aklatan - Setup");
}

SetupManager::~SetupManager()
{
    delete ui;
}

// ###Start Page###

void SetupManager::on_buttonCancel0_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
}

// Go to the Database setup
void SetupManager::on_buttonNext0_clicked()
{
	this->setWindowTitle("Aklatan - Database Setup");
	ui->stackedSetup->setCurrentIndex(1);
	ui->stackedDB->setCurrentIndex(0);
}

// ###Database Setup###

void SetupManager::on_buttonBackdb1_clicked()
{
	this->setWindowTitle("Aklatan - Setup");
	ui->stackedSetup->setCurrentIndex(0);
}

void SetupManager::on_buttonNextdb1_clicked()
{
	QString dbName = ui->linedbName->text();
    setMan.saveSettings("DatabaseName", dbName, "Settings"); // write the database name into the .ini file
    createDB(); // invokes the createDB function to create the database using the database name
	ui->stackedDB->setCurrentIndex(1);
}

void SetupManager::on_buttonCanceldb1_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
}

// Database Setup - Page 2

void SetupManager::on_buttonCanceldb2_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
}

void SetupManager::on_buttonBackdb2_clicked()
{
	ui->stackedDB->setCurrentIndex(0);
}

// creates the database
void SetupManager::createDB()
{
    // Read from the newly created .ini file for the database name
	setMan.loadConf();
	setMan.setConf();
	dbMan.connOpen();

    // Initialize the database
	QSqlQuery admin,books,category,damagedbooks,issued,logbook,users;	
	admin.prepare("CREATE TABLE 'admin' ( 'user-id' INTEGER, 'username' TEXT, 'password' BLOB, PRIMARY KEY('user-id') )");
	books.prepare( "CREATE TABLE 'books' ( 'BookID' INTEGER, 'BookName' BLOB, 'Category' BLOB, 'Author' BLOB, 'Publisher' BLOB, 'Edition' INTEGER, 'PublishingYear' INTEGER, 'Quantity' INTEGER, 'Status' TEXT, PRIMARY KEY('BookID') )");
	category.prepare("CREATE TABLE 'category' ( 'ID' INTEGER, 'Category Name' BLOB )");
	damagedbooks.prepare("CREATE TABLE 'damagedBooks' ( 'BookID' INTEGER, 'BookName' BLOB )");
	issued.prepare("CREATE TABLE 'issued' ( 'BookID' INTEGER, 'BookName' BLOB, 'UserID' INTEGER, 'UserName' BLOB, 'UserType' BLOB, 'DateIssued' BLOB, 'DateDue' BLOB, 'TransactionNum' INTEGER, PRIMARY KEY('TransactionNum') )");
	logbook.prepare("CREATE TABLE `logbook` ( `ID` INTEGER, `Name` BLOB, `Time` BLOB, `Date` BLOB, `Type` TEXT, `Action` TEXT )");
	users.prepare("CREATE TABLE 'users' ( 'UserID' INTEGER, 'UserName' BLOB, 'UserAddress' BLOB, 'UserContactNumber' BLOB, 'UserType' BLOB )");

	admin.exec();
	books.exec();
	category.exec();
	damagedbooks.exec();
	issued.exec();
	logbook.exec();
	users.exec();
}

// Creates the admin account
void SetupManager::on_buttonNextdb2_clicked()
{
	QString uName,pass,passCheck;
	uName = ui->lineUsername->text();
	pass = ui->linePassword->text();
	passCheck = ui->linePassCheck->text();

	QSqlQuery query;
	query.prepare("INSERT INTO admin (username,password) values ('"+uName+"', '"+pass+"')");

	if (pass == passCheck){
		query.exec();
		ui->stackedSetup->setCurrentIndex(2);
	}
	else {
        QMessageBox::about(this, "Password Error", "Passwords do not match.");
		ui->linePassword->setText("");
		ui->linePassCheck->setText("");
        this->setWindowTitle("Aklatan - Settings Setup");
	}
}

// ### Settings Page###

void SetupManager::on_buttonCancelSettings_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quit", "Would You like to exit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

        QApplication::quit();
      }
}

void SetupManager::on_buttonBackSettings_clicked()
{
	ui->stackedSetup->setCurrentIndex(1);
}

// Writes the given values into the .ini file
void SetupManager::on_buttonNextSettings_clicked()
{
	QString due,late,damaged;

	due = ui->lineDue->text();
	late = ui->lineLate->text();
	damaged = ui->lineDamaged->text();

	QString group = "Settings";
	QString key[3] = {"DaysDue", "LatePenalty", "DamagePenalty"};
	QString conf[3] = {due, late, damaged};
	for (int i = 0; i < 3; i++){
       QString keyPass, confPass, defPass;
       keyPass = key[i];
       confPass = conf[i];
       setMan.saveSettings(keyPass, confPass, group);
	}
	ui->stackedSetup->setCurrentIndex(3);
    this->setWindowTitle("Aklatan - Setup Finished");
}

void SetupManager::on_buttonFinish_clicked()
{
    // Writes a value of false for FirstRun indicating the setup function has been completed
    setMan.saveSettings("FirstRun", "False", "Settings");

	this->hide();

    // Load the admin login window
	setMan.loadConf();
	setMan.setConf();
	dbMan.connClose();
	login.show();
	login.dbCheck();
}
