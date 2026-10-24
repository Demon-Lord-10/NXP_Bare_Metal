#ifndef UTICK_H
#define UTICK_H

#include <stdint.h>

/* ============================================================================
 * UTICK (Micro-Tick Timer) Register Definition
 * Reference Manual: Chapter 28 (Base Address: 0x4000B000)
 * Clock Source: 1 MHz FRO12M/12 (1 tick = 1 microsecond)
 * ============================================================================ */

typedef struct {
    volatile uint32_t CTRL;              /**< 0x00: Control Register (Resets/loads counter) */
    volatile uint32_t STAT;              /**< 0x04: Status Register (W1C flags, active status) */
    volatile uint32_t CFG;               /**< 0x08: Capture Configuration Register */
    volatile uint32_t CAPCLR;            /**< 0x0C: Capture Clear Register */
    volatile const uint32_t CAP[4];      /**< 0x10 - 0x1C: Capture Registers 0 to 3 */
} UTICK_Type;

/* UTICK Base Address & Peripheral Pointer */
#define UTICK0_BASE                      (0x4000B000u)
#define UTICK0                           ((UTICK_Type *)UTICK0_BASE)

/* UTICK Interrupt Number (NVIC) */
#define UTICK0_IRQn                      (59)

/* UTICK Functional Clock (1 MHz FRO) */
#define UTICK_CLK_FREQ_HZ                (1000000U) /* 1 tick = 1 us */

/* ============================================================================
 * CTRL (Control Register) Bitfields & Masks
 * ============================================================================ */
#define UTICK_CTRL_DELAYVAL_MASK         (0x7FFFFFFFU) /**< Bits 30:0 - Tick interval */
#define UTICK_CTRL_DELAYVAL_SHIFT        (0U)
#define UTICK_CTRL_DELAYVAL(x)           (((uint32_t)(x)) & UTICK_CTRL_DELAYVAL_MASK)

#define UTICK_CTRL_REPEAT_MASK           (0x80000000U) /**< Bit 31 - Repeat delay enable */
#define UTICK_CTRL_REPEAT_SHIFT          (31U)
#define UTICK_CTRL_REPEAT(x)             ((((uint32_t)(x)) << UTICK_CTRL_REPEAT_SHIFT) & UTICK_CTRL_REPEAT_MASK)

#define UTICK_MODE_ONESHOT               (0U)
#define UTICK_MODE_REPEAT                (1U)

/* ============================================================================
 * STAT (Status Register) Bitfields & Masks
 * ============================================================================ */
#define UTICK_STAT_INTR_MASK             (0x1U)        /**< Bit 0 - Interrupt / Timeout pending (Write 1 to clear) */
#define UTICK_STAT_INTR_SHIFT            (0U)
#define UTICK_STAT_INTR(x)               (((uint32_t)(x)) & UTICK_STAT_INTR_MASK)

#define UTICK_STAT_ACTIVE_MASK           (0x2U)        /**< Bit 1 - Timer active flag (Read-only: 1 = running, 0 = stopped) */
#define UTICK_STAT_ACTIVE_SHIFT          (1U)
#define UTICK_STAT_ACTIVE(x)             ((((uint32_t)(x)) << UTICK_STAT_ACTIVE_SHIFT) & UTICK_STAT_ACTIVE_MASK)

/* ============================================================================
 * CFG (Capture Configuration Register) Bitfields & Masks
 * ============================================================================ */
#define UTICK_CFG_CAPEN0_MASK            (0x1U)        /**< Bit 0 - Enable Capture 0 */
#define UTICK_CFG_CAPEN1_MASK            (0x2U)        /**< Bit 1 - Enable Capture 1 */
#define UTICK_CFG_CAPEN2_MASK            (0x4U)        /**< Bit 2 - Enable Capture 2 */
#define UTICK_CFG_CAPEN3_MASK            (0x8U)        /**< Bit 3 - Enable Capture 3 */

#define UTICK_CFG_CAPPOL0_MASK           (0x100U)      /**< Bit 8  - Polarity 0 (0: Positive edge, 1: Negative edge) */
#define UTICK_CFG_CAPPOL1_MASK           (0x200U)      /**< Bit 9  - Polarity 1 (0: Positive edge, 1: Negative edge) */
#define UTICK_CFG_CAPPOL2_MASK           (0x400U)      /**< Bit 10 - Polarity 2 (0: Positive edge, 1: Negative edge) */
#define UTICK_CFG_CAPPOL3_MASK           (0x800U)      /**< Bit 11 - Polarity 3 (0: Positive edge, 1: Negative edge) */

/* ============================================================================
 * CAPCLR (Capture Clear Register) Bitfields & Masks
 * ============================================================================ */
#define UTICK_CAPCLR_CAPCLR0_MASK        (0x1U)        /**< Bit 0 - Clear Capture 0 */
#define UTICK_CAPCLR_CAPCLR1_MASK        (0x2U)        /**< Bit 1 - Clear Capture 1 */
#define UTICK_CAPCLR_CAPCLR2_MASK        (0x4U)        /**< Bit 2 - Clear Capture 2 */
#define UTICK_CAPCLR_CAPCLR3_MASK        (0x8U)        /**< Bit 3 - Clear Capture 3 */

/* ============================================================================
 * CAP (Capture Registers 0-3) Bitfields & Masks
 * ============================================================================ */
#define UTICK_CAP_CAP_VALUE_MASK         (0x7FFFFFFFU) /**< Bits 30:0 - Captured value */
#define UTICK_CAP_VALID_MASK             (0x80000000U) /**< Bit 31 - Valid capture flag */

void Utick_Init();
void delay_us(uint32_t us);

#endif /* UTICK_H */
