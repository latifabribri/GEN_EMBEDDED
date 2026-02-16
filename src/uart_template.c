#include "uart_template.h"

/* =============================== */
/* Internal Bit Manipulation       */
/* =============================== */

static void write_field(uart_reg_t *reg,
                        uint32_t position,
                        uint32_t width,
                        uint32_t value)
{
    uint32_t mask = ((1U << width) - 1U) << position;
    *reg = (*reg & ~mask) | ((value << position) & mask);
}

static uint32_t read_field(uart_reg_t *reg,
                           uint32_t position,
                           uint32_t width)
{
    uint32_t mask = ((1U << width) - 1U);
    return ((*reg >> position) & mask);
}

/* =============================== */
/* UART Initialization             */
/* =============================== */

void uart_init(uint32_t baud_value)
{
    /* Disable UART */
    write_field(&UART_CTRL,
                {{CTRL_UART_ENABLE_POS}},
                {{CTRL_UART_ENABLE_WIDTH}},
                0);

    /* Set Baud Rate */
    write_field(&UART_BAUD,
                {{BAUD_DIV_POS}},
                {{BAUD_DIV_WIDTH}},
                baud_value);

    /* Enable TX */
    write_field(&UART_CTRL,
                {{CTRL_TX_ENABLE_POS}},
                {{CTRL_TX_ENABLE_WIDTH}},
                1);

    /* Enable RX */
    write_field(&UART_CTRL,
                {{CTRL_RX_ENABLE_POS}},
                {{CTRL_RX_ENABLE_WIDTH}},
                1);

    /* Enable UART */
    write_field(&UART_CTRL,
                {{CTRL_UART_ENABLE_POS}},
                {{CTRL_UART_ENABLE_WIDTH}},
                1);
}

/* =============================== */
/* UART Transmit (Polling)         */
/* =============================== */

void uart_transmit(uint16_t data)
{
    /* Wait until TX empty */
    while (!read_field(&UART_STATUS,
                       {{STATUS_TX_EMPTY_POS}},
                       1));

    /* Write Data */
    write_field(&UART_DATA,
                {{DATA_POS}},
                {{DATA_WIDTH}},
                data);
}

/* =============================== */
/* UART Receive (Polling)          */
/* =============================== */

uint16_t uart_receive(void)
{
    /* Wait until RX not empty */
    while (!read_field(&UART_STATUS,
                       {{STATUS_RXNE_POS}},
                       1));

    return read_field(&UART_DATA,
                      {{DATA_POS}},
                      {{DATA_WIDTH}});
}

/* =============================== */
/* UART Interrupt Handler          */
/* =============================== */

void uart_irq_handler(void)
{
    /* RX Interrupt */
    if (read_field(&UART_STATUS,
                   {{STATUS_RXNE_POS}},
                   1))
    {
        uint16_t data = read_field(&UART_DATA,
                                   {{DATA_POS}},
                                   {{DATA_WIDTH}});

        /* User can override this section */
        (void)data;
    }

    /* Optional: Overrun error handling */
    if (read_field(&UART_STATUS,
                   {{STATUS_ORE_POS}},
                   1))
    {
        /* Clear error if required by hardware */
    }
}
