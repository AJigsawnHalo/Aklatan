#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlRecord>
#include <QDialog>
#include <QMessageBox>


namespace Ui {
class searchwindow;
}

class searchwindow : public QMainWindow
{
    Q_OBJECT

public:
	void loadWindow();
    explicit searchwindow(QWidget *parent = nullptr);
    ~searchwindow();

private slots:
	void searchFunc();
	void on_buttonSearch_clicked();
	void on_cancelButton_clicked();
private:
    Ui::searchwindow *ui;
};

#endif // SEARCHWINDOW_H
