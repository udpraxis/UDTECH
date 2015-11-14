
char characters[17];
char data1[6];
char data2[6];
char data3[6];
String S1;
String S2;
String S3;
float int_data1;
float int_data2;
float int_data3;


void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  analogWrite(2,0);

}

void loop() {

  if (Serial.available() > 0)
  {
    Serial.readBytesUntil(10, characters, 17);

    for (int x = 0; x < 5; x++) {
      data1[x] = characters[x];
      data2[x] = characters[x + 6];
      data3[x] = characters[x + 12];
      

      
    }
      S1 = data1;
      S2 = data2;
      S3 = data3;
      int_data1 = S1.toFloat();
      int_data2 = S2.toFloat();
      int_data3 = S3.toFloat();
    
    Serial.println("Raw Data:");
    Serial.print(characters);
    Serial.println();
    Serial.println("DATA1:");
    Serial.print(data1);
    Serial.println(S1);
    Serial.println(int_data1);
    Serial.println();
    Serial.println("DATA2:");
    Serial.print(data2);
    Serial.println(S2);
    Serial.println(int_data2);
    Serial.println();
    Serial.println("DATA3:");
    Serial.print(data3);
    Serial.println(S3);
    Serial.println(int_data3);
    Serial.println();
    Serial.println("This is te Prove tat this formular works");
    Serial.println(int_data3 - 0.1);
   
  }
 for(int x= 255; x < 1023 ; x++){
  analogWrite(3,240);
 }

}

