#include <msp430.h>
#include "libtimer.h"
#include "buzzer.h"

void buzzer_init(){

  timerAUpmode(); //used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;  //enable output to speaker (P2.6)
}

void buzzer_set_period(short cycles){  //buzzer clock = 2MHz. (Period of 1k results in 2kHz tone)

  CCR0 = cycles;
  CCR1 = cycles >> 1;  //one half cycle
}

//global state var to count time
int secondCount = 0;

void
_interrupt_vec(WDT_VECTOR) WDT()  // 250 interrupts/sec
{
  secondCount ++;
  if (secondCount >= 250){       // once each second
    secondCount = 0;             // reset count
    //P1OUT ^= LED_GREEN;
  }
}

void play_song(){
  int seconds = 0;

  float e_flat = 57723.72272;
  float d_flat = 51425.91197;
  float c_flat = 64792.64733;
  
  if (secondCount == 2){
    buzzer_set_period(e_flat); //e flat
    seconds++;
  }
  else if (secondCount == 3){
    buzzer_set_period(d_flat); //d flat
    seconds++;
  }
  else if (secondCount == 4){
    buzzer_set_period(e_flat); //e flat
    seconds++;
  }
  else if (secondCount == 5){
    buzzer_set_period(d_flat);
    seconds++;
  }
  else if (secondCount == 6){
    buzzer_set_period(e_flat);
    seconds++;
  }
  else if (secondCount == 7){
    buzzer_set_period(d_flat);
    seconds++;
  }
  else if (secondCount == 8){
    buzzer_set_period(e_flat);
    seconds++;
  }
  else if (secondCount == 9){
    buzzer_set_period(c_flat);
    seconds++;
  }
  else{
    buzzer_set_period(0);
  }
}

//call method for blink sequence 1/250th of second since it counts a second

