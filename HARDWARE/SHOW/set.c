#include "lcd.h"
#include "w25qxx.h"
#include "showrtad.h"
#include "touch.h"
#include "show.h"
#include "set.h"
#include "GaoYakongzhi.h"
#include "showrtad.h"
#include "text.h"




void set(u8 *dav,u8 *dan){

	LCD_Fill(0,0,319,479,WHITE);
	Show_Str(10,40,200,24,"设置高压模块",24,1);
	Show_Str(10,70,200,24,"实时显示采集到的电压及对应的电流",24,1);
	Show_Str(202,70,200,24,"电压及对应的电流",24,1);
	Show_Str(10,100,200,24,"的电流",24,1);
	Show_Str(10,130,200,24,"返回",24,1);
	while(1){
		tp_dev.scan(0);//触摸屏扫描	
		if(tp_dev.y[0]<70&&tp_dev.y[0]>20){
			gaoyakongzhi((u8 *)&dav,(u8 *)&dan);
			
		}
		if(tp_dev.y[0]<130&&tp_dev.y[0]>70){
			showrtad();
			
		}
		if(tp_dev.y[0]<160&&tp_dev.y[0]>130){
			break;
		}
		
	}
	SHOW_Init();

}




