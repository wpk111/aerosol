#include "lcd.h"
#include "adc.h"
#include "delay.h"
#include "w25qxx.h"
#include "showrtad.h"
#include "touch.h"
#include "show.h"
#include "text.h"

void showrtad(){
	u32 adv=0;
	showrtadinit();
	while(1){
		tp_dev.scan(0);//触摸屏扫描		
	  adv=(u32)Get_Adc(1);
	  adv=adv*3300/4095;
	  LCD_ShowxNum(50,90,adv,6,24,0);
		if(adv>=1060){
		LCD_ShowxNum(50,120,adv-1060,6,24,0);
		}
		else 	LCD_ShowxNum(50,120,1060-adv,6,24,0);
	  
	  delay_ms(200);
		if(tp_dev.x[0]<319&&tp_dev.x[0]>250&&tp_dev.y[0]<479&&tp_dev.y[0]>440){
			break;
		}
	}
	LCD_Fill(0,0,319,479,WHITE);
	Show_Str(10,40,200,24,"设置高压模块",24,1);
	Show_Str(10,70,200,24,"实时显示采集到的电压及对应的电流",24,1);
	Show_Str(202,70,200,24,"电压及对应的电流",24,1);
	Show_Str(10,100,200,24,"的电流",24,1);
	Show_Str(10,130,200,24,"返回",24,1);

}


void showrtadinit(){
	LCD_Fill(0,0,319,479,WHITE);
  Show_Str(10,10,200,24,"实时显示采集到的电压及对应的电流",24,1);
	Show_Str(202,10,200,24,"电压及对应的电流",24,1);
	Show_Str(10,40,200,24,"的电流",24,1);
	Show_Str(130,90,200,24,"mV",24,1);
	Show_Str(130,120,200,24,"pA",24,1);
	
	Show_Str(270,450,200,24,"返回",24,1);
}




