/*
 * ===========================================
 * = Lora gateway process for data agregate  =
 * ===========================================
 * 
 * Version : prototype
 * 
 * Content :
 * - LG01 : Dragino LoRa Gateway. Based on Arduino Yum 
 * - 2 nodes : Arduino Uno + LoRa Shield + DHT11
 */

// TODO : 
// * Add custom library for Lora Management : 
//   * Shared between server and client
//   * With simpler properties config
//   * With basic String io : ok String are bad in C, but it's C++, isn't it ? And I don't care of perf here
// * Organize code with functions

// Bauds for LG01 console 
#define BAUDRATE 115200

#include <Console.h>
#include <Process.h>
#include <SPI.h>
#include <RH_RF95.h>

// Lora radio driver
RH_RF95 rf95;
float frequency = 868.0;

// LG01 led
int HEART_LED=A2;

// Arduino setup
void setup() {
  // Heartbeat led control
  pinMode(HEART_LED, OUTPUT);

  // Network bridge for console
  Bridge.begin(BAUDRATE);

  Console.begin();
  Console.println("Start LoRa server");

  if (!rf95.init()){
    Console.println("LoRa init failed");
  }

  // Lora properties
  rf95.setFrequency(frequency);
  rf95.setTxPower(13);
  rf95.setSpreadingFactor(7);
  rf95.setSignalBandwidth(125000);
  rf95.setCodingRate4(5);
  
  Console.print("Listening on frequency: ");
  Console.println(frequency);
}

// Rest push
void uploadData(String nodeId, String payload) {

  Console.print("Call Linux Command to Send Data : ");
  Console.println(payload);
  Process p; 

  p.begin("/opt/garden/push_data_rest.sh");  
  p.addParameter(nodeId);
  p.addParameter(payload);
  p.run();

  Console.print("Feedback from Linux: ");

  // If there's output from Linux,
  // send it out the Console:
  while (p.available()>0) {
    char c = p.read();
    Console.write(c);
  }

  Console.println("");
  Console.println("Call Finished");
  Console.println("####################################");
  Console.println("");
}

// Main program
void loop() {

  // Process only when Lora is available
  if (rf95.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    // Start request process
    if (rf95.recv(buf, &len)){ 
      digitalWrite(HEART_LED, HIGH);
      RH_RF95::printBuffer("request: ", buf, len);
      Console.print("got request: ");
      Console.println((char*)buf);
      Console.print("RSSI: ");
      Console.println(rf95.lastRssi(), DEC);

      // Push to backend
      digitalWrite(HEART_LED, LOW);
      uploadData("test",(char*)buf);
      digitalWrite(HEART_LED, HIGH);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Console.println("Sent a reply");
      digitalWrite(HEART_LED, LOW);
    }
    else {
      Console.println("recv failed");
    }
  }
}
