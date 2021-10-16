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
uint8_t contadorLuz;
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

enum{
	tx_Valor_Claro,
	tx_Valor_Oscuro,
	noTx
};

uint32_t valorOscuro = 4040;
uint32_t valorClaro = 3300;

extern uint32_t adc_sensor_de_luz;
char app4St;
static uint32_t tiempo_espera;

void nivel_sensor_luz(void){
	if(adc_sensor_de_luz >= 4040){
		if(Alarma_Elapsed(tiempo_espera)){
			contadorLuz = contadorLuz + 1;
			if (contadorLuz > 5){
				app4St = tx_Valor_Oscuro;
				contadorLuz = 0;
			}
		}
	}else if(adc_sensor_de_luz <= 3300){
		if(Alarma_Elapsed(tiempo_espera)){
			contadorLuz = contadorLuz + 1;
			if (contadorLuz > 5){
				app4St = tx_Valor_Claro;
				contadorLuz = 0;
			}
		}
	}else{
		app4St = noTx;
	}
	tiempo_espera = Alarma_Set(1);
}

void app4_init(){
	// Codigo inicial
	app4St = noTx;
}

void app4_Run_Task(){
	// Maquina de estado para la app
	nivel_sensor_luz();
    switch(app4St){
		case tx_Valor_Claro:
			enviar_dato_sensor();
			app4St = noTx;
		break;
		case tx_Valor_Oscuro:
			enviar_dato_sensor();
			app4St = noTx;
		break;
		default:
		break;
    }
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
