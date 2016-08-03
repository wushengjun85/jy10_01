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


    QTimer *tm = new QTimer(this);
   // connect(tm, SIGNAL(timeout()), this, SLOT(funsetuptime()));  //连接信号槽，定时器超时触发窗体更新
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(funsetuptime()));
    tm->start(500);
}

Timesetup::~Timesetup()
{
    delete ui;
}

void Timesetup::funsetuptime()
{

    //QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    //ui->lcdNumber->display(dateStr);
}


void Timesetup::on_dateEdit_dateChanged(const QDate &date)
{

    QString lsdate = date.toString("yyyy-MM-dd");
    ui->lcdNumber->display(lsdate);
}

void Timesetup::on_timeEdit_timeChanged(const QTime &timed)
{
    QString timeStr= timed.toString();     //绘制当前的时间
    ui->lcdNumber_2->display(timeStr);

    QString str1 = """";
         str1 += "date -s ";
         str1 += timeStr;
         str1 += """";

         //system("clock -w");
         system("hwclock --hctosys");
         system(str1.toLatin1().data());//str1.toLatin1().data()
}

void Timesetup::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./imagejy/03.bmp");
    painter.drawPixmap(0,0,1024,600,pix);
}

void Timesetup::on_pushButton_clicked()
{
    this->close();
}
