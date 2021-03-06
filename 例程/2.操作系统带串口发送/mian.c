/**********************************************************************
作者：套套
邮箱：2011543651@qq.com
功能：用于演示STC15使用tiny51系统的例子
		使用自己写的函数以及系统自带的标准输入输出函数来进行串口输出
		使用自带的任务信号函数进行交流

**********************************************************************/
#include <rtx51tny.h>
#include <config.H>
#include <stdio.h>
#include <usar.h>

#define os_enter_critical() ET0=0
#define os_exit_critical() 	ET0=1

char code menu[] = 
   "\n"
   "+********* SERIAL PRINT using C51 and RTX-51 tiny ***************+\n"
   "| This program is a simple example with serial.                  |\n"
   "|                                          ----taotao            |\n"
   "+----------------------------------------------------------------+\n";


/**********************************************************************
	第一个任务，用于初始化。
**********************************************************************/
void Init() _task_ 0  {                  
	os_create_task (1);		  //创建第一个任务	
	os_create_task (2);		  //创建第二个任务		
	UartInit();			  	  //进行串口的初始化	

	os_delete_task (0);		  //初始化完毕，删除自身任务
}

/**********************************************************************
	第二个任务，使用SendString函数进行串口发送
**********************************************************************/
void LED1() _task_ 1{
	while (1)  {
		SendString("send data\n\r");
		os_wait2 (K_TMO, 50); //等待25个系统周期，约0.25秒
		os_send_signal (2);   //发送信号给任务编号2，也就是第三个任务
								//函数os_send_signal给一个指定任务（用task_id来标明）发送信号。如果该任务已经在等待信号，那么这个函数就让这个指定任务进入就绪状态准备运行，当然这个函数并没有启动一个任务的功能。如果所指定的任务还没有在等待信号，那么这个信号也保存在该指定任务的信号标志中。
		os_wait2 (K_TMO, 150); //等待25个系统周期，约0.75秒
	}
}

/**********************************************************************
	第三个任务，使用标准输入输出的printf来进行串口发送
**********************************************************************/
void LED2() _task_ 2{
	
	while(1){
		os_wait2 (K_TMO, 220);		   //等待接受信号
											//函数os_wait可以暂停当前任务并等待一个或者几个事件，例如：时间间隔、超时或者从另外一个任务或中断发出的信号。
											//第一个参数有三种传入方法：K_IVL	等待一个时间间隔事件，也就是延时
																	  //K_SIG	等待一个信号
																	  //K_TMO	等待一个信号，并进行超时判定。
		printf(menu);				   //发送字符数组			
	}
}


//void main(){
//	Timer1Init();
//	EA = 1;
//	while(1){
//		;
//	}
//}