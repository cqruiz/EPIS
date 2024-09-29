#include "Ejercicio1.h"

/*====================================================================
 * [EPIS]
 *====================================================================*/
#define    Ejercicio1   2
#define    mainDELAY_LOOP_COUNT pdMS_TO_TICKS( 200UL )

int main_Ejercicio1(void) {
                // Creación de la tarea 1
        xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);

        // Creación de la tarea 2
        xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);

        // Iniciar el scheduler
        vTaskStartScheduler();

        // El programa no debería llegar aquí nunca
        for (;;);
        return 0;

}


void vTask1( void *pvParameters ){
    const char *pcTaskName = "Task 1 is running\r\n";
    volatile uint32_t u1;
    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;

    for ( ;; ){
        //vTaskSuspend(NULL); 
        vTaskDelay( xDelay );
        console_print( pcTaskName );
        for (u1 = 0; u1 < mainDELAY_LOOP_COUNT; u1++){ }
    }
}

void vTask2( void *pvParameters ){
    const char *pcTaskName = "Task 2 is running\r\n";
    volatile uint32_t u1;
    const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
    for ( ;; ){
        vTaskDelay( xDelay );
        console_print( pcTaskName );
        for (u1 = 0; u1 < mainDELAY_LOOP_COUNT; u1++){ }
    }

}
























/*===================================================================*/
