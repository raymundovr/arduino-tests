const byte sevenSegValues[] = {
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

const int letras[] = {
  248,  //A
  254, // M
};

const int dataPin = 2;
const int latchPin = 4;
const int clockPin = 6;
const int buttonOnePin = 8;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buttonOnePin, INPUT);
}

byte count = 0;

void loop() {
  if (digitalRead(buttonOnePin) == HIGH) {
    while(digitalRead(buttonOnePin) != LOW) {
      //
    }
    if (count == 15) {
      count = -1;
    }
    count++;
  }
  sevenSegWrite(count);
}

void sevenSegWrite(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, sevenSegValues[digit]);
  digitalWrite(latchPin, HIGH);
}
