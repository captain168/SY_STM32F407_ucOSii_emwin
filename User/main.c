/****************************************Copyright (c)****************************************************
**                                      
**                                 淘      宝：shan-yan.taobao.com
**                                 技术交流群：15935762
**								   Q        Q: 895838470
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The ucOSII+Emwin application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              nongxiaoming
** Created date:            2011-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             shanyan
** Modified date:           2012-10-19
** Version:                 v2.0
** Descriptions:            
**
*********************************************************************************************************/
/* ------------------------------------------包含的头文件-----------------------------------------------*/
#include "gui.h"
#include "GUIDEMO.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "glcd.h"
#include "ucos_ii.h"
#include "app_cfg.h"
#include "bsp.h"


static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK App_Task1Stk[APP_TASK_1_STK_SIZE];

static  void App_TaskCreate(void);

static  void  App_TaskStart(void *p_arg);
static  void  App_Task1(void *p_arg);


/*************************************************************************************
  * 函数名称：main()
  * 参数    ：void
  * 返回值  ：void
  * 描述    ：程序主入口main函数
  *************************************************************************************/
int main(void)
{  
    INT8U  os_err;
    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */
    os_err = OSTaskCreate((void (*)(void *)) App_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_START_PRIO);
#if (OS_TASK_NAME_SIZE >= 11)
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
#endif
    
    OSStart();
    return (0);
}


static  void  App_TaskStart (void *p_arg)
{	 
    (void)p_arg;                                               /* Initialize BSP functions.                            */
    OS_CPU_SysTickInit();                                       /* Initialize the SysTick.                              */
     BSP_Init(); 
#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity.                              */
#endif

	/* 在此可创建事件 */

	/* 在此可创建其他任务 */
    //App_TaskCreate();	
    LED_GPIO_Conf();
    while (1) 
	{   
     	LED1(On);
 		OSTimeDly(300);
 		LED1(Off);
 		OSTimeDly(300);
		MainTask();
    }
}

//创建新任务
static  void App_TaskCreate(void)
{
    INT8U  os_err;

    os_err = OSTaskCreate((void (*)(void *)) App_Task1,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&App_Task1Stk[APP_TASK_1_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_1_PRIO);
	  
}

static  void  App_Task1(void *p_arg)
{
	(void)p_arg;
	 LED_GPIO_Conf();
	GUI_Init();
	GUI_SetBkColor(GUI_RED);
	GUI_SetColor(GUI_BLUE);
	GUI_Clear();
	while(1)
	{
     	LED0(On);
		OSTimeDly(500);
		LED0(Off);
		OSTimeDly(500);
		MainTask();
	}	
}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

