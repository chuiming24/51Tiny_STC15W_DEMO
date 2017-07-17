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
#include <table.h>

#define os_enter_critical() ET0=0
#define os_exit_critical() 	ET0=1

/**********************************************************************
	第一个任务，用于初始化。
**********************************************************************/
void Init() _task_ 0  {                  
	gpio();			
	Lcd_init();
	DIS12864M();

	os_create_task (1);		  //创建第一个任务	
	os_create_task (2);		  //创建第二个任务
	os_create_task (3);		  //创建第二个任务

	os_delete_task (0);		  //初始化完毕，删除自身任务
}

///**********************************************************************
//	第二个任务，使用按键驱动屏幕显示
//**********************************************************************/
void LED1() _task_ 1{
	while (1)  {
		if(P23 == 0){
			os_wait2 (K_TMO, 1);
			if(P23 == 0){
				MenuUpOneOption();
			}
			while(!P23);
		}
		if(P24 == 0){
			os_wait2 (K_TMO, 1);
			if(P24 == 0){
				MenuEnterOption();	
			}
			while(!P24);
		}
		if(P25 == 0){
			os_wait2 (K_TMO, 1);
			if(P25 == 0){
				MenuDownOneOption();	
			}
			while(!P25);
		}
		if(P26 == 0){
			os_wait2 (K_TMO, 1);
			if(P26 == 0){
				MenuCancelOption();	
			}
			while(!P26);
		}
	}
}

/**********************************************************************
	第三个任务，使用12864进行驱动显示按键按下了按键1
**********************************************************************/
void LCD1() _task_ 2{
	while(1){
		;
	}
}
/**********************************************************************
	第三个任务，使用12864进行LED驱动
**********************************************************************/
void LCD2() _task_ 3{
	uchar i;
	uchar i_uper = 0;
	uchar i_downr = 0;
	while(1){
//		DIS12864M();
	}
}


//void main(){
//	Timer1Init();
//	EA = 1;
//	while(1){
//		;
//	}
//}