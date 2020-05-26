#include <dht.h> //library for dht sensors
#include <Wire.h> //library for I2C connection
#include <LiquidCrystal_I2C.h> //librady for I2C display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Enable LCD use SDA = A4 and SCL = A5
dht DHT; // instance of dht class named DHT

#define DHT11_PIN 7 // Arduino Digital Pin Connected to DHT11 

void setup(){
  lcd.begin(16, 2); //Setting Screen as 16x2
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN); //Reading From Sensor
  lcd.setCursor(0,0); 
  lcd.print("Temp:     ");
  lcd.print(int(DHT.temperature)); // Printing temp without decimals(int)
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(int(DHT.humidity)); // Printing humidity without decimals(int)
  lcd.print("%");
  delay(1000);
}
