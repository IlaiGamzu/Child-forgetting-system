#include <LiquidCrystal_I2C.h>
#include <Wire.h>  

//dht11
#include <dht11.h>
#define DHT11PIN 4

4dht11 DHT11;
//#include <LCD_I2C.h>

#define SS_PIN 10    // Slave Select Pin (SS)
#define RST_PIN 9    // Reset Pin
#define BUZZER_PIN 7 // Pin for the Buzzer
LiquidCrystal_I2C lcd (0x27,16,2); // give 2 rows and 16 char i each row, start from 0x27
const int irSensorPin = 2; // Connect the IR sensor to digital pin 2
const int relayPin = 7;    // Connect the relay module to digital pin 7
const int buzzerPin = 8;   // Connect the buzzer to digital pin 8 (optional)
//LCD_I2C lcd(0x27);


void setup() {
//dht11
  Serial.begin(9600); 

//lcd 1602
  lcd.begin(16, 2);
  lcd.print("Child Presence");
  pinMode(irSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Simulate car ignition as initially on
}

void loop() {

//lcd+ buzzer+relay

  int irValue = digitalRead(irSensorPin);

  if (irValue == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("Child detected");

    // Check if car is turned off (relay is off)
    if (digitalRead(relayPin) == LOW) {
      lcd.setCursor(0, 1);
      lcd.print("Child in danger!");

      // Sound the buzzer (optional)
      tone(buzzerPin, 1000, 1000); // 1kHz tone for 1 second
      delay(2000); // Wait for 2 seconds before rechecking

      // You may want to implement additional actions, such as sending an alert message, etc.
    }
  } else {
    lcd.setCursor(0, 1);
    lcd.print("No child detected");
  }

  delay(1000); // Adjust the delay based on your needs

  //DHT11
  Serial.println();  // Print an empty line for better readability

  int chk = DHT11.read(DHT11PIN);  // Read data from the DHT11 sensor connected to the specified pin

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);  // Print the humidity value with two decimal places

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);  // Print the temperature value with two decimal places

  delay(2000);  // Delay for 2 seconds before the next reading
}
