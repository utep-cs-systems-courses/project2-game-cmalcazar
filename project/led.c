
#include <msp430.h>
#include "led.h"

void led_init(){
  P1DIR |= LEDS; //set LEDS to be outputs
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterupts();
}

int blinkLimit = 5;
int blinkCount = 0;
int secondCount = 0;

void
_interrupt_vec(WDT_VECTOR) WDT()
{
  blinkCount++;
  if (blinkCount >= 250){  //both LEDS turn on in 1 second
    P1OUT |= LED_RED;
    P1OUT |= LED_GREEN;
  }
  else if (blinkCount >= 500){   //at 2 seconds both LEDS turn off
    P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
  }
  else if (blinkCount >= 750){  //at 3 seconds both LEDS turn back on
    P1OUT |= LED_RED;
    P1OUT |= LED_GREEN;
  }
  else if (blinkCount >= 1000){  //at 4 seconds both LEDS turn off
    P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
  }
  else if (blinkCount >= 1250){  //at 5 seconds red LED turns on
    P1OUT |= LED_RED;
  }
  else if (blinkCount >= 1500){  //at 6 seconds red LED turns off 
    P1OUT &= ~LED_RED;
  }
  else if (blinkCount >= 1750){  //at 7 seconds red LED turns on
    P1OUT |= LED_RED;
  }
  else if (blinkCount > 2000){  //at 8 seconds red LED turns off and green LED turns on
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
  }
  else if (blinkCount >= 2250){ //at 9 seconds green LED turns off
    P1OUT &= ~LED_GREEN;
  }
  else if (blinkCount >= 2500){ // 100 seconds green LED turns onxs
    P1OUT |= LED_GREEN;
  }
  
  

  secondCount++;
  if (secondCount >= 250){
    secondCount = 0;
    blinkLimit++;
    if (blinkLimit >= 8){
      blinkLimit = 0;
    }
  }
}

