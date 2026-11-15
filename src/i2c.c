#include "i2c.h"
#include "gpio.h"
#include "clock.h"

void I2C_Init(LPI2C_Type *i2c){

    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;                     //Lock the Clock;

    if (i2c == LPI2C0) {
        /* Select FRO_12M (12 MHz) and Divider = 1 (Divide by DIV + 1, HALT = 0) */
        MRCC0->MRCC_LPI2C0_CLKSEL = 0u; // 0 = FRO_12M (12 MHz)
        MRCC0->MRCC_LPI2C0_CLKDIV = 0u; // 0 = Divide by 1
    }

    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;                     //Unlock the Clock;

    if(i2c == LPI2C0){
        MRCC_Enable(0u, MRCC_MRCC_GLB_CC0_LPI2C0_MASK);
        MRCC_Enable(1u, MRCC_MRCC_GLB_CC1_PORT3_MASK);
        PORT3->PCR[27u] = PORT_PCR_MUX(2u) | PORT_PCR_IBE(1u) | PORT_PCR_ODE(1u) | PORT_PCR_PE(1u) | PORT_PCR_PS(1u);   //SCL
        PORT3->PCR[28u] = PORT_PCR_MUX(2u) | PORT_PCR_IBE(1u) | PORT_PCR_ODE(1u) | PORT_PCR_PE(1u) | PORT_PCR_PS(1u);   //SDA
    }

    //Reset LPI2C0
    i2c->MCR = LPI2C_MCR_RST_MASK;
    i2c->MCR = 0u;

    //Set Prescalar to 0 meaning divide by 1 so 12Mhz clock
    i2c->MCFGR1 = LPI2C_MCFGR1_PRESCALE(0u);

    /* Set SCL Timing for 100 kHz from 12 MHz clock:
     * Cycle count = 12 MHz / 100 kHz = 120 cycles.
     * CLKLO = 62 (counts 62 + 1 = 63 cycles low)  -> 63 => 5.25us > 4.7us
     * CLKHI = 54 (counts 54 + 1 = 55 cycles high) -> 63 + 55 = 118 cycles but scl latency is to be accounted for which is 2 cycles so its 120 cycles. 55 cycles -> 4.75us > 4us
     * SETHOLD = 54 (Start/Stop hold time)         -> gives 54+1 = 55 cycles meaning => 4.58us which is greater than 4us requirement
     * DATAVD  = 3 (Data valid delay)              -> gives 3+1 = 4 cycles meaning => 0.33us <3.45us
     */

    i2c->MCCR0 = LPI2C_MCCR0_CLKLO(62u)     |
        LPI2C_MCCR0_CLKHI(54u)     |
        LPI2C_MCCR0_SETHOLD(54u)   |
        LPI2C_MCCR0_DATAVD(3u);

    i2c->MCR = LPI2C_MCR_MEN_MASK;
}

int I2C_Start(LPI2C_Type *i2c, uint8_t dev_addr, bool is_read){

    //Clear all error / status flags
    i2c->MSR = LPI2C_MSR_NDF_MASK | LPI2C_MSR_ALF_MASK | LPI2C_MSR_FEF_MASK | LPI2C_MSR_SDF_MASK; //NDF ->NACK flag , ALF -> Arbitration Lost FLag ,
                                                                                                  //FEF -> FIFO error flag , SDF -> Stop Detect Flag

    //if another bus is busy or another master is busy
    if((i2c->MSR & LPI2C_MSR_BBF_MASK) && !(i2c->MSR & LPI2C_MSR_MBF_MASK)){
        return I2C_ERR_BUS_BUSY;
    }

    i2c->MTDR = ((uint32_t)(dev_addr & 0x7FU) << 1U) | (is_read ? 1U : 0U) | LPI2C_MTDR_CMD(LPI2C_CMD_START);

    while(!(i2c->MSR & (LPI2C_MSR_TDF_MASK | LPI2C_MSR_NDF_MASK)));

    if (i2c->MSR & LPI2C_MSR_NDF_MASK){
        i2c->MSR = LPI2C_MSR_NDF_MASK;
        return I2C_ERR_NACK;
    }

    return I2C_OK;
}

int I2C_Stop(LPI2C_Type *i2c) {

    /* Push STOP command to MTDR */
    i2c->MTDR = LPI2C_MTDR_CMD(LPI2C_CMD_STOP);

    /* Wait until STOP condition completes on the bus */
    while (!(i2c->MSR & LPI2C_MSR_SDF_MASK));

    /* Clear the Stop Detect Flag (W1C) */
    i2c->MSR = LPI2C_MSR_SDF_MASK;

    return I2C_OK;
}

