#include "work.h"
#include "ui_work.h"

#include<QMouseEvent>
#include<QPainter>
#include<QString>
#include<QTime>
#include<QTimer>
#include<QDebug>

#include"camera_thread.h"


//extern QImage *img;



bool ok;

extern  unsigned char wsjtmpflag;

extern unsigned char DC;

uchar numjy = 0;
//extern unsigned char SouSa;
//extern unsigned char tmpflag;

//extern unsigned char KL;
//extern unsigned char SK;





extern unsigned char flagWidthlamp;




//2016.6.22  extern widget.cpp 中的变量。
/********************************************************************************************************************/
//速度定义 speed
extern unsigned short int speed;
//unsigned short int
extern unsigned char daoche;


/********************************************************************************************************************/


//2016.6.20 wsj
//下面是显示can数据 值的变量
//临时定义，后边产品要更根据情况去改和规范 变量的定义。 有一半的变量可以复用。
/********************************************************************************************************************/

//开关量
// 最终协议

//第一个字节
extern unsigned char DC;  //倒车信号（倒车+） 7,
extern unsigned char SK;  //位置灯（位置灯+） 6,
extern unsigned char SouSa;//手刹指示灯（手刹指示灯+） 5,
extern unsigned char Zuozhuan; //左转向灯（左转向灯）4,
extern unsigned char Youzhuan;  //右转向灯（右转向灯）3,
extern unsigned char YuanGuang; //远光指示灯（远光指示灯） 2,
extern unsigned char Jinguang; //近光指示灯（近光指示灯） 1,


//第二个字节
extern uchar youshuifenli;  //油水分离 6,
extern uchar fadongjiguzhang;//发动机故障 5,
extern uchar yure; //预热 4,
extern uchar liangman; //粮满 3,
extern uchar KL;  //空滤报警开关（空滤-） 2,
extern uchar CongDian; //充电指示灯-  1,


//频率量
extern ushort  shengyunqi;    //升运器
extern ushort  futuoqi;       //复脱器
extern ushort  zhouliuguntong;//轴流滚筒
extern ushort  shisu; //时速

//模拟量
//18FF04F6
extern unsigned char YouLiang;     //油量（油量）
extern unsigned char Yeyayouwen; //液压油油温（液压油油温）
extern unsigned int   MiJi;      //米计（预留）
extern unsigned int   LiCheng;   //里程（预留）


//发动机 数据
//18FEEE00
extern unsigned char SuiWen;//水温；
extern unsigned int  jiyouyali; //机油压力

//0CF00400

extern ushort fadongzhuansu; //发动机转速


//18FECA00
//故障报文
extern ulong guzhangbaowen; //故障报文
extern uint  spn;//spn 码
extern uchar fmi;//fmi 码


//预热指示灯
//18FEE400

extern uchar yurezhishideng;//18FEE400

//小时计
//18FEE500
extern unsigned int XiaoshiJi; //小时计



//新增相关变量


extern uchar qianbulihezhishi;  //前部离合指示输入, 8

extern uchar tuolilihezhishi;  //脱粒离合指示输入, 7

extern uchar xieliangtongbaijin;//卸粮筒摆进限位开关 6

extern uchar Shoubing;//界面切换输入（手柄控制）4
//
extern uchar liangman70;//粮满 70, 1

//byte3
extern uchar xielianglihe_input;//卸粮离合开关输入 2
extern uchar guoqiaofanzhuan_input;//过桥反转指示输入 1


//byte4

extern uchar getaisheng_input;//割台升输入; 8
extern uchar getaijiang_input;//割台降输入; 7

extern uchar xltbj_input;//卸粮筒摆进输入 6
extern uchar xltbc_input;//卸粮筒摆出输入 5

extern uchar bhls_input;//拨禾轮升输入 4
extern uchar bhlj_input; //拨禾轮降输入; 3
extern uchar tltjiashu_input;//脱粒滚筒加速输入; 2

extern uchar tltjianshu_input;//脱粒滚筒减速输入 1


//byte5

extern uchar getaisheng_out;//割台升输出; 8
extern uchar getaijiang_out;//割台降输出; 7

extern uchar xltbj_out;//卸粮筒摆进输出 6
extern uchar xltbc_out;//卸粮筒摆出输出 5

extern uchar bhls_out;//拨禾轮升输出 4
extern uchar bhlj_out; //拨禾轮降输出; 3
extern uchar tltjiashu_out;//脱粒滚筒加速输出; 2

extern uchar tltjianshu_out;//脱粒滚筒减速输出 1



extern uchar xiehefa_out;// 卸荷阀输出
extern uchar  xielianglihe_out;//卸粮离合输出; 1







//
extern ushort  qiesuiqizhuansu;//切碎器转速
extern ushort fengjizhuansu;//切碎器转速
extern ushort guoqiaozhuansu;//过桥转速；

