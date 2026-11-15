#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

/* ARM Cortex-M33 NVIC Base Address */
#define NVIC_BASE                        (0xE000E100UL)

typedef struct {
    volatile uint32_t ISER[16];   /**< 0x000: Interrupt Set-Enable Registers */
    uint32_t RESERVED0[16];
    volatile uint32_t ICER[16];   /**< 0x080: Interrupt Clear-Enable Registers */
    uint32_t RESERVED1[16];
    volatile uint32_t ISPR[16];   /**< 0x100: Interrupt Set-Pending Registers */
    uint32_t RESERVED2[16];
    volatile uint32_t ICPR[16];   /**< 0x180: Interrupt Clear-Pending Registers */
    uint32_t RESERVED3[16];
    volatile uint32_t IABR[16];   /**< 0x200: Interrupt Active Bit Registers */
    uint32_t RESERVED4[48];
    volatile uint8_t  IPR[480];   /**< 0x300: Interrupt Priority Registers (8-bit per IRQ) */
} NVIC_Type;

#define NVIC                             ((NVIC_Type *)NVIC_BASE)

/* Enable an interrupt in the ARM core */
static inline void NVIC_EnableIRQ(uint32_t irq) {
    NVIC->ISER[irq >> 5] = (1UL << (irq & 0x1F));
}

/* Disable an interrupt in the ARM core */
static inline void NVIC_DisableIRQ(uint32_t irq) {
    NVIC->ICER[irq >> 5] = (1UL << (irq & 0x1F));
}

/* Set interrupt priority (0 = highest priority, 7 = lowest priority on MCXA) */
static inline void NVIC_SetPriority(uint32_t irq, uint8_t priority) {
    /* MCXA153 implements 3 bits of priority (bits 7:5 of each byte) */
    NVIC->IPR[irq] = (uint8_t)((priority & 0x07) << 5);
}

#endif /* NVIC_H */
