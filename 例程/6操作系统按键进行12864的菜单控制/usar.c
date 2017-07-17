#include <config.h>
#include <usar.h>

bit busy = 0;
bit uart_get_flag = 0;
char uart_get_data = 0;

#define  ILEN  8
unsigned char  istart;         
unsigned char  iend;       
idata    char  inbuf[ILEN];

char getkey ()  {    
	while  (iend == istart);
	return (inbuf[istart++ & (ILEN-1)]);  
}


void uart_isr() interrupt 4{
	unsigned char c;
	if(RI){
		RI = 0;
		c = SBUF;
        if (istart + ILEN != iend)  {
          inbuf[iend++ & (ILEN-1)] = c;
        }
	}
	if(TI){
		TI = 0;
		busy = 0;
	}
}

void SendData(char dat){
	while(busy);
   	busy = 1;
	SBUF = dat;
}

void SendString(char *s){
	while(*s){
		SendData(*s++);
	}
}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE0;		//�趨��ʱ��ֵ
	TH1 = 0xFE;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	ES = 1;
	PS = 1;
}