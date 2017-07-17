#include <config.h>
#include <rtx51tny.h>
//os_wait2 (K_TMO, (ms/10));     
/*******************
**功    能：延时N个微秒
**函 数 名：Delayus
**函数入口：无符号整形
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
**功    能：延时N个毫秒
**函 数 名：Delayms
**函数入口：无符号整形
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
**功    能：延时N个10微秒
**函 数 名：Delay10us
**函数入口：无符号整形
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
**功    能：延时N个10毫秒
**函 数 名：Delay10ms
**函数入口：无符号整形
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
**功    能：延时N个微秒
**函 数 名：Delay100us
**函数入口：无符号整形
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
**功    能：延时N个毫秒
**函 数 名：Delay100ms
**函数入口：无符号整形
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