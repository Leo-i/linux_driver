
#include "PWM_controller.h"


uint32_t raed_reg(uint32_t base_addr, uint8_t offset){

    uint32_t *p = (uint32_t*)(base_addr + offset);
    return (uint32_t)*p;
}

void write_reg(uint32_t base_addr, uint8_t offset, uint32_t data){

    uint32_t *p = (uint32_t*)(base_addr + offset);
    *p = data;
}

uint8_t init_PWM(uint32_t base_addr){
    write_reg(base_addr, STA, 0x00000003);
    return 0;
}