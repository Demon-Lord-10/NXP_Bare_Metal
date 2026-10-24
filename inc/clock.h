#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

/* ============================================================================
 * SCG (System Clock Generator) Register Definition
 * Reference Manual: Chapter 22 (Base Address: 0x4008F000)
 * ============================================================================ */
typedef struct {
    volatile const uint32_t VERID;       /**< 0x00: Version ID */
    volatile const uint32_t PARAM;       /**< 0x04: Parameter */
    volatile uint32_t TRIM_LOCK;         /**< 0x08: Trim Lock */
    uint8_t RESERVED_0[4];               /**< 0x0C */
    volatile const uint32_t CSR;         /**< 0x10: Clock Status Register */
    volatile uint32_t RCCR;              /**< 0x14: Run Clock Control Register */
    uint8_t RESERVED_1[232];             /**< 0x18 - 0xFF */
    volatile uint32_t SOSCCSR;           /**< 0x100: SOSC Control Status */
    uint8_t RESERVED_2[4];               /**< 0x104 */
    volatile uint32_t SOSCCFG;           /**< 0x108: SOSC Configuration */
    uint8_t RESERVED_3[244];             /**< 0x10C - 0x1FF */
    volatile uint32_t SIRCCSR;           /**< 0x200: SIRC Control Status */
    uint8_t RESERVED_4[8];               /**< 0x204 - 0x20B */
    volatile uint32_t SIRCTCFG;          /**< 0x20C: SIRC Trim Configuration */
    uint8_t RESERVED_5[8];               /**< 0x210 - 0x217 */
    volatile uint32_t SIRCSTAT;          /**< 0x218: SIRC Auto-trimming Status */
    uint8_t RESERVED_6[228];             /**< 0x21C - 0x2FF */
    volatile uint32_t FIRCCSR;           /**< 0x300: FIRC Control Status */
    uint8_t RESERVED_7[4];               /**< 0x304 */
    volatile uint32_t FIRCCFG;           /**< 0x308: FIRC Configuration */
    volatile uint32_t FIRCTCFG;          /**< 0x30C: FIRC Trim Configuration */
    volatile uint32_t FIRCTRIM;          /**< 0x310: FIRC Trim */
    uint8_t RESERVED_8[4];               /**< 0x314 */
    volatile uint32_t FIRCSTAT;          /**< 0x318: FIRC Auto-trimming Status */
    uint8_t RESERVED_9[228];             /**< 0x31C - 0x3FF */
    volatile uint32_t ROSCCSR;           /**< 0x400: ROSC Control Status */
} SCG_Type;

#define SCG0_BASE                        (0x4008F000u)
#define SCG0                             ((SCG_Type *)SCG0_BASE)

/* SCG Bitfields & Masks */
#define SCG_CSR_SCS_MASK                 (0x7000000U)
#define SCG_CSR_SCS_SHIFT                (24U)
#define SCG_CSR_SCS(x)                   ((((uint32_t)(x)) << SCG_CSR_SCS_SHIFT) & SCG_CSR_SCS_MASK)

#define SCG_RCCR_SCS_MASK                (0x7000000U)
#define SCG_RCCR_SCS_SHIFT               (24U)
#define SCG_RCCR_SCS(x)                  ((((uint32_t)(x)) << SCG_RCCR_SCS_SHIFT) & SCG_RCCR_SCS_MASK)

#define SCG_FIRCCSR_FIRCEN_MASK          (0x1U)
#define SCG_FIRCCSR_FIRCSTEN_MASK        (0x2U)
#define SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK (0x10U)
#define SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK (0x20U)
#define SCG_FIRCCSR_LK_MASK              (0x800000U)
#define SCG_FIRCCSR_FIRCVLD_MASK         (0x1000000U)
#define SCG_FIRCCSR_FIRCSEL_MASK         (0x2000000U)
#define SCG_FIRCCSR_FIRCERR_MASK         (0x4000000U)

#define SCG_FIRCCFG_FREQ_SEL_MASK        (0xEU)
#define SCG_FIRCCFG_FREQ_SEL_SHIFT       (1U)
#define SCG_FIRCCFG_FREQ_SEL(x)          ((((uint32_t)(x)) << SCG_FIRCCFG_FREQ_SEL_SHIFT) & SCG_FIRCCFG_FREQ_SEL_MASK)

