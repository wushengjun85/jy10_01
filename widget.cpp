#include "widget.h"
#include "ui_widget.h"

#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include"signalcan.h"

#include"canread.h"

#include <QPalette>
#include <QFont>

//添加动态链接库
#include"hwlib/devlib.h"



#include"mylib.h"



/***************************************************************************************************************/
//2016.8.1  变量定义
bool flaglanguage = false; //中英文切换标志变量。

//uchar numtmp = 0; //临时 测试所用。

bool beep_flag = true;
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


unsigned char flagLeft = 0;  //左转
unsigned char countLeft = 0; //左转

unsigned char flagBattery = 0;//电瓶指示灯
unsigned char countBattery = 0;//电瓶指示灯

unsigned char flagWidthlamp = 0; //示宽灯
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

unsigned char   flagYL = 0; //油量
unsigned char    countYL = 0;//油量

unsigned char  flagYeyayouwen = 0;//液压油温
unsigned char  countYeyayouwen = 0; //液压油温

unsigned char    flagECU = 0;//ecu
unsigned char    countECU = 0;//ecu

unsigned char    flagPark = 0;//停车
unsigned char    countPark = 0; //停车

unsigned char   flagFDJGZ = 0; //发动机故障
unsigned char   countFDJGZ = 0; //发动机故障

unsigned char   flagRight = 0; //右转
unsigned char    countRight = 0;//右转


unsigned char  flagyouxiangman = 0; //油量满
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
//新增相关变量

uchar qianbulihezhishi;  //前部离合指示输入, 8

uchar tuolilihezhishi;  //脱粒离合指示输入, 7

uchar xieliangtongbaijin;//卸粮筒摆进限位开关 6

uchar Shoubing;//界面切换输入（手柄控制）4

//
uchar liangman70;//粮满 70, 1

//byte3
uchar xielianglihe_input;//卸粮离合开关输入 2
uchar guoqiaofanzhuan_input;//过桥反转指示输入 1


//byte4

uchar getaisheng_input;//割台升输入; 8
uchar getaijiang_input;//割台降输入; 7

uchar xltbj_input;//卸粮筒摆进输入 6
uchar xltbc_input;//卸粮筒摆出输入 5

uchar bhls_input;//拨禾轮升输入 4
uchar bhlj_input; //拨禾轮降输入; 3
uchar tltjiashu_input;//脱粒滚筒加速输入; 2

uchar tltjianshu_input = 0;//脱粒滚筒减速输入 1


//byte5

uchar getaisheng_out;//割台升输出; 8
uchar getaijiang_out;//割台降输出; 7

uchar xltbj_out;//卸粮筒摆进输出 6
uchar xltbc_out;//卸粮筒摆出输出 5

uchar bhls_out;//拨禾轮升输出 4
uchar bhlj_out; //拨禾轮降输出; 3
uchar tltjiashu_out;//脱粒滚筒加速输出; 2

uchar tltjianshu_out;//脱粒滚筒减速输出 1



uchar xiehefa_out;// 卸荷阀输出
uchar  xielianglihe_out;//卸粮离合输出; 1


//
ushort  qiesuiqizhuansu;//切碎器转速
ushort fengjizhuansu;//切碎器转速
ushort guoqiaozhuansu;//过桥转速；

ushort tuoliguntong;//脱粒滚筒转速
ushort fenliguntong;//分离滚筒转速


ushort jiyouwendu;//机油温度

/********************************************************************************************************************/
//故障码 标志定义
//用于数据库存储

uchar gzm_001;//空调压缩机开路
uchar gzm_002;//空调压缩机对电源短路
uchar gzm_003;//空调压缩机对地短路
uchar gzm_004;//油门与刹车信号不可信
uchar gzm_005;//空气质量流量传感器电压超上限
uchar gzm_006;//空气质量流量传感器电压超下限
uchar gzm_007;//进气加热常开故障
uchar gzm_008;//油门踏板1与油门踏板2的两倍的信号关系不可信
uchar gzm_009;//油门踏板1电压值高出上限门槛值
uchar gzm_010;//油门踏板1电压值低于下限门槛值





