#include "myiicg.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//初始化IIC
void IIC_InitG(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOG, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}
//产生IIC起始信号
void IIC_StartG(void)
{
	SDA_OUTG();     //sda线输出
	IIC_SDAG=1;	  	  
	IIC_SCLG=1;
	delay_us(4);
 	IIC_SDAG=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCLG=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_StopG(void)
{
	SDA_OUTG();//sda线输出
	IIC_SCLG=0;
	IIC_SDAG=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCLG=1; 
	IIC_SDAG=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_AckG(void)
{
	u8 ucErrTime=0;
	SDA_ING();      //SDA设置为输入  
	IIC_SDAG=1;delay_us(1);	   
	IIC_SCLG=1;delay_us(1);	 
	while(READ_SDAG)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_StopG();
			return 1;
		}
	}
	IIC_SCLG=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_AckG(void)
{
	IIC_SCLG=0;
	SDA_OUTG();
	IIC_SDAG=0;
	delay_us(2);
	IIC_SCLG=1;
	delay_us(2);
	IIC_SCLG=0;
}
//不产生ACK应答		    
void IIC_NAckG(void)
{
	IIC_SCLG=0;
	SDA_OUTG();
	IIC_SDAG=1;
	delay_us(2);
	IIC_SCLG=1;
	delay_us(2);
	IIC_SCLG=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_ByteG(u8 txd)
{                        
    u8 t;   
	SDA_OUTG(); 	    
    IIC_SCLG=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDAG=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCLG=1;
		delay_us(2); 
		IIC_SCLG=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_ByteG(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_ING();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCLG=0; 
        delay_us(2);
		IIC_SCLG=1;
        receive<<=1;
        if(READ_SDAG)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAckG();//发送nACK
    else
        IIC_AckG(); //发送ACK   
    return receive;
}



























