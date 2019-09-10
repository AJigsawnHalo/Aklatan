#include "searchwindow.h"
#include "ui_searchwindow.h"

searchwindow::searchwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchwindow)
{
    ui->setupUi(this);
	loadWindow();
}

searchwindow::~searchwindow()
{
    delete ui;
}

void searchwindow::loadWindow()
{
	QSqlQueryModel * model = new QSqlQueryModel;
	ui->lineSearch->setText("Type search here...");
	model->clear();
	ui->tableSearch->setModel(model);
}

void searchwindow::searchFunc()
{
	QSqlQuery query;
	QSqlQueryModel * model = new QSqlQueryModel;
	QString searchQ = ui->lineSearch->text();
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

	if (searchQ == "Type search here..."){
		QMessageBox::about(this, "", "Please enter a search query");
	}
	else{ query.prepare("SELECT * FROM BOOKS WHERE " + searchParam + " LIKE '" + searchQ + "%'");
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