uchar gzm_011;//油门踏板2与油门踏板1的1/2的信号关系不可信
uchar gzm_012;//油门踏板2电压值高出上限门槛值
uchar gzm_013;//油门踏板2电压值低于下限门槛值
uchar gzm_014;//大气压力传感器信号不可信
uchar gzm_015;//大气压力传感器电压高出上限门槛
uchar gzm_016;//大气压力传感器电压低于下限门槛
uchar gzm_017;//进气加热器开路
uchar gzm_018;//进气加热器对电源开路
uchar gzm_019;//进气加热器对地开路
uchar gzm_020;//电池电压原始值低于下限门槛

uchar gzm_021;//电池电压原始值超出上限门槛
uchar gzm_022;//进气压力传感器信号不可信
uchar gzm_023;//进气压力传感器电压超出上限门槛值
uchar gzm_024;//进气压力传感器电压低于下限门槛值
uchar gzm_025;//巡航控制要求的识别错误，使得故障灯常亮
uchar gzm_026;//制动踏板踩下前，巡航控制抑制错误
uchar gzm_027;//刹车信号不可信
uchar gzm_028;//刹车信号错误
uchar gzm_029;//冷却水温在一定时间内上升幅度没有达到最小值
uchar gzm_030;//冷却水温在一定时间内没有达到最小值

uchar gzm_031;//水温信号不可用
uchar gzm_032;//发动机转速信号不可用
uchar gzm_033;//离合器状态信号不可用
uchar gzm_034;//OBD扭矩限制激活错误
uchar gzm_035;//冷启动指示灯开路
uchar gzm_036;//冷启动指示灯对电源短路
uchar gzm_037;//冷启动指示灯对地短路
uchar gzm_038;//冷却水温度与机油温度信号不可信
uchar gzm_039;//水温传感器工作正常但水温超出门槛值
uchar gzm_040;//冷却水温度传感器电压超出上限门槛

uchar gzm_041;//冷却水温度传感器电压低于下限门槛
uchar gzm_042;//车下启动/停止按钮卡住
uchar gzm_043;//只有凸轮轴信号，进入跛形回家状态
uchar gzm_044;//凸轮轴信号缺失
uchar gzm_045;//凸轮轴周期错误
uchar gzm_046;//凸轮轴同步错误
uchar gzm_047;//凸轮轴与曲轴同步错误
uchar gzm_048;//曲轴信号缺失
uchar gzm_049;//曲轴同步错误
uchar gzm_050;//曲轴齿数错误

uchar gzm_051;//曲轴齿周期错误
uchar gzm_052;//齿数与凸轮轴信号偏差超出门槛值
uchar gzm_053;//发动机转速超限
uchar gzm_054;//发动机转速信号开路
uchar gzm_055;//发动机转速信号对电源短路
uchar gzm_056;//发动机转速信号对地短路
uchar gzm_057;//排气制动蝶阀开路
uchar gzm_058;//排气制动蝶阀对电源短路
uchar gzm_059;//排气制动蝶阀对地短路
uchar gzm_060;//风扇执行器（PWM波）开路

uchar gzm_061;//风扇执行器(PWM波)对电源短路
uchar gzm_062;//风扇执行器(PWM波)对地短路
uchar gzm_063;//风扇执行器(数字信号)开路
uchar gzm_064;//风扇执行器(数字信号)对电源短路
uchar gzm_065;//风扇执行器(数字信号)对地短路
uchar gzm_066;//冷却风扇速度高出上限门槛值
uchar gzm_067;//冷却风扇速度低于下限门槛值
uchar gzm_068;//燃油加热继电器(数字信号)开路
uchar gzm_069;//燃油加热继电器(数字信号)对电源短路
uchar gzm_070;//燃油加热继电器(数字信号)对地短路

uchar gzm_071;//燃油加热继执行器(PWM波)对地短路
uchar gzm_072;//燃油加热继执行器(PWM波)对电源短路
uchar gzm_073;//燃油加热继执行器(PWM波)开路
uchar gzm_074;//燃油升压执行器开路
uchar gzm_075;//燃油升压执行器对电源短路
uchar gzm_076;//燃油升压执行器对地短路
uchar gzm_077;//油中有水传感器检测到油中有水
uchar gzm_078;//总线接收油门信号超限
uchar gzm_079;//CAN接收帧CM1数据量错误
uchar gzm_080;//CAN接收帧CM1超时错误

