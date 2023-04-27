
#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include <linux/types.h>
#include <linux/io.h>

#define PWM0                PWM0_BASE_ADDR
#define PWM1                PWM1_BASE_ADDR

#define PWM0_BASE_ADDR      0x7e20c000
#define PWM1_BASE_ADDR      0x7e20c800

#define CTL                 0x00 // PWM Control
#define STA                 0x04 // PWM Status
#define DMAC                0x08 // PWM DMA Configuration
#define RNG1                0x10 // PWM Channel 1 Range
#define DAT1                0x14 // PWM Channel 1 Data
#define FIF1                0x18 // PWM FIFO Input
#define RNG2                0x20 // PWM Channel 2 Range
#define DAT2                0x24 // PWM Channel 2 Data


uint32_t raed_reg(uint32_t base_addr, uint8_t offset);
void write_reg(uint32_t base_addr, uint8_t offset, uint32_t data);
uint8_t init_PWM(uint32_t base_addr);
// void set_duty_cycle(uint32_t base_addr, uint8_t duty_cycle);
// void set_clock(uint32_t base_addr, uint32_t clock_frequency);


#endif
