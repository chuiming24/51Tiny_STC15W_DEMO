#ifndef _TABLE_H_
#define _TABLE_H_
#define MENU_SIZE 40             //�˵�����

//�������� 


//
//

void DIS12864M (void) ;

//��������������������������- 
// 
// ����ĳ��ܺ��� 
// ����ԭ�Σ�void MenuEnterOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuEnterOption (void); 
// 
//��������������������������- 
void MenuEnterOption (void) ;
//��������������������������- 
// 
// �˵��˳����ܺ��� 
// ����ԭ�Σ�void MenuCancelOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuCancelOption (void); 
// 
//��������������������������- 
void MenuCancelOption (void) ;
void shut_down(void); //�˵����˳�ϵͳ��ѡ��Ĺ���ʵ��

//��������������������������- 
// 
// �˵�����һ��� 
// ����ԭ�Σ�void MenuDownOneOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuDownOneOption (void); 
// 
//��������������������������- 
void MenuDownOneOption (void) ;

//��������������������������- 
// 
// �˵�����һ��� 
// ����ԭ�Σ�void MenuUpOneOption (void); 
// û�в�����û�з���ֵ 
// ���÷�ʽ��void MenuUpOneOption (void); 
// 
//��������������������������- 
void MenuUpOneOption (void) ; 
#endif