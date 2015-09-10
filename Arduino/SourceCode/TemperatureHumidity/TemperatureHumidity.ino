/**This is the mega project to set up automated 
 *    temperature and humidity reading 
 */
#include <DHT.h>

//Setting the pin DHT11 connected to 
#define DHTPIN 2

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
  
  Serial.begin(9600);
  dht.begin();
  
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Check if the any reads failed and exit early
  if(isnan(h)||isnan(t))
  {
    Serial.println("Failed to read from DHT Sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(t,h,false);


  Serial.print(h);                //Humiditylevel
  Serial.print(",");              
  Serial.print(t);                //Temperature
  Serial.print(",");      
  Serial.println(hic);              //HeatIndex
  delay(250);

}
