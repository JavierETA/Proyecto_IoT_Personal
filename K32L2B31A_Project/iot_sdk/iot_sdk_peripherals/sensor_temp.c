/*! @file : sensor_temp.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para sensor de temperatura
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensor_temp.h"
#include "peripherals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
//Inicia captura por ADC de voltaje generado por sensor de temperatura
 void SenTempIniciarCap(void);
//-----------------------------------------------------------------------------
//Espera que el ADC obtenga el resultado
 void SenTempEsperarResult(void);


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
 void SenTempIniciarCap(void){
      ADC16_SetChannelConfig(SenTemp_ADC16_BASE, SenTemp_ADC16_CHANNEL_GROUP, & ADC0_channelsConfig[1]);

  }

  void SenTempEsperarResult(void){
  	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(SenTemp_ADC16_BASE, SenTemp_ADC16_CHANNEL_GROUP))){
  	}
  }


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/

  float SenTempObtenerDatoCenti(void){
  	SenTempIniciarCap();
  	SenTempEsperarResult();
  	uint32_t resultadoADC;
  	float Temp, voltajeADC, m;
  	resultadoADC = ADC16_GetChannelConversionValue(SenTemp_ADC16_BASE, SenTemp_ADC16_CHANNEL_GROUP);
  	voltajeADC = (3.0*resultadoADC)/4095;
  	if(voltajeADC>=0.716){
  	 	m = 1.646;
  	}else{
  	 	m = 1.769;
  	}
  	Temp = 25 - ((voltajeADC - 0.716)/m);
   	return(Temp);
  }
