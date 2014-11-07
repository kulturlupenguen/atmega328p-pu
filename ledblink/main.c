#include "main.h"

void mcu_initialize(void){
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    DDRB |= _BV(DDB0); // PB0 çıkış yapıldı.
}

int main(void){
    mcu_initialize(); // MCU'yu ayarla.
    
    
    while(1){
        PORTB ^= _BV(B0);
        _delay_ms(500);
    }
}
