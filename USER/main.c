#include "led.h"
#include "set.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"
#include "adc.h"
#include "dht11.h"
#include "text.h"
#include "w25qxx.h"
#include "dac.h"
#include "touch.h"
#include "show.h"
#include "touchkey.h"
#include "drawpoint.h"
#include "myiicg.h"
#include "GaoYakongzhi.h"


 
/************************************************
  作者wpk
************************************************/


//要写入到STM32 FLASH的字符串数组
u16 TEXT_Buffer[2000];
u16 Draw_point[320];
u8 TEXT_Buffer1[2000];
u8 TEXT_Buffer2[2000];

#define SIZE sizeof(TEXT_Buffer)		//数组长度
#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

 int main(void)
 {	 
	float v1=0;
	u16 i=0,k=0,t=0;
	u8 temperature;  	    
	u8 humidity; 
	u8 count;
	u8 dav=51,dan=0;//AD电压和对应的八位数
	u16 vp=2000,vn=1000;
 	 
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
	LCD_Init();		 //初始化LCD  
	Adc_Init();
	Dac1_Init();
	font_init();
	tp_dev.init(); //触摸屏触摸初始化
  SHOW_Init();
	 							   	
	while(1)
	{
			
		tp_dev.scan(0);//触摸屏扫描
		TOUCH_key_v(&vp,&vn);//处理触摸结果
			
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height){
				if(tp_dev.x[0]>80&&tp_dev.x[0]<140&&tp_dev.y[0]>440){/*响应按键设置*/
				set(&dav,&dan);
				}
			
		
				if(tp_dev.x[0]>270&&tp_dev.y[0]>440&&k==2000)	{ //保存数据
					LCD_Fill(0,170,239,190,WHITE);//清除半屏    
					LCD_ShowString(30,170,200,16,16,"Start Write FLASH....");
					STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
					LCD_ShowString(30,170,200,16,16,"FLASH Save Finished!");//提示传送完成
					drawxy((u16*)TEXT_Buffer);
				 }
			
			
			
				if(tp_dev.x[0]>190&&tp_dev.x[0]<270&&tp_dev.y[0]>440&&k==2000){//串口传送数据
					for(t=0;t<k;t++){			 
						TEXT_Buffer2[t]=TEXT_Buffer[t];
						USART_SendData(USART1, TEXT_Buffer2[t]);//向串口1发送数据，低8位
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
						LCD_ShowNum(100,300,t,4,16);	
					}
					for(t=0;t<k;t++){
						TEXT_Buffer1[t]=TEXT_Buffer[t]>>8;
						USART_SendData(USART1, TEXT_Buffer1[t]);//向串口1发送数据,高8位
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
						LCD_ShowNum(140,300,t,4,16);	
					}
				/*USART_SendData(USART1, TEXT_Buffer1[1]);//向串口1发送数据,高8位
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				Show_Str(0,300,200,24,"传输完成",24,1);
				*/
			}/*响应传输按键*/
			
			
			
				if(tp_dev.x[0]<40&&tp_dev.y[0]>440){/*进行ADC转换，采集数据*/
					LCD_ShowString(30,170,200,16,16,"Start ADC,waiting.... ");
					k=0;			
					while(k<2000)
					 { Dac1_Set_Vol(vp);
						 for(count=0;count<250;count++,k++)
							{TEXT_Buffer[k]=Get_Adc(1);
							delay_ms(20);
							}
						 Dac1_Set_Vol(vn);
						 for(count=0;count<250;count++,k++)
							{TEXT_Buffer[k ]=Get_Adc(1);
							 delay_ms(20);
							}
					 }
					LCD_ShowString(30,170,200,16,16,"ADC Finished         ");
					v1=TEXT_Buffer[100];
					v1=v1*33/4095*100;
					Show_Str(30,320,200,16,"采集到的电压：",16,1);
					LCD_ShowxNum(160,320,v1,4,16,0);//显示第100个转换的电压，单位毫伏
					Show_Str(200,320,200,16,"mV",16,1);
					LCD_ShowxNum(200,340,TEXT_Buffer[100],4,16,0 );//显示第100个AD转换的AD值
				 }/*响应开始按钮*/
	 }
			
	 
	 
			i++;
			delay_ms(10);  
			if(i==20)
			{
				LED0=!LED0;//提示系统正在运行	
				i=0;
			}	
		
				delay_ms(20);							  
				//DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值					    
			//	LCD_ShowNum(30+40,360,temperature,2,16);	//显示温度	   		   
			//	LCD_ShowNum(110+40,360,humidity,2,16);		//显示湿度	

			
			
		} 
}


