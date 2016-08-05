#ifndef WORK_H
#define WORK_H

#include <QDialog>
#include"findlook.h"
#include"timesetup.h"

namespace Ui {
class Work;
}

class Work : public QDialog
{
    Q_OBJECT
    
public:
    explicit Work(QWidget *parent = 0);
    ~Work();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Work *ui;
    FindLook *findlokk_work;
    Timesetup *time_work;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WORK_H
