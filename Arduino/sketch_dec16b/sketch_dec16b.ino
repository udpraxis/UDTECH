

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);

}

void loop() {
  analogWrite(3,150);

}
