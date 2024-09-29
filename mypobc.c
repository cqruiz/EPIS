// Incluimos el header file
#include "mypobc.h"

/*******************************************************************************************
 * Inicialización de variables
 ******************************************************************************************/
char arrived_command[Nchar];
SemaphoreHandle_t xSemaphore = NULL;  // Semáforo para activar la tarea de lectura
TaskHandle_t xAcquiringTaskHandle = NULL;  // Manejo de la tarea de adquisición
TickType_t integrationTime = pdMS_TO_TICKS(10);  // Tiempo de integración inicial (10ms)

/*******************************************************************************************
 * Función principal
 ******************************************************************************************/
void main_mypobc(void) {
    // Crear el semáforo binario
    xSemaphore = xSemaphoreCreateBinary();

    if (xSemaphore != NULL) {
        // Crear las tareas
        xTaskCreate(vSendCommandToPOBCTask, "SendCmdTask", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
        xTaskCreate(vReadCommandTask, "ReadCmdTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

        // Iniciar el scheduler
        vTaskStartScheduler();
    }

    for (;;) {}
}

/*******************************************************************************************
 * Tarea que simula el envío de comandos a la POBC. 
 ******************************************************************************************/
void vSendCommandToPOBCTask(void *pvParameters) {
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
    const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000);

    char scan_0[Nchar] = "scan 0";
    char scan_1[Nchar] = "scan 1";
    char set_tint_1[Nchar] = "set_tint 26";
    char set_tint_2[Nchar] = "set_tint 73";

    for (;;) {
        // Simula enviar comando "scan 0"
        memcpy(arrived_command, scan_0, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay1000ms);

        // Simula enviar comando "set_tint 26"
        memcpy(arrived_command, set_tint_1, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay1000ms);

        // Simula enviar comando "scan 1"
        memcpy(arrived_command, scan_1, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay10000ms);

        // Simula enviar comando "scan 0"
        memcpy(arrived_command, scan_0, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay1000ms);

        // Simula enviar comando "set_tint 73"
        memcpy(arrived_command, set_tint_2, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay1000ms);

        // Simula enviar comando "scan 1"
        memcpy(arrived_command, scan_1, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay10000ms);

        memcpy(arrived_command, scan_0, sizeof arrived_command);
        xSemaphoreGive(xSemaphore);
        vTaskDelay(xDelay10000ms);

        // Detiene la tarea
        vTaskSuspend(NULL);
    }
}

/*******************************************************************************************
 * Tarea que recibe los comandos y los interpreta
 ******************************************************************************************/
void vReadCommandTask(void *pvParameters) {
    for (;;) {
        // Esperar el semáforo
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            // Interpretar el comando
            if (strncmp(arrived_command, "scan 1", 6) == 0) {
                scan_on();
            } else if (strncmp(arrived_command, "scan 0", 6) == 0) {
                scan_off();
            } else if (strncmp(arrived_command, "set_tint", 8) == 0) {
                tint_set();
            }
        }
    }
}

/*******************************************************************************************
 * Tarea que simula la adquisición de las líneas de píxeles
 ******************************************************************************************/
void vAcquiringTask(void *pvParameters) {
    for (;;) {
        // Simula la adquisición de imágenes con el tiempo de integración
        printf("Adquiriendo imagen...\n");
        vTaskDelay(integrationTime);  // Suspende según el tiempo de integración
    }
}

/*******************************************************************************************
 * Función para iniciar la adquisición
 ******************************************************************************************/
void scan_on(void) {
    if (xAcquiringTaskHandle == NULL) {
        // Crear la tarea de adquisición si no existe
        xTaskCreate(vAcquiringTask, "AcquiringTask", configMINIMAL_STACK_SIZE, NULL, 1, &xAcquiringTaskHandle);
        printf("Cámara encendida.\n");
    }
}

/*******************************************************************************************
 * Función para detener la adquisición
 ******************************************************************************************/
void scan_off(void) {
    if (xAcquiringTaskHandle != NULL) {
        // Eliminar la tarea de adquisición
        vTaskDelete(xAcquiringTaskHandle);
        xAcquiringTaskHandle = NULL;
        printf("Cámara apagada.\n");
    }
}

/*******************************************************************************************
 * Función para configurar el tiempo de integración
 ******************************************************************************************/
void tint_set(void) {
    // Obtener el tiempo de integración desde el comando
    int new_time = atoi(&arrived_command[9]);  // Extrae los dos dígitos del tiempo de integración
    if (new_time >= 1 && new_time <= 99) {
        integrationTime = pdMS_TO_TICKS(new_time);  // Convierte a ticks
        printf("Tiempo de integración configurado a %d ms.\n", new_time);
    } else {
        printf("Valor de tiempo de integración fuera de rango.\n");
    }
}
