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

//�򿪷�����
//return:1,�ɹ�;-1\-2,ʧ��
int beep_on()
{
	char path[50]={0};
	int fd=0,ret=0;
	
	strcpy(path,BEEP_PATH);
	strcat(path,"/"TRIGGER);
	//�򿪴������ļ�
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep trigger error!\n");
		return -1;
	}
	//���ô������ļ�Ϊ��ʱ������
	ret=write(fd,TRIGGER_TIMER,strlen(TRIGGER_TIMER));
	if(ret<0)
	{
		printf("write beep trigger_timer error!\n");
		return -2;
	}
	close(fd);

	strcpy(path,BEEP_PATH);
	strcat(path,"/"VALUE);
	//��brightness�ļ�
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep value error!\n");
		return -3;
	}
	//д��ʱ��ֵ����������
	ret=write(fd,BEEP_DEFAULT,strlen(BEEP_DEFAULT));
	if(ret<0)
	{
		printf("write beep value error!\n");
		return -4;
	}
	close(fd);
	
	return 1;
}

//�رշ�����
//return:1,�ɹ�;-1\-2,ʧ��
int beep_off()
{
	char path[50]={0};
	int fd=0,ret=0;
	
	strcpy(path,BEEP_PATH);
	strcat(path,"/"VALUE);
	//��brightness�ļ�
	fd=open(path,O_RDWR);
	if(fd<0)
	{
		printf("open beep value error!\n");
		return -1;
	}
	//д��ʱ��ֵ���رշ�����
	ret=write(fd,BEEP_OFF,strlen(BEEP_OFF));
	if(ret<0)
	{
		printf("write beep value error!\n");
		return -2;
	}
	close(fd);
	
	return 1;
}
//sysϵͳGPIO�ļ�����
//gpion:(GPIO1_4=32*1+4=36)
//return:1,�ɹ�;-1\-2,ʧ��

int Export_Gpio(int gpion)
{
	int fd_exp=0,ret=0;
	char val[5]={0};
	sprintf(val,"%d",gpion);
	//��EXPORT�ļ�
	fd_exp=open(EXPORT_PATH,O_RDWR);
	if(fd_exp<0)
	{
		printf("open export%d error!\n",gpion);
		return -1;
	}
	//дֵ������GPIO
	ret=write(fd_exp,val,strlen(val));
	if(ret<0)
	{
		printf("write export%d error!\n",gpion);
		return -2;
	}
	close(fd_exp);
	
	return 1;
}
//GPIO�ź����������������
//gpion:(GPIO1_4=32*1+4=36)
//dir:0--in;dir:1--out
//return:1,�ɹ�;-1\-2\-3,ʧ��
int Set_Gpio_Dir(int gpion,int dir)
{
	
	if(Export_Gpio(gpion))
	{
		int fd_exp=0,ret=0;
		char path[50]={0};
		
		sprintf(path,"%s/gpio%d/direction",DIRECTION_PATH,gpion);
		//��GPIO_EXPORT�ļ�
		fd_exp=open(path,O_RDWR);
		if(fd_exp<0)
		{
			printf("open GPIO%d_IN error!\n",gpion);
			return -1;
		}
		//дֵ������GPIO
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

//GPIO�ź��ø�
//gpion:(GPIO1_4=32*1+4=36)
//return:1,�ɹ�;-1\-2\-3,ʧ��

int Set_Gpio_H(int gpion)
{
	if(Set_Gpio_Dir(gpion,1))
	{
		int fd=0,ret=0;
		char path[50]={0};
			
		sprintf(path,"%s/gpio%d/value",DIRECTION_PATH,gpion);
		//��GPIO_EXPORT�ļ�
		fd=open(path,O_RDWR);
		if(fd<0)
		{
			printf("open GPIO%d_VALUE error!\n",gpion);
			return -1;
		}
		//дֵ��GPIO�ø�
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

//GPIO�ź��õ�
//gpion:(GPIO1_4=32*1+4=36)
//return:1,�ɹ�;-1\-2\-3,ʧ��

int Set_Gpio_L(int gpion)
{
	if(Set_Gpio_Dir(gpion,1))
	{
		int fd=0,ret=0;
		char path[50]={0};
			
		sprintf(path,"%s/gpio%d/value",DIRECTION_PATH,gpion);
		//��GPIO_EXPORT�ļ�
		fd=open(path,O_RDWR);
		if(fd<0)
		{
			printf("open GPIO%d_VALUE error!\n",gpion);
			return -1;
		}
		//дֵ��GPIO�õ�
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

//����ͷ��Դ��
//channel:ȡֵ{1,2,3},����ͨ����
//return:1,�ɹ�;0,ʧ��

int Cam_Power_on(int channel)
{
	if(!Set_Gpio_H(cam_channel[channel]))
	{
		printf("channel %d power_on failed!\n",channel);
		return 0;
	}
	return 1;
}
//����ͷ��Դ�ر�
//channel:ȡֵ{1,2,3,4},����ͨ����
//return:1,�ɹ�;0,ʧ��

int Cam_Power_off(int channel)
{
	if(!Set_Gpio_L(cam_channel[channel]))
	{
		printf("channel %d power_off failed!\n",channel);
		return 0;
	}
	return 1;
}
//�����źſ���
//channel:ȡֵ{1,2,3},����ͨ����
//return:1,�ɹ�;0,ʧ��
int Acc_Sig_on(int channel)
{
	if(!Set_Gpio_L(acc_channel[channel]))
	{
		printf("channel %d ACC ON failed!\n",channel);
		return 0;
	}
	return 1;
}
//�����źŹر�
//channel:ȡֵ{1,2,3},����ͨ����
//return:1,�ɹ�;0,ʧ��

int Acc_Sig_off(int channel)
{
	if(!Set_Gpio_H(acc_channel[channel]))
	{
		printf("channel %d ACC OFF failed!\n",channel);
		return 0;
	}
	return 1;
}


