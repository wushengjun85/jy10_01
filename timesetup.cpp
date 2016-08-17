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

    system("rm my.db");
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

//   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("my.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
   }
   QSqlQuery query;
//   bool ok = query.exec("CREATE TABLE IF NOT EXISTS  myjy10 (id INTEGER PRIMARY KEY AUTOINCREMENT,"
//                                      "name VARCHAR(20) NOT NULL,"
//                                      "age INTEGER NULL)");

   bool ok = query.exec("create table myjy10(id INTEGER,name varchar,age INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }

          query.prepare("INSERT INTO myjy10 (id, name, age) VALUES (:id, :name, :age)");

          query.bindValue(":id",1);
          query.bindValue(":name", QObject::tr("脱粒滚筒转速"));
          query.bindValue(":age", ui->label->text().toInt());
          query.exec();

          query.bindValue(":id",2);
          query.bindValue(":name", QObject::tr("切碎器转速"));
          query.bindValue(":age", ui->label_2->text().toInt());
          query.exec();

          query.bindValue(":id",3);
          query.bindValue(":name", QObject::tr("风机转速"));
          query.bindValue(":age", ui->label_5->text().toInt());
          query.exec();

          query.bindValue(":id",4);
          query.bindValue(":name", QObject::tr("复脱器堵塞转速"));
          query.bindValue(":age", ui->label_7->text().toInt());
          query.exec();

          query.bindValue(":id",5);
          query.bindValue(":name", QObject::tr("升运器堵塞转速"));
          query.bindValue(":age", ui->label_3->text().toInt());
          query.exec();

          query.bindValue(":id",6);
          query.bindValue(":name", QObject::tr("过桥转速"));
          query.bindValue(":age", ui->label_4->text().toInt());
          query.exec();

          query.bindValue(":id",7);
          query.bindValue(":name", QObject::tr("分离滚筒转速"));
          query.bindValue(":age", ui->label_6->text().toInt());
          query.exec();

        query.exec("select id, name, age from myjy10");
        while (query.next())
        {

           qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        }

        query.exec(QObject::tr("drop myjy10"));
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
