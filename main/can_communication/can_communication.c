#include "can_communication.h"

void can_init(void) {
    // Initialize CAN hardware
}

void can_receive_task(void *arg) {
    while (1) {
        // Receive CAN messages
        //vTaskDelay(pdMS_TO_TICKS(100));
    }
}
