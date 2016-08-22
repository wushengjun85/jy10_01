#include "work.h"
#include "ui_work.h"

#include<QMouseEvent>
#include<QPainter>
#include<QString>
#include<QTime>
#include<QTimer>
#include<QDebug>

#include"camera_thread.h"
#include"hwlib/devlib.h"
#include <QtSql>
#include <QTextCodec>

/***************************************************************************************************************/
//2016.8.11  变量定义
//bool flaglanguage = false; //中英文切换标志变量。

//uchar numtmp = 0; //临时 测试所用。

extern  bool beep_flag;// 蜂鸣器标志




uint matchine[7] = {0}; //保存风机，复托器，升运器，等转速

extern ushort jiyouwendu;//机油温度

extern float xiaoshiJi_h;//小时计


uchar j_w;
uchar jflag_w;
ushort mm_w;
uchar jjjflag_w;
ushort  mybufflag_w[312];//15
ushort  myindex_w[312];//15


unsigned char  countBuff_w = 0;



//18FECA00
//故障报文
//ulong guzhangbaowen; //故障报文
extern uint  spn;//spn 码
extern uchar fmi;//fmi 码

extern uint  spn2;//spn 码
extern uchar fmi2;//fmi 码

extern uint  spn3;//spn 码
extern uchar fmi3;//fmi 码

extern uint  spn4;//spn 码
extern uchar fmi4;//fmi 码
/***************************************************************************************************************/



bool ok = true;

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
//extern ulong guzhangbaowen; //故障报文
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

/********************************************************************************************************************/
//故障码 标志定义
//用于数据库存储

extern uchar gzm_001;//空调压缩机开路
extern uchar gzm_002;//空调压缩机对电源短路
extern uchar gzm_003;//空调压缩机对地短路
extern uchar gzm_004;//油门与刹车信号不可信
extern uchar gzm_005;//空气质量流量传感器电压超上限
extern uchar gzm_006;//空气质量流量传感器电压超下限
extern uchar gzm_007;//进气加热常开故障
extern uchar gzm_008;//油门踏板1与油门踏板2的两倍的信号关系不可信
extern uchar gzm_009;//油门踏板1电压值高出上限门槛值
extern uchar gzm_010;//油门踏板1电压值低于下限门槛值





extern uchar gzm_011;//油门踏板2与油门踏板1的1/2的信号关系不可信
extern uchar gzm_012;//油门踏板2电压值高出上限门槛值
extern uchar gzm_013;//油门踏板2电压值低于下限门槛值
extern uchar gzm_014;//大气压力传感器信号不可信
extern uchar gzm_015;//大气压力传感器电压高出上限门槛
extern uchar gzm_016;//大气压力传感器电压低于下限门槛
extern uchar gzm_017;//进气加热器开路
extern uchar gzm_018;//进气加热器对电源开路
extern uchar gzm_019;//进气加热器对地开路
extern uchar gzm_020;//电池电压原始值低于下限门槛

extern uchar gzm_021;//电池电压原始值超出上限门槛
extern uchar gzm_022;//进气压力传感器信号不可信
extern uchar gzm_023;//进气压力传感器电压超出上限门槛值
extern uchar gzm_024;//进气压力传感器电压低于下限门槛值
extern uchar gzm_025;//巡航控制要求的识别错误，使得故障灯常亮
extern uchar gzm_026;//制动踏板踩下前，巡航控制抑制错误
extern uchar gzm_027;//刹车信号不可信
extern uchar gzm_028;//刹车信号错误
extern uchar gzm_029;//冷却水温在一定时间内上升幅度没有达到最小值
extern uchar gzm_030;//冷却水温在一定时间内没有达到最小值

extern uchar gzm_031;//水温信号不可用
extern uchar gzm_032;//发动机转速信号不可用
extern uchar gzm_033;//离合器状态信号不可用
extern uchar gzm_034;//OBD扭矩限制激活错误
extern uchar gzm_035;//冷启动指示灯开路
extern uchar gzm_036;//冷启动指示灯对电源短路
extern uchar gzm_037;//冷启动指示灯对地短路
extern uchar gzm_038;//冷却水温度与机油温度信号不可信
extern uchar gzm_039;//水温传感器工作正常但水温超出门槛值
extern uchar gzm_040;//冷却水温度传感器电压超出上限门槛

extern uchar gzm_041;//冷却水温度传感器电压低于下限门槛
extern uchar gzm_042;//车下启动/停止按钮卡住
extern uchar gzm_043;//只有凸轮轴信号，进入跛形回家状态
extern uchar gzm_044;//凸轮轴信号缺失
extern uchar gzm_045;//凸轮轴周期错误
extern uchar gzm_046;//凸轮轴同步错误
extern uchar gzm_047;//凸轮轴与曲轴同步错误
extern uchar gzm_048;//曲轴信号缺失
extern uchar gzm_049;//曲轴同步错误
extern uchar gzm_050;//曲轴齿数错误

extern uchar gzm_051;//曲轴齿周期错误
extern uchar gzm_052;//齿数与凸轮轴信号偏差超出门槛值
extern uchar gzm_053;//发动机转速超限
extern uchar gzm_054;//发动机转速信号开路
extern uchar gzm_055;//发动机转速信号对电源短路
extern uchar gzm_056;//发动机转速信号对地短路
extern uchar gzm_057;//排气制动蝶阀开路
extern uchar gzm_058;//排气制动蝶阀对电源短路
extern uchar gzm_059;//排气制动蝶阀对地短路
extern uchar gzm_060;//风扇执行器（PWM波）开路

extern uchar gzm_061;//风扇执行器(PWM波)对电源短路
extern uchar gzm_062;//风扇执行器(PWM波)对地短路
extern uchar gzm_063;//风扇执行器(数字信号)开路
extern uchar gzm_064;//风扇执行器(数字信号)对电源短路
extern uchar gzm_065;//风扇执行器(数字信号)对地短路
extern uchar gzm_066;//冷却风扇速度高出上限门槛值
extern uchar gzm_067;//冷却风扇速度低于下限门槛值
extern uchar gzm_068;//燃油加热继电器(数字信号)开路
extern uchar gzm_069;//燃油加热继电器(数字信号)对电源短路
extern uchar gzm_070;//燃油加热继电器(数字信号)对地短路

extern uchar gzm_071;//燃油加热继执行器(PWM波)对地短路
extern uchar gzm_072;//燃油加热继执行器(PWM波)对电源短路
extern uchar gzm_073;//燃油加热继执行器(PWM波)开路
extern uchar gzm_074;//燃油升压执行器开路
extern uchar gzm_075;//燃油升压执行器对电源短路
extern uchar gzm_076;//燃油升压执行器对地短路
extern uchar gzm_077;//油中有水传感器检测到油中有水
extern uchar gzm_078;//总线接收油门信号超限
extern uchar gzm_079;//CAN接收帧CM1数据量错误
extern uchar gzm_080;//CAN接收帧CM1超时错误

extern uchar gzm_081;//CAN接收帧DashDspl数据量错误
extern uchar gzm_082;//CAN接收帧DashDspl超时错误
extern uchar gzm_083;//CAN接收帧DEC1数据量错误
extern uchar gzm_084;//DEC1报文接收超时
extern uchar gzm_085;//CAN接收帧EBC1数据长度错误
extern uchar gzm_086;//CAN接收帧EBC1超时错误
extern uchar gzm_087;//数据长度错误
extern uchar gzm_088;//超时错误
extern uchar gzm_089;//CAN接收帧EGF1数据量错误
extern uchar gzm_090;//CAN接收帧EGF1超时错误

extern uchar gzm_091;//CAN接收帧EngTemp2数据量错误
extern uchar gzm_092;//CAN接收帧EngTemp2超时错误
extern uchar gzm_093;//CAN接收帧ERC1DR数据量错误
extern uchar gzm_094;//CAN接收帧ERC1DR超时错误
extern uchar gzm_095;//ETC1报文数据长度错误
extern uchar gzm_096;//ETC1报文超时错误
extern uchar gzm_097;//CAN接收帧ETC2数据量错误
extern uchar gzm_098;//CAN接收帧ETC2超时错误
extern uchar gzm_099;//CAN接收帧ETC7数据量错误
extern uchar gzm_100;//CAN接收帧ETC7报文接收超时

extern uchar gzm_101;//CAN接收帧HRVD数据量错误
extern uchar gzm_102;//CAN接收帧HRVD超时错误
extern uchar gzm_103;//总线接收远程油门信号超限
extern uchar gzm_104;//RxCCVS报文数据长度错误
extern uchar gzm_105;//RxCCVS报文接收超时
extern uchar gzm_106;//CAN接收帧TRF1数据量错误
extern uchar gzm_107;//CAN接收帧TRF1超时错误
extern uchar gzm_108;//CAN接收帧TSC1AE数据量错误
extern uchar gzm_109;//CAN接收帧TSC1AE超时错误
extern uchar gzm_110;//CAN接收帧TSC1AR数据量错误

extern uchar gzm_111;//CAN接收帧TSC1AR超时错误
extern uchar gzm_112;//CAN接收帧TTSC1DE数据量错误
extern uchar gzm_113;//CAN接收帧TTSC1DE超时错误
extern uchar gzm_114;//CAN接收帧TSC1DR数据量错误
extern uchar gzm_115;//CAN接收帧TSC1DR超时错误
extern uchar gzm_116;//CANTOTSC1PE数据量错误
extern uchar gzm_117;//CANTOTSC1PE通信错误
extern uchar gzm_118;//CANTOTSC1TE数据量错误
extern uchar gzm_119;//CANTOTSC1TE超时错误
extern uchar gzm_120;//CAN TOTSC1TR数据量错误

extern uchar gzm_121;//CAN TOTSC1TR超时错误
extern uchar gzm_122;//CANTOTSC1VE 数据量错误
extern uchar gzm_123;//CANTOTSC1VE超时错误
extern uchar gzm_124;//CANTOTSC1VR 数据量错误
extern uchar gzm_125;//CANTOTSC1VR 超时错误
extern uchar gzm_126;//燃油温度传感器电压超出上限门槛值
extern uchar gzm_127;//燃油温度传感器电压超出下限门槛值
extern uchar gzm_128;//档位提升间隙时间过长
extern uchar gzm_129;//(油中有水灯)指示灯短路
extern uchar gzm_130;//(油中有水灯)指示灯电源短路


extern uchar gzm_131;//(油中油水灯)指示灯地短路
extern uchar gzm_132;//高压测试错误
extern uchar gzm_133;//EEPROM读错误
extern uchar gzm_134;//EEPROM写错误
extern uchar gzm_135;//进气温度传感器电压超出上限门槛值
extern uchar gzm_136;//进气温度传感器电压低于下限门槛值
extern uchar gzm_137;//喷孔磨损程度持续20次大于20%
extern uchar gzm_138;//喷孔磨损程度持续500ms介于5%到20%之间
extern uchar gzm_139;//INJ driver IC初始化版本号错误
extern uchar gzm_140;//INJ driver IC上电初始化错误

extern uchar gzm_141;//喷孔磨损超过20%故障
extern uchar gzm_142;//喷孔磨损在0～20%故障
extern uchar gzm_143;//INJ driver IC再次上电错误
extern uchar gzm_144;//喷油器1高端与电源短路
extern uchar gzm_145;//喷油器1高端与地短路
extern uchar gzm_146;//喷油器1低端与电源短路
extern uchar gzm_147;//喷油器1低端与地短路
extern uchar gzm_148;//喷油器1开路
extern uchar gzm_149;//1缸喷油器错误
extern uchar gzm_150;//同BANK中1缸和其他缸或者与弱电源短路

extern uchar gzm_151;//1缸喷油器对电源短路
extern uchar gzm_152;//1缸喷油器对地短路
extern uchar gzm_153;//喷油器1高低端短路
extern uchar gzm_154;//喷油器2高端与电源短路
extern uchar gzm_155;//喷油器2高端与地短路
extern uchar gzm_156;//喷油器2低端与电源短路
extern uchar gzm_157;//喷油器2低端与地短路
extern uchar gzm_158;//喷油器2开路
extern uchar gzm_159;//2缸喷油器错误
extern uchar gzm_160;//同Bank中2缸和其他缸开路或者与弱电源短路

extern uchar gzm_161;//2缸喷油器对电源短路
extern uchar gzm_162;//2缸喷油器对地短路
extern uchar gzm_163;//喷油器2高低端短路
extern uchar gzm_164;//喷油器3高端与电源短路
extern uchar gzm_165;//喷油器3高端与地短路
extern uchar gzm_166;//喷油器3低端与电源短路
extern uchar gzm_167;//喷油器3低端与地短路
extern uchar gzm_168;//喷油器3开路
extern uchar gzm_169;//3缸喷油器错误
extern uchar gzm_170;//同Bank中3缸和其他缸开路或者与弱电电源短路

extern uchar gzm_171;//3缸喷油器对电源短路
extern uchar gzm_172;//3缸喷油器对地短路
extern uchar gzm_173;//喷油器3高低端短路
extern uchar gzm_174;//喷油器4高端与电源短路
extern uchar gzm_175;//喷油器4高端与地短路
extern uchar gzm_176;//喷油器4低端与电源短路
extern uchar gzm_177;//喷油器4低端与地短路
extern uchar gzm_178;//喷油器4开路
extern uchar gzm_179;//4缸喷油器错误
extern uchar gzm_180;//同Bank中4缸和其他缸开路或者与弱电电源短路

extern uchar gzm_181;//4缸喷油器对电源短路
extern uchar gzm_182;//4缸喷油器对地短路
extern uchar gzm_183;//喷油器4高低端短路
extern uchar gzm_184;//喷油器5高端与电源短路
extern uchar gzm_185;//喷油器5高端与地短路
extern uchar gzm_186;//喷油器5低端与电源短路
extern uchar gzm_187;//喷油器5低端与地短路
extern uchar gzm_188;//喷油器5开路
extern uchar gzm_189;//5缸喷油器错误
extern uchar gzm_190;//同Bank中5缸和其他缸开路或者与弱电电源短路



extern uchar gzm_191;//5缸喷油器对电源短路
extern uchar gzm_192;//5缸喷油器对地短路
extern uchar gzm_193;//喷油器5高低端短路
extern uchar gzm_194;//喷油器6高端与电源短路
extern uchar gzm_195;//喷油器6高端与地短路
extern uchar gzm_196;//喷油器6低端与电源短路
extern uchar gzm_197;//喷油器6低端与地短路
extern uchar gzm_198;//喷油器6开路
extern uchar gzm_199;//6缸喷油器错误
extern uchar gzm_200;//同Bank中6缸和其他缸开路或者与弱电电源短路

//

extern uchar gzm_201;//6缸喷油器对电源短路
extern uchar gzm_202;//6缸喷油器对地短路
extern uchar gzm_203;//喷油器6高低端短路
extern uchar gzm_204;//燃油计量器开路
extern uchar gzm_205;//燃油计量器电源短路
extern uchar gzm_206;//燃油计量器对地短路
extern uchar gzm_207;//巡航信号不可靠(无效开关组合)
extern uchar gzm_208;//OBD灯开路
extern uchar gzm_209;//OBD灯与电源短路
extern uchar gzm_210;//OBD灯与地短路


extern uchar gzm_211;//1缸失火
extern uchar gzm_212;//10缸失火
extern uchar gzm_213;//11缸失火
extern uchar gzm_214;//12缸失火
extern uchar gzm_215;//2缸失火
extern uchar gzm_216;//3缸失火
extern uchar gzm_217;//4缸失火
extern uchar gzm_218;//5缸失火
extern uchar gzm_219;//6缸失火
extern uchar gzm_220;//7缸失火

extern uchar gzm_221;//8缸失火
extern uchar gzm_222;//9缸失火
extern uchar gzm_223;//失火总缸数超限
extern uchar gzm_224;//多态开关信号不可信
extern uchar gzm_225;//多态开关电压超上限
extern uchar gzm_226;//多态开关电压超下限
extern uchar gzm_227;//机油液位传感器信号不可靠
extern uchar gzm_228;//机油液位传感器电压电压超出上限
extern uchar gzm_229;//机油液位传感器电压电压超出下限
extern uchar gzm_230;//机油压力过低

extern uchar gzm_231;//机油压力过高或机油温度信号不可靠
extern uchar gzm_232;//机油压力传感器电压电压超出上限
extern uchar gzm_233;//机油压力传感器电压电压超出下限
extern uchar gzm_234;//机油温度传感器信号不可靠
extern uchar gzm_235;//机油温度传感器电压超出上限门槛值
extern uchar gzm_236;//机油温度传感器电压低于下限门槛值
extern uchar gzm_237;//机油温度与冷却水温度信号不可信
extern uchar gzm_238;//PCV阀开路
extern uchar gzm_239;//PCV阀对电源短路
extern uchar gzm_240;//PCV阀对地短路


//248 ，249 要注意一下
extern uchar gzm_241;//压力波动时共轨泻压阀未打开
extern uchar gzm_242;//共轨泻压阀打开次数超出技术要求的最大值
extern uchar gzm_243;//共轨泻压阀打开
extern uchar gzm_244;//限压阀打开时间超过限制
extern uchar gzm_245;//轨压传感器电压超出最大偏差
extern uchar gzm_246;//轨压传感器电压低于最小偏差
extern uchar gzm_247;//轨压传感器电压超出上限门槛值
extern uchar gzm_248;//中断采集方式轨压传感器电压超出上限门槛值
extern uchar gzm_249;//轨压传感器电压低于下限门槛值
extern uchar gzm_250;//中断采集方式轨压传感器电压低于下限门槛值

extern uchar gzm_251;//轨压偏差超出上限门槛值
extern uchar gzm_252;//燃油计量器中的油量超过门槛值
extern uchar gzm_253;//轨压偏差超出门槛值并且燃油计量器中的油量超过门槛值
extern uchar gzm_254;//轨压偏差超出上限门槛值并且喷油量超限
extern uchar gzm_255;//轨压偏差低于下限门槛值并且喷油量低于门槛值
extern uchar gzm_256;//轨压峰值低于下限门槛值
extern uchar gzm_257;//轨压峰值超出上限门槛值
extern uchar gzm_258;//轨压下降过快
extern uchar gzm_259;//超速模式下的油量计量单元设定不可信
extern uchar gzm_260;//低怠速下油量计量单元监控器错误

extern uchar gzm_261;//远程油门踏板1输出电压值超出上限
extern uchar gzm_262;//远程油门踏板1输出电压值低于下限
extern uchar gzm_263;//远程油门踏板2输出电压值超出上限
extern uchar gzm_264;//远程油门踏板2输出电压值低于下限
extern uchar gzm_265;//传感器电源1电压超出上限门槛值
extern uchar gzm_266;//传感器电源1电压低于下限门槛值
extern uchar gzm_267;//传感器电源2电压超出上限门槛值
extern uchar gzm_268;//传感器电源2电压低于下限门槛值
extern uchar gzm_269;//传感器电源3电压超出上限门槛值
extern uchar gzm_270;//传感器电源3电压低于下限门槛值

extern uchar gzm_271;//空滤更换
extern uchar gzm_272;//燃油沥青器更换
extern uchar gzm_273;//锁车且执行锁车模式1
extern uchar gzm_274;//锁车且执行锁车模式2
extern uchar gzm_275;//机油更换
extern uchar gzm_276;//机油滤清器更换
extern uchar gzm_277;//起动电机继电器低端电源短路
extern uchar gzm_278;//起动电机继电器低端对地短路
extern uchar gzm_279;//起动电机继电器开路
extern uchar gzm_280;//T50接通时间超限

extern uchar gzm_281;//ECU 温度传感器电压低于下限门槛值
extern uchar gzm_282;//ECU 温度传感器电压超出上限门槛值
extern uchar gzm_283;//尿素回流管(泵到箱)加热继电器开路
extern uchar gzm_284;//尿素回流管(泵到箱)加热继电器对电源短路
extern uchar gzm_285;//尿素回流管(泵到箱)加热继电器对地短路
extern uchar gzm_286;//尿素压力管(泵到嘴)加热继电器开路
extern uchar gzm_287;//尿素压力管(泵到嘴)加热继电器对电源短路
extern uchar gzm_288;//尿素压力管(泵到嘴)加热继电器对地短路
extern uchar gzm_289;//尿素加热主继电器开路
extern uchar gzm_290;//尿素加热主继电器对电源短路

extern uchar gzm_291;//尿素加热主继电器对地短路
extern uchar gzm_292;//尿素吸液管(箱到泵)加热继电器开路
extern uchar gzm_293;//尿素吸液管(箱到泵)加热继电器对电源短路
extern uchar gzm_294;//尿素吸液管(箱到泵)加热继电器对地短路
extern uchar gzm_295;//尿素箱水加热电磁阀开路
extern uchar gzm_296;//尿素箱水加热电磁阀对电源短路
extern uchar gzm_297;//尿素箱水加热电磁阀对地短路
extern uchar gzm_298;//车速1高于最大门槛值
extern uchar gzm_299;//车速1月喷油量及发动机转速不可信
extern uchar gzm_300;//车速3信号脉宽超过上限门槛值

extern uchar gzm_301;//车速3信号脉宽低于下限门槛值
extern uchar gzm_302;//车速信号平均周期小于门槛值
extern uchar gzm_303;//报警灯开路
extern uchar gzm_304;//报警灯电源短路
extern uchar gzm_305;//报警灯对地短路
extern uchar gzm_306;//油中有水传感器电压原始值超出上限门槛
extern uchar gzm_307;//油中有水传感器电压原始值低于下限门槛
extern uchar gzm_308;//CAN 通讯错误
extern uchar gzm_309;//远程油门2倍关系不可信
extern uchar gzm_310;//远程油门与刹车可信性校验

