#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
 * LPI2C (Low Power Inter-Integrated Circuit) Register Definition
 * Reference Manual: Chapter 36 (Base Address: 0x4009A000)
 * ============================================================================ */

typedef struct {
    volatile const uint32_t VERID;       /**< 0x00: Version ID */
    volatile const uint32_t PARAM;       /**< 0x04: Parameter */
    uint8_t RESERVED_0[8];               /**< 0x08 - 0x0F */
    volatile uint32_t MCR;               /**< 0x10: Controller Control */
    volatile uint32_t MSR;               /**< 0x14: Controller Status */
    volatile uint32_t MIER;              /**< 0x18: Controller Interrupt Enable */
    volatile uint32_t MDER;              /**< 0x1C: Controller DMA Enable */
    volatile uint32_t MCFGR0;            /**< 0x20: Controller Configuration 0 */
    volatile uint32_t MCFGR1;            /**< 0x24: Controller Configuration 1 */
    volatile uint32_t MCFGR2;            /**< 0x28: Controller Configuration 2 */
    volatile uint32_t MCFGR3;            /**< 0x2C: Controller Configuration 3 */
    uint8_t RESERVED_1[16];              /**< 0x30 - 0x3F */
    volatile uint32_t MDMR;              /**< 0x40: Controller Data Match */
    uint8_t RESERVED_2[4];               /**< 0x44 - 0x47 */
    volatile uint32_t MCCR0;             /**< 0x48: Controller Clock Configuration 0 */
    uint8_t RESERVED_3[4];               /**< 0x4C - 0x4F */
    volatile uint32_t MCCR1;             /**< 0x50: Controller Clock Configuration 1 */
    uint8_t RESERVED_4[4];               /**< 0x54 - 0x57 */
    volatile uint32_t MFCR;              /**< 0x58: Controller FIFO Control */
    volatile const uint32_t MFSR;        /**< 0x5C: Controller FIFO Status */
    volatile uint32_t MTDR;              /**< 0x60: Controller Transmit Data */
    uint8_t RESERVED_5[12];              /**< 0x64 - 0x6F */
    volatile const uint32_t MRDR;        /**< 0x70: Controller Receive Data */
    uint8_t RESERVED_6[4];               /**< 0x74 - 0x77 */
    volatile const uint32_t MRDROR;      /**< 0x78: Controller Receive Data Read Only */
    uint8_t RESERVED_7[148];             /**< 0x7C - 0x10F */
    volatile uint32_t SCR;               /**< 0x110: Target Control */
    volatile uint32_t SSR;               /**< 0x114: Target Status */
    volatile uint32_t SIER;              /**< 0x118: Target Interrupt Enable */
    volatile uint32_t SDER;              /**< 0x11C: Target DMA Enable */
    volatile uint32_t SCFGR0;            /**< 0x120: Target Configuration 0 */
    volatile uint32_t SCFGR1;            /**< 0x124: Target Configuration 1 */
    volatile uint32_t SCFGR2;            /**< 0x128: Target Configuration 2 */
    uint8_t RESERVED_8[20];              /**< 0x12C - 0x13F */
    volatile uint32_t SAMR;              /**< 0x140: Target Address Match */
    uint8_t RESERVED_9[12];              /**< 0x144 - 0x14F */
    volatile const uint32_t SASR;        /**< 0x150: Target Address Status */
    volatile uint32_t STAR;              /**< 0x154: Target Transmit ACK */
    uint8_t RESERVED_10[8];              /**< 0x158 - 0x15F */
    volatile uint32_t STDR;              /**< 0x160: Target Transmit Data */
    uint8_t RESERVED_11[12];             /**< 0x164 - 0x16F */
    volatile const uint32_t SRDR;        /**< 0x170: Target Receive Data */
    uint8_t RESERVED_12[4];              /**< 0x174 - 0x177 */
    volatile const uint32_t SRDROR;      /**< 0x178: Target Receive Data Read Only */
} LPI2C_Type;

/* LPI2C Base Address & Peripheral Pointer */
#define LPI2C0_BASE                      (0x4009A000u)
#define LPI2C0                           ((LPI2C_Type *)LPI2C0_BASE)

/* LPI2C NVIC Interrupt Number */
#define LPI2C0_IRQn                      (26)

/* ============================================================================
 * MCR (Controller Control Register) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MCR_MEN_MASK               (0x1U)        /**< Bit 0: Controller Enable */
#define LPI2C_MCR_RST_MASK               (0x2U)        /**< Bit 1: Software Reset */
#define LPI2C_MCR_DOZEN_MASK             (0x4U)        /**< Bit 2: Doze Mode Enable */
#define LPI2C_MCR_DBGEN_MASK             (0x8U)        /**< Bit 3: Debug Enable */
#define LPI2C_MCR_RTF_MASK               (0x100U)      /**< Bit 8: Reset Transmit FIFO */
#define LPI2C_MCR_RRF_MASK               (0x200U)      /**< Bit 9: Reset Receive FIFO */

