#include <config.h>
#include "12864.h"
#include "delay.h"
//LCD忙信号检测
void check_buys()
{
	rs = 0;
	rw = 1;
	e  = 1;
	LCD12864_DA_PORT = 0x00;
	while(((LCD12864_DA_PORT & 0x80) == 0x80));
	e = 0;
} 
//写指令
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
//写数据	
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
//LCD初始化
void Lcd_init()
{
	rw = 0;
	pst = 1;//选择并行输入
	Delayms(10);
	write_com(0x30);//基本指令
	Delay100us(5);
	write_com(0x0c);//显示开，关光标
	Delay100us(5);
	write_com(0x01);//写一个字符地址加一
	Delay100us(5);
	write_com(0x06);
	Delay100us(5);
}							 	
//图片显示
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
//指定位置显示汉字
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
从LCD中读出数据
************************************/
unsigned char Lcd_ReadData(void)
{
	unsigned char Temp;
	check_buys();
 	LCD12864_DA_PORT = 0xff;
 	rs=1;
	rw=1;
	e=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
   	Temp=LCD12864_DA_PORT;
   	e=0;
   	return Temp;
}

/**************************************
为加速逻辑运算而设置的掩码表，这是以牺牲空间而换取时间的办法
***************************************/
code unsigned int LcdMaskTab[]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};
/***************************************
向LCD指定坐标写入一个象素,象素颜色有两种，0代表白（无显示），1代表黑（有显示）
****************************************/
void Lcd_PutPixel(unsigned char x,unsigned char y,unsigned char Color)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64)
		return;
	Color=Color%2;
	w=15-x%16;//确定对这个字的第多少位进行操作
	x=x/16;//确定为一行上的第几字

	if(y<32) //如果为上页
		z=0x80;
	else     //否则如果为下页
		z=0x88;

	y=y%32;
	EA=0;
	write_com(0x36);
	write_com(y+0x80);        //行地址
	write_com(x+z);     //列地址 
	Temp=Lcd_ReadData();//先空读一次
	Temp=(unsigned int)Lcd_ReadData()<<8;//再读出高8位
	Temp|=(unsigned int)Lcd_ReadData();//再读出低8位
	EA=1;
	if(Color==1) //如果写入颜色为1
		Temp|=LcdMaskTab[w];//在此处查表实现加速
	else         //如果写入颜色为0
		Temp&=~LcdMaskTab[w];//在此处查表实现加速
	EA=0;
	write_com(y+0x80);        //行地址
	write_com(x+z);     //列地址
		write_data(Temp>>8);//先写入高8位，再写入低8位
    write_data(Temp&0x00ff);
	write_com(0x30);
	EA=1;
}
/*****************************************
清除Lcd全屏，如果清除模式Mode为0，则为全屏清除为颜色0（无任何显示）
否则为全屏清除为颜色1(全屏填充显示)
******************************************/
void Lcd_Clear(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)
		Temp=0x00;
	else
		Temp=0xff;
	write_com(0x36);//扩充指令 绘图显示
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				EA=0;
				write_com(y+0x80);        //行地址
				write_com(x+0x80+ii);     //列地址     
				write_data(Temp); //写数据 D15－D8 
				write_data(Temp); //写数据 D7－D0 
				EA=1;
			}
	write_com(0x30);
}	