#include <config.h>
#include "12864.h"
#include "delay.h"
//LCDæ�źż��
void check_buys()
{
	rs = 0;
	rw = 1;
	e  = 1;
	LCD12864_DA_PORT = 0x00;
	while(((LCD12864_DA_PORT & 0x80) == 0x80));
	e = 0;
} 
//дָ��
void write_com(uchar com)
{
	check_buys();
	rs = 0;
	rw = 0;
	e  = 1;
	LCD12864_DA_PORT = com;
	Delay100us(5);
	e  = 0;
	Delay100us(5);	
}			
//д����	
void write_data(uchar dat)
{
	check_buys();
	rs = 1;
	rw = 0;
	e  = 1;
	LCD12864_DA_PORT = dat;
	Delay100us(5);
	e  = 0;
	Delay100us(5);
}				 
//LCD��ʼ��
void Lcd_init()
{
	P5M1 &= ~(1<<4);		//����P5.4Ϊ׼˫��IO
	P5M0 &= ~(1<<4);


	P5M1 &= ~(1<<0);		//����P5.0Ϊ׼˫��IO
	P5M0 &= ~(1<<0);

	P5M1 &= ~(1<<1);		//����P5.1Ϊ׼˫��IO
	P5M0 &= ~(1<<1);

	P5M1 &= ~(1<<2);		//����P5.2Ϊ׼˫��IO
	P5M0 &= ~(1<<2);

	P4M1 = 0X00;		//����P4Ϊ׼˫��IO
	P4M0 = 0X00;
	rw = 0;
	pst = 1;//ѡ��������
	Delayms(10);
	write_com(0x30);//����ָ��
	Delay100us(5);
	write_com(0x0c);//��ʾ�����ع��
	Delay100us(5);
	write_com(0x01);//дһ���ַ���ַ��һ
	Delay100us(5);
	write_com(0x06);
	Delay100us(5);
}							 	
//ͼƬ��ʾ
void Lcd_draw(uchar code *pic)
{
	uchar i,j,k;

	write_com(0x34);
	for(i = 0;i < 2;i++)
	{
		for(j = 0;j < 32; j++)
		{
			write_com(0x80 + j);
			if(i == 0)
			{
				write_com(0x80);
			}
			else
			{
				write_com(0x88);
			}
			for(k = 0;k < 16;k++)
			{
				write_data(*pic++);
			}
		}
	}
	write_com(0x36);
	write_com(0x30);
}		   
//ָ��λ����ʾ����
void Lcd_str(uchar X,uchar Y,uchar *s)
{
	uchar pos;
	if(X == 0)
		X = 0x80;
	else if(X == 1)
		X = 0x90;
	else if(X == 2)
		X = 0x88;
	else if(X == 3)
		X = 0x98;
	pos = X+Y;
	write_com(pos);
	while(*s>0)
	{
		write_data(*s++);
		Delay100us(5);
	}
}
/***********************************
��LCD�ж�������
************************************/

void Delay100u()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}

unsigned char Lcd_ReadData(void)
{
	unsigned char Temp;
	check_buys();
 	LCD12864_DA_PORT = 0xff;
 	rs=1;
	rw=1;
	e=0;
	e=1;
	Delay100u();
   	Temp=LCD12864_DA_PORT;
   	e=0;
   	return Temp;
}

/**************************************
Ϊ�����߼���������õ�����������������ռ����ȡʱ��İ취
***************************************/
code unsigned int LcdMaskTab[]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};
/***************************************
��LCDָ������д��һ������,������ɫ�����֣�0����ף�����ʾ����1����ڣ�����ʾ��
****************************************/
void Lcd_PutPixel(unsigned char x,unsigned char y,unsigned char Color)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64)
		return;
	Color=Color%2;
	w=15-x%16;//ȷ��������ֵĵڶ���λ���в���
	x=x/16;//ȷ��Ϊһ���ϵĵڼ���

	if(y<32) //���Ϊ��ҳ
		z=0x80;
	else     //�������Ϊ��ҳ
		z=0x88;

	y=y%32;
	EA=0;
	write_com(0x36);
	write_com(y+0x80);        //�е�ַ
	write_com(x+z);     //�е�ַ 
	Temp=Lcd_ReadData();//�ȿն�һ��

	Temp=(unsigned int)Lcd_ReadData()<<8;//�ٶ�����8λ
	Temp|=(unsigned int)Lcd_ReadData();//�ٶ�����8λ
	EA=1;
	if(Color==1) //���д����ɫΪ1
		Temp|=LcdMaskTab[w];//�ڴ˴����ʵ�ּ���
	else         //���д����ɫΪ0
		Temp&=~LcdMaskTab[w];//�ڴ˴����ʵ�ּ���
	EA=0;
	write_com(y+0x80);        //�е�ַ
	write_com(x+z);     //�е�ַ
	write_data(Temp>>8);//��д���8λ����д���8λ
    write_data(Temp&0x00ff);
	write_com(0x30);
	EA=1;

}

void Lcd_PutPixel_Sp(unsigned char x,unsigned char y,unsigned char Color)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64)
		return;
	Color=Color%2;
	w=15-x%16;//ȷ��������ֵĵڶ���λ���в���
	x=x/16;//ȷ��Ϊһ���ϵĵڼ���

	if(y<32) //���Ϊ��ҳ
		z=0x80;
	else     //�������Ϊ��ҳ
		z=0x88;

	y=y%32;
	Temp = 0x0000;
	if(Color==1) //���д����ɫΪ1
		Temp|=LcdMaskTab[w];//�ڴ˴����ʵ�ּ���
	else         //���д����ɫΪ0
		Temp&=~LcdMaskTab[w];//�ڴ˴����ʵ�ּ���
	EA=0;
	write_com(0x36);
	write_com(y+0x80);        //�е�ַ
	write_com(x+z);     //�е�ַ
	write_data(Temp>>8);//��д���8λ����д���8λ
    write_data(Temp&0x00ff);
	write_com(0x30);
	EA=1;

}
/*****************************************
���Lcdȫ����������ģʽModeΪ0����Ϊȫ�����Ϊ��ɫ0�����κ���ʾ��
����Ϊȫ�����Ϊ��ɫ1(ȫ�������ʾ)
******************************************/
void Lcd_Clear(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)
		Temp=0x00;
	else
		Temp=0xff;
	write_com(0x36);//����ָ�� ��ͼ��ʾ
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				EA=0;
				write_com(y+0x80);        //�е�ַ
				write_com(x+0x80+ii);     //�е�ַ     
				write_data(Temp); //д���� D15��D8 
				write_data(Temp); //д���� D7��D0 
				EA=1;
			}
	write_com(0x30);
}	