/* ============================================================================
 * MSR (Controller Status Register) Bitfields & Masks (W1C = Write 1 to Clear)
 * ============================================================================ */
#define LPI2C_MSR_TDF_MASK               (0x1U)        /**< Bit 0:  Transmit Data Flag */
#define LPI2C_MSR_RDF_MASK               (0x2U)        /**< Bit 1:  Receive Data Flag */
#define LPI2C_MSR_EPF_MASK               (0x100U)      /**< Bit 8:  End Packet Flag (W1C) */
#define LPI2C_MSR_SDF_MASK               (0x200U)      /**< Bit 9:  Stop Detect Flag (W1C) */
#define LPI2C_MSR_NDF_MASK               (0x400U)      /**< Bit 10: NACK Detect Flag (W1C) */
#define LPI2C_MSR_ALF_MASK               (0x800U)      /**< Bit 11: Arbitration Lost Flag (W1C) */
#define LPI2C_MSR_FEF_MASK               (0x1000U)     /**< Bit 12: FIFO Error Flag (W1C) */
#define LPI2C_MSR_PLTF_MASK              (0x2000U)     /**< Bit 13: Pin Low Timeout Flag (W1C) */
#define LPI2C_MSR_DMF_MASK               (0x4000U)     /**< Bit 14: Data Match Flag (W1C) */
#define LPI2C_MSR_STF_MASK               (0x8000U)     /**< Bit 15: Start Flag (W1C) */
#define LPI2C_MSR_MBF_MASK               (0x1000000U)  /**< Bit 24: Controller Busy Flag */
#define LPI2C_MSR_BBF_MASK               (0x2000000U)  /**< Bit 25: Bus Busy Flag */

#define LPI2C_MSR_ERROR_MASK             (LPI2C_MSR_NDF_MASK | LPI2C_MSR_ALF_MASK | \
                                          LPI2C_MSR_FEF_MASK | LPI2C_MSR_PLTF_MASK)

/* ============================================================================
 * MIER (Controller Interrupt Enable Register) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MIER_TDIE_MASK             (0x1U)        /**< Bit 0:  Transmit Data Interrupt Enable */
#define LPI2C_MIER_RDIE_MASK             (0x2U)        /**< Bit 1:  Receive Data Interrupt Enable */
#define LPI2C_MIER_EPIE_MASK             (0x100U)      /**< Bit 8:  End Packet Interrupt Enable */
#define LPI2C_MIER_SDIE_MASK             (0x200U)      /**< Bit 9:  Stop Detect Interrupt Enable */
#define LPI2C_MIER_NDIE_MASK             (0x400U)      /**< Bit 10: NACK Detect Interrupt Enable */
#define LPI2C_MIER_ALIE_MASK             (0x800U)      /**< Bit 11: Arbitration Lost Interrupt Enable */
#define LPI2C_MIER_FEIE_MASK             (0x1000U)     /**< Bit 12: FIFO Error Interrupt Enable */
#define LPI2C_MIER_PLTIE_MASK            (0x2000U)     /**< Bit 13: Pin Low Timeout Interrupt Enable */
#define LPI2C_MIER_DMIE_MASK             (0x4000U)     /**< Bit 14: Data Match Interrupt Enable */
#define LPI2C_MIER_STIE_MASK             (0x8000U)     /**< Bit 15: Start Interrupt Enable */

/* ============================================================================
 * MCFGR1 (Controller Configuration Register 1) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MCFGR1_PRESCALE_MASK       (0x7U)        /**< Bits 2:0 - Prescaler (div 2^n) */
#define LPI2C_MCFGR1_PRESCALE(x)         (((uint32_t)(x)) & LPI2C_MCFGR1_PRESCALE_MASK)
#define LPI2C_MCFGR1_AUTOSTOP_MASK       (0x100U)      /**< Bit 8:  Automatic Stop Generation */
#define LPI2C_MCFGR1_IGNACK_MASK         (0x200U)      /**< Bit 9:  Ignore NACK */
#define LPI2C_MCFGR1_PINCFG_MASK         (0x7000000U)  /**< Bits 26:24: Pin Configuration */
#define LPI2C_MCFGR1_PINCFG(x)           ((((uint32_t)(x)) << 24U) & LPI2C_MCFGR1_PINCFG_MASK)

/* ============================================================================
 * MCCR0 (Controller Clock Configuration Register 0) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MCCR0_CLKLO_MASK           (0x3FU)       /**< Bits 5:0 - Clock Low Period */
#define LPI2C_MCCR0_CLKLO(x)             (((uint32_t)(x)) & LPI2C_MCCR0_CLKLO_MASK)