uchar gzm_081;//CAN接收帧DashDspl数据量错误
uchar gzm_082;//CAN接收帧DashDspl超时错误
uchar gzm_083;//CAN接收帧DEC1数据量错误
uchar gzm_084;//DEC1报文接收超时
uchar gzm_085;//CAN接收帧EBC1数据长度错误
uchar gzm_086;//CAN接收帧EBC1超时错误
uchar gzm_087;//数据长度错误
uchar gzm_088;//超时错误
uchar gzm_089;//CAN接收帧EGF1数据量错误
uchar gzm_090;//CAN接收帧EGF1超时错误

uchar gzm_091;//CAN接收帧EngTemp2数据量错误
uchar gzm_092;//CAN接收帧EngTemp2超时错误
uchar gzm_093;//CAN接收帧ERC1DR数据量错误
uchar gzm_094;//CAN接收帧ERC1DR超时错误
uchar gzm_095;//ETC1报文数据长度错误
uchar gzm_096;//ETC1报文超时错误
uchar gzm_097;//CAN接收帧ETC2数据量错误
uchar gzm_098;//CAN接收帧ETC2超时错误
uchar gzm_099;//CAN接收帧ETC7数据量错误
uchar gzm_100;//CAN接收帧ETC7报文接收超时

uchar gzm_101;//CAN接收帧HRVD数据量错误
uchar gzm_102;//CAN接收帧HRVD超时错误
uchar gzm_103;//总线接收远程油门信号超限
uchar gzm_104;//RxCCVS报文数据长度错误
uchar gzm_105;//RxCCVS报文接收超时
uchar gzm_106;//CAN接收帧TRF1数据量错误
uchar gzm_107;//CAN接收帧TRF1超时错误
uchar gzm_108;//CAN接收帧TSC1AE数据量错误
uchar gzm_109;//CAN接收帧TSC1AE超时错误
uchar gzm_110;//CAN接收帧TSC1AR数据量错误

uchar gzm_111;//CAN接收帧TSC1AR超时错误
uchar gzm_112;//CAN接收帧TTSC1DE数据量错误
uchar gzm_113;//CAN接收帧TTSC1DE超时错误
uchar gzm_114;//CAN接收帧TSC1DR数据量错误
uchar gzm_115;//CAN接收帧TSC1DR超时错误
uchar gzm_116;//CANTOTSC1PE数据量错误
uchar gzm_117;//CANTOTSC1PE通信错误
uchar gzm_118;//CANTOTSC1TE数据量错误
uchar gzm_119;//CANTOTSC1TE超时错误
uchar gzm_120;//CAN TOTSC1TR数据量错误

uchar gzm_121;//CAN TOTSC1TR超时错误
uchar gzm_122;//CANTOTSC1VE 数据量错误
uchar gzm_123;//CANTOTSC1VE超时错误
uchar gzm_124;//CANTOTSC1VR 数据量错误
uchar gzm_125;//CANTOTSC1VR 超时错误
uchar gzm_126;//燃油温度传感器电压超出上限门槛值
uchar gzm_127;//燃油温度传感器电压超出下限门槛值
uchar gzm_128;//档位提升间隙时间过长
uchar gzm_129;//(油中有水灯)指示灯短路
uchar gzm_130;//(油中有水灯)指示灯电源短路


uchar gzm_131;//(油中油水灯)指示灯地短路
uchar gzm_132;//高压测试错误
uchar gzm_133;//EEPROM读错误
uchar gzm_134;//EEPROM写错误
uchar gzm_135;//进气温度传感器电压超出上限门槛值
uchar gzm_136;//进气温度传感器电压低于下限门槛值
uchar gzm_137;//喷孔磨损程度持续20次大于20%
uchar gzm_138;//喷孔磨损程度持续500ms介于5%到20%之间
uchar gzm_139;//INJ driver IC初始化版本号错误
uchar gzm_140;//INJ driver IC上电初始化错误

uchar gzm_141;//喷孔磨损超过20%故障
uchar gzm_142;//喷孔磨损在0～20%故障
uchar gzm_143;//INJ driver IC再次上电错误
uchar gzm_144;//喷油器1高端与电源短路
uchar gzm_145;//喷油器1高端与地短路
uchar gzm_146;//喷油器1低端与电源短路
uchar gzm_147;//喷油器1低端与地短路
uchar gzm_148;//喷油器1开路
uchar gzm_149;//1缸喷油器错误
uchar gzm_150;//同BANK中1缸和其他缸或者与弱电源短路

