#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

const int intervalos = (24 * 3600) / 5;
const int msAberto = 2000;
const int pinRele = 8;

volatile int intervalosFeitos;

void setup()
{
  Serial.begin(9600);
  intervalosFeitos = 0;       //inicia
  digitalWrite(pinRele, LOW); //para nao ter estado indefinodo no pinRele
}

ISR(WDT_vect)
{
  wdt_disable(); // disable watchdog
} // end of WDT_vect

void sleep()
{
    ADCSRA = 0;

  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset
  WDTCSR = bit(WDCE) | bit(WDE);
  // set interrupt mode and an interval
  WDTCSR = bit(WDIE) | bit(WDP3) | bit(WDP0); // set WDIE, and 8 seconds delay
  wdt_reset();                                // pat the dog

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts(); // timed sequence follows
  sleep_enable();

  // turn off brown-out enable in software
  MCUCR = bit(BODS) | bit(BODSE);
  MCUCR = bit(BODS);
  interrupts(); // guarantees next instruction executed
  sleep_cpu();

  // cancel sleep as a precaution
  sleep_disable();
}

void loop()
{
  if (intervalosFeitos >= intervalos)
  {
    noInterrupts(); //não deixar sem interrompido entquanto abre a mangueira

    digitalWrite(pinRele, HIGH);
    // Serial.println("deu");
    delay(msAberto);
    digitalWrite(pinRele, LOW);

    intervalosFeitos = 0;
    delay(10000); //espera um pouco pra dormir de novo
    interrupts(); //interrupts de novo
  }
  intervalosFeitos++;
  sleep();
}