#include <config.h>
#include <table.h>
#include <12864.h>
#define MENULEVEL 2 //��ǰ�˵������ 
#define OPTIONMETE 20 //��ǰѡ�����������һ���ر���ѡ�� 
//#define SIZE sizeof(Address_buf) 
//������������������������- 
// 
// �˵��ṹ���� 
// 
//������������������������- 

void DIS12864M ();
void SetALineReverse(unsigned char input);
struct Option{ 
unsigned char KeyLevel; //�˵�ѡ�������˵���� 
unsigned char EnterIndex; //ѡ����������� 
unsigned char CancelIndex; //ѡ���˳������� 
unsigned char KeyWord[16]; //�˵�ѡ��������������  
}; 
//������������������������- 
// 
// ����˵�ѡ��壬����һ���ṹ���� 
// �洢�ڱ���������ʡ�ڴ�RAM 
// ���ܵĽ�������Ӧ����OPTIONMETE 
// ��FunctionAction(void)������caseѡ�� 
// ��Ӧ�����������Ӧ�Ĺ��ܺ����� 
//������������������������- 
struct Option sOption[OPTIONMETE] = { 
{0,OPTIONMETE-1,0,"���ñ�������"}, //0 

{0,OPTIONMETE-1,0,"���ñ�����ʱ"}, //1 //һ���˵� 
{0,OPTIONMETE-1,0,"����ʱ��ʱ��"}, //2 
{0,OPTIONMETE-1,0,"�������뿪��"}, //3 
{0,6,0,"ϵͳ�汾"}, //4 
{0,OPTIONMETE-1,0,"�˳��˵�"}, //5
{1,OPTIONMETE-1,3,"****Ӳ��****"},           //6        
{1,OPTIONMETE-1,3,"GSDC_V1.5"},               //7      
{1,OPTIONMETE-1,3,"****���****"},           //8  
      
{1,OPTIONMETE-1,3,"GUI:"},                    //9//��ϵͳ�汾��ѡ������˵�
{1,OPTIONMETE-1,3,"Worm_V0.95"},             //10         
{1,OPTIONMETE-1,3,"Program:"},                //11         
{1,OPTIONMETE-1,3,"GSDC_Program"},           //12        
{1,OPTIONMETE-1,3,"V1.6.1"},                  //13         
{1,OPTIONMETE-1,3,"****����****"},           //14       
{1,OPTIONMETE-1,3," TCP�ն��豸"},           //15         
{1,OPTIONMETE-1,3,"�ͷ��绰��"},             //16      
{1,OPTIONMETE-1,3,"          "},             //17        
{1,0,0,"����"},             //18 

{0,0,0,""}                                    //19//���⣬�޲������� �����б��Ƿ���빦�ܺ���
}; 
//�������������������������C 
// 
// �˵���������� 
// 
//�������������������������C 
unsigned char Level[MENULEVEL][3] = {//ÿ�����Ӧ ��ʼ�����š����������š�ѡ����Ŀ 
										{0,5,6}, 
										{6,18,13}, 
									}; 


//���²����޸�
unsigned char FirstLineDisIndex = 0; //��Ļ��һ����ʾ�������� 
unsigned char SelectLine = 1; //��ǰѡ����� 
unsigned char SelectIndex = 0; //��ǰѡ���ж�Ӧ�������� 
unsigned char LastIndex = 0; //���빦�ܺ���ǰ�������ţ��жϾ��幦��ʹ�� 
/*�˲���Ϊ�˵���Ԥ���岿��Ӧ�����ļ����ͷ*/ 