#define LPI2C_MCCR0_CLKHI_MASK           (0x3F00U)     /**< Bits 13:8 - Clock High Period */
#define LPI2C_MCCR0_CLKHI(x)             ((((uint32_t)(x)) << 8U) & LPI2C_MCCR0_CLKHI_MASK)

#define LPI2C_MCCR0_SETHOLD_MASK         (0x3F0000U)   /**< Bits 21:16 - Setup Hold Delay */
#define LPI2C_MCCR0_SETHOLD(x)           ((((uint32_t)(x)) << 16U) & LPI2C_MCCR0_SETHOLD_MASK)

#define LPI2C_MCCR0_DATAVD_MASK          (0x3F000000U) /**< Bits 29:24 - Data Valid Delay */
#define LPI2C_MCCR0_DATAVD(x)            ((((uint32_t)(x)) << 24U) & LPI2C_MCCR0_DATAVD_MASK)

/* ============================================================================
 * MFCR & MFSR (FIFO Control & Status) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MFCR_TXWATER_MASK          (0x3U)        /**< Bits 1:0 - Transmit FIFO Watermark */
#define LPI2C_MFCR_TXWATER(x)            (((uint32_t)(x)) & LPI2C_MFCR_TXWATER_MASK)

#define LPI2C_MFCR_RXWATER_MASK          (0x30000U)    /**< Bits 17:16 - Receive FIFO Watermark */
#define LPI2C_MFCR_RXWATER(x)            ((((uint32_t)(x)) << 16U) & LPI2C_MFCR_RXWATER_MASK)

#define LPI2C_MFSR_TXCOUNT_MASK          (0x7U)        /**< Bits 2:0 - TX FIFO Count */
#define LPI2C_MFSR_RXCOUNT_MASK          (0x70000U)    /**< Bits 18:16 - RX FIFO Count */

/* ============================================================================
 * MTDR (Controller Transmit Data & Command) Bitfields & Commands
 * ============================================================================ */
#define LPI2C_MTDR_DATA_MASK             (0xFFU)       /**< Bits 7:0 - Transmit Data */
#define LPI2C_MTDR_DATA(x)               (((uint32_t)(x)) & LPI2C_MTDR_DATA_MASK)

#define LPI2C_MTDR_CMD_MASK              (0x700U)      /**< Bits 10:8 - Command Data */
#define LPI2C_MTDR_CMD(x)                ((((uint32_t)(x)) << 8U) & LPI2C_MTDR_CMD_MASK)

/* Hardware Command Codes written to MTDR[CMD] */
#define LPI2C_CMD_TX_DATA                (0x0U) /**< 000b: Transmit DATA[7:0] */
#define LPI2C_CMD_RX_DATA                (0x1U) /**< 001b: Receive (DATA[7:0] + 1) bytes */
#define LPI2C_CMD_STOP                   (0x2U) /**< 010b: Generate STOP condition */
#define LPI2C_CMD_RX_DISCARD             (0x3U) /**< 011b: Receive and discard (DATA[7:0] + 1) bytes */
#define LPI2C_CMD_START                  (0x4U) /**< 100b: Generate START and send address in DATA[7:0] */
#define LPI2C_CMD_START_NACK             (0x5U) /**< 101b: Generate START with NACK expected */

/* ============================================================================
 * MRDR (Controller Receive Data) Bitfields & Masks
 * ============================================================================ */
#define LPI2C_MRDR_DATA_MASK             (0xFFU)       /**< Bits 7:0 - Receive Data */
#define LPI2C_MRDR_RXEMPTY_MASK          (0x4000U)     /**< Bit 14 - Receive FIFO Empty */

/* ============================================================================
 * Driver Return Codes
 * ============================================================================ */
#define I2C_OK                           (0)
#define I2C_ERR_BUS_BUSY                (-1)
#define I2C_ERR_NACK                    (-2)
#define I2C_ERR_TIMEOUT                 (-3)
#define I2C_ERR_ARBITRATION_LOST        (-4)
#define I2C_ERR_FIFO                    (-5)
#define I2C_ERR_PARAM                   (-6)

/* ============================================================================
 * I2C Driver Function Prototypes
 * ============================================================================ */
void I2C_Init(LPI2C_Type *i2c);
int  I2C_Start(LPI2C_Type *i2c, uint8_t dev_addr, bool is_read);
int  I2C_Stop(LPI2C_Type *i2c);
int  I2C_WriteByte(LPI2C_Type *i2c, uint8_t data);
int  I2C_ReadByte(LPI2C_Type *i2c, uint8_t *data);
int  I2C_Write(LPI2C_Type *i2c, uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint32_t len);
int  I2C_Read(LPI2C_Type *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);
void I2C_ResetBus(LPI2C_Type *i2c);

#endif /* I2C_H */