/* ============================================================================
 * MRCC (Module Reset and Clock Control) Register Definition
 * Reference Manual: Chapter 14 (Base Address: 0x40091000)
 * ============================================================================ */
typedef struct {
    volatile uint32_t MRCC_GLB_RST0;     /**< 0x00: Reset Control 0 */
    volatile uint32_t MRCC_GLB_RST0_SET; /**< 0x04: Reset Control Set 0 (Write 1 to set) */
    volatile uint32_t MRCC_GLB_RST0_CLR; /**< 0x08: Reset Control Clear 0 */
    uint8_t RESERVED_0[4];               /**< 0x0C */
    volatile uint32_t MRCC_GLB_RST1;     /**< 0x10: Reset Control 1 */
    volatile uint32_t MRCC_GLB_RST1_SET; /**< 0x14: Reset Control Set 1 (Write 1 to set) */
    volatile uint32_t MRCC_GLB_RST1_CLR; /**< 0x18: Reset Control Clear 1 */
    uint8_t RESERVED_1[36];              /**< 0x1C - 0x3F */
    volatile uint32_t MRCC_GLB_CC0;      /**< 0x40: Clock Control 0 */
    volatile uint32_t MRCC_GLB_CC0_SET;  /**< 0x44: Clock Control Set 0 (Write 1 to set) */
    volatile uint32_t MRCC_GLB_CC0_CLR;  /**< 0x48: Clock Control Clear 0 */
    uint8_t RESERVED_2[4];               /**< 0x4C */
    volatile uint32_t MRCC_GLB_CC1;      /**< 0x50: Clock Control 1 */
    volatile uint32_t MRCC_GLB_CC1_SET;  /**< 0x54: Clock Control Set 1 (Write 1 to set) */
    volatile uint32_t MRCC_GLB_CC1_CLR;  /**< 0x58: Clock Control Clear 1 */
} MRCC_Type;

#define MRCC0_BASE                       (0x40091000u)
#define MRCC0                            ((MRCC_Type *)MRCC0_BASE)

/* ============================================================================
 * MRCC Peripheral Reset Masks (MRCC_GLB_RST0 & MRCC_GLB_RST1)
 * Write 1 to release peripheral from reset (e.g. MRCC0->MRCC_GLB_RST0_SET = MASK)
 * ============================================================================ */

/* --- MRCC_GLB_RST0 (Offset 0x00) --- */
#define MRCC_MRCC_GLB_RST0_INPUTMUX0_MASK (0x1U)        /* Bit 0 */
#define MRCC_MRCC_GLB_RST0_I3C0_MASK      (0x2U)        /* Bit 1 */
#define MRCC_MRCC_GLB_RST0_CTIMER0_MASK   (0x4U)        /* Bit 2 */
#define MRCC_MRCC_GLB_RST0_CTIMER1_MASK   (0x8U)        /* Bit 3 */
#define MRCC_MRCC_GLB_RST0_CTIMER2_MASK   (0x10U)       /* Bit 4 */
#define MRCC_MRCC_GLB_RST0_FREQME_MASK    (0x20U)       /* Bit 5 */
#define MRCC_MRCC_GLB_RST0_UTICK0_MASK    (0x40U)       /* Bit 6 */
#define MRCC_MRCC_GLB_RST0_DMA_MASK       (0x100U)      /* Bit 8 */
#define MRCC_MRCC_GLB_RST0_AOI0_MASK      (0x200U)      /* Bit 9 */
#define MRCC_MRCC_GLB_RST0_CRC_MASK       (0x400U)      /* Bit 10 */
#define MRCC_MRCC_GLB_RST0_EIM_MASK       (0x800U)      /* Bit 11 */
#define MRCC_MRCC_GLB_RST0_ERM_MASK       (0x1000U)     /* Bit 12 */
#define MRCC_MRCC_GLB_RST0_LPI2C0_MASK    (0x10000U)    /* Bit 16 */
#define MRCC_MRCC_GLB_RST0_LPSPI0_MASK    (0x20000U)    /* Bit 17 */
#define MRCC_MRCC_GLB_RST0_LPSPI1_MASK    (0x40000U)    /* Bit 18 */
#define MRCC_MRCC_GLB_RST0_LPUART0_MASK   (0x80000U)    /* Bit 19 */
#define MRCC_MRCC_GLB_RST0_LPUART1_MASK   (0x100000U)   /* Bit 20 */
#define MRCC_MRCC_GLB_RST0_LPUART2_MASK   (0x200000U)   /* Bit 21 */
#define MRCC_MRCC_GLB_RST0_USB0_MASK      (0x400000U)   /* Bit 22 */
#define MRCC_MRCC_GLB_RST0_QDC0_MASK      (0x800000U)   /* Bit 23 */
#define MRCC_MRCC_GLB_RST0_FLEXPWM0_MASK  (0x1000000U)  /* Bit 24 */
#define MRCC_MRCC_GLB_RST0_OSTIMER0_MASK  (0x2000000U)  /* Bit 25 */
#define MRCC_MRCC_GLB_RST0_ADC0_MASK      (0x4000000U)  /* Bit 26 */
#define MRCC_MRCC_GLB_RST0_CMP1_MASK      (0x10000000U) /* Bit 28 */
#define MRCC_MRCC_GLB_RST0_PORT0_MASK     (0x20000000U) /* Bit 29 */
#define MRCC_MRCC_GLB_RST0_PORT1_MASK     (0x40000000U) /* Bit 30 */
#define MRCC_MRCC_GLB_RST0_PORT2_MASK     (0x80000000U) /* Bit 31 */

