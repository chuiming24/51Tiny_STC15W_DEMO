#include <config.h>

//菜单的实现
/*-------------------------------------------------------------*/
#define MENU_SIZE 40             //菜单长度

unsigned char KeyFuncIndex=0;    //存放当前的菜单索引
void (*KeyFuncPtr)();            //定义按键功能指针
//定义类型 

typedef struct 
{
   unsigned char KeyStateIndex;   //当前的状态索引号
   unsigned char KeyDownState;    //按下向下键时的状态索引号
   unsigned char KeyUpState;      //按下向上键时的状态索引号
   unsigned char KeyEnterState;   //按下回车键时的状态索引号
   void (*CurrentOperate)();      //当前状态应该执行的功能操作
   char ShowChar[17];
}  StateTab;
//
//


/*-------------------------------------------------------------
   菜单要修改的内容
-------------------------------------------------------------*/
 //数据结构数组
 //记录每一层的第一个数字的数组
//一个记录当前指针的数组
//一个记录列表的函数
StateTab code KeyTab[MENU_SIZE]=
{
//当前，向下，向上，确定
   	{0,1,1,2,   (*Stat0), "111111111111"},    //顶层  当前的状态索引号,按下向下键时的状态索引号,按下向上键时的状态索引号,按下回车键时的状态索引号,当前状态应该执行的功能操作
	{1,0,0,6,   (*Stat1)},	   //顶层

	{2,3,5,10,  (*Stat2)},     //二层
	{3,4,2,11,  (*Stat3)},	   //二层
	{4,5,3,12,  (*Stat4)},	   //二层
	{5,2,4,0,   (*Stat5)},	   //二层

	{6,7,9,13,  (*Stat6)},     //二层
	{7,8,6,14,  (*Stat7)},     //
	{8,9,7,15,  (*Stat8)},   
	{9,6,8,1 ,  (*Stat9)},     //二层

	{10,2,2,2,(*Stat10)},    //三		   LineTest
	{11,3,3,3,(*Stat11)},	   //		   RectTest
	{12,4,4,4,(*Stat12)},	   //          ImgTest

	{13,6,6,6,(*Stat13)},	    //三		Univercity
	{14,7,7,7,(*Stat14)},		//          E-Mail
 	{15,8,8,8,(*Stat15)}		//          QQ Numeber 
};

/*-------------------------------------------------------------*/
void MenuOperate(unsigned char key)
{
    switch(key)
	{
	    case  0x30:		       //向上的键
		{
		    KeyFuncIndex=KeyTab[KeyFuncIndex].KeyUpState;
			break; 
		}
		case  0x28:			  //回车键
		{
			KeyFuncIndex=KeyTab[KeyFuncIndex].KeyEnterState;
			break; 
		}
		case  0x18:			  //向下的键
		{
			KeyFuncIndex=KeyTab[KeyFuncIndex].KeyDownState;
			break; 
		}
		//此处添加按键错误代码
	}
	//下面是执行按键的操作
	KeyFuncPtr=KeyTab[KeyFuncIndex].CurrentOperate;

	(*KeyFuncPtr)();     //执行当前的按键操作
}	 //*/


