#include <stdint.h>
volatile uint16_t SYMBEX_SYNTHETIC_STATUS_REGISTER;


//Intrinsics
void __bis_status_register(unsigned int arg1){ 
	SYMBEX_SYNTHETIC_STATUS_REGISTER |= arg1; 
}
void __write_status_register(unsigned int arg1){
	SYMBEX_SYNTHETIC_STATUS_REGISTER = arg1; 
}

void __bic_status_register(unsigned int arg1){ 
	SYMBEX_SYNTHETIC_STATUS_REGISTER &= ~arg1; 
}
void __bic_status_register_on_exit(unsigned int arg){}
void __no_operation(){}
void __nop(){}
void _delay_cycles(unsigned long arg1){} 
void __delay_cycles(unsigned long arg1){} 
void __eint(){ 
	SYMBEX_SYNTHETIC_STATUS_REGISTER = 0xFFFF;
}
void __dint(){
	SYMBEX_SYNTHETIC_STATUS_REGISTER = 0x0;
}
uint16_t __even_in_range(uint16_t a, uint16_t b){ return a; }
uint16_t __get_SR_register() { return SYMBEX_SYNTHETIC_STATUS_REGISTER; }
