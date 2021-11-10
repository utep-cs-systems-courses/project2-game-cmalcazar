#include <msp430.h>
#include "leds.h"
#include "stateMachine.h"

int intensity_state = 0;
int fast_state = 0;
int blink_state = 0;

char on_off_state(int blinkCount){
  if (blinkCount % 125 == 0){
    blinkState ^= 1;
  }
  return blinkState;
}

char light_intensity_state(int blinkCount){
  if (blinkCount % 250 ==0){
    intensity_state = (intensity_state % 4) + 1;
  }
  retern intensity_state;
}

void light_25(int state){
  switch(state){
  case 0;
  case 1:
  case 2:
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 3:
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  default:
    break;
  }
}

void light_50(int state){
  switch(state){
  case 0:
  case 1:
    P1OUT &= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 2:
  case 3:
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  default:
    break;
  }
}

void light_75(int state){
  switch(state){
  case 0:
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 1:
  case 2:
  case 3:
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  default:
    break;
  }
}

void light_on(){
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;
}

char fast_blink_state(){
  fast_state = (fast_state + 1) % 4;
  switch(intensity_state){
  case 1:
    light_on(fast_state);
    break;
  case 2:
    light_25(fast_state);
    break;
  case 3:
    light_50(fast_state);
    break;
  case 4:
    light_75(fast_state);
    break;
  default:
    break;
  }
}

void state_advance(int blinkCount){
  on_off_state(blinkCount);

  if (blink_state == 0){
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED:
  }
  else{
    light_intensity_state(blinkCount);
    fast_blink_state();
  }
}
