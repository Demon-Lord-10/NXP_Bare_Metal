.cpu cortex-m33
.syntax unified
.thumb

.global reset_handler
.global systick_handler
.extern main

.section .vectors, "a", %progbits
vector_table:
    .word _estack                       /* 0x00: Initial SP */
    .word reset_handler                 /* 0x04: Initial PC */
    .word default_handler               /* 0x08: NMI */
    .word default_handler               /* 0x0C: HardFault */
    .word default_handler               /* 0x10: MemManage */
    .word default_handler               /* 0x14: BusFault */
    .word default_handler               /* 0x18: UsageFault */
    .word default_handler               /* 0x1C: SecureFault */

    /* NXP Image Header Fields (replaces ARM reserved slots) */
    .word 0x00000000                    /* 0x20: Image Length */
    .word 0x00000000                    /* 0x24: Image Type */
    .word 0x00000000                    /* 0x28: Extended Header */

    .word default_handler               /* 0x2C: SVCall */
    .word default_handler               /* 0x30: DebugMonitor */
    .word 0x00000000                    /* 0x34: ImageExecutionAddress*/
    .word default_handler               /* 0x38: PendSV */
    .word default_handler               /* 0x3C: SysTick */
    .rept 448                           /*IRQ0 to IRQ 479*/
    .long default_handler
    .endr

.section .text
.align 1

.type reset_handler, %function
reset_handler:
    /*Copy .data from ROM -> RAM*/
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata

data_loop:
    cmp r0,r1
    bge data_done
    ldr r3, [r2], #4
    str r3, [r0], #4
    b data_loop

data_done:
    /*Zero BSS*/
    ldr r0, =_sbss
    ldr r1, =_ebss
    mov r2, #0

bss_loop:
    cmp r0,r1
    bge bss_done
    str r2, [r0], #4
    b bss_loop

bss_done:
    bl main
    b .

.type default_handler, %function
default_handler:
    b .
