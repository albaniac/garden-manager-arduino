//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;

int lastTemp = 0;
int lastHumid = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
  } else {
    lastTemp = (int)temperature;
    lastHumid = (int)humidity;
  }
  
  Serial.print("Get values: ");
  Serial.print(lastTemp); Serial.print(" *C, ");
  Serial.print(lastHumid); Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  delay(1000);
}
