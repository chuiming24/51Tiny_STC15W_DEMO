#include <config.h>
#include <key.h>

uchar keyPress = 0;
bit key_re;
uchar keyValue = 0;

uchar read_keyboard(void)
{
    static unsigned char col;
    
	P2 = 0xf0; 

    if(P2 != 0xf0) //有按键按下
        keyPress++;
	else
		keyPress = 0;  //抖动
    
    if(keyPress == 3)
    {
		return 1;
		keyPress = 0;
		key_re = 1;
		
		if((P2 & 0x80) == 0)	col = 1;
		if((P2 & 0x40) == 0)	col = 2;
		if((P2 & 0x20) == 0)	col = 3;
		if((P2 & 0x10) == 0)	col = 4;
        
        P2 = 0x0F;

		if((P2&0x01) == 0)	keyValue = (col-1);
		if((P2&0x02) == 0)	keyValue = (col+3);
		if((P2&0x04) == 0)	keyValue = (col+7);
		if((P2&0x08) == 0)	keyValue = (col+11);
    }
    
	//连续三次检测到按键被按下，并且该按键已经释放
	P2 = 0x0f;
	
    if(((key_re == 1) && (P2 == 0x0f)))
    {
        key_re = 0;
        return keyValue;
    }
    
    return 0xff;  //无按键按下或被按下的按键未被释放 
}