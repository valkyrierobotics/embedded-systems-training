int base_timer = 0;
int high_timer = 0;
bool high_state = 0;
bool base_state = 0;
void setup() {
  // initialize LED
  pinMode(LED_BUILTIN, OUTPUT);

  // set up timer
  TCCR0A|=(1<<WGM01);    //Set the CTC mode
  OCR0A=0xF9;            //Set the value for 1ms
  TIMSK0|=(1<<OCIE0A);   //Set the interrupt request
  sei();                 //Enable interrupt
  TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR0B|=(1<<CS00);
}

void loop() {
  if (base_state) {
    if (high_timer >= 96) {
      high_state = 0;
    } else {
      high_state = 1;
    }
    if (high_timer >= 128) {
      high_timer = 0;
    }
    
    digitalWrite(LED_BUILTIN, high_state);
  } else {
    high_state = 0;
  }
  if (base_timer >= 1024) {
    base_state = !base_state;
    base_timer = 0;
  }

  digitalWrite(LED_BUILTIN, high_state);
}


ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  high_timer++;
  base_timer++;
}
