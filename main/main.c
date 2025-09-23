// ===============================
// main.c
// ===============================

#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_servo_server.h" // Wi-Fi and Servo Control Server
#include "robot_io.h"          // Robotic Arm Kinematics
#include "esp_spiffs.h"
#include <string.h>

static void init_spiffs(void); // Initialize SPIFFS (File System)

void app_main(void)
{
    init_spiffs();
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_servo_server_start(); // Start Wi-Fi and Servo Control Server
    
    servos_init(); // Initialize servos
    sensors_init(); // Initialize sensors
}

static void init_spiffs(void) { // Init File System
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE("SPIFFS", "Failed to mount or format filesystem");
        } 
        else {
            ESP_LOGE("SPIFFS", "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    esp_spiffs_info(NULL, &total, &used);
    ESP_LOGI("SPIFFS", "Partition size: total: %d, used: %d", total, used);
}

/*
// ===============================
// UART COMMAND INTERFACE TASK
#include "driver/uart.h"
#include "esp_vfs_dev.h"

void init_uart_console(void) {
    // Zapne UART0 s driverem, 256 bajtů buffer RX
    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);

    // Přesměruje stdin/stdout na UART
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    // Nastaví rychlost 115200 baud
    uart_set_baudrate(UART_NUM_0, 115200);
}


static void uart_cmd_task(void *arg) {
    char line[64];

    while (fgets(line, sizeof(line), stdin)) {
        char *nl = strchr(line, '\n');
        if (nl) *nl = 0;

        // SERVO <id> <angle>
        int id, ang;
        if (sscanf(line, "SERVO %d %d", &id, &ang) == 2) {
            if (id >= 0 && id < SERVO_COUNT) {
                if (ang < 0) ang = 0;
                if (ang > 180) ang = 180;
                servo_set_angle(id, ang);
                printf("OK SERVO %d %d\n", id, ang);
            } else {
                printf("ERR invalid servo id\n");
            }
            continue;
        }

        // MOVE <x> <y> <z>
        float x, y, z;
        if (sscanf(line, "MOVE %f %f %f", &x, &y, &z) == 3) {
            float q[SERVO_COUNT] = {0};
            inverse_kinematics(x, y, z, q);
            move_to_position(q);
            printf("OK MOVE %.1f %.1f %.1f\n", x, y, z);
            continue;
        }

        // HELP
        if (strcmp(line, "HELP") == 0) {
            printf("Commands:\n");
            printf("  SERVO <id> <angle>\n");
            printf("  MOVE <x> <y> <z>\n");
            printf("  HELP\n");
            continue;
        }

        printf("ERR unknown command. Type HELP\n");
    }

    vTaskDelete(NULL);
} */