#include "usart.h"


/*******************************************************************************************************************************
 * ��������USART1_Conf()
 * ��������
 *����ֵ����
 * ���ܣ�����USART1������ʼ��
********************************************************************************************************************************/																		
void USART1_Conf(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;                                          //����GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;                                        //����USART��ʼ���ṹ��
		/*����USART1��Ӧ��ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);                          //ʹ��GPIOA��AHB1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                        //ʹ��USART1��APB2ʱ��
	 /*���ø��ùܽ�TXD(PA9)��RXD(PA10)���ӵ�USART1*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);						  //����PA9�������ӵ�USART1
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);				      //����PA10�������ӵ�USART1

	/*����USART1�ķ��͹ܽ�TXD(PA9)Ϊ�����������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;                                       //���ó�ʼ��GPIOΪPIN9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                               //����GPIO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    //����GPIOģʽΪ����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;								  //����GPIO�������Ϊ�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;						          //����GPIOΪ������������
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                         //��ʼ��GPIOA��PIN9
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;                                      //���ó�ʼ��GPIOΪPIN10
	/*����USART1�Ľ��չܽ�RXD(PA10)Ϊ��������*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                    //����GPIO��ģʽΪ����ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                         //��ʼ��GPIOA��PIN10
   
	/*����USART1��ģʽ*/
    USART_InitStructure.USART_BaudRate=115200;                                    //����USART�Ĳ�����Ϊ115200
    USART_InitStructure.USART_Parity=USART_Parity_No;                             //����USART��У��λΪNone
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                     //����USART������λΪ8bit
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                          //����USART��ֹͣλΪ1
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //ʧ��Ӳ��������
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;                   //����USART��ģʽΪ���ͽ���ģʽ
    USART_Init(USART1,&USART_InitStructure);                                      //��ʼ��USART1		  	
    USART_Cmd(USART1,ENABLE);                                                     //ʹ��USART1
	//USART_SmartCardCmd(USART1,DISABLE);
}


/********************************************************************************************************************************
*��������USART_SendString()
* ������USART_TypeDef* USARTx ��Ҫ���͵��Ĵ��ڵ�ָ�룬u8 *str ָ���͵��ַ�����ָ��
* ����ֵ��void
* ���ܣ���ĳ�����ڷ���һ���ַ���
*********************************************************************************************************************************/
void USART_SendString(USART_TypeDef* USARTx,u8 *str)
{
  while(*str)
  {
  	 USART_SendData(USARTx,*str);													   //��*str��USARTx���ͳ�ȥ
	  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)				       //�ȴ��������
    {
      																		           //str�ĵ�ַ����1������һ���ַ�
    }
	str++;	
  }
}


/********************************************************************************************************************************
*��������fputc()
* ������int ch��FILE *f
* ����ֵ��int
* ���ܣ����¶���stdio.h�е�fputc()������ʹprintf()�����USART1
*********************************************************************************************************************************/
int fputc(int ch,FILE *f)
{
  USART_SendData(USART1,(u8)ch);	                                                   //��ch��USART1���ͳ�ȥ
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)				       //�ȴ��������
  {
  }											  
  return ch;																	   //���� ch
}																		           








