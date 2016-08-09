#include "timesetup.h"
#include "ui_timesetup.h"
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QString>


uint  tuoliguntong_zs = 850; //脱离滚筒转速
uint fenliguntong_zs = 680;//分离滚筒
uint fj_zs = 1180;//风机
uint ftq_zs = 350;//复脱器
uint syq_zs = 110; //升运器
uint qsq_zs = 110; //切碎器
uint gq_zs = 110;//过桥转速

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

void Timesetup::on_pushButton_5_clicked()//脱粒滚筒转速 - 号
{
    tuoliguntong_zs--;
    ui->label->setText(QString::number(tuoliguntong_zs,10));
}

void Timesetup::on_pushButton_4_clicked()//脱粒滚筒转速 + 号
{
    tuoliguntong_zs++;
    ui->label->setText(QString::number(tuoliguntong_zs,10));
}

void Timesetup::on_pushButton_7_clicked()//切碎器转速 - 号
{
    qsq_zs--;
    ui->label_2->setText(QString::number(qsq_zs,10));
}

void Timesetup::on_pushButton_6_clicked()//切碎器转速 + 号
{
    qsq_zs++;
    ui->label_2->setText(QString::number(qsq_zs,10));
}

void Timesetup::on_pushButton_9_clicked()//升运器堵塞转速 -号按钮
{
    syq_zs++;
    ui->label_3->setText(QString::number(syq_zs,10));
}



void Timesetup::on_pushButton_11_clicked()//升运器堵塞转速 +号按钮
{
    syq_zs
            --;
    ui->label_3->setText(QString::number(syq_zs,10));
}

void Timesetup::on_pushButton_8_clicked() //过桥器转速 - 号按钮
{
    gq_zs--;
    ui->label_4->setText(QString::number(gq_zs,10));
}

void Timesetup::on_pushButton_10_clicked()//过桥器转速 + 号按钮
{
    gq_zs++;
    ui->label_4->setText(QString::number(gq_zs,10));
}

void Timesetup::on_pushButton_16_clicked()//一键设定
{

}

void Timesetup::on_pushButton_18_clicked()//复脱器 -号
{
    ftq_zs--;
    ui->label_7->setText(QString::number(ftq_zs));
}


void Timesetup::on_pushButton_17_clicked()//复脱器 +号
{
    ftq_zs++;
    ui->label_7->setText(QString::number(ftq_zs));
}

void Timesetup::on_pushButton_15_clicked()//分离滚筒 -号
{
    fenliguntong_zs--;
    ui->label_6->setText(QString::number(fenliguntong_zs));
}

void Timesetup::on_pushButton_14_clicked()//分离滚筒 +号
{
    fenliguntong_zs++;
    ui->label_6->setText(QString::number(fenliguntong_zs));
}

void Timesetup::on_pushButton_12_clicked()//风机转速 -号
{
    fj_zs--;
    ui->label_5->setText(QString::number(fj_zs));
}

void Timesetup::on_pushButton_13_clicked()//风机转速 +号
{
    fj_zs++;
    ui->label_5->setText(QString::number(fj_zs));
}
