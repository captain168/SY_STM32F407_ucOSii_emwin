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
File        : GUIDRV_ST7591_DCache.h
Purpose     : Interface definition for GUIDRV_ST7591_DCache driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_ST7591_DCACHE_H
#define GUIDRV_ST7591_DCACHE_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_ST7591_DCache_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_ST7591_DCACHE &GUIDRV_Win_API

#else

  #define GUIDRV_ST7591_DCACHE &GUIDRV_ST7591_DCache_API

#endif

/*********************************************************************
*
*       Configuration structure
*/
typedef struct {
  //
  // Driver specific configuration items
  //
  int FirstSEG;
  int FirstCOM;
} CONFIG_ST7591_DCACHE;

/*********************************************************************
*
*       Public routines
*/
void GUIDRV_ST7591_DCache_SetBus8(GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);
void GUIDRV_ST7591_DCache_Config (GUI_DEVICE * pDevice, CONFIG_ST7591_DCACHE * pConfig);

#endif

/*************************** End of file ****************************/
