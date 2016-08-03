#ifndef TIMESETUP_H
#define TIMESETUP_H

#include <QDialog>
#include<QDate>

namespace Ui {
class Timesetup;
}

class Timesetup : public QDialog
{
    Q_OBJECT
    
public:
    explicit Timesetup(QWidget *parent = 0);
    ~Timesetup();
    
private slots:
    void funsetuptime();
    void on_dateEdit_dateChanged(const QDate &date);

    void on_timeEdit_timeChanged(const QTime &timed);

    void on_pushButton_clicked();

private:
    Ui::Timesetup *ui;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // TIMESETUP_H
