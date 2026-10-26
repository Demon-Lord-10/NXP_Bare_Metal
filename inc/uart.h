#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdarg.h>

/* ============================================================================
 * LPUART (Low Power UART) Register Definition
 * Reference Manual: Chapter 38 (Base Address: 0x4009F000 - 0x400A1000)
 * ============================================================================ */

typedef struct {
    volatile const uint32_t VERID;       /**< 0x00: Version ID */
    volatile const uint32_t PARAM;       /**< 0x04: Parameter */
    volatile uint32_t GLOBAL;            /**< 0x08: Global Register */
    volatile uint32_t PINCFG;            /**< 0x0C: Pin Configuration */
    volatile uint32_t BAUD;              /**< 0x10: Baud Rate */
    volatile uint32_t STAT;              /**< 0x14: Status */
    volatile uint32_t CTRL;              /**< 0x18: Control */
    volatile uint32_t DATA;              /**< 0x1C: Data */
    volatile uint32_t MATCH;             /**< 0x20: Match Address */
    volatile uint32_t MODIR;             /**< 0x24: MODEM IrDA */
    volatile uint32_t FIFO;              /**< 0x28: FIFO */
    volatile uint32_t WATER;             /**< 0x2C: Watermark */
    volatile const uint32_t DATARO;      /**< 0x30: Data Read-Only */
} LPUART_Type;

/* LPUART Base Addresses & Peripheral Pointers */
#define LPUART0_BASE                     (0x4009F000u)
#define LPUART1_BASE                     (0x400A0000u)
#define LPUART2_BASE                     (0x400A1000u)

#define LPUART0                          ((LPUART_Type *)LPUART0_BASE)
#define LPUART1                          ((LPUART_Type *)LPUART1_BASE)
#define LPUART2                          ((LPUART_Type *)LPUART2_BASE)

/* LPUART Interrupt Numbers (NVIC) */
#define LPUART0_IRQn                     (31)
#define LPUART1_IRQn                     (32)
#define LPUART2_IRQn                     (33)

/* ============================================================================
 * BAUD (Baud Rate Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_BAUD_SBR_MASK             (0x1FFFU)     /**< Bits 12:0 - Baud rate modulo divisor */
#define LPUART_BAUD_SBR_SHIFT            (0U)
#define LPUART_BAUD_SBR(x)               (((uint32_t)(x)) & LPUART_BAUD_SBR_MASK)

#define LPUART_BAUD_SBNS_MASK            (0x2000U)     /**< Bit 13 - Stop Bit Number Select (0: 1 stop bit, 1: 2 stop bits) */
#define LPUART_BAUD_RXEDGIE_MASK         (0x4000U)     /**< Bit 14 - RX Input Active Edge Interrupt Enable */
#define LPUART_BAUD_LBKDIE_MASK          (0x8000U)     /**< Bit 15 - LIN Break Detect Interrupt Enable */
#define LPUART_BAUD_RESYNCDIS_MASK       (0x10000U)    /**< Bit 16 - Resynchronization Disable */
#define LPUART_BAUD_BOTHEDGE_MASK        (0x20000U)    /**< Bit 17 - Both Edge Sampling (Required for OSR 4x - 7x) */
#define LPUART_BAUD_MATCFG_MASK          (0xC0000U)    /**< Bits 19:18 - Match Configuration */
#define LPUART_BAUD_RIDMAE_MASK          (0x100000U)   /**< Bit 20 - Receiver Idle DMA Enable */
#define LPUART_BAUD_RDMAE_MASK           (0x200000U)   /**< Bit 21 - Receiver Full DMA Enable */
#define LPUART_BAUD_TDMAE_MASK           (0x800000U)   /**< Bit 23 - Transmitter Empty DMA Enable */

#define LPUART_BAUD_OSR_MASK             (0x1F000000U) /**< Bits 28:24 - Oversampling Ratio (3 to 31 -> 4x to 32x) */
#define LPUART_BAUD_OSR_SHIFT            (24U)
#define LPUART_BAUD_OSR(x)               ((((uint32_t)(x)) << LPUART_BAUD_OSR_SHIFT) & LPUART_BAUD_OSR_MASK)

#define LPUART_BAUD_M10_MASK             (0x20000000U) /**< Bit 29 - 10-bit Mode Select */
#define LPUART_BAUD_MAEN2_MASK           (0x40000000U) /**< Bit 30 - Match Address Mode Enable 2 */
#define LPUART_BAUD_MAEN1_MASK           (0x80000000U) /**< Bit 31 - Match Address Mode Enable 1 */

