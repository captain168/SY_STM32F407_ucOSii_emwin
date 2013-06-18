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
File        : GUIDRV_1611.h
Purpose     : Interface definition for GUIDRV_1611 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_1611_H
#define GUIDRV_1611_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_1611_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_1611             &GUIDRV_Win_API

#else

  #define GUIDRV_1611             &GUIDRV_1611_API

#endif

#endif

/*************************** End of file ****************************/
