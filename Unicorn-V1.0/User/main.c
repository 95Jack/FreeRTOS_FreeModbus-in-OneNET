#include "includes.h"
/*****************��������*************/
/*<<<<<<< HEAD:Unicorn-V1.0/User/main.c*/
static void vTaskFLASH(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
/*****************��������**************/
static TaskHandle_t xHandleTaskFLASH = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
/**
  * @brief  ��ѭ��
  * @param  None
  * @retval None
  */
int main(void)
{         
          LCD_Init();
          KEY_Init();
          LED_Init();
          Beep_Init();
         //__set_PRIMASK(1); 
        //��ʼ�� RTUģʽ �ӻ���ַΪ1 USART1 9600 ��У��
          eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
        //����FreeModbus 
          eMBEnable();
        // ��������
        AppTaskCreate();
                
        /* �������ȣ���ʼִ������ */
        vTaskStartScheduler();
        /* 
        ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п��������ڶ�ʱ��������߿��������
        heap�ռ䲻����ɴ���ʧ�ܣ���Ҫ�Ӵ�FreeRTOSConfig.h�ļ��ж����heap��С��
        #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
        */
                while(1);
}
/*
*********************************************************************************************************
*	�� �� ��: vTaskFLASH
*	����˵��: �ӿ���Ϣ������������FLASH
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 1  (��ֵԽС���ȼ�Խ�ͣ������uCOS�෴)
*********************************************************************************************************
*/
//Ҫд�뵽STM32 FLASH���ַ�������
#define FLASH_SAVE_ADDR  0X08020000   
#define SIZE sizeof(FreeSize)	 	//���鳤��
u8 FreeSize[]={"STM32 ModbusTEST"};  
u8 datatemp[SIZE];   	
//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
static void vTaskFLASH(void *pvParameters)
{
   
    while(1)
    {
       //STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
      //STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)FreeSize,SIZE);
      vTaskDelay(100);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskLED
*	����˵��: LED��˸	
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
    /* LED��˸ */
    while(1)
    {

    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskMsgPro
*	����˵��: ��Ϣ��������������LED��˸	
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 3  
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
    while(1)
    { 
        eMBPoll(); 
        vTaskDelay(300);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTaskStart
*	����˵��: ��������Ҳ����������ȼ�������������LED��˸
*	��    ��: pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ��: 4  
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
        KEY_red();
        LED_Poll();
        vTaskDelay(400);
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
    xTaskCreate( vTaskFLASH,   	/* ������  */
                 "vTaskFLASH",     	/* ������    */
                 512,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 1,                 	/* �������ȼ�*/
                 &xHandleTaskFLASH );  /* ������  */
	
	
	xTaskCreate( vTaskLED,    		/* ������  */
                 "vTaskLED",  		/* ������    */
                 512,         		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,        		/* �������  */
                 2,           		/* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
	
	xTaskCreate( vTaskMsgPro,     		/* ������  */
                 "vTaskMsgPro",   		/* ������    */
                 512,             		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,           		/* �������  */
                 3,               		/* �������ȼ�*/
                 &xHandleTaskMsgPro );  /* ������  */
	
	
	xTaskCreate( vTaskStart,     		/* ������  */
                 "vTaskStart",   		/* ������    */
                 512,            		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,           		/* �������  */
                 4,              		/* �������ȼ�*/
                 &xHandleTaskStart );   /* ������  */
}
//
//#include "includes.h"
///*****************函数声明*************/
//static void vTaskFLASH(void *pvParameters);
//static void vTaskLED(void *pvParameters);
//static void vTaskMsgPro(void *pvParameters);
//static void vTaskStart(void *pvParameters);
//static void AppTaskCreate (void);
///*****************变量声明**************/
//static TaskHandle_t xHandleTaskFLASH = NULL;
//static TaskHandle_t xHandleTaskLED = NULL;
//static TaskHandle_t xHandleTaskMsgPro = NULL;
//static TaskHandle_t xHandleTaskStart = NULL;
///**
//  * @brief  主循环
//  * @param  None
//  * @retval None
//  */
//int main(void)
//{         
//          LCD_Init();
//          KEY_Init();
//          LED_Init();
//        //__set_PRIMASK(1); 
//        //初始化 RTU模式 从机地址为1 USART1 9600 无校验
//          eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
//        //启动FreeModbus 
//          eMBEnable();
//        // 创建任务
//        AppTaskCreate();
//                
//        /* 启动调度，开始执行任务 */
//        vTaskStartScheduler();
//        /* 
//        如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
//        heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
//        #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
//        */
//                while(1);
//}
///*
//*********************************************************************************************************
//*	函 数 名: vTaskFLASH
//*	功能说明: 接口消息处理，这里用作FLASH
//*	形    参: pvParameters 是在创建该任务时传递的形参
//*	返 回 值: 无
//*   优 先 级: 1  (数值越小优先级越低，这个跟uCOS相反)
//*********************************************************************************************************
//*/
////要写入到STM32 FLASH的字符串数组
//#define FLASH_SAVE_ADDR  0X08020000   
//#define SIZE sizeof(FreeSize)	 	//数组长度
//u8 FreeSize[]={"STM32 ModbusTEST"};  
//u8 datatemp[SIZE];   	
////设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
//static void vTaskFLASH(void *pvParameters)
//{
//   
//    while(1)
//    {
//       //STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
//      //STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)FreeSize,SIZE);
//      vTaskDelay(100);
//    }
//}
//
///*
//*********************************************************************************************************
//*	函 数 名: vTaskLED
//*	功能说明: LED闪烁	
//*	形    参: pvParameters 是在创建该任务时传递的形参
//*	返 回 值: 无
//*   优 先 级: 2  
//*********************************************************************************************************
//*/
//static void vTaskLED(void *pvParameters)
//{
//    /* LED闪烁 */
//    while(1)
//    {
//         LED0_ON();
//         vTaskDelay(100);
//         LED0_OFF();
//    }
//}
//
///*
//*********************************************************************************************************
//*	函 数 名: vTaskMsgPro
//*	功能说明: 信息处理，这里是用作LED闪烁	
//*	形    参: pvParameters 是在创建该任务时传递的形参
//*	返 回 值: 无
//*   优 先 级: 3  
//*********************************************************************************************************
//*/
//static void vTaskMsgPro(void *pvParameters)
//{
//    while(1)
//    {
//        
//        eMBPoll(); 
//        vTaskDelay(300);
//    }
//}
//
///*
//*********************************************************************************************************
//*	函 数 名: vTaskStart
//*	功能说明: 启动任务，也就是最高优先级任务，这里用作LED闪烁
//*	形    参: pvParameters 是在创建该任务时传递的形参
//*	返 回 值: 无
//*   优 先 级: 4  
//*********************************************************************************************************
//*/
//static void vTaskStart(void *pvParameters)
//{
//    while(1)
//    {
//        KEY_red();
//        LED_Poll();
//        vTaskDelay(400);
//    }
//}
//
///*
//*********************************************************************************************************
//*	函 数 名: AppTaskCreate
//*	功能说明: 创建应用任务
//*	形    参：无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//static void AppTaskCreate (void)
//{
//    xTaskCreate( vTaskFLASH,   	/* 任务函数  */
//                 "vTaskFLASH",     	/* 任务名    */
//                 512,               	/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,              	/* 任务参数  */
//                 1,                 	/* 任务优先级*/
//                 &xHandleTaskFLASH );  /* 任务句柄  */
//	
//	
//	xTaskCreate( vTaskLED,    		/* 任务函数  */
//                 "vTaskLED",  		/* 任务名    */
//                 512,         		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,        		/* 任务参数  */
//                 2,           		/* 任务优先级*/
//                 &xHandleTaskLED ); /* 任务句柄  */
//	
//	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
//                 "vTaskMsgPro",   		/* 任务名    */
//                 512,             		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,           		/* 任务参数  */
//                 3,               		/* 任务优先级*/
//                 &xHandleTaskMsgPro );  /* 任务句柄  */
//	
//	
//	xTaskCreate( vTaskStart,     		/* 任务函数  */
//                 "vTaskStart",   		/* 任务名    */
//                 512,            		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,           		/* 任务参数  */
//                 4,              		/* 任务优先级*/
//                 &xHandleTaskStart );   /* 任务句柄  */
//}
//>>>>>>> 9fd0c1753aa48fb6da98c1c2c579a419d710233d:FreeModbus+FreeRTOS-8.0/User/main.c
