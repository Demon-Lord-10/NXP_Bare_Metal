#include "i2c.h"
#include "lcd.h"
#include "clock.h"
#include "utick.h"

void Init(void) {
    Clock_Init_48MHZ();
    Utick_Init();
    I2C_Init(LPI2C0);
    lcd_init();
    __asm volatile ("cpsie i");   // Enable interrupts globally in ARM core
}

int main(void) {

    Init();
    lcd_print("Hello World!!");

    while(1){
    }

    return 0;
}
