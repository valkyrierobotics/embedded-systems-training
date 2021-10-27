#ifndef __VLIB_H
#define __VLIB_H

void irq_setup(void);

long int timer = 0;
static long int internal_timer = 0;

void irq_setup(void) {
  /* Setup timer interrupt */
  TCCR0A |= (1 << WGM01);  // Set the CTC mode
  OCR0A   = 0xF9;          // Set the value for 1ms
  TIMSK0 |= (1 << OCIE0A); // Set the interrupt request
  sei();                   // Enable interrupt
  TCCR0B |= (1 << CS01);   // Set the prescale 1/64 clock
  TCCR0B |= (1 << CS00);
}

/* Interrupt service routine for the timer interrupt. */
ISR(TIMER0_COMPA_vect) {
  internal_timer++;
  timer = internal_timer;
}

#endif // __VLIB_H
