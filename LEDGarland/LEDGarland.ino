/*
  LED garland
 */


const int ledCount = 6;

int ledPins[] = {2, 3, 5, 7, 6, 4};  // adjust numbers depending on wiring

void setup() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop() {
//  styleThree();
//  styleOneByOne();
  styleComplexQueue();
}

/*
 * ======================
 * Different blink styles
 * ======================
 */

/*
 * Constant blinking of all leds
 */
int ledMode = HIGH;

void styleSimple() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], ledMode);
  }

  if (ledMode == HIGH) {
    ledMode = LOW;
  } else {
    ledMode = HIGH;
  }
  delay(1150);
}


/*
 * Blink leds one by one
 */
void styleOneByOne() {
  for (int i = 0; i < ledCount; i++) {
    // turn off the previous led
    if (i > 0) {
      digitalWrite(ledPins[i-1], LOW);
    } else {
      digitalWrite(ledPins[ledCount-1], LOW);
    }

    // turn on the current led
    digitalWrite(ledPins[i], HIGH);
    delay(500);
  }
}

/*
 * Turn ON leds one by one unti the last of them then keep it ON.
 * Repeat until all of them will be ON.
 * Then blink using all leds (change "simpleStyleNum" to define the number of "blinks") several times.
 * Repeat everything.
 * 
 */
int ledEnabledNum = ledCount;
int simpleStyleNum = 7;  // how many times all leds should be ON

void styleComplexQueue() {
  for (int i = 0; i < ledEnabledNum; i++) {
    if (i > 0) {
      digitalWrite(ledPins[i-1], LOW);
    }
    digitalWrite(ledPins[i], HIGH);
    delay(250);
  }

  ledEnabledNum--;

  if (ledEnabledNum < 0) {
    ledMode = LOW; // first cycle of "styleSimple" should disable all leds
    int cyclesNum = simpleStyleNum * 2 + 1; // equal number of OFF and ON cycles + 1 to turn OFF all leds at the first iteration
    for (int i = 0; i < cyclesNum; i++) {
      styleSimple();
    }
    ledEnabledNum = ledCount;
  }
}
