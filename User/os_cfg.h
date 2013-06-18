/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                  uC/OS-II Configuration File for V2.8x
*
*                               (c) Copyright 2005-2009, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
* File    : OS_CFG.H
* By      : Jean J. Labrosse
* Version : V2.91
*
* LICENSING TERMS:
* ---------------
*   uC/OS-II is provided in source form for FREE evaluation, for educational use or for peaceful research.
* If you plan on using  uC/OS-II  in a commercial product you need to contact Micri�m to properly license
* its use in your product. We provide ALL the source code for your convenience and to help you experience
* uC/OS-II.   The fact that the  source is provided does  NOT  mean that you can use it without  paying a
* licensing fee.
*********************************************************************************************************
*/

#ifndef OS_CFG_H
#define OS_CFG_H


 /* ---------------------- �ۺ����� ----------------------- *//* ---------------------- MISCELLANEOUS ----------------------- */
#define OS_APP_HOOKS_EN           0u   /* Ӧ�ýӿ� *//* Application-defined hooks are called from the uC/OS-II hooks */
#define OS_ARG_CHK_EN             1u   /* ������� *//* Enable (1) or Disable (0) argument checking                  */
#define OS_CPU_HOOKS_EN           1u   /* �������ӿ��ļ� *//* uC/OS-II hooks are found in the processor port files         */

#define OS_DEBUG_EN               0u   /* ���Ա��� *//* Enable(1) debug variables                                    */

#define OS_EVENT_MULTI_EN         1u   /* ʹ�� OSEventPendMulti() *//* Include code for OSEventPendMulti()                          */
#define OS_EVENT_NAME_EN          1u   /* Enable names for Sem, Mutex, Mbox and Q                      */

#define OS_LOWEST_PRIO           63u   /* ������ȼ�*//* Defines the lowest priority that can be assigned ...         */
                                       /* ... MUST NEVER be higher than 254!                           */

#define OS_MAX_EVENTS            10u   /* ���Ӧ���¼����ƿ����� *//* Max. number of event control blocks in your application      */
#define OS_MAX_FLAGS              5u   /* ���Ӧ���¼���־���� *//* Max. number of Event Flag Groups    in your application      */
#define OS_MAX_MEM_PART           5u   /* ���洢���������� *//* Max. number of memory partitions                             */
#define OS_MAX_QS                 4u   /* ���Ӧ�ö��п��ƿ����� *//* Max. number of queue control blocks in your application      */
#define OS_MAX_TASKS             20u   /* ���Ӧ����������, һ��>=2 *//* Max. number of tasks in your application, MUST be >= 2       */

#define OS_SCHED_LOCK_EN          1u   /* ʹ�� OSSchedLock() �� OSSchedUnlock() *//* Include code for OSSchedLock() and OSSchedUnlock()           */

#define OS_TICK_STEP_EN           1u   /* ʹ�ܲ����� *//* Enable tick stepping feature for uC/OS-View                  */
#define OS_TICKS_PER_SEC       1000u   /* �趨һ����ĵ����� *//* Set the number of ticks in one second                        */


/* --------------------- �����ջ��С ---------------------- *//* --------------------- TASK STACK SIZE ---------------------- */
#define OS_TASK_TMR_STK_SIZE    128u   /* ��ʱ�������ջ��С (��� OS_STK ʹ��) *//* Timer      task stack size (# of OS_STK wide entries)        */
#define OS_TASK_STAT_STK_SIZE   128u   /* ͳ�������ջ��С (��� OS_STK ʹ��) *//* Statistics task stack size (# of OS_STK wide entries)        */
#define OS_TASK_IDLE_STK_SIZE   128u   /* ���������ջ��С (��� OS_STK ʹ��) *//* Idle       task stack size (# of OS_STK wide entries)        */


