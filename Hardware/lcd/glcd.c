#include "glcd.h"
/*******************Һ����Ӳ������**********************

PD14 -----FSMC_D0  ----D0
PD15 -----FSMC_D1  ----D1
PD0   -----FSMC_D2  ----D2
PD1   -----FSMC_D3  ----D3
PE7    -----FSMC_D4  ---D4
PE8    -----FSMC_D5  ---D5
PE9    -----FSMC_D6  ---D6
PE10  -----FSMC_D7   ----D7
PE11  -----FSMC_D8   ----D8
PE12  -----FSMC_D9   ----D9
PE13  -----FSMC_D10   ----D10
PE14  -----FSMC_D11   ----D11
PE15  -----FSMC_D12   ----D12
PD8   -----FSMC_D13   ----D13
PD9   -----FSMC_D14   ----D14
PD10 -----FSMC_D15   ----D15
PD4   -----FSMC_NOE -----RD
PD5   -----FSMC_NWE ----WR
PD7    -----FSMC_NE1  ----CS
PD11 -----FSMC_A16   ----RS

PB5-------------------LCD_BL

***************************************************************/
/* ѡ��BANK1-NORSRAM1 ���� TFT����ַ��ΧΪ0X60000000~0X63FFFFFF
 * FSMC_A16 ��LCD��DC(�Ĵ���/����ѡ��)��
 * �Ĵ�������ַ = 0X60000000
 * RAM����ַ = 0X60020000 = 0X60000000+2^16*2 = 0X60000000 + 0X20000 = 0X60020000
 * ������Ҫ���ڿ���RS����д�Ĵ���д���ݲ�������Ϊ���ӵ�Һ��RS����A16�ܽţ�����Ҫʹ��ַ��A16Ϊ�ߵ�ƽ����д��ַ��2��16�η�����������ΪҺ����16bit��
 *�����ٳ���2���ó��ĵ�ַ����BANK���ڵĵ�ַ���ɡ���RS��A0������RAM����ַΪbank���ڵ�ַ����2��0�η���2��������8bit������Ҫ����2
 */
#define LCD_RAM   *(vu16*)((u32)0x60020000)  //disp Data ADDR
#define LCD_REG   *(vu16*)((u32)0x60000000)	 //disp Reg  ADDR
  /*Һ����������*/

  /*Һ������ǰ��ɫ�ͱ���ɫ*/
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
/**************************************************************************************************************
 * ��������GPIO_AF_FSMC_Config()
 * ����  ��void
 * ���  ��void
 * ����  ������LCD���ӵ�GPIO�������ӵ�FSMC
 * ����  ���ڲ�����        
 *****************************************************************************************************************/
static void GPIO_AF_FSMC_Config(void)
{
  /*����GPIOD��Ӧ�ĹܽŸ������ӵ�FSMC*/
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);	        //����GPIOD��Pin0�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);			//����GPIOD��Pin1�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);			//����GPIOD��Pin4�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);			//����GPIOD��Pin5�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);			//����GPIOD��Pin7�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);			//����GPIOD��Pin8�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);			//����GPIOD��Pin9�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);		//����GPIOD��Pin10�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);		//����GPIOD��Pin11�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);		//����GPIOD��Pin14�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);		//����GPIOD��Pin15�������ӵ�FSMC
   /*����GPIOE��Ӧ�ĹܽŸ������ӵ�FSMC*/
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);			//����GPIOE��Pin7�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);			//����GPIOE��Pin8�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);			//����GPIOE��Pin9�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);		//����GPIOE��Pin10�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);		//����GPIOE��Pin11�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);		//����GPIOE��Pin12�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);	    //����GPIOE��Pin13�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);		//����GPIOE��Pin14�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);		//����GPIOE��Pin15�������ӵ�FSMC
}
/**************************************************************************************************************
 * ��������LCD_GPIO_Config()
 * ����  ��void
 * ���  ��void
 * ����  ������LCD��GPIO�ܽ���FSMC����
 * ����  ���ڲ�����        
 *****************************************************************************************************************/
