#include "widget.h"
#include "ui_widget.h"

#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include"signalcan.h"

/***************************************************************************************************************/
//2016.8.1  变量定义
bool flaglanguage = false; //中英文切换标志变量。

//uchar numtmp = 0; //临时 测试所用。


/***************************************************************************************************************/






int num = 0;
int numtmp = 0;


unsigned char wsjtmpflag = 0;

bool OK = false;

extern bool ok;



uchar wsj1 = 0;
uchar wsj2 = 0;
uchar wsj3 = 0;
uchar wsj4 = 0;
/********************************************************************************************************************/
//定义时间变量用于各界面传递
//2016.7.11

QString  Datesetup;
/********************************************************************************************************************/



/********************************************************************************************************************/
//2016 6.1  wushengjun
//定义变量 控制图标闪烁。
//
/********************************************************************************************************************/
uchar j=0;
uchar jflag = 0;
uchar mm=0;
uchar jjjflag = 0;
unsigned char  mybufflag[15] = {0};
unsigned char  myindex[15] = {0};


unsigned char  countBuff = 0;


unsigned char flagLeft = 1;  //左转
unsigned char countLeft = 0; //左转

unsigned char flagBattery = 1;//电瓶指示灯
unsigned char countBattery = 0;//电瓶指示灯

unsigned char flagWidthlamp = 1; //示宽灯
unsigned char countWidthlamp = 0;//示宽灯

unsigned char  flagYG = 0; //远光灯
unsigned char  countYG = 0;//远光灯

unsigned char  flagSW  = 0; //水温
unsigned char  countSW = 0; //水温

unsigned char  flagJG = 0; //近光灯
unsigned char  countJG = 0; //近光灯


unsigned char  flagJY = 0; //机油
unsigned char  countJY = 0; //机油

unsigned char  flagLCM = 0; //粮仓满
unsigned char  countLCM = 0; //粮仓满

unsigned char   flagFDJYR = 0; //发动机预热
unsigned char   countFDJYR = 0; //发动机预热

unsigned char   flagGL = 0; //过滤
unsigned char   countGL = 0; //过滤

unsigned char   flagYL = 1; //油量
unsigned char    countYL = 0;//油量

unsigned char  flagYeyayouwen = 1;//液压油温
unsigned char  countYeyayouwen = 0; //液压油温

unsigned char    flagECU = 0;//ecu
unsigned char    countECU = 0;//ecu

unsigned char    flagPark = 0;//停车
unsigned char    countPark = 0; //停车

unsigned char   flagFDJGZ = 0; //发动机故障
unsigned char   countFDJGZ = 0; //发动机故障

unsigned char   flagRight = 0; //右转
unsigned char    countRight = 0;//右转


unsigned char  flagyouxiangman = 1; //油量满
unsigned char  flagyouliangdi  = 0; // 油量低


unsigned char  flagCanfault = 0;//Can 通信故障
unsigned char  flagJinqifault = 0;//进气温度传感器故障
unsigned char  flagYalisenserfault = 0;//增压压力传感器故障

unsigned char  flagSwSenserfault = 0; //水温传感器故障
unsigned char  flagTulunzhoufault = 0;//凸轮轴故障
unsigned char flagQulunzhoufault = 0;//曲轴故障

/********************************************************************************************************************/


//2016.6.20 wsj
//下面是显示can数据 值的变量
//临时定义，后边产品要更根据情况去改和规范 变量的定义。 有一半的变量可以复用。
/********************************************************************************************************************/
// 最终协议
//2016.7.8
/********************************************************************************************************************/
//开关量
//18FF01F6


//第一个字节
unsigned char DC;  //倒车信号（倒车+） 7,
unsigned char SK;  //位置灯（位置灯+） 6,
unsigned char SouSa;//手刹指示灯（手刹指示灯+） 5,
unsigned char Zuozhuan; //左转向灯（左转向灯）4,
unsigned char Youzhuan;  //右转向灯（右转向灯）3,
unsigned char YuanGuang; //远光指示灯（远光指示灯） 2,
unsigned char Jinguang; //近光指示灯（近光指示灯） 1,


