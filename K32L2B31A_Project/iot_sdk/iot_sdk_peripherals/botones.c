/*! @file : botones.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para controlar los botones
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "botones.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
bool boton1,boton2;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 bool boton1LeerEstado(void){
	 uint32_t valor_pin;
	 bool resultado;
	 valor_pin = GPIO_PinRead(GPIOC,3);
	 if (valor_pin == 1) {
		resultado = true;
	 } else {
		resultado = false;
	 }
	 return(resultado);
 }
 
 bool boton2LeerEstado(void){
	 uint32_t valor_pin;
	 bool resultado;
	 valor_pin = GPIO_PinRead(GPIOA,4);
	 if (valor_pin == 1) {
		resultado = true;
	 } else {
	 	resultado = false;
	 }
	 return(resultado);
 }

char Boton1_Presionado(void){
   return !boton1;
}

void Key_Task_Init(void){
  	boton1 = 0;
  	boton2 = 0;
 }

void Key_Task_Run(void){
  	boton1=boton1LeerEstado();
  	boton2=boton2LeerEstado();
}
