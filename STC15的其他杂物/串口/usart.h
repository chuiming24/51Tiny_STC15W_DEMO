#ifndef _USART_H_
#define _USART_H_

extern char data up[10];  		//ǰ׺
extern char data upLoog;	  	//ǰ׺����

extern char down[10]; 			//��׺
extern char data downLoog;	  	//��׺����

extern bit New_rec;				//�յ����ݱ�־λ
extern char ustData[25];		  	//����

void UartInit(void);		
void SendString(char *s);

#endif