/*****************
**��  ��: Lcd12864����
**�����ˣ�������   
**��  ��11.0592MHZ
**��  �ã�STC-Y5
**ʱ  �䣺2017-06-02
**��  ����V����1.0
*****************/
#ifndef __LCD12864_H__
#define __LCD12864_H__

sbit rs = P3^5;
sbit rw = P4^2;
sbit e  = P3^4;
sbit pst = P4^4;
//�Զ��庯��
extern void check_buys();						//LCDæ�źż��
extern void write_com(uchar com);				//дָ��
extern void write_data(uchar dat);				//д����
extern void Lcd_init();							//LCD��ʼ��
extern void Lcd_draw(uchar code *pic);			//ͼƬ��ʾ
extern void Lcd_str(uchar X,uchar Y,uchar *s);	//ָ��λ����ʾ����
extern void Lcd_Clear(unsigned char Mode);//���Lcdȫ��
extern void Lcd_PutPixel(unsigned char x,unsigned char y,unsigned char Color);//��LCDָ������д��һ������,������ɫ�����֣�0����ף�����ʾ����1����ڣ�����ʾ��
#endif