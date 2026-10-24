#include "gpio.h"
#include "clock.h"

void GPIO_PinInit(GPIO_Type *base, PORT_Type *port, uint32_t pin, uint8_t dir) {

    uint8_t n = (uint8_t)((uintptr_t)port >> 12) & 3u;   // gives number for each port
    Clock_Enable_Port(n);

    n = (uint8_t)(((uintptr_t)base - GPIO0_BASE) >> 12);
    Clock_Enable_GPIO(n);

    /* 1. Set pin mux to Alternative 0 (GPIO) */
    port->PCR[pin] = PORT_PCR_MUX(0);

    /* 2. Configure direction */
    if (dir == GPIO_PIN_OUTPUT) {
        base->PDDR |= (1UL << pin);
    } else {
        base->PDDR &= ~(1UL << pin);
        /* Enable input buffer for reading , if you dont enable you will read 0 no matter what*/
        port->PCR[pin] |= PORT_PCR_IBE(1);
    }
}

void GPIO_PinWrite(GPIO_Type *base, uint32_t pin, uint8_t value) {
    if (value) {
        base->PSOR = (1UL << pin);
    } else {
        base->PCOR = (1UL << pin);
    }
}

void GPIO_PinToggle(GPIO_Type *base, uint32_t pin) {
    base->PTOR = (1UL << pin);
}

uint8_t GPIO_PinRead(GPIO_Type *base, uint32_t pin) {
    return (base->PDIR >> pin) & 1UL;
}
