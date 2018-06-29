#include <config.h>

void revData(char a);
extern bit Send_ed;



void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE8;		//�趨��ʱ��ֵ
	TH1 = 0xFF;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}
char SendData(char dat){
	if(Send_ed == 1){
	   	Send_ed = 0;
		SBUF = dat;	
		return 1;	
	}
	return 0;
}

void ser() interrupt 4{
	char a;
	if(TI){
		TI = 0;
		Send_ed = 1;
	}
	if(RI){
		RI = 0;
		a = SBUF;
		revData(a);
	}
}