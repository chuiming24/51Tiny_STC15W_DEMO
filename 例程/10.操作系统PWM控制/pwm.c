#include <config.h>
#include <pwm.h>
sfr P_SW1       = 0xA2;             //���蹦���л��Ĵ���1

void pwmInit(){
	
    ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=0
    P_SW1 = ACC;                    //(P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2)

    CCON = 0;                       //��ʼ��PCA���ƼĴ���
                                    //PCA��ʱ��ֹͣ
                                    //���CF��־
                                    //���ģ���жϱ�־
    CL = 0;                         //��λPCA�Ĵ���
    CH = 0;
    CMOD = 0x02;                    //����PCAʱ��Դ
                                    //��ֹPCA��ʱ������ж�
    PCA_PWM0 = 0x00;                //PCAģ��0������8λPWM
    CCAP0H = CCAP0L = 0x20;         //PWM0��ռ�ձ�Ϊ87.5% ((100H-20H)/100H)
    CCAPM0 = 0x42;                  //PCAģ��0Ϊ8λPWMģʽ

    PCA_PWM1 = 0x40;                //PCAģ��1������7λPWM
    CCAP1H = CCAP1L = 0x20;         //PWM1��ռ�ձ�Ϊ75% ((80H-20H)/80H)
    CCAPM1 = 0x42;                  //PCAģ��1Ϊ7λPWMģʽ


    CR = 1;                         //PCA��ʱ����ʼ����
    
}

void setPwmOne(uchar i){
	CCAP0H = CCAP0L = i;
}
void setPwmTwo(uchar i){
	CCAP1H = CCAP1L = i;
}

