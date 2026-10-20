#include "gpio.h"

void GPIO_PinInit(GPIO_Type *base, PORT_Type *port, uint32_t pin, uint8_t dir) {
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
