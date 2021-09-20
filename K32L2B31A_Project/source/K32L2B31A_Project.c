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
/* TODO: insert other definitions and declarations here. */

enum lista_comandos_control {
	kLED_VERDE_ON = 0,
	kLED_VERDE_OFF,
	kLED_ROJO_ON,
	kLED_ROJO_OFF,
	kLEER_TEMP,
	kLEER_LUZ,
	kATI,
	kAT_CPIN,
	kAT_CREG
};

enum lista_ec25_respuesta_at {
	kRespATI = 0,
	kRespAT_CPIN,
	kRespAT_CREG
};

#define numero_comandos_control 9
const char *comandos_control[] = {
		"LED_VERDE_ON", //ENCIENDE LED VERDE
		"LED_VERDE_OFF",//APAGA LED VERDE
		"LED_ROJO_ON", //ENCIENDE LED ROJO
		"LED_ROJO_OFF",//APAGA LED ROJO
		"LEER_TEMP", //ENCIENDE LED VERDE
		"LEER_LUZ",//APAGA LED VERDE
		"ATI",//consulta informacion del modem
		"AT+CPIN?",//consulta estado de la simcard
		"AT+CREG?",//consulta estado de la red celular y tecnologia usada en red celular
};

#define numero_respuestas_AT 3
const char *lista_ec25_respuesta_at[] = {
		"Quectel EC25 Revision: EC25EFAR02A09M4G OK",
		"+CPIN: <code> OK",
		"+CREG: <n>,<stat>[,<lac>,<ci>[,<Act>]] OK",
};


char buffer_nuevo_comando_recibido[50];
uint32_t index_buffer_nuevo_comando_recibido = 0;


/*
 * @brief   Application entry point.
 */
//Funcion que cuenta encendido led verde

void limpiar_buffer_comando(){
	for (int var = 0; var < 50; ++var) {
		buffer_nuevo_comando_recibido[var] = 0x00;
	}
	index_buffer_nuevo_comando_recibido = 0;
}

int main(void) {
	float ADC_SenLuz, ADC_SenTemp;
	uint8_t nuevoByteLPUART0;
	bool boton1,boton2;
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();
#endif
    printf("K32L2B31 Iniciando......\r\n");
    LPTMR_StartTimer(LPTMR0);
    while(1) {
//    	if (lpuart0_irq_counter != 0){
//    		printf("dato %c , 0x%x \r\n\r\n", dato_lpuart0, dato_lpuart0);
//    		lpuart0_irq_counter = 0;
//    	}
    	if (numerodebytedisponiblesenbuffer() != 0) {
    		nuevoByteLPUART0 = sacarByteBuffCir();
    		buffer_nuevo_comando_recibido[index_buffer_nuevo_comando_recibido] = nuevoByteLPUART0;
    		index_buffer_nuevo_comando_recibido++;
    		char *puntero_ok;

    		if (nuevoByteLPUART0 == '\n') {
				for (int var = 0; var < numero_comandos_control; ++var) {
					puntero_ok = (char*)(strstr((char*)(&buffer_nuevo_comando_recibido[0]), (char*)(comandos_control[var])));
					if (puntero_ok != 0){
						switch (var) {
							case kLED_VERDE_ON:
								led_on_green();
								break;
							case kLED_VERDE_OFF:
								led_off_green();
								break;
							case kLED_ROJO_ON:
								led_on_red();
								break;
							case kLED_ROJO_OFF:
								led_off_red();
								break;
							case kLEER_TEMP:
								ADC_SenTemp = SenTempObtenerDatoCenti();
								printf("Sensor de temperatura = %f grados C \r\n", ADC_SenTemp);
								break;
							case kLEER_LUZ:
								ADC_SenLuz = SenLuzObtenerDatoLux();
								printf("Sensor de luz - Lux = %f \r\n", ADC_SenLuz);
								break;
							case kATI:
								printf("%s \r\n", comandos_control[kATI]);
								break;
							case kAT_CPIN:
								printf("%s \r\n", comandos_control[kAT_CPIN]);
								break;
							case kAT_CREG:
								printf("%s \r\n", comandos_control[kAT_CREG]);
								break;
							default:
								break;
						}
					}
				}
				puntero_ok = 0;
				for (int var = 0; var < numero_respuestas_AT; ++var) {
					puntero_ok = (char*)(strstr((char*)(&buffer_nuevo_comando_recibido[0]), (char*)(lista_ec25_respuesta_at[var])));
					if (puntero_ok != 0){
						switch (var) {
							case kRespATI:
								printf("Comando ATI OK \r\n");
								break;
							case kRespAT_CPIN:
								printf("Comando AT+CPIN? OK \r\n");
								break;
							case kRespAT_CREG:
								printf("Comando AT+CREG? OK \r\n");
								break;
							default:
								break;
						}
					}
				}
				limpiar_buffer_comando();
			}
		}
    	boton1 = boton1LeerEstado();
    	boton2 = boton2LeerEstado();
    	if (boton2 == false && lptmr0_irqCounter != 0) {
    		printf("Boton 2 \r\n");
    		lptmr0_irqCounter = 0;
    	}
    	if (boton1 == false && lptmr0_irqCounter != 0) {
    	    printf("Boton 1 \r\n");
			lptmr0_irqCounter = 0;
    	}
    }
    return 0 ;
}
