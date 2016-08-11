#include "devlib.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BEEP_PATH	"/sys/class/leds/beeper-pwm"
#define TRIGGER		"trigger"
#define VALUE		"brightness"
#define TRIGGER_TIMER	"timer"
#define TRIGGER_none	"none"
#define BEEP_DEFAULT	"80"
#define BEEP_OFF		"0"

#define EXPORT_PATH		"/sys/class/gpio/export"
#define DIRECTION_PATH	"/sys/class/gpio"

#define DIRECTION		"direction"
#define DIR_IN			"in"
#define DIR_OUT			"out"
#define DIR_VAL			"value"

int cam_channel[4]={46,163,162,164};
int acc_channel[3]={162,164,163};

//打开蜂鸣器
//return:1,成功;-1\-2,失败
int beep_on()
{
	char path[50]={0};
	int fd=0,ret=0;
	
	strcpy(path,BEEP_PATH);
	strcat(path,"/"TRIGGER);
	//打开触发器文件
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep trigger error!\n");
		return -1;
	}
	//设置触发器文件为定时器类型
	ret=write(fd,TRIGGER_TIMER,strlen(TRIGGER_TIMER));
	if(ret<0)
	{
		printf("write beep trigger_timer error!\n");
		return -2;
	}
	close(fd);

	strcpy(path,BEEP_PATH);
	strcat(path,"/"VALUE);
	//打开brightness文件
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep value error!\n");
		return -3;
	}
	//写定时器值，蜂鸣器响
	ret=write(fd,BEEP_DEFAULT,strlen(BEEP_DEFAULT));
	if(ret<0)
	{
		printf("write beep value error!\n");
		return -4;
	}
	close(fd);
	
	return 1;
}

//关闭蜂鸣器
//return:1,成功;-1\-2,失败
int beep_off()
{
	char path[50]={0};
	int fd=0,ret=0;
	
	strcpy(path,BEEP_PATH);
	strcat(path,"/"VALUE);
	//打开brightness文件
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep value error!\n");
		return -1;
	}
	//写定时器值，关闭蜂鸣器
	ret=write(fd,BEEP_OFF,strlen(BEEP_OFF));
	if(ret<0)
	{
		printf("write beep value error!\n");
		return -2;
	}
	close(fd);
	
	return 1;
}
//sys系统GPIO文件导出
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2,失败

int Export_Gpio(int gpion)
{
	int fd_exp=0,ret=0;
	char val[5]={0};
	sprintf(val,"%d",gpion);
	//打开EXPORT文件
	fd_exp=open(EXPORT_PATH,O_RDWR);
	if(fd_exp<0)
	{
		printf("open export%d error!\n",gpion);
		return -1;
	}
	//写值，导出GPIO
	ret=write(fd_exp,val,strlen(val));
	if(ret<0)
	{
		printf("write export%d error!\n",gpion);
		return -2;
	}
	close(fd_exp);
	
	return 1;
}
//GPIO信号输入输出方向设置
//gpion:(GPIO1_4=32*1+4=36)
//dir:0--in;dir:1--out
//return:1,成功;-1\-2\-3,失败
int Set_Gpio_Dir(int gpion,int dir)
{
	
	if(Export_Gpio(gpion))
	{
		int fd_exp=0,ret=0;
		char path[50]={0};
		
		sprintf(path,"%s/gpio%d/direction",DIRECTION_PATH,gpion);
		//打开GPIO_EXPORT文件
		fd_exp=open(path,O_RDWR);
		if(fd_exp<0)
		{
			printf("open GPIO%d_IN error!\n",gpion);
			return -1;
		}
		//写值，导出GPIO
		if(dir==0)
		{
			ret=write(fd_exp,DIR_IN,strlen(DIR_IN));
			if(ret<0)
			{
				printf("write GPIO%d_IN error!\n",gpion);
				return -2;
			}
		}
		else if(dir==1)
		{
			ret=write(fd_exp,DIR_OUT,strlen(DIR_OUT));
			if(ret<0)
			{
				printf("write GPIO%d_OUT error!\n",gpion);
				return -3;
			}
		}
		close(fd_exp);
	}
	else
	{
		printf("export gpio error!\n");
	}
	
	return 1;	
}

//GPIO信号置高
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2\-3,失败

int Set_Gpio_H(int gpion)
{
	if(Set_Gpio_Dir(gpion,1))
	{
		int fd=0,ret=0;
		char path[50]={0};
			
		sprintf(path,"%s/gpio%d/value",DIRECTION_PATH,gpion);
		//打开GPIO_EXPORT文件
		fd=open(path,O_RDWR);
		if(fd<0)
		{
			printf("open GPIO%d_VALUE error!\n",gpion);
			return -1;
		}
		//写值，GPIO置高
		ret=write(fd,"1",1);
		if(ret<0)
		{
			printf("write GPIO%d_VALUE error!\n",gpion);
			return -2;
		}
	}
	else
	{
		printf("set gpio%d dir error!\n",gpion);
		return -3;
	}
	return 1;
}

//GPIO信号置低
//gpion:(GPIO1_4=32*1+4=36)
//return:1,成功;-1\-2\-3,失败

int Set_Gpio_L(int gpion)
{
	if(Set_Gpio_Dir(gpion,1))
	{
		int fd=0,ret=0;
		char path[50]={0};
			
		sprintf(path,"%s/gpio%d/value",DIRECTION_PATH,gpion);
		//打开GPIO_EXPORT文件
		fd=open(path,O_RDWR);
		if(fd<0)
		{
			printf("open GPIO%d_VALUE error!\n",gpion);
			return -1;
		}
		//写值，GPIO置低
		ret=write(fd,"0",1);
		if(ret<0)
		{
			printf("write GPIO%d_VALUE error!\n",gpion);
			return -2;
		}
	}
	else
	{
		printf("set gpio%d dir error!\n",gpion);
		return -3;
	}
	return 1;
}

//摄像头电源打开
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败

int Cam_Power_on(int channel)
{
	if(!Set_Gpio_H(cam_channel[channel]))
	{
		printf("channel %d power_on failed!\n",channel);
		return 0;
	}
	return 1;
}
//摄像头电源关闭
//channel:取值{1,2,3,4},代表通道号
//return:1,成功;0,失败

int Cam_Power_off(int channel)
{
	if(!Set_Gpio_L(cam_channel[channel]))
	{
		printf("channel %d power_off failed!\n",channel);
		return 0;
	}
	return 1;
}
//倒车信号开启
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败
int Acc_Sig_on(int channel)
{
	if(!Set_Gpio_L(acc_channel[channel]))
	{
		printf("channel %d ACC ON failed!\n",channel);
		return 0;
	}
	return 1;
}
//倒车信号关闭
//channel:取值{1,2,3},代表通道号
//return:1,成功;0,失败

int Acc_Sig_off(int channel)
{
	if(!Set_Gpio_H(acc_channel[channel]))
	{
		printf("channel %d ACC OFF failed!\n",channel);
		return 0;
	}
	return 1;
}