uchar gzm_151;//1缸喷油器对电源短路
uchar gzm_152;//1缸喷油器对地短路
uchar gzm_153;//喷油器1高低端短路
uchar gzm_154;//喷油器2高端与电源短路
uchar gzm_155;//喷油器2高端与地短路
uchar gzm_156;//喷油器2低端与电源短路
uchar gzm_157;//喷油器2低端与地短路
uchar gzm_158;//喷油器2开路
uchar gzm_159;//2缸喷油器错误
uchar gzm_160;//同Bank中2缸和其他缸开路或者与弱电源短路

uchar gzm_161;//2缸喷油器对电源短路
uchar gzm_162;//2缸喷油器对地短路
uchar gzm_163;//喷油器2高低端短路
uchar gzm_164;//喷油器3高端与电源短路
uchar gzm_165;//喷油器3高端与地短路
uchar gzm_166;//喷油器3低端与电源短路
uchar gzm_167;//喷油器3低端与地短路
uchar gzm_168;//喷油器3开路
uchar gzm_169;//3缸喷油器错误
uchar gzm_170;//同Bank中3缸和其他缸开路或者与弱电电源短路

uchar gzm_171;//3缸喷油器对电源短路
uchar gzm_172;//3缸喷油器对地短路
uchar gzm_173;//喷油器3高低端短路
uchar gzm_174;//喷油器4高端与电源短路
uchar gzm_175;//喷油器4高端与地短路
uchar gzm_176;//喷油器4低端与电源短路
uchar gzm_177;//喷油器4低端与地短路
uchar gzm_178;//喷油器4开路
uchar gzm_179;//4缸喷油器错误
uchar gzm_180;//同Bank中4缸和其他缸开路或者与弱电电源短路

uchar gzm_181;//4缸喷油器对电源短路
uchar gzm_182;//4缸喷油器对地短路
uchar gzm_183;//喷油器4高低端短路
uchar gzm_184;//喷油器5高端与电源短路
uchar gzm_185;//喷油器5高端与地短路
uchar gzm_186;//喷油器5低端与电源短路
uchar gzm_187;//喷油器5低端与地短路
uchar gzm_188;//喷油器5开路
uchar gzm_189;//5缸喷油器错误
uchar gzm_190;//同Bank中5缸和其他缸开路或者与弱电电源短路



uchar gzm_191;//5缸喷油器对电源短路
uchar gzm_192;//5缸喷油器对地短路
uchar gzm_193;//喷油器5高低端短路
uchar gzm_194;//喷油器6高端与电源短路
uchar gzm_195;//喷油器6高端与地短路
uchar gzm_196;//喷油器6低端与电源短路
uchar gzm_197;//喷油器6低端与地短路
uchar gzm_198;//喷油器6开路
uchar gzm_199;//6缸喷油器错误
uchar gzm_200;//同Bank中6缸和其他缸开路或者与弱电电源短路

//

uchar gzm_201;//6缸喷油器对电源短路
uchar gzm_202;//6缸喷油器对地短路
uchar gzm_203;//喷油器6高低端短路
uchar gzm_204;//燃油计量器开路
uchar gzm_205;//燃油计量器电源短路
uchar gzm_206;//燃油计量器对地短路
uchar gzm_207;//巡航信号不可靠(无效开关组合)
uchar gzm_208;//OBD灯开路
uchar gzm_209;//OBD灯与电源短路
uchar gzm_210;//OBD灯与地短路


uchar gzm_211;//1缸失火
uchar gzm_212;//10缸失火
uchar gzm_213;//11缸失火
uchar gzm_214;//12缸失火
uchar gzm_215;//2缸失火
uchar gzm_216;//3缸失火
uchar gzm_217;//4缸失火
uchar gzm_218;//5缸失火
uchar gzm_219;//6缸失火
uchar gzm_220;//7缸失火

uchar gzm_221;//8缸失火
uchar gzm_222;//9缸失火
uchar gzm_223;//失火总缸数超限
uchar gzm_224;//多态开关信号不可信
uchar gzm_225;//多态开关电压超上限
uchar gzm_226;//多态开关电压超下限
uchar gzm_227;//机油液位传感器信号不可靠
uchar gzm_228;//机油液位传感器电压电压超出上限
uchar gzm_229;//机油液位传感器电压电压超出下限
uchar gzm_230;//机油压力过低

