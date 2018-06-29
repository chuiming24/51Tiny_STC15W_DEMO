#ifndef _TABLE_H_
#define _TABLE_H_
#define MENU_SIZE 40             //菜单长度

//定义类型 


//
//

void DIS12864M (void) ;

//—————————————- 
// 
// 进入某项功能函数 
// 函数原形：void MenuEnterOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuEnterOption (void); 
// 
//—————————————- 
void MenuEnterOption (void) ;
//—————————————- 
// 
// 菜单退出功能函数 
// 函数原形：void MenuCancelOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuCancelOption (void); 
// 
//—————————————- 
void MenuCancelOption (void) ;
void shut_down(void); //菜单“退出系统”选项的功能实现

//—————————————- 
// 
// 菜单下移一项函数 
// 函数原形：void MenuDownOneOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuDownOneOption (void); 
// 
//—————————————- 
void MenuDownOneOption (void) ;

//—————————————- 
// 
// 菜单上移一项函数 
// 函数原形：void MenuUpOneOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuUpOneOption (void); 
// 
//—————————————- 
void MenuUpOneOption (void) ; 
#endif