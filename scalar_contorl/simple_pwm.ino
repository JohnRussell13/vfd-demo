#define PWM_PIN 9
#define FREQ 8000
#define PWM_REG 16000 / (FREQ/1000 * 8) - 1;
#define PER 1000000 / 8000 // in [ns]

// OCR2A = 16MHz / (F * 8) - 1
// OCR2A = (1/F) * 16MHz / 8 - 1
// OCR2A = T * 16MHz / 8 - 1 
// OCR2A = T [us] * 16 / 8 -1
// OCR2A = T [us] * 2 - 1

//storage variables
boolean toggle = 0;
double FF = 0.2;
int T = (int) (FF * PER);

void setup(){
	PWM_INIT();
}
  
ISR(TIMER2_COMPA_vect){
  	if (toggle){
      digitalWrite(PWM_PIN, HIGH);
      toggle = 0;
      OCR2A = (T<<1) - 1;
    }
    else{
      digitalWrite(PWM_PIN, LOW);
      toggle = 1;
      OCR2A = ((PER - T)<<1) - 1;
    }
}


void loop(){
  	//do other things here
}

void PWM_INIT(){
  	// SETUP PIN 9 AS PWM
    pinMode(PWM_PIN, OUTPUT);
  
    cli(); //stop interrupts
  
    TCCR2A = 0; // set entire TCCR2A register to 0
    TCCR2B = 0; // same for TCCR2B
    TCNT2  = 0; //initialize counter value to 0
    // set compare match register for 8khz increments
    OCR2A = PWM_REG;// = (16*10^6) / (8000*8) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);   
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
  
    sei();//allow interrupts
}