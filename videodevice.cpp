#include "videodevice.h"
#include <stdio.h>
#include <unistd.h>
#include "common.h"

VideoDevice::VideoDevice(QString dev_name)
{
    this->dev_name = dev_name;
    this->fd = -1;
    this->buffers = NULL;
    this->n_buffers = 0;
    this->index = -1;
 
}
 
int VideoDevice::open_device()
{
    fd = open(dev_name.toStdString().c_str(), O_RDWR/*|O_NONBLOCK*/, 0);
   // fd = open(dev_name.toStdString().c_str(), O_RDWR|O_NONBLOCK, 0);
 
    if(-1 == fd)
    {
        //emit (tr("open: %1").arg(QString(strerror(errno))));
        printf("open device error!\n");
        return -1;
    }
    return 0;
}
 
int VideoDevice::close_device()
{
    if(-1 == close(fd))
    {
       //emit display_error(tr("close: %1").arg(QString(strerror(errno))));
        printf("close device error!\n");
        return -1;
    }
    return 0;
}
 
int VideoDevice::init_device()
{
    v4l2_capability cap;
    v4l2_cropcap cropcap;
    v4l2_crop crop;
    v4l2_format fmt;
    v4l2_streamparm setfps;//设置采样率
    v4l2_fmtdesc fmtdesc;//查询摄像头支持像素格式

    if(-1 == ioctl(fd, VIDIOC_QUERYCAP, &cap))
    {
        if(EINVAL == errno)
        {
            //emit display_error(tr("%1 is no V4l2 device").arg(dev_name));
            printf("open device is no V4l2 device!\n");
        }
        else
        {
            //emit display_error(tr("VIDIOC_QUERYCAP: %1").arg(QString(strerror(errno))));
            printf("VIDIOC_QUERYCAP error!\n");
        }
        return -1;
    }
    else
    {
        printf("driver:\t\t%s\n",cap.driver);//驱动名
        printf("card:\t\t%s\n",cap.card);//摄像头信息
        printf("bus_info:\t%s\n",cap.bus_info);//PCI总线信息
        printf("version:\t%d\n",cap.version);//内核版本
        printf("capabili ties:\t%x\n",cap.capabilities);
        //以上打印信息详见设备能力结构体(struct v4l2_capability)
    }
    printf("Driver Name:%s/n Card Name:%s/n Bus info:%s/n/n",cap.driver,cap.card,cap.bus_info);
    //emit (tr("Driver Name:%d/n Card Name:%d/n Bus info:%s/n").arg(QString((char *)cap.driver),QString(cap.card),QString(cap.bus_info));
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        //emit display_error(tr("%1 is no video capture device").arg(dev_name));
        printf("device is no video capture device!\n");
        return -1;
    }
 
    if(!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        //emit display_error(tr("%1 does not support streaming i/o").arg(dev_name));
        printf("device does not support streaming i/o!\n");
        return -1;
    }

    //列举摄像头所支持像素格式
    fmtdesc.index=0;
    fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    printf("Support format:\n");
    while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc)!=-1)
    {
        printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
        fmtdesc.index++;
    }

    CLEAR(fmt);
    //set fmt
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = IMG_WIDTH;
    fmt.fmt.pix.height = IMG_HEIGTH;
    //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if(-1 == ioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        //emit display_error(tr("VIDIOC_S_FMT").arg(QString(strerror(errno))));
        printf("SFT set error!\n");
        return -1;
    }
#if 0
    //set fps 具体参考结构体v4l2_captureparm
    setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    /*timeperframe字段用于指定想要使用的帧频率，它是一个结构体：  numerator 和denominator所描述的系数给出的是成功的帧之间的时间间隔。
     numerator分子，denominator分母。主要表达每次帧之间时间间隔。numerator/denominator秒一帧。*/
    setfps.parm.capture.timeperframe.numerator = 1;
    setfps.parm.capture.timeperframe.denominator = 25;//本摄像头帧频范围[5,30]帧/秒
    if(ioctl(fd, VIDIOC_S_PARM, &setfps) == -1)
    {
        printf("Unable to set frame rate\n");
        return FALSE;
    }
    else
    {
        printf("set fps OK!\n");
    }
    if(ioctl(fd, VIDIOC_G_PARM, &setfps) == -1)
    {
        printf("Unable to get frame rate\n");
        return FALSE;
    }
    else
    {
        printf("get fps OK!\n");
        printf("timeperframe.numerator:\t%d\n",setfps.parm.capture.timeperframe.numerator);
        printf("timeperframe.denominator:\t%d\n",setfps.parm.capture.timeperframe.denominator);
    }
#endif
    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
 
    if(0 == ioctl(fd, VIDIOC_CROPCAP, &cropcap))
    {
        CLEAR(crop);
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;
 
        if(-1 == ioctl(fd, VIDIOC_S_CROP, &crop))
        {
            if(EINVAL == errno)
            {
//                emit display_error(tr("VIDIOC_S_CROP not supported"));
                printf("VIDIOC_S_CROP not supported!\n");
            }
            else
            {
                //emit display_error(tr("VIDIOC_S_CROP: %1").arg(QString(strerror(errno))));
                printf("VIDIOC_S_CROP is supported!\n");
                //return -1;
            }
        }
    }
    else
    {
        //emit display_error(tr("VIDIOC_CROPCAP: %1").arg(QString(strerror(errno))));
        printf("VIDIOC_S_CROP error!\n");
        //return -1;
    }
 
 
    if(-1 == init_mmap())
    {
        return -1;
    }
 
    return 0;
}
 //printf("device !\n");
