#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class searchwindow;
}

class searchwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchwindow(QWidget *parent = nullptr);
    ~searchwindow();

private:
    Ui::searchwindow *ui;
};

#endif // SEARCHWINDOW_H
