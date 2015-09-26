/**This is the project to set up automated 
 *    -temperature and humidity reading Using Sensor DHT11 type
 *    -Detect Rain using Rain Sensor
 *     @DarwinSUbramaniam
 *    
 *    permission in Linux : sudo chmod 666 /dev/ttyACM0
 */
#include <DHT.h>

//Setting the pin Sensor connected to 
#define DHTPIN 2
#define Rain A0

//Setting which type of the DHT sensor
#define DHTTYPE DHT11

//Object of the DHT
DHT dht(DHTPIN,DHTTYPE);

void setup() 
{
/*China Made Arduino, LED13 always HIGH*/
/**/  pinMode(13,OUTPUT);            /**/
/**/  digitalWrite(13,LOW);          /**/
/***************************************/

/*Setup need to start the program*/
  Serial.begin(9600);
  pinMode(Rain,INPUT);
  dht.begin();
  
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int rain_input = analogRead(Rain);

  //Check if the any reads failed and exit early
  if(isnan(h)||isnan(t))
  {
    Serial.println("Failed to read from DHT Sensor!");
    return;
  }
  if(isnan(rain_input))
  {
    Serial.println("Failed to read from Rain Sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(t,h,false);

  Serial.println(rain_input);
  Serial.print(",");
  Serial.print(h);                  //Humiditylevel
  Serial.print(",");              
  Serial.print(t);                  //Temperature
  Serial.print(",");      
  Serial.println(hic);              //HeatIndex*/
  delay(1000);                      //delay 1 second

}
