#include <LiquidCrystal.h>
#define DELAY 30000
#include "DHT.h"
#define DHTPIN A1 // what digital pin we're connected to
#define LM35 A0 // what digital pin we're connected to
#define NORTH A2 // what digital pin we're connected to
#define SOUTH A3 // what digital pin we're connected to
#define EAST A4 // what digital pin we're connected to
#define WEST A5 // what digital pin we're connected to
#define LED 13
#define DHTTYPE DHT11 // DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
float temp,temp_max = 40;
float humidity;
int north,south,east,west;
unsigned long previousMillis;
float find_temp()
{
int i;
long avg_val = 0;
for(i=0;i<1000;i++)
{
avg_val += analogRead(LM35);
}
avg_val/=1000;
temp = avg_val*(500.0/1023.0);
lcd.setCursor(0, 0);
lcd.print("T:");
lcd.print(temp,1);
lcd.print("*C ");
//return temp;
}
int read_humidity()
{
humidity = dht.readHumidity();
lcd.setCursor(9, 0);
lcd.print("H:");
lcd.print(humidity,1);
lcd.print("% ");
}
void read_direction()
{
int i;
long avg_val = 0;
for(i=0;i<1000;i++)
{
avg_val += analogRead(NORTH);
}
avg_val/=1000;
//north = (avg_val*5.0)/1023.0;
north = avg_val;
north = map(north,0,200,0,5);
lcd.setCursor(0, 1);
lcd.print("N:");
lcd.print(north);
lcd.print(" ");
avg_val = 0;
for(i=0;i<1000;i++)
{
avg_val += analogRead(SOUTH);
}
avg_val/=1000;
//north = (avg_val*5.0)/1023.0;
south = avg_val;
south = map(south,0,200,0,5);
lcd.print("S:");
lcd.print(south);
lcd.print(" ");
avg_val = 0;
for(i=0;i<1000;i++)
{
avg_val += analogRead(EAST);
}
avg_val/=1000;
//north = (avg_val*5.0)/1023.0;
east = avg_val;
east = map(east,0,200,0,5);
lcd.print("E:");
lcd.print(east);
lcd.print(" ");
avg_val = 0;
for(i=0;i<1000;i++)
{
avg_val += analogRead(WEST);
}
avg_val/=1000;
//north = (avg_val*5.0)/1023.0;
west = avg_val;
west = map(west,0,200,0,5);
lcd.print("W:");
lcd.print(west);
lcd.print(" ");
}
void upload_values()
{
if(millis() - previousMillis >= DELAY) // Sends values to WiFi Every 10 sec for uploading on Thingspeak
{
lcd.clear();
lcd.print("UPLOADING...");
previousMillis = millis();
Serial.print("<T");Serial.print(temp);Serial.println(">");
delay(100);
Serial.print("<H");Serial.print(humidity);Serial.println(">");
delay(100);
Serial.print("<N");Serial.print(north);Serial.println(">");
delay(100);
Serial.print("<S");Serial.print(south);Serial.println(">");
delay(100);
Serial.print("<E");Serial.print(east);Serial.println(">");
delay(100);
Serial.print("<W");Serial.print(west);Serial.println(">");
delay(100);
Serial.println("<U>");
delay(100);
}
}
void setup()
{
Serial.begin(9600);
Serial.print("START");
lcd.begin(16, 2);
pinMode(LED, OUTPUT);
digitalWrite(LED, HIGH);
// Print a message to the LCD.
lcd.print(" IoT Weather ");
lcd.setCursor(0, 1);

lcd.print(" Monitor System");
delay(1500); // waits for the servo to get there
digitalWrite(LED, LOW);
lcd.clear();
previousMillis = millis();
}
void loop()
{
find_temp();
read_humidity();
read_direction();
upload_values();
delay(1000);
}
