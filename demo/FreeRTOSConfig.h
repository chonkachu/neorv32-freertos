/*
 * FreeRTOS V202212.00
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* NEORV32 HAL */
#include <neorv32.h>

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * Adapted for the NEORV32 RISC-V Processor.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
#define configMTIME_BASE_ADDRESS                ( NEORV32_CLINT_BASE + 0xbff8u )
#define configMTIMECMP_BASE_ADDRESS             ( NEORV32_CLINT_BASE + 0x4000u )
#define configISR_STACK_SIZE_WORDS              ( 256 )
#define configUSE_PREEMPTION                    ( 1 )
#define configUSE_IDLE_HOOK                     ( 1 )
#define configUSE_TICK_HOOK                     ( 1 )
#define configCPU_CLOCK_HZ                      ( 50000000 )
#define configTICK_RATE_HZ                      ( (TickType_t)(100) )
#define configMAX_PRIORITIES                    ( 5 )
#define configMINIMAL_STACK_SIZE                ( (unsigned short)(128) )
#define configTOTAL_HEAP_SIZE                   ( (size_t)(8192) )
#define configMAX_TASK_NAME_LEN                 ( 16 )
#define configUSE_TRACE_FACILITY                ( 0 )
#define configUSE_16_BIT_TICKS                  ( 0 )
#define configIDLE_SHOULD_YIELD                 ( 0 )
#define configUSE_MUTEXES                       ( 1 )
#define configQUEUE_REGISTRY_SIZE               ( 8 )
#define configCHECK_FOR_STACK_OVERFLOW          ( 2 )
#define configUSE_RECURSIVE_MUTEXES             ( 1 )
#define configUSE_MALLOC_FAILED_HOOK            ( 1 )
#define configUSE_APPLICATION_TASK_TAG          ( 0 )
#define configUSE_COUNTING_SEMAPHORES           ( 1 )
#define configGENERATE_RUN_TIME_STATS           ( 0 )
#define configUSE_PORT_OPTIMISED_TASK_SELECTION ( 1 )
#define configUSE_QUEUE_SETS                    ( 1 )
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   ( 4 )

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                   ( 0 )
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS                        ( 1 )
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                ( 8 )
#define configTIMER_TASK_STACK_DEPTH            ( 160 )

/* Task priorities. Allow these to be overridden. */
#ifndef uartPRIMARY_PRIORITY
  #define uartPRIMARY_PRIORITY                  ( configMAX_PRIORITIES - 3 )
#endif

/* Set the following definitions to 1 to include the API function, or zero to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                ( 1 )
#define INCLUDE_uxTaskPriorityGet               ( 1 )
#define INCLUDE_vTaskDelete                     ( 1 )
#define INCLUDE_vTaskCleanUpResources           ( 1 )
#define INCLUDE_vTaskSuspend                    ( 1 )
#define INCLUDE_vTaskDelayUntil                 ( 1 )
#define INCLUDE_vTaskDelay                      ( 1 )
#define INCLUDE_eTaskGetState                   ( 1 )
#define INCLUDE_xTimerPendFunctionCall          ( 1 )
#define INCLUDE_xTaskAbortDelay                 ( 1 )
#define INCLUDE_xTaskGetHandle                  ( 1 )
#define INCLUDE_xSemaphoreGetMutexHolder        ( 1 )
#define INCLUDE_xSemaphoreGive                  ( 1 )
#define INCLUDE_xSemaphoreTake                  ( 1 )
#define INCLUDE_xSemaphoreCreateCounting        ( 1 )
#define INCLUDE_xTaskCreate                     ( 1 )

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
void vAssertCalled( void );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled()

/* Map to the platform's write function. */
#define configPRINT_STRING( pcString )          vSendString( pcString )

#endif /* FREERTOS_CONFIG_H */
