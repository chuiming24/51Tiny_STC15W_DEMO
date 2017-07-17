/*****************
**功  能: Lcd12864驱动
**制作人：悠牧人   
**晶  振：11.0592MHZ
**适  用：STC-Y5
**时  间：2017-06-02
**版  本：V——1.0
*****************/
#ifndef __LCD12864_H__
#define __LCD12864_H__

sbit rs = P5^0;
sbit rw = P5^1;
sbit e  = P5^2;
sbit pst = P5^4;
#define LCD12864_DA_PORT P4
//自定义函数
extern void check_buys();						//LCD忙信号检测
extern void write_com(uchar com);				//写指令
extern void write_data(uchar dat);				//写数据
extern void Lcd_init();							//LCD初始化
extern void Lcd_draw(uchar code *pic);			//图片显示
extern void Lcd_str(uchar X,uchar Y,uchar *s);	//指定位置显示汉字
extern void Lcd_Clear(unsigned char Mode);//清除Lcd全屏
extern void Lcd_PutPixel(unsigned char x,unsigned char y,unsigned char Color);//向LCD指定坐标写入一个象素,象素颜色有两种，0代表白（无显示），1代表黑（有显示）
#endif