/* --------------------- ������� ---------------------- *//* --------------------- TASK MANAGEMENT ---------------------- */
#define OS_TASK_CHANGE_PRIO_EN    1u   /* ʹ�� OSTaskChangePrio() *//*     Include code for OSTaskChangePrio()                      */
#define OS_TASK_CREATE_EN         1u   /* ʹ�� OSTaskCreate() *//*     Include code for OSTaskCreate()                          */
#define OS_TASK_CREATE_EXT_EN     1u   /* ʹ�� OSTaskCreateExt() *//*     Include code for OSTaskCreateExt()                       */
#define OS_TASK_DEL_EN            1u   /* ʹ�� OSTaskDel() *//*     Include code for OSTaskDel()                             */
#define OS_TASK_NAME_EN           1u   /*     Enable task names                                        */
#define OS_TASK_PROFILE_EN        1u   /* OS_TCB �İ������� *//*     Include variables in OS_TCB for profiling                */
#define OS_TASK_QUERY_EN          1u   /* ʹ�� OSTaskQuery() *//*     Include code for OSTaskQuery()                           */
#define OS_TASK_REG_TBL_SIZE      1u   /*     Size of task variables array (#of INT32U entries)        */
#define OS_TASK_STAT_EN           1u   /* ʹ��(1)���ֹ(0)ͳ������ *//*     Enable (1) or Disable(0) the statistics task             */
#define OS_TASK_STAT_STK_CHK_EN   1u   /* ��ͳ�������ջ�������  *//*     Check task stacks from statistic task                    */
#define OS_TASK_SUSPEND_EN        1u   /* ʹ�� OSTaskSuspend() �� OSTaskResume() *//*     Include code for OSTaskSuspend() and OSTaskResume()      */
#define OS_TASK_SW_HOOK_EN        1u   /* ʹ�� OSTaskSwHook() *//*     Include code for OSTaskSwHook()                          */


/* ----------------------- �¼���־ ------------------------ *//* ----------------------- EVENT FLAGS ------------------------ */
#define OS_FLAG_EN                1u   /* ʹ��(1)���ֹ(0)�¼���־ *//* Enable (1) or Disable (0) code generation for EVENT FLAGS    */
#define OS_FLAG_ACCEPT_EN         1u   /* ʹ�� OSFlagAccept() *//*     Include code for OSFlagAccept()                          */
#define OS_FLAG_DEL_EN            1u   /* ʹ�� OSFlagDel() *//*     Include code for OSFlagDel()                             */
#define OS_FLAG_NAME_EN           1u   /*     Enable names for event flag group                        */
#define OS_FLAG_QUERY_EN          1u   /* ʹ�� OSFlagQuery() *//*     Include code for OSFlagQuery()                           */
#define OS_FLAG_WAIT_CLR_EN       1u   /* �ȴ�����¼���־ *//* Include code for Wait on Clear EVENT FLAGS                   */
#define OS_FLAGS_NBITS           16u   /* OS_FLAGS ��������(8,16��32λ) *//* Size in #bits of OS_FLAGS data type (8, 16 or 32)            */


/* -------------------- ��Ϣ���� --------------------- *//* -------------------- MESSAGE MAILBOXES --------------------- */
#define OS_MBOX_EN                1u   /* ʹ��(1)���ֹ(0)��Ϣ���� *//* Enable (1) or Disable (0) code generation for MAILBOXES      */
#define OS_MBOX_ACCEPT_EN         1u   /* ʹ�� OSMboxAccept() *//*     Include code for OSMboxAccept()                          */
#define OS_MBOX_DEL_EN            1u   /* ʹ�� OSMboxDel() *//*     Include code for OSMboxDel()                             */
#define OS_MBOX_PEND_ABORT_EN     1u   /* ʹ�� OSMboxPendAbort() *//*     Include code for OSMboxPendAbort()                       */
#define OS_MBOX_POST_EN           1u   /* ʹ�� OSMboxPost() *//*     Include code for OSMboxPost()                            */
#define OS_MBOX_POST_OPT_EN       1u   /* ʹ�� OSMboxPostOpt() *//*     Include code for OSMboxPostOpt()                         */
#define OS_MBOX_QUERY_EN          1u   /* ʹ�� OSMboxQuery() *//*     Include code for OSMboxQuery()                           */


/* --------------------- �洢���� -------------------- *//* --------------------- MEMORY MANAGEMENT -------------------- */
#define OS_MEM_EN                 1u   /* ʹ��(1)���ֹ(0)�洢���� *//* Enable (1) or Disable (0) code generation for MEMORY MANAGER */
#define OS_MEM_NAME_EN            1u   /*     Enable memory partition names                            */
#define OS_MEM_QUERY_EN           1u   /* ʹ�� OSMemQuery() *//*     Include code for OSMemQuery()                            */