extern ushort tuoliguntong;//脱粒滚筒转速
extern ushort fenliguntong;//分离滚筒转速
//extern ushort
/********************************************************************************************************************/


/********************************************************************************************************************/
//2016 6.1  wushengjun
//定义变量 控制图标闪烁。
//
/********************************************************************************************************************/

extern unsigned char flagLeft;  //左转
extern unsigned char countLeft; //左转


extern unsigned char flagBattery;//电瓶指示灯


extern unsigned char flagWidthlamp; //示宽灯


extern unsigned char  flagYG; //远光灯


extern unsigned char  flagSW; //水温


extern unsigned char  flagJG; //近光灯



extern unsigned char  flagJY; //机油


extern unsigned char  flagLCM; //粮仓满


extern unsigned char   flagFDJYR; //发动机预热


extern unsigned char   flagGL; //过滤


extern unsigned char   flagYL; //油量


extern unsigned char  flagYeyayouwen;//液压油温


extern unsigned char    flagECU;//ecu


extern unsigned char    flagPark;//停车


extern unsigned char   flagFDJGZ; //发动机故障


extern unsigned char   flagRight; //右转



extern unsigned char  flagyouxiangman;//油量满报警
extern unsigned char  flagyouliangdi; //油量低报警


/********************************************************************************************************************/


