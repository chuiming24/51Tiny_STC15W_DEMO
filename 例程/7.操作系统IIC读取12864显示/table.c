#include <config.h>

//�˵���ʵ��
/*-------------------------------------------------------------*/
#define MENU_SIZE 40             //�˵�����

unsigned char KeyFuncIndex=0;    //��ŵ�ǰ�Ĳ˵�����
void (*KeyFuncPtr)();            //���尴������ָ��
//�������� 

typedef struct 
{
   unsigned char KeyStateIndex;   //��ǰ��״̬������
   unsigned char KeyDownState;    //�������¼�ʱ��״̬������
   unsigned char KeyUpState;      //�������ϼ�ʱ��״̬������
   unsigned char KeyEnterState;   //���»س���ʱ��״̬������
   void (*CurrentOperate)();      //��ǰ״̬Ӧ��ִ�еĹ��ܲ���
   char ShowChar[17];
}  StateTab;
//
//


/*-------------------------------------------------------------
   �˵�Ҫ�޸ĵ�����
-------------------------------------------------------------*/
 //���ݽṹ����
 //��¼ÿһ��ĵ�һ�����ֵ�����
//һ����¼��ǰָ�������
//һ����¼�б�ĺ���
StateTab code KeyTab[MENU_SIZE]=
{
//��ǰ�����£����ϣ�ȷ��
   	{0,1,1,2,   (*Stat0), "111111111111"},    //����  ��ǰ��״̬������,�������¼�ʱ��״̬������,�������ϼ�ʱ��״̬������,���»س���ʱ��״̬������,��ǰ״̬Ӧ��ִ�еĹ��ܲ���
	{1,0,0,6,   (*Stat1)},	   //����

	{2,3,5,10,  (*Stat2)},     //����
	{3,4,2,11,  (*Stat3)},	   //����
	{4,5,3,12,  (*Stat4)},	   //����
	{5,2,4,0,   (*Stat5)},	   //����

	{6,7,9,13,  (*Stat6)},     //����
	{7,8,6,14,  (*Stat7)},     //
	{8,9,7,15,  (*Stat8)},   
	{9,6,8,1 ,  (*Stat9)},     //����

	{10,2,2,2,(*Stat10)},    //��		   LineTest
	{11,3,3,3,(*Stat11)},	   //		   RectTest
	{12,4,4,4,(*Stat12)},	   //          ImgTest

	{13,6,6,6,(*Stat13)},	    //��		Univercity
	{14,7,7,7,(*Stat14)},		//          E-Mail
 	{15,8,8,8,(*Stat15)}		//          QQ Numeber 
};

/*-------------------------------------------------------------*/
void MenuOperate(unsigned char key)
{
    switch(key)
	{
	    case  0x30:		       //���ϵļ�
		{
		    KeyFuncIndex=KeyTab[KeyFuncIndex].KeyUpState;
			break; 
		}
		case  0x28:			  //�س���
		{
			KeyFuncIndex=KeyTab[KeyFuncIndex].KeyEnterState;
			break; 
		}
		case  0x18:			  //���µļ�
		{
			KeyFuncIndex=KeyTab[KeyFuncIndex].KeyDownState;
			break; 
		}
		//�˴���Ӱ����������
	}
	//������ִ�а����Ĳ���
	KeyFuncPtr=KeyTab[KeyFuncIndex].CurrentOperate;

	(*KeyFuncPtr)();     //ִ�е�ǰ�İ�������
}	 //*/


