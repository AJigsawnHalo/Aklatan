#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QMessageBox>

namespace Ui {
class LogBook;
}

class LogBook : public QWidget
{
    Q_OBJECT

public:
    explicit LogBook(QWidget *parent = nullptr);
    ~LogBook();
	void loadWindow();

private slots:
	void loadLogBook();
	void on_buttonClose_clicked();
	void on_buttonLoad_clicked();
private:
    Ui::LogBook *ui;
};

#endif // LOGBOOK_H