static void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;		                                              //����GPIO��ʼ���ṹ��
     
    /* ʹ��FSMC��AHB3ʱ�ӣ�����ע�⣬��ͬоƬ���߻᲻ͬ */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
    
    /* ʹ��GPIOB��GPIOD��GPIOE��AHB1ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE , ENABLE);
   	 /*����Һ�����ı�����ƹܽ�*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;											  //���ùܽ�ģʽΪ���ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										  //���÷�ת�ٶ�Ϊ100Mhz��M4���ǿ찡
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;											  //�����������Ϊ�������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;												  //���ùܽ�ΪPin_5,�����Լ�Һ���ӷ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;										  //������/��������Ϊ��������������		
    GPIO_Init(GPIOB, &GPIO_InitStructure);													  //��ʼ��GPIOB��Pin_5
    		   
    /* ���û���FSMC��Һ������������
	 * Һ���������ߣ�FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10
	 */	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										  //���÷�ת�ٶ�Ϊ100Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;											  //���ùܽ�ģʽΪ����ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);													  //��ʼ��GPIOB��Pin_0��Pin_��Pin_2��
	                                                                    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    /* ���û���FSMC��Һ����������
	 * PD4-FSMC_NOE  :LCD-RD
   * PD5-FSMC_NWE  :LCD-WR
	 * PD7-FSMC_NE1  :LCD-CS
   * PD11-FSMC_A16 :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    GPIO_AF_FSMC_Config();				             //��F407�б��������������������ã����������ӵ�FSMC
    GPIO_SetBits(GPIOB, GPIO_Pin_5);			 
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		  
    GPIO_SetBits(GPIOD, GPIO_Pin_5);		 
    GPIO_SetBits(GPIOD, GPIO_Pin_7);		 
   
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    GPIO_SetBits(GPIOD, GPIO_Pin_6); 	
}

/**************************************************************************************************************
 * ��������LCD_FSMC_Config()
 * ����  ��void
 * ���  ��void
 * ����  ������LCD��FSMC
 * ����  ���ڲ�����        
 *****************************************************************************************************************/
static void LCD_FSMC_Config(void)
{    
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;
	  LCD_GPIO_Config();                                                     //LCD�ܽ�����
  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;                                           //��ַ����ʱ��
  	p.FSMC_AddressHoldTime = 0;                                            //��ַ����ʱ��
  	p.FSMC_DataSetupTime = 9;                                              //���ݽ���ʱ��
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;                                  // ��ģʽA����LCD
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 
}
/**************************************************************************************************************
 * ��������GLCD_WriteReg()
 * ����  ��uint8_t LCD_Reg �Ĵ�����ַ, uint16_t LCD_RegValue �Ĵ�����ֵ
 * ���  ��void
 * ����  ��дLCD�Ĵ�������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /*д�Ĵ�����ַ*/
  LCD_REG = LCD_Reg;
  /*д��Ĵ���ֵ*/
  LCD_RAM = LCD_RegValue;
}
/**************************************************************************************************************
 * ��������LCD_ReadReg()
 * ����  ��uint8_t LCD_Reg ��Ҫ��ȡ�ļĴ�����ַ
 * ���  ��uint16_t �Ĵ�����ֵ
 * ����  ����ȡLCD�Ĵ�����ֵ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
uint16_t GLCD_ReadReg(uint8_t LCD_Reg)
{
  /*д�Ĵ�����ַ*/
  LCD_REG = LCD_Reg;
  /*�����Ĵ���ֵ������*/
  return (LCD_RAM);
}
/**************************************************************************************************************
 * ��������GLCD_WriteRAM_Start()
 * ����  ��void
 * ���  ��void
 * ����  ����ʼдLCD��RAM
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_WriteRAM_Start(void)
{
  LCD_REG = 0x22;
}

/**************************************************************************************************************
 * ��������GLCD_WriteRAM()
 * ����  ��uint16_t RGB_data  16bit��ɫ����
 * ���  ��void
 * ����  ����LCD��RAMд����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_WriteRAM(uint16_t RGB_data)
{
  /*��LCD��RAMд����*/
  LCD_RAM = RGB_data;
}

