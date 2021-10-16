/*! @file : sensor_luz.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensor_luz.h"
#include "peripherals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
//Inicia captura por ADC de voltaje generado por sensor de luz
 void SenLuzIniciarCap(void);
//-----------------------------------------------------------------------------
//Espera que el ADC obtenga el resultado
 void SenLuzEsperarResult(void);

/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
 uint32_t adc_sensor_de_luz;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
 void SenLuzIniciarCap(void){
     ADC16_SetChannelConfig(SenLuz_ADC16_BASE, SenLuz_ADC16_CHANNEL_GROUP, & ADC0_channelsConfig[0]);

 }

 void SenLuzEsperarResult(void){
 	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(SenLuz_ADC16_BASE, SenLuz_ADC16_CHANNEL_GROUP))){
 	}
 }

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/

uint32_t SenLuzObtenerDatoLux(void){
	SenLuzIniciarCap();
	SenLuzEsperarResult();
	uint32_t resultadoADC;
	float corrienteADC,Lux;
	resultadoADC = ADC16_GetChannelConversionValue(SenLuz_ADC16_BASE, SenLuz_ADC16_CHANNEL_GROUP);
	corrienteADC = (13513.5 - (3.3*resultadoADC))/40950000;
	Lux = (corrienteADC * 9500)/(0.005);
 	return(resultadoADC);
}


void SensorLuz_Init(void){

}

void SensorLuz_Task_Run(void){
	  adc_sensor_de_luz = SenLuzObtenerDatoLux();
}

 
