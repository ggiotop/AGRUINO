#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const int FrontPin2 = 3;
const int BackPin2= 4;
const int FrontPin = 5;
const int BackPin= 6;
const int Trigger =8;
const int Echo =7;
const int buzzer = 12;

long dur;
long distance;
long distanceA;
long distanceB;
int stopcounter=0;
int mssturning = 1200;

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(FrontPin,OUTPUT);
  pinMode(BackPin,OUTPUT);
  pinMode(FrontPin2,OUTPUT);
  pinMode(BackPin2,OUTPUT);
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);

}

void loop()
{
  //starting lcd
  //lcd.clear();
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
  lcd.clear();lcd.setCursor(0,0);
  lcd.print("Obstacle :");lcd.print(distance);lcd.print("cm");
  lcd.setCursor(0,1);lcd.print("!!!Stopping!!!");
  tone(buzzer, 1000);
  delay(600);noTone(buzzer);
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
  lcd.print("Checking LEFT");
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
  lcd.print("Checking RIGHT");
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
