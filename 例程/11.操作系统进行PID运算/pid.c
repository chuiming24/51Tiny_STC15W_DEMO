#include <config.h>
#include <pid.h>

float M2PID_SetPoint;
float M2PID_SumError;
float M2PID_LastError;

uint PID_M2_PosLocCalc(float NextPoint)
{
	register float  iError,dError;	
	float M2PID_Proportion=80,M2PID_Integral=0.01,M2PID_Derivative=5;//130,0.012,10

	iError = M2PID_SetPoint - NextPoint;     
	M2PID_SumError += iError;				  
	if(M2PID_SumError > 800.0)				
		M2PID_SumError = 800.0;
	else if(M2PID_SumError < -800.0)
		M2PID_SumError = -800.0;	
	dError = iError - M2PID_LastError; 			// ¦Ì¡À?¡ã?¡é¡¤?
	M2PID_LastError = iError;
	
	return(uint)(  M2PID_Proportion * iError           	// ¡À¨¨¨¤y??
          		    + M2PID_Integral   * M2PID_SumError 		// ?y¡¤???
          		    + M2PID_Derivative * dError);
}