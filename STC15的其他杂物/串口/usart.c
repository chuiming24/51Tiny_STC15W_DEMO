#include <stc15_usart.h>

bit Send_ed = 1;   				//�������ݽ�����־λ
bit New_rec = 0;				//�յ����ݱ�־λ
char xdata Rec_data[25] = {0};	//������
char Rec_data_down = 0;			//�������±�
char ustData[25] = {0};		  	//����
char ustData_down = 0;			//�����±�

char ustStat = 0;			//�ж�״̬��0Ϊʶ�����жϣ�1Ϊ����״̬��2Ϊ�������ж�
char data up[10] = "AT";  //ǰ׺
char data upLoog = 2;	  //ǰ׺����
//��׺
char down[10] = "QQQQQ"; //��׺
char ustDataDownDown = 0;	//��׺ʶ���±�
char data downLoog = 3;	  //��׺����

void SendString(char *s){
	while(*s){
		if(SendData(*s) == 1){
			s++;
		}
	}
}
void revData(char a){
	Rec_data[Rec_data_down] = a;
	switch(ustStat){
		case 0:
			if(Rec_data_down < upLoog && Rec_data[Rec_data_down] == up[Rec_data_down]){
				Rec_data_down++;
			}else{
				Rec_data_down = 0;	
			}
			if(Rec_data_down == upLoog){
				ustStat = 1;
			}
			break;
		case 1:
			//�ж��ǲ��Ǻ�׺
			if(Rec_data[Rec_data_down] == down[ustDataDownDown]){
				ustDataDownDown++;
			}else{
				ustDataDownDown = 0;
			}
			if(ustDataDownDown == downLoog){	//ȷ���Ǻ�ʶ������ȷ
				//���㻺��������
				ustDataDownDown = 0;
				Rec_data_down = 0;
				ustStat = 0;
				New_rec = 1;
				//����������ݱ�����ȥ�������ʶ����
				ustData[ustData_down-2] = '\0';
				//��������������
				ustData_down = 0;
				break;				
			}
			//�������������ݶ����������������±��λ
			ustData[ustData_down] = Rec_data[Rec_data_down];
			ustData_down++;
			Rec_data_down++;
			break;
	}
}