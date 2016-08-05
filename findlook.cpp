#include "findlook.h"
#include "ui_findlook.h"


#include<QPainter>
#include<QString>
#include<QTime>
#include<QTimer>

FindLook::FindLook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindLook)
{
    ui->setupUi(this);

    FindLook::move(0,0);//回到原来主窗口的位置
    //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮
}

FindLook::~FindLook()
{
    delete ui;
}

void FindLook::on_pushButton_clicked()
{
    this->close();
}

void FindLook::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./imagejy/findlook.bmp");
    painter.drawPixmap(0,0,1024,600,pix);

}
