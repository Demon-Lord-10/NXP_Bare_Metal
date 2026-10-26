#include "uart.h"
#include "clock.h"
#include "gpio.h"
#include <stdint.h>


void UART_SetBaudRate(LPUART_Type *uart, uint32_t baudrate, uint32_t src_clock_hz)
{
    uint32_t best_osr = 16;
    uint32_t best_sbr = 1;
    uint32_t min_diff = 0xFFFFFFFF;

    /* Search OSR from 4 to 32 to minimize baud rate error */
    for (uint32_t osr = 4; osr <= 32; osr++) {
        uint32_t sbr = (src_clock_hz + (baudrate * osr / 2U)) / (baudrate * osr);
        if (sbr == 0) sbr = 1;
        if (sbr > 8191) sbr = 8191;

        uint32_t actual_baud = src_clock_hz / (osr * sbr);
        uint32_t diff = (actual_baud > baudrate) ? (actual_baud - baudrate) : (baudrate - actual_baud);

        if (diff < min_diff) {
            min_diff = diff;
            best_osr = osr;
            best_sbr = sbr;
        }
    }

    /* Disable TX/RX before modifying BAUD register */
    uart->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);

    uint32_t baud_reg = LPUART_BAUD_OSR(best_osr - 1) | LPUART_BAUD_SBR(best_sbr);
    /* For OSR between 4x and 7x, BOTHEDGE sampling is required by hardware */
    if (best_osr < 8) {
        baud_reg |= LPUART_BAUD_BOTHEDGE_MASK;
    }

    uart->BAUD = baud_reg;
    uart->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
}

void UART_Init(LPUART_Type *uart){

    //Choose a known clock for baud rate calc
    /* 1. Unlock MRCC */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    if (uart == LPUART0) {
        /* Select FRO_12M (12 MHz) and Divider = 1 (Divide by DIV + 1, HALT = 0) */
        MRCC0->MRCC_LPUART0_CLKSEL = 0u; // 0 = FRO_12M (12 MHz)
        MRCC0->MRCC_LPUART0_CLKDIV = 0u; // 0 = Divide by 1
    }
    else if (uart == LPUART1) {
        MRCC0->MRCC_LPUART1_CLKSEL = 0u;
        MRCC0->MRCC_LPUART1_CLKDIV = 0u;
    }
    else if (uart == LPUART2) {
        MRCC0->MRCC_LPUART2_CLKSEL = 0u;
        MRCC0->MRCC_LPUART2_CLKDIV = 0u;
    }

    /* 2. Re-lock MRCC */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;

    if(uart == LPUART0){
        MRCC_Enable(0u, MRCC_MRCC_GLB_CC0_LPUART0_MASK | MRCC_MRCC_GLB_CC0_PORT0_MASK);
        PORT0->PCR[2u] = PORT_PCR_MUX(2u) | PORT_PCR_IBE(1u);   //RX
        PORT0->PCR[3u] = PORT_PCR_MUX(2u);                      //TX
    }
    else if(uart == LPUART1){
        MRCC_Enable(0u, MRCC_MRCC_GLB_CC0_LPUART1_MASK | MRCC_MRCC_GLB_CC0_PORT2_MASK);
        PORT2->PCR[12u] = PORT_PCR_MUX(3u) | PORT_PCR_IBE(1u);   //RX
        PORT2->PCR[13u] = PORT_PCR_MUX(3u);                      //TX
    }
    else if(uart == LPUART2){
        MRCC_Enable(0u, MRCC_MRCC_GLB_CC0_LPUART2_MASK);
        MRCC_Enable(1u, MRCC_MRCC_GLB_CC1_PORT3_MASK);
        PORT3->PCR[14u] = PORT_PCR_MUX(2u) | PORT_PCR_IBE(1u);   //RX
        PORT3->PCR[15u] = PORT_PCR_MUX(2u);                      //TX
    }

    UART_SetBaudRate(uart,115200u,12000000u);

}

void UART_SendChar(LPUART_Type *uart, char c){
    while (!(uart->STAT & LPUART_STAT_TDRE_MASK));
    uart->DATA = (uint32_t)c;
}

void UART_Send(LPUART_Type *uart, const char *buff, const uint32_t len){
    for(uint32_t i = 0; i < len ; i++){
        if(buff[i] == '\n') UART_SendChar(uart, '\r');
        UART_SendChar(uart, buff[i]);
    }

}

char UART_RecvChar(LPUART_Type *uart){
    /* If overrun error occurs, clear it so RX doesn't freeze */
    if (uart->STAT & LPUART_STAT_OR_MASK) {
        uart->STAT |= LPUART_STAT_OR_MASK;
    }

    /* Wait until a character arrives */
    while ((uart->STAT & LPUART_STAT_RDRF_MASK) == 0) {}

    /* Read byte (reading DATA automatically clears RDRF) */
    return (char)(uart->DATA & 0xFF);
}

void UART_Recv(LPUART_Type *uart, char *buff, const uint32_t len){

    if (buff == 0 || len == 0) return;
    uint32_t i = 0;
    while (i < (len - 1)) {
        char c = UART_RecvChar(uart);
        /* Stop if we receive Null, Carriage Return, or Newline */
        if (c == '\0' || c == '\r' || c == '\n') {
            break;
        }
        buff[i++] = c;
    }
    /* Guarantee the string in memory is null-terminated */
    buff[i] = '\0';
}

void UART_Printf(LPUART_Type *uart, const char *buff, ...){
    va_list arg;
    va_start(arg,buff);

    int32_t d;
    char c;
    char *s;

    while(*buff){
        if(*buff == '%'){
            buff++;
            if(*buff == '\0') break;
        switch(*buff){
            case 's':
                s = va_arg(arg,char*);
                while(*s != '\0'){
                    UART_SendChar(uart, *s);
                    s++;
                }
                break;

            case 'c':
                c = va_arg(arg,char);
                UART_SendChar(uart, c);
                break;

            case 'd':
                d = va_arg(arg,int32_t);
                char buffer[MAX];
                uint32_t len = itoa(buffer , d);
                UART_Send(uart, buffer , len);
                break;
            case '%':
                UART_SendChar(uart, '%');
                break;
            default:
                break;
        }
        buff++;
        }
        else{
            UART_SendChar(uart , *buff++);
        }
    }
    va_end(arg);
    UART_SendChar(uart,'\r');
    UART_SendChar(uart,'\n');

}


uint32_t itoa(char* buff,int32_t d){
    uint32_t i = 0;
    uint32_t j = 0;

    unsigned int uval; 

    // Determine sign and get absolute value safely using unsigned
    int sign = d;
    if (sign < 0) {
        uval = (unsigned int)(-d); 
    } else {
        uval = (unsigned int)d;
    }

    // Generate digits in reverse order
    do {
        buff[i++] = (char)(uval % 10 + '0');
    } while ((uval /= 10) > 0);

    if (sign < 0) {
        buff[i++] = '-';
    }

    buff[i] = '\0';
    uint32_t x = i;
    i--;
    while(j < i){
        buff[i] = buff[i]^buff[j];
        buff[j] = buff[i]^buff[j];
        buff[i] = buff[i]^buff[j];
        --i,j++;
    }

    return x;
}

