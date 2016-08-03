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

    resize(1024,600);
    Work::move(0,0);//回到原来主窗口的位置
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮


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
    dppix.load("./imagejy/02.bmp");
    dp.drawPixmap(0,0,1024,600,dppix);
}
