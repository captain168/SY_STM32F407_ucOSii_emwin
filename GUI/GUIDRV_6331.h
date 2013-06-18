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
File        : GUIDRV_6331.h
Purpose     : Interface definition for GUIDRV_6331 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_6331_H
#define GUIDRV_6331_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_6331_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_6331             &GUIDRV_Win_API

#else

  #define GUIDRV_6331             &GUIDRV_6331_API

#endif

#endif

/*************************** End of file ****************************/
