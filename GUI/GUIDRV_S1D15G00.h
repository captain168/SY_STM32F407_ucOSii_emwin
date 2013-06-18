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
File        : GUIDRV_S1D15G00.h
Purpose     : Interface definition for GUIDRV_S1D15G00 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_S1D15G00_H
#define GUIDRV_S1D15G00_H

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
  int Orientation;
  int UseCache;
} CONFIG_S1D15G00;

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_S1D15G00_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_S1D15G00    &GUIDRV_Win_API

#else

  #define GUIDRV_S1D15G00    &GUIDRV_S1D15G00_API

#endif

/*********************************************************************
*
*       Public routines
*/
void GUIDRV_S1D15G00_Config (GUI_DEVICE * pDevice, CONFIG_S1D15G00 * pConfig);
void GUIDRV_S1D15G00_SetBus8(GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);

#endif

/*************************** End of file ****************************/
