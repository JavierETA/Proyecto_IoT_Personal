/*! @file : app4.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    17/10/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app4.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "leds.h"
#include "sensor_luz.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "modem.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum{
	tx_Valor_Claro,
	tx_Valor_Oscuro,
	noTx
};

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void Alarma_Init(void);
uint32_t Alarma_Set(uint32_t time2Wait);
char Alarma_Elapsed(uint32_t time2Test);
void nivel_sensor_luz(void);
void SecLuz_Task(uint32_t tiempo1, uint32_t tiempo2);

/*******************************************************************************
 * External vars
 ******************************************************************************/

extern float adc_sensor_de_luz;
extern unsigned char SecLuz[2];

/*******************************************************************************
 * Local vars
 ******************************************************************************/

uint8_t contadorLuz, contadorLuz1, contadorLuz2;
static float valorOscuro = 9.0;
static float valorClaro = 150.0;
char app4St;
static uint32_t tiempo_espera;
static uint32_t tiempo_espera1;
uint8_t ledapagado;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void nivel_sensor_luz(void){
	if(adc_sensor_de_luz <= valorOscuro){
		if(Alarma_Elapsed(tiempo_espera)){
			contadorLuz = contadorLuz + 1;
			if (contadorLuz > 5){
				app4St = tx_Valor_Oscuro;
				contadorLuz = 0;
			}
		}
	}
	if(adc_sensor_de_luz >= valorClaro){
		if(Alarma_Elapsed(tiempo_espera)){
			contadorLuz = contadorLuz + 1;
			if (contadorLuz > 5){
				app4St = tx_Valor_Claro;
				contadorLuz = 0;
			}
		}
	}
	if(adc_sensor_de_luz > valorOscuro && adc_sensor_de_luz < valorClaro){
		app4St = noTx;
	}
	tiempo_espera = Alarma_Set(1);
}

void SecLuz_Task(uint32_t tiempo1, uint32_t tiempo2){
	if(ledapagado == 0){
		if(Alarma_Elapsed(tiempo_espera1)){
			contadorLuz1 = contadorLuz1 + 1;
			if (contadorLuz1 >= tiempo1){
				ledapagado = 1;
				led_off_green();
				contadorLuz1 = 0;
			}
		}
	}
	if(ledapagado == 1){
		if(Alarma_Elapsed(tiempo_espera1)){
				contadorLuz2 = contadorLuz2 + 1;
				if (contadorLuz2 >= tiempo2){
					led_on_green();
					contadorLuz2 = 0;
					ledapagado = 0;
				}
		}
	}
	tiempo_espera1 = Alarma_Set(1);
}
/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
void app4_init(void){
	// Codigo inicial
	app4St = noTx;
}

void app4_Run_Task(void){
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
    SecLuz_Task(SecLuz[0] - 0x30, SecLuz[1] - 0x30);
}
