/**********************************************************************
作者：套套
邮箱：2011543651@qq.com
功能：用于演示STC15使用tiny51系统的例子
		使用keil官方的Tiny用串口函数进行串口命令读取并回显

**********************************************************************/
#include <rtx51tny.h>
#include <config.H>
#include <stdio.h>
#include <12864.h>
#include <delay.h>
#include <gpio.h>
#include <iic.h>
#include <usar.h>
#include <stdlib.h>

#define os_enter_critical() ET0=0
#define os_exit_critical() 	ET0=1
char temp[17];


/**********************************************************************
	第一个任务，用于初始化。
**********************************************************************/
void Init() _task_ 0  {                  
	os_create_task (1);		  //创建第一个任务	
	os_create_task (2);		  //创建第二个任务
	os_create_task (3);		  //创建第二个任务
	gpio();			
	Lcd_init();
	UartInit();
	Lcd_str(0, 0, "1 OFF!");
	Lcd_str(1, 0, "2 OFF!");
	os_delete_task (0);		  //初始化完毕，删除自身任务
}

///**********************************************************************
//	第二个任务，使用按键驱动屏幕显示
//**********************************************************************/
void LED1() _task_ 1{
	while (1)  {
		if(P24 == 0){
			os_wait2 (K_TMO, 1);
			if(P24 == 0){
				os_send_signal (3);	
			}
			while(!P24);
		}
	}
}

/**********************************************************************
	第三个任务，使用12864进行驱动显示按键按下了按键1
**********************************************************************/
void LCD1() _task_ 2{
	while(1){
		uchar ad_value;
		int i;
		ad_value=ADC_read(0x41);
		i = i|ad_value;
		i = i&ad_value;
		sprintf(temp, "adc:%d", i);
	 	Lcd_str(0, 0, temp);				//显示内容
		SendData(ad_value);
		os_wait2 (K_TMO, 1);
	}
}
/**********************************************************************
	第三个任务，使用12864进行LED驱动
**********************************************************************/
void LCD2() _task_ 3{
	while(1){
		os_wait2 (K_SIG, 0);
			P1 = ~0x01;
			Lcd_str(1, 0, "                ");
		 	Lcd_str(1, 0, "状态1!");				//显示内容
		os_wait2 (K_SIG, 0);
			P1 = ~0x02;
			Lcd_str(1, 0, "                ");
		 	Lcd_str(1, 0, "状态2!");				//显示内容
		os_wait2 (K_SIG, 0);
			P1 = ~0x04;
			Lcd_str(1, 0, "                ");
		 	Lcd_str(1, 0, "状态3!");				//显示内容
		os_wait2 (K_SIG, 0);
			P1 = ~0x08;
			Lcd_str(1, 0, "                ");
		 	Lcd_str(1, 0, "状态4!");				//显示内容
	}
}


//void main(){
//	Timer1Init();
//	EA = 1;
//	while(1){
//		;
//	}
//}