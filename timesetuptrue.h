#ifndef TIMESETUPTRUE_H
#define TIMESETUPTRUE_H

#include <QDialog>
#include<QTime>
#include<QTimer>
#include<QPainter>

namespace Ui {
class TimesetupTrue;
}

class TimesetupTrue : public QDialog
{
    Q_OBJECT
    
public:
    explicit TimesetupTrue(QWidget *parent = 0);
    ~TimesetupTrue();
    
private slots:
    void on_pushButton_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_timeEdit_timeChanged(const QTime &timed);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &date);

private:
    Ui::TimesetupTrue *ui;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // TIMESETUPTRUE_H
