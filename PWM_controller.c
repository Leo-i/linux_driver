
#include "PWM_controller.h"



uint32_t raed_reg(uint32_t base_addr, uint8_t offset){

    return readl(base_addr + offset);
}

void write_reg(uint32_t base_addr, uint8_t offset, uint32_t data){

    writel(base_addr + offset, data);

}

uint8_t init_PWM(uint32_t base_addr){
    write_reg(base_addr, STA, 0x00000003);
    return 0;
}