uchar gzm_231;//机油压力过高或机油温度信号不可靠
uchar gzm_232;//机油压力传感器电压电压超出上限
uchar gzm_233;//机油压力传感器电压电压超出下限
uchar gzm_234;//机油温度传感器信号不可靠
uchar gzm_235;//机油温度传感器电压超出上限门槛值
uchar gzm_236;//机油温度传感器电压低于下限门槛值
uchar gzm_237;//机油温度与冷却水温度信号不可信
uchar gzm_238;//PCV阀开路
uchar gzm_239;//PCV阀对电源短路
uchar gzm_240;//PCV阀对地短路


//248 ，249 要注意一下
uchar gzm_241;//压力波动时共轨泻压阀未打开
uchar gzm_242;//共轨泻压阀打开次数超出技术要求的最大值
uchar gzm_243;//共轨泻压阀打开
uchar gzm_244;//限压阀打开时间超过限制
uchar gzm_245;//轨压传感器电压超出最大偏差
uchar gzm_246;//轨压传感器电压低于最小偏差
uchar gzm_247;//轨压传感器电压超出上限门槛值
uchar gzm_248;//中断采集方式轨压传感器电压超出上限门槛值
uchar gzm_249;//轨压传感器电压低于下限门槛值
uchar gzm_250;//中断采集方式轨压传感器电压低于下限门槛值

uchar gzm_251;//轨压偏差超出上限门槛值
uchar gzm_252;//燃油计量器中的油量超过门槛值
uchar gzm_253;//轨压偏差超出门槛值并且燃油计量器中的油量超过门槛值
uchar gzm_254;//轨压偏差超出上限门槛值并且喷油量超限
uchar gzm_255;//轨压偏差低于下限门槛值并且喷油量低于门槛值
uchar gzm_256;//轨压峰值低于下限门槛值
uchar gzm_257;//轨压峰值超出上限门槛值
uchar gzm_258;//轨压下降过快
uchar gzm_259;//超速模式下的油量计量单元设定不可信
uchar gzm_260;//低怠速下油量计量单元监控器错误

uchar gzm_261;//远程油门踏板1输出电压值超出上限
uchar gzm_262;//远程油门踏板1输出电压值低于下限
uchar gzm_263;//远程油门踏板2输出电压值超出上限
uchar gzm_264;//远程油门踏板2输出电压值低于下限
uchar gzm_265;//传感器电源1电压超出上限门槛值
uchar gzm_266;//传感器电源1电压低于下限门槛值
uchar gzm_267;//传感器电源2电压超出上限门槛值
uchar gzm_268;//传感器电源2电压低于下限门槛值
uchar gzm_269;//传感器电源3电压超出上限门槛值
uchar gzm_270;//传感器电源3电压低于下限门槛值

uchar gzm_271;//空滤更换
uchar gzm_272;//燃油沥青器更换
uchar gzm_273;//锁车且执行锁车模式1
uchar gzm_274;//锁车且执行锁车模式2
uchar gzm_275;//机油更换
uchar gzm_276;//机油滤清器更换
uchar gzm_277;//起动电机继电器低端电源短路
uchar gzm_278;//起动电机继电器低端对地短路
uchar gzm_279;//起动电机继电器开路
uchar gzm_280;//T50接通时间超限

uchar gzm_281;//ECU 温度传感器电压低于下限门槛值
uchar gzm_282;//ECU 温度传感器电压超出上限门槛值
uchar gzm_283;//尿素回流管(泵到箱)加热继电器开路
uchar gzm_284;//尿素回流管(泵到箱)加热继电器对电源短路
uchar gzm_285;//尿素回流管(泵到箱)加热继电器对地短路
uchar gzm_286;//尿素压力管(泵到嘴)加热继电器开路
uchar gzm_287;//尿素压力管(泵到嘴)加热继电器对电源短路
uchar gzm_288;//尿素压力管(泵到嘴)加热继电器对地短路
uchar gzm_289;//尿素加热主继电器开路
uchar gzm_290;//尿素加热主继电器对电源短路

uchar gzm_291;//尿素加热主继电器对地短路
uchar gzm_292;//尿素吸液管(箱到泵)加热继电器开路
uchar gzm_293;//尿素吸液管(箱到泵)加热继电器对电源短路
uchar gzm_294;//尿素吸液管(箱到泵)加热继电器对地短路
uchar gzm_295;//尿素箱水加热电磁阀开路
uchar gzm_296;//尿素箱水加热电磁阀对电源短路
uchar gzm_297;//尿素箱水加热电磁阀对地短路
uchar gzm_298;//车速1高于最大门槛值
uchar gzm_299;//车速1月喷油量及发动机转速不可信
uchar gzm_300;//车速3信号脉宽超过上限门槛值

