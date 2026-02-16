#ifndef UART_H
#define UART_H

#include <stdint.h>
typedef volatile uint32_t uart_reg_t;
/* Register Size Selection */
#if {{REGISTER_SIZE}} == 8
typedef volatile uint8_t uart_reg_t;
#elif {{REGISTER_SIZE}} == 16
typedef volatile uint16_t uart_reg_t;
#elif {{REGISTER_SIZE}} == 32
typedef volatile uint32_t uart_reg_t;
#else
#error "Unsupported register size"
#endif

/* Base Address */
#define UART_BASE_ADDRESS {{BASE_ADDRESS}}

/* Register Offsets */
#define UART_CTRL_OFFSET   {{CTRL_OFFSET}}
#define UART_FRAME_OFFSET  {{FRAME_OFFSET}}
#define UART_BAUD_OFFSET   {{BAUD_OFFSET}}
#define UART_STATUS_OFFSET {{STATUS_OFFSET}}
#define UART_DATA_OFFSET   {{DATA_OFFSET}}

/* Register Access */
#define UART_REG(addr) (*(uart_reg_t *)(addr))

#define UART_CTRL   UART_REG(UART_BASE_ADDRESS + UART_CTRL_OFFSET)
#define UART_FRAME  UART_REG(UART_BASE_ADDRESS + UART_FRAME_OFFSET)
#define UART_BAUD   UART_REG(UART_BASE_ADDRESS + UART_BAUD_OFFSET)
#define UART_STATUS UART_REG(UART_BASE_ADDRESS + UART_STATUS_OFFSET)
#define UART_DATA   UART_REG(UART_BASE_ADDRESS + UART_DATA_OFFSET)

/* Function Prototypes */
extern void uart_init(uint32_t baud_value);
extern void uart_transmit(uint16_t data);
extern uint16_t uart_receive(void);
extern void uart_irq_handler(void);

#endif
