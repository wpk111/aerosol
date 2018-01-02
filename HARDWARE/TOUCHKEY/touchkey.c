#include "lcd.h"
#include "text.h"
#include "delay.h"




TOUCH_key_v(u16 vp,u16 vn);
    {

    	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			
     {if(tp_dev.x[0]<100&&tp_dev.x[0]>60&&tp_dev.y[0]<310)
	      {
					LCD_Fill(70,270,100,290,WHITE);
					delay_ms(200);
			  	 LCD_Fill(70,270,100,290,LIGHTBLUE);
	      
	         Show_Str(0,270,200,24,"    +   ",24,1);
				
				   vp=+100;
			     LCD_ShowxNum(30,250,vp/1000,1,16,0);
	         LCD_ShowxNum(30+12,250,vp/10-(vol/1000)*100,2,16,0);
	      }
				
				
				
				
				if(tp_dev.x[0]<140&&tp_dev.x[0]>100&&tp_dev.y[0]<310)
					
	     {
				 LCD_ShowxNum(80,250,vol/1000,1,16,0);
      	
				 LCD_ShowxNum(90,250,vol/10-(vol/1000)*100,2,16,0);
	    	}
			}			
		}
		
			
			
			