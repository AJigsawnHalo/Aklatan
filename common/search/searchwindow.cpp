#include "searchwindow.h"
#include "ui_searchwindow.h"

searchwindow::searchwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchwindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aklatan - Search");
	loadWindow();
}

searchwindow::~searchwindow()
{
    delete ui;
}

// Initialize the search window
void searchwindow::loadWindow()
{
	QSqlQueryModel * model = new QSqlQueryModel;
	ui->lineSearch->setText("Type search here...");
	model->clear();
	ui->tableSearch->setModel(model);
}

// Main search function
void searchwindow::searchFunc()
{
	QSqlQuery query;
	QSqlQueryModel * model = new QSqlQueryModel;

    // Sets the search terms for the query
	QString searchQ = ui->lineSearch->text();

    // Sets the search parameters selected by the user
	QString searchParam;
	int i = ui->comboBox->currentIndex();
	switch (i){
		case 1:
			searchParam = "Category";
			break;
		case 2:
			searchParam = "Author";
			break;
		case 3:
			searchParam = "Publisher";
			break;
		case 4:
			searchParam = "BookID";
			break;
		default:
			searchParam = "BookName";
			break;
	}

    if (searchQ == "Type search here..."){ // checks if the search bar still has the default text
		QMessageBox::about(this, "", "Please enter a search query");
	}
    else{ query.prepare("SELECT * FROM BOOKS WHERE " + searchParam + " LIKE '" + searchQ + "%'"); // query the database for the search term using the search parameters
		if (query.exec()){
			int rowNumber = 0;
			if (query.last()){
				rowNumber = query.at() + 1;
				query.first();
				query.previous();
			}
			if (rowNumber != 0){
				model->setQuery(query);
				ui->tableSearch->setModel(model);
			}
			else {
				QMessageBox::about(this, "None Found", "No books matching search found.");
				model->clear();
				ui->tableSearch->setModel(model);
			}
		}
	}
}

void searchwindow::on_buttonSearch_clicked()
{
	searchFunc();
}

void searchwindow::on_cancelButton_clicked()
{
	this->hide();
}
