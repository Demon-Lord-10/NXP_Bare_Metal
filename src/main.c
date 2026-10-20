#include "gpio.h"
#include "clock.h"



int main(void) {
    Clock_Init_48MHZ();
    Clock_Enable_Port(3u);
    Clock_Enable_GPIO(3u);
    GPIO_PinInit(GPIO3, PORT3, 12u, GPIO_PIN_OUTPUT);

    GPIO_PinInit(GPIO3, PORT3, 13u, GPIO_PIN_OUTPUT);

    GPIO_PinWrite(GPIO3, 12u,0);
    GPIO_PinWrite(GPIO3, 13u,0);
    while (1);

    return 0;
}
