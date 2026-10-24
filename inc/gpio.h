#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* ============================================================================
 * PORT (Port Control) Register Definition
 * Reference Manual: Chapter 11 (Base: 0x400BC000 - 0x400BF000)
 * ============================================================================ */
    typedef struct {
    volatile const uint32_t VERID;       /**< 0x00: Version ID */
    uint8_t RESERVED_0[12];              /**< 0x04 - 0x0F */
    volatile uint32_t GPCLR;             /**< 0x10: Global Pin Control Low */
    volatile uint32_t GPCHR;             /**< 0x14: Global Pin Control High */
    uint8_t RESERVED_1[8];               /**< 0x18 - 0x1F */
    volatile uint32_t CONFIG;            /**< 0x20: Configuration */
    uint8_t RESERVED_2[60];              /**< 0x24 - 0x5F */
    volatile uint32_t CALIB0;            /**< 0x60: Calibration 0 */
    volatile uint32_t CALIB1;            /**< 0x64: Calibration 1 */
    uint8_t RESERVED_3[24];              /**< 0x68 - 0x7F */
    volatile uint32_t PCR[32];           /**< 0x80 - 0xFC: Pin Control 0..31 */
} PORT_Type;

#define PORT0_BASE                       (0x400BC000u)
#define PORT1_BASE                       (0x400BD000u)
#define PORT2_BASE                       (0x400BE000u)
#define PORT3_BASE                       (0x400BF000u)

#define PORT0                            ((PORT_Type *)PORT0_BASE)
#define PORT1                            ((PORT_Type *)PORT1_BASE)
#define PORT2                            ((PORT_Type *)PORT2_BASE)
#define PORT3                            ((PORT_Type *)PORT3_BASE)

/* PORT PCR Bitfield Definitions */
#define PORT_PCR_PS_MASK                 (0x1U)
#define PORT_PCR_PS(x)                   (((uint32_t)(x)) & PORT_PCR_PS_MASK)          /* 0: Pull-Down, 1: Pull-Up */
#define PORT_PCR_PE_MASK                 (0x2U)
#define PORT_PCR_PE(x)                   ((((uint32_t)(x)) << 1U) & PORT_PCR_PE_MASK)  /* 1: Pull Enable */
#define PORT_PCR_SRE_MASK                (0x4U)
#define PORT_PCR_SRE(x)                  ((((uint32_t)(x)) << 2U) & PORT_PCR_SRE_MASK) /* 0: Fast, 1: Slow Slew Rate */
#define PORT_PCR_PFE_MASK                (0x10U)
#define PORT_PCR_PFE(x)                  ((((uint32_t)(x)) << 4U) & PORT_PCR_PFE_MASK) /* 1: Passive Filter Enable */
#define PORT_PCR_ODE_MASK                (0x20U)
#define PORT_PCR_ODE(x)                  ((((uint32_t)(x)) << 5U) & PORT_PCR_ODE_MASK) /* 1: Open Drain Enable */
#define PORT_PCR_DSE_MASK                (0x40U)
#define PORT_PCR_DSE(x)                  ((((uint32_t)(x)) << 6U) & PORT_PCR_DSE_MASK) /* 0: Low Drive, 1: High Drive */
#define PORT_PCR_MUX_MASK                (0xF00U)
#define PORT_PCR_MUX_SHIFT               (8U)
#define PORT_PCR_MUX(x)                  ((((uint32_t)(x)) << PORT_PCR_MUX_SHIFT) & PORT_PCR_MUX_MASK) /* 0: GPIO */
#define PORT_PCR_IBE_MASK                (0x1000U)
#define PORT_PCR_IBE_SHIFT               (12U)
#define PORT_PCR_IBE(x)                  ((((uint32_t)(x)) << PORT_PCR_IBE_SHIFT) & PORT_PCR_IBE_MASK) /* 1: Input Buffer Enable */
#define PORT_PCR_INV_MASK                (0x2000U)
#define PORT_PCR_INV(x)                  ((((uint32_t)(x)) << 13U) & PORT_PCR_INV_MASK)/* 1: Invert Input */
#define PORT_PCR_LK_MASK                 (0x8000U)
#define PORT_PCR_LK(x)                   ((((uint32_t)(x)) << 15U) & PORT_PCR_LK_MASK) /* 1: Lock Register */

/* ============================================================================
 * GPIO (General Purpose Input/Output) Register Definition
 * Reference Manual: Chapter 12 (Base: 0x40102000 - 0x40105000)
 * ============================================================================ */
typedef struct {
    volatile const uint32_t VERID;       /**< 0x00: Version ID */
    volatile const uint32_t PARAM;       /**< 0x04: Parameter */
    uint8_t RESERVED_0[56];              /**< 0x08 - 0x3F */
    volatile uint32_t PDOR;              /**< 0x40: Port Data Output */
    volatile uint32_t PSOR;              /**< 0x44: Port Set Output (Atomic Set) */
    volatile uint32_t PCOR;              /**< 0x48: Port Clear Output (Atomic Clear) */
    volatile uint32_t PTOR;              /**< 0x4C: Port Toggle Output (Atomic Toggle) */
    volatile const uint32_t PDIR;        /**< 0x50: Port Data Input */
    volatile uint32_t PDDR;              /**< 0x54: Port Data Direction */
    volatile uint32_t PIDR;              /**< 0x58: Port Input Disable */
    uint8_t RESERVED_1[4];               /**< 0x5C - 0x5F */
    volatile uint8_t  PDR[32];           /**< 0x60 - 0x7F: Pin Data Byte Array */
    volatile uint32_t ICR[32];           /**< 0x80 - 0xFF: Interrupt Control */
    volatile uint32_t GICLR;             /**< 0x100: Global Interrupt Control Low */
    volatile uint32_t GICHR;             /**< 0x104: Global Interrupt Control High */
    uint8_t RESERVED_2[24];              /**< 0x108 - 0x11F */
    volatile uint32_t ISFR[8];           /**< 0x120 - 0x13F: Interrupt Status Flag */
} GPIO_Type;

#define GPIO0_BASE                       (0x40102000u)
#define GPIO1_BASE                       (0x40103000u)
#define GPIO2_BASE                       (0x40104000u)
#define GPIO3_BASE                       (0x40105000u)

#define GPIO0                            ((GPIO_Type *)GPIO0_BASE)
#define GPIO1                            ((GPIO_Type *)GPIO1_BASE)
#define GPIO2                            ((GPIO_Type *)GPIO2_BASE)
#define GPIO3                            ((GPIO_Type *)GPIO3_BASE)

/* ============================================================================
 * Driver Types & Function Prototypes
 * ============================================================================ */
#define GPIO_PIN_INPUT  0UL
#define GPIO_PIN_OUTPUT 1UL

#define GPIO_PIN_RESET  0UL
#define GPIO_PIN_SET    1UL

void GPIO_PinInit(GPIO_Type *base, PORT_Type *port, uint32_t pin, uint8_t dir);
void GPIO_PinWrite(GPIO_Type *base, uint32_t pin, uint8_t value);
void GPIO_PinToggle(GPIO_Type *base, uint32_t pin);
uint8_t GPIO_PinRead(GPIO_Type *base, uint32_t pin);

#endif /* GPIO_H */

