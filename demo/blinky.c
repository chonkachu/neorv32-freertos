/*
 * FreeRTOS V202212.00
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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


/* Standard includes. */
#include <stdio.h>
#include <neorv32.h>
#include <unistd.h>
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define MATRIX_SIZE 4
#define NUM_TASKS 4


void blinky( void );
static void vSupervisorTask( void *pvParameters );
static void vMatrixMultiplyTask( void *pvParameters );

uint16_t A[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
uint16_t B[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
uint16_t C[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

SemaphoreHandle_t xMatrixSemaphore;


void vMatrixMultiplyTask(void *pvParameters) {
    int32_t task_num = (int)pvParameters;

    neorv32_uart_printf(NEORV32_UART0, "DENTRO DA TASK %d \n", task_num);
    int32_t row_start = task_num * (MATRIX_SIZE / NUM_TASKS);
    int32_t row_end = row_start + (MATRIX_SIZE / NUM_TASKS);

    for (int32_t i = row_start; i < row_end; i++) {
        for (int32_t j = 0; j < MATRIX_SIZE; j++) {
            for (int32_t k = 0; k < MATRIX_SIZE; k++) {
                C[i*MATRIX_SIZE+j] += A[i*MATRIX_SIZE+k] * B[k*MATRIX_SIZE+j];
            }
        }
    }
    xSemaphoreGive(xMatrixSemaphore);
    vTaskDelete(NULL);
}

static void vSupervisorTask(void *pvParameters) {
    (void) pvParameters;

    xMatrixSemaphore = xSemaphoreCreateCounting(NUM_TASKS, 0);

    if( xMatrixSemaphore != NULL )
    {
        neorv32_uart_puts(NEORV32_UART0, "Supervisor: Creating worker tasks...\n");

        for (int32_t i = 0; i < NUM_TASKS; i++) {
            xTaskCreate(vMatrixMultiplyTask,        
                        "MatrixTask",               
                        configMINIMAL_STACK_SIZE,   
                        (void *)i,                  
                        tskIDLE_PRIORITY + 1,       
                        NULL);                      
        }

        neorv32_uart_puts(NEORV32_UART0, "Supervisor: Waiting for worker tasks to complete...\n");

        for (int32_t i = 0; i < NUM_TASKS; i++) {
            xSemaphoreTake(xMatrixSemaphore, portMAX_DELAY);
        }


        for (int32_t i = 0; i < MATRIX_SIZE; i++) {
            for (int32_t j = 0; j < MATRIX_SIZE; j++) {
                neorv32_uart_printf(NEORV32_UART0, "%d ", C[i*MATRIX_SIZE+j]);
            }
            neorv32_uart_printf(NEORV32_UART0, "\n");
        }
        neorv32_uart_puts(NEORV32_UART0, "ACABOU: All worker tasks have completed.\n");
    }

    vTaskDelete(NULL);
}

void blinky( void ) {
    neorv32_uart_puts(NEORV32_UART0, "VAI COMECAR AGR\n");

    // Create the supervisor task.
    xTaskCreate(vSupervisorTask, "Supervisor", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start the scheduler. This function will not return.
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached. */
    for( ;; );
}
