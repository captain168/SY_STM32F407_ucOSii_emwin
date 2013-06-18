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
File        : GUIDRV_13700.h
Purpose     : Interface definition for GUIDRV_13700 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_13700_H
#define GUIDRV_13700_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_13700_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_13700            &GUIDRV_Win_API

#else

  #define GUIDRV_13700            &GUIDRV_13700_API

#endif

#endif

/*************************** End of file ****************************/
