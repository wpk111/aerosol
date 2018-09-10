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
  ���ߣwwpk
************************************************/


//Ҫд�뵽STM32 FLASH���ַ�������
u16 TEXT_Buffer[2000];
u16 Draw_point[320];
u8 TEXT_Buffer1[2000];
u8 TEXT_Buffer2[2000];

#define SIZE sizeof(TEXT_Buffer)		//���鳤��
#define FLASH_SAVE_ADDR  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)

 int main(void)
 {	 
	float v1=0;
	u16 i=0,k=0,t=0;
	u8 temperature;  	    
	u8 humidity; 
	u8 count;
	u8 dav=51,dan=0;//AD��ѹ�Ͷ�Ӧ�İ�λ��
	u16 vp=2000,vn=1000;
 	 
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
	LCD_Init();		 //��ʼ��LCD  
	Adc_Init();
	Dac1_Init();
	font_init();
	tp_dev.init(); //������������ʼ��
  SHOW_Init();
	 							   	
	while(1)
	{
			
		tp_dev.scan(0);//������ɨ��
		TOUCH_key_v(&vp,&vn);//���������
			
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height){
				if(tp_dev.x[0]>80&&tp_dev.x[0]<140&&tp_dev.y[0]>440){/*��Ӧ��������*/
				set(&dav,&dan);
				}
			
		
				if(tp_dev.x[0]>270&&tp_dev.y[0]>440&&k==2000)	{ //��������
					LCD_Fill(0,170,239,190,WHITE);//�������    
					LCD_ShowString(30,170,200,16,16,"Start Write FLASH....");
					STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
					LCD_ShowString(30,170,200,16,16,"FLASH Save Finished!");//��ʾ�������
					drawxy((u16*)TEXT_Buffer);
				 }
			
			
			
				if(tp_dev.x[0]>190&&tp_dev.x[0]<270&&tp_dev.y[0]>440&&k==2000){//���ڴ�������
					for(t=0;t<k;t++){			 
						TEXT_Buffer2[t]=TEXT_Buffer[t];
						USART_SendData(USART1, TEXT_Buffer2[t]);//�򴮿�1�������ݣ���8λ
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						LCD_ShowNum(100,300,t,4,16);	
					}
					for(t=0;t<k;t++){
						TEXT_Buffer1[t]=TEXT_Buffer[t]>>8;
						USART_SendData(USART1, TEXT_Buffer1[t]);//�򴮿�1��������,��8λ
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						LCD_ShowNum(140,300,t,4,16);	
					}
				/*USART_SendData(USART1, TEXT_Buffer1[1]);//�򴮿�1��������,��8λ
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
				Show_Str(0,300,200,24,"�������",24,1);
				*/
			}/*��Ӧ���䰴��*/
			
			
			
				if(tp_dev.x[0]<40&&tp_dev.y[0]>440){/*����ADCת�����ɼ�����*/
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
					Show_Str(30,320,200,16,"�ɼ����ĵ�ѹ��",16,1);
					LCD_ShowxNum(160,320,v1,4,16,0);//��ʾ��100��ת���ĵ�ѹ����λ����
					Show_Str(200,320,200,16,"mV",16,1);
					LCD_ShowxNum(200,340,TEXT_Buffer[100],4,16,0 );//��ʾ��100��ADת����ADֵ
				 }/*��Ӧ��ʼ��ť*/
	 }
			
	 
	 
			i++;
			delay_ms(10);  
			if(i==20)
			{
				LED0=!LED0;//��ʾϵͳ��������	
				i=0;
			}	
		
				delay_ms(20);							  
				//DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
			//	LCD_ShowNum(30+40,360,temperature,2,16);	//��ʾ�¶�	   		   
			//	LCD_ShowNum(110+40,360,humidity,2,16);		//��ʾʪ��	

			
			
		} 
}


