#include <avr/io.h>

#include <avr/interrupt.h>

#include <stdbool.h>

#include <util/delay.h>

volatile uint32_t RecdData;
//int data[7];
int use = 0;
int b = 12;
int last_num = 0;
int iter = 0;
int adress, rev_adress, data, rev_data, res, symbols, n, nextbit, time;
volatile uint32_t codes[10] = {
   86,
   126,
   52,
   70,
   134,
   130,
   192,
   60,
   20,
   30
};


ISR(TIMER1_OVF_vect) {
   TIMSK = 0x02;
   TCNT1 = 0;
   TCCR0B = 0x06;
   TCNT0 = 255;
}





ISR(TIMER0_OVF_vect) {


    switch(iter){
    case 0:
      TCNT1 = 0;
            TCCR1B = 0x05;
            TIMSK = 0x82;
            TCCR0B = 0x07;
            TCNT0 = 0xFF;
            iter = 1;
      break;
    
    case 1:
       time = TCNT1;

            if (time >= 69) {
               TCCR0B = 0x06;
               TCNT0 = 0xFF;

               symbols = 0;
               adress = 0;
               data = 0;
               rev_adress = 0;
               rev_data = 0;

               TCNT1 = 0;

               iter = 2;
            } else {
               iter = 9;
            }
      break;
      
    case 2:
      time = TCNT1;

            iter = 3;

            if (time < (2 * b)) {
               iter = 9;
            }

            TCNT1 = 0;
            TCNT0 = 0xFF;

            n = 1;
    
    case 3:
      time = TCNT1;

            nextbit = 0;

            if (time > b) {
               nextbit = 1;
            }

            adress = adress + nextbit * n;
            symbols = symbols + 1;
            n = n * 2;

            if (symbols == 8) {
               symbols = 0;
               iter = 4;
               n = 1;
            }

            TCNT1 = 0;
            TCNT0 = 0xFF;
      
      break;
      
    case 4:
      time = TCNT1;

            nextbit = 0;

            if (time > b) {
               nextbit = 1;
            }

            rev_adress = rev_adress + nextbit * n;
            symbols = symbols + 1;
            n = n * 2;

            if (symbols == 8) {
               symbols = 0;
               iter = 5;
               n = 1;
            }

            TCNT1 = 0;
            TCNT0 = 0xFF;
      break;
      
    case 5:
      
            time = TCNT1;

            nextbit = 0;

            if (time > b) {
               nextbit = 1;
            }

            data = data + nextbit * n;
            symbols = symbols + 1;
            n = n * 2;

            if (symbols == 8) {
               symbols = 0;
               iter = 6;
               n = 1;
            }

            TCNT1 = 0;
            TCNT0 = 0xFF;
      
      break;
      
    case 6:
      time = TCNT1;

            nextbit = 0;

            if (time > b) {
               nextbit = 1;
            }

            rev_data = rev_data + nextbit * n;
            symbols = symbols + 1;
            n = n * 2;

            if (symbols == 8) {
               symbols = 0;
               iter = 7;
               n = 1;
            }
            TCNT1 = 0;
            TCNT0 = 0xFF;
      
      break;
    
    case 7:
      PORTB = 0x00;
      res = data;
      use = 1;
      //use your code here
        break;
      default: break;
        
      }

      TIMSK = 0x02;
      TCNT1 = 0x00;
      TCCR0B = 0x06;
      TCNT0 = 0xFF;

      iter = 0;
         
      break;
     
     case 9:  //error case
      TIMSK = 0x02;
      TCNT1 = 0x00;
      TCCR0B = 0x06;
      TCNT0 = 0xFF;

      iter = 0;
      
    default: break;
      
  
  }
     
     
     
     
     
  }
    

      int main(void) {
         DDRB = 0xFF;
         DDRD = 0x00;
         PORTB = 0x00;
         PORTD = 0xFE;

         TCCR0A = 0x00;
         TCCR0B = 0x06;
         TCNT0 = 0x00;
         OCR0A = 0x00;
         OCR0B = 0x00;
         TCNT0 = 0xFF;

         TCCR1A = 0x00;
         TCCR1B = 0x05;
         TCNT1 = 0;

         TIMSK = 0x02;

         sei();

         while (1) {}
      }
