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
#include "sensor_luz.h"
#include "irq_lptmr0.h"
#include "botones.h"
/* TODO: insert other definitions and declarations here. */
int contador = 0;
bool sem;


/*
 * @brief   Application entry point.
 */
//Funcion que cuenta encendido led verde
void cont_verde(void){
	++contador;
	if (contador == 20) {
		toggle_led_red();
		contador = 0;
	}
}

int main(void) {
	float ADC_SenLuz;
	bool boton1,boton2;
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();
#endif
    LPTMR_StartTimer(LPTMR0);
    while(1) {
    	if (lptmr0_irqCounter) {
    		toggle_led_green();
    		cont_verde();
    		ADC_SenLuz = SenLuzObtenerDatoLux();
    		printf("Sensor de luz - Lux= %f \r\n", ADC_SenLuz);
    		lptmr0_irqCounter = false;
    		boton1 = boton1LeerEstado();
    		boton2 = boton2LeerEstado();
    		printf("boton1: %u \r\n", boton1);
    		printf("boton2: %u \r\n", boton2);
		}
    }
    return 0 ;
}
