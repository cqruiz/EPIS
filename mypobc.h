#include <stdio.h>
#include <pthread.h>
#include <string.h>
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h" 

/*******************************************************************************************
 * Definiciones
 ******************************************************************************************/

// Cantidad máxima de caracteres del comando
#define     Nchar   20 

/*******************************************************************************************
 * Prototipos de funciones y tareas
 ******************************************************************************************/
void main_mypobc( void );

void vReadCommandTask(void *pvParameters);

void vSendCommandToPOBCTask(void *pvParameters);

void vAcquiringTask(void *pvParameters);

void scan_on( void );

void scan_off( void );

void tint_set( void );