#include "timesetup.h"
#include "ui_timesetup.h"
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QString>


Timesetup::Timesetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timesetup)
{
    ui->setupUi(this);

    Timesetup::move(0,0);//回到原来主窗口的位置
    //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

    time_timeset = new TimesetupTrue();


    QTimer *tm = new QTimer(this);
    tm->start(500);
}

Timesetup::~Timesetup()
{
    delete ui;
}


void Timesetup::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./imagejy/setup.bmp");
    painter.drawPixmap(0,0,1024,600,pix);
}

void Timesetup::on_pushButton_clicked()//返回按钮
{
    this->close();
}

void Timesetup::on_pushButton_2_clicked() //时间设置界面按钮
{
    this->close();
    time_timeset->show();
    time_timeset->exec();
    this->show();
}
