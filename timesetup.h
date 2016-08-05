#ifndef TIMESETUP_H
#define TIMESETUP_H

#include <QDialog>
#include<QDate>
#include"timesetuptrue.h"

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Timesetup *ui;
    TimesetupTrue *time_timeset;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // TIMESETUP_H