/**************************************************************************************************************
 * ��������LCD_ReadRAM()
 * ����  ��void
 * ���  ��uint16_t  16bit��ɫֵ
 * ����  ����ȡLCD��RAM����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
uint16_t GLCD_ReadRAM(void)
{ 
	uint16_t dumry;
  LCD_REG = 0x22; /*ѡ��RAM�Ĵ���*/
	dumry=LCD_RAM;   /*�ٶ�*/
  /*��ȡ16bit RAMֵ*/
  return LCD_RAM;
}

/**************************************************************************************************************
 * ��������LCD_DisplayOn()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD����ʾ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DisplayOn(void)
{
  /*����ʾ */
  GLCD_WriteReg(0x07, 0x0173); /*����LCDΪ262Kɫ������ʾ*/
}

/**************************************************************************************************************
 * ��������LCD_DisplayOff()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD�ر���ʾ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DisplayOff(void)
{
  /*�ر���ʾ*/
  GLCD_WriteReg(0x07, 0x0); 
}
/**************************************************************************************************************
 * ��������LCD_Init()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD��ʼ������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_Init(void)
{ 
  	u16 lcdid=0;

   	LCD_FSMC_Config();
	GLCD_WriteReg(0x00,0x0001);
  	delay_nms(5); 
  	lcdid=GLCD_ReadReg(0x00); 
	printf("ID:%d\n",lcdid); 
  	if(lcdid == 0x9320)
  	{
		GLCD_WriteReg(0xE5,0x8000);
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0700);
		GLCD_WriteReg(0x03,0x1030);
		GLCD_WriteReg(0x04,0x0000);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x09,0x0000);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x0B,0x0000);
		GLCD_WriteReg(0x0C,0x0000);
		GLCD_WriteReg(0x0F,0x0000);
		GLCD_WriteReg(0x10,0x0000);
		GLCD_WriteReg(0x11,0x0000);
		GLCD_WriteReg(0x12,0x0000);
		GLCD_WriteReg(0x13,0x0000);
		delay_nms(20);
		GLCD_WriteReg(0x10,0x17B0);
		GLCD_WriteReg(0x11,0x0137);
		delay_nms(5);
		GLCD_WriteReg(0x12,0x0139);
		delay_nms(5);
		GLCD_WriteReg(0x13,0x1d00);
		GLCD_WriteReg(0x29,0x0013);
		delay_nms(5);
		GLCD_WriteReg(0x20,0x0000);
		GLCD_WriteReg(0x21,0x0000);
		GLCD_WriteReg(0x30,0x0006);
		GLCD_WriteReg(0x31,0x0101);
		GLCD_WriteReg(0x32,0x0003);
		GLCD_WriteReg(0x35,0x0106);
		GLCD_WriteReg(0x36,0x0b02);
		GLCD_WriteReg(0x37,0x0302);
		GLCD_WriteReg(0x38,0x0707);
		GLCD_WriteReg(0x39,0x0007);
		GLCD_WriteReg(0x3C,0x0600);
		GLCD_WriteReg(0x3D,0x020b);
		GLCD_WriteReg(0x50,0x0000);
		GLCD_WriteReg(0x51,0x00EF);
		GLCD_WriteReg(0x52,0x0000);
		GLCD_WriteReg(0x53,0x013F);
		GLCD_WriteReg(0x60,0x2700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x6A,0x0000);
		GLCD_WriteReg(0x80,0x0000);
		GLCD_WriteReg(0x81,0x0000);
		GLCD_WriteReg(0x82,0x0000);
		GLCD_WriteReg(0x83,0x0000);
		GLCD_WriteReg(0x84,0x0000);
		GLCD_WriteReg(0x85,0x0000);
		GLCD_WriteReg(0x90,0x0010);
		GLCD_WriteReg(0x92,0x0000);
		GLCD_WriteReg(0x93,0x0003);
		GLCD_WriteReg(0x95,0x0110);
		GLCD_WriteReg(0x97,0x0000);
		GLCD_WriteReg(0x98,0x0000);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x07,0x0173); 
  	}
  	else if(lcdid == 0x9325)
  	{
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0700);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x04,0x0000);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x09,0x0000);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x0C,0x0000);
		GLCD_WriteReg(0x0D,0x0000);
		GLCD_WriteReg(0x0F,0x0000);
		GLCD_WriteReg(0x10,0x0000);
		GLCD_WriteReg(0x11,0x0000);
		GLCD_WriteReg(0x12,0x0000);
		GLCD_WriteReg(0x13,0x0000);
		delay_nms(20);
		GLCD_WriteReg(0x10,0x17B0);
		GLCD_WriteReg(0x11,0x0137);
		delay_nms(5);
		GLCD_WriteReg(0x12,0x0139);
		delay_nms(5);
		GLCD_WriteReg(0x13,0x1d00);
		GLCD_WriteReg(0x29,0x0013);
		delay_nms(5);
		GLCD_WriteReg(0x20,0x0000);
		GLCD_WriteReg(0x21,0x0000);
		GLCD_WriteReg(0x30,0x0007);
		GLCD_WriteReg(0x31,0x0302);
		GLCD_WriteReg(0x32,0x0105);
		GLCD_WriteReg(0x35,0x0206);
		GLCD_WriteReg(0x36,0x0808);
		GLCD_WriteReg(0x37,0x0206);
		GLCD_WriteReg(0x38,0x0504);
		GLCD_WriteReg(0x39,0x0007);
		GLCD_WriteReg(0x3C,0x0105);
		GLCD_WriteReg(0x3D,0x0808);
		GLCD_WriteReg(0x50,0x0000);
		GLCD_WriteReg(0x51,0x00EF);
		GLCD_WriteReg(0x52,0x0000);
		GLCD_WriteReg(0x53,0x013F);
		GLCD_WriteReg(0x60,0xA700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x6A,0x0000);
		GLCD_WriteReg(0x80,0x0000);
		GLCD_WriteReg(0x81,0x0000);
		GLCD_WriteReg(0x82,0x0000);
		GLCD_WriteReg(0x83,0x0000);
		GLCD_WriteReg(0x84,0x0000);
		GLCD_WriteReg(0x85,0x0000);
		GLCD_WriteReg(0x90,0x0010);
		GLCD_WriteReg(0x92,0x0000);
		GLCD_WriteReg(0x93,0x0003);
		GLCD_WriteReg(0x95,0x0110);
		GLCD_WriteReg(0x97,0x0000);
		GLCD_WriteReg(0x98,0x0000);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x07,0x0133);
  	}
  	else if(lcdid==0x4531)
  	{		
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x10,0x0628);
		GLCD_WriteReg(0x12,0x0006);
		GLCD_WriteReg(0x13,0x0A32);
		GLCD_WriteReg(0x11,0x0040);
		GLCD_WriteReg(0x15,0x0050);
		GLCD_WriteReg(0x12,0x0016);
		delay_nms(15);
		GLCD_WriteReg(0x10,0x5660);
		delay_nms(15);
		GLCD_WriteReg(0x13,0x2A4E);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0300);	
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x30,0x0000);
		GLCD_WriteReg(0x31,0x0402);
		GLCD_WriteReg(0x32,0x0106);
		GLCD_WriteReg(0x33,0x0700);
		GLCD_WriteReg(0x34,0x0104);
		GLCD_WriteReg(0x35,0x0301);
		GLCD_WriteReg(0x36,0x0707);
		GLCD_WriteReg(0x37,0x0305);
		GLCD_WriteReg(0x38,0x0208);
		GLCD_WriteReg(0x39,0x0F0B);
		delay_nms(15);
		GLCD_WriteReg(0x41,0x0002);
		GLCD_WriteReg(0x60,0x2700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x90,0x0119);
		GLCD_WriteReg(0x92,0x010A);
		GLCD_WriteReg(0x93,0x0004);
		GLCD_WriteReg(0xA0,0x0100);
		delay_nms(15);
		delay_nms(15);
		GLCD_WriteReg(0x07,0x0133);
		delay_nms(15);
		GLCD_WriteReg(0xA0,0x0000);
		delay_nms(20);
  	} 
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GLCD_Clear(BLUE);
	GLCD_SetMode(4);							 
}
/**************************************************************************************************************
 * ��������LCD_SetMode()
 * ����  ��uint8_t mode ������Ļˢ��ģʽ
 * ���  ��void
 * ����  ������LCDˢ��ģʽ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetMode(uint8_t mode)
{
	switch(mode)//����4(����)��7(����)
	{
		case 1:GLCD_WriteReg(0x03,0x1000);break;//��������:���I
		case 2:GLCD_WriteReg(0x03,0x1008);break;//��������:���I
		case 3:GLCD_WriteReg(0x03,0x1010);break;//��������:���J
		case 4:GLCD_WriteReg(0x03,0x1018);break;//��������:���J
		case 5:GLCD_WriteReg(0x03,0x1020);break;//��������:���L
		case 6:GLCD_WriteReg(0x03,0x1028);break;//��������:���L
		case 7:GLCD_WriteReg(0x03,0x1030);break;//��������:���K
		case 8:GLCD_WriteReg(0x03,0x1038);break;//��������:���K
	}
}
/**************************************************************************************************************
 * ��������LCD_Clear()
 * ����  ��void
 * ���  ��void
 * ����  ��LCD��������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_Clear(uint16_t Color)
{
  uint32_t index = 0;
  
  GLCD_SetCursor(0,319); 
  GLCD_WriteRAM_Start(); /*��ʼдGRAM */
  for(index = 0; index < 76800; index++)
  {
    LCD_RAM = Color;
  }  
}

