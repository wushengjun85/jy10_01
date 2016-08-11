#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"work.h"

#include"timesetup.h"
#include"findlook.h"
#include"signalcan.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_pushButton_timesetup_clicked();//设置按钮
    void on_ptn_back_clicked();//返回按钮

    void diplaytime();

    void on_pushButton_timesetup_2_clicked();

    void on_pushButton_timesetup_3_clicked();

private:
    Ui::Widget *ui;
    Work *work;
    Timesetup *timeObj;
    FindLook  *findlook;

    //线程
    SignalCan *mycan;



protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
