#include "clock.h"

void Clock_Init_48MHZ(){
    // 1. Select 48 MHz (FREQ_SEL = 1)
    SCG0->FIRCCFG = SCG_FIRCCFG_FREQ_SEL(1u);

    // 2. Unlock FIRCCSR (LK = 0)
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;

    // 3 & 4. Enable peripheral clocks from FIRC
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK;

    // Ensure FIRC is enabled (Do NOT write 0!)
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCEN_MASK;

    // 6. Wait until FIRC is valid and stable
    while (!(SCG0->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK));

    // 7. Check for errors
    if (SCG0->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) {
        return;
    }

    // 8. Switch system clock to FIRC (SCS = 3)
    SCG0->RCCR = (SCG0->RCCR & ~SCG_RCCR_SCS_MASK) | SCG_RCCR_SCS(3u);

    // 9. Wait until Clock Status Register confirms switch
    while ((SCG0->CSR & SCG_CSR_SCS_MASK) != SCG_CSR_SCS(3u));

    // 11. Lock FIRCCSR against accidental writes
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK;

}

void Clock_Init_96MHz(){
    //Wait State to 2 for 96Mhz
    FMU0->FCTRL = (FMU0->FCTRL & ~FMU_FCTRL_RWSC_MASK) | FMU_FCTRL_RWSC(2u);

    // 1. Select 96 MHz (FREQ_SEL = 5)
    SCG0->FIRCCFG = SCG_FIRCCFG_FREQ_SEL(5u);

    // 2. Unlock FIRCCSR (LK = 0)
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;

    // 3 & 4. Enable peripheral clocks from FIRC
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK;

    // Ensure FIRC is enabled (Do NOT write 0!)
    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCEN_MASK;

    // 6. Wait until FIRC is valid and stable
    while (!(SCG0->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK));

    // 7. Check for errors
    if (SCG0->FIRCCSR & SCG_FIRCCSR_FIRCERR_MASK) {
        return;
    }

    // 8. Switch system clock to FIRC (SCS = 3)
    SCG0->RCCR = (SCG0->RCCR & ~SCG_RCCR_SCS_MASK) | SCG_RCCR_SCS(3);

    // 9. Wait until Clock Status Register confirms switch
    while ((SCG0->CSR & SCG_CSR_SCS_MASK) != SCG_CSR_SCS(3));

    // 11. Lock FIRCCSR against accidental writes
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK;

}

void Clock_Enable_Port(uint8_t port_num){

    /* Unlock clock configuration registers */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    switch (port_num){
        case 0:
            MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT0_MASK;
            MRCC0->MRCC_GLB_CC0_SET  = MRCC_MRCC_GLB_CC0_PORT0_MASK;
            break;
        case 1:
            MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1_MASK;
            MRCC0->MRCC_GLB_CC0_SET  = MRCC_MRCC_GLB_CC0_PORT1_MASK;
            break;
        case 2:
            MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT2_MASK;
            MRCC0->MRCC_GLB_CC0_SET  = MRCC_MRCC_GLB_CC0_PORT2_MASK;
            break;
        case 3:
            MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_PORT3_MASK;
            MRCC0->MRCC_GLB_CC1_SET  = MRCC_MRCC_GLB_CC1_PORT3_MASK;
            break;
        default:
            break;
    }

    /* Freeze clock configuration registers */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}

void Clock_Enable_GPIO(uint8_t gpio_num){

    /* Unlock clock configuration registers */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    switch (gpio_num){
        case 0:
            MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO0_MASK;
            MRCC0->MRCC_GLB_CC1_SET  = MRCC_MRCC_GLB_CC1_GPIO0_MASK;
            break;
        case 1:
            MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO1_MASK;
            MRCC0->MRCC_GLB_CC1_SET  = MRCC_MRCC_GLB_CC1_GPIO1_MASK;
            break;
        case 2:
            MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO2_MASK;
            MRCC0->MRCC_GLB_CC1_SET  = MRCC_MRCC_GLB_CC1_GPIO2_MASK;
            break;
        case 3:
            MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO3_MASK;
            MRCC0->MRCC_GLB_CC1_SET  = MRCC_MRCC_GLB_CC1_GPIO3_MASK;
            break;
        default:
            break;
    }

    /* Freeze clock configuration registers */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}
