#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "library-window/loginform/loginform.h"
#include "common/dbmanager/dbmanager.h"
#include "common/settings/settingsmanager.h"

namespace Ui {
class SetupManager;
}

class SetupManager : public QWidget
{
    Q_OBJECT

public:
    explicit SetupManager(QWidget *parent = nullptr);
    ~SetupManager();

private slots:
	void on_buttonCancel0_clicked();
	void on_buttonNext0_clicked();
	
	// Database Setup - Page 1
	void on_buttonBackdb1_clicked();
	void on_buttonNextdb1_clicked();
	void on_buttonCanceldb1_clicked();
	void createDB();
	// Database Setup - Page 2
	void on_buttonBackdb2_clicked();
	void on_buttonNextdb2_clicked();
	void on_buttonCanceldb2_clicked();
	// Settings Setup
	void on_buttonBackSettings_clicked();
	void on_buttonNextSettings_clicked();
	void on_buttonCancelSettings_clicked();
	// Final Page
	void on_buttonFinish_clicked();

private:
    Ui::SetupManager *ui;
	LoginForm login;
	SettingsManager setMan;
	dbManager dbMan;
};

#endif // SETUPMANAGER_H
