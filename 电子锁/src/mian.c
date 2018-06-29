/**********************************************************************
���ߣ�����
���䣺2011543651@qq.com
���ܣ�������ʾSTC15ʹ��tiny51ϵͳ������
		ʹ��keil�ٷ���Tiny�ô��ں������д��������ȡ������

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

unsigned char card_type[20];//������
unsigned char card_key[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//������
char code_string[20];
bit flag_rfid  = 0;//��ʾ�Ƿ���RFID��ǩ�Ӵ��Ÿ�Ӧ��
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
//	��һ���������ڳ�ʼ����
//**********************************************************************/
//void Init() _task_ 0  {                  
//	gpio();			
//	Lcd_init();	
//	//
//	os_create_task (1);		  //������һ������	
//	os_create_task (2);		  //�����ڶ�������
//	os_create_task (3);		  //�����ڶ�������
//
//	os_delete_task (0);		  //��ʼ����ϣ�ɾ����������
//}
//
/////**********************************************************************
////	�ڶ���������������
////**********************************************************************/
//void LED1() _task_ 1{
//
//
//
//}
//
///**********************************************************************
//	�������������ڼ���ɨ��
//**********************************************************************/
//void LCD1() _task_ 2{
//	char temp_char[20];
//	int key_temp = 0;
//	int i;
//
////	Lcd_str(1, 0, "�ද�޵�����");
////	P55 = 0;
//	while(1){
//		key_temp = read_keyboard();
//		if(key_temp != 0xff){
////			sprintf(temp_char , "%d �Ű���������", key_temp);
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
//	���������񣬿���
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

	Lcd_str(3, 0, "�ද�޵�����");
	while(1){
		temp = PcdRequest(PICC_REQALL, card_type);	 //��RFID��һ����Ѱ��
		if (temp != MI_OK)
		{
			temp = PcdReset();
			PcdAntennaOff();
			PcdAntennaOn();
			continue; //�����ô�ѭ�������еڶ���ѭ����ȡ
		}
		temp = PcdAnticoll(card_type); //��RFID�ڶ���������ײ
		if (temp != MI_OK)
			continue;

		temp = PcdSelect(card_type); //��RFID��������ѡ����Ƭ
		if (temp != MI_OK)
			continue;
		else
		{

				//card_type[3]~[0]�����rfid����uid���룬��16������
				card_code = card_type[3];
				card_code<<=8;//��ʾcard_code�����ƶ�8��������λ���൱�ڳ���2��8�η������Բο�ʮ���������ƶ�nλ���൱�ڳ���10��n�η�
				card_code |= card_type[2];
				card_code<<=8;
				card_code |= card_type[1];
				card_code<<=8;
				card_code |= card_type[0];//��uid���루unsigned long int���ͣ����µ���������


				sprintf(code_string, "%lu", card_code);//sprintfָ�����ַ�����ʽ�������Ҫ�����ǰѸ�ʽ��������д��ĳ���ַ�����,%lu��ʾ����޷��ų�������������ʾ���ǽ��и�ʽ������Ĳ����ĸ�ʽ	
				Lcd_str(0, 0, code_string);

				for(i = 0; i<7; i++){
					if(card_code == card[i]){
						Lcd_str(1, 0, "����");
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