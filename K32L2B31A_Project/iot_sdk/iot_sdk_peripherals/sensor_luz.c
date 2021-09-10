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

uint32_t SenLuzObtenerDatoADC(void){
	SenLuzIniciarCap();
	SenLuzEsperarResult();
	uint32_t resultadoADC;
	resultadoADC = ADC16_GetChannelConversionValue(SenLuz_ADC16_BASE, SenLuz_ADC16_CHANNEL_GROUP);
 	return(resultadoADC);
}

 
