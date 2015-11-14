
char characters[25];
char data1[7];
char data2[7];
char data3[7];
char command[3];
String S_command;
String S1;
String S2;
String S3;
float float_data1;
float float_data2;
float float_data3;
int int_data1;
int int_data2;
int int_data3;


#define accelerator 3
#define sterring 5

void setup() {
  Serial.begin(9600);
  pinMode(accelerator, OUTPUT);
  pinMode(sterring, OUTPUT);
  analogWrite(accelerator, 0);
  analogWrite(sterring, 0);

}

void loop() {

  if (Serial.available() > 0)
  {
    Serial.readBytesUntil(10, characters, 23);


    for (int x = 0; x < 2; x++) {
      command[x] = characters[x];
    }
    S_command = command;
    //Serial.println(characters);

    if (S_command == "CM") {
      for (int x = 0; x <= 4; x++) {
        data1[x] = characters[3 + x];
        data2[x] = characters[10 + x];
        data3[x] = characters[17 + x];
      }
      S1 = data1;
      S2 = data2;
      S3 = data3;

      float_data1 = S1.toFloat();
      float_data2 = S2.toFloat();
      float_data3 = S3.toFloat();

      CMMotion(float_data1, float_data2, float_data3);

      //memory of data array reset
      memset(data1, 0, sizeof(data1));
      memset(data2, 0, sizeof(data2));
      memset(data3, 0, sizeof(data3));

    } else if (S_command == "MC") {
      Serial.println("Recieved the Manual Data");
      for (int x = 0; x <= 3 ; x++) {
        data1[x] = characters[3 + x];
        data2[x] = characters[8 + x];
        data3[x] = characters[13 + x];
      }
      S1 = data1;
      S2 = data2;
      S3 = data3;

      int_data1 = S1.toInt();
      int_data2 = S2.toInt();
      int_data3 = S3.toInt();

      withoutCMMotion(int_data1, int_data2);

      memset(data1, 0, sizeof(data1));
      memset(data2, 0, sizeof(data2));
      memset(data3, 0, sizeof(data3));

    }

  }

}

//Function when there is no data from the gyro or accelerometer
void withoutCMMotion(int acceleration , int sterr ) {
  Serial.println("This is withoutCMMotion function");
  analogWrite(accelerator, acceleration);
  analogWrite(sterring, sterr);
}

//function when there is data from gyro or accelerometer
void CMMotion(float xaxes, float yaxes, float zaxes) {
  Serial.println("This is CMMotion funtion");

  int X_axes = (int)(325 - (-xaxes * 255));
  int Y_axes = (int)(yaxes * 100);// converted to display value as in 1- 100
  int Z_axes = (int)(zaxes * 225);

  Serial.println("This is the debug setting");
  Serial.println("This is the value of the X_axes :");
  Serial.print(X_axes);
  Serial.println();
  Serial.println("This is the value of the Y_axes :");
  Serial.print(Y_axes);
  Serial.println();
  Serial.println("This is the value of the Z_axes :");
  Serial.print(Z_axes);
  Serial.println();


  // this funtion will be personal. change this funtion to what u want and get the output as require.. I call this the real deal starts now
  remotecontrol(X_axes, Y_axes);
}












// didnt use sterring as variable because it is used as define the pin in arduino = 5
void remotecontrol(int tilt , int leftright) {
  int acceleration;
  int sterr;
  /* this funtion is the main brain to control the output for the remote control.
   *  this funtion correspond to the given graph. so after all the success in reading the data from the ipad and sending to the server
   *  now is the time for arduino use the data effectively and giving the command to the controller to move the car to the direction which i wants
   *  Ranges
   *    if 0- 91 then send the value of around 144 till 172
   *    if 92 - 144 then it is ok.
   *    if value is 172 till 225 then it is ok.
   */

  //setting the tilt only for acceleration
  //this is for the range if unkn
  if (tilt < 91) {
    acceleration =  159;
  } else if ( tilt <= 144 & tilt >= 92 || tilt <= 230 & tilt >= 173) { // this is for the range of A and B
    acceleration = tilt;
  } else if (tilt <= 172 & tilt >= 145) { //setting optimised breaking 2.5V
    acceleration = 159;
  } else {
    acceleration = 240;
  }

  //Setting the LeftRight condition
  /* so for the left condition is performed as the 91 till 144 of the  as the representation from the ipad is 0.03 till 0.56 each 0.01 increment in ipad data is minus 1 in the variable of the leftright variable
   *
   */

  if ( leftright >= 3 & leftright <= 56) {
    sterr = 144 - ( leftright - 3);
  } else if (leftright <= -3 & leftright >= -56) {
    sterr = 172 - ( leftright + 3); // hv to correct the algebra
  } else if ( leftright > 56) {
    sterr = 91;
  } else if (leftright < -56) {
    sterr = 255; // change this and fine a better formular
  } else {
    sterr = 170;
  }

  analogWrite(accelerator, acceleration);
  analogWrite(sterring, sterr);

}

