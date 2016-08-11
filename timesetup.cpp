#include "timesetup.h"
#include "ui_timesetup.h"
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QString>



#include<QtSql>
#include<QTextCodec>

int ele0;


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
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

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




void Timesetup::on_pushButton_16_clicked()//一键设定
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase dbconn=QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    dbconn.setDatabaseName("mytest.db");  //在工程目录新建一个mytest.db的文件
    if(!dbconn.open())    {
    qDebug()<<"fdsfds";
    }
   QSqlQuery query;//以下执行相关QSL语句
   query.exec("create table student(id varchar,name varchar,age varchar)");    //新建student表，id设置为主键，还有一个name项
   //query.exec(QObject::tr("insert into student values(1,'李刚','ui')"));

   query.exec(QObject::tr("insert into student values(2,'脱粒滚筒转速',500)"));



   //insert into mytable(id,name,age) values(2,"李四","23");

//     query.exec(QObject::tr("insert into student values(2,'苹果')"));
//      query.exec(QObject::tr("insert into student values(3,'葡萄')"));
//      query.exec(QObject::tr("insert into student values(3,'李子')"));
//      query.exec(QObject::tr("insert into student values(4,’橘子')"));
//      query.exec(QObject::tr("insert into student values(5,'核桃')"));
//      query.exec(QObject::tr("insert into student values(6,'芒果')"));
//         //query.exec(QObject::tr("select id,name from student where id>=1"));
     query.exec("select id,name,age from student where id>=1");
      while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
      {

             ele0=query.value(0).toInt();//query.value(0)是id的值，将其转换为int型
             QString ele1=query.value(1).toString();
             int ele2=query.value(2).toInt();
             qDebug()<<ele0<<ele1<<ele2;//输出两个值
      }
   query.exec(QObject::tr("drop student"));
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