/* --- MRCC_GLB_RST1 (Offset 0x10) --- */
#define MRCC_MRCC_GLB_RST1_PORT3_MASK     (0x1U)        /* Bit 0 */
#define MRCC_MRCC_GLB_RST1_GPIO0_MASK     (0x20U)       /* Bit 5 */
#define MRCC_MRCC_GLB_RST1_GPIO1_MASK     (0x40U)       /* Bit 6 */
#define MRCC_MRCC_GLB_RST1_GPIO2_MASK     (0x80U)       /* Bit 7 */
#define MRCC_MRCC_GLB_RST1_GPIO3_MASK     (0x100U)      /* Bit 8 */

/* ============================================================================
 * MRCC Peripheral Clock Gate Masks (MRCC_GLB_CC0 & MRCC_GLB_CC1)
 * Write 1 to enable peripheral clock (e.g. MRCC0->MRCC_GLB_CC0_SET = MASK)
 * ============================================================================ */

/* --- MRCC_GLB_CC0 (Offset 0x40) --- */
#define MRCC_MRCC_GLB_CC0_INPUTMUX0_MASK  (0x1U)        /* Bit 0 */
#define MRCC_MRCC_GLB_CC0_I3C0_MASK       (0x2U)        /* Bit 1 */
#define MRCC_MRCC_GLB_CC0_CTIMER0_MASK    (0x4U)        /* Bit 2 */
#define MRCC_MRCC_GLB_CC0_CTIMER1_MASK    (0x8U)        /* Bit 3 */
#define MRCC_MRCC_GLB_CC0_CTIMER2_MASK    (0x10U)       /* Bit 4 */
#define MRCC_MRCC_GLB_CC0_FREQME_MASK     (0x20U)       /* Bit 5 */
#define MRCC_MRCC_GLB_CC0_UTICK0_MASK     (0x40U)       /* Bit 6 */
#define MRCC_MRCC_GLB_CC0_WWDT0_MASK      (0x80U)       /* Bit 7 */
#define MRCC_MRCC_GLB_CC0_DMA_MASK        (0x100U)      /* Bit 8 */
#define MRCC_MRCC_GLB_CC0_AOI0_MASK       (0x200U)      /* Bit 9 */
#define MRCC_MRCC_GLB_CC0_CRC_MASK        (0x400U)      /* Bit 10 */
#define MRCC_MRCC_GLB_CC0_EIM_MASK        (0x800U)      /* Bit 11 */
#define MRCC_MRCC_GLB_CC0_ERM_MASK        (0x1000U)     /* Bit 12 */
#define MRCC_MRCC_GLB_CC0_LPI2C0_MASK     (0x10000U)    /* Bit 16 */
#define MRCC_MRCC_GLB_CC0_LPSPI0_MASK     (0x20000U)    /* Bit 17 */
#define MRCC_MRCC_GLB_CC0_LPSPI1_MASK     (0x40000U)    /* Bit 18 */
#define MRCC_MRCC_GLB_CC0_LPUART0_MASK    (0x80000U)    /* Bit 19 */
#define MRCC_MRCC_GLB_CC0_LPUART1_MASK    (0x100000U)   /* Bit 20 */
#define MRCC_MRCC_GLB_CC0_LPUART2_MASK    (0x200000U)   /* Bit 21 */
#define MRCC_MRCC_GLB_CC0_USB0_MASK       (0x400000U)   /* Bit 22 */
#define MRCC_MRCC_GLB_CC0_QDC0_MASK       (0x800000U)   /* Bit 23 */
#define MRCC_MRCC_GLB_CC0_FLEXPWM0_MASK   (0x1000000U)  /* Bit 24 */
#define MRCC_MRCC_GLB_CC0_OSTIMER0_MASK   (0x2000000U)  /* Bit 25 */
#define MRCC_MRCC_GLB_CC0_ADC0_MASK       (0x4000000U)  /* Bit 26 */
#define MRCC_MRCC_GLB_CC0_CMP0_MASK       (0x8000000U)  /* Bit 27 */
#define MRCC_MRCC_GLB_CC0_CMP1_MASK       (0x10000000U) /* Bit 28 */
#define MRCC_MRCC_GLB_CC0_PORT0_MASK      (0x20000000U) /* Bit 29 */
#define MRCC_MRCC_GLB_CC0_PORT1_MASK      (0x40000000U) /* Bit 30 */
#define MRCC_MRCC_GLB_CC0_PORT2_MASK      (0x80000000U) /* Bit 31 */

