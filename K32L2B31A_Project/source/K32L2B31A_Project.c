/*
* @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    ${date}
 * @brief   Driver para
 * @details
 *
*/
/**
 * @file    K32L2B31A_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
unsigned int test_global_var=100;


/*
 * @brief   Application entry point.
 */
int main(void) {
	int i = 0 ;/* Force the counter to be placed into memory. */

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();
#endif

    printf("Hello World\n\r");
    printf("Prueba variable: %d", test_global_var);

    while(1) {
        i++ ;
        printf("i: %u\r\n", i);
    }
    return 0 ;
}
