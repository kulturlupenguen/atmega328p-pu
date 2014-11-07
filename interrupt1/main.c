#include "main.h"
void mcu_initialize(void){
    PORTB = 0x00;;
    DDRB |= _BV(B0); // PB0 çıkış yapıldı.
    
    TCCR0A = (1 << WGM01); // CTC bit
    OCR0A = 195;
    TIMSK0 = (1 << OCIE0A);
    
    sei(); // Global interrupt etkinleştirildi.
    
    TCCR0B = (1 << CS02) | (1 << CS00); // 1024 prescaler.
    
}

uint8_t extraTimer = 0;

int main(void){
    mcu_initialize(); // MCU'yu ayarla.
    while(1){
        // TODO: Code
    }
}

ISR(TIMER0_COMPA_vect)
{
    extraTimer++;
    if(extraTimer > 100){
        volatile uint8_t *port; // PORTB'ye pointer.
        port = &PORTB;
        high(port, 0); 
        _delay_ms(500);
        low(port, 0);
        _delay_ms(500);
        extraTimer = 0;
    }
}
