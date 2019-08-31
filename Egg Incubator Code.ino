#include <Wire.h> // Include Wire.h to control I2C
#include <LiquidCrystal_I2C.h> //Download & include the code library can be downloaded below
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); // pins connected to LCD
#include "DHT.h"
#include <EEPROM.h>
#define DHTPIN 2 // definisikan pin yang digunakan utk sensor DHT11

// Tentukan jenis DHT yang digunakan (pilih salah satu)
// Saat ini yang dipilih adalah DHT11
#define DHTTYPE DHT11 // DHT 11 


DHT dht(DHTPIN, DHTTYPE);

#define RELAY_ON 0
#define RELAY_OFF 1
#define RELAY_1  8   // pin yang digunakan yaitu pin 8

#define suhuon 11
#define suhuoff 12

  float h = dht.readHumidity();
  float t = dht.readTemperature();

long durasiSerial = 0;
long durasiLed = 0;
long jedaText = 3000;
long jedaLed = 8000;
long jedaSerial = 12000;


int S = 59; // count seconds 
int M = 59; // count minutes
int H = 23; // count hours
int D = 20;
int i;
  
void setup()
{
  Serial.println("DHTxx test!");
  dht.begin();
  
 // Set pin as output.
  pinMode(RELAY_1, OUTPUT);
  pinMode(suhuon, OUTPUT);
  pinMode(suhuoff, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
   
 // Initialize relay one as off so that on reset it would be off by default
  digitalWrite(RELAY_1, RELAY_OFF);
  
  lcd.begin (16,2);
  Serial.begin(9600); 
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  unsigned long curr = millis();


 S = EEPROM.read(60);
 M = EEPROM.read(61);
 H = EEPROM.read(0);
 D = EEPROM.read(1);

   if (D<0)
 {
 D=20;
 H=23;
 M=59;
 S=59;
 }
 
  S--;
 delay(1000);

 if(S<0)
 {
 M--;
 S=59;
 }
 
 if(M<0)
 {
 H--;
 M=59;
 }
 
 if(H<0)
 {
 D--;
 H=23;
 }

 EEPROM.write(60, S);
 EEPROM.write(61, M);
 EEPROM.write(0, H);
 EEPROM.write(1, D);


 if(S==50 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, HIGH);
  }
  if(S==48 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, LOW);
  }
  if(S==47 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, HIGH);
  }
  if(S==45 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, LOW);
  }
  if(S==44 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, HIGH);
  }
  if(S==41 && M==59 && H==23 && D==2)
  {
    digitalWrite(7, LOW);
  }


  if(S==50 && M==59 && H==23 && D==1)
  {
    digitalWrite(7, HIGH);
  }
  if(S==48 && M==59 && H==23 && D==1)
  {
    digitalWrite(7, LOW);
  }
  if(S==47 && M==59 && H==23 && D==1)
  {
    digitalWrite(7, HIGH);
  }
  if(S==44 && M==59 && H==23 && D==1)
  {
    digitalWrite(7, LOW);
  }

  
   if(S==10 && M==0 && H==0 && D==0)
  {
    digitalWrite(7, HIGH);
  }
  if(S==0 && M==0 && H==0 && D==0)
  {
    digitalWrite(7, LOW);
  }

  if(H==21)
   {
    digitalWrite(10, HIGH);
  }
  if(H==20)
  {
    digitalWrite(10, LOW);
  }
  if(H==15)
   {
    digitalWrite(10, HIGH);
  }
  if(H==14)
  {
    digitalWrite(10, LOW);
  }
  if(H==9)
   {
    digitalWrite(10, HIGH);
  }
  if(H==8)
  {
    digitalWrite(10, LOW);
  }
//displaylcd

 if(curr - durasiSerial < jedaText)
      {
        lcd.clear();
        text();  
      }
      if(curr - durasiSerial > jedaText)
       {
       lcd.clear();       // suhu();
       lcd.setCursor(0,0);
       lcd.print("Humi: "); 
       lcd.print(h);
       lcd.print(" %      ");
       lcd.setCursor(0,1);
       lcd.print("Temp: "); 
       lcd.print(t);
       lcd.print(" C      ");
       Serial.println(millis());
       }
       if(curr - durasiSerial > jedaLed)
       {
        lcd.clear();
       timer();
 if(M>9)
 {
 lcd.setCursor(7,1);
 lcd.print(M);
 }
 else
 {
 lcd.setCursor(7,1);
 lcd.print("0"); 
 lcd.setCursor(8,1);
 lcd.print(M);
 lcd.setCursor(9,1);
 lcd.print(":");
 }
  
 if(S>9)
 {
 lcd.setCursor(10,1);
 lcd.print(S);
 }
 else
 {
 lcd.setCursor(10,1);
 lcd.print("0"); 
 lcd.setCursor(11,1);
 lcd.print(S);
 lcd.setCursor(12,1);
 lcd.print(" ");
 }
  
 if(H>9)
 {
 lcd.setCursor(4,1);
 lcd.print (H);
 }
 else
 {
 lcd.setCursor(4,1);
 lcd.print("0"); 
 lcd.setCursor(5,1);
 lcd.print(H);
 lcd.setCursor(6,1);
 lcd.print(":");
 }
  if(D>9)
 {
 lcd.setCursor(2,0);
 lcd.print (D);
 }
 else
 {
 lcd.setCursor(3,0);
 lcd.print("0"); 
 lcd.setCursor(4,0);
 lcd.print(D);
 }
 
  if(curr - durasiSerial > jedaSerial)
        {
          durasiSerial = curr;
        }
       }
      
      
      Serial.println(curr - durasiSerial);

//end display

  // Baca humidity dan temperature


  // Cek hasil pembacaan, dan tampilkan bila ok
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    return;
  }

  if (t<37)// ON
{
  digitalWrite(RELAY_1, RELAY_ON);
  digitalWrite(suhuon, HIGH);
  digitalWrite(suhuoff, LOW);
}
 else if (t>39)//OFF
  {
  digitalWrite(RELAY_1, RELAY_OFF);
  digitalWrite(suhuoff, HIGH); 
  digitalWrite(suhuon, LOW);
  }

  if (h<50)
  {
    digitalWrite(10, HIGH);
  }
  if (h>65)
  {
    digitalWrite(10, LOW);
  }
  
}

unsigned long timer()
    {
 lcd.setCursor(5,0);
 lcd.print("Hari Lagi");
 lcd.setCursor(6,1);
 lcd.print(":");
 lcd.setCursor(9,1);
 lcd.print(":");
    }
    
  unsigned long suhu()
  {
     float h = dht.readHumidity();
  float t = dht.readTemperature();
   if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    return;   }
  lcd.setCursor(0,0);
  lcd.print("Humi: "); 
  lcd.print(h);
  lcd.print(" %      ");
  lcd.setCursor(0,1);
  lcd.print("Temp: "); 
  lcd.print(t);
  lcd.print(" C      ");
  lcd.clear();
  }
  
  unsigned long text()
    {
 lcd.setCursor(1,0);
 lcd.print("PENETAS  TELUR");
 lcd.setCursor(6,1);
 lcd.print("AJAIB");
    }
