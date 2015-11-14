
#define blue A0
#define orange A1
#define red A2
#define blue_led 3
#define red_led 5
#define green_led 6

int blue_value = 0;
int orange_value = 0;
int red_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(blue,INPUT);
  pinMode(orange,INPUT);
  pinMode(red,INPUT);
  pinMode(blue_led,OUTPUT);
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);

}

void loop() {
  blue_value = analogRead(blue)/4;

  orange_value = analogRead(orange)/4;

  red_value = analogRead(red)/4;

  
  analogWrite(blue_led,blue_value);  
  analogWrite(red_led,orange_value);
  analogWrite(green_led,red_value);
  
  Serial.println(blue_value);
  Serial.println(",");
  Serial.println(orange_value);
  Serial.println(",");
  Serial.println(red_value);
  

}
