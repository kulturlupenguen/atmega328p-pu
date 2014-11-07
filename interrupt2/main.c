#include "main.h"

unsigned char compare[1];
volatile unsigned char compbuff[1];

int redVal = 0;

void mcu_initialize(void){
    PORTB = 0x00;
    
    DDRB |= _BV(B0); // PB0 çıkış yapıldı.
    TIFR0 = (1 << TOV0); // Overflow olduğunda hardware tarafından temizlenmeyi etkinleştir.
    TCCR0B = (1 << WGM01); // CTC bit enable
    TIMSK0 = (1 << TOIE0); // Timer overflow olduğunda ISR'ı etkinleştir.
    
    sei(); // Global interrupt etkinleştirildi.
    
    TCCR0B = (1 << CS00); // Timer Prescaler yok.
    
}


int main(void){
    mcu_initialize(); // MCU'yu ayarla.
    int r_dir = 1;
    while(1){
        if (redVal > 254) {
          r_dir = -1;
        }
        if (redVal < 2) {
          r_dir = 1;
        }
        
        redVal += r_dir;    
        compbuff[0] = redVal;        
        delay_ms(5);
    }
}

 
ISR (TIMER0_OVF_vect) {
  static unsigned char pinlevelB=(1 << PB0);
  static unsigned char softcount= 0xFF;
  PORTB = pinlevelB;            
  volatile uint8_t *port;
  port = &pinlevelB;
  
  if(++softcount == 0){         
    compare[0] = compbuff[0];  // karşılaştır. 
    high(port, 0);   // PWM pinini lojik 1 yap
  }

  if(compare[0] == softcount) low(port, 0); // LOW dönemi

}
