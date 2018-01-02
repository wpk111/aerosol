#include "lcd.h"
#include "text.h"




SHOW_Init()
{
		LCD_Fill(0,0,319,479,WHITE);
  POINT_COLOR=BLUE;
	Show_Str(70,20,200,24,"气溶胶检测系统",24,0);
 	POINT_COLOR=LIGHTGREEN;		 //设置字体为
	
	
	LCD_Fill(0,440,50,480,BROWN);
	LCD_Fill(270,440,380,480, BROWN);
	Show_Str(0,450,200,24,"开始",24,1);
	Show_Str(270,450,200,24,"保存",24,1);
	Show_Str(200-10,450,200,24,"传输",24,1);
	Show_Str(80,450,200,24,"设置",24,1);
	
	LCD_Fill(70,270,100,290,BROWN);
	LCD_Fill(110,270,140,290,BROWN);
	Show_Str(0,270,200,24,"高压： +  - ",24,1);
	LCD_Fill(220,270,260,290, BROWN);
	LCD_Fill(270,270,310,290, BROWN);
	Show_Str(160,270,200,24,"低压：+   - ",24,1);
	
	
	
	Show_Str(30,190,200,16,"粒径:  ",16,1);	 
  Show_Str(130,190,200,16,"浓度:  ",16,1);	 
  LCD_ShowString(39,250,200,16,16,".  V  .  V");
  Show_Str(30,230,200,16,"输出方波高低电压",16,1);

	Show_Str(30,400,200,16,"可采样2k次，采样周期20us",16,1);	
  Show_Str(30,360,200,16,"温度:  ℃",16,1);	 
 	Show_Str(110,360,200,16,"湿度:  %",16,1);


}


