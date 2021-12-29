#include <STC89C5xRC.H>
#include <intrins.h>
#include <reg51.h>
#include "lcd12864.h"

unsigned char js=0;//定义变量js


void Delay100ms()		//@11.0592MHz 延时100ms
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

//100ms延时函数

void Delay5000ms()		//@11.0592MHz 延时5000ms
{
	unsigned char i, j, k;

	_nop_();
	i = 36;
	j = 5;
	k = 211;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//5000ms延时函数

void bee3()        //蜂鸣器响3次
{
	int a=0;
	while(a<3)
	{
		P20=0;Delay100ms();
		P20=1;Delay100ms();
		a=a+1;
	}	
	return;
}

void bee1() 			//蜂鸣器响1次
{
	int a=0;
	while(a<1)
	{
		P20=0;Delay100ms();
		P20=1;Delay100ms();
		a=a+1;
	}	
	return;
}

unsigned char code CharCode1[]="欢迎使用求助机";
unsigned char code CharCode2[]="我生病了      ";
unsigned char code CharCode3[]="着火了        ";
unsigned char code CharCode4[]="电路故障      ";
unsigned char code CharCode5[]="其他求助      ";  
unsigned char code CharCode6[]="WiFi连接成功  ";  //设置6个字符串


void com1() interrupt 4//串口通信终端函数
{


	if(RI)
	{
		RI = 0;//清除接收中断标志位
//		com[js]=SBUF;//存储接收到的数据
		js = js+1;
		

	}
}


void main()					//主函数开始
{
	unsigned char i;
	Delay100ms();
	LCD12864_Init();		//定义一些变量
	
	bee3();							//蜂鸣器响3次
	
	LCD12864_SetWindow(0, 0);
		while(CharCode1[i]!='\0')          //显示字符串_1
	{
			LCD12864_WriteData(CharCode1[i]);
			i++;
			if(i==16)  //第一行满写第三行
			{LCD12864_SetWindow(1,0);}
			if(i==32)  //第三行满写第四行
			{LCD12864_SetWindow(2,0);}
			if(i==48)  //第三行满写第四行
			{LCD12864_SetWindow(3,0);}		
	}
	
	
	
	
	
	
TMOD |= 0x20;   //设置计数器工作方式
SCON = 0x50;    //设置为工作方式
PCON = 0x80;    //波特率加倍
TH1 = 0xfa;     //计数器初始值设置 9600bps
TL1 = 0xfa;
ES = 1;         //打开接收中断
EA = 1;         //打开总中断
TR1 = 1;        //打开计数器
	
	
	


	
	i=0;
	Delay5000ms(); 
	
	P21=0;  //指示灯亮
	js=0;
	
	
	while(js<35);
		
	P21=1;  //指示灯暗

	LCD12864_SetWindow(0, 0);
		while(CharCode6[i]!='\0')          //显示字符串_6
	{
			LCD12864_WriteData(CharCode6[i]);
			i++;
			if(i==16)  //第一行满写第三行
			{LCD12864_SetWindow(1,0);}
			if(i==32)  //第三行满写第四行
			{LCD12864_SetWindow(2,0);}
			if(i==48)  //第三行满写第四行
			{LCD12864_SetWindow(3,0);}		
	}
	

	
	
	while(1)
{
	i=0;
	LCD12864_SetWindow(0, 0);					//定义变量后，依次判断哪个按钮被按下，不妨设P12
	OPTION:	
	if(P12==0)												
		{	
			while(CharCode2[i]!='\0')			//按下	P12后显示字符串_2
			{
				LCD12864_WriteData(CharCode2[i]);
				i++;
				if(i==16)  //第一行满写第三行
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //第三行满写第四行
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //第三行满写第四行
				{LCD12864_SetWindow(3,0);}
			}
			bee1();                      //写完后蜂鸣器响1次，整个程序返回if判断按钮前（标签OPTION）
			goto OPTION;
		}	
	else if(P13==0)
		{	while(CharCode3[i]!='\0')
			{
				LCD12864_WriteData(CharCode3[i]);
				i++;
				if(i==16)  //第一行满写第三行
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //第三行满写第四行
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //第三行满写第四行
				{LCD12864_SetWindow(3,0);}
			}
				bee1();
				goto OPTION;
		}	
	else if(P14==0)
		{	while(CharCode4[i]!='\0')
			{
				LCD12864_WriteData(CharCode4[i]);
				i++;
				if(i==16)  //第一行满写第三行
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //第三行满写第四行
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //第三行满写第四行
				{LCD12864_SetWindow(3,0);}
			}
			bee1();
		  goto OPTION;
		}	
	else if(P15==0)
		{	while(CharCode5[i]!='\0')
			{
				LCD12864_WriteData(CharCode5[i]);
				i++;
				if(i==16)  //第一行满写第三行
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //第三行满写第四行
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //第三行满写第四行
				{LCD12864_SetWindow(3,0);}
			}
			bee1();
		  goto OPTION;
		}	
}
}