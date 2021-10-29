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

void play_sounds(){
  int seconds = 0;
  
  if (secondCount == 2){
    buzzer_set_period(50);
    seconds++;
  }
  seconds = 0;
}

//call method for blink sequence 1/250th of second since it counts a second
