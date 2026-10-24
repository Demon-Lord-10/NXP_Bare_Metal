#include "utick.h"
#include "clock.h"
#include <stdint.h>


void Utick_Init(){
    MRCC_Enable(0u, MRCC_MRCC_GLB_RST0_UTICK0_MASK); //bit 6
}

void delay_us(uint32_t us) {
    if (us < 2u) us = 2u;

    //Load the value to count downwards
    UTICK0->CTRL = (us - 1u);

    //Wait until timer turns ACTIVE (1)
    while (!(UTICK0->STAT & UTICK_STAT_ACTIVE_MASK));

    // just check if it becomes inactive
    while (UTICK0->STAT & UTICK_STAT_ACTIVE_MASK);
}



