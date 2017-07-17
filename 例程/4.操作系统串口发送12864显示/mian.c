/**********************************************************************
作者：套套
邮箱：2011543651@qq.com
功能：用于演示STC15使用tiny51系统的例子
		使用keil官方的Tiny用串口函数进行串口命令读取并回显

**********************************************************************/
#include <rtx51tny.h>
#include <config.H>
#include <stdio.h>
#include <usar.h>
#include <12864.h>
#include <delay.h>

#define os_enter_critical() ET0=0
#define os_exit_critical() 	ET0=1

uchar idata inline[16] = "JKLJK";
char code menu[] = "\nCommand: ";


/**********************************************************************
	第一个任务，用于初始化。
**********************************************************************/
void Init() _task_ 0  {                  
	os_create_task (1);		  //创建第一个任务	
	os_create_task (2);		  //创建第二个任务		
	UartInit();			  	  //进行串口的初始化	
	Lcd_init();
	os_delete_task (0);		  //初始化完毕，删除自身任务
}

///**********************************************************************
//	第二个任务，使用keil官方的Tiny用串口函数进行串口命令读取并回显
//**********************************************************************/
void LED1() _task_ 1{
	while (1)  {
		SendString("send data:");
	 	getline (&inline, sizeof (inline));	//此处读取串口会自动调用putchar进行回显
		os_send_signal (2);					//注意，请勿在printf中调用inline，会造成资源冲突
		SendString ("getData\n\r");
	}
}

/**********************************************************************
	第三个任务，使用12864进行驱动
**********************************************************************/
void LCD12864() _task_ 2{
	static uchar i;	
	while(1){
		os_wait2 (K_SIG, 0);
		Lcd_str(i, 0, "                ");
	 	Lcd_str(i, 0, inline);				//显示内容
		P11 = ~P11;
		//计数增加限制
		i++;
		if(i == 4){
			i = 0;
		}
	}
}



//void main(){
//	Timer1Init();
//	EA = 1;
//	while(1){
//		;
//	}
//}