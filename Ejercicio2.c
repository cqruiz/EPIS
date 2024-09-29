#include "Ejercicio2.h"

#define    Ejercicio2   2
#define    mainDELAY_LOOP_COUNT pdMS_TO_TICKS( 200UL )

// Declaramos el handle para la cola

QueueHandle_t xQueue;


// Implementación de la tarea vSenderTask
static void vSenderTask( void *pvParameters){

    int32_t lValueToSend;
    BaseType_t xStatus;
    
    // Convertir el parámetro de entrada a int32_t
    lValueToSend = *(int32_t *) pvParameters;
    console_print( "Tarea Enviador Creada\r\n" );
    for ( ;; ){
        // Enviar el valor a la cola
        xStatus = xQueueSendToBack( xQueue, (void*) &lValueToSend, 0);
        
        // Comprobar si la operación de envío fue exitosa
        if ( xStatus != pdPASS) {
            console_print( "Could not send to the queue.\r\n" );
        }

        // Añadir un retardo para no saturar la cola
        vTaskDelay(500 / portTICK_PERIOD_MS);  // Esperar 500 ms

    }
}

// Implementación de la tarea vReceiverTask
static void vReceiverTask( void *pvParameters ){


    int32_t lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 ); // Esperar 100 ms
    console_print( "Tarea Recibidor Creada\r\n" );

    for( ;; ){

        // Recibir un valor de la cola
        xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
        //console_print( "Tarea Recibidor AAA\r\n" );
        
        if ( xStatus == pdPASS ){
            console_print( "Received = %d\r\n", lReceivedValue );
        } else {
            console_print( "Could not receive from the queue.\r\n" );
        }
    }
}

int main_Ejercicio2( void ){

 
    xQueue = xQueueCreate(5, sizeof(uint32_t) );

    int32_t valueA = 100;
    int32_t valueB = 200;
    if (xQueue != NULL) {

        xTaskCreate(vSenderTask, "Sender1", 1000, &valueA, 1, NULL);
        xTaskCreate(vSenderTask, "Sender2", 1000, &valueB, 1, NULL);
        xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 2, NULL);
        vTaskStartScheduler();

    } else {
    /* The queue could not be created */
        console_print( "The queue could not be created \r\n" );       
    }

    for( ;; );

}