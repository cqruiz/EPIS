#include "Ejercicio3.h"

#define    Ejercicio3   2
// Definición de la cola
QueueHandle_t xQueue3;

// Estructura para almacenar el ID del sensor y su valor de temperatura
typedef struct {
    uint8_t sensorID;
    uint8_t temperatureValue;
} TemperatureData;

// Función vT1Task: mide cada 200 ms
void vT1Task(void *pvParameters) {
    TemperatureData t1Data;
    t1Data.sensorID = 1;
    const TickType_t xDelay = pdMS_TO_TICKS(200);  // Delay de 200 ms

    for (;;) {
        // Simula la lectura del sensor T1
        t1Data.temperatureValue = (uint8_t)(rand() % 256);
        xQueueSend(xQueue3, &t1Data, portMAX_DELAY);
        vTaskDelay(xDelay);  // Espera 200 ms
    }
}

// Función vT2Task: mide cada 350 ms
void vT2Task(void *pvParameters) {
    TemperatureData t2Data;
    t2Data.sensorID = 2;
    const TickType_t xDelay = pdMS_TO_TICKS(350);  // Delay de 350 ms

    for (;;) {
        // Simula la lectura del sensor T2
        t2Data.temperatureValue = (uint8_t)(rand() % 256);
        xQueueSend(xQueue3, &t2Data, portMAX_DELAY);
        vTaskDelay(xDelay);  // Espera 350 ms
    }
}

// Función vT3Task: mide cada 100 ms
void vT3Task(void *pvParameters) {
    TemperatureData t3Data;
    t3Data.sensorID = 3;
    const TickType_t xDelay = pdMS_TO_TICKS(100);  // Delay de 100 ms

    for (;;) {
        // Simula la lectura del sensor T3
        t3Data.temperatureValue = (uint8_t)(rand() % 256);
        xQueueSend(xQueue3, &t3Data, portMAX_DELAY);
        vTaskDelay(xDelay);  // Espera 100 ms
    }
}

// Función vReadTask: lee de la cola y muestra en consola el sensor y su valor
void vReadTask(void *pvParameters) {
    TemperatureData receivedData;

    for (;;) {
        if (xQueueReceive(xQueue3, &receivedData, portMAX_DELAY) == pdPASS) {
            // Identifica el sensor y muestra la temperatura
            printf("Sensor %d: %d°C\n", receivedData.sensorID, receivedData.temperatureValue);
        }
    }
}

// Función principal donde se crean las tareas y la cola
void main_Ejercicio3(void) {
    // Crear la cola con espacio para 10 elementos de tipo TemperatureData
    xQueue3 = xQueueCreate(10, sizeof(TemperatureData));

    if (xQueue3 != NULL) {
        // Crear las tareas
        xTaskCreate(vT1Task, "T1Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
        xTaskCreate(vT2Task, "T2Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
        xTaskCreate(vT3Task, "T3Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
        xTaskCreate(vReadTask, "ReadTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

        // Iniciar el scheduler
        vTaskStartScheduler();
    } else {
        printf("Error creating the queue.\n");
    }

    // Si llega aquí, hubo un error al iniciar el scheduler
    for (;;) {}
}
