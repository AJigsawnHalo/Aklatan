#include "logbook.h"
#include "ui_logbook.h"

LogBook::LogBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Aklatan - Logbook");
}

LogBook::~LogBook()
{
    delete ui;
}

// load the logbook for the current date
void LogBook::loadWindow()
{
	QDate today = QDate::currentDate();
	ui->dateEdit->setDate(today);
	QString date = today.toString("dd-MM-yy");

	loadLogBook();
}

// load the log for the selected date
void LogBook::loadLogBook()
{
	QString date = ui->dateEdit->text();
	QSqlQuery query;
	QSqlQueryModel * model = new QSqlQueryModel();
	query.prepare("SELECT * FROM logbook WHERE Date='" + date + "'");
	query.exec();

	if (query.exec()){
        // Check if there are logs for the given date
		int rowNumber = 0;
		if (query.last()){
			rowNumber = query.at() + 1;
			query.first();
			query.previous();
		}
		if (rowNumber != 0){
			model->setQuery(query);
			ui->tableLogBook->setModel(model);
			ui->tableLogBook->repaint();
		}
		else {
			QMessageBox::about(this, "None Found", "No records found.");
		}

	}

}

void LogBook::on_buttonClose_clicked()
{
	this->hide();
}

void LogBook::on_buttonLoad_clicked()
{
	loadLogBook();
}