/* --- MRCC_GLB_CC1 (Offset 0x50) --- */
#define MRCC_MRCC_GLB_CC1_PORT3_MASK      (0x1U)        /* Bit 0 */
#define MRCC_MRCC_GLB_CC1_MTR_MASK        (0x4U)        /* Bit 2 */
#define MRCC_MRCC_GLB_CC1_TCU_MASK        (0x8U)        /* Bit 3 */
#define MRCC_MRCC_GLB_CC1_EZRAMC_RAMA_MASK (0x10U)      /* Bit 4 */
#define MRCC_MRCC_GLB_CC1_GPIO0_MASK      (0x20U)       /* Bit 5 */
#define MRCC_MRCC_GLB_CC1_GPIO1_MASK      (0x40U)       /* Bit 6 */
#define MRCC_MRCC_GLB_CC1_GPIO2_MASK      (0x80U)       /* Bit 7 */
#define MRCC_MRCC_GLB_CC1_GPIO3_MASK      (0x100U)      /* Bit 8 */
#define MRCC_MRCC_GLB_CC1_ROMCP_MASK      (0x200U)      /* Bit 9 */

/* ============================================================================
 * SYSCON (System Controller) Register Definition
 * Reference Manual: Chapter 14 (Base Address: 0x40091000)
 * ============================================================================ */
typedef struct {
    uint8_t RESERVED_0[0x3FC];           /**< 0x000 - 0x3FB */
    volatile uint32_t CLKUNLOCK;         /**< 0x3FC: Clock Configuration Unlock */
} SYSCON_Type;

#define SYSCON_BASE                      (0x40091000u)
#define SYSCON                           ((SYSCON_Type *)SYSCON_BASE)

#define SYSCON_CLKUNLOCK_UNLOCK_MASK     (0x1U)

/* ============================================================================
 * FMU (Flash Memory Unit) Register Definition
 * Reference Manual: Chapter 6 (Base Address: 0x40095000)
 * ============================================================================ */
typedef struct {
    volatile uint32_t FSTAT;             /**< 0x00: Flash Status Register */
    volatile uint32_t FCNFG;             /**< 0x04: Flash Configuration Register */
    volatile uint32_t FCTRL;             /**< 0x08: Flash Control Register */
} FMU_Type;

#define FMU0_BASE                        (0x40095000u)
#define FMU0                             ((FMU_Type *)FMU0_BASE)

#define FMU_FCTRL_RWSC_MASK              (0xFU)
#define FMU_FCTRL_RWSC(x)                (((uint32_t)(x)) & FMU_FCTRL_RWSC_MASK)

/* ============================================================================
 * Clock Driver Function Prototypes
 * ============================================================================ */
void MRCC_Enable(uint8_t group, uint32_t mask);
void MRCC_Disable(uint8_t group, uint32_t mask);
void Clock_Init_48MHZ(void);
void Clock_Init_96MHZ(void);
void Clock_Enable_Port(uint8_t port_num);
void Clock_Enable_GPIO(uint8_t gpio_num);

#endif /* CLOCK_H */