uchar gzm_301;//车速3信号脉宽低于下限门槛值
uchar gzm_302;//车速信号平均周期小于门槛值
uchar gzm_303;//报警灯开路
uchar gzm_304;//报警灯电源短路
uchar gzm_305;//报警灯对地短路
uchar gzm_306;//油中有水传感器电压原始值超出上限门槛
uchar gzm_307;//油中有水传感器电压原始值低于下限门槛
uchar gzm_308;//CAN 通讯错误
uchar gzm_309;//远程油门2倍关系不可信
uchar gzm_310;//远程油门与刹车可信性校验

uchar gzm_311;//key报文故障
uchar gzm_312;//key报文超时
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
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

    //倒车摄像头信号与槽
    //connect(this,SIGNAL(sendcamersignal()),this,SLOT(cameraslot()));


    //线程初始化与启动
    mycan = new SignalCan();
    mycan->start();

    //测试库调用
    //beep_on();

    //P();

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
   // painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.rotate(-133);
//    painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
//    painter.rotate(numtmp++);  //设置旋转(6° * 秒)
    painter.rotate(4.0 *shisu);

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

    //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))

    painter.rotate(4.0*shisu);  //设旋转(角度 = 6° * )
    painter.rotate(-133);
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

    //2016.6.25  定义数值
    #if 1
        ui->label->setText(QString::number(jiyouwendu));//机油温度
        ui->label_2->setText(QString::number(Yeyayouwen));//液压油油温（液压油油温）
        ui->label_3->setText(QString::number(SuiWen));//水温；
        ui->label_4->setText(QString::number(jiyouyali)); //机油压力
        ui->label_5->setText(QString::number(XiaoshiJi));//小时计

    #endif


     /************************************************************************************************/
    //返回主界面。
        if((DC==1)&&(wsjtmpflag == 0))
        {

            //DC = 0;
            //emit sendcamersignal();
             ok = true;

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
            //if (flagyouxiangman|flagyouliangdi)//油量
            if (1)
            {
                switch(flagyouxiangman)
                {

                case 0:
                    pixShanshuo.load("./imagejy/yl00.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;

                case 1:
                    pixShanshuo.load("./imagejy/yl01.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;

                case 2:
                    pixShanshuo.load("./imagejy/yl02.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;

                case 3:
                    pixShanshuo.load("./imagejy/yl03.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                case 4:
                    pixShanshuo.load("./imagejy/yl04.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                case 5:
                    pixShanshuo.load("./imagejy/yl05.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                case 6:
                    pixShanshuo.load("./imagejy/yl06.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                case 7:
                    pixShanshuo.load("./imagejy/yl07.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                case 8:
                    pixShanshuo.load("./imagejy/yl08.png");//14.jpg
                    paintShanshuo.drawPixmap(446,182,166,26,pixShanshuo);
                    break;
                }

            }//end off //油量格数

#if 0
            if(beep_flag)
            {
                //添加蜂鸣器报警
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



            /****************************************************************************************************/
                  //故障码解析  后期要单独解析 暂时先放到这。

                  if((spn==522000)&&(fmi==12)) //Can 通信故障
                  {
                      flagCanfault = 1;

                  }
                  if(((spn==105)&&(fmi ==3))|((spn==105)&&(fmi ==4))) //进气温度传感器故障
                  {
                      flagJinqifault = 1;
                  }
                  if(spn == 102)//增压压力传感器故障
                  {
                      flagYalisenserfault = 1;
                  }

                  if(spn == 110)//水温传感器故障
                  {
                      flagSwSenserfault = 1;
                  }

                  if(spn == 4201)//凸轮轴故障
                  {
                       flagTulunzhoufault = 1;
                  }

                  if(spn == 4203)//曲轴故障
                  {
                       flagQulunzhoufault = 1;
                  }



                  /*****************************************************************************************************/
                  //正下方长方形图标显示
                  //2016.7.16

                  QPainter paintBuff(this);
                  QPixmap pixBuff;

                  /**********************************************************************************************************/

                          //临时添加 做测试用
                          //2016.7.16
                          mybufflag[0] =   1;//flagSW;//水温报警
                          mybufflag[1] = 1;//flagJY;//机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。

                          mybufflag[2] = 1;//flagYeyayouwen;//flagYeyayouwen = 1;//液压油温
                          mybufflag[3] = 1;//flagGL;//空气 过滤阻塞报警

                          mybufflag[4] =  flagyouxiangman; //油箱满 报警
                          //mybufflag[5] =  ;  //液压油温偏高请检查

                          mybufflag[6] =  flagyouliangdi;//及时加油 油量低报警
                          mybufflag[7] =  flagCanfault;  //通信故障

                          mybufflag[8] = flagPark;//手刹 报警
                          mybufflag[9] = flagJinqifault;//进气温度传感器故障

                          mybufflag[10] = flagYalisenserfault;//增压压力传感器故障
                          mybufflag[11] = flagTulunzhoufault; //凸轮轴故障

                          mybufflag[12] =  flagQulunzhoufault;//曲轴故障
                          mybufflag[13] =  flagBattery;//蓄电池故障

                          mybufflag[14] =  flagSwSenserfault;//水温传感器故障


                          //建立索引 对mybufflag进行提取。
                          for (mm = 0; mm < 15; mm++)
                          {
                              if(mybufflag[mm])
                              {
                                  myindex[jflag] = mm;
                                  jflag++;

                              }

                          }
                  /**********************************************************************************************************/

                  if(jflag == 0)
                  {
                      memset(myindex,0,15);
                  }


                  jjjflag = jflag;
                  jflag = 0;

              if (j >= jjjflag)
              {
                  j = 0;
                  memset(myindex,0,15);
              }
              countBuff++;
              if (countBuff>1)
                  countBuff = 0;
              switch(countBuff)
              {
                case 1:
                 // printf("===== flagyeyayouwen:: %d,midex[j] = %d\r\n",flagYeyayouwen,myindex[j]);
                  switch(myindex[j])
                  {
                      //qDebug()<<"flagyeyayouwen::"<<flagYeyayouwen<<"  myindex[j]:"<<myindex[j]<<endl;
                      case 0:
                           if (flagSW)
                           {
                               pixBuff.load("./img2/41.png");//41.jpg
                               paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                            }
                           break;

                      case 1:
//                           pixBuff.load("./img2/42.png");//42.jpg
//                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁


                  {
                      ui->label_6->setText("yuv");
                      //设置字号

                      QFont ft;
                      ft.setPointSize(32);
                      ui->label_6->setFont(ft);

//                      //设置颜色
                      QPalette pa;
                      pa.setColor(QPalette::WindowText,Qt::red);
                      ui->label_6->setPalette(pa);
                   }
                      break;

                      case 2:
//                          pixBuff.load("./img2/43.png");//43.jpg
//                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      ui->label_6->setText("wsj");

                      break;

                      case 3:
                          pixBuff.load("./img2/44.png");//44.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 4:
                           pixBuff.load("./img2/45.png");//45.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 5:
                           pixBuff.load("./img2/46.png");//46.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 6:
                          pixBuff.load("./img2/47.png");//47.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 7:
                          pixBuff.load("./img2/48.png");//48.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;


                      case 8:
                           pixBuff.load("./img2/49.png");//49.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 9:
                           pixBuff.load("./img2/50.png");//50.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 10:
                          pixBuff.load("./img2/51.png");//51.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 11:
                          pixBuff.load("./img2/52.png");//52.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;


                      case 12:
                           pixBuff.load("./img2/53.png");//53.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 13:
                           pixBuff.load("./img2/54.png");//54.jpg
                           paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                      case 14:
                          pixBuff.load("./img2/55.png");//55.jpg
                          paintBuff.drawPixmap(280,535,255,50,pixBuff); //正下方图标闪烁
                      break;

                  }
                  j++;
                  break;
              }
           /******************************************************************************************************/





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
//    QString time_display =  QTime::currentTime().toString();     //绘制当前的时间
//    ui->lcdNumber->display(time_display);

    QString timeStr= QTime::currentTime().toString();     //绘制当前的时间
    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");

    ui->lcdNumber_2->display(dateStr);
    ui->lcdNumber->display(timeStr);
}

void Widget::on_pushButton_timesetup_2_clicked()  //查询按钮
{
    this->close();
    findlook->show();
    findlook->exec();
    this->show();
}

void Widget::on_pushButton_timesetup_3_clicked()//喇叭按钮
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