//第二个字节
uchar youshuifenli;  //油水分离 6,
uchar fadongjiguzhang;//发动机故障 5,
uchar yure; //预热 4,
uchar liangman; //粮满 3,
uchar KL;  //空滤报警开关（空滤-） 2,
uchar CongDian; //充电指示灯-  1,


//第三个字节
uchar kg6;//开关6 6，
uchar kg5;//开关5 5，
uchar kg4;//开关4 4,
uchar kg3;//开关3 3,
uchar kg2;//开关2 2,
uchar kg1;//开关1 1,


//第二个字节
uchar out6;//输出6 6，
uchar out5;//输出5 5,
uchar out4;//输出4 4,


//第一个字节
uchar out3;//输出3 3,
uchar out2;//输出2 2,
uchar out1;//输出1 1,

//频率量
ushort  shengyunqi;    //升运器
ushort  futuoqi;       //复脱器
ushort  zhouliuguntong;//轴流滚筒
ushort  shisu; //时速

//模拟量
//18FF04F6
unsigned char YouLiang;     //油量（油量）
unsigned char Yeyayouwen; //液压油油温（液压油油温）
unsigned int   MiJi = 0;      //米计（预留）
unsigned int   LiCheng;   //里程（预留）


//发动机 数据


//18FEEE00
unsigned char SuiWen;//水温；
unsigned int  jiyouyali; //机油压力

//0CF00400

ushort fadongzhuansu; //发动机转速


//18FECA00
//故障报文
ulong guzhangbaowen; //故障报文
uint  spn = 0;//spn 码
uchar fmi = 0;//fmi 码


//预热指示灯
//18FEE400

uchar yurezhishideng;//18FEE400

//小时计
//18FEE500
unsigned int XiaoshiJi; //小时计

/********************************************************************************************************************/


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Widget::move(0,0);//回到原来主窗口的位置
    //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

    //初始化 work子界面
    work = new Work();
    //初始化 Timesetup子界面
    timeObj = new Timesetup();

    //初始化 FindLook 子界面
    findlook = new FindLook();


    setWindowTitle(tr("Haovel"));  //设置窗体名称
    //resize(1024,600);

    QTimer *timer = new QTimer(this);   //声明一个定时器
   //QTimer *timertst = new QTimer(this);

    //update()会自动产生重绘消息，调用paintEvent()
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    connect(timer, SIGNAL(timeout()), this, SLOT(diplaytime()));  //连接信号槽，定时器超时触发窗体更新
    timer->start(500);   //启动定时器
    //timertst->start(1000);

    //解析现象，当去掉 setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); 这一句，在开发板子上能显示上方图标，但是不闪烁，
    //不注释则可以在板子上闪烁。
   // setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

    //倒车摄像头信号与槽
    //connect(this,SIGNAL(sendcamersignal()),this,SLOT(cameraslot()));


    //线程初始化与启动
    mycan = new SignalCan();
    mycan->start();


}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;

    if (flaglanguage)
    {
    pix.load("./imagejy/xingzou2.bmp");
    painter.drawPixmap(0,0,800,600,pix);

    }
    else
    {
    pix.load("./imagejy/xingzou.bmp");
    painter.drawPixmap(0,0,1024,600,pix);
    }

    painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
    painter.translate(218, 303);//重新定位坐标起始点，把坐标原点放到窗体的中央

    //下面两个数组用来定义表针的两个顶点，以便后面的填充
    static const QPoint hourHand[4] = {
        QPoint(8, 0),
        QPoint(-8,0),
        QPoint(-1.5, -170),
        QPoint(1.5, -170)
    };
    static const QPoint minuteHand[4] = {
        QPoint(8, 0),
        QPoint(-8,0),
        QPoint(-1.5, -170),
        QPoint(1.5, -170)
    };

    // r/mini

    painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.rotate(-132);
    painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
    painter.rotate(numtmp++);  //设置旋转(6° * 秒)
    //painter.rotate(4.0 *shisu);

    painter.drawConvexPolygon(hourHand, 4);  //填充分针部分

    painter.restore();

    /***********************************************/
    //2016.6.25   画白圈
    painter.setBrush(Qt::lightGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),25,25);
    painter.restore();

    //画白圈
    /***********************************************/

    painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),20,20);
    painter.restore();


    //km/h
    painter.translate(579,1);//重新定位坐标起始点，把坐标原点放到窗体的中央
