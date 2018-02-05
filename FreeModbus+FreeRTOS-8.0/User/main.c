#include "includes.h"
/*****************��������*************/
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
    while(1)
    {
         LED0_ON();
       	/* LED��˸ */
         vTaskDelay(100);
         LED0_OFF();
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