//��������������������������- 
// 
// �жϵ�ǰ�����Ƿ��Ǳ���һ��ܺ��� 
// ����ԭ�Σ�u8 MenuLevelStart (void); 
// û�в���������Bit��־���ǵ�һ���1�����Ƿ���0 
// ���÷�ʽ��u8 MenuLevelStart (void); 
// 
//��������������������������- 
uchar MenuLevelStart (void) //�жϵ�ǰ�����Ƿ�Ϊ��ǰ���һ��ѡ�� 
{ 
	unsigned char i = MENULEVEL; 
	do 
	{ 
		i--; 
		if(SelectIndex == Level[i][0])
			return 1; 
	}while(i);
	 
	return 0; 
} 
//��������������������������- 
// 
// �жϵ�ǰ�����Ƿ��Ǳ����һ��ܺ��� 
// ����ԭ�Σ�u8 MenuLevelEnd (void); 
// û�в���������Bit��־�������һ���1�����Ƿ���0 
// ���÷�ʽ��u8 MenuLevelEnd (void); 
// 
//��������������������������- 
uchar MenuLevelEnd (void) 
{ 
	unsigned char i = MENULEVEL; 
	do 
	{ 
		i--; 
		if(SelectIndex == Level[i][1])
			return 1; 
	}while(i); 

	return 0; 
} 
//��������������������������- 
// 
// �˵�����һ��� 
// ����ԭ�Σ�void MenuUpOneOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuUpOneOption (void); 
// 
//��������������������������- 
void MenuUpOneOption (void) 
{ 
	if(MenuLevelStart ()) //�����ǰΪ����һ�� 
	{ 
		if(Level[sOption[SelectIndex].KeyLevel][2]>=4) //���ұ���ѡ����Ŀ���ڵ���4�� 
		{ 
			FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][1]-3; 
			//��һ����ʾ������Ϊ���������� 
			SelectIndex = Level[sOption[SelectIndex].KeyLevel][1]; //ѡ������Ϊ�����һ�� 
			SelectLine = 4; //���ѡ����Ϊ������ 
			DIS12864M (); //ˢ����Ļ��ʾ 
		} 
		else //���ѡ����Ŀ���������ĸ� 
		{ 
		//��û����
			SelectIndex = Level[sOption[SelectIndex].KeyLevel][1]; //ѡ������Ϊ��ǰ�����һ�� 
			SelectLine = Level[sOption[SelectIndex].KeyLevel][2]; //��ʾ�б���Ŀ(���һ��) 
			DIS12864M (); //ˢ����Ļ��ʾ 
		} 
	} 
	else //�����ǰ���ǿ�ʼ���� 
	{ 
		if(SelectLine==1) //�����Ѿ�����Ļ���ϱ�һ�� 
		{ 
			FirstLineDisIndex--;//��ʾ�������� 
			SelectIndex--; //ѡ�������Լ� 
			SelectLine = 1; //ѡ���л��ǵ�һ�� 
			DIS12864M (); //ˢ����Ļ 
		} 
		else //������ǵ�һ�� 
		{ 
			SelectLine--;//ѡ�����Լ� 
			SelectIndex--;//ѡ�������Լ� 
			DIS12864M (); //ˢ����Ļ��ʾ 
		} 
	} 
} 
//��������������������������- 
// 
// �˵�����һ��� 
// ����ԭ�Σ�void MenuDownOneOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuDownOneOption (void); 
// 
//��������������������������- 
void MenuDownOneOption (void) 
{ 
	if(MenuLevelEnd ()) //�����ǰ�Ǳ����һ������ 
	{ 
		FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][0];
		//��һ����ʾ����Ϊ����һ��ѡ�� 
		SelectIndex = Level[sOption[SelectIndex].KeyLevel][0]; 
		//ѡ������Ϊ����һ��ѡ������ 
		SelectLine = 1; //ѡ����Ϊ��һ�� 
		DIS12864M (); //ˢ����ʾ 
	} 
	else //��������������� 
	{ 
		if(SelectLine!=4) //�����ǰ������Ļ����� 
		{ 
			SelectIndex++; //ѡ�������Լ� 
			SelectLine++; //ѡ�������� 
			SetALineReverse(SelectLine); //ˢ��ѡ���� 
			DIS12864M (); //ˢ����ʾ 
		} 
		else //�������Ļ����� 
		{ 
			FirstLineDisIndex++; //��һ����ʾ���� 
			SelectIndex++; //ѡ�������Լ� 
			DIS12864M(); //ˢ����ʾ 
		} 
	} 
}

void shut_down(void) //�˵����˳�ϵͳ��ѡ��Ĺ���ʵ�� 
{ 
	FirstLineDisIndex = 0; //��Ļ��һ����ʾ�������� 
	SelectLine = 1; //��ǰѡ����� 
	SelectIndex = 0; //��ǰѡ���ж�Ӧ�������� 
	LastIndex = 0; //���빦�ܺ���ǰ�������ţ��жϾ��幦��ʹ�� 
//	down = 1; 
}

