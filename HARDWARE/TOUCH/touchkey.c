#include "lcd.h"
#include "text.h"
#include "delay.h"
#include "text.h"
#include "lcd.h"
#include "touch.h"



void TOUCH_key_v(u16 *vp,u16 * vn)
{

   if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
	 {
		 
		 
		 if(tp_dev.x[0]>280&&tp_dev.y[0]>440&&!(tp_dev.x[0]==0xffff))	
				{LCD_Fill(270,440,320,480,WHITE);
				delay_ms(200);
				LCD_Fill(270,440,320,480,LBBLUE);
				Show_Str(270,450,200,24,"±£´æ",24,1);
				}
	
			if(tp_dev.x[0]<40&&tp_dev.y[0]>440)
				{			
				LCD_Fill(0,440,50,480,WHITE);
				delay_ms(200);
				LCD_Fill(0,440,50,480,LBBLUE);
				Show_Str(0,450,200,24,"¿ªÊ¼",24,1);		
				}
			
			
			 if(tp_dev.x[0]<100&&tp_dev.x[0]>60&&tp_dev.y[0]<290&&tp_dev.y[0]>270)
	      {
					LCD_Fill(70,270,100,290,WHITE);
					delay_ms(200);
			  	LCD_Fill(70,270,100,290,LBBLUE);
	        Show_Str(0,270,200,24,"       +   ",24,1);				
					*vp=*vp+100;
				  LCD_ShowxNum(30,250,*vp/1000,1,16,0);
				  LCD_ShowxNum(30+12,250,*vp/10-(*vp/1000)*100,2,16,0);
	      }
			if(tp_dev.x[0]<140&&tp_dev.x[0]>100&&tp_dev.y[0]<290&&tp_dev.y[0]>270)					
						{ LCD_Fill(110,270,140,290,WHITE);
							delay_ms(200);
							LCD_Fill(110,270,140,290,LBBLUE);					
							Show_Str(0,270,200,24,"          -   ",24,1);
							*vp=*vp-100;
							LCD_ShowxNum(30,250,*vp/1000,1,16,0);
							LCD_ShowxNum(30+12,250,*vp/10-(*vp/1000)*100,2,16,0);					 
						}
						
						
				if(tp_dev.x[0]<270&&tp_dev.x[0]>220&&tp_dev.y[0]<290&&tp_dev.y[0]>270)
	      {
					LCD_Fill(220,270,260,290,WHITE);
					delay_ms(200);
			  	LCD_Fill(220,270,260,290,LBBLUE);
	        Show_Str(235,270,200,24,"+",24,1);
				  *vn=*vn+100;
			    LCD_ShowxNum(80,250,*vn/1000,1,16,0);						
					LCD_ShowxNum(90,250,*vn/10-(*vn/1000)*100,2,16,0);
	      }
				if(tp_dev.x[0]<320&&tp_dev.x[0]>270&&tp_dev.y[0]<290&&tp_dev.y[0]>270)					
						{  LCD_Fill(270,270,315,290,WHITE);
							 delay_ms(200);
							 LCD_Fill(270,270,315,290,LBBLUE);					
						   Show_Str(290,270,200,24,"-",24,1);						
							 *vn=*vn-100;
							 LCD_ShowxNum(80,250,*vn/1000,1,16,0);
							 LCD_ShowxNum(90,250,*vn/10-(*vn/1000)*100,2,16,0);
						}
			}		

}

