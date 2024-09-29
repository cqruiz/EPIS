#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* Local includes. */
#include "console.h"

// Prototipos de las tareas
void vT1Task(void *pvParameters);
void vT2Task(void *pvParameters);
void vT3Task(void *pvParameters);
void vReadTask(void *pvParameters);

// Prototipo de la función principal
void main_Ejercicio3(void);