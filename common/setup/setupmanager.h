#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include <QWidget>

namespace Ui {
class SetupManager;
}

class SetupManager : public QWidget
{
    Q_OBJECT

public:
    explicit SetupManager(QWidget *parent = nullptr);
    ~SetupManager();

private:
    Ui::SetupManager *ui;
};

#endif // SETUPMANAGER_H
