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
File        : GUIDRV_GW7630_1.h
Purpose     : Interface definition for GUIDRV_GW7630_1 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_GW7630_1_H
#define GUIDRV_GW7630_1_H

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_Win_API;

extern const GUI_DEVICE_API GUIDRV_GW7630_1_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_GW7630_1            &GUIDRV_Win_API

#else

  #define GUIDRV_GW7630_1            &GUIDRV_GW7630_1_API

#endif

#endif

void GUIDRV_GW7630_SetBus8(GUI_DEVICE * pDevice, GUI_PORT_API * pPortAPI);

/*************************** End of file ****************************/