//painter.translate(220, 304);

    //painter.scale(side / 400.0, side / 300.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();

    painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.rotate(-132);
   // painter.rotate(4.0 *shisu);  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    //内测用
    /****************************************************************************/
    //qDebug()<<"time: "<<time.second()<<endl;

    /****************************************************************************/

    painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.restore();

    /***********************************************/
    //2016.6.25   画白圈
    painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),25,25);
    painter.restore();

    //画白圈
    /***********************************************/


    painter.setBrush(Qt::black);
    painter.save();//画上中心原点
     painter.drawEllipse(QPoint(0,0),20,20);
    painter.restore();


    //处理图片闪烁 shansuo
    painter.translate(-405,-432);//平移到左上角

/************************************************************************************************/
//2016.7.8
//加载里程图片



    /************************************************************************************************/
    //2016.7.8
    //加载里程图片
        QPainter paintLicheng(this);
        QPixmap pixLicheng;

        pixLicheng.load("./img2/35.png");//14.jpg
        paintLicheng.drawPixmap(625,380,96,27,pixLicheng);


    /************************************************************************************************/
    //2016.6.25  定义数值

#if 0
        ui->label->setText(QString::number(YouLiang)); //油量（油量）
        ui->label_3->setText(QString::number(jiyouyali)); //机油压力
        ui->label_2->setText(QString::number(Yeyayouwen));//液压油油温（液压油油温）
        ui->label_4->setText(QString::number(SuiWen));//水温；
        //ui->label_5->setText(QString::number(KL)); //机油温度
        ui->label_6->setText(QString::number(CongDian));//充放电
        ui->label_7->setText(QString::number(fmi));//FMI
        ui->label_8->setText(QString::number(spn));//SPN

        ui->label_9->setText(QString::number(zhouliuguntong));//轴流滚筒
        ui->label_10->setText(QString::number(futuoqi)); //复脱器
        ui->label_11->setText(QString::number(shengyunqi));//升运器
        ui->label_12->setText(QString::number(MiJi));  //里程
        ui->label_13->setText(QString::number(XiaoshiJi));//小时计
