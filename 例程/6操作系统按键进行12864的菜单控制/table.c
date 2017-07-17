#include <config.h>
#include <table.h>
#include <12864.h>
#define MENULEVEL 2 //当前菜单表个数 
#define OPTIONMETE 20 //当前选项个数，包括一个特别功能选项 
//#define SIZE sizeof(Address_buf) 
//————————————- 
// 
// 菜单结构定义 
// 
//————————————- 

void DIS12864M ();
void SetALineReverse(unsigned char input);
struct Option{ 
unsigned char KeyLevel; //菜单选项所属菜单表号 
unsigned char EnterIndex; //选项进入索引号 
unsigned char CancelIndex; //选项退出索引号 
unsigned char KeyWord[16]; //菜单选项文字描述数组  
}; 
//————————————- 
// 
// 具体菜单选项定义，定义一个结构数组 
// 存储在编码区，节省内存RAM 
// 功能的进入索引应大于OPTIONMETE 
// 在FunctionAction(void)函数的case选项 
// 中应定义出索引对应的功能函数。 
//————————————- 
struct Option sOption[OPTIONMETE] = { 
{0,OPTIONMETE-1,0,"设置报警界限"}, //0 

{0,OPTIONMETE-1,0,"设置报警延时"}, //1 //一级菜单 
{0,OPTIONMETE-1,0,"设置时钟时间"}, //2 
{0,OPTIONMETE-1,0,"设置密码开关"}, //3 
{0,6,0,"系统版本"}, //4 
{0,OPTIONMETE-1,0,"退出菜单"}, //5
{1,OPTIONMETE-1,3,"****硬件****"},           //6        
{1,OPTIONMETE-1,3,"GSDC_V1.5"},               //7      
{1,OPTIONMETE-1,3,"****软件****"},           //8  
      
{1,OPTIONMETE-1,3,"GUI:"},                    //9//“系统版本”选项二级菜单
{1,OPTIONMETE-1,3,"Worm_V0.95"},             //10         
{1,OPTIONMETE-1,3,"Program:"},                //11         
{1,OPTIONMETE-1,3,"GSDC_Program"},           //12        
{1,OPTIONMETE-1,3,"V1.6.1"},                  //13         
{1,OPTIONMETE-1,3,"****服务****"},           //14       
{1,OPTIONMETE-1,3," TCP终端设备"},           //15         
{1,OPTIONMETE-1,3,"客服电话："},             //16      
{1,OPTIONMETE-1,3,"          "},             //17        
{1,0,0,"返回"},             //18 

{0,0,0,""}                                    //19//特殊，无操作索引 用于判别是否进入功能函数
}; 
//————————————– 
// 
// 菜单表分类数组 
// 
//————————————– 
unsigned char Level[MENULEVEL][3] = {//每层表单对应 开始索引号、结束索引号、选项数目 
										{0,5,6}, 
										{6,18,13}, 
									}; 


//以下不用修改
unsigned char FirstLineDisIndex = 0; //屏幕第一行显示的索引号 
unsigned char SelectLine = 1; //当前选择的行 
unsigned char SelectIndex = 0; //当前选定行对应的索引号 
unsigned char LastIndex = 0; //进入功能函数前的索引号，判断具体功能使用 
/*此部分为菜单的预定义部分应放在文件的最开头*/ 