Work::Work(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Work)
{
    ui->setupUi(this);

    findlokk_work = new FindLook();//初始化查询对象

    time_work = new Timesetup();//初始化设置对象


    resize(1024,600);
    Work::move(0,0);//回到原来主窗口的位置
   // setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

#if 1
    QTimer *dialogtime = new QTimer(this);
    connect(dialogtime, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
#endif

       connect(this,SIGNAL(camerastartsignal()),this,SLOT(start_thread()));//摄像头程序打开

    dialogtime->start(500);

}


Work::~Work()
{
    delete ui;
}


void Work::start_thread()
{
    video = new Camera_thread();
    video->start();
    connect(video,SIGNAL(image_data(QImage *)),this,SLOT(show_picture(QImage *)));
}
void Work::show_picture(QImage *img)
{


     ui->show_label1->setPixmap(QPixmap::fromImage(*img));
     ui->show_label1->setScaledContents(true);//图片自适应label大小 等比例大小,缩放问题解决。

     //全屏显示 要加条件判断
#if 0
//     ui->show_label1->resize(img->width(),img->height());
//     ui->show_label1->resize(1024,600);
//     ui->show_label1->move(0,0);
#endif
}
void Work::stop_thread()
{
    delete video;
}




void Work::on_pushButton_clicked()
{
    this->close();
}


void Work::paintEvent(QPaintEvent *event)
{
    QPainter dp(this);
    QPixmap dppix;
    dppix.load("./imagejy/work.bmp");
    dp.drawPixmap(0,0,1024,600,dppix);

    /**************************************************************************************************************/
    //显示时间 。2016.7.12
        QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
        QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");

        ui->lcdNumber_2->display(dateStr1);
        ui->lcdNumber->display(timeStr1);
    /**************************************************************************************************************/

    //2016.8.8  定义数值

            #if 1
                ui->label->setText("6"); //r/min

                ui->label_2->setText("88");// k/mh
                ui->label_3->setText(QString::number(XiaoshiJi));//小时计
                ui->label_4->setText(QString::number(SuiWen));//水温
                ui->label_5->setText(QString::number(Yeyayouwen));//液压油油温（液压油油温）
                ui->label_6->setText("1");//机油温度
                ui->label_7->setText(QString::number(jiyouyali));//机油压力
                ui->label_8->setText(QString::number(guoqiaozhuansu));//过桥转速
                ui->label_9->setText(QString::number(fengjizhuansu));//风机转速
                ui->label_10->setText(QString::number(futuoqi));//复脱器转速
                ui->label_11->setText(QString::number(shengyunqi));//升运器转速
                ui->label_12->setText(QString::number(qiesuiqizhuansu));//切碎器转速
                ui->label_13->setText(QString::number(tuoliguntong));//脱粒滚筒转速
                ui->label_14->setText(QString::number(fenliguntong));//分离滚筒转速

            #endif

                //加载上方图标 闪烁用到
                //zuo zhuandeng
                QPainter paintLeft(this);
                QPixmap pixLeft;

                if((DC==1)&&(wsjtmpflag == 0))
                {

                    //DC = 0;
                    //emit sendcamersignal();
                    //ok = true;

                     QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(2,2), Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                     QApplication::postEvent(ui->pushButton,press);
                     QMouseEvent* release=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(2,2),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                     QApplication::postEvent(ui->pushButton,release);

                     wsjtmpflag = 1;

                }
            /************************************************************************************************/
            //闪烁不同步问题解决办法。
            //利用消息队列 和 for 循环解决。
            //2016.7.25
            #if 1

                QPainter paintShanshuo(this);
                QPixmap pixShanshuo;
                if(1) //左转灯闪烁
                {
                    countLeft++;
                    if (countLeft>1)
                        countLeft = 0;
                    switch(countLeft)
                    {
                        case 1:
                        if(flagLeft)//左转灯闪烁
                        {
                            pixShanshuo.load("./imagejy/01.png");//14.jpg
                            paintShanshuo.drawPixmap(0,0,44,46,pixShanshuo);
                        }
                        if(flagBattery)//电瓶指示灯
                        {
                            pixShanshuo.load("./imagejy/03.png");//14.jpg
                            paintShanshuo.drawPixmap(60,0,46,32,pixShanshuo);//正上方图片显示
                            //paintShanshuo.drawPixmap(20,335,43,34,pixShanshuo);//左边图片显示
                        }

                        if(flagSW)//水温 0~120度  95度以上报警。
                        {
                             pixShanshuo.load("./imagejy/07.png");//07.jpg
                             paintShanshuo.drawPixmap(118,0,45,40,pixShanshuo);//正上方位置显示的图标
                        }

                        if(flagJY) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
                        {
                             pixShanshuo.load("./imagejy/08.png");//08.jpg
                             paintShanshuo.drawPixmap(396,0,59,24,pixShanshuo);//正上方位置显示的图标
                             //paintShanshuo.drawPixmap(20,180,43,43,pixShanshuo);//左边显示的图标
                        }

                        if(flagLCM)//flagLCM = 1; //粮仓满
                        {
                            pixShanshuo.load("./imagejy/13.png");//13.jpg
                            paintShanshuo.drawPixmap(542,0,42,41,pixShanshuo);
                        }

                        if(flagFDJYR)//flagFDJYR = 1; //发动机预热
                        {
                            pixShanshuo.load("./imagejy/15.png");//15.jpg
                            paintShanshuo.drawPixmap(761,0,46,27,pixShanshuo);
                        }

                        if(flagGL)//空 滤
                        {
                            pixShanshuo.load("./imagejy/04.png");//04.jpg
                            paintShanshuo.drawPixmap(469,0,42,43,pixShanshuo);
                        }
                        if (flagyouxiangman|flagyouliangdi)//油量
                        {
                            pixShanshuo.load("./imagejy/09.png");//14.jpg
                            paintShanshuo.drawPixmap(615,0,31,36,pixShanshuo);

                            // paintShanshuo.drawPixmap(409,172,31,36,pixShanshuo);

                        }
                        if(flagYeyayouwen)//液压油温
                        {
                             pixShanshuo.load("./imagejy/10.png");//10.jpg
                             paintShanshuo.drawPixmap(688,0,48,38,pixShanshuo);//上边图标
                             //paintShanshuo.drawPixmap(423,216,49,38,pixShanshuo);//左边图标
                        }
                        if(flagECU)//ecu
                        {
                            pixShanshuo.load("./imagejy/91.png");//03.jpg
                            paintShanshuo.drawPixmap(594,0,43,32,pixShanshuo);
                        }

                        if(flagFDJGZ)//发动机故障
                        {
                            pixShanshuo.load("./imagejy/16.png");//16.jpg
                            paintShanshuo.drawPixmap(907,0,47,30,pixShanshuo);
                        }

                        if(flagRight)//右转
                        {
                            pixShanshuo.load("./imagejy/02.png");//14.jpg
                            paintShanshuo.drawPixmap(980,0,44,46,pixShanshuo);
                        }
                        break;
                    }

                    //不用闪烁
                    if(flagWidthlamp)//示宽灯
                    {
                        pixShanshuo.load("./imagejy/06.png");//06.jpg
                        paintShanshuo.drawPixmap(177,0,57,32,pixShanshuo);
                    }

                    if(flagJG)//近光灯flagJG
                    {
                        pixShanshuo.load("./imagejy/12.png");//12.jpg
                        paintShanshuo.drawPixmap(250,0,46,37,pixShanshuo);
                    }

                    if(flagYG)//远光灯
                    {
                        pixShanshuo.load("./imagejy/05.png");//05.jpg
                        paintShanshuo.drawPixmap(323,0,46,37,pixShanshuo);
                    }

                    if(flagPark)//停车 刹车
                    {
                        pixShanshuo.load("./imagejy/11.png");//11.jpg
                        paintShanshuo.drawPixmap(834,0,48,37,pixShanshuo);
                    }

                    //油量格数
                    if (flagyouxiangman|flagyouliangdi)//油量
                    {
                        pixShanshuo.load("./imagejy/yl08.png");//14.jpg
                      paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                    }

                }

            #endif
}

void Work::on_pushButton_4_clicked()//查询按钮
{
    this->close();
    findlokk_work->show();
    findlokk_work->exec();
    this->show();
}

void Work::on_pushButton_2_clicked()// 设置按钮
{
    this->close();
    time_work->show();
    time_work->exec();
    this->close();
}

void Work::on_pushButton_5_clicked()
{
    emit camerastartsignal();
}
