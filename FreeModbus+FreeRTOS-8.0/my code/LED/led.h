#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x_rcc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

#define LED0_ON()	GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define LED0_OFF()	GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define LED1_ON()	GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define LED1_OFF()	GPIO_ResetBits(GPIOD,GPIO_Pin_2)

void LED_Init(void);//��ʼ��

		 				    
#endif