/* ---------------- �����ź��� --------------- *//* ---------------- MUTUAL EXCLUSION SEMAPHORES --------------- */
#define OS_MUTEX_EN               1u   /* ʹ��(1)���ֹ(0)�����ź��� *//* Enable (1) or Disable (0) code generation for MUTEX          */
#define OS_MUTEX_ACCEPT_EN        1u   /* ʹ�� OSMutexAccept() *//*     Include code for OSMutexAccept()                         */
#define OS_MUTEX_DEL_EN           1u   /* ʹ�� OSMutexDel() *//*     Include code for OSMutexDel()                            */
#define OS_MUTEX_QUERY_EN         1u   /* ʹ�� OSMutexQuery() *//*     Include code for OSMutexQuery()                          */


/* ---------------------- ��Ϣ���� ---------------------- *//* ---------------------- MESSAGE QUEUES ---------------------- */
#define OS_Q_EN                   1u   /* ʹ��(1)���ֹ(0)��Ϣ���� *//* Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_Q_ACCEPT_EN            1u   /* ʹ�� OSQAccept() *//*     Include code for OSQAccept()                             */
#define OS_Q_DEL_EN               1u   /* ʹ�� OSQDel() *//*     Include code for OSQDel()                                */
#define OS_Q_FLUSH_EN             1u   /* ʹ�� OSQFlush() *//*     Include code for OSQFlush()                              */
#define OS_Q_PEND_ABORT_EN        1u   /* ʹ�� OSQPendAbort() *//*     Include code for OSQPendAbort()                          */
#define OS_Q_POST_EN              1u   /* ʹ�� OSQPost() *//*     Include code for OSQPost()                               */
#define OS_Q_POST_FRONT_EN        1u   /* ʹ�� OSQPostFront() *//*     Include code for OSQPostFront()                          */
#define OS_Q_POST_OPT_EN          1u   /* ʹ�� OSQPostOpt() *//*     Include code for OSQPostOpt()                            */
#define OS_Q_QUERY_EN             1u   /* ʹ�� OSQQuery() *//*     Include code for OSQQuery()                              */


/* ------------------------ �ź��� ------------------------ *//* ------------------------ SEMAPHORES ------------------------ */
#define OS_SEM_EN                 1u   /* ʹ��(1)���ֹ(0)�ź��� *//* Enable (1) or Disable (0) code generation for SEMAPHORES     */
#define OS_SEM_ACCEPT_EN          1u   /* ʹ�� OSSemAccept() *//*    Include code for OSSemAccept()                            */
#define OS_SEM_DEL_EN             1u   /* ʹ�� OSSemDel() *//*    Include code for OSSemDel()                               */
#define OS_SEM_PEND_ABORT_EN      1u   /* ʹ�� OSSemPendAbort() *//*    Include code for OSSemPendAbort()                         */
#define OS_SEM_QUERY_EN           1u   /* ʹ�� OSSemQuery() *//*    Include code for OSSemQuery()                             */
#define OS_SEM_SET_EN             1u   /* ʹ�� OSSemSet() *//*    Include code for OSSemSet()                               */


/* --------------------- ʱ����� ---------------------- *//* --------------------- TIME MANAGEMENT ---------------------- */
#define OS_TIME_DLY_HMSM_EN       1u   /* ʹ�� OSTimeDlyHMSM() *//*     Include code for OSTimeDlyHMSM()                         */
#define OS_TIME_DLY_RESUME_EN     1u   /* ʹ�� OSTimeDlyResume() *//*     Include code for OSTimeDlyResume()                       */
#define OS_TIME_GET_SET_EN        1u   /* ʹ�� OSTimeGet() and OSTimeSet() *//*     Include code for OSTimeGet() and OSTimeSet()             */
#define OS_TIME_TICK_HOOK_EN      1u   /* ʹ�� OSTimeTickHook() *//*     Include code for OSTimeTickHook()                        */


/* --------------------- ��ʱ������ --------------------- *//* --------------------- TIMER MANAGEMENT --------------------- */
#define OS_TMR_EN                 1u   /* ʹ��(1)���ֹ(0)��ʱ������ *//* Enable (1) or Disable (0) code generation for TIMERS         */
#define OS_TMR_CFG_MAX           16u   /* ��ʱ�����ֵ *//*     Maximum number of timers                                 */
#define OS_TMR_CFG_NAME_EN        1u   /* ��ʱ�����ִ�С  *//*     Determine timer names                                    */
#define OS_TMR_CFG_WHEEL_SIZE     8u   /* ��ʱ���ִ�С *//*     Size of timer wheel (#Spokes)                            */
#define OS_TMR_CFG_TICKS_PER_SEC 10u   /* ��ʱ���������������ٶ�(Hz) *//*     Rate at which timer management task runs (Hz)            */

#endif
	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
