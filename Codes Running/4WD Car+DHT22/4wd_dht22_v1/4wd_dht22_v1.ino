#include <Wire.h> //This library allows communication with I2C / TWI devices.
#include <LiquidCrystal_I2C.h> //This is a library for I2C LCD displays
#include <dht.h> //Library for DTH sensors
dht DHT; // instance of dht class named DHT
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Setup of Display with SDA -> A4 and SCL -> A5, in case 0x27 do not work replace with 0x3F

#define DHT22_PIN 10 // Signal Pin of DTH22
const int FrontPin2 = 3; // Side 2 motors Red Wire
const int BackPin2= 4; //Side 2 motors Black Wire
const int FrontPin = 5; // Side 1 motors Black Wire
const int BackPin= 6; //Side 1 motors Red Wire
const int Echo =7; // HR-SC04 pin
const int Trigger =8; // HR-SC04 pin
const int LedPin = 9; // Led Pin(+)is the curved or the shortest inside tube, 220R or bigger depending on led
const int buzzer = 12; // Buzzer (+) pin +100R

float hum;
float temp;
long dur;
long distance;
long distanceA;
long distanceB;
int stopcounter=0;
int mssturning = 500;
int f=0;

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(LedPin,OUTPUT);
  pinMode(FrontPin,OUTPUT);
  pinMode(BackPin,OUTPUT);
  pinMode(FrontPin2,OUTPUT);
  pinMode(BackPin2,OUTPUT);
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(9600);
  lcd.begin(20,4);

}

void loop()
{
  //Starting 1 time dead time for circuit to balance
  while(f !=2){
  delay(4000);f=2;}

  digitalWrite(Trigger,LOW);
  delayMicroseconds(10);
  digitalWrite(Trigger,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trigger,LOW);
  dur=pulseIn(Echo,HIGH);
  distance=dur/58.2;


if(distance>30)
{ digitalWrite(FrontPin,HIGH);
  digitalWrite(BackPin,LOW);
  digitalWrite(FrontPin2,HIGH);
  digitalWrite(BackPin2,LOW);
  Serial.println(distance);
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Obstacle :");lcd.print(distance);lcd.print("cm");
  lcd.setCursor(0,1);lcd.print("Move Forward");
  stopcounter=0;
  delay (400);
}

if(distance<15)
{
  Serial.println(distance);
  digitalWrite(FrontPin,LOW);
  digitalWrite(BackPin,LOW);
  digitalWrite(FrontPin2,LOW);
  digitalWrite(BackPin2,LOW);
  int chk =DHT.read22(DHT22_PIN);
  hum = DHT.humidity;
  temp = DHT.temperature;
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Obstacle :");lcd.print(distance);lcd.print("cm");
  lcd.setCursor(0,1);lcd.print("!!!Stopping!!!");
  lcd.setCursor(0,2);lcd.print("Humidity : ");lcd.print(hum);lcd.print("%");
  lcd.setCursor(0,3);lcd.print("Temperature : ");lcd.print(temp);lcd.print(" Celsius");
  tone(buzzer, 1000);digitalWrite(LedPin,HIGH);
  delay(900);noTone(buzzer);digitalWrite(LedPin,LOW);
  stopcounter++;
    // ean gia 2.4 second exei empodio
    if(stopcounter>4)
  {
  stopcounter=0;
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Searching for...");
  lcd.setCursor(0,1);lcd.print("Other Route!!!");
  delay(3000);
                        // peristrofh pros mia kateu8unsh
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Checking RIGHT");
  lcd.setCursor(0,1);lcd.print("!!Patience please!!");
  digitalWrite(BackPin,HIGH); delay(mssturning);
  digitalWrite(BackPin,LOW); delay(800);
  digitalWrite(Trigger,LOW);
  delayMicroseconds(10);
  digitalWrite(Trigger,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trigger,LOW);
  dur=pulseIn(Echo,HIGH);
  distanceA=dur/58.2;
                        //epistrofh sthn arxikh 8esh
  digitalWrite(FrontPin,HIGH);delay(mssturning);
  digitalWrite(FrontPin,LOW);delay(500);
                        //tsekarei apo thn allh
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Checking LEFT");
  lcd.setCursor(0,1);lcd.print("!!Patience please!!");
  digitalWrite(BackPin2,HIGH);delay(mssturning);
  digitalWrite(BackPin2,LOW);delay(800);
  digitalWrite(Trigger,LOW);
  delayMicroseconds(10);
  digitalWrite(Trigger,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trigger,LOW);
  dur=pulseIn(Echo,HIGH);
  distanceB=dur/58.2;
                      //epistrofh sthn arxikh 8esh
  digitalWrite(FrontPin2,HIGH);delay(mssturning);
  digitalWrite(FrontPin2,LOW);delay(500);
                    //Pairnei apofash
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("LEFT  =");lcd.print(distanceA);
  lcd.setCursor(0,1);lcd.print("Right =");lcd.print(distanceB);
  delay(5000);
                                                //eligmos diafughs
    if(distanceA<15 && distanceB<15)
    {
      digitalWrite(FrontPin,HIGH);digitalWrite(BackPin2,HIGH);delay(2*mssturning);
      digitalWrite(FrontPin,LOW);digitalWrite(BackPin2,LOW);
    }
    
    if(distanceA>distanceB)
     {
      digitalWrite(FrontPin2,HIGH);delay(mssturning);
      digitalWrite(FrontPin2,LOW);delay(500);
     }
     if(distanceB>distanceA)
     {
      digitalWrite(FrontPin,HIGH);delay(mssturning);
      digitalWrite(FrontPin,LOW);delay(500);                     
     }
  }}}
