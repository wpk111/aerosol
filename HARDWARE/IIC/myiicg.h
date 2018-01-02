#ifndef __MY_H_G
#define __MY_H_G
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO方向设置
 
#define SDA_ING()  {GPIOG->CRL&=0X0FFFFFFF;GPIOG->CRL|=(u32)8<<28;}
#define SDA_OUTG() {GPIOG->CRL&=0X0FFFFFFF;GPIOG->CRL|=(u32)3<<28;}

//IO操作函数	 
#define IIC_SCLG    PGout(6) //SCL
#define IIC_SDAG    PGout(7) //SDA	 
#define READ_SDAG   PGin(7)  //输入SDA 

//IIC所有操作函数
void IIC_InitG(void);                //初始化IIC的IO口				 
void IIC_StartG(void);				//发送IIC开始信号
void IIC_StopG(void);	  			//发送IIC停止信号
void IIC_Send_ByteG(u8 txd);			//IIC发送一个字节
u8 IIC_Read_ByteG(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_AckG(void); 				//IIC等待ACK信号
void IIC_AckG(void);					//IIC发送ACK信号
void IIC_NAckG(void);				//IIC不发送ACK信号

void IIC_Write_One_ByteG(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_ByteG(u8 daddr,u8 addr);	  
#endif
















