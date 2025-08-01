#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <iostream>
#include <atomic>

const uint LED1_PIN = 0;
const uint LED2_PIN = 1;
const uint BUTTON_PIN = 2;

std::atomic<bool> paused(false);
bool led1_state = false;
bool led2_state = false;

void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        paused = !paused;
        std::cout << (paused ? "PAUSED\n" : "RESUMED\n");
    }
}

int main() {

    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);

    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (true) {
        if (!paused) {
            led1_state = !led1_state;
            gpio_put(LED1_PIN, led1_state);
            std::cout << "LED1 " << (led1_state ? "ON\n" : "OFF\n");

            for (int i = 0; i < 2; ++i) {
                led2_state = !led2_state;
                gpio_put(LED2_PIN, led2_state);
                std::cout << "LED2 " << (led2_state ? "ON\n" : "OFF\n");
                sleep_ms(250);
            }
        } else {
            gpio_put(LED1_PIN, 0);
            gpio_put(LED2_PIN, 0);
        }

        sleep_ms(500);
    }
}
