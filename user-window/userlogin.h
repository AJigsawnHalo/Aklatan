#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class UserLogin;
}

class UserLogin : public QWidget
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = nullptr);
    ~UserLogin();
	void loadUserLogWin();

private slots:
	void on_buttonCancel_clicked();
	void on_buttonLogin_clicked();
	void loginFunc();
	void on_lineID_textChanged(const QString &arg1);

private:
    Ui::UserLogin *ui;
};

#endif // USERLOGIN_H
