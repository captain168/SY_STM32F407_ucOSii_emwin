/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2012     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File        : LCD_X_8080.c
Purpose     : Port routines 8080 interface, 16 bit data bus
----------------------------------------------------------------------
*/

/*********************************************************************
*
*           Hardware configuration
*
**********************************************************************
  Needs to be adapted to your target hardware.
*/

#include "LCDConf.h"
#include "Global.h"
#include "GUI.h"

/*********************************************************************
*
*       Local defines (sfrs used in LCD_X_8080_16.c)
*
**********************************************************************
*/
#define _GPIO_SPEED_50MHz         (0x3uL)
#define _GPIO_MODE_AF_PP          (0x18uL)
#define _GPIO_ALTOUTPP            (0x2uL)  // Alternate function output Push-Pull
#define _GPIO_PORT_LCD_CONF       (_GPIO_SPEED_50MHz << 0) | (_GPIO_ALTOUTPP << 2)

#define _BIT_FSMC_MBKEN     0
#define _BIT_FSMC_MWID      4
#define _BIT_FSMC_WREN      12
#define _BIT_FSMC_EXTMOD    14
#define _BIT_FSMC_ADDSET    0
#define _BIT_FSMC_DATAST    8

#define _RCC_AHB_BIT_FSMC   8
#define _RCC_APB_BIT_AFIO   0
#define _RCC_APB_BIT_GPIOD  5
#define _RCC_APB_BIT_GPIOE  6
#define _RCC_APB_BIT_GPIOF  7
#define _RCC_APB_BIT_GPIOG  8

#define _GPIO_PORT0  0
#define _GPIO_PORT1  4
#define _GPIO_PORT2  8
#define _GPIO_PORT3  12
#define _GPIO_PORT4  16
#define _GPIO_PORT5  20
#define _GPIO_PORT6  24
#define _GPIO_PORT7  28
#define _GPIO_PORT8  0
#define _GPIO_PORT9  4
#define _GPIO_PORT10 8
#define _GPIO_PORT11 12
#define _GPIO_PORT12 16
#define _GPIO_PORT13 20
#define _GPIO_PORT14 24
#define _GPIO_PORT15 28

#define _GPIO_BASE_ADDR  (0x40010800)
#define _GPIOAH_OFFS     (0x04)
#define _GPIOBL_OFFS     (0x0400)
#define _GPIOBH_OFFS     (0x0404)
#define _GPIOCL_OFFS     (0x0800)
#define _GPIOCH_OFFS     (0x0804)
#define _GPIODL_OFFS     (0x0C00)
#define _GPIODH_OFFS     (0x0C04)
#define _GPIOD_IDR_OFFS  (0x0C08)
#define _GPIOEL_OFFS     (0x1000)
#define _GPIOEH_OFFS     (0x1004)
#define _GPIOFL_OFFS     (0x1400)
#define _GPIOFH_OFFS     (0x1404)
#define _GPIOGL_OFFS     (0x1800)
#define _GPIOGH_OFFS     (0x1804)
#define _GPIOG_IDR_OFFS  (0x1808)

#define _GPIOAL     (*(volatile unsigned long*)  _GPIO_BASE_ADDR)
#define _GPIOAH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOAH_OFFS))
#define _GPIOBL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOBL_OFFS))
#define _GPIOBH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOBH_OFFS))
#define _GPIOCL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOCL_OFFS))
#define _GPIOCH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOCH_OFFS))
#define _GPIODL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIODL_OFFS))
#define _GPIODH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIODH_OFFS))
#define _GPIOD_IDR  (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOD_IDR_OFFS))
#define _GPIOEL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOEL_OFFS))
#define _GPIOEH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOEH_OFFS))
#define _GPIOFL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOFL_OFFS))
#define _GPIOFH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOFH_OFFS))
#define _GPIOGL     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOGL_OFFS))
#define _GPIOGH     (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOGH_OFFS))
#define _GPIOG_IDR  (*(volatile unsigned long*) (_GPIO_BASE_ADDR + _GPIOG_IDR_OFFS))

#define _FSMC_BASE_ADDR   (0xA0000000)
#define _FSMC_BTR1_OFFS   (0x4)
#define _FSMC_BCR2_OFFS   (0x8)
#define _FSMC_BTR2_OFFS   (0xC)
#define _FSMC_BCR3_OFFS   (0x10)
#define _FSMC_BTR3_OFFS   (0x14)
#define _FSMC_BCR4_OFFS   (0x18)
#define _FSMC_BTR4_OFFS   (0x1C)
#define _FSMC_BWTR1_OFFS  (0x104)
#define _FSMC_BWTR2_OFFS  (0x10C)
#define _FSMC_BWTR3_OFFS  (0x114)
#define _FSMC_BWTR4_OFFS  (0x11C)

