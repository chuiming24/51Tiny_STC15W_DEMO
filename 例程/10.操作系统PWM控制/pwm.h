#ifndef __PWM_H_
#define __PWM_H_

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5

void pwmInit();
void setPwmOne(uchar i);
void setPwmTwo(uchar i);

#endif