/* ============================================================================
 * STAT (Status Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_STAT_LBKFE_MASK           (0x1U)        /**< Bit 0  - LIN Break Flag Enable */
#define LPUART_STAT_AME_MASK             (0x2U)        /**< Bit 1  - Address Mark Enable */
#define LPUART_STAT_MA2F_MASK            (0x4000U)     /**< Bit 14 - Match 2 Flag (W1C) */
#define LPUART_STAT_MA1F_MASK            (0x8000U)     /**< Bit 15 - Match 1 Flag (W1C) */
#define LPUART_STAT_PF_MASK              (0x10000U)    /**< Bit 16 - Parity Error Flag (W1C) */
#define LPUART_STAT_FE_MASK              (0x20000U)    /**< Bit 17 - Framing Error Flag (W1C) */
#define LPUART_STAT_NF_MASK              (0x40000U)    /**< Bit 18 - Noise Flag (W1C) */
#define LPUART_STAT_OR_MASK              (0x80000U)    /**< Bit 19 - Receiver Overrun Flag (W1C) */
#define LPUART_STAT_IDLE_MASK            (0x100000U)   /**< Bit 20 - Idle Line Flag (W1C) */
#define LPUART_STAT_RDRF_MASK            (0x200000U)   /**< Bit 21 - Receive Data Register Full (1 = data ready) */
#define LPUART_STAT_TC_MASK              (0x400000U)   /**< Bit 22 - Transmission Complete (1 = TX idle) */
#define LPUART_STAT_TDRE_MASK            (0x800000U)   /**< Bit 23 - Transmit Data Register Empty (1 = ready for next byte) */
#define LPUART_STAT_RAF_MASK             (0x1000000U)  /**< Bit 24 - Receiver Active Flag */
#define LPUART_STAT_LBKDE_MASK           (0x2000000U)  /**< Bit 25 - LIN Break Detection Enable */
#define LPUART_STAT_BRK13_MASK           (0x4000000U)  /**< Bit 26 - Break Character Length */
#define LPUART_STAT_RWUID_MASK           (0x8000000U)  /**< Bit 27 - Receive Wake Up Idle Detect */
#define LPUART_STAT_RXINV_MASK           (0x10000000U) /**< Bit 28 - Receive Data Inversion */
#define LPUART_STAT_MSBF_MASK            (0x20000000U) /**< Bit 29 - MSB First */
#define LPUART_STAT_RXEDGIF_MASK         (0x40000000U) /**< Bit 30 - RX Pin Active Edge Interrupt Flag (W1C) */
#define LPUART_STAT_LBKDIF_MASK          (0x80000000U) /**< Bit 31 - LIN Break Detect Interrupt Flag (W1C) */

/* ============================================================================
 * CTRL (Control Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_CTRL_PT_MASK              (0x1U)        /**< Bit 0  - Parity Type (0: Even, 1: Odd) */
