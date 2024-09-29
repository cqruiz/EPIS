#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"


/* Local includes. */
#include "console.h"

/*====================================================================
 * [EPIS]
 *====================================================================*/

//Ejercicio 1
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
int main_Ejercicio1(void);




/*===================================================================*/
