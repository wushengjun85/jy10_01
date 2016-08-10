#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

#include <qtimer.h>
#include "videodevice.h"

class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = 0);

    void camera_init();
    
signals:
    
public slots:

        void tmtt( QImage *image);

private:
    /*****************************************************************************/
    //摄像头对象定义
    QImage *frame;//定义抓取帧
    QImage *frame1;//定义抓取帧
    //QPixmap *frame;
    //MyLabel *labelx;//定义子类化显示窗体
    QTimer *timer;//定时器
    int rs,rs1;
    uchar *pp;//摄像头抓取指针
    uchar * p;//转换RGB指针
    uchar *pp1;//摄像头抓取指针
    uchar * p1;//转换RGB指针
    //uchar * pimg;//转换IMG需要的指针缓冲区
    unsigned int len;//帧缓冲区长度
    int convert_yuv_to_rgb_pixel(int y, int u, int v);//YUV格式到RGB的转换
    int convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height);
    VideoDevice *vd;//定义摄像头设备
    VideoDevice *vd1;//定义摄像头设备
    /*****************************************************************************/
    
};

#endif // CAMERA_H
