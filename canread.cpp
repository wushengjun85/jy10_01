
#include "canread.h"
#include <QWidget>
extern unsigned char flagWidthlamp;




//2016.6.22  extern widget.cpp 中的变量。
/********************************************************************************************************************/
//速度定义 speed
extern unsigned short int speed = 0;
//unsigned short int
extern unsigned char daoche = 0;


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


//第三个字节
extern uchar kg6;//开关6 6，
extern uchar kg5;//开关5 5，
extern uchar kg4;//开关4 4,
extern uchar kg3;//开关3 3,
extern uchar kg2;//开关2 2,
extern uchar kg1;//开关1 1,


//第二个字节
extern ushort out6;//输出6 6，
extern ushort out5;//输出5 5,
extern ushort out4;//输出4 4,


//第一个字节
extern ushort out3;//输出3 3,
extern ushort out2;//输出2 2,
extern ushort out1;//输出1 1,

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

/********************************************************************************************************************/


/********************************************************************************************************************/
//2016 6.1  wushengjun
//定义变量 控制图标闪烁。
//
/********************************************************************************************************************/

extern unsigned char flagLeft;  //左转


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

Canread::Canread()
{
}

void Canread::shutdownfd(int fd)
{
    close(fd);
}


 int Canread::initcan(int *retfd)
 {
     int s;
         int ret;
         struct sockaddr_can addr;
         struct ifreq ifr;



     srand(time(NULL));
         s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
         if (s < 0) {
             perror("socket PF_CAN failed");
             return 1;
         }
         else
         {
            *retfd = s;
         }

         strcpy(ifr.ifr_name, "can0");
         ret = ioctl(s, SIOCGIFINDEX, &ifr);
         if (ret < 0) {
             perror("ioctl failed");
             return 1;
         }

         addr.can_family = PF_CAN;
         addr.can_ifindex = ifr.ifr_ifindex;

         ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
         if (ret < 0) {
             perror("bind failed");
             return 1;
         }
     if (1) {
         struct can_filter filter[20];
         filter[0].can_id = 0x200 | CAN_EFF_FLAG;
         filter[0].can_mask = 0xFFF;

         filter[1].can_id = 0x20F | CAN_EFF_FLAG;
         filter[1].can_mask = 0xFFF;

         filter[2].can_id = 0x18ff01f6;
         filter[2].can_mask = 0xfff;

         filter[3].can_id = 0x18FF03F6;
         filter[3].can_mask = 0xfff;

         filter[4].can_id = 0x18FEEE00;
         filter[4].can_mask = 0xfff;

         filter[5].can_id = 0x18FEEF00;
         filter[5].can_mask = 0xfff;


         filter[6].can_id = 0x18FF04F6;
         filter[6].can_mask = 0xfff;


         filter[7].can_id = 0x18FECA00;
         filter[7].can_mask = 0xfff;


         ret = setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(filter));
         if (ret < 0) {
             perror("setsockopt failed");
             return 1;
         }
     }

 }


 void Canread::print_frame(struct can_frame *fr)
{
    int i;
    printf("%08x\n", fr->can_id & CAN_EFF_MASK);
    //printf("%08x\n", fr->can_id);
    printf("dlc = %d\n", fr->can_dlc);
    printf("data = ");
    for (i = 0; i < fr->can_dlc; i++)
        printf("%02x ", fr->data[i]);//
    printf("\n");
}


 void Canread::handle_err_frame(const struct can_frame *fr)
{
    if (fr->can_id & CAN_ERR_TX_TIMEOUT) {
        errout("CAN_ERR_TX_TIMEOUT");
    }
    if (fr->can_id & CAN_ERR_LOSTARB) {
        errout("CAN_ERR_LOSTARB");
        errcode(fr->data[0]);
    }
    if (fr->can_id & CAN_ERR_CRTL) {
        errout("CAN_ERR_CRTL");
        errcode(fr->data[1]);
    }
    if (fr->can_id & CAN_ERR_PROT) {
        errout("CAN_ERR_PROT");
        errcode(fr->data[2]);
        errcode(fr->data[3]);
    }
    if (fr->can_id & CAN_ERR_TRX) {
        errout("CAN_ERR_TRX");
        errcode(fr->data[4]);
    }
    if (fr->can_id & CAN_ERR_ACK) {
        errout("CAN_ERR_ACK");
    }
    if (fr->can_id & CAN_ERR_BUSOFF) {
        errout("CAN_ERR_BUSOFF");
    }
    if (fr->can_id & CAN_ERR_BUSERROR) {
        errout("CAN_ERR_BUSERROR");
    }
    if (fr->can_id & CAN_ERR_RESTARTED) {
        errout("CAN_ERR_RESTARTED");
    }
}

 int Canread::test_can_rw(int fd, int master)
{
    int ret, i;
    struct can_frame fr, frdup;
    struct timeval tv;
    fd_set rset;

    while (1) {
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        FD_ZERO(&rset);
        FD_SET(fd, &rset);
        printf("=====\r\n");
/*
        ret = select(fd+1, &rset, NULL, NULL, NULL);
        if (ret == 0) {
            myerr("select time out");
            return -1;
        }
*/
        printf("------------------------ \n");
        ret = read(fd, &frdup, sizeof(frdup));
        if (ret < sizeof(frdup)) {
            myerr("read failed");
            return -1;
        }
        if (frdup.can_id & CAN_ERR_FLAG) { /* 出错设备错误 */
            handle_err_frame(&frdup);
            myerr("CAN device error");
            continue;
        }


       //解析数据
       switch(frdup.can_id&CAN_EFF_MASK)
       {
            case 0x18ff01f6:
            speed = frdup.data[0]|frdup.data[1];


            /********************************************************************/
            //仪表值 有可以不用定义的变量，目前来说只是实验，等到正式产品的时候可以精简一下。
            /********************************************************************/
            //byte1 移位操作
            DC = (frdup.data[0]>>6)&0x01; //倒车信号（倒车+） 7,
            flagGL = DC;

            SK = (frdup.data[0]>>5)&0x01; //位置灯（位置灯+） 6,
            flagWidthlamp =SK;


            SouSa = (frdup.data[0]>>4)&0x01; //手刹指示灯（手刹指示灯+） 5,
             flagPark= SouSa;

            Zuozhuan = (frdup.data[0]>>3)&0x01; //左转向灯（左转向灯）4,
            flagLeft = Zuozhuan;

            Youzhuan = (frdup.data[0]>>2)&0x01; //右转向灯（右转向灯）3,
            flagRight = Youzhuan;

            YuanGuang = (frdup.data[0]>>1)&0x01; //远光指示灯（远光指示灯） 2,
            flagYG = YuanGuang;

            Jinguang = frdup.data[0]&0x01; //近光指示灯（近光指示灯） 1,
            flagJG = Jinguang;


            //byte2
            youshuifenli = (frdup.data[1]>>5)&0x01;  //油水分离 6,
            flagBattery = youshuifenli;

            fadongjiguzhang = (frdup.data[1]>>4)&0x01;//发动机故障 5,

            yure = (frdup.data[1]>>3)&0x01;  //预热 4,

            liangman = (frdup.data[1]>>2)&0x01; //粮满 3,

            KL = (frdup.data[1]>>1)&0x01;   //空滤报警开关（空滤-） 2,

            CongDian = frdup.data[1]&0x01;  //充电指示灯-  1,


            //byte3

            kg6  = (frdup.data[2]>>5)&0x01;//开关6 6，
            kg5  = (frdup.data[2]>>4)&0x01;//开关5 5，
            kg4 = (frdup.data[2]>>3)&0x01; //开关4 4,
            kg3 = (frdup.data[2]>>2)&0x01; //开关3 3,
            kg2 = (frdup.data[2]>>1)&0x01; //开关2 2,
            kg1 = (frdup.data[2])&0x01;    //开关1 1,

            break;


            //18FF02F6
       case 0x18FF02F6:
            out1 = ((frdup.data[0]>>1)<<1)|(frdup.data[0]&0x01);
            out2 = ((frdup.data[0]>>3)<<1)|((frdup.data[0]>>2)&0x01);
            out3 = ((frdup.data[0]>>5)<<1)|((frdup.data[0]>>4)&0x01);

            out4 = ((frdup.data[0]>>1)<<1)|(frdup.data[0]&0x01);
            out5 = ((frdup.data[0]>>3)<<1)|((frdup.data[0]>>2)&0x01);
            out6 = ((frdup.data[0]>>5)<<1)|((frdup.data[0]>>4)&0x01);

            break;
            //频率量
            //18FF03F6
       case 0x18FF03F6:
            shengyunqi = frdup.data[1]<<8|frdup.data[0];
            futuoqi  = frdup.data[3]<<8|frdup.data[2];
            zhouliuguntong = frdup.data[5]<<8|frdup.data[4];
            shisu = frdup.data[7]<<8|frdup.data[6];
            break;

           //模拟量 18FF04F6
       case 0x18FF04F6:
           YouLiang = frdup.data[0]; //油量（油量）
           if(frdup.data[0]>= 100)
           {
               frdup.data[0] = 100;//邮箱满了
               flagyouxiangman = 1;
               flagyouliangdi = 0;

           }
           else if(frdup.data[0]<10)
           {
                flagyouliangdi = 1; //油量低报警
                flagyouxiangman = 0;
           }
           else if((frdup.data[0]<100)&&(frdup.data[0]>10))
           {
                flagyouliangdi = 0;
                 flagyouxiangman = 0;
           }

           Yeyayouwen = frdup.data[1];//液压油油温（液压油油温）
           if(frdup.data[1]>90)
           {
                flagYeyayouwen = 1;
           }
           else
           {
                flagYeyayouwen = 0;
           }


           //MiJi  = frdup[2];// 暂时不定义。
           MiJi = frdup.data[4];
           MiJi = MiJi<<24;
           MiJi = (MiJi>>16)|frdup.data[3];
           MiJi = (MiJi<<8)|frdup.data[2];

           //LiCheng = frdup[];

           break;

           //发动机 数据
           //18FEEE00
       case 0x18FEEE00:
           SuiWen = frdup.data[0]; //水温；
           if(SuiWen > 90)
           {
                flagSW = 1;
           }
           else
           {
                flagSW = 0;
           }
           break;

           //发动机 数据
           //18FEEF00
       case 0x18FEEF00:
           jiyouyali = frdup.data[3]; //机油压力

           if(jiyouyali<1)
           {
                flagJY = 1;
           }
           else
           {
                flagJY = 0;
           }
           break;


           //发动机 数据
           //0CF00400
       case 0x0CF00400:
           fadongzhuansu = frdup.data[4]<<8|frdup.data[3]; //发动机转速
           break;

           //18FECA00
           //故障报文
           //memcpy  dai chuli
           //guzhangbaowen = frdup.data[]; //故障报文
        case 0x18FECA00:
           fmi = frdup.data[4]&0x1f; //Byte5 的 5-1 位为fmi 码；

           spn = frdup.data[4]&0xe0;
           spn = spn<<8;
           spn = spn|frdup.data[4];
           spn = spn<<8;
           spn = spn|frdup.data[3];

           break;


           //预热指示灯
           //18FEE400
       case 0x18FEE400:
           yurezhishideng = ((frdup.data[3]>>1)&0x01)|(frdup.data[3]&0x01);//18FEE400
            break;

           //小时计
           //18FEE500
       //case 18FEE500:
           //XiaoshiJi = frdup.data[]; //小时计
           // break;

            default:
            break;

       }


        print_frame(&frdup);

        memset(&frdup,0,sizeof(frdup));
/*
        ret = write(fd, &frdup, sizeof(frdup));
        if (ret < 0) {
            myerr("write failed");
            return -1;
        }
*/
        //sleep(2);


    }

    return 0;
}

