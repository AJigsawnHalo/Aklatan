#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <QWidget>

namespace Ui {
class LogBook;
}

class LogBook : public QWidget
{
    Q_OBJECT

public:
    explicit LogBook(QWidget *parent = nullptr);
    ~LogBook();

private:
    Ui::LogBook *ui;
};

#endif // LOGBOOK_H
