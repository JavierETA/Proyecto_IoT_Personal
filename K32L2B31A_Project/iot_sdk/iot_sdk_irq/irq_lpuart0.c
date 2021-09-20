/*! @file : irq_lpuart0.c
 * @author  JAVIER ELIAS TOBON AYUBB
 * @version 1.0.0
 * @date    16/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "irq_lpuart0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void agregarNuevoByteBuffCir(uint8_t nuevoByte);

/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
volatile uint8_t rx_ring_buffer[RX_RING_BUFFER_SIZE];
volatile uint32_t rx_index_productor = 0;
volatile uint32_t rx_index_consumidor = 0;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void agregarNuevoByteBuffCir(uint8_t nuevoByte) {
	  //verifica que exista espacio de memoria disponible para almacenar nueva informacion
	  //incluye correcion del buffer circular
	  if (((rx_index_productor + 1) % RX_RING_BUFFER_SIZE) != rx_index_consumidor){
		  //si tiene espacio disponible, almacena nuevo byte
		  rx_ring_buffer[rx_index_productor] = nuevoByte;
		  rx_index_productor++;
		  rx_index_productor %= RX_RING_BUFFER_SIZE;
	  }
}
/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
 uint32_t intStatus;
 /* Reading all interrupt flags of status registers */
 intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL);
 uint8_t nuevo_dato_uart;

 /* Place your code here */
 if ((kLPUART_RxDataRegFullFlag) & intStatus)
 {
	  nuevo_dato_uart = LPUART_ReadByte(LPUART0);
	  agregarNuevoByteBuffCir(nuevo_dato_uart);
 }

 /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
    Store immediate overlapping exception return operation might vector to incorrect interrupt. */
 #if defined __CORTEX_M && (__CORTEX_M == 4U)
   __DSB();
 #endif
}
/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
uint8_t sacarByteBuffCir(){
	uint8_t ByteReturn;
	if (rx_index_productor != rx_index_consumidor){
		ByteReturn = rx_ring_buffer[rx_index_consumidor];
		rx_index_consumidor++;
		rx_index_consumidor %= RX_RING_BUFFER_SIZE;
	}
	return(ByteReturn);
}

uint32_t numerodebytedisponiblesenbuffer(){
	return((uint32_t)(rx_index_productor-rx_index_consumidor));
}
