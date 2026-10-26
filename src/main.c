#include "clock.h"
#include "utick.h"
#include "uart.h"

void Init(){
    Clock_Init_48MHZ();
    UART_Init(LPUART0);
    Utick_Init();
}

int main(void) {

    Init();
    int d = 0xFFFFFFFF;
    while(1){
        UART_Printf(LPUART0,"Hello %d",d);
        delay_us(1000000u);
    }

    return 0;
}
