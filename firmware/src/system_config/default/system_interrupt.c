/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************



void __ISR(_TIMER_1_VECTOR, ipl4AUTO) IntHandlerDrvTmrInstance0(void)
{
    BSP_LEDOff(BSP_LED_0);      //Mis un �tat High sur la LED0 afin de pouvoir voir la dur�e tu timer1
    
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);  //Efface l'�tat du drapeau d'interruption pour le Timer1
    
    static uint8_t compteur = 0, flag = 0;
    
    compteur ++;
    
    if(flag == 0 && compteur >= 150) //Ici, je viens compter jusqua 150x20ms donc 3 secondes 
    {
        flag = 1;                   //Qui vient activer un flag afin que
    }                               //l'�tat APP_STATE_SERVICE_TASKS ce update � chaque cycle apres les 3 premi�res secondes
    
    if(flag)
    {                               //Changement d'�tat de ma machine d'�tat
        APP_UpdateState (APP_STATE_SERVICE_TASKS);
        
        GPWM_GetSettings(&appData.mesValeurs);     // Obtention vitesse et angle
        GPWM_DispSettings(&appData.mesValeurs);    // Affichage
        GPWM_ExecPWM(&appData.mesValeurs);         // Execution PWM et gestion moteur
    }
    BSP_LEDOn(BSP_LED_0);      //Mis un �tat Low sur la LED0 afin de pouvoir voir la dur�e tu timer1
}
void __ISR(_TIMER_2_VECTOR, ipl0AUTO) IntHandlerDrvTmrInstance1(void)
{
}
void __ISR(_TIMER_3_VECTOR, ipl0AUTO) IntHandlerDrvTmrInstance2(void)
{
}
void __ISR(_TIMER_4_VECTOR, ipl7AUTO) IntHandlerDrvTmrInstance3(void)
{
    BSP_LEDOff(BSP_LED_1);      //Mis un �tat High sur la LED1 afin de pouvoir voir la dur�e tu timer4
    
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_4);  //Efface l'�tat du drapeau d'interruption pour le Timer4
    GPWM_ExecPWMSoft(&appData.mesValeurs);                  //Execution PWM Software
    
    BSP_LEDOn(BSP_LED_1);      //Mis un �tat Low sur la LED1 afin de pouvoir voir la dur�e tu timer4
}
 
/*******************************************************************************
 End of File
*/ 
