#include <Arduino.h>

const int intervalos= (24*3600)/4;
const int msAberto=2000;
const int pinRele=8;


volatile int intervalosFeitos;



void setup() {
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  //compara match para 4 segundos
  OCR1A = (16e6) / (1024*(1/              4          )) - 1; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();

  // Serial.begin(9600);
  intervalosFeitos = intervalos; //inicia 
  pinMode(pinRele,OUTPUT);
  digitalWrite(pinRele, HIGH); //para nao ter estado indefinodo no pinRele
}


ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  intervalosFeitos++;
}

void loop() {
  if (intervalosFeitos>=intervalos) {
    noInterrupts(); //não deixar sem interrompido entquanto abre a mangueira

    digitalWrite(pinRele, LOW);
    // Serial.println("deu");
    delay(msAberto);
    digitalWrite(pinRele, HIGH);

    intervalosFeitos=0;
    interrupts(); //interrupts de novo
  }
}