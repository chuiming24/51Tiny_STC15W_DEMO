#include <config.h>
#include <12864.h>

uchar xdata tableData[100] = {0};
uchar tableData_uper = 0;
uchar tableData_downer = 0;

void setData(uchar input){
	if((tableData_uper + 1 ) % 100 == tableData_downer){
		tableData_downer = (tableData_downer + 1)%100;
		tableData[tableData_uper++] = input;
		tableData_uper %=100;	
	}else{
		tableData[tableData_uper++] = input;
		tableData_uper%=100;
	}
}

void tableInit(){
	uchar i;
	for(i = 5; i < 56; i++){
		 Lcd_PutPixel(7, i, 1);
	}
	for(i = 7; i < 120; i++){
		 Lcd_PutPixel(i, 56, 1);
	}
}

void setTable(uchar input){
//	uchar i;
//	for(i = 0; i < 100; i++){
//		Lcd_PutPixel_Sp((9+i), (50-tableData[(tableDat_uper + i)% 100]+6), 1);	
//	}
	static uchar i;
	
	Lcd_PutPixel((8+i), (64-tableData[tableData_uper]-9), 0); 	
	Lcd_PutPixel((8+i), (64-input-9), 1);
	setData(input);	
	i++;
	if(i == 100){
		i = 0;
	}
}