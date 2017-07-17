#include <config.h>
#include <rtx51tny.h>
//os_wait2 (K_TMO, (ms/10));     
/*******************
**��    �ܣ���ʱN��΢��
**�� �� ����Delayus
**������ڣ��޷�������
*******************/
void Delayus(uint us)
{
	for(;us>0;us--)
	{
		_nop_();
		_nop_();
		_nop_();
	} 
}
/*******************
**��    �ܣ���ʱN������
**�� �� ����Delayms
**������ڣ��޷�������
*******************/
void Delayms(uint ms)
{
	unsigned char i, j;
	for(;ms>0;ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);	
	}
}
/*******************
**��    �ܣ���ʱN��10΢��
**�� �� ����Delay10us
**������ڣ��޷�������
*******************/
void Delay10us(uint us)
{
	unsigned char i;

	for(;us>0;us--)
	{
		_nop_();
		i = 25;
		while (--i);
	}
}
/*******************
**��    �ܣ���ʱN��10����
**�� �� ����Delay10ms
**������ڣ��޷�������
*******************/
void Delay10ms(uint ms)
{
	unsigned char i, j;

	for(;ms>0;ms--)
	{
		i = 108;
		j = 145;
		do
		{
			while (--j);
		} while (--i);	
	}
}
/*******************
**��    �ܣ���ʱN��΢��
**�� �� ����Delay100us
**������ڣ��޷�������
*******************/
void Delay100us(uint us)
{
	unsigned char i, j;

	for(;us>0;us--)
	{
		_nop_();
		_nop_();
		i = 2;
		j = 15;
		do
		{
			while (--j);
		} while (--i);
	}
}
/*******************
**��    �ܣ���ʱN������
**�� �� ����Delay100ms
**������ڣ��޷�������
*******************/
void Delay100ms(uint ms)
{
	unsigned char i, j,k;

	for(;ms>0;ms--)
	{
		_nop_();
		_nop_();
		i = 5;
		j = 52;
		k = 195;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);	
	}
}