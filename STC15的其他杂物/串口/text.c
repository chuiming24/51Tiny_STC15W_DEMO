#include <config.h>
#include <usart.h>

void main(){
	UartInit();
	ES = 1;		  	//�򿪴����ж�
	EA = 1;			//�����ж�
	strcpy(up, "QTAT");		   //�趨ʶ����ǰ׺����
	upLoog = 4;				   //�趨ʶ����ǰ׺����
	strcpy(down, "QQQ");		   //�趨ʶ�����׺����
	downLoog = 3;				   //�趨ʶ�����׺����
	while(1){
	 	if(New_rec == 1){
			New_rec = 0;
			SendString(ustData);
		}
	}
}