#ifndef _DEV_LIB_H_
#define _DEV_LIB_H_

extern "C" {


//打开蜂鸣器
//return:1,成功;-1\-2,失败
int beep_on();
//关闭蜂鸣器
//return:1,成功;-1\-2,失败
int beep_off();
//sys系统GPIO文件导出
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2,失败
int Export_Gpio(int gpion);
//GPIO信号输入输出方向设置
//gpion:(GPIO1_4=32*1+4=36)
//dir:0--in;dir:1--out
//return:1,成功;-1\-2\-3,失败
int Set_Gpio_Dir(int gpion,int dir);
//GPIO信号置高
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2\-3,失败
int Set_Gpio_H(int gpion);
//GPIO信号置低
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2\-3,失败
int Set_Gpio_L(int gpion);
//倒车信号关闭
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败
int Cam_Power_on(int channel);
//摄像头电源关闭
//channel:取值{1,2,3,4},代表通道号
//return:1,成功;0,失败
int Cam_Power_off(int channel);
//倒车信号开启
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败
int Acc_Sig_on(int channel);
//倒车信号关闭
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败
int Acc_Sig_off(int channel);

}
#endif