int I2C_WriteByte(LPI2C_Type *i2c, uint8_t data){

    /* Wait until TX FIFO is ready */
    while(!(i2c->MSR & LPI2C_MSR_TDF_MASK));

    /* Send data byte with TX command (CMD = 0) */
    i2c->MTDR = LPI2C_MTDR_CMD(LPI2C_CMD_TX_DATA) | LPI2C_MTDR_DATA(data);

    /* Wait for transmission or NACK */
    while(!(i2c->MSR & (LPI2C_MSR_TDF_MASK | LPI2C_MSR_NDF_MASK)));

    /* Check if slave responded with NACK */
    if(i2c->MSR & LPI2C_MSR_NDF_MASK){
        i2c->MSR = LPI2C_MSR_NDF_MASK;
        return I2C_ERR_NACK;
    }

    return I2C_OK;
}

int I2C_ReadByte(LPI2C_Type *i2c, uint8_t *data) {

    if (!data) return I2C_ERR_FIFO;

    /* Command hardware to receive 1 byte (DATA = 0 means 1 byte) */
    i2c->MTDR = LPI2C_MTDR_CMD(LPI2C_CMD_RX_DATA) | LPI2C_MTDR_DATA(0);

    /* Wait until data is in RX FIFO */
    while (!(i2c->MSR & LPI2C_MSR_RDF_MASK));

    *data = (uint8_t)(i2c->MRDR & LPI2C_MRDR_DATA_MASK);

    return I2C_OK;
}

int I2C_Write(LPI2C_Type *i2c, uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint32_t len) {

    int ret;

    /* 1. START with device address (Write mode) */
    ret = I2C_Start(i2c, dev_addr, false);
    if(ret != I2C_OK){
        I2C_Stop(i2c);
        return ret;
    }

    /* 2. Write target register address */
    ret = I2C_WriteByte(i2c, reg_addr);
    if(ret != I2C_OK){
        I2C_Stop(i2c);
        return ret;
    }

    /* 3. Send payload bytes */
    for(uint32_t i = 0; i < len; i++){
        ret = I2C_WriteByte(i2c, data[i]);
        if(ret != I2C_OK){
            I2C_Stop(i2c);
            return ret;
        }
    }

    /* 4. Release bus with STOP */
    return I2C_Stop(i2c);
}

int I2C_Read(LPI2C_Type *i2c, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint32_t len) {

    int ret;
    if(!data || len == 0) return I2C_ERR_FIFO;

    /* 1. START with write to select register */
    ret = I2C_Start(i2c, dev_addr, false);
    if(ret != I2C_OK){
        I2C_Stop(i2c);
        return ret;
    }

    /* 2. Write register address */
    ret = I2C_WriteByte(i2c, reg_addr);
    if(ret != I2C_OK){
        I2C_Stop(i2c);
        return ret;
    }

    /* 3. Repeated START with read */
    ret = I2C_Start(i2c, dev_addr, true);
    if(ret != I2C_OK){
        I2C_Stop(i2c);
        return ret;
    }

    /* 4. Command hardware to receive len bytes (DATA = len - 1)
     * Hardware ACKs intermediate bytes and automatically NACKs the last byte */
    i2c->MTDR = LPI2C_MTDR_CMD(LPI2C_CMD_RX_DATA) | LPI2C_MTDR_DATA(len - 1);

    /* 5. Fetch all received bytes from RX FIFO */
    for(uint32_t i = 0; i < len; i++){
        while (!(i2c->MSR & LPI2C_MSR_RDF_MASK));
        data[i] = (uint8_t)(i2c->MRDR & LPI2C_MRDR_DATA_MASK);
    }

    /* 6. Release bus with STOP */
    return I2C_Stop(i2c);
}

void I2C_ResetBus(LPI2C_Type *i2c) {

    /* Save configuration & timing registers */
    uint32_t mcfgr1 = i2c->MCFGR1;
    uint32_t mccr0  = i2c->MCCR0;

    /* Disable controller */
    i2c->MCR = 0;

    /* Reset FIFOs and internal state machine */
    i2c->MCR = LPI2C_MCR_RST_MASK | LPI2C_MCR_RTF_MASK | LPI2C_MCR_RRF_MASK;
    i2c->MCR = 0;

    /* Restore settings and baud rate timing */
    i2c->MCFGR1 = mcfgr1;
    i2c->MCCR0  = mccr0;

    /* Clear all sticky error / status flags */
    i2c->MSR = LPI2C_MSR_NDF_MASK | LPI2C_MSR_ALF_MASK | 
        LPI2C_MSR_FEF_MASK | LPI2C_MSR_SDF_MASK;

    /* Re-enable controller */
    i2c->MCR = LPI2C_MCR_MEN_MASK;
}