//��������������������������- 
// 
// ���幦��ɢת���� 
// ����ԭ�Σ�void FunctionAction 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void FunctionAction (void); 
// 
//��������������������������- 
void FunctionAction (void) //////////////////////////////// 
{ 
//	switch(LastIndex) //���ݽ���ǰ�������жϾ��庯�� 
//	{ 
//		case 5:shut_down(); break; //�˳��˵���������
//	
//	    case 0:Arm_SEN_set(); break;          //��������������         
//	    case 1:Arm_Delay_set(); break;         //������ʱ����     
//	    case 2:Time_set(); break;             //ʱ�����ù�������    
//	    case 3:Password_switch_set(); break;     //����У�鿪��
//	
//	    default:shut_down();break;             //���û�о����������ʾû���������
//	}
} 
//��������������������������- 
// 
// ����ĳ��ܺ��� 
// ����ԭ�Σ�void MenuEnterOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuEnterOption (void); 
// 
//��������������������������- 
void MenuEnterOption (void) 
{ 
	if(SelectIndex != OPTIONMETE-1) //�����ǰ�������ǹ���ѡ������ ///////////////////////////////////////////////////////////// 
	{ 	
		LastIndex = SelectIndex; //��ǽ���ǰ�������ţ��Ա��жϾ��幦�ܣ� 
		SelectIndex = sOption[SelectIndex].EnterIndex; 
		//����ѡ������Ϊ֮ǰ�����Ŷ�Ӧ�������� 
		if(SelectIndex != OPTIONMETE-1) //�����ǰ�������ǹ���ѡ������ ///////////////////////////////////////////////////////////// 
		{ 
			FirstLineDisIndex = SelectIndex;
			//��һ����ʾΪ�������һ�� 
			SelectLine = 1; //�趨��һ��Ϊѡ���� 
			DIS12864M (); //ˢ�²˵� 
		} 
		else{
			write_com(0x30); //����Һ����ָͨ��ģʽ 
			write_com(0x01); //���� 		 
			Lcd_str(0,1,sOption[LastIndex].KeyWord);
			Lcd_str(2,0,"�˹�����δʵ��!!");
			//FunctionAction (); //����ǹ���ѡ������빦�ܷ�֧�жϺ���
		}
	} 
} 
//��������������������������- 
// 
// �˵��˳����ܺ��� 
// ����ԭ�Σ�void MenuCancelOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuCancelOption (void); 
// 
//��������������������������- 
void MenuCancelOption (void) 
{ 
	if(SelectIndex != OPTIONMETE-1) //������Ǵӹ��ܷ��� 
		SelectIndex = sOption[SelectIndex].CancelIndex; //ѡ������Ϊѡ������� 
	else //����Ǵӹ��ܷ��� 
		SelectIndex = LastIndex; //�������ڽ���ǰ�������� 
	if(Level[sOption[SelectIndex].KeyLevel][2]>=4) //������ر�ѡ����Ŀ����4�� 
	{ 
		if(SelectIndex > Level[sOption[SelectIndex].KeyLevel][1]-3) 
		//���ݷ���ѡ��ȷ����ʾ���� 
		{ 
			FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][1]-3; 
			SelectLine = 4-(Level[sOption[SelectIndex].KeyLevel][1]-SelectIndex); 
			DIS12864M (); //ˢ����ʾ 
		} 
		else //һ����ʾ��ʽ 
		{ 
			FirstLineDisIndex = SelectIndex; //��һ����ʾ���� 
			SelectLine = 1; //ѡ���һ�� 
			DIS12864M (); //ˢ�²˵� 
		} 
	} 
	else //������ر�ѡ����Ŀ����4�� 
	{ 
		FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][0]; 
		//��һ����ʾ����Ϊ����һ�� 
		//ѡ���б�־Ϊ��ǰѡ��������Ӧ�� 
		DIS12864M (); //ˢ�²˵� 
	} 
} 

//��������������������������- 
// 
// ˢ�²˵����ܺ��� 
// ����ԭ�Σ�void DIS12864M (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void DIS12864M (void); 
// 
//��������������������������- 
void DIS12864M (void) 
{ 
	unsigned char LineMete = Level[sOption[SelectIndex].KeyLevel][2]; //ѭ����,��ʾ����
//	LineMete 
	write_com(0x30); //����Һ����ָͨ��ģʽ 
	write_com(0x01); //���� 
	SetALineReverse(SelectLine); //������跴�� 
	do //�ֱ���ʾ���в˵��� 
	{ 
		Lcd_str(0,1,sOption[FirstLineDisIndex].KeyWord);
		LineMete--; 
		if(LineMete == 0) break;
		
		Lcd_str(1,1,sOption[FirstLineDisIndex+1].KeyWord);
		LineMete--; 
		if(LineMete == 0) break;
		
		Lcd_str(2,1,sOption[FirstLineDisIndex+2].KeyWord);
		LineMete--; 
		if(LineMete == 0) break;
		
		Lcd_str(3,1,sOption[FirstLineDisIndex+3].KeyWord);
	}while(0);
	SetALineReverse(SelectLine);           //������跴�� 
}

void SetALineReverse(uchar input){
	Lcd_str(input-1,0,">>");
}