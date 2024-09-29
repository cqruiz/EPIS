#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* Local includes. */
#include "console.h"


/*====================================================================
 * [EPIS]
 *====================================================================*/
// Prototipos de las tareas
static void vSenderTask(void *pvParameters);
static void vReceiverTask(void *pvParameters);
int main_Ejercicio2(void);
