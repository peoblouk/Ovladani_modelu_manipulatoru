// ===============================
// can_communication.h
// ===============================

#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H
#include "config.h"   // Configuration


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "driver/can.h"

void can_init(void);
//void can_send_message(can_message_t *msg);
void can_receive_task(void *arg);

#endif // CAN_COMMUNICATION_H