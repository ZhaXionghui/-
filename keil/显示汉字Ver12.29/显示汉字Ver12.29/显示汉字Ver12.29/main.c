#include <STC89C5xRC.H>
#include <intrins.h>
#include <reg51.h>
#include "lcd12864.h"

unsigned char js=0;//�������js


void Delay100ms()		//@11.0592MHz ��ʱ100ms
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

//100ms��ʱ����

void Delay5000ms()		//@11.0592MHz ��ʱ5000ms
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

//5000ms��ʱ����

void bee3()        //��������3��
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

void bee1() 			//��������1��
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

unsigned char code CharCode1[]="��ӭʹ��������";
unsigned char code CharCode2[]="��������      ";
unsigned char code CharCode3[]="�Ż���        ";
unsigned char code CharCode4[]="��·����      ";
unsigned char code CharCode5[]="��������      ";  
unsigned char code CharCode6[]="WiFi���ӳɹ�  ";  //����6���ַ���


void com1() interrupt 4//����ͨ���ն˺���
{


	if(RI)
	{
		RI = 0;//��������жϱ�־λ
//		com[js]=SBUF;//�洢���յ�������
		js = js+1;
		

	}
}


void main()					//��������ʼ
{
	unsigned char i;
	Delay100ms();
	LCD12864_Init();		//����һЩ����
	
	bee3();							//��������3��
	
	LCD12864_SetWindow(0, 0);
		while(CharCode1[i]!='\0')          //��ʾ�ַ���_1
	{
			LCD12864_WriteData(CharCode1[i]);
			i++;
			if(i==16)  //��һ����д������
			{LCD12864_SetWindow(1,0);}
			if(i==32)  //��������д������
			{LCD12864_SetWindow(2,0);}
			if(i==48)  //��������д������
			{LCD12864_SetWindow(3,0);}		
	}
	
	
	
	
	
	
TMOD |= 0x20;   //���ü�����������ʽ
SCON = 0x50;    //����Ϊ������ʽ
PCON = 0x80;    //�����ʼӱ�
TH1 = 0xfa;     //��������ʼֵ���� 9600bps
TL1 = 0xfa;
ES = 1;         //�򿪽����ж�
EA = 1;         //�����ж�
TR1 = 1;        //�򿪼�����
	
	
	


	
	i=0;
	Delay5000ms(); 
	
	P21=0;  //ָʾ����
	js=0;
	
	
	while(js<35);
		
	P21=1;  //ָʾ�ư�

	LCD12864_SetWindow(0, 0);
		while(CharCode6[i]!='\0')          //��ʾ�ַ���_6
	{
			LCD12864_WriteData(CharCode6[i]);
			i++;
			if(i==16)  //��һ����д������
			{LCD12864_SetWindow(1,0);}
			if(i==32)  //��������д������
			{LCD12864_SetWindow(2,0);}
			if(i==48)  //��������д������
			{LCD12864_SetWindow(3,0);}		
	}
	

	
	
	while(1)
{
	i=0;
	LCD12864_SetWindow(0, 0);					//��������������ж��ĸ���ť�����£�������P12
	OPTION:	
	if(P12==0)												
		{	
			while(CharCode2[i]!='\0')			//����	P12����ʾ�ַ���_2
			{
				LCD12864_WriteData(CharCode2[i]);
				i++;
				if(i==16)  //��һ����д������
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //��������д������
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //��������д������
				{LCD12864_SetWindow(3,0);}
			}
			bee1();                      //д����������1�Σ��������򷵻�if�жϰ�ťǰ����ǩOPTION��
			goto OPTION;
		}	
	else if(P13==0)
		{	while(CharCode3[i]!='\0')
			{
				LCD12864_WriteData(CharCode3[i]);
				i++;
				if(i==16)  //��һ����д������
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //��������д������
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //��������д������
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
				if(i==16)  //��һ����д������
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //��������д������
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //��������д������
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
				if(i==16)  //��һ����д������
				{LCD12864_SetWindow(1,0);}
				if(i==32)  //��������д������
				{LCD12864_SetWindow(2,0);}
				if(i==48)  //��������д������
				{LCD12864_SetWindow(3,0);}
			}
			bee1();
		  goto OPTION;
		}	
}
}