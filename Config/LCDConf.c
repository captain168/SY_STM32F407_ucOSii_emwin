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
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "glcd.h"
//#include "RTOS.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  240
#define YSIZE_PHYS  320

//
// Color conversion
//
#define COLOR_CONVERSION  GUICC_M565

//
// Display driver
//
#define DISPLAY_DRIVER  GUIDRV_FLEXCOLOR


/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Defines, configuration
*
**********************************************************************
*/

#define JOYSTICK_TIMER_INTERVAL  40  // Poll joystick input every x ms

/*********************************************************************
*
*       Defines, sfrs
*
**********************************************************************
*/

//
// RCC
//
#define RCC_BASE_ADDR      0x40021000

#define RCC_AHBENR_OFFS    0x14
#define RCC_APB2ENR_OFFS   0x18

#define RCC_AHBENR         (*(volatile U32*)(RCC_BASE_ADDR + RCC_AHBENR_OFFS))
#define RCC_APB2ENR        (*(volatile U32*)(RCC_BASE_ADDR + RCC_APB2ENR_OFFS))

#define RCC_AHB_FSMC_BIT   8

#define RCC_APB_AFIO_BIT   0

#define RCC_APB_GPIOD_BIT  5
#define RCC_APB_GPIOE_BIT  6
#define RCC_APB_GPIOF_BIT  7
#define RCC_APB_GPIOG_BIT  8

//
// GPIO
//
#define GPIO_BASE_ADDR      0x40010800

#define GPIODL_OFFS         0x0C00
#define GPIODH_OFFS         0x0C04
#define GPIOEL_OFFS         0x1000
#define GPIOEH_OFFS         0x1004
#define GPIOFL_OFFS         0x1400
#define GPIOGH_OFFS         0x1804

#define GPIODL              (*(volatile U32*)(GPIO_BASE_ADDR + GPIODL_OFFS))
#define GPIODH              (*(volatile U32*)(GPIO_BASE_ADDR + GPIODH_OFFS))
#define GPIOEL              (*(volatile U32*)(GPIO_BASE_ADDR + GPIOEL_OFFS))
#define GPIOEH              (*(volatile U32*)(GPIO_BASE_ADDR + GPIOEH_OFFS))
#define GPIOFL              (*(volatile U32*)(GPIO_BASE_ADDR + GPIOFL_OFFS))
#define GPIOGH              (*(volatile U32*)(GPIO_BASE_ADDR + GPIOGH_OFFS))

#define GPIO_PORT0_BIT       0
#define GPIO_PORT1_BIT       4
#define GPIO_PORT4_BIT      16
#define GPIO_PORT5_BIT      20
#define GPIO_PORT7_BIT      28
#define GPIO_PORT8_BIT       0
#define GPIO_PORT9_BIT       4
#define GPIO_PORT10_BIT      8
#define GPIO_PORT11_BIT     12
#define GPIO_PORT12_BIT     16
#define GPIO_PORT13_BIT     20
#define GPIO_PORT14_BIT     24
#define GPIO_PORT15_BIT     28

#define GPIO_SPEED_50MHz    0x03uL
#define GPIO_ALTOUTPP       0x02uL  // Alternate function output Push-Pull
#define GPIO_PORT_LCD_CONF  ((GPIO_SPEED_50MHz << 0) | (GPIO_ALTOUTPP << 2))

//
// FSMC
//
#define FSMC_BASE_ADDR   0xA0000000

#define FSMC_BCR4_OFFS   0x0018
#define FSMC_BTR4_OFFS   0x001C
#define FSMC_BWTR4_OFFS  0x011C

#define FSMC_BCR4        (*(volatile U32*)(FSMC_BASE_ADDR + FSMC_BCR4_OFFS))
#define FSMC_BTR4        (*(volatile U32*)(FSMC_BASE_ADDR + FSMC_BTR4_OFFS))
#define FSMC_BWTR4       (*(volatile U32*)(FSMC_BASE_ADDR + FSMC_BWTR4_OFFS))

#define FSMC_MBKEN_BIT    0
#define FSMC_MWID_BIT     4
#define FSMC_WREN_BIT    12
#define FSMC_EXTMOD_BIT  14
#define FSMC_ADDSET_BIT   0
#define FSMC_DATAST_BIT   8

//
// COG interface register addr.
//
#define LCD_REG_16   *(vu16*)((u32)0x60000000)
#define LCD_DATA_16  *(vu16*)((u32)0x60020000)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

//
// OS timers
//
//static OS_TIMER _JoystickTimer;

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/********************************************************************
*
*       _LcdSetReg
*
* Function description:
*   Sets display register
*/
static void _LcdSetReg(U16 Data) {
  LCD_REG_16 = Data;
}

/********************************************************************
*
*       _LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void _LcdWriteData(U16 Data) {
  LCD_DATA_16 = Data;
}

/********************************************************************
*
*       _LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void _LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    LCD_DATA_16 = *pData++;
  }
}

/********************************************************************
*
*       _LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void _LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    *pData++ = LCD_DATA_16;
  }
}

/********************************************************************
*
*       _WriteReg
*
* Function description:
*   Write a value to a display register.
*/
static void _WriteReg(U16 Reg, U16 Data) {
  _LcdSetReg   (Reg);
  _LcdWriteData(Data);
}

/*********************************************************************
*
*       _LCD_CtrlLinesConfig
*
* Function description:
*   Configures LCD Control lines (FSMC Pins) in alternate function
*   Push-Pull mode.
*/


/********************************************************************
*
*       _InitLcdController
*
* Function description:
*   Initializes the LCD controller
*/
static void _InitLcdController(void) {
 GLCD_Init();
}

/********************************************************************
*
*       _ExecJoystick
*
* Function description:
*   Periodically evaluate the joystick input
*/
static void _ExecJoystick(void) {
  //unsigned KeyState;

  GUI_PID_STATE State = {0};
  //KeyState = BSP_GetKeyStat();

  GUI_JOYSTICK_StoreState(&State);
 // OS_RetriggerTimer(&_JoystickTimer);
}

/********************************************************************
*
*       _Init
*
* Function description:
*   Initializes the LCD controller
*/
static void _Init(void) {
  _InitLcdController();
  //
  // Start joystick timer
  //
  //OS_CREATETIMER(&_JoystickTimer, _ExecJoystick, JOYSTICK_TIMER_INTERVAL);
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.Orientation =  GUI_SWAP_XY |GUI_MIRROR_Y;// GUI_MIRROR_X;//
  //Config.RegEntryMode=8;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = _LcdSetReg;
  PortAPI.pfWrite16_A1  = _LcdWriteData;
  PortAPI.pfWriteM16_A1 = _LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = _LcdReadDataMultiple;
  
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    _Init();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

