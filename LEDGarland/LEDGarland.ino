/*
  LED garland
 */


const int ledCount = 6;    // the number of LEDs in the bar graph

int ledPins[] = {
  2, 3, 5, 7, 6, 4, // 8, 9, 10, 11
};

int current_mode = HIGH;

void styleOne() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    if (thisLed > 0) {
      digitalWrite(ledPins[thisLed-1], LOW);
    } else if (thisLed == 0) {
      digitalWrite(ledPins[ledCount-1], LOW);
    }
    digitalWrite(ledPins[thisLed], HIGH);
    delay(250 * max(thisLed, 1));
  }
}

void styleTwo() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    if (thisLed > 1) {
      digitalWrite(ledPins[thisLed-1], LOW);
      digitalWrite(ledPins[thisLed-2], LOW);
    } else if (thisLed == 0) {
      digitalWrite(ledPins[ledCount-1], LOW);
      digitalWrite(ledPins[ledCount-2], LOW);
    }

    if (thisLed < ledCount) {
      digitalWrite(ledPins[thisLed], HIGH);
      digitalWrite(ledPins[thisLed+1], HIGH);
    } else {
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[1], HIGH);
    }
    delay(500);
  }
}

void styleThree() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    digitalWrite(ledPins[thisLed], current_mode);
  }

  if (current_mode == HIGH) {
    current_mode = LOW;
  } else {
    current_mode = HIGH;
  }
  delay(1000);
}

const int funcs_number = 3;
int current_function = 0;


void setup() {
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop() {
  styleThree();

  /* TODO: implement the proper styles changing s
  unsigned long seconds;
  seconds = millis() / 100;

  // Change current function every X seconds
  if (seconds % 20 == 0) {
    if (current_function + 1 == funcs_number) {
      current_function = 0;
    } else {
      current_function += 1;
    }
  }

  if (current_function == 0) {
    styleOne();
  } else if (current_function == 1) {
    styleTwo();
  } else if (current_function == 2) {
    styleThree();
  }
  */
}