#endif

    #if 1
        ui->label->setText("6");
        ui->label_2->setText("88");
        ui->label_3->setText("99");
        ui->label_4->setText("11");
        ui->label_5->setText("77");

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
             QApplication::postEvent(ui->ptn_back,press);
             QMouseEvent* release=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(2,2),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
             QApplication::postEvent(ui->ptn_back,release);

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
                    paintShanshuo.drawPixmap(0,0,43,34,pixShanshuo);
                }
                if(flagBattery)//电瓶指示灯
                {
                    pixShanshuo.load("./imagejy/03.png");//14.jpg
                    paintShanshuo.drawPixmap(51,0,43,34,pixShanshuo);//正上方图片显示
                    paintShanshuo.drawPixmap(20,335,43,34,pixShanshuo);//左边图片显示
                }

                if(flagSW)//水温 0~120度  95度以上报警。
                {
                     pixShanshuo.load("./imagejy/07.png");//14.jpg
                     paintShanshuo.drawPixmap(204,0,35,35,pixShanshuo);//正上方位置显示的图标
                }

                if(flagJY) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
                {
                     pixShanshuo.load("./imagejy/22.png");//14.jpg
                     paintShanshuo.drawPixmap(306,0,43,43,pixShanshuo);//正上方位置显示的图标
                     paintShanshuo.drawPixmap(20,180,43,43,pixShanshuo);//左边显示的图标
                }

                if(flagLCM)//flagLCM = 1; //粮仓满
                {
                    pixShanshuo.load("./imagejy/7.png");//14.jpg
                    paintShanshuo.drawPixmap(357,0,43,43,pixShanshuo);
                }

                if(flagFDJYR)//flagFDJYR = 1; //发动机预热
                {
                    pixShanshuo.load("./imagejy/17.png");//14.jpg
                    paintShanshuo.drawPixmap(357,0,43,43,pixShanshuo);
                }

                if(flagGL)//过滤
                {
                    pixShanshuo.load("./imagejy/20.png");//14.jpg
                    paintShanshuo.drawPixmap(408,0,43,43,pixShanshuo);
                }
                if (flagyouxiangman|flagyouliangdi)//油量
                {
                    pixShanshuo.load("./imagejy/09.png");//14.jpg
                    paintShanshuo.drawPixmap(459,0,31,36,pixShanshuo);

                     paintShanshuo.drawPixmap(400,172,31,36,pixShanshuo);

                }
                if(flagYeyayouwen)//液压油温
                {
                     pixShanshuo.load("./imagejy/14.png");//14.jpg
                     paintShanshuo.drawPixmap(523,0,43,43,pixShanshuo);//上边图标
                     //paintShanshuo.drawPixmap(423,216,49,38,pixShanshuo);//左边图标
                }
                if(flagECU)//ecu
                {
                    pixShanshuo.load("./imagejy/91.png");//14.jpg
                    paintShanshuo.drawPixmap(585,0,43,32,pixShanshuo);
                }

                if(flagFDJGZ)//发动机故障
                {
                    pixShanshuo.load("./imagejy/8.png");//14.jpg
                    paintShanshuo.drawPixmap(697,0,43,37,pixShanshuo);
                }

                if(flagRight)//右转
                {
                    pixShanshuo.load("./imagejy/right.png");//14.jpg
                    paintShanshuo.drawPixmap(752,0,48,48,pixShanshuo);
                }
                break;
            }

            //不用闪烁
            if(flagWidthlamp)//示宽灯
            {
                pixShanshuo.load("./imagejy/06.png");//14.jpg
                paintShanshuo.drawPixmap(102,0,43,34,pixShanshuo);
            }

            if(flagJG)//近光灯flagJG
            {
                pixShanshuo.load("./imagejy/15.png");//14.jpg
                paintShanshuo.drawPixmap(255,0,38,41,pixShanshuo);
            }

            if(flagYG)//远光灯
            {
                pixShanshuo.load("./imagejy/24.png");//14.jpg
                paintShanshuo.drawPixmap(153,0,43,34,pixShanshuo);
            }

            if(flagPark)//停车 刹车
            {
                pixShanshuo.load("./imagejy/18.png");//14.jpg
                paintShanshuo.drawPixmap(640,0,43,34,pixShanshuo);
            }

            //油量格数
            if (flagyouxiangman|flagyouliangdi)//油量
            {
                pixShanshuo.load("./imagejy/yl08.png");//14.jpg
                paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
            }

        }

    #endif



}

void Widget::on_pushButton_timesetup_clicked() //设置按钮
{
    this->close();
    timeObj->show();
    timeObj->exec();
    this->show();
}

void Widget::on_ptn_back_clicked()// 进入子界面，并返回按键事件
{
    this->close();
    work->show();
    work->exec();
    this->show();
}

void Widget::diplaytime()
{
    QString time_display =  QTime::currentTime().toString();     //绘制当前的时间
    ui->lcdNumber->display(time_display);
}

void Widget::on_pushButton_timesetup_2_clicked()  //查询按钮
{
    this->close();
    findlook->show();
    findlook->exec();
    this->show();
}