int VideoDevice::init_mmap()
{
    v4l2_requestbuffers req;
    CLEAR(req);
 
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
 
    if(-1 == ioctl(fd, VIDIOC_REQBUFS, &req))
    {
        if(EINVAL == errno)
        {
            //emit display_error(tr("%1 does not support memory mapping").arg(dev_name));
            printf("device does not support memory mapping!\n");
            return -1;
        }
        else
        {
            //emit display_error(tr("VIDIOC_REQBUFS %1").arg(QString(strerror(errno))));
            printf("device VIDIOC_REQBUFS error!\n");
            return -1;
        }
    }
 
    if(req.count < 2)
    {
        //emit display_error(tr("Insufficient buffer memory on %1").arg(dev_name));
        printf("device Insufficient buffer memory!\n");
        return -1;
    }
 
    buffers = (buffer*)calloc(req.count, sizeof(*buffers));
 
    if(!buffers)
    {
        //emit display_error(tr("out of memory"));
        printf("device out of memory!\n");
        return -1;
    }
 
    for(n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
        v4l2_buffer buf;
        CLEAR(buf);
 
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
 
        if(-1 == ioctl(fd, VIDIOC_QUERYBUF, &buf))
        {
            //emit display_error(tr("VIDIOC_QUERYBUF: %1").arg(QString(strerror(errno))));
            printf("device !VIDIOC_QUERYBUF\n");
            return -1;
        }
 
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start =
                mmap(NULL, // start anywhere
                     buf.length,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     fd, buf.m.offset);
 
        if(MAP_FAILED == buffers[n_buffers].start)
        {
            //emit display_error(tr("mmap %1").arg(QString(strerror(errno))));
            printf("device mmap error!\n");
            return -1;
        }
    }
    return 0;
 
}
 
int VideoDevice::start_capturing()
{
    unsigned int i;
    for(i = 0; i < n_buffers; ++i)
    {
        v4l2_buffer buf;
        CLEAR(buf);
 
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;
        buf.index = i;
//        fprintf(stderr, "n_buffers: %d\n", i);
 
        if(-1 == ioctl(fd, VIDIOC_QBUF, &buf))
        {
            //emit display_error(tr("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            printf("device VIDIOC_QBUF!\n");
            return -1;
        }
    }
 
    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
 
    if(-1 == ioctl(fd, VIDIOC_STREAMON, &type))
    {
        //emit display_error(tr("VIDIOC_STREAMON: %1").arg(QString(strerror(errno))));
        printf("device VIDIOC_STREAMON!\n");
        return -1;
    }
    return 0;
}
 
int VideoDevice::stop_capturing()
{
    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
 
    if(-1 == ioctl(fd, VIDIOC_STREAMOFF, &type))
    {
        //emit (tr("VIDIOC_STREAMOFF: %1").arg(QString(strerror(errno))));
        printf("device VIDIOC_STREAMOFF!\n");
        return -1;
    }
    return 0;
}
 
int VideoDevice::uninit_device()
{
    unsigned int i;
    for(i = 0; i < n_buffers; ++i)
    {
        if(-1 == munmap(buffers[i].start, buffers[i].length))
        {
            //emit display_error(tr("munmap: %1").arg(QString(strerror(errno))));
            printf("device munmap!\n");
            return -1;
        }
 
    }
    free(buffers);
    return 0;
}
 
int VideoDevice::get_frame(void **frame_buf, size_t* len)
{
    v4l2_buffer queue_buf;
    CLEAR(queue_buf);
 
    queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    queue_buf.memory = V4L2_MEMORY_MMAP;
 
    if(-1 == ioctl(fd, VIDIOC_DQBUF, &queue_buf))
    {
        printf("error is %d!\n",errno);
        QString s;
        s.sprintf("%d",errno);
        //emit display_error(s);
       // printf(s);
        switch(errno)
        {
        case EAGAIN:
//            perror("dqbuf");
            return -1;
        case EIO:
            return -1 ;
        default:
            //emit display_error(tr("VIDIOC_DQBUF: %d").arg(QString(strerror(errno))));
            printf("device VIDIOC_DQBUF error!\n");
            return -1;
        }
    }
 
    *frame_buf = buffers[queue_buf.index].start;
    *len = buffers[queue_buf.index].length;
    index = queue_buf.index;

    return 0;
 
}
 
int VideoDevice::unget_frame()
{
    if(index != -1)
    {
        v4l2_buffer queue_buf;
        CLEAR(queue_buf);
 
        queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        queue_buf.memory = V4L2_MEMORY_MMAP;
        queue_buf.index = index;
 
        if(-1 == ioctl(fd, VIDIOC_QBUF, &queue_buf))
        {
            //emit display_error(tr("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            printf("VIDIOC_QBUF eror");
            return -1;
        }
        return 0;
    }
    return -1;
}
