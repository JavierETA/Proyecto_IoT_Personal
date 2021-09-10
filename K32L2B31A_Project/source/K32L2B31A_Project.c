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
#include "leds.h"
/* TODO: insert other definitions and declarations here. */
bool auxiliar = 0;
int contador = 0;


/*
 * @brief   Application entry point.
 */
//Funcion que cuenta encendido led verde
bool cont_verde(void){
	++contador;
	if (contador == 10) {
		auxiliar = true;
	}
	if (contador == 20) {
		auxiliar = false;
		contador = 0;
	}
	return(auxiliar);
}
//funcion para producir un retardo
void delay_block(void){
	int i = 0 ;
	for (i= 0; i < 1000000; ++i) {
		//printf("%d", i);
	}
}

int main(void) {
	bool sem;
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();
#endif

    while(1) {
        led_on_green();
        delay_block();
        led_off_green();
        delay_block();
        sem = cont_verde();
        if (sem) {
			led_on_red();
		} else {
			led_off_red();
		}
    }
    return 0 ;
}