//—————————————- 
// 
// 判断当前索引是否是表单第一项功能函数 
// 函数原形：u8 MenuLevelStart (void); 
// 没有参数，返回Bit标志，是第一项返回1，不是返回0 
// 调用方式：u8 MenuLevelStart (void); 
// 
//—————————————- 
uchar MenuLevelStart (void) //判断当前索引是否为当前层第一个选项 
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
//—————————————- 
// 
// 判断当前索引是否是表单最后一项功能函数 
// 函数原形：u8 MenuLevelEnd (void); 
// 没有参数，返回Bit标志，是最后一项返回1，不是返回0 
// 调用方式：u8 MenuLevelEnd (void); 
// 
//—————————————- 
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
//—————————————- 
// 
// 菜单上移一项函数 
// 函数原形：void MenuUpOneOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuUpOneOption (void); 
// 
//—————————————- 
void MenuUpOneOption (void) 
{ 
	if(MenuLevelStart ()) //如果当前为表单第一项 
	{ 
		if(Level[sOption[SelectIndex].KeyLevel][2]>=4) //并且表单中选项数目大于等于4个 
		{ 
			FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][1]-3; 
			//第一行显示索引号为倒数第四项 
			SelectIndex = Level[sOption[SelectIndex].KeyLevel][1]; //选择索引为表单最后一项 
			SelectLine = 4; //标记选择行为第四行 
			DIS12864M (); //刷新屏幕显示 
		} 
		else //如果选项数目并不大于四个 
		{ 
		//还没折腾
			SelectIndex = Level[sOption[SelectIndex].KeyLevel][1]; //选择索引为当前表单最后一个 
			SelectLine = Level[sOption[SelectIndex].KeyLevel][2]; //显示行表单数目(最后一个) 
			DIS12864M (); //刷新屏幕显示 
		} 
	} 
	else //如果当前不是开始索引 
	{ 
		if(SelectLine==1) //并且已经在屏幕最上边一行 
		{ 
			FirstLineDisIndex--;//显示索引上移 
			SelectIndex--; //选择索引自减 
			SelectLine = 1; //选择行还是第一行 
			DIS12864M (); //刷新屏幕 
		} 
		else //如果不是第一行 
		{ 
			SelectLine--;//选择行自减 
			SelectIndex--;//选择索引自减 
			DIS12864M (); //刷新屏幕显示 
		} 
	} 
} 
//—————————————- 
// 
// 菜单下移一项函数 
// 函数原形：void MenuDownOneOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuDownOneOption (void); 
// 
//—————————————- 
void MenuDownOneOption (void) 
{ 
	if(MenuLevelEnd ()) //如果当前是表单最后一个索引 
	{ 
		FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][0];
		//第一行显示索引为表单第一个选项 
		SelectIndex = Level[sOption[SelectIndex].KeyLevel][0]; 
		//选择索引为表单第一个选项索引 
		SelectLine = 1; //选择行为第一行 
		DIS12864M (); //刷新显示 
	} 
	else //如果不是最后的索引 
	{ 
		if(SelectLine!=4) //如果当前不是屏幕最底行 
		{ 
			SelectIndex++; //选择索引自加 
			SelectLine++; //选择行下移 
			SetALineReverse(SelectLine); //刷新选择行 
			DIS12864M (); //刷新显示 
		} 
		else //如果是屏幕最低行 
		{ 
			FirstLineDisIndex++; //第一行显示下移 
			SelectIndex++; //选择索引自加 
			DIS12864M(); //刷新显示 
		} 
	} 
}

void shut_down(void) //菜单“退出系统”选项的功能实现 
{ 
	FirstLineDisIndex = 0; //屏幕第一行显示的索引号 
	SelectLine = 1; //当前选择的行 
	SelectIndex = 0; //当前选定行对应的索引号 
	LastIndex = 0; //进入功能函数前的索引号，判断具体功能使用 
//	down = 1; 
}

