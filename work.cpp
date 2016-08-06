#include "work.h"
#include "ui_work.h"


#include<QPainter>
#include<QString>
#include<QTime>
#include<QTimer>

Work::Work(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Work)
{
    ui->setupUi(this);

    findlokk_work = new FindLook();//初始化查询对象

    time_work = new Timesetup();//初始化设置对象


    resize(1024,600);
    Work::move(0,0);//回到原来主窗口的位置
   // setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮


    QTimer *dialogtime = new QTimer(this);
    connect(dialogtime, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新

    dialogtime->start(500);
}

Work::~Work()
{
    delete ui;
}

void Work::on_pushButton_clicked()
{
    this->close();
}


void Work::paintEvent(QPaintEvent *event)
{
    QPainter dp(this);
    QPixmap dppix;
    dppix.load("./imagejy/work.bmp");
    dp.drawPixmap(0,0,1024,600,dppix);




    /**************************************************************************************************************/
    //显示时间 。2016.7.12
        QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
        QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");

        ui->lcdNumber_2->display(dateStr1);
        ui->lcdNumber->display(timeStr1);
    /**************************************************************************************************************/

}

void Work::on_pushButton_4_clicked()//查询按钮
{
    this->close();
    findlokk_work->show();
    findlokk_work->exec();
    this->show();
}

void Work::on_pushButton_2_clicked()// 设置按钮
{
    this->close();
    time_work->show();
    time_work->exec();
    this->close();
}
