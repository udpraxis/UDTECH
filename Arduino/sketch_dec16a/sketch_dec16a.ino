/****All the pin naming***/
#define forward_pedal 3
#define backward_pedal 5
#define right_pedal 6
#define left_pedal 9

/**********All variable naming*****************/
char data_recieve[25];
boolean debug_mode = true;
String S_command;
String S_speed;
String S_steering;
//Variable needed to hold the data fraction
char data_speed[10];  // data which is still in array form
char data_steering[10]; // data which is still in array form
char command[2];
bool wasForward;
bool wasRightTurn;
int int_speed;
int int_turn;
bool activemode;
int speed_p;
int turn_p;
bool brakingdone ;



void setup() {

  Serial.begin(9600);
  pinMode(forward_pedal, OUTPUT);
  pinMode(backward_pedal, OUTPUT);
  pinMode(right_pedal, OUTPUT);
  pinMode(left_pedal, OUTPUT);

  analogWrite(forward_pedal, 0);
  analogWrite(backward_pedal, 0);
  analogWrite(right_pedal, 0);
  analogWrite(left_pedal, 0);
  brakingdone = true;
  speed_p = 0;
  turn_p = 0;
  activemode = false;
  // put your setup code here, to run once:

}

void loop() {
  
    if (Serial.available() > 0) {
      Serial.readBytesUntil(10, data_recieve, 23);
      if (brakingdone) {
      synthesisData(data_recieve);
      }
      Serial.flush();
    }
    memset(data_recieve, 0, sizeof(data_recieve));
   
}

//Function to synthesis data recieved. The data will be in the form of bytes. so now the parts of data looks like this MC:000:000@ so the data is in 3 parts which is identified using the ":" and end with "@".
void synthesisData(char data[]) {
  if (debug_mode) {
    Serial.println(data);
  }

  //Ths Part of code will ensure the data CM/MC extracted properly
  int indexOfLastData = 0;

  //The commond mode is synthesis here .
  for (indexOfLastData; checkfor(':', data[indexOfLastData]) ; indexOfLastData++) {
    command[indexOfLastData] = data[indexOfLastData];

  }
  S_command = command;

  if (debug_mode) {
    Serial.println(S_command);
  }

  indexOfLastData += 1;
  //Speed data is synthesised here
  // THIS TO DO NEXT IS TO use the IndexOfLastData to jump btw the synthesiser. it will ensure the command can be more than 2 alphabets or less . with current design command must in 2 alphabets
  for (int x = 0; checkfor(':', data[x + 3]) ; x++) {
    data_speed[x] = data[indexOfLastData];
    indexOfLastData += 1; // add one for the last data index to begin steering search at the right data index omit the ":"
  }
  S_speed = data_speed;

  if (debug_mode) {
    Serial.print("This is the Speed :");
    Serial.println(S_speed);
  }

  int x = 0;
  indexOfLastData += 1;
  for (indexOfLastData; checkfor('@', data[indexOfLastData]); indexOfLastData++) {
    data_steering[x] = data[indexOfLastData];
    x += 1;
  }
  S_steering = data_steering;

  if (debug_mode) {
    Serial.print("This is the Steering :");
    Serial.println(S_steering);
    Serial.print("");
  }

  //Start the action on car
  conditionManager(S_command, S_speed, S_steering);

  //Delete the data and execute command before this
  memset(command, 0, sizeof(command));
  memset(data, 0, sizeof(data));
  memset(data_speed, 0, sizeof(data_speed));
  memset(data_steering, 0, sizeof(data_steering));


}

//Funtion which return false if the element searching is found and true if the element is not found. Very useful for searching data thru for loops.
bool checkfor(char element, char data) {
  Serial.println("Check for");
  Serial.println(data);
  if (element == data) {
    Serial.println("ending");
    return false;

  } else {
    return true;
  }
}