#define _FSMC_BCR1  (*(volatile unsigned long*) _FSMC_BASE_ADDR)
#define _FSMC_BCR2  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BCR2_OFFS))
#define _FSMC_BCR3  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BCR3_OFFS))
#define _FSMC_BCR4  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BCR4_OFFS))
#define _FSMC_BTR1  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BTR1_OFFS))
#define _FSMC_BTR2  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BTR2_OFFS))
#define _FSMC_BTR3  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BTR3_OFFS))
#define _FSMC_BTR4  (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BTR4_OFFS))
#define _FSMC_BWTR1 (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BWTR1_OFFS))
#define _FSMC_BWTR2 (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BWTR2_OFFS))
#define _FSMC_BWTR3 (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BWTR3_OFFS))
#define _FSMC_BWTR4 (*(volatile unsigned long*) (_FSMC_BASE_ADDR + _FSMC_BWTR4_OFFS))

#define _RCC_BASE_ADDR    (0x40021000)
#define _RCC_AHBENR_OFFS  (0x14)
#define _RCC_APB2ENR_OFFS (0x18)

#define _RCC_AHBENR  (*(volatile unsigned long*) (_RCC_BASE_ADDR + _RCC_AHBENR_OFFS))
#define _RCC_APB2ENR (*(volatile unsigned long*) (_RCC_BASE_ADDR + _RCC_APB2ENR_OFFS))

#define _LCD_REG_16  (*((volatile unsigned short*) 0x6C000000))
#define _LCD_DATA_16 (*((volatile unsigned short*) 0x6C000002))

/*********************************************************************
*
*           High level LCD access macros
*
**********************************************************************
  Usually, there is no need to modify these macros.
  It should be sufficient ot modify the low-level macros
  above.
*/

#define LCD_X_READ(c)                                       \
  LCD_SET_DIR_IN();                                         \
  LCD_CLR_CS();                                             \
  LCD_CLR_RD();                                             \
  c = LCD_DATA_IN_L | ((unsigned short)LCD_DATA_IN_H << 8); \
  LCD_SET_CS();                                             \
  LCD_SET_RD()

#define LCD_X_WRITE(c)                                      \
  LCD_SET_DIR_OUT();                                        \
  LCD_DATA_OUT_L = (unsigned char)c;                        \
  LCD_DATA_OUT_H = c >> 8;                                  \
  LCD_CLR_CS();                                             \
  LCD_CLR_WR();                                             \
  LCD_SET_WR();                                             \
  LCD_SET_CS()

/*********************************************************************
*
*           Initialisation
*
**********************************************************************
  This routine should be called from your application program
  to set port pins to their initial values
*/

