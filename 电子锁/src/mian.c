/**********************************************************************
作者：套套
邮箱：2011543651@qq.com
功能：用于演示STC15使用tiny51系统的例子
		使用keil官方的Tiny用串口函数进行串口命令读取并回显

**********************************************************************/
#include <config.H>
#include <stdio.h>
#include <12864.h>
#include <delay.h>
#include <gpio.h>
#include <key.h>
#include "mfrc522.h"

#define os_enter_critical() ET0=0
#define os_exit_critical() 	ET0=1

unsigned char card_type[20];//卡类型
unsigned char card_key[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//卡密码
char code_string[20];
bit flag_rfid  = 0;//表示是否有RFID标签接触着感应器
long int card_code;

long int code card[7] = {
1646022205,
1646445629 ,
2891902230	,
2892454518	 ,
1382879549	  ,
1382896445	   ,
2892253110

};

///**********************************************************************
//	第一个任务，用于初始化。
//**********************************************************************/
//void Init() _task_ 0  {                  
//	gpio();			
//	Lcd_init();	
//	//
//	os_create_task (1);		  //创建第一个任务	
//	os_create_task (2);		  //创建第二个任务
//	os_create_task (3);		  //创建第二个任务
//
//	os_delete_task (0);		  //初始化完毕，删除自身任务
//}
//
/////**********************************************************************
////	第二个任务，填入数据
////**********************************************************************/
//void LED1() _task_ 1{
//
//
//
//}
//
///**********************************************************************
//	第三个任务，用于键盘扫描
//**********************************************************************/
//void LCD1() _task_ 2{
//	char temp_char[20];
//	int key_temp = 0;
//	int i;
//
////	Lcd_str(1, 0, "多动朕电子锁");
////	P55 = 0;
//	while(1){
//		key_temp = read_keyboard();
//		if(key_temp != 0xff){
////			sprintf(temp_char , "%d 号按键按下了", key_temp);
////			Lcd_str(2, 0, temp_char);
////			i++;			
//		}
//
//		
////		sprintf(temp_char , "%d number", i);
////		Lcd_str(3, 0, temp_char);
//	}
//}
///**********************************************************************
//	第三个任务，开锁
//**********************************************************************/
//void LCD2() _task_ 3{
//	uchar i;
//	uchar i_uper = 0;
//	uchar i_downr = 0;
//	while(1){
////		DIS12864M();
//	}
//}


void main(){
unsigned char temp,t=0, i = 0;

	gpio();			
	Lcd_init();	

	Lcd_str(3, 0, "多动朕电子锁");
	while(1){
		temp = PcdRequest(PICC_REQALL, card_type);	 //读RFID第一步：寻卡
		if (temp != MI_OK)
		{
			temp = PcdReset();
			PcdAntennaOff();
			PcdAntennaOn();
			continue; //跳出该次循环，进行第二次循环读取
		}
		temp = PcdAnticoll(card_type); //读RFID第二步：防冲撞
		if (temp != MI_OK)
			continue;

		temp = PcdSelect(card_type); //读RFID第三步：选定卡片
		if (temp != MI_OK)
			continue;
		else
		{

				//card_type[3]~[0]存放着rfid卡的uid号码，是16进制码
				card_code = card_type[3];
				card_code<<=8;//表示card_code向左移动8个二进制位，相当于乘上2的8次方，可以参考十进制向左移动n位就相当于乘上10的n次方
				card_code |= card_type[2];
				card_code<<=8;
				card_code |= card_type[1];
				card_code<<=8;
				card_code |= card_type[0];//把uid号码（unsigned long int类型）更新到数组里面


				sprintf(code_string, "%lu", card_code);//sprintf指的是字符串格式化命令，主要功能是把格式化的数据写入某个字符串中,%lu表示输出无符号长整型整数，表示的是进行格式化输入的参数的格式	
				Lcd_str(0, 0, code_string);

				for(i = 0; i<7; i++){
					if(card_code == card[i]){
						Lcd_str(1, 0, "开锁");
						P36 = 0;
						Delayms(1500ul);
						P36 = 1;
						Delayms(2000ul);
						Lcd_str(1, 0, "    ");	
					}
				}
		}				
	
	}
}