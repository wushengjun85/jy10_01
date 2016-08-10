#include "camera_thread.h"
#include"videodevice.h"
#include"common.h"
#include<QDebug>



uchar *m;
QImage *img;

Camera_thread::Camera_thread(QObject *parent) :
    QThread(parent)
{
}

void Camera_thread::run()
{
    camera_hw.camera_init();
    m = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));

    img = new QImage(m,IMG_WIDTH,IMG_HEIGTH,QImage::Format_RGB888);//定义摄像头抓取帧句柄-QImage类型

    while(1)
    {
        camera_hw.tmtt(img);
        usleep(40000); //停留40毫秒
        emit image_data(img);
    }

}
