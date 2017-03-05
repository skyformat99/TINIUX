/**********************************************************************************************************
AIOS(Advanced Input Output System) - An Embedded Real Time Operating System (RTOS)
Copyright (C) 2012~2017 SenseRate.Com All rights reserved.
http://www.aios.io -- Documentation, latest information, license and contact details.
http://www.SenseRate.com -- Commercial support, development, porting, licensing and training services.
--------------------------------------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met: 
1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution. 
3. Neither the name of the copyright holder nor the names of its contributors may be used 
to endorse or promote products derived from this software without specific prior written 
permission. 
--------------------------------------------------------------------------------------------------------
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
--------------------------------------------------------------------------------------------------------
 Notice of Export Control Law 
--------------------------------------------------------------------------------------------------------
 SenseRate AIOS may be subject to applicable export control laws and regulations, which might 
 include those applicable to SenseRate AIOS of U.S. and the country in which you are located. 
 Import, export and usage of SenseRate AIOS in any manner by you shall be in compliance with such 
 applicable export control laws and regulations. 
***********************************************************************************************************/

#ifndef __FITCPU_HPP
#define __FITCPU_HPP

#include "OSType.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Scheduler utilities. */
extern void FitSchedule( void );
#define FitNVIC_INT_CTRL_REG		( * ( ( volatile uOS32_t * ) 0xe000ed04UL ) )
#define FitNVIC_PENDSVSET_BIT		( 1UL << 28UL )
#define FitScheduleFromISR( b ) 	if( b ) FitSchedule()
/*-----------------------------------------------------------*/

#include <intrinsics.h>
#define FIT_QUICK_GET_PRIORITY		1
#define FitGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - __CLZ( ( uxReadyPriorities ) ) )

/* Critical section management. */
extern void FitEnterCritical( void );
extern void FitExitCritical( void );
extern uOS32_t FitSetInterruptMask( void );
extern void FitClearInterruptMask( uOS32_t ulNewMask );

#define FitDISABLE_INTERRUPTS()					FitSetInterruptMask()
#define FitENABLE_INTERRUPTS()					FitClearInterruptMask( 0 )
#define FitENTER_CRITICAL()						FitEnterCritical()
#define FitEXIT_CRITICAL()						FitExitCritical()
#define FitSET_INTERRUPT_MASK_FROM_ISR()		FitSetInterruptMask()
#define FitCLEAR_INTERRUPT_MASK_FROM_ISR(x)		FitClearInterruptMask( x )
/*-----------------------------------------------------------*/

#define OS_ENTER_CRITICAL()						FitEnterCritical()
#define OS_EXIT_CRITICAL()						FitExitCritical()

uOSStack_t *FitInitializeStack( uOSStack_t *pxTopOfStack, OSTaskFunction_t TaskFunction, void *pvParameters );
sOSBase_t FitStartScheduler( void );

void FitPendSVHandler( void );
void FitOSTickISR( void );
void FitSVCHandler( void );

#ifdef __cplusplus
}
#endif

#endif //__FITCPU_HPP