//—————————————- 
// 
// 具体功能散转函数 
// 函数原形：void FunctionAction 
// 没有参数，没有返回值 
// 调用方式：void FunctionAction (void); 
// 
//—————————————- 
void FunctionAction (void) //////////////////////////////// 
{ 
//	switch(LastIndex) //根据进入前的索引判断具体函数 
//	{ 
//		case 5:shut_down(); break; //退出菜单功能索引
//	
//	    case 0:Arm_SEN_set(); break;          //报警灵敏度设置         
//	    case 1:Arm_Delay_set(); break;         //报警延时设置     
//	    case 2:Time_set(); break;             //时间设置功能索引    
//	    case 3:Password_switch_set(); break;     //密码校验开关
//	
//	    default:shut_down();break;             //如果没有具体操作，显示没有这个功能
//	}
} 
//—————————————- 
// 
// 进入某项功能函数 
// 函数原形：void MenuEnterOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuEnterOption (void); 
// 
//—————————————- 
void MenuEnterOption (void) 
{ 
	if(SelectIndex != OPTIONMETE-1) //如果当前索引不是功能选择索引 ///////////////////////////////////////////////////////////// 
	{ 	
		LastIndex = SelectIndex; //标记进入前的索引号（以便判断具体功能） 
		SelectIndex = sOption[SelectIndex].EnterIndex; 
		//更新选择索引为之前索引号对应进入索引 
		if(SelectIndex != OPTIONMETE-1) //如果当前索引不是功能选择索引 ///////////////////////////////////////////////////////////// 
		{ 
			FirstLineDisIndex = SelectIndex;
			//第一行显示为进入表单第一项 
			SelectLine = 1; //设定第一行为选择行 
			DIS12864M (); //刷新菜单 
		} 
		else{
			write_com(0x30); //进入液晶普通指令模式 
			write_com(0x01); //清屏 		 
			Lcd_str(0,1,sOption[LastIndex].KeyWord);
			Lcd_str(2,0,"此功能尚未实现!!");
			//FunctionAction (); //如果是功能选择项，进入功能分支判断函数
		}
	} 
} 
//—————————————- 
// 
// 菜单退出功能函数 
// 函数原形：void MenuCancelOption (void); 
// 没有参数，没有返回值 
// 调用方式：void MenuCancelOption (void); 
// 
//—————————————- 
void MenuCancelOption (void) 
{ 
	if(SelectIndex != OPTIONMETE-1) //如果不是从功能返回 
		SelectIndex = sOption[SelectIndex].CancelIndex; //选择索引为选项返回索引 
	else //如果是从功能返回 
		SelectIndex = LastIndex; //索引等于进入前保存索引 
	if(Level[sOption[SelectIndex].KeyLevel][2]>=4) //如果返回表单选项数目大于4个 
	{ 
		if(SelectIndex > Level[sOption[SelectIndex].KeyLevel][1]-3) 
		//根据返回选项确定显示首项 
		{ 
			FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][1]-3; 
			SelectLine = 4-(Level[sOption[SelectIndex].KeyLevel][1]-SelectIndex); 
			DIS12864M (); //刷新显示 
		} 
		else //一般显示方式 
		{ 
			FirstLineDisIndex = SelectIndex; //第一行显示索引 
			SelectLine = 1; //选择第一行 
			DIS12864M (); //刷新菜单 
		} 
	} 
	else //如果返回表单选项数目不足4个 
	{ 
		FirstLineDisIndex = Level[sOption[SelectIndex].KeyLevel][0]; 
		//第一行显示索引为表单第一项 
		//选择行标志为当前选择索引对应行 
		DIS12864M (); //刷新菜单 
	} 
} 

//—————————————- 
// 
// 刷新菜单功能函数 
// 函数原形：void DIS12864M (void); 
// 没有参数，没有返回值 
// 调用方式：void DIS12864M (void); 
// 
//—————————————- 
void DIS12864M (void) 
{ 
	unsigned char LineMete = Level[sOption[SelectIndex].KeyLevel][2]; //循环量,显示行数
//	LineMete 
	write_com(0x30); //进入液晶普通指令模式 
	write_com(0x01); //清屏 
	SetALineReverse(SelectLine); //填充所需反白 
	do //分别显示各行菜单项 
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
	SetALineReverse(SelectLine);           //填充所需反白 
}

void SetALineReverse(uchar input){
	Lcd_str(input-1,0,">>");
}