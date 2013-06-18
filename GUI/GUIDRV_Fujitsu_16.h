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
File        : GUIDRV_Fujitsu_16.h
Purpose     : Interface definition for GUIDRV_FUJITSU_16 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_FUJITSU_16_H
#define GUIDRV_FUJITSU_16_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_Fujitsu_16_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_FUJITSU_16    &GUIDRV_Win_API

#else

  #define GUIDRV_FUJITSU_16    &GUIDRV_Fujitsu_16_API

#endif

#endif /* GUIDRV_FUJITSU_16_H */

/*************************** End of file ****************************/
