// ===============================
// uart_receive.h
// ===============================
#ifndef UART_RECEIVE
#define UART_RECEIVE

#include "driver/uart.h"
#include "esp_log.h"
#include "robot_io.h"
#include <string.h>

// ===============================
// UART RECEIVE CONFIG
// ===============================
#define UART_PORT_NUM      UART_NUM_1
#define UART_TX_PIN        GPIO_NUM_10
#define UART_RX_PIN        GPIO_NUM_9
#define UART_BAUD_RATE     115200
#define BUF_SIZE           256

// ===============================
// FUNCTION PROTOTYPES
// ===============================
void uart1_init(void);
void uart_cmd_task(void *arg);

#endif // UART_RECEIVE