#define LPUART_CTRL_PE_MASK              (0x2U)        /**< Bit 1  - Parity Enable (0: Disabled, 1: Enabled) */
#define LPUART_CTRL_ILT_MASK             (0x4U)        /**< Bit 2  - Idle Line Type Select */
#define LPUART_CTRL_WAKE_MASK            (0x8U)        /**< Bit 3  - Receiver Wakeup Method */
#define LPUART_CTRL_M_MASK               (0x10U)       /**< Bit 4  - 9-Bit or 8-Bit Mode Select (0: 8-bit, 1: 9-bit) */
#define LPUART_CTRL_RSRC_MASK            (0x20U)       /**< Bit 5  - Receiver Source Select */
#define LPUART_CTRL_DOZEEN_MASK          (0x40U)       /**< Bit 6  - Doze Enable */
#define LPUART_CTRL_LOOPS_MASK           (0x80U)       /**< Bit 7  - Loop Mode Select */
#define LPUART_CTRL_IDLECFG_MASK         (0x700U)      /**< Bits 10:8 - Idle Configuration */
#define LPUART_CTRL_M7_MASK              (0x800U)      /**< Bit 11 - 7-Bit Mode Select */
#define LPUART_CTRL_MA2IE_MASK           (0x4000U)     /**< Bit 14 - Match 2 Interrupt Enable */
#define LPUART_CTRL_MA1IE_MASK           (0x8000U)     /**< Bit 15 - Match 1 Interrupt Enable */
#define LPUART_CTRL_SBK_MASK             (0x10000U)    /**< Bit 16 - Send Break */
#define LPUART_CTRL_RWU_MASK             (0x20000U)    /**< Bit 17 - Receiver Wakeup Control */
#define LPUART_CTRL_RE_MASK              (0x40000U)    /**< Bit 18 - Receiver Enable (1: Enable RX) */
#define LPUART_CTRL_TE_MASK              (0x80000U)    /**< Bit 19 - Transmitter Enable (1: Enable TX) */
#define LPUART_CTRL_ILIE_MASK            (0x100000U)   /**< Bit 20 - Idle Line Interrupt Enable */
#define LPUART_CTRL_RIE_MASK             (0x200000U)   /**< Bit 21 - Receiver Interrupt Enable */
#define LPUART_CTRL_TCIE_MASK            (0x400000U)   /**< Bit 22 - Transmission Complete Interrupt Enable */
#define LPUART_CTRL_TIE_MASK             (0x800000U)   /**< Bit 23 - Transmit Interrupt Enable */
#define LPUART_CTRL_PEIE_MASK            (0x100000U)   /**< Bit 24 - Parity Error Interrupt Enable */
#define LPUART_CTRL_FEIE_MASK            (0x2000000U)  /**< Bit 25 - Framing Error Interrupt Enable */
#define LPUART_CTRL_NEIE_MASK            (0x4000000U)  /**< Bit 26 - Noise Error Interrupt Enable */
#define LPUART_CTRL_ORIE_MASK            (0x8000000U)  /**< Bit 27 - Overrun Interrupt Enable */
#define LPUART_CTRL_TXINV_MASK           (0x10000000U) /**< Bit 28 - Transmit Data Inversion */
#define LPUART_CTRL_TXDIR_MASK           (0x20000000U) /**< Bit 29 - TX Pin Direction in Single-Wire Mode */
#define LPUART_CTRL_R9T8_MASK            (0x40000000U) /**< Bit 30 - Receive Bit 9 / Transmit Bit 8 */
#define LPUART_CTRL_R8T9_MASK            (0x80000000U) /**< Bit 31 - Receive Bit 8 / Transmit Bit 9 */

/* ============================================================================
 * DATA (Data Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_DATA_DATA_MASK            (0x3FFU)      /**< Bits 9:0 - Receive data / Transmit data */
#define LPUART_DATA_RXEMPT_MASK          (0x1000U)     /**< Bit 12 - Receive Buffer Empty */
#define LPUART_DATA_FRETSC_MASK          (0x2000U)     /**< Bit 13 - Frame Error / Transmit Special Character */
#define LPUART_DATA_PARITYE_MASK         (0x4000U)     /**< Bit 14 - Parity Error */
#define LPUART_DATA_NOISY_MASK           (0x8000U)     /**< Bit 15 - Noise Flag */

/* ============================================================================
 * FIFO (FIFO Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_FIFO_RXFIFOSIZE_MASK      (0x7U)        /**< Bits 2:0 - Receive FIFO Size */
#define LPUART_FIFO_RXFE_MASK            (0x8U)        /**< Bit 3 - Receive FIFO Enable */
#define LPUART_FIFO_TXFIFOSIZE_MASK      (0x70U)       /**< Bits 6:4 - Transmit FIFO Size */
#define LPUART_FIFO_TXFE_MASK            (0x80U)       /**< Bit 7 - Transmit FIFO Enable */
#define LPUART_FIFO_RXFLUSH_MASK         (0x4000U)     /**< Bit 14 - Receive FIFO Flush */
#define LPUART_FIFO_TXFLUSH_MASK         (0x8000U)     /**< Bit 15 - Transmit FIFO Flush */
#define LPUART_FIFO_RXEMPT_MASK          (0x400000U)   /**< Bit 22 - RX FIFO Empty */
#define LPUART_FIFO_TXEMPT_MASK          (0x800000U)   /**< Bit 23 - TX FIFO Empty */

/* ============================================================================
 * GLOBAL (Global Register) Bitfields & Masks
 * ============================================================================ */
#define LPUART_GLOBAL_RST_MASK           (0x2U)        /**< Bit 1 - Software Reset (1: Reset, 0: Normal) */

#define MAX 100

void UART_Init(LPUART_Type *uart);
void UART_SendChar(LPUART_Type *uart, char c);
void UART_Send(LPUART_Type *uart, const char *buff, const uint32_t len);
void UART_Recv(LPUART_Type *uart, char *buff, const uint32_t len);
char UART_RecvChar(LPUART_Type *uart);
void UART_SetBaudRate(LPUART_Type *uart, uint32_t baudrate, uint32_t src_clock_hz);
void UART_Printf(LPUART_Type *uart, const char *buff,...);
uint32_t itoa(char* buff,int32_t d);

#endif /* UART_H */
