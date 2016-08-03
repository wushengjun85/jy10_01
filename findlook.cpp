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
    pix.load("./imagejy/04.bmp");
    painter.drawPixmap(0,0,1024,600,pix);

}
