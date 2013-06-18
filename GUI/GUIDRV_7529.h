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
File        : GUIDRV_7529.h
Purpose     : Interface definition for GUIDRV_7529 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_7529_H
#define GUIDRV_7529_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_7529_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_7529             &GUIDRV_Win_API

#else

  #define GUIDRV_7529             &GUIDRV_7529_API

#endif

#endif

/*************************** End of file ****************************/
