#include "timesetuptrue.h"
#include "ui_timesetuptrue.h"


TimesetupTrue::TimesetupTrue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimesetupTrue)
{
    ui->setupUi(this);

    TimesetupTrue::move(0,0);//回到原来主窗口的位置
    //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

    QTimer *tm_set = new QTimer(this);
   // connect(tm, SIGNAL(timeout()), this, SLOT(funsetuptime()));  //连接信号槽，定时器超时触发窗体更新
    //connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(funsetuptime()));
    tm_set->start(500);

}

TimesetupTrue::~TimesetupTrue()
{
    delete ui;
}

void TimesetupTrue::on_pushButton_clicked()//返回上一界面按钮
{
    this->close();
}


void TimesetupTrue::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./imagejy/beijingtu.bmp");
    painter.drawPixmap(0,0,1024,600,pix);
}

void TimesetupTrue::on_dateEdit_dateChanged(const QDate &date)
{
    QString lsdate = date.toString("yyyy-MM-dd");
    ui->lcdNumber->display(lsdate);
}

void TimesetupTrue::on_timeEdit_timeChanged(const QTime &timed)
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