extern uchar gzm_311;//key报文故障
extern uchar gzm_312;//key报文超时
/********************************************************************************************************************/







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
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);//删除 最小化、最大化、关闭按钮

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
     ui->show_label1->resize(img->width(),img->height());
     ui->show_label1->resize(1024,600);
     ui->show_label1->move(0,0);
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

        ui->lcdNumber_2->display(dateStr1);//dateStr1
        ui->lcdNumber->display(timeStr1);
    /**************************************************************************************************************/

    /**************************************************************************************************************/
        //测试摄像头直接采集图像并显示
        //
        #if 0
            if ((ok == true)&&(numjy == 0))
            {
                 numjy = 1;
                 emit camerastartsignal();
            }
            else if ((ok == false)&&(numjy==1))
            {

                numjy = 0;
                qDebug()<<"stopcamera::"<<ok<<DC<<endl;
                //emit stopcamerasignal();
            }

        #endif

   /************************************************************************************************/

            //2016.8.8  定义数值

            #if 1
                ui->label->setText("6"); //r/min

                ui->label_2->setText("88");// k/mh
                ui->label_3->setText( QString("%1").arg(xiaoshiJi_h));

                ui->label_4->setText(QString::number(SuiWen));//水温
                ui->label_5->setText(QString::number(Yeyayouwen));//液压油油温（液压油油温）
                ui->label_6->setText(QString::number(jiyouwendu));//机油温度
                ui->label_7->setText(QString::number(jiyouyali));//机油压力
                ui->label_8->setText(QString::number(guoqiaozhuansu));//过桥转速
                ui->label_9->setText(QString::number(fengjizhuansu));//风机转速
                ui->label_10->setText(QString::number(futuoqi));//复脱器转速
                ui->label_11->setText(QString::number(shengyunqi));//升运器转速
                ui->label_12->setText(QString::number(qiesuiqizhuansu));//切碎器转速
                ui->label_13->setText(QString::number(tuoliguntong));//脱粒滚筒转速
                ui->label_14->setText(QString::number(fenliguntong));//分离滚筒转速

            #endif

                /************************************************************************************************/
                    if((DC == 0)&&(wsjtmpflag == 1)) //返回主界面。
                    {
                        //emit back();
                        QMouseEvent* pressdialog=new QMouseEvent(QEvent::MouseButtonPress,QPoint(2,2), Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                        QApplication::postEvent(ui->pushButton,pressdialog);
                        QMouseEvent* releasedialog=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(2,2),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                        QApplication::postEvent(ui->pushButton,releasedialog);
                        wsjtmpflag = 0;
                    }

                /************************************************************************************************/




                //加载上方图标 闪烁用到
                //zuo zhuandeng
//                QPainter paintLeft(this);
//                QPixmap pixLeft;


            /************************************************************************************************/
            //闪烁不同步问题解决办法。
            //利用消息队列 和 for 循环解决。
            //2016.7.25

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


                        //读取数据库信息
                        //
                        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示

                        QSqlDatabase db;
                        if(QSqlDatabase::contains("qt_sql_default_connection"))
                          db = QSqlDatabase::database("qt_sql_default_connection");
                        else
                          db = QSqlDatabase::addDatabase("QSQLITE");

                       db.setDatabaseName("my.db");
                       if (!db.open())
                       {
                           qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
                       }
                       QSqlQuery query;
                    //   bool ok = query.exec("CREATE TABLE IF NOT EXISTS  myjy10 (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    //                                      "name VARCHAR(20) NOT NULL,"
                    //                                      "age INTEGER NULL)");
#if 0
                       bool ok = query.exec("create table myjy10(id INTEGER,name varchar,age INTEGER)");
                       if (ok)
                       {
                           qDebug()<<"ceate table partition success"<<endl;
                       }
                       else
                       {
                           qDebug()<<"ceate table partition failed"<<endl;
                       }
#endif
                            query.prepare("INSERT INTO myjy10 (id, name, age) VALUES (:id, :name, :age)");

                            uchar i = 0;
                            query.exec("select id, name, age from myjy10");
                            while (query.next())
                            {

                               //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
                                //qDebug()<<query.value(2).toInt();

                                matchine[i++] = query.value(2).toInt();
                            }
#if 0

                            i = 0;
                            for (i = 0; i < 7; i++)
                                {
                                    qDebug()<<matchine[i]<<endl;
                                }
                            i = 0;
#endif
                            query.exec(QObject::tr("drop myjy10"));


        /*******************************************************************/
        //比较can传过来的值 ，实现闪烁
                            if(tuoliguntong<matchine[0])//脱粒滚筒转速
                            {
                                pixShanshuo.load("./imagejy/tlgt.png");//11.jpg
                                paintShanshuo.drawPixmap(740,430,113,21,pixShanshuo);
                            }

                            if(qiesuiqizhuansu<matchine[1])//切碎器转速
                            {
                                pixShanshuo.load("./imagejy/qsq.png");//11.jpg
                                paintShanshuo.drawPixmap(740,349,94,21,pixShanshuo);
                            }

                            if(fengjizhuansu<matchine[2])//风机转速
                            {
                                pixShanshuo.load("./imagejy/fj.png");//11.jpg
                                paintShanshuo.drawPixmap(740,165,75,21,pixShanshuo);
                            }
                            if(futuoqi<matchine[3])//复脱器堵塞转速
                            {
                                pixShanshuo.load("./imagejy/ftq.png");//11.jpg
                                paintShanshuo.drawPixmap(740,250,94,21,pixShanshuo);
                            }
                            if(shengyunqi<matchine[4])//升运器堵塞转速
                            {
                                pixShanshuo.load("./imagejy/syq.png");//11.jpg
                                paintShanshuo.drawPixmap(740,299,93,22,pixShanshuo);
                            }
                            if(guoqiaozhuansu<matchine[5])//过桥转速
                            {
                                pixShanshuo.load("./imagejy/gqzs.png");//11.jpg
                                paintShanshuo.drawPixmap(740,118,75,21,pixShanshuo);
                            }
                            if(fenliguntong<matchine[6])//分离滚筒转速
                            {
                                pixShanshuo.load("./imagejy/flgt.png");//11.jpg
                                paintShanshuo.drawPixmap(740,479,113,21,pixShanshuo);
                            }


        /*******************************************************************/



                        break;
                    }//end if(1)

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
                   // if (flagyouxiangman|flagyouliangdi)//油量
                    if (1)//油量
                    {
                        switch(flagyouxiangman)
                        {

                        case 0:
                            pixShanshuo.load("./imagejy/yl00.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;

                        case 1:
                            pixShanshuo.load("./imagejy/yl01.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;

                        case 2:
                            pixShanshuo.load("./imagejy/yl02.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;

                        case 3:
                            pixShanshuo.load("./imagejy/yl03.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        case 4:
                            pixShanshuo.load("./imagejy/yl04.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        case 5:
                            pixShanshuo.load("./imagejy/yl05.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        case 6:
                            pixShanshuo.load("./imagejy/yl06.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        case 7:
                            pixShanshuo.load("./imagejy/yl07.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        case 8:
                            pixShanshuo.load("./imagejy/yl08.png");//14.jpg
                            paintShanshuo.drawPixmap(106,225,166,26,pixShanshuo);
                            break;
                        }

                    }//end off //油量格数

                }//endof 闪烁

#if 0
                //添加蜂鸣器报警
                if(beep_flag)
                {

                    if(flagBattery|flagSW|flagLCM|flagFDJYR|flagGL|flagyouxiangman|flagyouliangdi|flagYeyayouwen|flagFDJGZ)
                    {
                        beep_on();//打开蜂鸣器
                    }
                    else
                    {
                        beep_off();//关闭蜂鸣器
                    }
                }
                else
                {
                    beep_off();
                }
#endif



                /*****************************************************************************************************/
                //故障码解析

                 if((spn==1351)&&(fmi==5))//空调压缩机开路
                 {
                    gzm_001 = 1;
                 }

                 if((spn==1351)&&(fmi==3)) //空调压缩机对电源短路
                 {
                     gzm_002 = 1;

                 }

                 if((spn==1351)&&(fmi==4))//空调压缩机对地短路
                 {
                    gzm_003 = 1;
                 }

                 if((spn==91)&&(fmi==7)) //油门与刹车信号不可信
                 {
                     gzm_004 = 1;

                 }

                 if((spn==132)&&(fmi==3))//空气质量流量传感器电压超上限
                 {
                    gzm_005 = 1;
                 }

                 if((spn==132)&&(fmi==4)) //空气质量流量传感器电压超下限
                 {
                     gzm_006 = 1;

                 }

                 if((spn==2898)&&(fmi==7))//007进气加热常开故障
                 {
                    gzm_007 = 1;
                 }

                 if((spn==520252)&&(fmi==2)) //008油门踏板1与油门踏板2的两倍的信号关系不可信
                 {
                     gzm_008 = 1;

                 }

                 if((spn==91)&&(fmi==3))//009油门踏板1电压值高出上限门槛值
                 {
                    gzm_009 = 1;
                 }

                 if((spn== 91)&&(fmi== 4))//10油门踏板1电压值低于下限门槛值
                 {
                    gzm_010 = 1;
                 }

                 if((spn== 520252)&&(fmi== 2))//11 油门踏板2与油门踏板1的1/2的信号关系不可信
                 {
                    gzm_011 = 1;
                 }

                 if((spn== 29)&&(fmi== 3))//12 油门踏板2电压值高出上限门槛值
                 {
                    gzm_012 = 1;
                 }

                 if((spn== 29)&&(fmi== 4))//13 油门踏板2电压值低于下限门槛值
                 {
                    gzm_013 = 1;
                 }

                 if((spn== 102)&&(fmi== 2))//14 大气压力传感器信号不可信
                 {
                    gzm_014 = 1;
                 }

                 if((spn== 108)&&(fmi== 3))//15 大气压力传感器电压高出上限门槛
                 {
                    gzm_015 = 1;
                 }

                 if((spn== 108)&&(fmi== 4))//16 大气压力传感器电压低于下限门槛
                 {
                    gzm_016 = 1;
                 }

                 if((spn== 2898)&&(fmi== 5))//17进气加热器开路
                 {
                    gzm_017 = 1;
                 }

                 if((spn== 2898)&&(fmi== 3))//18 进气加热器对电源开路
                 {
                    gzm_018 = 1;
                 }

                 if((spn== 2898)&&(fmi== 4))//19
                 {
                    gzm_019 = 1;
                 }

                 if((spn== 168)&&(fmi== 4))//20
                 {
                    gzm_020 = 1;
                 }


                 if((spn== 168)&&(fmi== 3))//21
                 {
                    gzm_021 = 1;
                 }

                 if((spn== 102)&&(fmi== 2))//22
                 {
                    gzm_022 = 1;
                 }

                 if((spn== 102)&&(fmi== 3))//
                 {
                    gzm_023 = 1;
                 }

                 if((spn== 102)&&(fmi== 4))//
                 {
                    gzm_024 = 1;
                 }

                 if((spn== 597)&&(fmi== 11))//
                 {
                    gzm_025 = 1;
                 }

                 if((spn== 597)&&(fmi== 7))//
                 {
                    gzm_026 = 1;
                 }

                 if((spn== 597)&&(fmi== 2))//
                 {
                    gzm_027 = 1;
                 }

                 if((spn== 597)&&(fmi== 19))//
                 {
                    gzm_028 = 1;
                 }

                 if((spn== 110)&&(fmi== 18))//
                 {
                    gzm_029 = 1;
                 }

                 if((spn== 110)&&(fmi== 17))//
                 {
                    gzm_030 = 1;
                 }

                 if((spn== 110)&&(fmi== 2))//
                 {
                    gzm_031 = 1;
                 }

                 if((spn== 190)&&(fmi== 2))//
                 {
                    gzm_032 = 1;
                 }


                 if((spn== 598)&&(fmi== 2))//
                 {
                    gzm_033 = 1;
                 }

                 if((spn== 520198)&&(fmi== 11))//
                 {
                    gzm_034 = 1;
                 }


                 if((spn== 626)&&(fmi== 5))//
                 {
                    gzm_035 = 1;
                 }
                 if((spn== 626)&&(fmi== 3))//
                 {
                    gzm_036 = 1;
                 }
                 if((spn== 626)&&(fmi== 4))//
                 {
                    gzm_037 = 1;
                 }
                 if((spn== 110)&&(fmi== 2))//
                 {
                    gzm_038 = 1;
                 }
                 if((spn== 110)&&(fmi== 15))//
                 {
                    gzm_039 = 1;
                 }
                 if((spn== 110)&&(fmi== 3))//
                 {
                    gzm_040 = 1;
                 }
                 if((spn== 110)&&(fmi== 4))//
                 {
                    gzm_041 = 1;
                 }
                 if((spn== 520203)&&(fmi== 5))//
                 {
                    gzm_042 = 1;
                 }
                 if((spn== 4203)&&(fmi== 13))//
                 {
                    gzm_043 = 1;
                 }
                 if((spn== 4201)&&(fmi== 12))//
                 {
                    gzm_044 = 1;
                 }
                 if((spn== 4201)&&(fmi== 2))//
                 {
                    gzm_045 = 1;
                 }
                 if((spn== 4201)&&(fmi== 11))//
                 {
                    gzm_046 = 1;
                 }
                 if((spn== 4201)&&(fmi== 13))//
                 {
                    gzm_047 = 1;
                 }
                 if((spn== 4203)&&(fmi== 12))//
                 {
                    gzm_048 = 1;
                 }
                 if((spn== 4203)&&(fmi== 3))//
                 {
                    gzm_049 = 1;
                 }
                 if((spn== 4203)&&(fmi== 4))//
                 {
                    gzm_050 = 1;
                 }

                 if((spn== 4203)&&(fmi== 2))//
                 {
                    gzm_051 = 1;
                 }

                 if((spn== 4201)&&(fmi== 14))//
                 {
                    gzm_052 = 1;
                 }
                 if((spn== 1769)&&(fmi== 11))//
                 {
                    gzm_053 = 1;
                 }
                 if((spn== 1623)&&(fmi== 5))//
                 {
                    gzm_054 = 1;
                 }
                 if((spn== 1623)&&(fmi== 3))//
                 {
                    gzm_055 = 1;
                 }
                 if((spn== 1623)&&(fmi== 4))//
                 {
                    gzm_056 = 1;
                 }
                 if((spn== 520208)&&(fmi== 5))//
                 {
                    gzm_057 = 1;
                 }
                 if((spn== 520208)&&(fmi== 3))//
                 {
                    gzm_058 = 1;
                 }
                 if((spn== 520208)&&(fmi== 4))//
                 {
                    gzm_059 = 1;
                 }
                 if((spn== 4815)&&(fmi== 7))//
                 {
                    gzm_060 = 1;
                 }
                 if((spn== 4815)&&(fmi== 9))//
                 {
                    gzm_061 = 1;
                 }

                 if((spn== 4815)&&(fmi== 10))//
                 {
                    gzm_062 = 1;
                 }
                 if((spn== 4815)&&(fmi== 5))//
                 {
                    gzm_063 = 1;
                 }
                 if((spn== 4815)&&(fmi== 3))//
                 {
                    gzm_064 = 1;
                 }
                 if((spn== 4815)&&(fmi== 4))//
                 {
                    gzm_065 = 1;
                 }
                 if((spn== 1639)&&(fmi== 3))//
                 {
                    gzm_066 = 1;
                 }
                 if((spn== 1639)&&(fmi== 4))//
                 {
                    gzm_067 = 1;
                 }
                 if((spn== 520261)&&(fmi== 5))//
                 {
                    gzm_068 = 1;
                 }
                 if((spn== 520261)&&(fmi== 3))//
                 {
                    gzm_069 = 1;
                 }
                 if((spn== 520261)&&(fmi== 4))//
                 {
                    gzm_070 = 1;
                 }
                 if((spn== 520261)&&(fmi== 10))//
                 {
                    gzm_071 = 1;
                 }
                 if((spn== 520261)&&(fmi== 9))//
                 {
                    gzm_072 = 1;
                 }
                 if((spn== 520261)&&(fmi== 7))//
                 {
                    gzm_073 = 1;
                 }
                 if((spn== 95)&&(fmi== 5))//
                 {
                    gzm_074 = 1;
                 }
                 if((spn== 95)&&(fmi== 3))//
                 {
                    gzm_075 = 1;
                 }
                 if((spn== 95)&&(fmi== 4))//
                 {
                    gzm_076 = 1;
                 }
                 if((spn== 520264)&&(fmi== 11))//
                 {
                    gzm_077 = 1;
                 }
                 if((spn== 522064)&&(fmi== 19))//
                 {
                    gzm_078 = 1;
                 }
                 if((spn== 522056)&&(fmi== 14))//
                 {
                    gzm_079 = 1;
                 }
                 if((spn== 522056)&&(fmi== 19))//
                 {
                    gzm_080 = 1;
                 }
                 if((spn== 522052)&&(fmi== 14))//
                 {
                    gzm_081 = 1;
                 }
                 if((spn== 522052)&&(fmi== 19))//
                 {
                    gzm_082 = 1;
                 }
                 if((spn== 522062)&&(fmi== 14))//
                 {
                    gzm_083 = 1;
                 }
                 if((spn== 522062)&&(fmi== 19))//
                 {
                    gzm_084 = 1;
                 }
                 if((spn== 522013)&&(fmi== 14))//
                 {
                    gzm_085 = 1;
                 }
                 if((spn== 522013)&&(fmi== 19))//
                 {
                    gzm_086 = 1;
                 }
                 if((spn== 522015)&&(fmi== 14))//
                 {
                    gzm_087 = 1;
                 }
                 if((spn== 522015)&&(fmi== 19))//
                 {
                    gzm_088 = 1;
                 }
                 if((spn== 522053)&&(fmi== 14))//
                 {
                    gzm_089 = 1;
                 }
                 if((spn== 522053)&&(fmi== 19))//
                 {
                    gzm_090 = 1;
                 }
                 if((spn== 522020)&&(fmi== 14))//
                 {
                    gzm_091 = 1;
                 }
                 if((spn== 522020)&&(fmi== 19))//
                 {
                    gzm_092 = 1;
                 }
                 if((spn== 522021)&&(fmi== 14))//
                 {
                    gzm_093 = 1;
                 }
                 if((spn== 522021)&&(fmi== 19))//
                 {
                    gzm_094 = 1;
                 }
                 if((spn== 522022)&&(fmi== 14))//
                 {
                    gzm_095 = 1;
                 }
                 if((spn== 522022)&&(fmi== 19))//
                 {
                    gzm_096 = 1;
                 }
                 if((spn== 522023)&&(fmi== 14))//
                 {
                    gzm_097 = 1;
                 }
                 if((spn== 522023)&&(fmi== 19))//
                 {
                    gzm_098 = 1;
                 }
                 if((spn== 522063)&&(fmi== 14))//
                 {
                    gzm_099 = 1;
                 }
                 if((spn==522063 )&&(fmi== 19))//
                 {
                    gzm_100 = 1;
                 }
                 if((spn== 522051)&&(fmi== 14))//
                 {
                    gzm_101 = 1;
                 }

                 if((spn== 522051)&&(fmi== 19))//
                 {
                    gzm_102 = 1;
                 }
                 if((spn== 522065)&&(fmi== 19))//
                 {
                    gzm_103 = 1;
                 }
                 if((spn== 522030)&&(fmi== 14))//
                 {
                    gzm_104 = 1;
                 }
                 if((spn== 522030)&&(fmi== 19))//
                 {
                    gzm_105 = 1;
                 }
                 if((spn== 520217)&&(fmi== 14))//
                 {
                    gzm_106 = 1;
                 }
                 if((spn== 520217)&&(fmi== 19))//
                 {
                    gzm_107 = 1;
                 }
                 if((spn== 522035)&&(fmi== 14))//
                 {
                    gzm_108 = 1;
                 }
                 if((spn== 522035)&&(fmi== 19))//
                 {
                    gzm_109 = 1;
                 }
                 if((spn== 522036)&&(fmi== 14))//
                 {
                    gzm_110 = 1;
                 }
                 if((spn== 522036)&&(fmi== 19))//
                 {
                    gzm_111 = 1;
                 }

                 if((spn== 522037)&&(fmi== 14))//
                 {
                    gzm_112 = 1;
                 }
                 if((spn== 522037)&&(fmi== 19))//
                 {
                    gzm_113 = 1;
                 }
                 if((spn== 522038)&&(fmi== 14))//
                 {
                    gzm_114 = 1;
                 }
                 if((spn== 522038)&&(fmi== 19))//
                 {
                    gzm_115 = 1;
                 }
                 if((spn== 522039)&&(fmi== 14))//
                 {
                    gzm_116 = 1;
                 }
                 if((spn== 522039)&&(fmi== 19))//
                 {
                    gzm_117 = 1;
                 }
                 if((spn== 522040)&&(fmi== 14))//
                 {
                    gzm_118 = 1;
                 }
                 if((spn== 522040)&&(fmi== 19))//
                 {
                    gzm_119 = 1;
                 }

                 if((spn== 522041)&&(fmi== 14))//
                 {
                    gzm_120 = 1;
                 }

                 if((spn== 522041)&&(fmi== 19))//
                 {
                    gzm_121 = 1;
                 }
                 if((spn== 522042)&&(fmi== 14))//
                 {
                    gzm_122 = 1;
                 }
                 if((spn== 522042)&&(fmi== 19))//
                 {
                    gzm_123 = 1;
                 }
                 if((spn== 522043)&&(fmi== 14))//
                 {
                    gzm_124 = 1;
                 }
                 if((spn== 522043)&&(fmi== 19))//
                 {
                    gzm_125 = 1;
                 }
                 if((spn== 174)&&(fmi== 3))//
                 {
                    gzm_126 = 1;
                 }
                 if((spn== 174)&&(fmi== 4))//
                 {
                    gzm_127 = 1;
                 }
                 if((spn== 520221)&&(fmi== 2))//
                 {
                    gzm_128 = 1;
                 }
                 if((spn== 624)&&(fmi== 12))//
                 {
                    gzm_129 = 1;
                 }
                 if((spn== 624)&&(fmi== 3))//
                 {
                    gzm_130 = 1;
                 }
                 if((spn== 624)&&(fmi== 4))//
                 {
                    gzm_131 = 1;
                 }
                 if((spn== 520223)&&(fmi== 20))//
                 {
                    gzm_132 = 1;
                 }
                 if((spn== 2802)&&(fmi== 14))//
                 {
                    gzm_133 = 1;
                 }
                 if((spn== 2802)&&(fmi== 12))//
                 {
                    gzm_134 = 1;
                 }
                 if((spn== 105)&&(fmi== 3))//
                 {
                    gzm_135 = 1;
                 }
                 if((spn== 105)&&(fmi== 4))//
                 {
                    gzm_136 = 1;
                 }
                 if((spn== 520210)&&(fmi== 15))//
                 {
                    gzm_137 = 1;
                 }
                 if((spn== 520210)&&(fmi== 15))//
                 {
                    gzm_138 = 1;
                 }
                 if((spn== 507)&&(fmi== 11))//
                 {
                    gzm_139 = 1;
                 }
                 if((spn== 507)&&(fmi== 11))//
                 {
                    gzm_140 = 1;
                 }
                 if((spn== 520210)&&(fmi== 15))//
                 {
                    gzm_141 = 1;
                 }
                 if((spn== 520210)&&(fmi== 15))//
                 {
                    gzm_142 = 1;
                 }
                 if((spn== 507)&&(fmi== 11))//
                 {
                    gzm_143 = 1;
                 }
                 if((spn== 1413)&&(fmi== 15))//
                 {
                    gzm_144 = 1;
                 }
                 if((spn== 1413)&&(fmi== 17))//
                 {
                    gzm_145 = 1;
                 }
                 if((spn== 1413)&&(fmi== 16))//
                 {
                    gzm_146 = 1;
                 }
                 if((spn== 1413)&&(fmi== 18))//
                 {
                    gzm_147 = 1;
                 }
                 if((spn== 1413)&&(fmi== 5))//
                 {
                    gzm_148 = 1;
                 }
                 if((spn== 1413)&&(fmi== 11))//
                 {
                    gzm_149 = 1;
                 }
                 if((spn== 1413)&&(fmi== 6))//
                 {
                    gzm_150 = 1;
                 }
                 if((spn== 1413)&&(fmi== 3))//
                 {
                    gzm_151 = 1;
                 }
                 if((spn== 1413)&&(fmi== 7))//
                 {
                    gzm_152 = 1;
                 }
                 if((spn== 1413)&&(fmi== 4))//
                 {
                    gzm_153 = 1;
                 }
                 if((spn== 1414)&&(fmi== 15))//
                 {
                    gzm_154 = 1;
                 }
                 if((spn== 1414)&&(fmi== 17))//
                 {
                    gzm_155 = 1;
                 }
                 if((spn== 1414)&&(fmi== 16))//
                 {
                    gzm_156 = 1;
                 }
                 if((spn== 1414)&&(fmi== 18))//
                 {
                    gzm_157 = 1;
                 }
                 if((spn== 1414)&&(fmi== 5))//
                 {
                    gzm_158 = 1;
                 }
                 if((spn== 1414)&&(fmi== 11))//
                 {
                    gzm_159 = 1;
                 }
                 if((spn== 1414)&&(fmi== 6))//
                 {
                    gzm_160 = 1;
                 }
                 if((spn== 1414)&&(fmi== 3))//
                 {
                    gzm_161 = 1;
                 }
                 if((spn== 1414)&&(fmi== 7))//
                 {
                    gzm_162 = 1;
                 }
                 if((spn== 1414)&&(fmi== 4))//
                 {
                    gzm_163 = 1;
                 }
                 if((spn== 1415)&&(fmi== 15))//
                 {
                    gzm_164 = 1;
                 }
                 if((spn== 1415)&&(fmi== 17))//
                 {
                    gzm_165 = 1;
                 }
                 if((spn== 1415)&&(fmi== 16))//
                 {
                    gzm_166 = 1;
                 }
                 if((spn== 1415)&&(fmi== 16))//
                 {
                    gzm_167 = 1;
                 }
                 if((spn== 1415)&&(fmi== 5))//
                 {
                    gzm_168 = 1;
                 }
                 if((spn== 1415)&&(fmi== 11))//
                 {
                    gzm_169 = 1;
                 }
                 if((spn== 1415)&&(fmi== 6))//
                 {
                    gzm_170 = 1;
                 }
                 if((spn== 1415)&&(fmi== 3))//
                 {
                    gzm_171 = 1;
                 }
                 if((spn== 1415)&&(fmi== 7))//
                 {
                    gzm_172 = 1;
                 }
                 if((spn== 1415)&&(fmi== 4))//
                 {
                    gzm_173 = 1;
                 }
                 if((spn== 1416)&&(fmi== 15))//
                 {
                    gzm_174 = 1;
                 }
                 if((spn== 1416)&&(fmi== 17))//
                 {
                    gzm_175 = 1;
                 }
                 if((spn== 1416)&&(fmi== 16))//
                 {
                    gzm_176 = 1;
                 }
                 if((spn== 1416)&&(fmi== 18))//
                 {
                    gzm_177 = 1;
                 }
                 if((spn== 1416)&&(fmi== 5))//
                 {
                    gzm_178 = 1;
                 }
                 if((spn== 1416)&&(fmi== 11))//
                 {
                    gzm_179 = 1;
                 }

                 if((spn== 1416)&&(fmi== 6))//
                 {
                    gzm_180 = 1;
                 }

                 if((spn== 1416)&&(fmi== 3))//
                 {
                    gzm_181 = 1;
                 }
                 if((spn== 1416)&&(fmi== 7))//
                 {
                    gzm_182 = 1;
                 }

                 if((spn== 1416)&&(fmi== 4))//
                 {
                    gzm_183 = 1;
                 }
                 if((spn== 1417)&&(fmi== 15))//
                 {
                    gzm_184 = 1;
                 }

                 if((spn== 1417)&&(fmi== 17))//
                 {
                    gzm_185 = 1;
                 }
                 if((spn== 1417)&&(fmi== 16))//
                 {
                    gzm_186 = 1;
                 }

                 if((spn== 1417)&&(fmi== 18))//
                 {
                    gzm_187 = 1;
                 }
                 if((spn== 1417)&&(fmi== 5))//
                 {
                    gzm_188 = 1;
                 }

                 if((spn== 1417)&&(fmi== 11))//
                 {
                    gzm_189 = 1;
                 }
                 if((spn== 1417)&&(fmi== 6))//
                 {
                    gzm_190 = 1;
                 }

                 if((spn== 1417)&&(fmi== 3))//
                 {
                    gzm_191 = 1;
                 }
                 if((spn== 1417)&&(fmi== 7))//
                 {
                    gzm_192 = 1;
                 }

                 if((spn== 1417)&&(fmi== 4))//
                 {
                    gzm_193 = 1;
                 }
                 if((spn== 1418)&&(fmi== 15))//
                 {
                    gzm_194 = 1;
                 }

                 if((spn== 1418)&&(fmi== 17))//
                 {
                    gzm_195 = 1;
                 }
                 if((spn== 1418)&&(fmi== 16))//
                 {
                    gzm_196 = 1;
                 }

                 if((spn== 1418)&&(fmi== 18))//
                 {
                    gzm_197 = 1;
                 }
                 if((spn== 1418)&&(fmi== 5))//
                 {
                    gzm_198 = 1;
                 }

                 if((spn== 1418)&&(fmi== 11))//
                 {
                    gzm_199 = 1;
                 }




                 //200 分界线

                 if((spn== 1418)&&(fmi== 6))//
                 {
                    gzm_200 = 1;
                 }
                 if((spn== 1418)&&(fmi== 3))//
                 {
                    gzm_201 = 1;
                 }
                 if((spn== 1418)&&(fmi== 7))//
                 {
                    gzm_202 = 1;
                 }
                 if((spn== 1418)&&(fmi== 4))//
                 {
                    gzm_203 = 1;
                 }

                 if((spn== 1442)&&(fmi== 7))//
                 {
                    gzm_204 = 1;
                 }
                 if((spn== 1442)&&(fmi== 9))//
                 {
                    gzm_205 = 1;
                 }
                 if((spn== 1442)&&(fmi== 10))//
                 {
                    gzm_206 = 1;
                 }
                 if((spn== 596)&&(fmi== 2))//
                 {
                    gzm_207 = 1;
                 }
                 if((spn== 520219)&&(fmi== 5))//
                 {
                    gzm_208 = 1;
                 }
                 if((spn== 520219)&&(fmi== 3))//
                 {
                    gzm_209 = 1;
                 }

                 if((spn== 520219)&&(fmi== 4))//
                 {
                    gzm_210 = 1;
                 }
                 if((spn== 1323)&&(fmi== 3))//
                 {
                    gzm_211 = 1;
                 }
                 if((spn== 1332)&&(fmi== 3))//
                 {
                    gzm_212 = 1;
                 }
                 if((spn== 1333)&&(fmi== 3))//
                 {
                    gzm_213 = 1;
                 }
                 if((spn== 1334)&&(fmi== 3))//
                 {
                    gzm_214 = 1;
                 }
                 if((spn== 1324)&&(fmi== 3))//
                 {
                    gzm_215 = 1;
                 }
                 if((spn== 1325)&&(fmi== 3))//
                 {
                    gzm_216 = 1;
                 }
                 if((spn== 1326)&&(fmi== 3))//
                 {
                    gzm_217 = 1;
                 }
                 if((spn== 1327)&&(fmi== 3))//
                 {
                    gzm_218 = 1;
                 }
                 if((spn== 1328)&&(fmi== 3))//
                 {
                    gzm_219 = 1;
                 }
                 if((spn== 1329)&&(fmi== 3))//
                 {
                    gzm_220 = 1;
                 }
                 if((spn== 1330)&&(fmi== 3))//
                 {
                    gzm_221 = 1;
                 }
                 if((spn== 1331)&&(fmi== 3))//
                 {
                    gzm_222 = 1;
                 }
                 if((spn== 1322)&&(fmi== 3))//
                 {
                    gzm_223 = 1;
                 }
                 if((spn== 976)&&(fmi== 19))//
                 {
                    gzm_224 = 1;
                 }
                 if((spn== 976)&&(fmi== 3))//
                 {
                    gzm_225 = 1;
                 }
                 if((spn== 976)&&(fmi== 4))//
                 {
                    gzm_226 = 1;
                 }
                 if((spn== 98)&&(fmi== 2))//
                 {
                    gzm_227 = 1;
                 }
                 if((spn== 98)&&(fmi== 3))//
                 {
                    gzm_228 = 1;
                 }
                 if((spn== 98)&&(fmi== 4))//
                 {
                    gzm_229 = 1;
                 }
                 if((spn== 100)&&(fmi== 17))//
                 {
                    gzm_230 = 1;
                 }
                 if((spn== 100)&&(fmi== 15))//
                 {
                    gzm_231 = 1;
                 }
                 if((spn== 100)&&(fmi== 16))//
                 {
                    gzm_232 = 1;
                 }
                 if((spn== 100)&&(fmi== 18))//
                 {
                    gzm_233 = 1;
                 }
                 if((spn== 175)&&(fmi== 15))//
                 {
                    gzm_234 = 1;
                 }


                 if((spn== 175)&&(fmi== 3))//
                 {
                    gzm_235 = 1;
                 }
                 if((spn==175 )&&(fmi== 4))//
                 {
                    gzm_236 = 1;
                 }
                 if((spn== 110)&&(fmi== 15))//
                 {
                    gzm_237 = 1;
                 }
                 if((spn== 1443)&&(fmi== 7))//
                 {
                    gzm_238 = 1;
                 }
                 if((spn== 1443)&&(fmi== 9))//
                 {
                    gzm_239 = 1;
                 }
                 if((spn== 1443)&&(fmi== 10))//
                 {
                    gzm_240 = 1;
                 }
                 if((spn== 523470)&&(fmi== 21))//
                 {
                    gzm_241 = 1;
                 }
                 if((spn== 520241)&&(fmi== 11))//
                 {
                    gzm_242 = 1;
                 }
                 if((spn== 520241)&&(fmi== 14))//
                 {
                    gzm_243 = 1;
                 }
                 if((spn== 520241)&&(fmi== 0))//
                 {
                    gzm_244 = 1;
                 }
                 if((spn== 157)&&(fmi== 15))//
                 {
                    gzm_245 = 1;
                 }
                 if((spn== 157)&&(fmi== 17))//
                 {
                    gzm_246 = 1;
                 }
                 if((spn== 157)&&(fmi== 3))//
                 {
                    gzm_247 = 1;
                 }
                 if((spn== 157)&&(fmi== 3))//
                 {
                    gzm_248 = 1;
                 }
                 if((spn== 157)&&(fmi== 4))//
                 {
                    gzm_249 = 1;
                 }
                 if((spn== 157)&&(fmi== 4))//
                 {
                    gzm_250 = 1;
                 }
                 if((spn== 520243)&&(fmi== 16))//
                 {
                    gzm_251 = 1;
                 }
                 if((spn== 520243)&&(fmi== 7))//
                 {
                    gzm_252 = 1;
                 }
                 if((spn== 520243)&&(fmi== 5))//
                 {
                    gzm_253 = 1;
                 }
                 if((spn== 520243)&&(fmi== 0))//
                 {
                    gzm_254 = 1;
                 }
                 if((spn== 520243)&&(fmi== 1))//
                 {
                    gzm_255 = 1;
                 }
                 if((spn== 520243)&&(fmi== 20))//
                 {
                    gzm_256 = 1;
                 }
                 if((spn== 520243)&&(fmi== 21))//
                 {
                    gzm_257 = 1;
                 }
                 if((spn== 520243)&&(fmi== 18))//
                 {
                    gzm_258 = 1;
                 }
                 if((spn== 520243)&&(fmi== 23))//
                 {
                    gzm_259 = 1;
                 }
                 if((spn== 520243)&&(fmi== 24))//
                 {
                    gzm_260 = 1;
                 }
                 if((spn== 520277)&&(fmi== 3))//
                 {
                    gzm_261 = 1;
                 }
                 if((spn== 520277)&&(fmi== 4))//
                 {
                    gzm_262 = 1;
                 }
                 if((spn== 520278)&&(fmi== 3))//
                 {
                    gzm_263 = 1;
                 }
                 if((spn== 520278)&&(fmi== 4))//
                 {
                    gzm_264 = 1;
                 }
                 if((spn== 3509)&&(fmi== 3))//
                 {
                    gzm_265 = 1;
                 }
                 if((spn== 3509)&&(fmi== 4))//
                 {
                    gzm_266 = 1;
                 }
                 if((spn== 3510)&&(fmi== 3))//
                 {
                    gzm_267 = 1;
                 }
                 if((spn== 3510)&&(fmi== 4))//
                 {
                    gzm_268 = 1;
                 }
                 if((spn== 3511)&&(fmi== 3))//
                 {
                    gzm_269 = 1;
                 }
                 if((spn== 3511)&&(fmi== 4))//
                 {
                    gzm_270 = 1;
                 }
                 if((spn== 107)&&(fmi== 7))//
                 {
                    gzm_271 = 1;
                 }
                 if((spn== 520289)&&(fmi== 11))//
                 {
                    gzm_272 = 1;
                 }
                 if((spn== 522014)&&(fmi== 1))//
                 {
                    gzm_273 = 1;
                 }
                 if((spn== 522014)&&(fmi== 2))//
                 {
                    gzm_274 = 1;
                 }
                 if((spn== 99)&&(fmi== 11))//
                 {
                    gzm_275 = 1;
                 }
                 if((spn== 99)&&(fmi== 7))//
                 {
                    gzm_276 = 1;
                 }
                 if((spn== 1675)&&(fmi== 3))//
                 {
                    gzm_277 = 1;
                 }
                 if((spn== 1675)&&(fmi== 4))//
                 {
                    gzm_278 = 1;
                 }
                 if((spn== 1675)&&(fmi== 5))//
                 {
                    gzm_279 = 1;
                 }

                 if((spn== 520253)&&(fmi== 11))//
                 {
                    gzm_280 = 1;
                 }

                 if((spn== 1136)&&(fmi== 4))//
                 {
                    gzm_281 = 1;
                 }
                 if((spn== 1136)&&(fmi== 3))//
                 {
                    gzm_282 = 1;
                 }

                 if((spn== 4346)&&(fmi== 5))//
                 {
                    gzm_283 = 1;
                 }
                 if((spn== 4346)&&(fmi== 3))//
                 {
                    gzm_284 = 1;
                 }

                 if((spn== 4346)&&(fmi== 4))//
                 {
                    gzm_285 = 1;
                 }
                 if((spn== 4344)&&(fmi== 5))//
                 {
                    gzm_286 = 1;
                 }

                 if((spn== 4344)&&(fmi== 3))//
                 {
                    gzm_287 = 1;
                 }
                 if((spn== 4344)&&(fmi== 4))//
                 {
                    gzm_288 = 1;
                 }

                 if((spn== 523003)&&(fmi== 5))//
                 {
                    gzm_289 = 1;
                 }
                 if((spn== 523003)&&(fmi== 3))//
                 {
                    gzm_290 = 1;
                 }

                 if((spn== 523003)&&(fmi== 4))//
                 {
                    gzm_291 = 1;
                 }
                 if((spn== 4340)&&(fmi== 5))//
                 {
                    gzm_292 = 1;
                 }

                 if((spn== 4340)&&(fmi== 3))//
                 {
                    gzm_293 = 1;
                 }
                 if((spn== 4340)&&(fmi== 4))//
                 {
                    gzm_294 = 1;
                 }

                 if((spn== 3363)&&(fmi== 5))//
                 {
                    gzm_295 = 1;
                 }
                 if((spn== 3363)&&(fmi== 3))//
                 {
                    gzm_296 = 1;
                 }

                 if((spn== 3363)&&(fmi== 4))//
                 {
                    gzm_297 = 1;
                 }
                 if((spn== 84)&&(fmi== 0))//
                 {
                    gzm_298 = 1;
                 }

                 if((spn== 84)&&(fmi== 2))//
                 {
                    gzm_299 = 1;
                 }

                 //300 分界线
                 if((spn== 1624)&&(fmi== 3))//
                 {
                    gzm_300 = 1;
                 }

                 if((spn== 1624)&&(fmi== 4))//
                 {
                    gzm_301 = 1;
                 }
                 if((spn== 1624)&&(fmi== 8))//
                 {
                    gzm_302 = 1;
                 }

                 if((spn== 520250)&&(fmi== 5))//
                 {
                    gzm_303 = 1;
                 }
                 if((spn== 520250)&&(fmi== 3))//
                 {
                    gzm_304 = 1;
                 }

                 if((spn== 520250)&&(fmi== 4))//
                 {
                    gzm_305 = 1;
                 }
                 if((spn== 520264)&&(fmi== 3))//
                 {
                    gzm_306 = 1;
                 }

                 if((spn== 520264)&&(fmi== 4))//
                 {
                    gzm_307 = 1;
                 }
                 if((spn== 522000)&&(fmi== 12))//
                 {
                    gzm_308 = 1;
                 }

                 if((spn== 520252)&&(fmi== 2))//
                 {
                    gzm_309 = 1;
                 }

                 if((spn== 520277)&&(fmi== 7))//
                 {
                    gzm_310 = 1;
                 }

                 if((spn== 520218)&&(fmi== 14))//
                 {
                    gzm_311 = 1;
                 }
                 if((spn== 520218)&&(fmi== 19))//
                 {
                    gzm_312 = 1;
                 }

                /***********************************************************************************************************/
                 //spn2

                 /*****************************************************************************************************/
                 //故障码解析

                  if((spn2==1351)&&(fmi2==5))//空调压缩机开路
                  {
                     gzm_001 = 1;
                  }

                  if((spn2==1351)&&(fmi2==3)) //空调压缩机对电源短路
                  {
                      gzm_002 = 1;

                  }

                  if((spn2==1351)&&(fmi2==4))//空调压缩机对地短路
                  {
                     gzm_003 = 1;
                  }

                  if((spn2==91)&&(fmi2==7)) //油门与刹车信号不可信
                  {
                      gzm_004 = 1;

                  }

                  if((spn2==132)&&(fmi2==3))//空气质量流量传感器电压超上限
                  {
                     gzm_005 = 1;
                  }

                  if((spn2==132)&&(fmi2==4)) //空气质量流量传感器电压超下限
                  {
                      gzm_006 = 1;

                  }

                  if((spn2==2898)&&(fmi2==7))//007进气加热常开故障
                  {
                     gzm_007 = 1;
                  }

                  if((spn2==520252)&&(fmi2==2)) //008油门踏板1与油门踏板2的两倍的信号关系不可信
                  {
                      gzm_008 = 1;

                  }

                  if((spn2==91)&&(fmi2==3))//009油门踏板1电压值高出上限门槛值
                  {
                     gzm_009 = 1;
                  }

                  if((spn2== 91)&&(fmi2== 4))//10油门踏板1电压值低于下限门槛值
                  {
                     gzm_010 = 1;
                  }

                  if((spn2== 520252)&&(fmi2== 2))//11 油门踏板2与油门踏板1的1/2的信号关系不可信
                  {
                     gzm_011 = 1;
                  }

                  if((spn2== 29)&&(fmi2== 3))//12 油门踏板2电压值高出上限门槛值
                  {
                     gzm_012 = 1;
                  }

                  if((spn2== 29)&&(fmi2== 4))//13 油门踏板2电压值低于下限门槛值
                  {
                     gzm_013 = 1;
                  }

                  if((spn2== 102)&&(fmi2== 2))//14 大气压力传感器信号不可信
                  {
                     gzm_014 = 1;
                  }

                  if((spn2== 108)&&(fmi2== 3))//15 大气压力传感器电压高出上限门槛
                  {
                     gzm_015 = 1;
                  }

                  if((spn2== 108)&&(fmi2== 4))//16 大气压力传感器电压低于下限门槛
                  {
                     gzm_016 = 1;
                  }

                  if((spn2== 2898)&&(fmi2== 5))//17进气加热器开路
                  {
                     gzm_017 = 1;
                  }

                  if((spn2== 2898)&&(fmi2== 3))//18 进气加热器对电源开路
                  {
                     gzm_018 = 1;
                  }

                  if((spn2== 2898)&&(fmi2== 4))//19
                  {
                     gzm_019 = 1;
                  }

                  if((spn2== 168)&&(fmi2== 4))//20
                  {
                     gzm_020 = 1;
                  }


                  if((spn2== 168)&&(fmi2== 3))//21
                  {
                     gzm_021 = 1;
                  }

                  if((spn2== 102)&&(fmi2== 2))//22
                  {
                     gzm_022 = 1;
                  }

                  if((spn2== 102)&&(fmi2== 3))//
                  {
                     gzm_023 = 1;
                  }

                  if((spn2== 102)&&(fmi2== 4))//
                  {
                     gzm_024 = 1;
                  }

                  if((spn2== 597)&&(fmi2== 11))//
                  {
                     gzm_025 = 1;
                  }

                  if((spn2== 597)&&(fmi2== 7))//
                  {
                     gzm_026 = 1;
                  }

                  if((spn2== 597)&&(fmi2== 2))//
                  {
                     gzm_027 = 1;
                  }

                  if((spn2== 597)&&(fmi2== 19))//
                  {
                     gzm_028 = 1;
                  }

                  if((spn2== 110)&&(fmi2== 18))//
                  {
                     gzm_029 = 1;
                  }

                  if((spn2== 110)&&(fmi2== 17))//
                  {
                     gzm_030 = 1;
                  }

                  if((spn2== 110)&&(fmi2== 2))//
                  {
                     gzm_031 = 1;
                  }

                  if((spn2== 190)&&(fmi2== 2))//
                  {
                     gzm_032 = 1;
                  }


                  if((spn2== 598)&&(fmi2== 2))//
                  {
                     gzm_033 = 1;
                  }

                  if((spn2== 520198)&&(fmi2== 11))//
                  {
                     gzm_034 = 1;
                  }


                  if((spn2== 626)&&(fmi2== 5))//
                  {
                     gzm_035 = 1;
                  }
                  if((spn2== 626)&&(fmi2== 3))//
                  {
                     gzm_036 = 1;
                  }
                  if((spn2== 626)&&(fmi2== 4))//
                  {
                     gzm_037 = 1;
                  }
                  if((spn2== 110)&&(fmi2== 2))//
                  {
                     gzm_038 = 1;
                  }
                  if((spn2== 110)&&(fmi2== 15))//
                  {
                     gzm_039 = 1;
                  }
                  if((spn2== 110)&&(fmi2== 3))//
                  {
                     gzm_040 = 1;
                  }
                  if((spn2== 110)&&(fmi2== 4))//
                  {
                     gzm_041 = 1;
                  }
                  if((spn2== 520203)&&(fmi2== 5))//
                  {
                     gzm_042 = 1;
                  }
                  if((spn2== 4203)&&(fmi2== 13))//
                  {
                     gzm_043 = 1;
                  }
                  if((spn2== 4201)&&(fmi2== 12))//
                  {
                     gzm_044 = 1;
                  }
                  if((spn2== 4201)&&(fmi2== 2))//
                  {
                     gzm_045 = 1;
                  }
                  if((spn2== 4201)&&(fmi2== 11))//
                  {
                     gzm_046 = 1;
                  }
                  if((spn2== 4201)&&(fmi2== 13))//
                  {
                     gzm_047 = 1;
                  }
                  if((spn2== 4203)&&(fmi2== 12))//
                  {
                     gzm_048 = 1;
                  }
                  if((spn2== 4203)&&(fmi2== 3))//
                  {
                     gzm_049 = 1;
                  }
                  if((spn2== 4203)&&(fmi2== 4))//
                  {
                     gzm_050 = 1;
                  }

                  if((spn2== 4203)&&(fmi2== 2))//
                  {
                     gzm_051 = 1;
                  }

                  if((spn2== 4201)&&(fmi2== 14))//
                  {
                     gzm_052 = 1;
                  }
                  if((spn2== 1769)&&(fmi2== 11))//
                  {
                     gzm_053 = 1;
                  }
                  if((spn2== 1623)&&(fmi2== 5))//
                  {
                     gzm_054 = 1;
                  }
                  if((spn2== 1623)&&(fmi2== 3))//
                  {
                     gzm_055 = 1;
                  }
                  if((spn2== 1623)&&(fmi2== 4))//
                  {
                     gzm_056 = 1;
                  }
                  if((spn2== 520208)&&(fmi2== 5))//
                  {
                     gzm_057 = 1;
                  }
                  if((spn2== 520208)&&(fmi2== 3))//
                  {
                     gzm_058 = 1;
                  }
                  if((spn2== 520208)&&(fmi2== 4))//
                  {
                     gzm_059 = 1;
                  }
                  if((spn2== 4815)&&(fmi2== 7))//
                  {
                     gzm_060 = 1;
                  }
                  if((spn2== 4815)&&(fmi2== 9))//
                  {
                     gzm_061 = 1;
                  }

                  if((spn2== 4815)&&(fmi2== 10))//
                  {
                     gzm_062 = 1;
                  }
                  if((spn2== 4815)&&(fmi2== 5))//
                  {
                     gzm_063 = 1;
                  }
                  if((spn2== 4815)&&(fmi2== 3))//
                  {
                     gzm_064 = 1;
                  }
                  if((spn2== 4815)&&(fmi2== 4))//
                  {
                     gzm_065 = 1;
                  }
                  if((spn2== 1639)&&(fmi2== 3))//
                  {
                     gzm_066 = 1;
                  }
                  if((spn2== 1639)&&(fmi2== 4))//
                  {
                     gzm_067 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 5))//
                  {
                     gzm_068 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 3))//
                  {
                     gzm_069 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 4))//
                  {
                     gzm_070 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 10))//
                  {
                     gzm_071 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 9))//
                  {
                     gzm_072 = 1;
                  }
                  if((spn2== 520261)&&(fmi2== 7))//
                  {
                     gzm_073 = 1;
                  }
                  if((spn2== 95)&&(fmi2== 5))//
                  {
                     gzm_074 = 1;
                  }
                  if((spn2== 95)&&(fmi2== 3))//
                  {
                     gzm_075 = 1;
                  }
                  if((spn2== 95)&&(fmi2== 4))//
                  {
                     gzm_076 = 1;
                  }
                  if((spn2== 520264)&&(fmi2== 11))//
                  {
                     gzm_077 = 1;
                  }
                  if((spn2== 522064)&&(fmi2== 19))//
                  {
                     gzm_078 = 1;
                  }
                  if((spn2== 522056)&&(fmi2== 14))//
                  {
                     gzm_079 = 1;
                  }
                  if((spn2== 522056)&&(fmi2== 19))//
                  {
                     gzm_080 = 1;
                  }
                  if((spn2== 522052)&&(fmi2== 14))//
                  {
                     gzm_081 = 1;
                  }
                  if((spn2== 522052)&&(fmi2== 19))//
                  {
                     gzm_082 = 1;
                  }
                  if((spn2== 522062)&&(fmi2== 14))//
                  {
                     gzm_083 = 1;
                  }
                  if((spn2== 522062)&&(fmi2== 19))//
                  {
                     gzm_084 = 1;
                  }
                  if((spn2== 522013)&&(fmi2== 14))//
                  {
                     gzm_085 = 1;
                  }
                  if((spn2== 522013)&&(fmi2== 19))//
                  {
                     gzm_086 = 1;
                  }
                  if((spn2== 522015)&&(fmi2== 14))//
                  {
                     gzm_087 = 1;
                  }
                  if((spn2== 522015)&&(fmi2== 19))//
                  {
                     gzm_088 = 1;
                  }
                  if((spn2== 522053)&&(fmi2== 14))//
                  {
                     gzm_089 = 1;
                  }
                  if((spn2== 522053)&&(fmi2== 19))//
                  {
                     gzm_090 = 1;
                  }
                  if((spn2== 522020)&&(fmi2== 14))//
                  {
                     gzm_091 = 1;
                  }
                  if((spn2== 522020)&&(fmi2== 19))//
                  {
                     gzm_092 = 1;
                  }
                  if((spn2== 522021)&&(fmi2== 14))//
                  {
                     gzm_093 = 1;
                  }
                  if((spn2== 522021)&&(fmi2== 19))//
                  {
                     gzm_094 = 1;
                  }
                  if((spn2== 522022)&&(fmi2== 14))//
                  {
                     gzm_095 = 1;
                  }
                  if((spn2== 522022)&&(fmi2== 19))//
                  {
                     gzm_096 = 1;
                  }
                  if((spn2== 522023)&&(fmi2== 14))//
                  {
                     gzm_097 = 1;
                  }
                  if((spn2== 522023)&&(fmi2== 19))//
                  {
                     gzm_098 = 1;
                  }
                  if((spn2== 522063)&&(fmi2== 14))//
                  {
                     gzm_099 = 1;
                  }
                  if((spn2==522063 )&&(fmi2== 19))//
                  {
                     gzm_100 = 1;
                  }
                  if((spn2== 522051)&&(fmi2== 14))//
                  {
                     gzm_101 = 1;
                  }

                  if((spn2== 522051)&&(fmi2== 19))//
                  {
                     gzm_102 = 1;
                  }
                  if((spn2== 522065)&&(fmi2== 19))//
                  {
                     gzm_103 = 1;
                  }
                  if((spn2== 522030)&&(fmi2== 14))//
                  {
                     gzm_104 = 1;
                  }
                  if((spn2== 522030)&&(fmi2== 19))//
                  {
                     gzm_105 = 1;
                  }
                  if((spn2== 520217)&&(fmi2== 14))//
                  {
                     gzm_106 = 1;
                  }
                  if((spn2== 520217)&&(fmi2== 19))//
                  {
                     gzm_107 = 1;
                  }
                  if((spn2== 522035)&&(fmi2== 14))//
                  {
                     gzm_108 = 1;
                  }
                  if((spn2== 522035)&&(fmi2== 19))//
                  {
                     gzm_109 = 1;
                  }
                  if((spn2== 522036)&&(fmi2== 14))//
                  {
                     gzm_110 = 1;
                  }
                  if((spn2== 522036)&&(fmi2== 19))//
                  {
                     gzm_111 = 1;
                  }

                  if((spn2== 522037)&&(fmi2== 14))//
                  {
                     gzm_112 = 1;
                  }
                  if((spn2== 522037)&&(fmi2== 19))//
                  {
                     gzm_113 = 1;
                  }
                  if((spn2== 522038)&&(fmi2== 14))//
                  {
                     gzm_114 = 1;
                  }
                  if((spn2== 522038)&&(fmi2== 19))//
                  {
                     gzm_115 = 1;
                  }
                  if((spn2== 522039)&&(fmi2== 14))//
                  {
                     gzm_116 = 1;
                  }
                  if((spn2== 522039)&&(fmi2== 19))//
                  {
                     gzm_117 = 1;
                  }
                  if((spn2== 522040)&&(fmi2== 14))//
                  {
                     gzm_118 = 1;
                  }
                  if((spn2== 522040)&&(fmi2== 19))//
                  {
                     gzm_119 = 1;
                  }

                  if((spn2== 522041)&&(fmi2== 14))//
                  {
                     gzm_120 = 1;
                  }

                  if((spn2== 522041)&&(fmi2== 19))//
                  {
                     gzm_121 = 1;
                  }
                  if((spn2== 522042)&&(fmi2== 14))//
                  {
                     gzm_122 = 1;
                  }
                  if((spn2== 522042)&&(fmi2== 19))//
                  {
                     gzm_123 = 1;
                  }
                  if((spn2== 522043)&&(fmi2== 14))//
                  {
                     gzm_124 = 1;
                  }
                  if((spn2== 522043)&&(fmi2== 19))//
                  {
                     gzm_125 = 1;
                  }
                  if((spn2== 174)&&(fmi2== 3))//
                  {
                     gzm_126 = 1;
                  }
                  if((spn2== 174)&&(fmi2== 4))//
                  {
                     gzm_127 = 1;
                  }
                  if((spn2== 520221)&&(fmi2== 2))//
                  {
                     gzm_128 = 1;
                  }
                  if((spn2== 624)&&(fmi2== 12))//
                  {
                     gzm_129 = 1;
                  }
                  if((spn2== 624)&&(fmi2== 3))//
                  {
                     gzm_130 = 1;
                  }
                  if((spn2== 624)&&(fmi2== 4))//
                  {
                     gzm_131 = 1;
                  }
                  if((spn2== 520223)&&(fmi2== 20))//
                  {
                     gzm_132 = 1;
                  }
                  if((spn2== 2802)&&(fmi2== 14))//
                  {
                     gzm_133 = 1;
                  }
                  if((spn2== 2802)&&(fmi2== 12))//
                  {
                     gzm_134 = 1;
                  }
                  if((spn2== 105)&&(fmi2== 3))//
                  {
                     gzm_135 = 1;
                  }
                  if((spn2== 105)&&(fmi2== 4))//
                  {
                     gzm_136 = 1;
                  }
                  if((spn2== 520210)&&(fmi2== 15))//
                  {
                     gzm_137 = 1;
                  }
                  if((spn2== 520210)&&(fmi2== 15))//
                  {
                     gzm_138 = 1;
                  }
                  if((spn2== 507)&&(fmi2== 11))//
                  {
                     gzm_139 = 1;
                  }
                  if((spn2== 507)&&(fmi2== 11))//
                  {
                     gzm_140 = 1;
                  }
                  if((spn2== 520210)&&(fmi2== 15))//
                  {
                     gzm_141 = 1;
                  }
                  if((spn2== 520210)&&(fmi2== 15))//
                  {
                     gzm_142 = 1;
                  }
                  if((spn2== 507)&&(fmi2== 11))//
                  {
                     gzm_143 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 15))//
                  {
                     gzm_144 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 17))//
                  {
                     gzm_145 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 16))//
                  {
                     gzm_146 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 18))//
                  {
                     gzm_147 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 5))//
                  {
                     gzm_148 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 11))//
                  {
                     gzm_149 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 6))//
                  {
                     gzm_150 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 3))//
                  {
                     gzm_151 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 7))//
                  {
                     gzm_152 = 1;
                  }
                  if((spn2== 1413)&&(fmi2== 4))//
                  {
                     gzm_153 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 15))//
                  {
                     gzm_154 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 17))//
                  {
                     gzm_155 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 16))//
                  {
                     gzm_156 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 18))//
                  {
                     gzm_157 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 5))//
                  {
                     gzm_158 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 11))//
                  {
                     gzm_159 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 6))//
                  {
                     gzm_160 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 3))//
                  {
                     gzm_161 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 7))//
                  {
                     gzm_162 = 1;
                  }
                  if((spn2== 1414)&&(fmi2== 4))//
                  {
                     gzm_163 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 15))//
                  {
                     gzm_164 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 17))//
                  {
                     gzm_165 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 16))//
                  {
                     gzm_166 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 16))//
                  {
                     gzm_167 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 5))//
                  {
                     gzm_168 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 11))//
                  {
                     gzm_169 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 6))//
                  {
                     gzm_170 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 3))//
                  {
                     gzm_171 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 7))//
                  {
                     gzm_172 = 1;
                  }
                  if((spn2== 1415)&&(fmi2== 4))//
                  {
                     gzm_173 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 15))//
                  {
                     gzm_174 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 17))//
                  {
                     gzm_175 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 16))//
                  {
                     gzm_176 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 18))//
                  {
                     gzm_177 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 5))//
                  {
                     gzm_178 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 11))//
                  {
                     gzm_179 = 1;
                  }

                  if((spn2== 1416)&&(fmi2== 6))//
                  {
                     gzm_180 = 1;
                  }

                  if((spn2== 1416)&&(fmi2== 3))//
                  {
                     gzm_181 = 1;
                  }
                  if((spn2== 1416)&&(fmi2== 7))//
                  {
                     gzm_182 = 1;
                  }

                  if((spn2== 1416)&&(fmi2== 4))//
                  {
                     gzm_183 = 1;
                  }
                  if((spn2== 1417)&&(fmi2== 15))//
                  {
                     gzm_184 = 1;
                  }

                  if((spn2== 1417)&&(fmi2== 17))//
                  {
                     gzm_185 = 1;
                  }
                  if((spn2== 1417)&&(fmi2== 16))//
                  {
                     gzm_186 = 1;
                  }

                  if((spn2== 1417)&&(fmi2== 18))//
                  {
                     gzm_187 = 1;
                  }
                  if((spn2== 1417)&&(fmi2== 5))//
                  {
                     gzm_188 = 1;
                  }

                  if((spn2== 1417)&&(fmi2== 11))//
                  {
                     gzm_189 = 1;
                  }
                  if((spn2== 1417)&&(fmi2== 6))//
                  {
                     gzm_190 = 1;
                  }

                  if((spn2== 1417)&&(fmi2== 3))//
                  {
                     gzm_191 = 1;
                  }
                  if((spn2== 1417)&&(fmi2== 7))//
                  {
                     gzm_192 = 1;
                  }

                  if((spn2== 1417)&&(fmi2== 4))//
                  {
                     gzm_193 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 15))//
                  {
                     gzm_194 = 1;
                  }

                  if((spn2== 1418)&&(fmi2== 17))//
                  {
                     gzm_195 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 16))//
                  {
                     gzm_196 = 1;
                  }

                  if((spn2== 1418)&&(fmi2== 18))//
                  {
                     gzm_197 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 5))//
                  {
                     gzm_198 = 1;
                  }

                  if((spn2== 1418)&&(fmi2== 11))//
                  {
                     gzm_199 = 1;
                  }




                  //200 分界线

                  if((spn2== 1418)&&(fmi2== 6))//
                  {
                     gzm_200 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 3))//
                  {
                     gzm_201 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 7))//
                  {
                     gzm_202 = 1;
                  }
                  if((spn2== 1418)&&(fmi2== 4))//
                  {
                     gzm_203 = 1;
                  }

                  if((spn2== 1442)&&(fmi2== 7))//
                  {
                     gzm_204 = 1;
                  }
                  if((spn2== 1442)&&(fmi2== 9))//
                  {
                     gzm_205 = 1;
                  }
                  if((spn2== 1442)&&(fmi2== 10))//
                  {
                     gzm_206 = 1;
                  }
                  if((spn2== 596)&&(fmi2== 2))//
                  {
                     gzm_207 = 1;
                  }
                  if((spn2== 520219)&&(fmi2== 5))//
                  {
                     gzm_208 = 1;
                  }
                  if((spn2== 520219)&&(fmi2== 3))//
                  {
                     gzm_209 = 1;
                  }

                  if((spn2== 520219)&&(fmi2== 4))//
                  {
                     gzm_210 = 1;
                  }
                  if((spn2== 1323)&&(fmi2== 3))//
                  {
                     gzm_211 = 1;
                  }
                  if((spn2== 1332)&&(fmi2== 3))//
                  {
                     gzm_212 = 1;
                  }
                  if((spn2== 1333)&&(fmi2== 3))//
                  {
                     gzm_213 = 1;
                  }
                  if((spn2== 1334)&&(fmi2== 3))//
                  {
                     gzm_214 = 1;
                  }
                  if((spn2== 1324)&&(fmi2== 3))//
                  {
                     gzm_215 = 1;
                  }
                  if((spn2== 1325)&&(fmi2== 3))//
                  {
                     gzm_216 = 1;
                  }
                  if((spn2== 1326)&&(fmi2== 3))//
                  {
                     gzm_217 = 1;
                  }
                  if((spn2== 1327)&&(fmi2== 3))//
                  {
                     gzm_218 = 1;
                  }
                  if((spn2== 1328)&&(fmi2== 3))//
                  {
                     gzm_219 = 1;
                  }
                  if((spn2== 1329)&&(fmi2== 3))//
                  {
                     gzm_220 = 1;
                  }
                  if((spn2== 1330)&&(fmi2== 3))//
                  {
                     gzm_221 = 1;
                  }
                  if((spn2== 1331)&&(fmi2== 3))//
                  {
                     gzm_222 = 1;
                  }
                  if((spn2== 1322)&&(fmi2== 3))//
                  {
                     gzm_223 = 1;
                  }
                  if((spn2== 976)&&(fmi2== 19))//
                  {
                     gzm_224 = 1;
                  }
                  if((spn2== 976)&&(fmi2== 3))//
                  {
                     gzm_225 = 1;
                  }
                  if((spn2== 976)&&(fmi2== 4))//
                  {
                     gzm_226 = 1;
                  }
                  if((spn2== 98)&&(fmi2== 2))//
                  {
                     gzm_227 = 1;
                  }
                  if((spn2== 98)&&(fmi2== 3))//
                  {
                     gzm_228 = 1;
                  }
                  if((spn2== 98)&&(fmi2== 4))//
                  {
                     gzm_229 = 1;
                  }
                  if((spn2== 100)&&(fmi2== 17))//
                  {
                     gzm_230 = 1;
                  }
                  if((spn2== 100)&&(fmi2== 15))//
                  {
                     gzm_231 = 1;
                  }
                  if((spn2== 100)&&(fmi2== 16))//
                  {
                     gzm_232 = 1;
                  }
                  if((spn2== 100)&&(fmi2== 18))//
                  {
                     gzm_233 = 1;
                  }
                  if((spn2== 175)&&(fmi2== 15))//
                  {
                     gzm_234 = 1;
                  }


                  if((spn2== 175)&&(fmi2== 3))//
                  {
                     gzm_235 = 1;
                  }
                  if((spn2==175 )&&(fmi2== 4))//
                  {
                     gzm_236 = 1;
                  }
                  if((spn2== 110)&&(fmi2== 15))//
                  {
                     gzm_237 = 1;
                  }
                  if((spn2== 1443)&&(fmi2== 7))//
                  {
                     gzm_238 = 1;
                  }
                  if((spn2== 1443)&&(fmi2== 9))//
                  {
                     gzm_239 = 1;
                  }
                  if((spn2== 1443)&&(fmi2== 10))//
                  {
                     gzm_240 = 1;
                  }
                  if((spn2== 523470)&&(fmi2== 21))//
                  {
                     gzm_241 = 1;
                  }
                  if((spn2== 520241)&&(fmi2== 11))//
                  {
                     gzm_242 = 1;
                  }
                  if((spn2== 520241)&&(fmi2== 14))//
                  {
                     gzm_243 = 1;
                  }
                  if((spn2== 520241)&&(fmi2== 0))//
                  {
                     gzm_244 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 15))//
                  {
                     gzm_245 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 17))//
                  {
                     gzm_246 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 3))//
                  {
                     gzm_247 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 3))//
                  {
                     gzm_248 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 4))//
                  {
                     gzm_249 = 1;
                  }
                  if((spn2== 157)&&(fmi2== 4))//
                  {
                     gzm_250 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 16))//
                  {
                     gzm_251 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 7))//
                  {
                     gzm_252 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 5))//
                  {
                     gzm_253 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 0))//
                  {
                     gzm_254 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 1))//
                  {
                     gzm_255 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 20))//
                  {
                     gzm_256 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 21))//
                  {
                     gzm_257 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 18))//
                  {
                     gzm_258 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 23))//
                  {
                     gzm_259 = 1;
                  }
                  if((spn2== 520243)&&(fmi2== 24))//
                  {
                     gzm_260 = 1;
                  }
                  if((spn2== 520277)&&(fmi2== 3))//
                  {
                     gzm_261 = 1;
                  }
                  if((spn2== 520277)&&(fmi2== 4))//
                  {
                     gzm_262 = 1;
                  }
                  if((spn2== 520278)&&(fmi2== 3))//
                  {
                     gzm_263 = 1;
                  }
                  if((spn2== 520278)&&(fmi2== 4))//
                  {
                     gzm_264 = 1;
                  }
                  if((spn2== 3509)&&(fmi2== 3))//
                  {
                     gzm_265 = 1;
                  }
                  if((spn2== 3509)&&(fmi2== 4))//
                  {
                     gzm_266 = 1;
                  }
                  if((spn2== 3510)&&(fmi2== 3))//
                  {
                     gzm_267 = 1;
                  }
                  if((spn2== 3510)&&(fmi2== 4))//
                  {
                     gzm_268 = 1;
                  }
                  if((spn2== 3511)&&(fmi2== 3))//
                  {
                     gzm_269 = 1;
                  }
                  if((spn2== 3511)&&(fmi2== 4))//
                  {
                     gzm_270 = 1;
                  }
                  if((spn2== 107)&&(fmi2== 7))//
                  {
                     gzm_271 = 1;
                  }
                  if((spn2== 520289)&&(fmi2== 11))//
                  {
                     gzm_272 = 1;
                  }
                  if((spn2== 522014)&&(fmi2== 1))//
                  {
                     gzm_273 = 1;
                  }
                  if((spn2== 522014)&&(fmi2== 2))//
                  {
                     gzm_274 = 1;
                  }
                  if((spn2== 99)&&(fmi2== 11))//
                  {
                     gzm_275 = 1;
                  }
                  if((spn2== 99)&&(fmi2== 7))//
                  {
                     gzm_276 = 1;
                  }
                  if((spn2== 1675)&&(fmi2== 3))//
                  {
                     gzm_277 = 1;
                  }
                  if((spn2== 1675)&&(fmi2== 4))//
                  {
                     gzm_278 = 1;
                  }
                  if((spn2== 1675)&&(fmi2== 5))//
                  {
                     gzm_279 = 1;
                  }

                  if((spn2== 520253)&&(fmi2== 11))//
                  {
                     gzm_280 = 1;
                  }

                  if((spn2== 1136)&&(fmi2== 4))//
                  {
                     gzm_281 = 1;
                  }
                  if((spn2== 1136)&&(fmi2== 3))//
                  {
                     gzm_282 = 1;
                  }

                  if((spn2== 4346)&&(fmi2== 5))//
                  {
                     gzm_283 = 1;
                  }
                  if((spn2== 4346)&&(fmi2== 3))//
                  {
                     gzm_284 = 1;
                  }

                  if((spn2== 4346)&&(fmi2== 4))//
                  {
                     gzm_285 = 1;
                  }
                  if((spn2== 4344)&&(fmi2== 5))//
                  {
                     gzm_286 = 1;
                  }

                  if((spn2== 4344)&&(fmi2== 3))//
                  {
                     gzm_287 = 1;
                  }
                  if((spn2== 4344)&&(fmi2== 4))//
                  {
                     gzm_288 = 1;
                  }

                  if((spn2== 523003)&&(fmi2== 5))//
                  {
                     gzm_289 = 1;
                  }
                  if((spn2== 523003)&&(fmi2== 3))//
                  {
                     gzm_290 = 1;
                  }

                  if((spn2== 523003)&&(fmi2== 4))//
                  {
                     gzm_291 = 1;
                  }
                  if((spn2== 4340)&&(fmi2== 5))//
                  {
                     gzm_292 = 1;
                  }

                  if((spn2== 4340)&&(fmi2== 3))//
                  {
                     gzm_293 = 1;
                  }
                  if((spn2== 4340)&&(fmi2== 4))//
                  {
                     gzm_294 = 1;
                  }

                  if((spn2== 3363)&&(fmi2== 5))//
                  {
                     gzm_295 = 1;
                  }
                  if((spn2== 3363)&&(fmi2== 3))//
                  {
                     gzm_296 = 1;
                  }

                  if((spn2== 3363)&&(fmi2== 4))//
                  {
                     gzm_297 = 1;
                  }
                  if((spn2== 84)&&(fmi2== 0))//
                  {
                     gzm_298 = 1;
                  }

                  if((spn2== 84)&&(fmi2== 2))//
                  {
                     gzm_299 = 1;
                  }

                  //300 分界线
                  if((spn2== 1624)&&(fmi2== 3))//
                  {
                     gzm_300 = 1;
                  }

                  if((spn2== 1624)&&(fmi2== 4))//
                  {
                     gzm_301 = 1;
                  }
                  if((spn2== 1624)&&(fmi2== 8))//
                  {
                     gzm_302 = 1;
                  }

                  if((spn2== 520250)&&(fmi2== 5))//
                  {
                     gzm_303 = 1;
                  }
                  if((spn2== 520250)&&(fmi2== 3))//
                  {
                     gzm_304 = 1;
                  }

                  if((spn2== 520250)&&(fmi2== 4))//
                  {
                     gzm_305 = 1;
                  }
                  if((spn2== 520264)&&(fmi2== 3))//
                  {
                     gzm_306 = 1;
                  }

                  if((spn2== 520264)&&(fmi2== 4))//
                  {
                     gzm_307 = 1;
                  }
                  if((spn2== 522000)&&(fmi2== 12))//
                  {
                     gzm_308 = 1;
                  }

                  if((spn2== 520252)&&(fmi2== 2))//
                  {
                     gzm_309 = 1;
                  }

                  if((spn2== 520277)&&(fmi2== 7))//
                  {
                     gzm_310 = 1;
                  }

                  if((spn2== 520218)&&(fmi2== 14))//
                  {
                     gzm_311 = 1;
                  }
                  if((spn2== 520218)&&(fmi2== 19))//
                  {
                     gzm_312 = 1;
                  }
                /**********************************************************************************************/
                  //spn3
                  /*****************************************************************************************************/
                  //故障码解析

                   if((spn3==1351)&&(fmi3==5))//空调压缩机开路
                   {
                      gzm_001 = 1;
                   }

                   if((spn3==1351)&&(fmi3==3)) //空调压缩机对电源短路
                   {
                       gzm_002 = 1;

                   }

                   if((spn3==1351)&&(fmi3==4))//空调压缩机对地短路
                   {
                      gzm_003 = 1;
                   }

                   if((spn3==91)&&(fmi3==7)) //油门与刹车信号不可信
                   {
                       gzm_004 = 1;

                   }

                   if((spn3==132)&&(fmi3==3))//空气质量流量传感器电压超上限
                   {
                      gzm_005 = 1;
                   }

                   if((spn3==132)&&(fmi3==4)) //空气质量流量传感器电压超下限
                   {
                       gzm_006 = 1;

                   }

                   if((spn3==2898)&&(fmi3==7))//007进气加热常开故障
                   {
                      gzm_007 = 1;
                   }

                   if((spn3==520252)&&(fmi3==2)) //008油门踏板1与油门踏板2的两倍的信号关系不可信
                   {
                       gzm_008 = 1;

                   }

                   if((spn3==91)&&(fmi3==3))//009油门踏板1电压值高出上限门槛值
                   {
                      gzm_009 = 1;
                   }

                   if((spn3== 91)&&(fmi3== 4))//10油门踏板1电压值低于下限门槛值
                   {
                      gzm_010 = 1;
                   }

                   if((spn3== 520252)&&(fmi3== 2))//11 油门踏板2与油门踏板1的1/2的信号关系不可信
                   {
                      gzm_011 = 1;
                   }

                   if((spn3== 29)&&(fmi3== 3))//12 油门踏板2电压值高出上限门槛值
                   {
                      gzm_012 = 1;
                   }

                   if((spn3== 29)&&(fmi3== 4))//13 油门踏板2电压值低于下限门槛值
                   {
                      gzm_013 = 1;
                   }

                   if((spn3== 102)&&(fmi3== 2))//14 大气压力传感器信号不可信
                   {
                      gzm_014 = 1;
                   }

                   if((spn3== 108)&&(fmi3== 3))//15 大气压力传感器电压高出上限门槛
                   {
                      gzm_015 = 1;
                   }

                   if((spn3== 108)&&(fmi3== 4))//16 大气压力传感器电压低于下限门槛
                   {
                      gzm_016 = 1;
                   }

                   if((spn3== 2898)&&(fmi3== 5))//17进气加热器开路
                   {
                      gzm_017 = 1;
                   }

                   if((spn3== 2898)&&(fmi3== 3))//18 进气加热器对电源开路
                   {
                      gzm_018 = 1;
                   }

                   if((spn3== 2898)&&(fmi3== 4))//19
                   {
                      gzm_019 = 1;
                   }

                   if((spn3== 168)&&(fmi3== 4))//20
                   {
                      gzm_020 = 1;
                   }


                   if((spn3== 168)&&(fmi3== 3))//21
                   {
                      gzm_021 = 1;
                   }

                   if((spn3== 102)&&(fmi3== 2))//22
                   {
                      gzm_022 = 1;
                   }

                   if((spn3== 102)&&(fmi3== 3))//
                   {
                      gzm_023 = 1;
                   }

                   if((spn3== 102)&&(fmi3== 4))//
                   {
                      gzm_024 = 1;
                   }

                   if((spn3== 597)&&(fmi3== 11))//
                   {
                      gzm_025 = 1;
                   }

                   if((spn3== 597)&&(fmi3== 7))//
                   {
                      gzm_026 = 1;
                   }

                   if((spn3== 597)&&(fmi3== 2))//
                   {
                      gzm_027 = 1;
                   }

                   if((spn3== 597)&&(fmi3== 19))//
                   {
                      gzm_028 = 1;
                   }

                   if((spn3== 110)&&(fmi3== 18))//
                   {
                      gzm_029 = 1;
                   }

                   if((spn3== 110)&&(fmi3== 17))//
                   {
                      gzm_030 = 1;
                   }

                   if((spn3== 110)&&(fmi3== 2))//
                   {
                      gzm_031 = 1;
                   }

                   if((spn3== 190)&&(fmi3== 2))//
                   {
                      gzm_032 = 1;
                   }


                   if((spn3== 598)&&(fmi3== 2))//
                   {
                      gzm_033 = 1;
                   }

                   if((spn3== 520198)&&(fmi3== 11))//
                   {
                      gzm_034 = 1;
                   }


                   if((spn3== 626)&&(fmi3== 5))//
                   {
                      gzm_035 = 1;
                   }
                   if((spn3== 626)&&(fmi3== 3))//
                   {
                      gzm_036 = 1;
                   }
                   if((spn3== 626)&&(fmi3== 4))//
                   {
                      gzm_037 = 1;
                   }
                   if((spn3== 110)&&(fmi3== 2))//
                   {
                      gzm_038 = 1;
                   }
                   if((spn3== 110)&&(fmi3== 15))//
                   {
                      gzm_039 = 1;
                   }
                   if((spn3== 110)&&(fmi3== 3))//
                   {
                      gzm_040 = 1;
                   }
                   if((spn3== 110)&&(fmi3== 4))//
                   {
                      gzm_041 = 1;
                   }
                   if((spn3== 520203)&&(fmi3== 5))//
                   {
                      gzm_042 = 1;
                   }
                   if((spn3== 4203)&&(fmi3== 13))//
                   {
                      gzm_043 = 1;
                   }
                   if((spn3== 4201)&&(fmi3== 12))//
                   {
                      gzm_044 = 1;
                   }
                   if((spn3== 4201)&&(fmi3== 2))//
                   {
                      gzm_045 = 1;
                   }
                   if((spn3== 4201)&&(fmi3== 11))//
                   {
                      gzm_046 = 1;
                   }
                   if((spn3== 4201)&&(fmi3== 13))//
                   {
                      gzm_047 = 1;
                   }
                   if((spn3== 4203)&&(fmi3== 12))//
                   {
                      gzm_048 = 1;
                   }
                   if((spn3== 4203)&&(fmi3== 3))//
                   {
                      gzm_049 = 1;
                   }
                   if((spn3== 4203)&&(fmi3== 4))//
                   {
                      gzm_050 = 1;
                   }

                   if((spn3== 4203)&&(fmi3== 2))//
                   {
                      gzm_051 = 1;
                   }

                   if((spn3== 4201)&&(fmi3== 14))//
                   {
                      gzm_052 = 1;
                   }
                   if((spn3== 1769)&&(fmi3== 11))//
                   {
                      gzm_053 = 1;
                   }
                   if((spn3== 1623)&&(fmi3== 5))//
                   {
                      gzm_054 = 1;
                   }
                   if((spn3== 1623)&&(fmi3== 3))//
                   {
                      gzm_055 = 1;
                   }
                   if((spn3== 1623)&&(fmi3== 4))//
                   {
                      gzm_056 = 1;
                   }
                   if((spn3== 520208)&&(fmi3== 5))//
                   {
                      gzm_057 = 1;
                   }
                   if((spn3== 520208)&&(fmi3== 3))//
                   {
                      gzm_058 = 1;
                   }
                   if((spn3== 520208)&&(fmi3== 4))//
                   {
                      gzm_059 = 1;
                   }
                   if((spn3== 4815)&&(fmi3== 7))//
                   {
                      gzm_060 = 1;
                   }
                   if((spn3== 4815)&&(fmi3== 9))//
                   {
                      gzm_061 = 1;
                   }

                   if((spn3== 4815)&&(fmi3== 10))//
                   {
                      gzm_062 = 1;
                   }
                   if((spn3== 4815)&&(fmi3== 5))//
                   {
                      gzm_063 = 1;
                   }
                   if((spn3== 4815)&&(fmi3== 3))//
                   {
                      gzm_064 = 1;
                   }
                   if((spn3== 4815)&&(fmi3== 4))//
                   {
                      gzm_065 = 1;
                   }
                   if((spn3== 1639)&&(fmi3== 3))//
                   {
                      gzm_066 = 1;
                   }
                   if((spn3== 1639)&&(fmi3== 4))//
                   {
                      gzm_067 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 5))//
                   {
                      gzm_068 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 3))//
                   {
                      gzm_069 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 4))//
                   {
                      gzm_070 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 10))//
                   {
                      gzm_071 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 9))//
                   {
                      gzm_072 = 1;
                   }
                   if((spn3== 520261)&&(fmi3== 7))//
                   {
                      gzm_073 = 1;
                   }
                   if((spn3== 95)&&(fmi3== 5))//
                   {
                      gzm_074 = 1;
                   }
                   if((spn3== 95)&&(fmi3== 3))//
                   {
                      gzm_075 = 1;
                   }
                   if((spn3== 95)&&(fmi3== 4))//
                   {
                      gzm_076 = 1;
                   }
                   if((spn3== 520264)&&(fmi3== 11))//
                   {
                      gzm_077 = 1;
                   }
                   if((spn3== 522064)&&(fmi3== 19))//
                   {
                      gzm_078 = 1;
                   }
                   if((spn3== 522056)&&(fmi3== 14))//
                   {
                      gzm_079 = 1;
                   }
                   if((spn3== 522056)&&(fmi3== 19))//
                   {
                      gzm_080 = 1;
                   }
                   if((spn3== 522052)&&(fmi3== 14))//
                   {
                      gzm_081 = 1;
                   }
                   if((spn3== 522052)&&(fmi3== 19))//
                   {
                      gzm_082 = 1;
                   }
                   if((spn3== 522062)&&(fmi3== 14))//
                   {
                      gzm_083 = 1;
                   }
                   if((spn3== 522062)&&(fmi3== 19))//
                   {
                      gzm_084 = 1;
                   }
                   if((spn3== 522013)&&(fmi3== 14))//
                   {
                      gzm_085 = 1;
                   }
                   if((spn3== 522013)&&(fmi3== 19))//
                   {
                      gzm_086 = 1;
                   }
                   if((spn3== 522015)&&(fmi3== 14))//
                   {
                      gzm_087 = 1;
                   }
                   if((spn3== 522015)&&(fmi3== 19))//
                   {
                      gzm_088 = 1;
                   }
                   if((spn3== 522053)&&(fmi3== 14))//
                   {
                      gzm_089 = 1;
                   }
                   if((spn3== 522053)&&(fmi3== 19))//
                   {
                      gzm_090 = 1;
                   }
                   if((spn3== 522020)&&(fmi3== 14))//
                   {
                      gzm_091 = 1;
                   }
                   if((spn3== 522020)&&(fmi3== 19))//
                   {
                      gzm_092 = 1;
                   }
                   if((spn3== 522021)&&(fmi3== 14))//
                   {
                      gzm_093 = 1;
                   }
                   if((spn3== 522021)&&(fmi3== 19))//
                   {
                      gzm_094 = 1;
                   }
                   if((spn3== 522022)&&(fmi3== 14))//
                   {
                      gzm_095 = 1;
                   }
                   if((spn3== 522022)&&(fmi3== 19))//
                   {
                      gzm_096 = 1;
                   }
                   if((spn3== 522023)&&(fmi3== 14))//
                   {
                      gzm_097 = 1;
                   }
                   if((spn3== 522023)&&(fmi3== 19))//
                   {
                      gzm_098 = 1;
                   }
                   if((spn3== 522063)&&(fmi3== 14))//
                   {
                      gzm_099 = 1;
                   }
                   if((spn3==522063 )&&(fmi3== 19))//
                   {
                      gzm_100 = 1;
                   }
                   if((spn3== 522051)&&(fmi3== 14))//
                   {
                      gzm_101 = 1;
                   }

                   if((spn3== 522051)&&(fmi3== 19))//
                   {
                      gzm_102 = 1;
                   }
                   if((spn3== 522065)&&(fmi3== 19))//
                   {
                      gzm_103 = 1;
                   }
                   if((spn3== 522030)&&(fmi3== 14))//
                   {
                      gzm_104 = 1;
                   }
                   if((spn3== 522030)&&(fmi3== 19))//
                   {
                      gzm_105 = 1;
                   }
                   if((spn3== 520217)&&(fmi3== 14))//
                   {
                      gzm_106 = 1;
                   }
                   if((spn3== 520217)&&(fmi3== 19))//
                   {
                      gzm_107 = 1;
                   }
                   if((spn3== 522035)&&(fmi3== 14))//
                   {
                      gzm_108 = 1;
                   }
                   if((spn3== 522035)&&(fmi3== 19))//
                   {
                      gzm_109 = 1;
                   }
                   if((spn3== 522036)&&(fmi3== 14))//
                   {
                      gzm_110 = 1;
                   }
                   if((spn3== 522036)&&(fmi3== 19))//
                   {
                      gzm_111 = 1;
                   }

                   if((spn3== 522037)&&(fmi3== 14))//
                   {
                      gzm_112 = 1;
                   }
                   if((spn3== 522037)&&(fmi3== 19))//
                   {
                      gzm_113 = 1;
                   }
                   if((spn3== 522038)&&(fmi3== 14))//
                   {
                      gzm_114 = 1;
                   }
                   if((spn3== 522038)&&(fmi3== 19))//
                   {
                      gzm_115 = 1;
                   }
                   if((spn3== 522039)&&(fmi3== 14))//
                   {
                      gzm_116 = 1;
                   }
                   if((spn3== 522039)&&(fmi3== 19))//
                   {
                      gzm_117 = 1;
                   }
                   if((spn3== 522040)&&(fmi3== 14))//
                   {
                      gzm_118 = 1;
                   }
                   if((spn3== 522040)&&(fmi3== 19))//
                   {
                      gzm_119 = 1;
                   }

                   if((spn3== 522041)&&(fmi3== 14))//
                   {
                      gzm_120 = 1;
                   }

                   if((spn3== 522041)&&(fmi3== 19))//
                   {
                      gzm_121 = 1;
                   }
                   if((spn3== 522042)&&(fmi3== 14))//
                   {
                      gzm_122 = 1;
                   }
                   if((spn3== 522042)&&(fmi3== 19))//
                   {
                      gzm_123 = 1;
                   }
                   if((spn3== 522043)&&(fmi3== 14))//
                   {
                      gzm_124 = 1;
                   }
                   if((spn3== 522043)&&(fmi3== 19))//
                   {
                      gzm_125 = 1;
                   }
                   if((spn3== 174)&&(fmi3== 3))//
                   {
                      gzm_126 = 1;
                   }
                   if((spn3== 174)&&(fmi3== 4))//
                   {
                      gzm_127 = 1;
                   }
                   if((spn3== 520221)&&(fmi3== 2))//
                   {
                      gzm_128 = 1;
                   }
                   if((spn3== 624)&&(fmi3== 12))//
                   {
                      gzm_129 = 1;
                   }
                   if((spn3== 624)&&(fmi3== 3))//
                   {
                      gzm_130 = 1;
                   }
                   if((spn3== 624)&&(fmi3== 4))//
                   {
                      gzm_131 = 1;
                   }
                   if((spn3== 520223)&&(fmi3== 20))//
                   {
                      gzm_132 = 1;
                   }
                   if((spn3== 2802)&&(fmi3== 14))//
                   {
                      gzm_133 = 1;
                   }
                   if((spn3== 2802)&&(fmi3== 12))//
                   {
                      gzm_134 = 1;
                   }
                   if((spn3== 105)&&(fmi3== 3))//
                   {
                      gzm_135 = 1;
                   }
                   if((spn3== 105)&&(fmi3== 4))//
                   {
                      gzm_136 = 1;
                   }
                   if((spn3== 520210)&&(fmi3== 15))//
                   {
                      gzm_137 = 1;
                   }
                   if((spn3== 520210)&&(fmi3== 15))//
                   {
                      gzm_138 = 1;
                   }
                   if((spn3== 507)&&(fmi3== 11))//
                   {
                      gzm_139 = 1;
                   }
                   if((spn3== 507)&&(fmi3== 11))//
                   {
                      gzm_140 = 1;
                   }
                   if((spn3== 520210)&&(fmi3== 15))//
                   {
                      gzm_141 = 1;
                   }
                   if((spn3== 520210)&&(fmi3== 15))//
                   {
                      gzm_142 = 1;
                   }
                   if((spn3== 507)&&(fmi3== 11))//
                   {
                      gzm_143 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 15))//
                   {
                      gzm_144 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 17))//
                   {
                      gzm_145 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 16))//
                   {
                      gzm_146 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 18))//
                   {
                      gzm_147 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 5))//
                   {
                      gzm_148 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 11))//
                   {
                      gzm_149 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 6))//
                   {
                      gzm_150 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 3))//
                   {
                      gzm_151 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 7))//
                   {
                      gzm_152 = 1;
                   }
                   if((spn3== 1413)&&(fmi3== 4))//
                   {
                      gzm_153 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 15))//
                   {
                      gzm_154 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 17))//
                   {
                      gzm_155 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 16))//
                   {
                      gzm_156 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 18))//
                   {
                      gzm_157 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 5))//
                   {
                      gzm_158 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 11))//
                   {
                      gzm_159 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 6))//
                   {
                      gzm_160 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 3))//
                   {
                      gzm_161 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 7))//
                   {
                      gzm_162 = 1;
                   }
                   if((spn3== 1414)&&(fmi3== 4))//
                   {
                      gzm_163 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 15))//
                   {
                      gzm_164 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 17))//
                   {
                      gzm_165 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 16))//
                   {
                      gzm_166 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 16))//
                   {
                      gzm_167 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 5))//
                   {
                      gzm_168 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 11))//
                   {
                      gzm_169 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 6))//
                   {
                      gzm_170 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 3))//
                   {
                      gzm_171 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 7))//
                   {
                      gzm_172 = 1;
                   }
                   if((spn3== 1415)&&(fmi3== 4))//
                   {
                      gzm_173 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 15))//
                   {
                      gzm_174 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 17))//
                   {
                      gzm_175 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 16))//
                   {
                      gzm_176 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 18))//
                   {
                      gzm_177 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 5))//
                   {
                      gzm_178 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 11))//
                   {
                      gzm_179 = 1;
                   }

                   if((spn3== 1416)&&(fmi3== 6))//
                   {
                      gzm_180 = 1;
                   }

                   if((spn3== 1416)&&(fmi3== 3))//
                   {
                      gzm_181 = 1;
                   }
                   if((spn3== 1416)&&(fmi3== 7))//
                   {
                      gzm_182 = 1;
                   }

                   if((spn3== 1416)&&(fmi3== 4))//
                   {
                      gzm_183 = 1;
                   }
                   if((spn3== 1417)&&(fmi3== 15))//
                   {
                      gzm_184 = 1;
                   }

                   if((spn3== 1417)&&(fmi3== 17))//
                   {
                      gzm_185 = 1;
                   }
                   if((spn3== 1417)&&(fmi3== 16))//
                   {
                      gzm_186 = 1;
                   }

                   if((spn3== 1417)&&(fmi3== 18))//
                   {
                      gzm_187 = 1;
                   }
                   if((spn3== 1417)&&(fmi3== 5))//
                   {
                      gzm_188 = 1;
                   }

                   if((spn3== 1417)&&(fmi3== 11))//
                   {
                      gzm_189 = 1;
                   }
                   if((spn3== 1417)&&(fmi3== 6))//
                   {
                      gzm_190 = 1;
                   }

                   if((spn3== 1417)&&(fmi3== 3))//
                   {
                      gzm_191 = 1;
                   }
                   if((spn3== 1417)&&(fmi3== 7))//
                   {
                      gzm_192 = 1;
                   }

                   if((spn3== 1417)&&(fmi3== 4))//
                   {
                      gzm_193 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 15))//
                   {
                      gzm_194 = 1;
                   }

                   if((spn3== 1418)&&(fmi3== 17))//
                   {
                      gzm_195 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 16))//
                   {
                      gzm_196 = 1;
                   }

                   if((spn3== 1418)&&(fmi3== 18))//
                   {
                      gzm_197 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 5))//
                   {
                      gzm_198 = 1;
                   }

                   if((spn3== 1418)&&(fmi3== 11))//
                   {
                      gzm_199 = 1;
                   }




                   //200 分界线

                   if((spn3== 1418)&&(fmi3== 6))//
                   {
                      gzm_200 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 3))//
                   {
                      gzm_201 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 7))//
                   {
                      gzm_202 = 1;
                   }
                   if((spn3== 1418)&&(fmi3== 4))//
                   {
                      gzm_203 = 1;
                   }

                   if((spn3== 1442)&&(fmi3== 7))//
                   {
                      gzm_204 = 1;
                   }
                   if((spn3== 1442)&&(fmi3== 9))//
                   {
                      gzm_205 = 1;
                   }
                   if((spn3== 1442)&&(fmi3== 10))//
                   {
                      gzm_206 = 1;
                   }
                   if((spn3== 596)&&(fmi3== 2))//
                   {
                      gzm_207 = 1;
                   }
                   if((spn3== 520219)&&(fmi3== 5))//
                   {
                      gzm_208 = 1;
                   }
                   if((spn3== 520219)&&(fmi3== 3))//
                   {
                      gzm_209 = 1;
                   }

                   if((spn3== 520219)&&(fmi3== 4))//
                   {
                      gzm_210 = 1;
                   }
                   if((spn3== 1323)&&(fmi3== 3))//
                   {
                      gzm_211 = 1;
                   }
                   if((spn3== 1332)&&(fmi3== 3))//
                   {
                      gzm_212 = 1;
                   }
                   if((spn3== 1333)&&(fmi3== 3))//
                   {
                      gzm_213 = 1;
                   }
                   if((spn3== 1334)&&(fmi3== 3))//
                   {
                      gzm_214 = 1;
                   }
                   if((spn3== 1324)&&(fmi3== 3))//
                   {
                      gzm_215 = 1;
                   }
                   if((spn3== 1325)&&(fmi3== 3))//
                   {
                      gzm_216 = 1;
                   }
                   if((spn3== 1326)&&(fmi3== 3))//
                   {
                      gzm_217 = 1;
                   }
                   if((spn3== 1327)&&(fmi3== 3))//
                   {
                      gzm_218 = 1;
                   }
                   if((spn3== 1328)&&(fmi3== 3))//
                   {
                      gzm_219 = 1;
                   }
                   if((spn3== 1329)&&(fmi3== 3))//
                   {
                      gzm_220 = 1;
                   }
                   if((spn3== 1330)&&(fmi3== 3))//
                   {
                      gzm_221 = 1;
                   }
                   if((spn3== 1331)&&(fmi3== 3))//
                   {
                      gzm_222 = 1;
                   }
                   if((spn3== 1322)&&(fmi3== 3))//
                   {
                      gzm_223 = 1;
                   }
                   if((spn3== 976)&&(fmi3== 19))//
                   {
                      gzm_224 = 1;
                   }
                   if((spn3== 976)&&(fmi3== 3))//
                   {
                      gzm_225 = 1;
                   }
                   if((spn3== 976)&&(fmi3== 4))//
                   {
                      gzm_226 = 1;
                   }
                   if((spn3== 98)&&(fmi3== 2))//
                   {
                      gzm_227 = 1;
                   }
                   if((spn3== 98)&&(fmi3== 3))//
                   {
                      gzm_228 = 1;
                   }
                   if((spn3== 98)&&(fmi3== 4))//
                   {
                      gzm_229 = 1;
                   }
                   if((spn3== 100)&&(fmi3== 17))//
                   {
                      gzm_230 = 1;
                   }
                   if((spn3== 100)&&(fmi3== 15))//
                   {
                      gzm_231 = 1;
                   }
                   if((spn3== 100)&&(fmi3== 16))//
                   {
                      gzm_232 = 1;
                   }
                   if((spn3== 100)&&(fmi3== 18))//
                   {
                      gzm_233 = 1;
                   }
                   if((spn3== 175)&&(fmi3== 15))//
                   {
                      gzm_234 = 1;
                   }


                   if((spn3== 175)&&(fmi3== 3))//
                   {
                      gzm_235 = 1;
                   }
                   if((spn3==175 )&&(fmi3== 4))//
                   {
                      gzm_236 = 1;
                   }
                   if((spn3== 110)&&(fmi3== 15))//
                   {
                      gzm_237 = 1;
                   }
                   if((spn3== 1443)&&(fmi3== 7))//
                   {
                      gzm_238 = 1;
                   }
                   if((spn3== 1443)&&(fmi3== 9))//
                   {
                      gzm_239 = 1;
                   }
                   if((spn3== 1443)&&(fmi3== 10))//
                   {
                      gzm_240 = 1;
                   }
                   if((spn3== 523470)&&(fmi3== 21))//
                   {
                      gzm_241 = 1;
                   }
                   if((spn3== 520241)&&(fmi3== 11))//
                   {
                      gzm_242 = 1;
                   }
                   if((spn3== 520241)&&(fmi3== 14))//
                   {
                      gzm_243 = 1;
                   }
                   if((spn3== 520241)&&(fmi3== 0))//
                   {
                      gzm_244 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 15))//
                   {
                      gzm_245 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 17))//
                   {
                      gzm_246 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 3))//
                   {
                      gzm_247 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 3))//
                   {
                      gzm_248 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 4))//
                   {
                      gzm_249 = 1;
                   }
                   if((spn3== 157)&&(fmi3== 4))//
                   {
                      gzm_250 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 16))//
                   {
                      gzm_251 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 7))//
                   {
                      gzm_252 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 5))//
                   {
                      gzm_253 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 0))//
                   {
                      gzm_254 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 1))//
                   {
                      gzm_255 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 20))//
                   {
                      gzm_256 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 21))//
                   {
                      gzm_257 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 18))//
                   {
                      gzm_258 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 23))//
                   {
                      gzm_259 = 1;
                   }
                   if((spn3== 520243)&&(fmi3== 24))//
                   {
                      gzm_260 = 1;
                   }
                   if((spn3== 520277)&&(fmi3== 3))//
                   {
                      gzm_261 = 1;
                   }
                   if((spn3== 520277)&&(fmi3== 4))//
                   {
                      gzm_262 = 1;
                   }
                   if((spn3== 520278)&&(fmi3== 3))//
                   {
                      gzm_263 = 1;
                   }
                   if((spn3== 520278)&&(fmi3== 4))//
                   {
                      gzm_264 = 1;
                   }
                   if((spn3== 3509)&&(fmi3== 3))//
                   {
                      gzm_265 = 1;
                   }
                   if((spn3== 3509)&&(fmi3== 4))//
                   {
                      gzm_266 = 1;
                   }
                   if((spn3== 3510)&&(fmi3== 3))//
                   {
                      gzm_267 = 1;
                   }
                   if((spn3== 3510)&&(fmi3== 4))//
                   {
                      gzm_268 = 1;
                   }
                   if((spn3== 3511)&&(fmi3== 3))//
                   {
                      gzm_269 = 1;
                   }
                   if((spn3== 3511)&&(fmi3== 4))//
                   {
                      gzm_270 = 1;
                   }
                   if((spn3== 107)&&(fmi3== 7))//
                   {
                      gzm_271 = 1;
                   }
                   if((spn3== 520289)&&(fmi3== 11))//
                   {
                      gzm_272 = 1;
                   }
                   if((spn3== 522014)&&(fmi3== 1))//
                   {
                      gzm_273 = 1;
                   }
                   if((spn3== 522014)&&(fmi3== 2))//
                   {
                      gzm_274 = 1;
                   }
                   if((spn3== 99)&&(fmi3== 11))//
                   {
                      gzm_275 = 1;
                   }
                   if((spn3== 99)&&(fmi3== 7))//
                   {
                      gzm_276 = 1;
                   }
                   if((spn3== 1675)&&(fmi3== 3))//
                   {
                      gzm_277 = 1;
                   }
                   if((spn3== 1675)&&(fmi3== 4))//
                   {
                      gzm_278 = 1;
                   }
                   if((spn3== 1675)&&(fmi3== 5))//
                   {
                      gzm_279 = 1;
                   }

                   if((spn3== 520253)&&(fmi3== 11))//
                   {
                      gzm_280 = 1;
                   }

                   if((spn3== 1136)&&(fmi3== 4))//
                   {
                      gzm_281 = 1;
                   }
                   if((spn3== 1136)&&(fmi3== 3))//
                   {
                      gzm_282 = 1;
                   }

                   if((spn3== 4346)&&(fmi3== 5))//
                   {
                      gzm_283 = 1;
                   }
                   if((spn3== 4346)&&(fmi3== 3))//
                   {
                      gzm_284 = 1;
                   }

                   if((spn3== 4346)&&(fmi3== 4))//
                   {
                      gzm_285 = 1;
                   }
                   if((spn3== 4344)&&(fmi3== 5))//
                   {
                      gzm_286 = 1;
                   }

                   if((spn3== 4344)&&(fmi3== 3))//
                   {
                      gzm_287 = 1;
                   }
                   if((spn3== 4344)&&(fmi3== 4))//
                   {
                      gzm_288 = 1;
                   }

                   if((spn3== 523003)&&(fmi3== 5))//
                   {
                      gzm_289 = 1;
                   }
                   if((spn3== 523003)&&(fmi3== 3))//
                   {
                      gzm_290 = 1;
                   }

                   if((spn3== 523003)&&(fmi3== 4))//
                   {
                      gzm_291 = 1;
                   }
                   if((spn3== 4340)&&(fmi3== 5))//
                   {
                      gzm_292 = 1;
                   }

                   if((spn3== 4340)&&(fmi3== 3))//
                   {
                      gzm_293 = 1;
                   }
                   if((spn3== 4340)&&(fmi3== 4))//
                   {
                      gzm_294 = 1;
                   }

                   if((spn3== 3363)&&(fmi3== 5))//
                   {
                      gzm_295 = 1;
                   }
                   if((spn3== 3363)&&(fmi3== 3))//
                   {
                      gzm_296 = 1;
                   }

                   if((spn3== 3363)&&(fmi3== 4))//
                   {
                      gzm_297 = 1;
                   }
                   if((spn3== 84)&&(fmi3== 0))//
                   {
                      gzm_298 = 1;
                   }

                   if((spn3== 84)&&(fmi3== 2))//
                   {
                      gzm_299 = 1;
                   }

                   //300 分界线
                   if((spn3== 1624)&&(fmi3== 3))//
                   {
                      gzm_300 = 1;
                   }

                   if((spn3== 1624)&&(fmi3== 4))//
                   {
                      gzm_301 = 1;
                   }
                   if((spn3== 1624)&&(fmi3== 8))//
                   {
                      gzm_302 = 1;
                   }

                   if((spn3== 520250)&&(fmi3== 5))//
                   {
                      gzm_303 = 1;
                   }
                   if((spn3== 520250)&&(fmi3== 3))//
                   {
                      gzm_304 = 1;
                   }

                   if((spn3== 520250)&&(fmi3== 4))//
                   {
                      gzm_305 = 1;
                   }
                   if((spn3== 520264)&&(fmi3== 3))//
                   {
                      gzm_306 = 1;
                   }

                   if((spn3== 520264)&&(fmi3== 4))//
                   {
                      gzm_307 = 1;
                   }
                   if((spn3== 522000)&&(fmi3== 12))//
                   {
                      gzm_308 = 1;
                   }

                   if((spn3== 520252)&&(fmi3== 2))//
                   {
                      gzm_309 = 1;
                   }

                   if((spn3== 520277)&&(fmi3== 7))//
                   {
                      gzm_310 = 1;
                   }

                   if((spn3== 520218)&&(fmi3== 14))//
                   {
                      gzm_311 = 1;
                   }
                   if((spn3== 520218)&&(fmi3== 19))//
                   {
                      gzm_312 = 1;
                   }
                /*******************************************************************************************************/
                //spn4

                   /*****************************************************************************************************/
                   //故障码解析

                    if((spn4==1351)&&(fmi4==5))//空调压缩机开路
                    {
                       gzm_001 = 1;
                    }

                    if((spn4==1351)&&(fmi4==3)) //空调压缩机对电源短路
                    {
                        gzm_002 = 1;

                    }

                    if((spn4==1351)&&(fmi4==4))//空调压缩机对地短路
                    {
                       gzm_003 = 1;
                    }

                    if((spn4==91)&&(fmi4==7)) //油门与刹车信号不可信
                    {
                        gzm_004 = 1;

                    }

                    if((spn4==132)&&(fmi4==3))//空气质量流量传感器电压超上限
                    {
                       gzm_005 = 1;
                    }

                    if((spn4==132)&&(fmi4==4)) //空气质量流量传感器电压超下限
                    {
                        gzm_006 = 1;

                    }

                    if((spn4==2898)&&(fmi4==7))//007进气加热常开故障
                    {
                       gzm_007 = 1;
                    }

                    if((spn4==520252)&&(fmi4==2)) //008油门踏板1与油门踏板2的两倍的信号关系不可信
                    {
                        gzm_008 = 1;

                    }

                    if((spn4==91)&&(fmi4==3))//009油门踏板1电压值高出上限门槛值
                    {
                       gzm_009 = 1;
                    }

                    if((spn4== 91)&&(fmi4== 4))//10油门踏板1电压值低于下限门槛值
                    {
                       gzm_010 = 1;
                    }

                    if((spn4== 520252)&&(fmi4== 2))//11 油门踏板2与油门踏板1的1/2的信号关系不可信
                    {
                       gzm_011 = 1;
                    }

                    if((spn4== 29)&&(fmi4== 3))//12 油门踏板2电压值高出上限门槛值
                    {
                       gzm_012 = 1;
                    }

                    if((spn4== 29)&&(fmi4== 4))//13 油门踏板2电压值低于下限门槛值
                    {
                       gzm_013 = 1;
                    }

                    if((spn4== 102)&&(fmi4== 2))//14 大气压力传感器信号不可信
                    {
                       gzm_014 = 1;
                    }

                    if((spn4== 108)&&(fmi4== 3))//15 大气压力传感器电压高出上限门槛
                    {
                       gzm_015 = 1;
                    }

                    if((spn4== 108)&&(fmi4== 4))//16 大气压力传感器电压低于下限门槛
                    {
                       gzm_016 = 1;
                    }

                    if((spn4== 2898)&&(fmi4== 5))//17进气加热器开路
                    {
                       gzm_017 = 1;
                    }

                    if((spn4== 2898)&&(fmi4== 3))//18 进气加热器对电源开路
                    {
                       gzm_018 = 1;
                    }

                    if((spn4== 2898)&&(fmi4== 4))//19
                    {
                       gzm_019 = 1;
                    }

                    if((spn4== 168)&&(fmi4== 4))//20
                    {
                       gzm_020 = 1;
                    }


                    if((spn4== 168)&&(fmi4== 3))//21
                    {
                       gzm_021 = 1;
                    }

                    if((spn4== 102)&&(fmi4== 2))//22
                    {
                       gzm_022 = 1;
                    }

                    if((spn4== 102)&&(fmi4== 3))//
                    {
                       gzm_023 = 1;
                    }

                    if((spn4== 102)&&(fmi4== 4))//
                    {
                       gzm_024 = 1;
                    }

                    if((spn4== 597)&&(fmi4== 11))//
                    {
                       gzm_025 = 1;
                    }

                    if((spn4== 597)&&(fmi4== 7))//
                    {
                       gzm_026 = 1;
                    }

                    if((spn4== 597)&&(fmi4== 2))//
                    {
                       gzm_027 = 1;
                    }

                    if((spn4== 597)&&(fmi4== 19))//
                    {
                       gzm_028 = 1;
                    }

                    if((spn4== 110)&&(fmi4== 18))//
                    {
                       gzm_029 = 1;
                    }

                    if((spn4== 110)&&(fmi4== 17))//
                    {
                       gzm_030 = 1;
                    }

                    if((spn4== 110)&&(fmi4== 2))//
                    {
                       gzm_031 = 1;
                    }

                    if((spn4== 190)&&(fmi4== 2))//
                    {
                       gzm_032 = 1;
                    }


                    if((spn4== 598)&&(fmi4== 2))//
                    {
                       gzm_033 = 1;
                    }

                    if((spn4== 520198)&&(fmi4== 11))//
                    {
                       gzm_034 = 1;
                    }


                    if((spn4== 626)&&(fmi4== 5))//
                    {
                       gzm_035 = 1;
                    }
                    if((spn4== 626)&&(fmi4== 3))//
                    {
                       gzm_036 = 1;
                    }
                    if((spn4== 626)&&(fmi4== 4))//
                    {
                       gzm_037 = 1;
                    }
                    if((spn4== 110)&&(fmi4== 2))//
                    {
                       gzm_038 = 1;
                    }
                    if((spn4== 110)&&(fmi4== 15))//
                    {
                       gzm_039 = 1;
                    }
                    if((spn4== 110)&&(fmi4== 3))//
                    {
                       gzm_040 = 1;
                    }
                    if((spn4== 110)&&(fmi4== 4))//
                    {
                       gzm_041 = 1;
                    }
                    if((spn4== 520203)&&(fmi4== 5))//
                    {
                       gzm_042 = 1;
                    }
                    if((spn4== 4203)&&(fmi4== 13))//
                    {
                       gzm_043 = 1;
                    }
                    if((spn4== 4201)&&(fmi4== 12))//
                    {
                       gzm_044 = 1;
                    }
                    if((spn4== 4201)&&(fmi4== 2))//
                    {
                       gzm_045 = 1;
                    }
                    if((spn4== 4201)&&(fmi4== 11))//
                    {
                       gzm_046 = 1;
                    }
                    if((spn4== 4201)&&(fmi4== 13))//
                    {
                       gzm_047 = 1;
                    }
                    if((spn4== 4203)&&(fmi4== 12))//
                    {
                       gzm_048 = 1;
                    }
                    if((spn4== 4203)&&(fmi4== 3))//
                    {
                       gzm_049 = 1;
                    }
                    if((spn4== 4203)&&(fmi4== 4))//
                    {
                       gzm_050 = 1;
                    }

                    if((spn4== 4203)&&(fmi4== 2))//
                    {
                       gzm_051 = 1;
                    }

                    if((spn4== 4201)&&(fmi4== 14))//
                    {
                       gzm_052 = 1;
                    }
                    if((spn4== 1769)&&(fmi4== 11))//
                    {
                       gzm_053 = 1;
                    }
                    if((spn4== 1623)&&(fmi4== 5))//
                    {
                       gzm_054 = 1;
                    }
                    if((spn4== 1623)&&(fmi4== 3))//
                    {
                       gzm_055 = 1;
                    }
                    if((spn4== 1623)&&(fmi4== 4))//
                    {
                       gzm_056 = 1;
                    }
                    if((spn4== 520208)&&(fmi4== 5))//
                    {
                       gzm_057 = 1;
                    }
                    if((spn4== 520208)&&(fmi4== 3))//
                    {
                       gzm_058 = 1;
                    }
                    if((spn4== 520208)&&(fmi4== 4))//
                    {
                       gzm_059 = 1;
                    }
                    if((spn4== 4815)&&(fmi4== 7))//
                    {
                       gzm_060 = 1;
                    }
                    if((spn4== 4815)&&(fmi4== 9))//
                    {
                       gzm_061 = 1;
                    }

                    if((spn4== 4815)&&(fmi4== 10))//
                    {
                       gzm_062 = 1;
                    }
                    if((spn4== 4815)&&(fmi4== 5))//
                    {
                       gzm_063 = 1;
                    }
                    if((spn4== 4815)&&(fmi4== 3))//
                    {
                       gzm_064 = 1;
                    }
                    if((spn4== 4815)&&(fmi4== 4))//
                    {
                       gzm_065 = 1;
                    }
                    if((spn4== 1639)&&(fmi4== 3))//
                    {
                       gzm_066 = 1;
                    }
                    if((spn4== 1639)&&(fmi4== 4))//
                    {
                       gzm_067 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 5))//
                    {
                       gzm_068 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 3))//
                    {
                       gzm_069 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 4))//
                    {
                       gzm_070 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 10))//
                    {
                       gzm_071 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 9))//
                    {
                       gzm_072 = 1;
                    }
                    if((spn4== 520261)&&(fmi4== 7))//
                    {
                       gzm_073 = 1;
                    }
                    if((spn4== 95)&&(fmi4== 5))//
                    {
                       gzm_074 = 1;
                    }
                    if((spn4== 95)&&(fmi4== 3))//
                    {
                       gzm_075 = 1;
                    }
                    if((spn4== 95)&&(fmi4== 4))//
                    {
                       gzm_076 = 1;
                    }
                    if((spn4== 520264)&&(fmi4== 11))//
                    {
                       gzm_077 = 1;
                    }
                    if((spn4== 522064)&&(fmi4== 19))//
                    {
                       gzm_078 = 1;
                    }
                    if((spn4== 522056)&&(fmi4== 14))//
                    {
                       gzm_079 = 1;
                    }
                    if((spn4== 522056)&&(fmi4== 19))//
                    {
                       gzm_080 = 1;
                    }
                    if((spn4== 522052)&&(fmi4== 14))//
                    {
                       gzm_081 = 1;
                    }
                    if((spn4== 522052)&&(fmi4== 19))//
                    {
                       gzm_082 = 1;
                    }
                    if((spn4== 522062)&&(fmi4== 14))//
                    {
                       gzm_083 = 1;
                    }
                    if((spn4== 522062)&&(fmi4== 19))//
                    {
                       gzm_084 = 1;
                    }
                    if((spn4== 522013)&&(fmi4== 14))//
                    {
                       gzm_085 = 1;
                    }
                    if((spn4== 522013)&&(fmi4== 19))//
                    {
                       gzm_086 = 1;
                    }
                    if((spn4== 522015)&&(fmi4== 14))//
                    {
                       gzm_087 = 1;
                    }
                    if((spn4== 522015)&&(fmi4== 19))//
                    {
                       gzm_088 = 1;
                    }
                    if((spn4== 522053)&&(fmi4== 14))//
                    {
                       gzm_089 = 1;
                    }
                    if((spn4== 522053)&&(fmi4== 19))//
                    {
                       gzm_090 = 1;
                    }
                    if((spn4== 522020)&&(fmi4== 14))//
                    {
                       gzm_091 = 1;
                    }
                    if((spn4== 522020)&&(fmi4== 19))//
                    {
                       gzm_092 = 1;
                    }
                    if((spn4== 522021)&&(fmi4== 14))//
                    {
                       gzm_093 = 1;
                    }
                    if((spn4== 522021)&&(fmi4== 19))//
                    {
                       gzm_094 = 1;
                    }
                    if((spn4== 522022)&&(fmi4== 14))//
                    {
                       gzm_095 = 1;
                    }
                    if((spn4== 522022)&&(fmi4== 19))//
                    {
                       gzm_096 = 1;
                    }
                    if((spn4== 522023)&&(fmi4== 14))//
                    {
                       gzm_097 = 1;
                    }
                    if((spn4== 522023)&&(fmi4== 19))//
                    {
                       gzm_098 = 1;
                    }
                    if((spn4== 522063)&&(fmi4== 14))//
                    {
                       gzm_099 = 1;
                    }
                    if((spn4==522063 )&&(fmi4== 19))//
                    {
                       gzm_100 = 1;
                    }
                    if((spn4== 522051)&&(fmi4== 14))//
                    {
                       gzm_101 = 1;
                    }

                    if((spn4== 522051)&&(fmi4== 19))//
                    {
                       gzm_102 = 1;
                    }
                    if((spn4== 522065)&&(fmi4== 19))//
                    {
                       gzm_103 = 1;
                    }
                    if((spn4== 522030)&&(fmi4== 14))//
                    {
                       gzm_104 = 1;
                    }
                    if((spn4== 522030)&&(fmi4== 19))//
                    {
                       gzm_105 = 1;
                    }
                    if((spn4== 520217)&&(fmi4== 14))//
                    {
                       gzm_106 = 1;
                    }
                    if((spn4== 520217)&&(fmi4== 19))//
                    {
                       gzm_107 = 1;
                    }
                    if((spn4== 522035)&&(fmi4== 14))//
                    {
                       gzm_108 = 1;
                    }
                    if((spn4== 522035)&&(fmi4== 19))//
                    {
                       gzm_109 = 1;
                    }
                    if((spn4== 522036)&&(fmi4== 14))//
                    {
                       gzm_110 = 1;
                    }
                    if((spn4== 522036)&&(fmi4== 19))//
                    {
                       gzm_111 = 1;
                    }

                    if((spn4== 522037)&&(fmi4== 14))//
                    {
                       gzm_112 = 1;
                    }
                    if((spn4== 522037)&&(fmi4== 19))//
                    {
                       gzm_113 = 1;
                    }
                    if((spn4== 522038)&&(fmi4== 14))//
                    {
                       gzm_114 = 1;
                    }
                    if((spn4== 522038)&&(fmi4== 19))//
                    {
                       gzm_115 = 1;
                    }
                    if((spn4== 522039)&&(fmi4== 14))//
                    {
                       gzm_116 = 1;
                    }
                    if((spn4== 522039)&&(fmi4== 19))//
                    {
                       gzm_117 = 1;
                    }
                    if((spn4== 522040)&&(fmi4== 14))//
                    {
                       gzm_118 = 1;
                    }
                    if((spn4== 522040)&&(fmi4== 19))//
                    {
                       gzm_119 = 1;
                    }

                    if((spn4== 522041)&&(fmi4== 14))//
                    {
                       gzm_120 = 1;
                    }

                    if((spn4== 522041)&&(fmi4== 19))//
                    {
                       gzm_121 = 1;
                    }
                    if((spn4== 522042)&&(fmi4== 14))//
                    {
                       gzm_122 = 1;
                    }
                    if((spn4== 522042)&&(fmi4== 19))//
                    {
                       gzm_123 = 1;
                    }
                    if((spn4== 522043)&&(fmi4== 14))//
                    {
                       gzm_124 = 1;
                    }
                    if((spn4== 522043)&&(fmi4== 19))//
                    {
                       gzm_125 = 1;
                    }
                    if((spn4== 174)&&(fmi4== 3))//
                    {
                       gzm_126 = 1;
                    }
                    if((spn4== 174)&&(fmi4== 4))//
                    {
                       gzm_127 = 1;
                    }
                    if((spn4== 520221)&&(fmi4== 2))//
                    {
                       gzm_128 = 1;
                    }
                    if((spn4== 624)&&(fmi4== 12))//
                    {
                       gzm_129 = 1;
                    }
                    if((spn4== 624)&&(fmi4== 3))//
                    {
                       gzm_130 = 1;
                    }
                    if((spn4== 624)&&(fmi4== 4))//
                    {
                       gzm_131 = 1;
                    }
                    if((spn4== 520223)&&(fmi4== 20))//
                    {
                       gzm_132 = 1;
                    }
                    if((spn4== 2802)&&(fmi4== 14))//
                    {
                       gzm_133 = 1;
                    }
                    if((spn4== 2802)&&(fmi4== 12))//
                    {
                       gzm_134 = 1;
                    }
                    if((spn4== 105)&&(fmi4== 3))//
                    {
                       gzm_135 = 1;
                    }
                    if((spn4== 105)&&(fmi4== 4))//
                    {
                       gzm_136 = 1;
                    }
                    if((spn4== 520210)&&(fmi4== 15))//
                    {
                       gzm_137 = 1;
                    }
                    if((spn4== 520210)&&(fmi4== 15))//
                    {
                       gzm_138 = 1;
                    }
                    if((spn4== 507)&&(fmi4== 11))//
                    {
                       gzm_139 = 1;
                    }
                    if((spn4== 507)&&(fmi4== 11))//
                    {
                       gzm_140 = 1;
                    }
                    if((spn4== 520210)&&(fmi4== 15))//
                    {
                       gzm_141 = 1;
                    }
                    if((spn4== 520210)&&(fmi4== 15))//
                    {
                       gzm_142 = 1;
                    }
                    if((spn4== 507)&&(fmi4== 11))//
                    {
                       gzm_143 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 15))//
                    {
                       gzm_144 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 17))//
                    {
                       gzm_145 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 16))//
                    {
                       gzm_146 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 18))//
                    {
                       gzm_147 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 5))//
                    {
                       gzm_148 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 11))//
                    {
                       gzm_149 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 6))//
                    {
                       gzm_150 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 3))//
                    {
                       gzm_151 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 7))//
                    {
                       gzm_152 = 1;
                    }
                    if((spn4== 1413)&&(fmi4== 4))//
                    {
                       gzm_153 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 15))//
                    {
                       gzm_154 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 17))//
                    {
                       gzm_155 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 16))//
                    {
                       gzm_156 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 18))//
                    {
                       gzm_157 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 5))//
                    {
                       gzm_158 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 11))//
                    {
                       gzm_159 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 6))//
                    {
                       gzm_160 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 3))//
                    {
                       gzm_161 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 7))//
                    {
                       gzm_162 = 1;
                    }
                    if((spn4== 1414)&&(fmi4== 4))//
                    {
                       gzm_163 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 15))//
                    {
                       gzm_164 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 17))//
                    {
                       gzm_165 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 16))//
                    {
                       gzm_166 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 16))//
                    {
                       gzm_167 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 5))//
                    {
                       gzm_168 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 11))//
                    {
                       gzm_169 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 6))//
                    {
                       gzm_170 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 3))//
                    {
                       gzm_171 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 7))//
                    {
                       gzm_172 = 1;
                    }
                    if((spn4== 1415)&&(fmi4== 4))//
                    {
                       gzm_173 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 15))//
                    {
                       gzm_174 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 17))//
                    {
                       gzm_175 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 16))//
                    {
                       gzm_176 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 18))//
                    {
                       gzm_177 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 5))//
                    {
                       gzm_178 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 11))//
                    {
                       gzm_179 = 1;
                    }

                    if((spn4== 1416)&&(fmi4== 6))//
                    {
                       gzm_180 = 1;
                    }

                    if((spn4== 1416)&&(fmi4== 3))//
                    {
                       gzm_181 = 1;
                    }
                    if((spn4== 1416)&&(fmi4== 7))//
                    {
                       gzm_182 = 1;
                    }

                    if((spn4== 1416)&&(fmi4== 4))//
                    {
                       gzm_183 = 1;
                    }
                    if((spn4== 1417)&&(fmi4== 15))//
                    {
                       gzm_184 = 1;
                    }

                    if((spn4== 1417)&&(fmi4== 17))//
                    {
                       gzm_185 = 1;
                    }
                    if((spn4== 1417)&&(fmi4== 16))//
                    {
                       gzm_186 = 1;
                    }

                    if((spn4== 1417)&&(fmi4== 18))//
                    {
                       gzm_187 = 1;
                    }
                    if((spn4== 1417)&&(fmi4== 5))//
                    {
                       gzm_188 = 1;
                    }

                    if((spn4== 1417)&&(fmi4== 11))//
                    {
                       gzm_189 = 1;
                    }
                    if((spn4== 1417)&&(fmi4== 6))//
                    {
                       gzm_190 = 1;
                    }

                    if((spn4== 1417)&&(fmi4== 3))//
                    {
                       gzm_191 = 1;
                    }
                    if((spn4== 1417)&&(fmi4== 7))//
                    {
                       gzm_192 = 1;
                    }

                    if((spn4== 1417)&&(fmi4== 4))//
                    {
                       gzm_193 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 15))//
                    {
                       gzm_194 = 1;
                    }

                    if((spn4== 1418)&&(fmi4== 17))//
                    {
                       gzm_195 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 16))//
                    {
                       gzm_196 = 1;
                    }

                    if((spn4== 1418)&&(fmi4== 18))//
                    {
                       gzm_197 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 5))//
                    {
                       gzm_198 = 1;
                    }

                    if((spn4== 1418)&&(fmi4== 11))//
                    {
                       gzm_199 = 1;
                    }




                    //200 分界线

                    if((spn4== 1418)&&(fmi4== 6))//
                    {
                       gzm_200 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 3))//
                    {
                       gzm_201 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 7))//
                    {
                       gzm_202 = 1;
                    }
                    if((spn4== 1418)&&(fmi4== 4))//
                    {
                       gzm_203 = 1;
                    }

                    if((spn4== 1442)&&(fmi4== 7))//
                    {
                       gzm_204 = 1;
                    }
                    if((spn4== 1442)&&(fmi4== 9))//
                    {
                       gzm_205 = 1;
                    }
                    if((spn4== 1442)&&(fmi4== 10))//
                    {
                       gzm_206 = 1;
                    }
                    if((spn4== 596)&&(fmi4== 2))//
                    {
                       gzm_207 = 1;
                    }
                    if((spn4== 520219)&&(fmi4== 5))//
                    {
                       gzm_208 = 1;
                    }
                    if((spn4== 520219)&&(fmi4== 3))//
                    {
                       gzm_209 = 1;
                    }

                    if((spn4== 520219)&&(fmi4== 4))//
                    {
                       gzm_210 = 1;
                    }
                    if((spn4== 1323)&&(fmi4== 3))//
                    {
                       gzm_211 = 1;
                    }
                    if((spn4== 1332)&&(fmi4== 3))//
                    {
                       gzm_212 = 1;
                    }
                    if((spn4== 1333)&&(fmi4== 3))//
                    {
                       gzm_213 = 1;
                    }
                    if((spn4== 1334)&&(fmi4== 3))//
                    {
                       gzm_214 = 1;
                    }
                    if((spn4== 1324)&&(fmi4== 3))//
                    {
                       gzm_215 = 1;
                    }
                    if((spn4== 1325)&&(fmi4== 3))//
                    {
                       gzm_216 = 1;
                    }
                    if((spn4== 1326)&&(fmi4== 3))//
                    {
                       gzm_217 = 1;
                    }
                    if((spn4== 1327)&&(fmi4== 3))//
                    {
                       gzm_218 = 1;
                    }
                    if((spn4== 1328)&&(fmi4== 3))//
                    {
                       gzm_219 = 1;
                    }
                    if((spn4== 1329)&&(fmi4== 3))//
                    {
                       gzm_220 = 1;
                    }
                    if((spn4== 1330)&&(fmi4== 3))//
                    {
                       gzm_221 = 1;
                    }
                    if((spn4== 1331)&&(fmi4== 3))//
                    {
                       gzm_222 = 1;
                    }
                    if((spn4== 1322)&&(fmi4== 3))//
                    {
                       gzm_223 = 1;
                    }
                    if((spn4== 976)&&(fmi4== 19))//
                    {
                       gzm_224 = 1;
                    }
                    if((spn4== 976)&&(fmi4== 3))//
                    {
                       gzm_225 = 1;
                    }
                    if((spn4== 976)&&(fmi4== 4))//
                    {
                       gzm_226 = 1;
                    }
                    if((spn4== 98)&&(fmi4== 2))//
                    {
                       gzm_227 = 1;
                    }
                    if((spn4== 98)&&(fmi4== 3))//
                    {
                       gzm_228 = 1;
                    }
                    if((spn4== 98)&&(fmi4== 4))//
                    {
                       gzm_229 = 1;
                    }
                    if((spn4== 100)&&(fmi4== 17))//
                    {
                       gzm_230 = 1;
                    }
                    if((spn4== 100)&&(fmi4== 15))//
                    {
                       gzm_231 = 1;
                    }
                    if((spn4== 100)&&(fmi4== 16))//
                    {
                       gzm_232 = 1;
                    }
                    if((spn4== 100)&&(fmi4== 18))//
                    {
                       gzm_233 = 1;
                    }
                    if((spn4== 175)&&(fmi4== 15))//
                    {
                       gzm_234 = 1;
                    }


                    if((spn4== 175)&&(fmi4== 3))//
                    {
                       gzm_235 = 1;
                    }
                    if((spn4==175 )&&(fmi4== 4))//
                    {
                       gzm_236 = 1;
                    }
                    if((spn4== 110)&&(fmi4== 15))//
                    {
                       gzm_237 = 1;
                    }
                    if((spn4== 1443)&&(fmi4== 7))//
                    {
                       gzm_238 = 1;
                    }
                    if((spn4== 1443)&&(fmi4== 9))//
                    {
                       gzm_239 = 1;
                    }
                    if((spn4== 1443)&&(fmi4== 10))//
                    {
                       gzm_240 = 1;
                    }
                    if((spn4== 523470)&&(fmi4== 21))//
                    {
                       gzm_241 = 1;
                    }
                    if((spn4== 520241)&&(fmi4== 11))//
                    {
                       gzm_242 = 1;
                    }
                    if((spn4== 520241)&&(fmi4== 14))//
                    {
                       gzm_243 = 1;
                    }
                    if((spn4== 520241)&&(fmi4== 0))//
                    {
                       gzm_244 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 15))//
                    {
                       gzm_245 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 17))//
                    {
                       gzm_246 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 3))//
                    {
                       gzm_247 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 3))//
                    {
                       gzm_248 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 4))//
                    {
                       gzm_249 = 1;
                    }
                    if((spn4== 157)&&(fmi4== 4))//
                    {
                       gzm_250 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 16))//
                    {
                       gzm_251 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 7))//
                    {
                       gzm_252 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 5))//
                    {
                       gzm_253 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 0))//
                    {
                       gzm_254 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 1))//
                    {
                       gzm_255 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 20))//
                    {
                       gzm_256 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 21))//
                    {
                       gzm_257 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 18))//
                    {
                       gzm_258 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 23))//
                    {
                       gzm_259 = 1;
                    }
                    if((spn4== 520243)&&(fmi4== 24))//
                    {
                       gzm_260 = 1;
                    }
                    if((spn4== 520277)&&(fmi4== 3))//
                    {
                       gzm_261 = 1;
                    }
                    if((spn4== 520277)&&(fmi4== 4))//
                    {
                       gzm_262 = 1;
                    }
                    if((spn4== 520278)&&(fmi4== 3))//
                    {
                       gzm_263 = 1;
                    }
                    if((spn4== 520278)&&(fmi4== 4))//
                    {
                       gzm_264 = 1;
                    }
                    if((spn4== 3509)&&(fmi4== 3))//
                    {
                       gzm_265 = 1;
                    }
                    if((spn4== 3509)&&(fmi4== 4))//
                    {
                       gzm_266 = 1;
                    }
                    if((spn4== 3510)&&(fmi4== 3))//
                    {
                       gzm_267 = 1;
                    }
                    if((spn4== 3510)&&(fmi4== 4))//
                    {
                       gzm_268 = 1;
                    }
                    if((spn4== 3511)&&(fmi4== 3))//
                    {
                       gzm_269 = 1;
                    }
                    if((spn4== 3511)&&(fmi4== 4))//
                    {
                       gzm_270 = 1;
                    }
                    if((spn4== 107)&&(fmi4== 7))//
                    {
                       gzm_271 = 1;
                    }
                    if((spn4== 520289)&&(fmi4== 11))//
                    {
                       gzm_272 = 1;
                    }
                    if((spn4== 522014)&&(fmi4== 1))//
                    {
                       gzm_273 = 1;
                    }
                    if((spn4== 522014)&&(fmi4== 2))//
                    {
                       gzm_274 = 1;
                    }
                    if((spn4== 99)&&(fmi4== 11))//
                    {
                       gzm_275 = 1;
                    }
                    if((spn4== 99)&&(fmi4== 7))//
                    {
                       gzm_276 = 1;
                    }
                    if((spn4== 1675)&&(fmi4== 3))//
                    {
                       gzm_277 = 1;
                    }
                    if((spn4== 1675)&&(fmi4== 4))//
                    {
                       gzm_278 = 1;
                    }
                    if((spn4== 1675)&&(fmi4== 5))//
                    {
                       gzm_279 = 1;
                    }

                    if((spn4== 520253)&&(fmi4== 11))//
                    {
                       gzm_280 = 1;
                    }

                    if((spn4== 1136)&&(fmi4== 4))//
                    {
                       gzm_281 = 1;
                    }
                    if((spn4== 1136)&&(fmi4== 3))//
                    {
                       gzm_282 = 1;
                    }

                    if((spn4== 4346)&&(fmi4== 5))//
                    {
                       gzm_283 = 1;
                    }
                    if((spn4== 4346)&&(fmi4== 3))//
                    {
                       gzm_284 = 1;
                    }

                    if((spn4== 4346)&&(fmi4== 4))//
                    {
                       gzm_285 = 1;
                    }
                    if((spn4== 4344)&&(fmi4== 5))//
                    {
                       gzm_286 = 1;
                    }

                    if((spn4== 4344)&&(fmi4== 3))//
                    {
                       gzm_287 = 1;
                    }
                    if((spn4== 4344)&&(fmi4== 4))//
                    {
                       gzm_288 = 1;
                    }

                    if((spn4== 523003)&&(fmi4== 5))//
                    {
                       gzm_289 = 1;
                    }
                    if((spn4== 523003)&&(fmi4== 3))//
                    {
                       gzm_290 = 1;
                    }

                    if((spn4== 523003)&&(fmi4== 4))//
                    {
                       gzm_291 = 1;
                    }
                    if((spn4== 4340)&&(fmi4== 5))//
                    {
                       gzm_292 = 1;
                    }

                    if((spn4== 4340)&&(fmi4== 3))//
                    {
                       gzm_293 = 1;
                    }
                    if((spn4== 4340)&&(fmi4== 4))//
                    {
                       gzm_294 = 1;
                    }

                    if((spn4== 3363)&&(fmi4== 5))//
                    {
                       gzm_295 = 1;
                    }
                    if((spn4== 3363)&&(fmi4== 3))//
                    {
                       gzm_296 = 1;
                    }

                    if((spn4== 3363)&&(fmi4== 4))//
                    {
                       gzm_297 = 1;
                    }
                    if((spn4== 84)&&(fmi4== 0))//
                    {
                       gzm_298 = 1;
                    }

                    if((spn4== 84)&&(fmi4== 2))//
                    {
                       gzm_299 = 1;
                    }

                    //300 分界线
                    if((spn4== 1624)&&(fmi4== 3))//
                    {
                       gzm_300 = 1;
                    }

                    if((spn4== 1624)&&(fmi4== 4))//
                    {
                       gzm_301 = 1;
                    }
                    if((spn4== 1624)&&(fmi4== 8))//
                    {
                       gzm_302 = 1;
                    }

                    if((spn4== 520250)&&(fmi4== 5))//
                    {
                       gzm_303 = 1;
                    }
                    if((spn4== 520250)&&(fmi4== 3))//
                    {
                       gzm_304 = 1;
                    }

                    if((spn4== 520250)&&(fmi4== 4))//
                    {
                       gzm_305 = 1;
                    }
                    if((spn4== 520264)&&(fmi4== 3))//
                    {
                       gzm_306 = 1;
                    }

                    if((spn4== 520264)&&(fmi4== 4))//
                    {
                       gzm_307 = 1;
                    }
                    if((spn4== 522000)&&(fmi4== 12))//
                    {
                       gzm_308 = 1;
                    }

                    if((spn4== 520252)&&(fmi4== 2))//
                    {
                       gzm_309 = 1;
                    }

                    if((spn4== 520277)&&(fmi4== 7))//
                    {
                       gzm_310 = 1;
                    }

                    if((spn4== 520218)&&(fmi4== 14))//
                    {
                       gzm_311 = 1;
                    }
                    if((spn4== 520218)&&(fmi4== 19))//
                    {
                       gzm_312 = 1;
                    }

                /****************************************************************************************************/





                 QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                 //设置字号
                 QFont ft;
                 ft.setPointSize(32);
                 ui->label_15->setFont(ft);
                 //设置颜色
                 QPalette pa;
                 pa.setColor(QPalette::WindowText,Qt::red);
                 ui->label_15->setPalette(pa);

                 QPainter paintBuff(this);
                 QPixmap pixBuff;

                 mybufflag_w[0] = gzm_001;//gzm_001
                 mybufflag_w[1] = gzm_002;//gzm_002
                 mybufflag_w[2] = gzm_003;
                 mybufflag_w[3] = gzm_004;
                 mybufflag_w[4] = gzm_005;
                 mybufflag_w[5] = gzm_006;
                 mybufflag_w[6] = gzm_007;
                 mybufflag_w[7] = gzm_008;
                 mybufflag_w[8] = gzm_009;//gzm_009
                 mybufflag_w[9] = gzm_010;//gzm_010

                 mybufflag_w[10] = gzm_011;
                 mybufflag_w[11] = gzm_012;
                 mybufflag_w[12] = gzm_013;
                 mybufflag_w[13] = gzm_014;
                 mybufflag_w[14] = gzm_015;
                 mybufflag_w[15] = gzm_016;
                 mybufflag_w[16] = gzm_017;
                 mybufflag_w[17] = gzm_018;
                 mybufflag_w[18] = gzm_019;
                 mybufflag_w[19] = gzm_020;

                 mybufflag_w[20] = gzm_021;
                 mybufflag_w[21] = gzm_022;
                 mybufflag_w[22] = gzm_023;
                 mybufflag_w[23] = gzm_024;
                 mybufflag_w[24] = gzm_025;
                 mybufflag_w[25] = gzm_026;
                 mybufflag_w[26] = gzm_027;
                 mybufflag_w[27] = gzm_028;
                 mybufflag_w[28] = gzm_029;
                 mybufflag_w[29] = gzm_030;
                 mybufflag_w[30] = gzm_031;



                 mybufflag_w[31] = gzm_032;
                 mybufflag_w[32] = gzm_033;
                 mybufflag_w[33] = gzm_034;
                 mybufflag_w[34] = gzm_035;
                 mybufflag_w[35] = gzm_036;
                 mybufflag_w[36] = gzm_037;
                 mybufflag_w[37] = gzm_038;
                 mybufflag_w[38] = gzm_039;
                 mybufflag_w[39] = gzm_040;
                 mybufflag_w[40] = gzm_041;


                 mybufflag_w[41] = gzm_042;
                 mybufflag_w[42] = gzm_043;
                 mybufflag_w[43] = gzm_044;
                 mybufflag_w[44] = gzm_045;
                 mybufflag_w[45] = gzm_046;
                 mybufflag_w[46] = gzm_047;
                 mybufflag_w[47] = gzm_048;
                 mybufflag_w[48] = gzm_049;
                 mybufflag_w[49] = gzm_050;
                 mybufflag_w[50] = gzm_051;

                 mybufflag_w[51] = gzm_052;
                 mybufflag_w[52] = gzm_053;
                 mybufflag_w[53] = gzm_054;
                 mybufflag_w[54] = gzm_055;
                 mybufflag_w[55] = gzm_056;
                 mybufflag_w[56] = gzm_057;
                 mybufflag_w[57] = gzm_058;
                 mybufflag_w[58] = gzm_059;
                 mybufflag_w[59] = gzm_060;
                 mybufflag_w[60] = gzm_061;

                 mybufflag_w[61] = gzm_062;
                 mybufflag_w[62] = gzm_063;
                 mybufflag_w[63] = gzm_064;
                 mybufflag_w[64] = gzm_065;
                 mybufflag_w[65] = gzm_066;
                 mybufflag_w[66] = gzm_067;
                 mybufflag_w[67] = gzm_068;
                 mybufflag_w[68] = gzm_069;
                 mybufflag_w[69] = gzm_070;
                 mybufflag_w[70] = gzm_071;

                 mybufflag_w[71] = gzm_072;
                 mybufflag_w[72] = gzm_073;
                 mybufflag_w[73] = gzm_074;
                 mybufflag_w[74] = gzm_075;
                 mybufflag_w[75] = gzm_076;
                 mybufflag_w[76] = gzm_077;
                 mybufflag_w[77] = gzm_078;
                 mybufflag_w[78] = gzm_079;
                 mybufflag_w[79] = gzm_080;
                 mybufflag_w[80] = gzm_081;


                 mybufflag_w[81] = gzm_082;
                 mybufflag_w[82] = gzm_083;
                 mybufflag_w[83] = gzm_084;
                 mybufflag_w[84] = gzm_085;
                 mybufflag_w[85] = gzm_086;
                 mybufflag_w[86] = gzm_087;
                 mybufflag_w[87] = gzm_088;
                 mybufflag_w[88] = gzm_089;
                 mybufflag_w[89] = gzm_090;
                 mybufflag_w[90] = gzm_091;

                 mybufflag_w[91] = gzm_092;
                 mybufflag_w[92] = gzm_093;
                 mybufflag_w[93] = gzm_094;
                 mybufflag_w[94] = gzm_095;
                 mybufflag_w[95] = gzm_096;
                 mybufflag_w[96] = gzm_097;
                 mybufflag_w[97] = gzm_098;
                 mybufflag_w[98] = gzm_099;
                 mybufflag_w[99] = gzm_100;
                 mybufflag_w[100] = gzm_101;

                //100 分界线


                 mybufflag_w[101] = gzm_102;
                 mybufflag_w[102] = gzm_103;
                 mybufflag_w[103] = gzm_104;
                 mybufflag_w[104] = gzm_105;
                 mybufflag_w[105] = gzm_106;
                 mybufflag_w[106] = gzm_107;
                 mybufflag_w[107] = gzm_108;
                 mybufflag_w[108] = gzm_109;
                 mybufflag_w[109] = gzm_110;
                 mybufflag_w[110] = gzm_111;

                 mybufflag_w[111] = gzm_112;
                 mybufflag_w[112] = gzm_113;
                 mybufflag_w[113] = gzm_114;
                 mybufflag_w[114] = gzm_115;
                 mybufflag_w[115] = gzm_116;
                 mybufflag_w[116] = gzm_117;
                 mybufflag_w[117] = gzm_118;
                 mybufflag_w[118] = gzm_119;
                 mybufflag_w[119] = gzm_120;
                 mybufflag_w[120] = gzm_121;

                 mybufflag_w[121] = gzm_122;
                 mybufflag_w[122] = gzm_123;
                 mybufflag_w[123] = gzm_124;
                 mybufflag_w[124] = gzm_125;
                 mybufflag_w[125] = gzm_126;
                 mybufflag_w[126] = gzm_127;
                 mybufflag_w[127] = gzm_128;
                 mybufflag_w[128] = gzm_129;
                 mybufflag_w[129] = gzm_130;
                 mybufflag_w[130] = gzm_131;

                 mybufflag_w[131] = gzm_132;
                 mybufflag_w[132] = gzm_133;
                 mybufflag_w[133] = gzm_134;
                 mybufflag_w[134] = gzm_135;
                 mybufflag_w[135] = gzm_136;
                 mybufflag_w[136] = gzm_137;
                 mybufflag_w[137] = gzm_138;
                 mybufflag_w[138] = gzm_139;
                 mybufflag_w[139] = gzm_140;
                 mybufflag_w[140] = gzm_141;


                 mybufflag_w[141] = gzm_142;
                 mybufflag_w[142] = gzm_143;
                 mybufflag_w[143] = gzm_144;
                 mybufflag_w[144] = gzm_145;
                 mybufflag_w[145] = gzm_146;
                 mybufflag_w[146] = gzm_147;
                 mybufflag_w[147] = gzm_148;
                 mybufflag_w[148] = gzm_149;
                 mybufflag_w[149] = gzm_150;
                 mybufflag_w[150] = gzm_151;

                 mybufflag_w[151] = gzm_152;
                 mybufflag_w[152] = gzm_153;
                 mybufflag_w[153] = gzm_154;
                 mybufflag_w[154] = gzm_155;
                 mybufflag_w[155] = gzm_156;
                 mybufflag_w[156] = gzm_157;
                 mybufflag_w[157] = gzm_158;
                 mybufflag_w[158] = gzm_159;
                 mybufflag_w[159] = gzm_160;
                 mybufflag_w[160] = gzm_161;

                 mybufflag_w[161] = gzm_162;
                 mybufflag_w[162] = gzm_163;
                 mybufflag_w[163] = gzm_164;
                 mybufflag_w[164] = gzm_165;
                 mybufflag_w[165] = gzm_166;
                 mybufflag_w[166] = gzm_167;
                 mybufflag_w[167] = gzm_168;
                 mybufflag_w[168] = gzm_169;
                 mybufflag_w[169] = gzm_170;
                 mybufflag_w[170] = gzm_171;

                 mybufflag_w[171] = gzm_172;
                 mybufflag_w[172] = gzm_173;
                 mybufflag_w[173] = gzm_174;
                 mybufflag_w[174] = gzm_175;
                 mybufflag_w[175] = gzm_176;
                 mybufflag_w[176] = gzm_177;
                 mybufflag_w[177] = gzm_178;
                 mybufflag_w[178] = gzm_179;
                 mybufflag_w[179] = gzm_180;
                 mybufflag_w[180] = gzm_181;

                 mybufflag_w[181] = gzm_182;
                 mybufflag_w[182] = gzm_183;
                 mybufflag_w[183] = gzm_184;
                 mybufflag_w[184] = gzm_185;
                 mybufflag_w[185] = gzm_186;
                 mybufflag_w[186] = gzm_187;
                 mybufflag_w[187] = gzm_188;
                 mybufflag_w[188] = gzm_189;
                 mybufflag_w[189] = gzm_190;
                 mybufflag_w[190] = gzm_191;

                 mybufflag_w[191] = gzm_192;
                 mybufflag_w[192] = gzm_193;
                 mybufflag_w[193] = gzm_194;
                 mybufflag_w[194] = gzm_195;
                 mybufflag_w[195] = gzm_196;
                 mybufflag_w[196] = gzm_197;
                 mybufflag_w[197] = gzm_198;
                 mybufflag_w[198] = gzm_199;
                 mybufflag_w[199] = gzm_200;
                 mybufflag_w[200] = gzm_201;

                 //200分界线
                 mybufflag_w[201] = gzm_202;
                 mybufflag_w[202] = gzm_203;
                 mybufflag_w[203] = gzm_204;
                 mybufflag_w[204] = gzm_205;
                 mybufflag_w[205] = gzm_206;
                 mybufflag_w[206] = gzm_207;
                 mybufflag_w[207] = gzm_208;
                 mybufflag_w[208] = gzm_209;
                 mybufflag_w[209] = gzm_210;
                 mybufflag_w[210] = gzm_211;

                 mybufflag_w[211] = gzm_212;
                 mybufflag_w[212] = gzm_213;
                 mybufflag_w[213] = gzm_214;
                 mybufflag_w[214] = gzm_215;
                 mybufflag_w[215] = gzm_216;
                 mybufflag_w[216] = gzm_217;
                 mybufflag_w[217] = gzm_218;
                 mybufflag_w[218] = gzm_219;
                 mybufflag_w[219] = gzm_220;
                 mybufflag_w[220] = gzm_221;

                 mybufflag_w[221] = gzm_222;
                 mybufflag_w[222] = gzm_223;
                 mybufflag_w[223] = gzm_224;
                 mybufflag_w[224] = gzm_225;
                 mybufflag_w[225] = gzm_226;
                 mybufflag_w[226] = gzm_227;
                 mybufflag_w[227] = gzm_228;
                 mybufflag_w[228] = gzm_229;
                 mybufflag_w[229] = gzm_230;
                 mybufflag_w[230] = gzm_231;

                 mybufflag_w[231] = gzm_232;
                 mybufflag_w[232] = gzm_233;
                 mybufflag_w[233] = gzm_234;
                 mybufflag_w[234] = gzm_235;
                 mybufflag_w[235] = gzm_236;
                 mybufflag_w[236] = gzm_237;
                 mybufflag_w[237] = gzm_238;
                 mybufflag_w[238] = gzm_239;
                 mybufflag_w[239] = gzm_240;
                 mybufflag_w[240] = gzm_241;


                 mybufflag_w[241] = gzm_242;
                 mybufflag_w[242] = gzm_243;
                 mybufflag_w[243] = gzm_244;
                 mybufflag_w[244] = gzm_245;
                 mybufflag_w[245] = gzm_246;
                 mybufflag_w[246] = gzm_247;
                 mybufflag_w[247] = gzm_248;
                 mybufflag_w[248] = gzm_249;
                 mybufflag_w[249] = gzm_250;
                 mybufflag_w[250] = gzm_251;

                 mybufflag_w[251] = gzm_252;
                 mybufflag_w[252] = gzm_253;
                 mybufflag_w[253] = gzm_254;
                 mybufflag_w[254] = gzm_255;
                 mybufflag_w[255] = gzm_256;
                 mybufflag_w[256] = gzm_257;
                 mybufflag_w[257] = gzm_258;
                 mybufflag_w[258] = gzm_259;
                 mybufflag_w[259] = gzm_260;
                 mybufflag_w[260] = gzm_261;

                 mybufflag_w[261] = gzm_262;
                 mybufflag_w[262] = gzm_263;
                 mybufflag_w[263] = gzm_264;
                 mybufflag_w[264] = gzm_265;
                 mybufflag_w[265] = gzm_266;
                 mybufflag_w[266] = gzm_267;
                 mybufflag_w[267] = gzm_268;
                 mybufflag_w[268] = gzm_269;
                 mybufflag_w[269] = gzm_270;
                 mybufflag_w[270] = gzm_271;

                 mybufflag_w[271] = gzm_272;
                 mybufflag_w[272] = gzm_273;
                 mybufflag_w[273] = gzm_274;
                 mybufflag_w[274] = gzm_275;
                 mybufflag_w[275] = gzm_276;
                 mybufflag_w[276] = gzm_277;
                 mybufflag_w[277] = gzm_278;
                 mybufflag_w[278] = gzm_279;
                 mybufflag_w[279] = gzm_280;
                 mybufflag_w[280] = gzm_281;

                 mybufflag_w[281] = gzm_282;
                 mybufflag_w[282] = gzm_283;
                 mybufflag_w[283] = gzm_284;
                 mybufflag_w[284] = gzm_285;
                 mybufflag_w[285] = gzm_286;
                 mybufflag_w[286] = gzm_287;
                 mybufflag_w[287] = gzm_288;
                 mybufflag_w[288] = gzm_289;
                 mybufflag_w[289] = gzm_290;
                 mybufflag_w[290] = gzm_291;

                 mybufflag_w[291] = gzm_292;
                 mybufflag_w[292] = gzm_293;
                 mybufflag_w[293] = gzm_294;
                 mybufflag_w[294] = gzm_295;
                 mybufflag_w[295] = gzm_296;
                 mybufflag_w[296] = gzm_297;
                 mybufflag_w[297] = gzm_298;
                 mybufflag_w[298] = gzm_299;
                 mybufflag_w[299] = gzm_300;//gzm_300
                 mybufflag_w[300] = gzm_301;//gzm_301


                 //update();

                 //300分界线

                 mybufflag_w[301] = gzm_302;
                 mybufflag_w[302] = gzm_303;
                 mybufflag_w[303] = gzm_304;
                 mybufflag_w[304] = gzm_305;
                 mybufflag_w[305] = gzm_306;
                 mybufflag_w[306] = gzm_307;
                 mybufflag_w[307] = gzm_308;
                 mybufflag_w[308] = gzm_309;
                 mybufflag_w[309] = gzm_310;
                 mybufflag_w[310] = gzm_311;//gzm_311

                 mybufflag_w[311] = gzm_312;//gzm_312

                /*****************************************************************************************************/



                #if 0

                                          QPainter paintBuff(this);
                                          QPixmap pixBuff;
                                          //临时添加 做测试用
                                          //2016.7.16
                                          mybufflag_w[0] =   1;//flagSW;//水温报警
                                          mybufflag_w[1] = 1;//flagJY;//机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。

                                          mybufflag_w[2] = 1;//flagYeyayouwen;//flagYeyayouwen = 1;//液压油温
                                          mybufflag_w[3] = 1;//flagGL;//空气 过滤阻塞报警

                                          mybufflag_w[4] =  flagyouxiangman; //油箱满 报警
                                          //mybufflag_w[5] =  ;  //液压油温偏高请检查

                                          mybufflag_w[6] =  flagyouliangdi;//及时加油 油量低报警
                                          mybufflag_w[7] =  flagCanfault;  //通信故障

                                          mybufflag_w[8] = flagPark;//手刹 报警
                                          mybufflag_w[9] = flagJinqifault;//进气温度传感器故障

                                          mybufflag_w[10] = flagYalisenserfault;//增压压力传感器故障
                                          mybufflag_w[11] = flagTulunzhoufault; //凸轮轴故障

                                          mybufflag_w[12] =  flagQulunzhoufault;//曲轴故障
                                          mybufflag_w[13] =  flagBattery;//蓄电池故障

                                          mybufflag_w[14] =  flagSwSenserfault;//水温传感器故障

                #endif
                                          //建立索引 对mybufflag_w进行提取。
                                          for (mm_w = 0; mm_w < 312; mm_w++)
                                          {
                                              if(mybufflag_w[mm_w] == 1)
                                              {
                                                  myindex_w[jflag_w] = mm_w+1;
                                                  jflag_w++;

                                              }

                                          }


                                  if(jflag_w == 0)
                                  {
                                      memset(myindex_w,0,624);//15
                                  }

                                  jjjflag_w = jflag_w;
                                  jflag_w = 0;

                              if (j_w >= jjjflag_w)
                              {
                                  j_w = 0;
                                  memset(myindex_w,0,624);//15
                              }

                              /*****************************************************/
                              //usleep 调节休眠时间，用于update()函数优化带来的坑。
                              /*****************************************************/
                              //update();
                              //usleep(300000);
                              //sleep(1);
                              /*****************************************************/


                              countBuff_w++;
                              if (countBuff_w>1)
                                  countBuff_w = 0;

                              switch(countBuff_w)//countBuff
                              {

                                case 0:
                                    //ui->label_6->setText(QObject::tr("666666"));
                                    break;

                                case 1:
                              // printf("===== flagyeyayouwen:: %d,midex[j] = %d\r\n",flagYeyayouwen,myindex[j]);
                               switch(myindex_w[j_w])
                               {

                                   case 1:
                                   //ui->label_15->setText(QObject::tr("空调压缩机开路"));

                                   pixBuff.load("./imagejy/gzm/58.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                                   case 2:

                                  // ui->label_15->setText(QObject::tr("空调压缩机对电源短路"));

                                   pixBuff.load("./imagejy/gzm/002.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 3:
                                     //ui->label_15->setText(QObject::tr("空调压缩机对地短路"));

                                   pixBuff.load("./imagejy/gzm/003.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 4:
                                      //ui->label_15->setText(QObject::tr("油门与刹车信号不可信"));

                                   pixBuff.load("./imagejy/gzm/004.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 5:
                                       //ui->label_15->setText(QObject::tr("空气质量流量传感器电压超上限"));
                                   pixBuff.load("./imagejy/gzm/005.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 6:
                                      // ui->label_15->setText(QObject::tr("空气质量流量传感器电压超下限"));
                                   pixBuff.load("./imagejy/gzm/006.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 7:
                                        ui->label_15->setText(QObject::tr("进气加热常开故障"));

                                        pixBuff.load("./imagejy/gzm/007.png");//14.jpg
                                        paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;


                                   case 8:
                                        ui->label_15->setText(QObject::tr("油门踏板1与油门踏板2的两倍的信号关系不可信"));

                                        pixBuff.load("./imagejy/gzm/008.png");//14.jpg
                                        paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 9:
                                        //ui->label_15->setText(QObject::tr("油门踏板1电压值高出上限门槛值"));
                                   pixBuff.load("./imagejy/gzm/009.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                                   case 10:
                                       //ui->label_15->setText(QObject::tr("油门踏板1电压值低于下限门槛值"));
                                       pixBuff.load("./imagejy/gzm/010.png");//14.jpg
                                       paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 11:
                                          //ui->label_15->setText(QObject::tr("油门踏板2与油门踏板1的1/2的信号关系不可信"));
                                   pixBuff.load("./imagejy/gzm/011.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                                   case 12:
                                      //ui->label_15->setText(QObject::tr("油门踏板2电压值高出上限门槛值"));

                                      pixBuff.load("./imagejy/gzm/012.png");//14.jpg
                                      paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 13:
                                      //ui->label_15->setText(QObject::tr("油门踏板2电压值低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/013.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                                   case 14:
                                          //ui->label_15->setText(QObject::tr("大气压力传感器信号不可信"));

                                   pixBuff.load("./imagejy/gzm/014.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                                   case 15:
                                         //ui->label_15->setText(QObject::tr("大气压力传感器电压高出上限门槛"));

                                   pixBuff.load("./imagejy/gzm/015.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 16:
                                   //ui->label_15->setText(QObject::tr("大气压力传感器电压低于下限门槛"));

                                   pixBuff.load("./imagejy/gzm/016.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 17:

                                   //ui->label_15->setText(QObject::tr("进气加热器开路"));

                                   pixBuff.load("./imagejy/gzm/017.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 18:
                                   //ui->label_15->setText(QObject::tr("进气加热器对电源开路"));

                                   pixBuff.load("./imagejy/gzm/018.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 19:
                                   //ui->label_15->setText(QObject::tr("进气加热器对地开路"));
                                   pixBuff.load("./imagejy/gzm/019.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 20:
                                   //ui->label_15->setText(QObject::tr("电池电压原始值低于下限门槛"));

                                   pixBuff.load("./imagejy/gzm/020.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 21:
                                   //ui->label_15->setText(QObject::tr("电池电压原始值超出上限门槛"));

                                   pixBuff.load("./imagejy/gzm/021.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 22:
                                   //ui->label_15->setText(QObject::tr("进气压力传感器信号不可信"));
                                   pixBuff.load("./imagejy/gzm/022.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 23:
                                   //ui->label_15->setText(QObject::tr("进气压力传感器电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/023.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 24:
                                   //ui->label_15->setText(QObject::tr("进气压力传感器电压低于下限门槛值"));
                                   pixBuff.load("./imagejy/gzm/024.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 25:
                                   //ui->label_15->setText(QObject::tr("巡航控制要求的识别错误，使得故障灯常亮"));

                                   pixBuff.load("./imagejy/gzm/025.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 26:
                                   //ui->label_15->setText(QObject::tr("制动踏板踩下前，巡航控制抑制错误"));
                                   pixBuff.load("./imagejy/gzm/026.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 27:
                                   //ui->label_15->setText(QObject::tr("刹车信号不可信"));

                                   pixBuff.load("./imagejy/gzm/027.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 28:
                                   //ui->label_15->setText(QObject::tr("刹车信号错误"));

                                   pixBuff.load("./imagejy/gzm/028.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 29:
                                   //ui->label_15->setText(QObject::tr("冷却水温在一定时间内上升幅度没有达到最小值"));

                                   pixBuff.load("./imagejy/gzm/029.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 30:
                                   //ui->label_15->setText(QObject::tr("冷却水温在一定时间内没有达到最小值"));

                                   pixBuff.load("./imagejy/gzm/030.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 31:
                                   //ui->label_15->setText(QObject::tr("水温信号不可用"));

                                   pixBuff.load("./imagejy/gzm/031.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 32:
                                   //ui->label_15->setText(QObject::tr("发动机转速信号不可用"));

                                   pixBuff.load("./imagejy/gzm/032.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 33:
                                   //ui->label_15->setText(QObject::tr("离合器状态信号不可用"));

                                   pixBuff.load("./imagejy/gzm/033.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 34:
                                  // ui->label_15->setText(QObject::tr("OBD扭矩限制激活错误"));

                                   pixBuff.load("./imagejy/gzm/034.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 35:
                                   //ui->label_15->setText(QObject::tr("冷启动指示灯开路"));

                                   pixBuff.load("./imagejy/gzm/035.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 36:
                                  // ui->label_15->setText(QObject::tr("冷启动指示灯对电源短路"));
                                   pixBuff.load("./imagejy/gzm/036.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 37:
                                   //ui->label_15->setText(QObject::tr("冷启动指示灯对地短路"));

                                   pixBuff.load("./imagejy/gzm/037.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 38:
                                   //ui->label_15->setText(QObject::tr("冷却水温度与机油温度信号不可信"));
                                   pixBuff.load("./imagejy/gzm/038.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 39:
                                   //ui->label_15->setText(QObject::tr("水温传感器工作正常但水温超出门槛值"));

                                   pixBuff.load("./imagejy/gzm/039.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 40:
                                   //ui->label_15->setText(QObject::tr("冷却水温度传感器电压超出上限门槛"));
                                   pixBuff.load("./imagejy/gzm/040.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 41:
                                   //ui->label_15->setText(QObject::tr("冷却水温度传感器电压低于下限门槛"));
                                   pixBuff.load("./imagejy/gzm/041.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 42:
                                   //ui->label_15->setText(QObject::tr("车下启动/停止按钮卡住"));

                                   pixBuff.load("./imagejy/gzm/042.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 43:
                                   //ui->label_15->setText(QObject::tr("只有凸轮轴信号，进入跛形回家状态"));
                                   pixBuff.load("./imagejy/gzm/043.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 44:
                                   //ui->label_15->setText(QObject::tr("凸轮轴信号缺失"));
                                   pixBuff.load("./imagejy/gzm/041.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 45:
                                   //ui->label_15->setText(QObject::tr("凸轮轴周期错误"));
                                   pixBuff.load("./imagejy/gzm/041.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 46:
                                   //ui->label_15->setText(QObject::tr("凸轮轴同步错误"));
                                   pixBuff.load("./imagejy/gzm/046.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 47:
                                   //ui->label_15->setText(QObject::tr("凸轮轴与曲轴同步错误"));
                                   pixBuff.load("./imagejy/gzm/047.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 48:
                                   //ui->label_15->setText(QObject::tr("曲轴信号缺失"));

                                   pixBuff.load("./imagejy/gzm/048.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 49:
                                   //ui->label_15->setText(QObject::tr("曲轴同步错误"));

                                   pixBuff.load("./imagejy/gzm/049.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 50:
                                   //ui->label_15->setText(QObject::tr("曲轴齿数错误"));

                                   pixBuff.load("./imagejy/gzm/050.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 51:
                                   //ui->label_15->setText(QObject::tr("曲轴齿周期错误"));

                                   pixBuff.load("./imagejy/gzm/051.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 52:
                                   //ui->label_15->setText(QObject::tr("齿数与凸轮轴信号偏差超出门槛值"));

                                   pixBuff.load("./imagejy/gzm/052.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 53:
                                   //ui->label_15->setText(QObject::tr("发动机转速超限"));
                                   pixBuff.load("./imagejy/gzm/053.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 54:
                                   //ui->label_15->setText(QObject::tr("发动机转速信号开路"));
                                   pixBuff.load("./imagejy/gzm/054.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 55:
                                   //ui->label_15->setText(QObject::tr("发动机转速信号对电源短路"));
                                   pixBuff.load("./imagejy/gzm/055.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 56:
                                   //ui->label_15->setText(QObject::tr("发动机转速信号对地短路"));
                                   pixBuff.load("./imagejy/gzm/056.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 57:
                                   //ui->label_15->setText(QObject::tr("排气制动蝶阀开路"));
                                   pixBuff.load("./imagejy/gzm/057.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 58:
                                   //ui->label_15->setText(QObject::tr("排气制动蝶阀对电源短路"));
                                   pixBuff.load("./imagejy/gzm/058.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 59:
                                   //ui->label_15->setText(QObject::tr("排气制动蝶阀对地短路"));
                                   pixBuff.load("./imagejy/gzm/059.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 60:
                                   //ui->label_15->setText(QObject::tr("风扇执行器（PWM波）开路"));

                                   pixBuff.load("./imagejy/gzm/060.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 61:
                                   //ui->label_15->setText(QObject::tr("风扇执行器(PWM波)对电源短路"));
                                   pixBuff.load("./imagejy/gzm/061.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 62:
                                   //ui->label_15->setText(QObject::tr("风扇执行器(PWM波)对地短路"));

                                   pixBuff.load("./imagejy/gzm/062.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 63:
                                   //ui->label_15->setText(QObject::tr("风扇执行器(数字信号)开路"));

                                   pixBuff.load("./imagejy/gzm/063.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 64:
                                   //ui->label_15->setText(QObject::tr("风扇执行器(数字信号)对电源短路"));

                                   pixBuff.load("./imagejy/gzm/064.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 65:
                                   //ui->label_15->setText(QObject::tr("风扇执行器(数字信号)对地短路"));
                                   pixBuff.load("./imagejy/gzm/065.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 66:
                                   //ui->label_15->setText(QObject::tr("冷却风扇速度高出上限门槛值"));
                                   pixBuff.load("./imagejy/gzm/066.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 67:
                                   //ui->label_15->setText(QObject::tr("冷却风扇速度低于下限门槛值"));
                                   pixBuff.load("./imagejy/gzm/067.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 68:
                                   //ui->label_15->setText(QObject::tr("燃油加热继电器(数字信号)开路"));

                                   pixBuff.load("./imagejy/gzm/068.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 69:
                                   //ui->label_15->setText(QObject::tr("燃油加热继电器(数字信号)对电源短路"));

                                   pixBuff.load("./imagejy/gzm/069.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 70:
                                   //ui->label_15->setText(QObject::tr("燃油加热继电器(数字信号)对地短路"));

                                   pixBuff.load("./imagejy/gzm/070.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 71:
                                   //ui->label_15->setText(QObject::tr("燃油加热继执行器(PWM波)对地短路"));

                                   pixBuff.load("./imagejy/gzm/071.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 72:
                                   //ui->label_15->setText(QObject::tr("燃油加热继执行器(PWM波)对电源短路"));

                                   pixBuff.load("./imagejy/gzm/072.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 73:
                                   //ui->label_15->setText(QObject::tr("燃油加热继执行器(PWM波)开路"));
                                   pixBuff.load("./imagejy/gzm/073.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 74:
                                   //ui->label_15->setText(QObject::tr("燃油升压执行器开路"));
                                   pixBuff.load("./imagejy/gzm/074.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 75:
                                   //ui->label_15->setText(QObject::tr("燃油升压执行器对电源短路"));
                                   pixBuff.load("./imagejy/gzm/075.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 76:
                                   //ui->label_15->setText(QObject::tr("燃油升压执行器对地短路"));
                                   pixBuff.load("./imagejy/gzm/076.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 77:
                                   //ui->label_15->setText(QObject::tr("油中有水传感器检测到油中有水"));

                                   pixBuff.load("./imagejy/gzm/077.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 78:
                                   //ui->label_15->setText(QObject::tr("总线接收油门信号超限"));

                                   pixBuff.load("./imagejy/gzm/078.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 79:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧CM1数据量错误"));

                                   pixBuff.load("./imagejy/gzm/079.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 80:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧CM1超时错误"));
                                   pixBuff.load("./imagejy/gzm/080.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 81:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧DashDspl数据量错误"));

                                   pixBuff.load("./imagejy/gzm/081.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 82:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧DashDspl超时错误"));

                                   pixBuff.load("./imagejy/gzm/082.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 83:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧DEC1数据量错误"));

                                   pixBuff.load("./imagejy/gzm/083.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 84:
                                   //ui->label_15->setText(QObject::tr("DEC1报文接收超时"));
                                   pixBuff.load("./imagejy/gzm/084.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 85:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EBC1数据长度错误"));

                                   pixBuff.load("./imagejy/gzm/085.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 86:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EBC1超时错误"));

                                   pixBuff.load("./imagejy/gzm/086.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 87:
                                   //ui->label_15->setText(QObject::tr("数据长度错误"));

                                   pixBuff.load("./imagejy/gzm/087.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 88:
                                   //ui->label_15->setText(QObject::tr("超时错误"));

                                   pixBuff.load("./imagejy/gzm/088.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 89:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EGF1数据量错误"));

                                   pixBuff.load("./imagejy/gzm/089.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 90:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EGF1超时错误"));

                                   pixBuff.load("./imagejy/gzm/090.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 91:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EngTemp2数据量错误"));

                                   pixBuff.load("./imagejy/gzm/091.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 92:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧EngTemp2超时错误"));

                                   pixBuff.load("./imagejy/gzm/092.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 93:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ERC1DR数据量错误"));

                                   pixBuff.load("./imagejy/gzm/093.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 94:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ERC1DR超时错误"));

                                   pixBuff.load("./imagejy/gzm/094.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 95:
                                   //ui->label_15->setText(QObject::tr("ETC1报文数据长度错误"));
                                   pixBuff.load("./imagejy/gzm/095.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 96:
                                   //ui->label_15->setText(QObject::tr("ETC1报文超时错误"));

                                   pixBuff.load("./imagejy/gzm/096.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 97:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ETC2数据量错误"));

                                   pixBuff.load("./imagejy/gzm/097.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 98:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ETC2超时错误"));
                                   pixBuff.load("./imagejy/gzm/098.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 99:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ETC7数据量错误"));

                                   pixBuff.load("./imagejy/gzm/099.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 100:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧ETC7报文接收超时"));
                                   pixBuff.load("./imagejy/gzm/100.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 101:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧HRVD数据量错误"));
                                   pixBuff.load("./imagejy/gzm/101.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 102:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧HRVD超时错误"));

                                   pixBuff.load("./imagejy/gzm/102.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 103:
                                   //ui->label_15->setText(QObject::tr("总线接收远程油门信号超限"));

                                   pixBuff.load("./imagejy/gzm/103.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 104:
                                   //ui->label_15->setText(QObject::tr("RxCCVS报文数据长度错误"));

                                   pixBuff.load("./imagejy/gzm/104.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 105:
                                   //ui->label_15->setText(QObject::tr("RxCCVS报文接收超时"));

                                   pixBuff.load("./imagejy/gzm/105.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 106:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TRF1数据量错误"));
                                   pixBuff.load("./imagejy/gzm/106.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 107:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TRF1超时错误"));
                                   pixBuff.load("./imagejy/gzm/107.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 108:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1AE数据量错误"));
                                   pixBuff.load("./imagejy/gzm/108.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 109:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1AE超时错误"));

                                   pixBuff.load("./imagejy/gzm/109.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 110:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1AR数据量错误"));
                                   pixBuff.load("./imagejy/gzm/110.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 111:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1AR超时错误"));
                                   pixBuff.load("./imagejy/gzm/111.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 112:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TTSC1DE数据量错误"));
                                   pixBuff.load("./imagejy/gzm/112.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 113:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TTSC1DE超时错误"));
                                   pixBuff.load("./imagejy/gzm/113.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 114:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1DR数据量错误"));

                                   pixBuff.load("./imagejy/gzm/114.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 115:
                                   //ui->label_15->setText(QObject::tr("CAN接收帧TSC1DR超时错误"));
                                   pixBuff.load("./imagejy/gzm/115.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 116:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1PE数据量错误"));

                                   pixBuff.load("./imagejy/gzm/116.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 117:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1PE通信错误"));

                                   pixBuff.load("./imagejy/gzm/117.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 118:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1TE数据量错误"));
                                   pixBuff.load("./imagejy/gzm/118.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 119:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1TE超时错误"));

                                   pixBuff.load("./imagejy/gzm/119.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 120:
                                   //ui->label_15->setText(QObject::tr("CAN TOTSC1TR数据量错误"));

                                   pixBuff.load("./imagejy/gzm/120.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 121:
                                   //ui->label_15->setText(QObject::tr("CAN TOTSC1TR超时错误"));

                                   pixBuff.load("./imagejy/gzm/121.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 122:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1VE 数据量错误"));
                                   pixBuff.load("./imagejy/gzm/122.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 123:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1VE超时错误"));

                                   pixBuff.load("./imagejy/gzm/123.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 124:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1VR 数据量错误"));

                                   pixBuff.load("./imagejy/gzm/124.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 125:
                                   //ui->label_15->setText(QObject::tr("CANTOTSC1VR 超时错误"));

                                   pixBuff.load("./imagejy/gzm/125.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 126:
                                   //ui->label_15->setText(QObject::tr("燃油温度传感器电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/126.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 127:
                                   //ui->label_15->setText(QObject::tr("燃油温度传感器电压超出下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/127.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 128:
                                   //ui->label_15->setText(QObject::tr("档位提升间隙时间过长"));

                                   pixBuff.load("./imagejy/gzm/128.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 129:
                                   //ui->label_15->setText(QObject::tr("(油中有水灯)指示灯短路"));
                                   pixBuff.load("./imagejy/gzm/129.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 130:
                                   //ui->label_15->setText(QObject::tr("(油中有水灯)指示灯电源短路"));

                                   pixBuff.load("./imagejy/gzm/130.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 131:
                                   //ui->label_15->setText(QObject::tr("(油中油水灯)指示灯地短路"));
                                   pixBuff.load("./imagejy/gzm/131.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 132:
                                   //ui->label_15->setText(QObject::tr("高压测试错误"));
                                   pixBuff.load("./imagejy/gzm/132.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 133:
                                   //ui->label_15->setText(QObject::tr("EEPROM读错误"));

                                   pixBuff.load("./imagejy/gzm/133.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 134:
                                   //ui->label_15->setText(QObject::tr("EEPROM写错误"));
                                   pixBuff.load("./imagejy/gzm/134.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 135:
                                  // ui->label_15->setText(QObject::tr("进气温度传感器电压超出上限门槛值"));
                                   pixBuff.load("./imagejy/gzm/135.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 136:
                                   //ui->label_15->setText(QObject::tr("进气温度传感器电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/136.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 137:
                                   //ui->label_15->setText(QObject::tr("喷孔磨损程度持续20次大于20%"));

                                   pixBuff.load("./imagejy/gzm/137.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 138:
                                   //ui->label_15->setText(QObject::tr("喷孔磨损程度持续500ms介于5%到20%之间"));
                                   pixBuff.load("./imagejy/gzm/138.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 139:
                                   //ui->label_15->setText(QObject::tr("INJ driver IC初始化版本号错误"));

                                   pixBuff.load("./imagejy/gzm/139.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 140:
                                   //ui->label_15->setText(QObject::tr("INJ driver IC上电初始化错误"));
                                   pixBuff.load("./imagejy/gzm/140.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 141:
                                   //ui->label_15->setText(QObject::tr("喷孔磨损超过20%故障"));
                                   pixBuff.load("./imagejy/gzm/141.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 142:
                                   //ui->label_15->setText(QObject::tr("喷孔磨损在0～20%故障"));
                                   pixBuff.load("./imagejy/gzm/142.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 143:
                                   //ui->label_15->setText(QObject::tr("INJ driver IC再次上电错误"));

                                   pixBuff.load("./imagejy/gzm/143.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 144:
                                   //ui->label_15->setText(QObject::tr("喷油器1高端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/144.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 145:
                                   //ui->label_15->setText(QObject::tr("喷油器1高端与地短路"));
                                   pixBuff.load("./imagejy/gzm/145.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 146:
                                   //ui->label_15->setText(QObject::tr("喷油器1低端与电源短路"));
                                   pixBuff.load("./imagejy/gzm/146.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 147:
                                   //ui->label_15->setText(QObject::tr("喷油器1低端与地短路"));
                                   pixBuff.load("./imagejy/gzm/147.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 148:
                                   //ui->label_15->setText(QObject::tr("喷油器1开路"));

                                   pixBuff.load("./imagejy/gzm/148.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 149:
                                   //ui->label_15->setText(QObject::tr("1缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/149.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);
                                   break;

                               case 150:
                                   //ui->label_15->setText(QObject::tr("同BANK中1缸和其他缸或者与弱电源短路"));

                                   pixBuff.load("./imagejy/gzm/150.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 151:
                                   //ui->label_15->setText(QObject::tr("1缸喷油器对电源短路"));
                                   pixBuff.load("./imagejy/gzm/151.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 152:
                                   //ui->label_15->setText(QObject::tr("1缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/152.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 153:
                                   //ui->label_15->setText(QObject::tr("喷油器1高低端短路"));

                                   pixBuff.load("./imagejy/gzm/153.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 154:
                                   //ui->label_15->setText(QObject::tr("喷油器2高端与电源短路"));
                                   pixBuff.load("./imagejy/gzm/154.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 155:
                                   //ui->label_15->setText(QObject::tr("喷油器2高端与地短路"));

                                   pixBuff.load("./imagejy/gzm/155.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 156:
                                   //ui->label_15->setText(QObject::tr("喷油器2低端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/156.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 157:
                                   //ui->label_15->setText(QObject::tr("喷油器2低端与地短路"));

                                   pixBuff.load("./imagejy/gzm/157.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 158:
                                   //ui->label_15->setText(QObject::tr("喷油器2开路"));
                                   pixBuff.load("./imagejy/gzm/158.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 159:
                                   //ui->label_15->setText(QObject::tr("2缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/159.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 160:
                                   //ui->label_15->setText(QObject::tr("同Bank中2缸和其他缸开路或者与弱电源短路"));

                                   pixBuff.load("./imagejy/gzm/160.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 161:
                                   //ui->label_15->setText(QObject::tr("2缸喷油器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/161.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 162:
                                   //ui->label_15->setText(QObject::tr("2缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/162.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 163:
                                   //ui->label_15->setText(QObject::tr("喷油器2高低端短路"));

                                   pixBuff.load("./imagejy/gzm/163.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 164:
                                   //ui->label_15->setText(QObject::tr("喷油器3高端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/164.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 165:
                                   //ui->label_15->setText(QObject::tr("喷油器3高端与地短路"));

                                   pixBuff.load("./imagejy/gzm/165.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 166:
                                   //ui->label_15->setText(QObject::tr("喷油器3低端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/166.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 167:
                                   //ui->label_15->setText(QObject::tr("喷油器3低端与地短路"));

                                   pixBuff.load("./imagejy/gzm/167.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 168:
                                   //ui->label_15->setText(QObject::tr("喷油器3开路"));

                                   pixBuff.load("./imagejy/gzm/168.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 169:
                                   //ui->label_15->setText(QObject::tr("3缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/169.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 170:
                                   //ui->label_15->setText(QObject::tr("同Bank中3缸和其他缸开路或者与弱电电源短路"));

                                   pixBuff.load("./imagejy/gzm/170.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 171:
                                   //ui->label_15->setText(QObject::tr("3缸喷油器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/171.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 172:
                                   //ui->label_15->setText(QObject::tr("3缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/172.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 173:
                                   //ui->label_15->setText(QObject::tr("喷油器3高低端短路"));

                                   pixBuff.load("./imagejy/gzm/173.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 174:
                                   //ui->label_15->setText(QObject::tr("喷油器4高端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/174.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 175:
                                   //ui->label_15->setText(QObject::tr("喷油器4高端与地短路"));

                                   pixBuff.load("./imagejy/gzm/175.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 176:
                                   //ui->label_15->setText(QObject::tr("喷油器4低端与电源短路"));
                                   pixBuff.load("./imagejy/gzm/176.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 177:
                                   //ui->label_15->setText(QObject::tr("喷油器4低端与地短路"));

                                   pixBuff.load("./imagejy/gzm/177.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 178:
                                   //ui->label_15->setText(QObject::tr("喷油器4开路"));
                                   pixBuff.load("./imagejy/gzm/178.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 179:
                                   //ui->label_15->setText(QObject::tr("4缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/179.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 180:
                                   //ui->label_15->setText(QObject::tr("同Bank中4缸和其他缸开路或者与弱电电源短路"));

                                   pixBuff.load("./imagejy/gzm/180.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 181:
                                   //ui->label_15->setText(QObject::tr("4缸喷油器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/181.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 182:
                                   //ui->label_15->setText(QObject::tr("4缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/182.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 183:
                                   //ui->label_15->setText(QObject::tr("喷油器4高低端短路"));

                                   pixBuff.load("./imagejy/gzm/183.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 184:
                                   //ui->label_15->setText(QObject::tr("喷油器5高端与电源短路"));
                                   pixBuff.load("./imagejy/gzm/184.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 185:
                                   //ui->label_15->setText(QObject::tr("喷油器5高端与地短路"));

                                   pixBuff.load("./imagejy/gzm/185.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 186:
                                   //ui->label_15->setText(QObject::tr("喷油器5低端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/186.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 187:
                                   //ui->label_15->setText(QObject::tr("喷油器5低端与地短路"));

                                   pixBuff.load("./imagejy/gzm/187.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 188:
                                   //ui->label_15->setText(QObject::tr("喷油器5开路"));

                                   pixBuff.load("./imagejy/gzm/188.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 189:
                                   //ui->label_15->setText(QObject::tr("5缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/189.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 190:
                                   //ui->label_15->setText(QObject::tr("同Bank中5缸和其他缸开路或者与弱电电源短路"));

                                   pixBuff.load("./imagejy/gzm/190.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 191:
                                   //ui->label_15->setText(QObject::tr("5缸喷油器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/191.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 192:
                                   //ui->label_15->setText(QObject::tr("5缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/192.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 193:
                                   //ui->label_15->setText(QObject::tr("喷油器5高低端短路"));

                                   pixBuff.load("./imagejy/gzm/193.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 194:
                                   //ui->label_15->setText(QObject::tr("喷油器6高端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/194.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 195:
                                   //ui->label_15->setText(QObject::tr("喷油器6高端与地短路"));

                                   pixBuff.load("./imagejy/gzm/195.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 196:
                                   //ui->label_15->setText(QObject::tr("喷油器6低端与电源短路"));

                                   pixBuff.load("./imagejy/gzm/196.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 197:
                                   //ui->label_15->setText(QObject::tr("喷油器6低端与地短路"));

                                   pixBuff.load("./imagejy/gzm/197.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 198:
                                   //ui->label_15->setText(QObject::tr("喷油器6开路"));

                                   pixBuff.load("./imagejy/gzm/198.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 199:
                                   //ui->label_15->setText(QObject::tr("6缸喷油器错误"));

                                   pixBuff.load("./imagejy/gzm/199.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 200:
                                   //ui->label_15->setText(QObject::tr("同Bank中6缸和其他缸开路或者与弱电电源短路"));

                                   pixBuff.load("./imagejy/gzm/200.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 201:
                                   //ui->label_15->setText(QObject::tr("6缸喷油器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/201.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 202:
                                   //ui->label_15->setText(QObject::tr("6缸喷油器对地短路"));

                                   pixBuff.load("./imagejy/gzm/202.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 203:
                                   //ui->label_15->setText(QObject::tr("喷油器6高低端短路"));


                                   pixBuff.load("./imagejy/gzm/203.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 204:
                                   //ui->label_15->setText(QObject::tr("燃油计量器开路"));

                                   pixBuff.load("./imagejy/gzm/204.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 205:
                                   //ui->label_15->setText(QObject::tr("燃油计量器电源短路"));

                                   pixBuff.load("./imagejy/gzm/205.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 206:
                                   //ui->label_15->setText(QObject::tr("燃油计量器对地短路"));

                                   pixBuff.load("./imagejy/gzm/206.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 207:
                                   //ui->label_15->setText(QObject::tr("巡航信号不可靠(无效开关组合)"));

                                   pixBuff.load("./imagejy/gzm/207.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 208:
                                   //ui->label_15->setText(QObject::tr("OBD灯开路"));


                                   pixBuff.load("./imagejy/gzm/208.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 209:
                                   //ui->label_15->setText(QObject::tr("OBD灯与电源短路"));


                                   pixBuff.load("./imagejy/gzm/209.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 210:
                                   //ui->label_15->setText(QObject::tr("OBD灯与地短路"));

                                   pixBuff.load("./imagejy/gzm/210.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 211:
                                   //ui->label_15->setText(QObject::tr("1缸失火"));

                                   pixBuff.load("./imagejy/gzm/211.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 212:
                                   //ui->label_15->setText(QObject::tr("10缸失火"));

                                   pixBuff.load("./imagejy/gzm/212.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 213:
                                   //ui->label_15->setText(QObject::tr("11缸失火"));

                                   pixBuff.load("./imagejy/gzm/213.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 214:
                                   //ui->label_15->setText(QObject::tr("12缸失火"));

                                   pixBuff.load("./imagejy/gzm/214.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 215:
                                   //ui->label_15->setText(QObject::tr("2缸失火"));

                                   pixBuff.load("./imagejy/gzm/215.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 216:
                                   //ui->label_15->setText(QObject::tr("3缸失火"));

                                   pixBuff.load("./imagejy/gzm/216.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 217:
                                   //ui->label_15->setText(QObject::tr("4缸失火"));

                                   pixBuff.load("./imagejy/gzm/217.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 218:
                                   //ui->label_15->setText(QObject::tr("5缸失火"));

                                   pixBuff.load("./imagejy/gzm/218.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 219:
                                   //ui->label_15->setText(QObject::tr("6缸失火"));

                                   pixBuff.load("./imagejy/gzm/219.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 220:
                                   //ui->label_15->setText(QObject::tr("7缸失火"));

                                   pixBuff.load("./imagejy/gzm/220.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 221:
                                   //ui->label_15->setText(QObject::tr("8缸失火"));
                                   pixBuff.load("./imagejy/gzm/221.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 222:
                                   //ui->label_15->setText(QObject::tr("9缸失火"));

                                   pixBuff.load("./imagejy/gzm/222.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 223:
                                   //ui->label_15->setText(QObject::tr("失火总缸数超限"));

                                   pixBuff.load("./imagejy/gzm/223.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 224:
                                   //ui->label_15->setText(QObject::tr("多态开关信号不可信"));

                                   pixBuff.load("./imagejy/gzm/224.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 225:
                                   //ui->label_15->setText(QObject::tr("多态开关电压超上限"));

                                   pixBuff.load("./imagejy/gzm/225.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               case 226:
                                   //ui->label_15->setText(QObject::tr("多态开关电压超下限"));
                                   pixBuff.load("./imagejy/gzm/226.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 227:
                                   //ui->label_15->setText(QObject::tr("机油液位传感器信号不可靠"));

                                   pixBuff.load("./imagejy/gzm/227.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 228:
                                   //ui->label_15->setText(QObject::tr("机油液位传感器电压电压超出上限"));

                                   pixBuff.load("./imagejy/gzm/228.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 229:
                                   //ui->label_15->setText(QObject::tr("机油液位传感器电压电压超出下限"));

                                   pixBuff.load("./imagejy/gzm/229.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 230:
                                   //ui->label_15->setText(QObject::tr("机油压力过低"));

                                   pixBuff.load("./imagejy/gzm/230.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 231:
                                   //ui->label_15->setText(QObject::tr("机油压力过高或机油温度信号不可靠"));


                                   pixBuff.load("./imagejy/gzm/231.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 232:
                                   //ui->label_15->setText(QObject::tr("机油压力传感器电压电压超出上限"));

                                   pixBuff.load("./imagejy/gzm/232.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 233:
                                   //ui->label_15->setText(QObject::tr("机油压力传感器电压电压超出下限"));

                                   pixBuff.load("./imagejy/gzm/233.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 234:
                                   //ui->label_15->setText(QObject::tr("机油温度传感器信号不可靠"));

                                   pixBuff.load("./imagejy/gzm/234.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 235:
                                   //ui->label_15->setText(QObject::tr("机油温度传感器电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/235.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 236:
                                   //ui->label_15->setText(QObject::tr("机油温度传感器电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/236.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 237:
                                   //ui->label_15->setText(QObject::tr("机油温度与冷却水温度信号不可信"));

                                   pixBuff.load("./imagejy/gzm/237.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 238:
                                   //ui->label_15->setText(QObject::tr("PCV阀开路"));

                                   pixBuff.load("./imagejy/gzm/238.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 239:
                                   //ui->label_15->setText(QObject::tr("PCV阀对电源短路"));

                                   pixBuff.load("./imagejy/gzm/239.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 240:
                                   //ui->label_15->setText(QObject::tr("PCV阀对地短路"));

                                   pixBuff.load("./imagejy/gzm/240.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 241:
                                   //ui->label_15->setText(QObject::tr("压力波动时共轨泻压阀未打开"));


                                   pixBuff.load("./imagejy/gzm/241.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 242:
                                   //ui->label_15->setText(QObject::tr("共轨泻压阀打开次数超出技术要求的最大值"));

                                   pixBuff.load("./imagejy/gzm/242.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 243:
                                   //ui->label_15->setText(QObject::tr("共轨泻压阀打开"));

                                   pixBuff.load("./imagejy/gzm/243.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 244:
                                   //ui->label_15->setText(QObject::tr("限压阀打开时间超过限制"));

                                   pixBuff.load("./imagejy/gzm/244.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 245:
                                   //ui->label_15->setText(QObject::tr("轨压传感器电压超出最大偏差"));

                                   pixBuff.load("./imagejy/gzm/245.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 246:
                                   //ui->label_15->setText(QObject::tr("轨压传感器电压低于最小偏差"));

                                   pixBuff.load("./imagejy/gzm/246.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 247:
                                   //ui->label_15->setText(QObject::tr("轨压传感器电压超出上限门槛值"));


                                   pixBuff.load("./imagejy/gzm/247.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 248:
                                   //ui->label_15->setText(QObject::tr("中断采集方式轨压传感器电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/248.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 249:
                                   //ui->label_15->setText(QObject::tr("轨压传感器电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/249.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 250:
                                   //ui->label_15->setText(QObject::tr("中断采集方式轨压传感器电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/250.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 251:
                                   //ui->label_15->setText(QObject::tr("轨压偏差超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/251.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 252:
                                   //ui->label_15->setText(QObject::tr("燃油计量器中的油量超过门槛值"));

                                   pixBuff.load("./imagejy/gzm/252.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 253:
                                   //ui->label_15->setText(QObject::tr("轨压偏差超出门槛值并且燃油计量器中的油量超过门槛值"));

                                   pixBuff.load("./imagejy/gzm/253.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 254:
                                   //ui->label_15->setText(QObject::tr("轨压偏差超出上限门槛值并且喷油量超限"));

                                   pixBuff.load("./imagejy/gzm/254.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 255:
                                   //ui->label_15->setText(QObject::tr("轨压偏差低于下限门槛值并且喷油量低于门槛值"));

                                   pixBuff.load("./imagejy/gzm/255.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 256:
                                   //ui->label_15->setText(QObject::tr("轨压峰值低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/256.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 257:
                                   //ui->label_15->setText(QObject::tr("轨压峰值超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/257.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 258:
                                   //ui->label_15->setText(QObject::tr("轨压下降过快"));

                                   pixBuff.load("./imagejy/gzm/258.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 259:
                                   //ui->label_15->setText(QObject::tr("超速模式下的油量计量单元设定不可信"));

                                   pixBuff.load("./imagejy/gzm/259.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 260:
                                   //ui->label_15->setText(QObject::tr("低怠速下油量计量单元监控器错误"));

                                   pixBuff.load("./imagejy/gzm/260.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 261:
                                   //ui->label_15->setText(QObject::tr("远程油门踏板1输出电压值超出上限"));

                                   pixBuff.load("./imagejy/gzm/261.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 262:
                                   //ui->label_15->setText(QObject::tr("远程油门踏板1输出电压值低于下限"));

                                   pixBuff.load("./imagejy/gzm/262.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 263:
                                   //ui->label_15->setText(QObject::tr("远程油门踏板2输出电压值超出上限"));

                                   pixBuff.load("./imagejy/gzm/263.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 264:
                                   //ui->label_15->setText(QObject::tr("远程油门踏板2输出电压值低于下限"));

                                   pixBuff.load("./imagejy/gzm/264.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 265:
                                   //ui->label_15->setText(QObject::tr("传感器电源1电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/265.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 266:
                                   //ui->label_15->setText(QObject::tr("传感器电源1电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/266.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 267:
                                   //ui->label_15->setText(QObject::tr("传感器电源2电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/267.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 268:
                                   //ui->label_15->setText(QObject::tr("传感器电源2电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/268.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 269:
                                   //ui->label_15->setText(QObject::tr("传感器电源3电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/269.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 270:
                                   //ui->label_15->setText(QObject::tr("传感器电源3电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/270.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 271:
                                   //ui->label_15->setText(QObject::tr("空滤更换"));

                                   pixBuff.load("./imagejy/gzm/271.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 272:
                                   //ui->label_15->setText(QObject::tr("燃油沥青器更换"));

                                   pixBuff.load("./imagejy/gzm/272.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 273:
                                   //ui->label_15->setText(QObject::tr("锁车且执行锁车模式1"));

                                   pixBuff.load("./imagejy/gzm/273.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 274:
                                   //ui->label_15->setText(QObject::tr("锁车且执行锁车模式2"));

                                   pixBuff.load("./imagejy/gzm/274.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 275:
                                   //ui->label_15->setText(QObject::tr("机油更换"));

                                   pixBuff.load("./imagejy/gzm/275.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 276:
                                   //ui->label_15->setText(QObject::tr("机油滤清器更换"));

                                   pixBuff.load("./imagejy/gzm/276.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 277:
                                   //ui->label_15->setText(QObject::tr("起动电机继电器低端电源短路"));

                                   pixBuff.load("./imagejy/gzm/277.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 278:
                                   //ui->label_15->setText(QObject::tr("起动电机继电器低端对地短路"));

                                   pixBuff.load("./imagejy/gzm/278.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 279:
                                   //ui->label_15->setText(QObject::tr("起动电机继电器开路"));

                                   pixBuff.load("./imagejy/gzm/279.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 280:
                                   //ui->label_15->setText(QObject::tr("T50接通时间超限"));

                                   pixBuff.load("./imagejy/gzm/280.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 281:
                                   //ui->label_15->setText(QObject::tr("ECU 温度传感器电压低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/281.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 282:
                                   //ui->label_15->setText(QObject::tr("ECU 温度传感器电压超出上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/282.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 283:
                                   //ui->label_15->setText(QObject::tr("尿素回流管(泵到箱)加热继电器开路"));

                                   pixBuff.load("./imagejy/gzm/283.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 284:
                                   //ui->label_15->setText(QObject::tr("尿素回流管(泵到箱)加热继电器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/284.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 285:
                                   //ui->label_15->setText(QObject::tr("尿素回流管(泵到箱)加热继电器对地短路"));

                                   pixBuff.load("./imagejy/gzm/285.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 286:
                                   //ui->label_15->setText(QObject::tr("尿素压力管(泵到嘴)加热继电器开路"));

                                   pixBuff.load("./imagejy/gzm/286.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 287:
                                   //ui->label_15->setText(QObject::tr("尿素压力管(泵到嘴)加热继电器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/287.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 288:
                                   //ui->label_15->setText(QObject::tr("尿素压力管(泵到嘴)加热继电器对地短路"));

                                   pixBuff.load("./imagejy/gzm/288.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 289:
                                   //ui->label_15->setText(QObject::tr("尿素加热主继电器开路"));

                                   pixBuff.load("./imagejy/gzm/289.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 290:
                                   //ui->label_15->setText(QObject::tr("尿素加热主继电器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/290.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 291:
                                   //ui->label_15->setText(QObject::tr("尿素加热主继电器对地短路"));

                                   pixBuff.load("./imagejy/gzm/291.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 292:
                                   //ui->label_15->setText(QObject::tr("尿素吸液管(箱到泵)加热继电器开路"));

                                   pixBuff.load("./imagejy/gzm/292.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 293:
                                   //ui->label_15->setText(QObject::tr("尿素吸液管(箱到泵)加热继电器对电源短路"));

                                   pixBuff.load("./imagejy/gzm/293.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 294:
                                   //ui->label_15->setText(QObject::tr("尿素吸液管(箱到泵)加热继电器对地短路"));

                                   pixBuff.load("./imagejy/gzm/294.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 295:
                                   //ui->label_15->setText(QObject::tr("尿素箱水加热电磁阀开路"));

                                   pixBuff.load("./imagejy/gzm/295.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 296:
                                   //ui->label_15->setText(QObject::tr("尿素箱水加热电磁阀对电源短路"));

                                   pixBuff.load("./imagejy/gzm/296.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 297:
                                   //ui->label_15->setText(QObject::tr("尿素箱水加热电磁阀对地短路"));

                                   pixBuff.load("./imagejy/gzm/297.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 298:
                                   //ui->label_15->setText(QObject::tr("车速1高于最大门槛值"));

                                   pixBuff.load("./imagejy/gzm/298.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 299:
                                   //ui->label_15->setText(QObject::tr("车速1月喷油量及发动机转速不可信"));

                                   pixBuff.load("./imagejy/gzm/299.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 300:
                                   //ui->label_15->setText(QObject::tr("车速3信号脉宽超过上限门槛值"));

                                   pixBuff.load("./imagejy/gzm/300.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 301:
                                   //ui->label_15->setText(QObject::tr("车速3信号脉宽低于下限门槛值"));

                                   pixBuff.load("./imagejy/gzm/301.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 302:
                                   //ui->label_15->setText(QObject::tr("车速信号平均周期小于门槛值"));

                                   pixBuff.load("./imagejy/gzm/302.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 303:
                                   //ui->label_15->setText(QObject::tr("报警灯开路"));

                                   pixBuff.load("./imagejy/gzm/303.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 304:
                                   //ui->label_15->setText(QObject::tr("报警灯电源短路"));

                                   pixBuff.load("./imagejy/gzm/304.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 305:
                                   //ui->label_15->setText(QObject::tr("报警灯对地短路"));

                                   pixBuff.load("./imagejy/gzm/305.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 306:
                                   //ui->label_15->setText(QObject::tr("油中有水传感器电压原始值超出上限门槛"));

                                   pixBuff.load("./imagejy/gzm/306.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;


                               case 307:
                                   //ui->label_15->setText(QObject::tr("油中有水传感器电压原始值低于下限门槛"));

                                   pixBuff.load("./imagejy/gzm/307.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 308:
                                   //ui->label_15->setText(QObject::tr("CAN 通讯错误"));

                                   pixBuff.load("./imagejy/gzm/308.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 309:
                                   //ui->label_15->setText(QObject::tr("远程油门2倍关系不可信"));

                                   pixBuff.load("./imagejy/gzm/309.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 310:
                                   //ui->label_15->setText(QObject::tr("远程油门与刹车可信性校验"));

                                   pixBuff.load("./imagejy/gzm/310.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 311:
                                   //ui->label_15->setText(QObject::tr("key报文故障"));

                                   pixBuff.load("./imagejy/gzm/311.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;

                               case 312:
                                   //ui->label_15->setText(QObject::tr("key报文超时"));

                                   pixBuff.load("./imagejy/gzm/312.png");//14.jpg
                                   paintBuff.drawPixmap(198,542,461,51,pixBuff);

                                   break;
                               default:
                                   //ui->label_15->setText(QObject::tr(""));
                                   break;
                               }

                               j_w++;
                               break;

                           default:
                              // ui->label_15->setText(QObject::tr(""));
                               break;
                           }


                        /******************************************************************************************************/





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

void Work::on_pushButton_3_clicked()//喇叭按钮
{
#if 0
    if(beep_flag)
    {
        beep_flag = false;
        qDebug()<<"beep_flag = "<<beep_flag<<endl;
    }
    else
    {
        beep_flag = true;
        qDebug()<<"beep_flag = "<<beep_flag<<endl;
    }
#endif
}
