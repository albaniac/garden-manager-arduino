/*
 * ===========================================
 * = Locally managed sensors with LCD screen =
 * ===========================================
 * 
 * Version : prototype
 * 
 * Content :
 * - LCD1602A : 2*16 LCD screen
 * - DHT11 : Humidity / temperature sensor
 * - DS3231 : I2c Real Time Clock
 * - Requires also :
 *   - 10k potentiometer for LCD screen
 *   - 2 ways push button
 */

// Screen
#include <LiquidCrystal.h>
// Humidity / temp sensor
#include <SimpleDHT.h>
// I2C 
#include <Wire.h>
// RTC with I2C
#include <DS3231.h>

/*
 * ######## Sensor / modules init #########
 */

// Init RTC
DS3231 clock;
RTCDateTime dt;

// Init Screen => set interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Init DHT11
SimpleDHT11 dht11;
const int pinDHT11 = 2;

// Button pin
const int buttonApin = 6;

/*
 * ########### Local variables ##########
 */
 
// Temperature and Humidity are stabilized on change
int lastTemp = 0;
int lastHumid = 0;

// Mode management with filtered button push
int previousMode = 2;
int currMode = 1;

/*
 * ########### Arduino init ##########
 */
void setup() {
  // Enable Serial, 9600 Bauds
  Serial.begin(9600);

  // Enable pin button
  pinMode(buttonApin, INPUT_PULLUP);
    
  // Setup LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Start clock management
  clock.begin();
  
  // Set sketch compiling time (uncomment for new time)
  // clock.setDateTime(__DATE__, __TIME__);
}

/*
 * ########### Process functions ##########
 */
 
// Write locally datetime
void readRTC(){
  dt = clock.getDateTime();
}

// Write locally temperature and humidity
void readDHT11() {
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};

  // Keep correct read only
  if (!dht11.read(pinDHT11, &temperature, &humidity, data)) {
    lastTemp = (int)temperature;
    lastHumid = (int)humidity;
  }
}

/*
 * ########### Arduino program ##########
 */
void loop() {

  // Get current DT
  readRTC();
  
  // Gather humidity / temp, even if not ready
  readDHT11();

  // 5 pages display, regarding mode
  if(currMode == 1){
    lcd.setCursor(0, 0);
    lcd.print("Humidity :      ");
    lcd.setCursor(0, 1);
    lcd.print("%:");
    lcd.setCursor(3, 1);
    lcd.print(lastHumid);
  } else if(currMode == 2){
    lcd.setCursor(0, 0);
    lcd.print("Temperature :   ");
    lcd.setCursor(0, 1);
    lcd.print("C:");
    lcd.setCursor(3, 1);
    lcd.print(lastTemp);
  } else if(currMode == 3){
    lcd.setCursor(0, 0);
    lcd.print("Time :          ");
    lcd.setCursor(0, 1);
    lcd.print(clock.dateFormat("H:i:s", dt));
  } else if(currMode == 4){
    lcd.setCursor(0, 0);
    lcd.print("Date :          ");
    lcd.setCursor(0, 1);
    lcd.print(clock.dateFormat("Y-m-d", dt));
  } else if(currMode == 5){
    lcd.setCursor(0, 0);
    lcd.print("Maya arrete de  ");
    lcd.setCursor(0, 1);
    lcd.print("jouer avec ca ! ");
  }

  // Serial outputs : temperature, humidity, RTC
  Serial.print(lastTemp); Serial.print(" *C, ");
  Serial.print(lastHumid); Serial.println(" %");
  Serial.print("RTC:"); Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));

  // Pushed button
  if (digitalRead(buttonApin) == LOW){
    
    // Changing mode
    if(currMode == previousMode){
      
       // Reset print
       lcd.setCursor(0, 1);
       lcd.print("                     ");
    
       // Switch current mode
       currMode++;
       if(currMode > 5){
         currMode = 1;
       }
    }
  } 

  // Else record current for filtering
  else {
    previousMode = currMode;
  }

  // Compromize between interactivity and sensor use
  delay(500);
}

