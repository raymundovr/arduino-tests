// Color - Pin
#define R 4
#define G 5
#define B 6

#define DELAY 10 // ms

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
}

void loop() {
  int red = 255;
  int green = 0;
  int blue = 0;

  for (int i = 1; i <= 255; i++) {
    red--;
    blue++;
    analogWrite(R, red);
    analogWrite(B, blue);
    delay(DELAY);
  }

  delay(500);
  for (int i = 1; i <= 255; i++) {
    blue--;
    green++;
    analogWrite(G, green);
    analogWrite(B, blue);
    delay(DELAY);
  }

  delay(500);
  for (int i = 1; i <= 255; i++) {
    green--;
    red++;
    analogWrite(G, green);
    analogWrite(R, red);
    delay(DELAY);
  }
  delay(1000);
}
