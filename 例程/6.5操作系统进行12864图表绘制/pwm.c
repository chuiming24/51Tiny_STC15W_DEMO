#include <config.h>
#include <pwm.h>
sfr P_SW1       = 0xA2;             //外设功能切换寄存器1

void pwmInit(){
	
    ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=0
    P_SW1 = ACC;                    //(P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2)

    CCON = 0;                       //初始化PCA控制寄存器
                                    //PCA定时器停止
                                    //清除CF标志
                                    //清除模块中断标志
    CL = 0;                         //复位PCA寄存器
    CH = 0;
    CMOD = 0x02;                    //设置PCA时钟源
                                    //禁止PCA定时器溢出中断
    PCA_PWM0 = 0x00;                //PCA模块0工作于8位PWM
    CCAP0H = CCAP0L = 0x20;         //PWM0的占空比为87.5% ((100H-20H)/100H)
    CCAPM0 = 0x42;                  //PCA模块0为8位PWM模式

    PCA_PWM1 = 0x40;                //PCA模块1工作于7位PWM
    CCAP1H = CCAP1L = 0x20;         //PWM1的占空比为75% ((80H-20H)/80H)
    CCAPM1 = 0x42;                  //PCA模块1为7位PWM模式


    CR = 1;                         //PCA定时器开始工作
    
}

void setPwmOne(uchar i){
	CCAP0H = CCAP0L = i;
}
void setPwmTwo(uchar i){
	CCAP1H = CCAP1L = i;
}

