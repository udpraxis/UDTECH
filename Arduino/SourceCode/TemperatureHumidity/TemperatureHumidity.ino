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
  Serial.begin(9600);
  dht.begin();
  
}

void loop() 
{
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Check if the any reads failed and exit early
  if(isnan(h)||isnan(t))
  {
    Serial.println("Failed to read from DHT Sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(t,h,false);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("*c\t");
  Serial.print("Heat Index: ");
  Serial.print(hic);
  Serial.println("*c");
  

}