/**************************************************************************************************************
 * ��������GLCD_SetCursor()
 * ����  ��uint16_t Xpos, uint16_t Ypos �趨����Ļ��Xֵ��Yֵ
 * ���  ��void
 * ����  ��LCD���ù��λ�ú���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
  GLCD_WriteReg(0x20, Ypos);
  GLCD_WriteReg(0x21, 319-Xpos);
}
/**************************************************************************************************************
 * ��������LCD_SetWindow()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width �������㣬��͸�
 * ���  ��void
 * ����  ������ĳ���ض����������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  /*����ˮƽ����X��ʼ����*/
  if(Xpos >= Height)
  {
    GLCD_WriteReg(0x50, (Xpos - Height + 1));
  }
  else
  {
    GLCD_WriteReg(0x50, 0);
  }
  /*����ˮƽ����X��������*/
  GLCD_WriteReg(0x51, Xpos);
  /*������ֱ����Y��ʼ����*/
  if(Ypos >= Width)
  {
    GLCD_WriteReg(0x52, (Ypos - Width + 1));
  }  
  else
  {
    GLCD_WriteReg(0x52, 0);
  }
  /*������ֱ����Y��������*/
  GLCD_WriteReg(0x53, Ypos);
  GLCD_SetCursor(Xpos, Ypos);
}
/**************************************************************************************************************
 * ��������LCD_SetColors()
 * ����  ��_TextColor ǰ��ɫ,_BackColor ����ɫ
 * ���  ��void
 * ����  ������LCD��ǰ��ɫ�ͱ���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}
/**************************************************************************************************************
 * ��������LCD_GetColors()
 * ����  ��*_TextColor ǰ��ɫ��ָ��,*_BackColor ����ɫ��ָ��
 * ���  ��void
 * ����  ����ȡLCD��ǰ��ɫ�ͱ���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}
/**************************************************************************************************************
 * ��������LCD_SetTextColor()
 * ����  ��uint16_t Color ǰ��ɫ
 * ���  ��void
 * ����  ������LCD��ǰ��ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetTextColor(__IO uint16_t Color)
{
  TextColor = Color;
}


/**************************************************************************************************************
 * ��������LCD_SetBackColor()
 * ����  ��uint16_t Color ����ɫ
 * ���  ��void
 * ����  ������LCD�ı���ɫ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_SetBackColor(__IO uint16_t Color)
{
  BackColor = Color;
}


/**************************************************************************************************************
 * ��������GLCD_DrawHLine()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Length ���X��Y���꼰����
 * ���  ��void
 * ����  ����ˮƽ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
  GLCD_SetCursor(Xpos, Ypos);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    for(i = 0; i < Length; i++)
    {
      GLCD_WriteRAM(TextColor);
    }
}
/**************************************************************************************************************
 * ��������GLCD_DrawVLine()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Length ���X��Y���꼰����
 * ���  ��void
 * ����  ������ֱ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
  GLCD_SetCursor(Xpos, Ypos);
    for(i = 0; i < Length; i++)
    {
      GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
      GLCD_WriteRAM(TextColor);
      Ypos++;
      GLCD_SetCursor(Xpos, Ypos);
    }
}
/**************************************************************************************************************
 * ��������LCD_DrawRect()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height �������Ͻǵ�����꼰��͸�
 * ���  ��void
 * ����  �������κ���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  GLCD_DrawHLine(Xpos, Ypos, Width);
  GLCD_DrawHLine(Xpos, Ypos+ Height, Width); 
  GLCD_DrawVLine(Xpos, Ypos, Height);
  GLCD_DrawVLine(Xpos+ Width,Ypos, Height);
}
/**************************************************************************************************************
 * ��������LCD_DrawCircle()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Radius Բ������㼰�뾶
 * ���  ��void
 * ����  ����Բ����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    GLCD_SetCursor(Xpos + CurX, Ypos + CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurX, Ypos - CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurX, Ypos + CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurX, Ypos - CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurY, Ypos + CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurY, Ypos - CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurY, Ypos + CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurY, Ypos - CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}
/**************************************************************************************************************
 * ��������LCD_DrawMonoPict()
 * ����  ��const uint32_t *Pict ��һ��ȫ����ɫ��ȡĤ����
 * ���  ��void
 * ����  ����һ����ɫ��ȫ��ͼƬ����
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawMonoPict(const uint32_t *Pict)
{
  uint32_t index = 0, i = 0;
  GLCD_SetCursor(0, (LCD_PIXEL_WIDTH - 1)); 
  GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
  for(index = 0; index < 2400; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        GLCD_WriteRAM(BackColor);
      }
      else
      {
        GLCD_WriteRAM(TextColor);
      }
    }
  }
}
/**************************************************************************************************************
 * ��������LCD_FillRect()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height ���������Ͻǵ㡢��͸�
 * ���  ��void
 * ����  ����һ�����ľ���
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{ 
	uint16_t tempcolor;
  GLCD_SetTextColor(TextColor);
  GLCD_DrawHLine(Xpos, Ypos, Width);
  GLCD_DrawHLine(Xpos, Ypos+ Height, Width);
  
  GLCD_DrawVLine(Xpos, Ypos, Height);
  GLCD_DrawVLine(Xpos+Width, Ypos, Height);

  Width --;
  Height-=2;
  Xpos++;
  tempcolor=TextColor;
  GLCD_SetTextColor(BackColor);

  while(Height--)
  {
    GLCD_DrawHLine(Xpos, ++Ypos, Width);    
  }

  GLCD_SetTextColor(tempcolor);
}
/**************************************************************************************************************
 * ��������LCD_FillCircle()
 * ����  ��uint16_t Xpos, uint16_t Ypos, uint16_t Radius ���Բ��Բ�ĺͰ뾶
 * ���  ��void
 * ����  ����һ�����Բ
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  uint16_t tempcolor;
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  tempcolor=TextColor;
  GLCD_SetTextColor(BackColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      GLCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY);
      GLCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      GLCD_DrawHLine(Xpos - CurX, Ypos -CurY, 2*CurX);
      GLCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  GLCD_SetTextColor(tempcolor);
  GLCD_DrawCircle(Xpos, Ypos, Radius);
}
/**************************************************************************************************************
 * ��������LCD_DrawUniLine()
 * ����  ��uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ��ʼ��������յ�����
 * ���  ��void
 * ����  �������ⷽ���ֱ��
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
void GLCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    GDrawPixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
/**************************************************************************************************************
 * ��������DrawPixel()
 * ����  ��int16_t x, int16_t y  �������
 * ���  ��void
 * ����  ����һ�����ص�
 * ����  ���ⲿ����        
 *****************************************************************************************************************/
static void GDrawPixel(uint16_t x, uint16_t y)
{ 
  if(x < 0 || x > LCD_XMAX || y < 0 || y > LCD_YMAX)
  {
    return;  
  }
  GLCD_DrawHLine(x, y, 1);
}