void conditionManager(String command, String speed, String turnlimit) {
  if (debug_mode) {
    Serial.println("");
    Serial.println("ConditionManager is started");
    Serial.println("");
  }

  //what to do if gyro data is recieved
  if (command == "CM") {

  } else if (command == "MC") { //What to di if manual data is recieved
    //convert string data to integer
    int_speed = speed.toInt();
    int_turn = turnlimit.toInt();

    //all the possible forward and backward condition
    if (wasForward == true && int_speed < 0) {// was in forward so brake first and then move backward.
      if (debug_mode) {
        Serial.println("");
        Serial.println("Brake and then move backward");
        Serial.println("");
      }
      brake();
      backward(-int_speed);
      wasForward = false;

    } else if (wasForward == false && int_speed > 0) {//was in backward so brake first and then move forward.
      if (debug_mode) {
        Serial.println("");
        Serial.println("Brake and then move forward");
        Serial.println("");
      }
      brake();
      forward(int_speed);
      wasForward = true;
    } else if (wasForward == true && int_speed > 0) {//Continue to move forward.
      if (debug_mode) {
        Serial.println("");
        Serial.println("continue move forward");
        Serial.println("");
      }
      forward(int_speed);
    } else if (wasForward == false && int_speed < 0) {//Continue to move backward.
      if (debug_mode) {
        Serial.println("");
        Serial.println("continue move backward");
        Serial.println("");
      }
      backward(-int_speed);
    } else if (int_speed == 0) {// Braking condition.
      Serial.println("");
      Serial.println("Braking");
      Serial.println("");
      brake();
    }

    //Possible condition for the steering section
    if (int_turn > 0) {
      if (debug_mode) {
        Serial.println("");
        Serial.println("Turning Right");
        Serial.println("");
      }
      turnRight(int_turn + 50);
      wasRightTurn = true;
    } else if (int_turn < 0) {
      if (debug_mode) {
        Serial.println("");
        Serial.println("Turning Left");
        Serial.println("");
      }
      turnLeft(-int_turn + 50);
      wasRightTurn = false;
    } else if (int_turn == 0) {
      if (debug_mode) {
        Serial.println("");
        Serial.println("Moving Straight");
        Serial.println("");
      }
      if (wasRightTurn) {
        if (debug_mode) {
          Serial.println("");
          Serial.println("From right turn to straight");
          Serial.println("");
        }
        turnRight(0);
        wasRightTurn = false;
      } else {
        if (debug_mode) {
          Serial.println("");
          Serial.println("From left turn to straight");
          Serial.println("");
        }
        turnLeft(0);
        wasRightTurn = false;
      }
    } else {
      Serial.println("Turn Data error");
    }
  } else {
    Serial.println("Data command is corrupted"); // Data is read wrongly throwing error ..... change this accordingly when the command from the server is no longer CM or MC only
  }
}


void forward(int speed) {
  if (speed != speed_p) {
    analogWrite(forward_pedal, speed + 50);
    activemode = true;
    speed_p = speed;
    delay(500);

  }
}

void brake() {
  if (activemode) {
    if (wasForward == true) {
      analogWrite(forward_pedal, 0);
      activemode = false;
      brakingdone = false;
      wasForward = false;
      delay(3000);
      brakingdone = true;
      Serial.flush();
    } else {
      analogWrite(backward_pedal, 0);
      activemode = false;
      brakingdone = false;
      wasForward = false;
      delay(3000);
      brakingdone = true;
      Serial.flush();
    }
  }
}

void backward(int speed) {
  if (speed != speed_p) {
    analogWrite(backward_pedal, speed);
    activemode = true;
    speed_p = speed;
    delay(500);
  }
}

void turnRight(int turnLimit) {
  if (turn_p != turnLimit) {
    analogWrite(right_pedal, turnLimit);
    turn_p = turnLimit;
    delay(500);
  }
}

void turnLeft(int turnLimit) {
  if (turn_p != turnLimit) {
    analogWrite(left_pedal, turnLimit);
    turn_p = turnLimit;
    delay(500);
  }
}

