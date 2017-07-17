#ifndef _IIC_H
#define _IIC_H


#define somenop Delay5us()
//#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();}
#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SDA = P2^0;  /* ������ */
sbit SCL = P2^1;  /* ʱ���� */

//��������
void Delay5us();		//@11.0592MHz
void IIC_Start(void); 
void IIC_Stop(void);  
void IIC_Ack(unsigned char ackbit); 
void IIC_SendByte(unsigned char byt); 
bit IIC_WaitAck(void);  
unsigned char IIC_RecByte(void); 
unsigned char ADC_read(uchar com);

#endif