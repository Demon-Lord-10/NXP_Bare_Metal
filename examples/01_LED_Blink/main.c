#include "gpio.h"
#include "clock.h"
#include "utick.h"

void Init(){
    Clock_Init_48MHZ();
    GPIO_PinInit(GPIO3, PORT3, 12u, GPIO_PIN_OUTPUT);
    GPIO_PinInit(GPIO3, PORT3, 13u, GPIO_PIN_OUTPUT);
    GPIO_PinInit(GPIO3, PORT3, 0u, GPIO_PIN_OUTPUT);
    Utick_Init();
}

void Red_Led(){
    GPIO_PinToggle(GPIO3,12u);
}

void Green_Led(){
    GPIO_PinToggle(GPIO3,13u);
}

void Blue_Led(){
    GPIO_PinToggle(GPIO3,0);
}

int main(void) {

    Init();

    GPIO_PinWrite(GPIO3, 12u,1);
    GPIO_PinWrite(GPIO3, 13u,1);
    GPIO_PinWrite(GPIO3, 0u,1);


    //note the GPIO is 0 by default since we didnt change GPIO pin 0
    while (1){
        delay_us(1000000u);
        Red_Led();
        delay_us(1000000u);
        Red_Led();
        delay_us(1000000u);
        Green_Led();
        delay_us(1000000u);
        Green_Led();
        delay_us(1000000u);
        Blue_Led();
        delay_us(1000000u);
        Blue_Led();
    }

    return 0;
}
