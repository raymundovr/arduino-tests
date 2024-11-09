#define NOTE_C 131
#define NOTE_D 147
#define NOTE_E 165
#define NOTE_F 175
#define NOTE_G 196
#define NOTE_A 220
#define NOTE_B 247

const byte DISPLAY_VALUES[] = {
  // ABCDEFGP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
  B11101110,  // A
  B00111110,  // B
  B10011100,  // C
  B01111010,  // D
  B10011110,  // E
  B10001110,  // F
};

const byte MELODY[] = { NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G, NOTE_G, NOTE_G, NOTE_G, 0, NOTE_F, NOTE_G, NOTE_A, NOTE_G};
const byte NOTE_DURATIONS_MELODY[] = { 150, 150, 150, 150, 150, 150, 150, 150, 150, 200, 200, 250, 250};
const byte LED_NOTES[] = { NOTE_C, NOTE_D, NOTE_F, NOTE_G };
const int NOTE_DURATION = 500;  // ms

/* In */
const byte BUTTON_0 = 6;
const byte BUTTON_1 = 8;
const byte BUTTON_2 = 10;
const byte BUTTON_3 = 12;
const byte INPUTS[] = { BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3 };
/* --- */

/* Out */
const byte DATA = 2;
const byte LATCH = 3;
const byte CLOCK = 4;
const byte BUZZER = 13;
const byte LED_0 = 5;
const byte LED_1 = 7;
const byte LED_2 = 9;
const byte LED_3 = 11;
const byte OUTPUTS[] = { DATA, LATCH, CLOCK, BUZZER, LED_0, LED_1, LED_2, LED_3 };
const byte LEDS[] = { LED_0, LED_1, LED_2, LED_3 };
/* --- */

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(INPUTS[i], INPUT);
  }

  for (byte i = 0; i < 8; i++) {
    pinMode(OUTPUTS[i], OUTPUT);
  }
}

const byte MAX = 2;
bool isPlaying = true;
bool hasWon = true;
byte sequence[MAX];
byte currentPosition = 0;

void loop() {
  while (isPlaying && currentPosition < MAX) {
    int next = getRandom(4);
    sequence[currentPosition] = next;
    currentPosition++;
    sevenSegWrite(currentPosition);
    playSequence();
    if (!isUserSequenceCorrect()) {
      hasWon = false;
      isPlaying = false;
    }
  }
  if (hasWon) {
    playSong();
  } else {
    sevenSegWrite(15);  // fail
  }
  delay(5000);
  reset();
}

void reset() {
  isPlaying = true;
  hasWon = true;
  currentPosition = 0;
}

void playSequence() {
  for (byte led = 0; led < currentPosition; led++) {
    byte currentLed = sequence[led];
    digitalWrite(LEDS[currentLed], HIGH);
    tone(BUZZER, LED_NOTES[currentLed], NOTE_DURATION);
    delay(NOTE_DURATION);
    digitalWrite(LEDS[currentLed], LOW);
    delay(NOTE_DURATION);
  }
}

bool isUserSequenceCorrect() {
  byte currentInput = 0;
  bool isOk = true;
  byte noteDuration = 50;
  while (currentInput < currentPosition) {
    if (digitalRead(BUTTON_0) == HIGH) {
      while (digitalRead(BUTTON_0) == HIGH) {
        tone(BUZZER, LED_NOTES[0], noteDuration);
        digitalWrite(LED_0, HIGH);
      }
      digitalWrite(LED_0, LOW);
      if (sequence[currentInput] != 0) {
        return false;
      }
      currentInput++;
    }
    if (digitalRead(BUTTON_1) == HIGH) {
      while (digitalRead(BUTTON_1) == HIGH) {
        tone(BUZZER, LED_NOTES[1], noteDuration);
        digitalWrite(LED_1, HIGH);
      }
      digitalWrite(LED_1, LOW);

      if (sequence[currentInput] != 1) {
        return false;
      }
      currentInput++;
    }
    if (digitalRead(BUTTON_2) == HIGH) {
      while (digitalRead(BUTTON_2) == HIGH) {
        tone(BUZZER, LED_NOTES[2], noteDuration);
        digitalWrite(LED_2, HIGH);
      }
      digitalWrite(LED_2, LOW);

      if (sequence[currentInput] != 2) {
        return false;
      }
      currentInput++;
    }
    if (digitalRead(BUTTON_3) == HIGH) {
      while (digitalRead(BUTTON_3) == HIGH) {
        tone(BUZZER, LED_NOTES[3], noteDuration);
        digitalWrite(LED_3, HIGH);
      }
      digitalWrite(LED_3, LOW);

      if (sequence[currentInput] != 3) {
        return false;
      }
      currentInput++;
    }
  }

  delay(1000);
  return true;
}

void playSong() {
  for (byte i = 0; i < 13; i++) {
    tone(BUZZER, MELODY[i], NOTE_DURATIONS_MELODY[i]);
    delay(NOTE_DURATIONS_MELODY[i] + 50);
  }
}

int getRandom(int max) {
  randomSeed(analogRead(0));
  return random(max);
}

void sevenSegWrite(int digit) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, DISPLAY_VALUES[digit]);
  digitalWrite(LATCH, HIGH);
}
