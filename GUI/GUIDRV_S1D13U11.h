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
File        : GUIDRV_S1D13U11.h
Purpose     : Interface definition for GUIDRV_S1D13U11 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_S1D13U11_H
#define GUIDRV_S1D13U11_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_S1D13U11_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_S1D13U11            &GUIDRV_Win_API

#else

  #define GUIDRV_S1D13U11            &GUIDRV_S1D13U11_API

#endif

void GUIDRV_S1D13U11_SetBus(GUI_DEVICE * pDevice, GUI_PORT_API * pPortAPI);

#endif

/*************************** End of file ****************************/
