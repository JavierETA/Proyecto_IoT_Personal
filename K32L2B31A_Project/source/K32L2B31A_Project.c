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
#include "sensor_temp.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "botones.h"
#include "modem.h"
#include "app4.h"
/* TODO: insert other definitions and declarations here. */

#define SIZE_BUFFER_COMANDO	105
/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/
extern int8_t bandera;

/*******************************************************************************
 * Local vars
 ******************************************************************************/
volatile uint32_t segAct=0;
/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void Alarma_Init(void);
uint32_t Alarma_Set(uint32_t time2Wait);
char Alarma_Elapsed(uint32_t time2Test);
// Inicializa Alarma
void Alarma_Init(void){
	segAct = lptmr0_irqCounter;
}

// retorna el tiempo futuro de la alarma
uint32_t Alarma_Set(uint32_t time2Wait){
	segAct = lptmr0_irqCounter;
	return (segAct + time2Wait);
}

// retorna si la alarma se cumplio
char Alarma_Elapsed(uint32_t time2Test){
	segAct = lptmr0_irqCounter;
	if(segAct >= time2Test) return true;
	else return false;
}

#define Timer_Init() LPTMR_StartTimer(LPTMR0)

/* Init board hardware. */
void BOARD_Init(void){
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
}
// Scratch

	// 1. crear codigo nuevo
	// 2. Se compilar
	// 3. Se prueba en el board
	// 4. Se depura
	// 5.Funciona??? NO --> va al punto 1.
	// Funciona??? SI ---> punto 6.
	// 6. Backup Version
	// 7.Modularizar el modulo que Funciono
	// 8. Ensayar el Funcionamiento ya modularizado
	// 9. Comentar y organizar
	// 10.Optimizar codigo si es necesario
	// 11. Clean y Build
	// 12. Liberar version V2.0

//end Scratf
//  main
int main(void) {
	BOARD_Init();
    Timer_Init();
    Modem_Init();
    SensorLuz_Init();
    Alarma_Init();
    app4_init();
    while(1) {
    	Modem_Task_Run();
    	Key_Task_Run();
    	SensorLuz_Task_Run();
    	if (bandera == 1) {
			app4_Run_Task();
		}
    }
    return 0 ;
}
