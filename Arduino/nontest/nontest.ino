#define blue 3
#define yellow 5
#define green 6
 
void setup() {
  Serial.begin(9600);
  pinMode(blue,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
    
}

void loop(){

  digitalWrite(blue,HIGH);
  digitalWrite(green,LOW);
}