/*********************************************************************
*
*       _LCD_CtrlLinesConfig
*
*       Purpose: Configures LCD Control lines (FSMC Pins) in alternate
*                function Push-Pull mode.
*/
static void _LCD_CtrlLinesConfig(void) {
  U32 TempReg;

  _RCC_AHBENR  |= (1 << _RCC_AHB_BIT_FSMC);   // Enable FSMC clock
  _RCC_APB2ENR |= (1 << _RCC_APB_BIT_GPIOD);  // Enable GPIOD clock
  _RCC_APB2ENR |= (1 << _RCC_APB_BIT_GPIOE);  // Enable GPIOE clock
  _RCC_APB2ENR |= (1 << _RCC_APB_BIT_GPIOF);  // Enable GPIOF clock
  _RCC_APB2ENR |= (1 << _RCC_APB_BIT_GPIOG);  // Enable GPIOG clock
  _RCC_APB2ENR |= (1 << _RCC_APB_BIT_AFIO);   // Enable AFIO clock
  //
  // Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
  // PD.10(D15), PD.14(D0), PD.15(D1) as alternate function push pull.
  //
  TempReg  = _GPIODL;
  TempReg &= ~0x440044;  // Clean out bits which are nulled
  TempReg |=  (_GPIO_PORT_LCD_CONF  << _GPIO_PORT0)   // PD.00(D2)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT1)   // PD.01(D3)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT4)   // PD.04(NOE)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT5)   // PD.05(NWE)
          ;
  _GPIODL  = TempReg;
  TempReg  = _GPIODH;
  TempReg &= ~0x44000444;  // Clean out bits which are nulled
  TempReg |=  (_GPIO_PORT_LCD_CONF  << _GPIO_PORT8)   // PD.08(D13)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT9)   // PD.09(D14)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT10)  // PD.10(D15)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT14)  // PD.14(D0)
          |  ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT15)  // PD.15(D1)
          ;
  _GPIODH = TempReg;
  //
  // Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9),
  // PE.13(D10), PE.14(D11), PE.15(D12) as alternate function push pull.
  //
  TempReg  = _GPIOEL;
  TempReg &= ~0x40000000;  // Clean out bits which are nulled
  TempReg |= (U32)((_GPIO_PORT_LCD_CONF) << _GPIO_PORT7);   // PE.07(D4)
  _GPIOEL  = TempReg;
  _GPIOEH  = ((_GPIO_PORT_LCD_CONF  << _GPIO_PORT8)    // PE.08(D5)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT9)    // PE.09(D6)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT10)   // PE.10(D7)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT11)   // PE.11(D8)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT12)   // PE.12(D9)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT13)   // PE.13(D10)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT14)   // PE.14(D11)
           | ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT15))  // PE.15(D12)
           ;
  //
  // Set PF.00(A0 (RS)) as alternate function push pull
  //
  TempReg  = _GPIOFL;
  TempReg &= ~0x04;  // Clean out bits which are nulled
  TempReg |=  (_GPIO_PORT_LCD_CONF  << _GPIO_PORT0);    // PF.00(A0 (RS))
  _GPIOFL  = TempReg;
  //
  // Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS)
  //
  TempReg  = _GPIOGH;
  TempReg &= ~0x40000;  // Clean out which that are nulled
  TempReg |= ((_GPIO_PORT_LCD_CONF) << _GPIO_PORT12);   // PG.12(NE4 (LCD/CS))
  _GPIOGH  = TempReg;
}

/*********************************************************************
*
*       _LCD_CtrlLinesConfig
*
*       Purpose: Configures the Parallel interface (FSMC) for
*                LCD(Parallel mode).
*/
static void _LCD_FSMCConfig(void) {
  _FSMC_BCR4 = 0
             | (1 << _BIT_FSMC_MWID)       // 16bit memory width
             | (1 << _BIT_FSMC_WREN)       // Write enable
             | (1 << _BIT_FSMC_EXTMOD)     // Extended mode enable. Read/Write operations can have different timings.
             ;
  _FSMC_BTR4 = 0
             | (0x0A << _BIT_FSMC_ADDSET)  // Address setup time  = 11 HCLK clock cycles
             | (0x0A << _BIT_FSMC_DATAST)  // Data-phase duration = 11 HCLK clock cycles
             ;
  _FSMC_BWTR4 = 0
              | (1 << _BIT_FSMC_ADDSET)    // Address setup phase duration = 2 HCLK clock cycles
              | (1 << _BIT_FSMC_DATAST)    // Data-phase duration = 2 HCLK clock cycles
              ;
  _FSMC_BCR4 |= (1 << _BIT_FSMC_MBKEN);    // Memory bank enable
}

void LCD_X_Init(void) {
  _LCD_CtrlLinesConfig();
  _LCD_FSMCConfig();
}

/*********************************************************************
*
*           Access routines
*
**********************************************************************
  Usually, there is no need to modify these routines.
  It should be sufficient ot modify the low-level macros
  above.
*/

/* Write to controller, with A0 = 0 */
void LCD_X_Write00_16(unsigned short c) {
  _LCD_REG_16 = c;
}

/* Write to controller, with A0 = 1 */
void LCD_X_Write01_16(unsigned short c) {
  _LCD_DATA_16 = c;
}

/* Write multiple bytes to controller, with A0 = 1 */
void LCD_X_WriteM01_16(unsigned short * pData, int NumWords) {
  U16 Data;
  for (; NumWords; NumWords--) {
    Data = *pData++;
    _LCD_DATA_16 = Data;
  }
}

/* Write multiple bytes to controller, with A0 = 0 */
void LCD_X_WriteM00_16(unsigned short * pData, int NumWords) {
  do {
    _LCD_REG_16 = *pData++;
  } while (--NumWords);
}

/* Read multiple bytes from controller, with A0 = 1 */
void LCD_X_ReadM01_16(unsigned short * pData, int NumWords) {
  U16 Data;
  volatile U32 i;
  do {
    Data = _LCD_DATA_16;
    *pData++ = Data;
  } while (--NumWords);
}
