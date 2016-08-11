#include "camera.h"

#include <QMessageBox>
#include "videodevice.h"
#include "common.h"
#include <unistd.h>
#include<QDebug>


Camera::Camera(QWidget *parent) :
    QWidget(parent)
{
}


void Camera::camera_init()
{

        //申请提取帧缓冲区空间
        //pp = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
        p = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
        //pp1 = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
        p1 = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));

        frame = new QImage(p,IMG_WIDTH,IMG_HEIGTH,QImage::Format_RGB888);//定义摄像头抓取帧句柄-QImage类型
        frame1 = new QImage(p1,IMG_WIDTH,IMG_HEIGTH,QImage::Format_RGB888);//定义摄像头抓取帧句柄-QImage类型

        //labelx = new MyLabel();//定义显示窗体

        vd = new VideoDevice(tr("/dev/video1"));//定义摄像头设备，linux下摄像头句柄为/mnt/dev/video0\1\2...
        vd1 = new VideoDevice(tr("/dev/video1"));//定义摄像头设备，linux下摄像头句柄为/mnt/dev/video0\1\2...

    #if 1
        rs = vd->open_device();//打开设备
        if(-1==rs)
        {
            QMessageBox::warning(this,"error","open /dev/video0 error",QMessageBox::Yes);
            vd->close_device();
        }

        rs = vd->init_device();//初始化摄像头设备
        if(-1==rs)
        {
            QMessageBox::warning(this,"error","init failed",QMessageBox::Yes);
            vd->close_device();
        }

        rs = vd->start_capturing();//控制摄像头设备开始抓图
        if(-1==rs)
        {
            QMessageBox::warning(this,tr("error"),tr("start capture failed"),QMessageBox::Yes);
            vd->close_device();
        }

        if(-1==rs)
        {
            QMessageBox::warning(this,tr("error"),tr("get frame failed"),QMessageBox::Yes);
            vd->stop_capturing();
        }
    #endif

    #if 0
        rs1 = vd1->open_device();//打开设备
        if(-1==rs1)
        {
            QMessageBox::warning(this,"error","open /dev/video1 error",QMessageBox::Yes);
            vd1->close_device();
        }

        rs1 = vd1->init_device();//初始化摄像头设备
        if(-1==rs1)
        {
            QMessageBox::warning(this,"error","init failed1",QMessageBox::Yes);
            vd1->close_device();
        }

        rs1 = vd1->start_capturing();//控制摄像头设备开始抓图
        if(-1==rs1)
        {
            QMessageBox::warning(this,tr("error"),tr("start capture failed1"),QMessageBox::Yes);
            vd1->close_device();
        }

        if(-1==rs1)
        {
            QMessageBox::warning(this,tr("error"),tr("get frame failed1"),QMessageBox::Yes);
            vd1->stop_capturing();
        }
    #endif
//        timer = new QTimer(this);
//        //connect(timer,SIGNAL(timeout()),this,SLOT(update()));
//        connect(timer,SIGNAL(timeout()),this,SLOT(tmtt()));//链接定时器到时间后执行的槽函数
//        timer->start(40);//开启定时器,33ms;即每秒30帧
}

void Camera::tmtt( QImage *image)
{
#if 1
    rs = vd->unget_frame();
    rs = vd->get_frame((void **)&p,(size_t*)&len);//抓取帧
    //convert_yuv_to_rgb_buffer(p,pp,IMG_WIDTH,IMG_HEIGTH);//转换为RGB数据
    frame->loadFromData((uchar *)p,/*len*/IMG_WIDTH * IMG_HEIGTH * 3 * sizeof(char));//载入转换后的RGB数据到帧句柄
    //memcpy(pimg,pp,sizeof(pp));

    *image = *frame; //教训  image  = frame ; 只是值赋予了 地址，没有把值传进去
    //usleep(40000); //停留40毫秒

    //ui->label->setPixmap(QPixmap::fromImage(*frame,Qt::AutoColor));//显示帧图像到窗体,此处会执行子类化的label函数体--MyLabel.cpp中的void MyLabel::paintEvent(QPaintEvent * event)
    //ui->label_2->setPixmap(QPixmap::fromImage(*frame,Qt::AutoColor));//显示帧图像到窗体,此处会执行子类化的label函数体--MyLabel.cpp中的void MyLabel::paintEvent(QPaintEvent * event)
    //rs = vd->unget_frame();
#endif

#if 0
    rs1 = vd1->unget_frame();
    rs1 = vd1->get_frame((void **)&p1,(size_t*)&len);//抓取帧
    //convert_yuv_to_rgb_buffer(p1,pp1,IMG_WIDTH,IMG_HEIGTH);//转换为RGB数据
    frame1->loadFromData((uchar *)p1,IMG_WIDTH * IMG_HEIGTH * 3 * sizeof(char));//载入转换后的RGB数据到帧句柄
    ui->label_2->setPixmap(QPixmap::fromImage(*frame1,Qt::AutoColor));//显示帧图像到窗体,此处会执行子类化的label函数体--MyLabel.cpp中的void MyLabel::paintEvent(QPaintEvent * event)
    //rs1 = vd1->unget_frame();
#endif

}
