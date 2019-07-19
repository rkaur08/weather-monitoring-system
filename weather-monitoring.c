{\rtf1\ansi\ansicpg1252\cocoartf1671
{\fonttbl\f0\froman\fcharset0 TimesNewRomanPS-BoldMT;\f1\froman\fcharset0 TimesNewRomanPSMT;\f2\fswiss\fcharset0 Helvetica;
}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\b\fs23 \cf0 #include <LiquidCrystal.h> 
\f1\b0 \

\f0\b #define DELAY 30000 
\f1\b0 \

\f0\b #include "DHT.h" 
\f1\b0 \

\f0\b #define DHTPIN A1 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define LM35 A0 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define NORTH A2 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define SOUTH A3 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define EAST A4 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define WEST A5 // what digital pin we're connected to 
\f1\b0 \

\f0\b #define LED 13 
\f1\b0 \

\f0\b #define DHTTYPE DHT11 // DHT 22 (AM2302), AM2321 
\f1\b0 \

\f0\b DHT dht(DHTPIN, DHTTYPE); 
\f1\b0 \

\f0\b LiquidCrystal lcd(4, 5, 6, 7, 8, 9); 
\f1\b0 \

\f0\b float temp,temp_max = 40; 
\f1\b0 \

\f0\b float humidity; 
\f1\b0 \

\f0\b int north,south,east,west; 
\f1\b0 \

\f0\b unsigned long previousMillis; 
\f1\b0 \

\f0\b float find_temp() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \
int i; \
long avg_val = 0; \
for(i=0;i<1000;i++) \
\{ \
avg_val += analogRead(LM35); \
\} \
avg_val/=1000; \
temp = avg_val*(500.0/1023.0); \
\pard\pardeftab720\partightenfactor0

\fs24 \cf0 lcd.setCursor(0, 0); \
lcd.print("T:"); \
lcd.print(temp,1); \
lcd.print("*C "); \
//return temp; \
\pard\pardeftab720\partightenfactor0

\f0\b\fs23 \cf0 \} 
\f1\b0 \

\f0\b int read_humidity() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \
humidity = dht.readHumidity(); \
lcd.setCursor(9, 0); \
lcd.print("H:"); \
lcd.print(humidity,1); \
lcd.print("% "); \

\f0\b \} 
\f2\b0\fs22 63 \
\pard\pardeftab720\partightenfactor0

\f1\fs24 \cf0 \
\pard\pardeftab720\partightenfactor0

\f0\b\fs23 \cf0 void read_direction() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \
int i; \
long avg_val = 0; \
for(i=0;i<1000;i++) \
\{ \

\f0\b avg_val += analogRead(NORTH); 
\f1\b0 \
\} \
avg_val/=1000; \
//north = (avg_val*5.0)/1023.0; \
north = avg_val; \
north = map(north,0,200,0,5); \
lcd.setCursor(0, 1); \
lcd.print("N:"); \
lcd.print(north); \
lcd.print(" "); \
avg_val = 0; \
for(i=0;i<1000;i++) \
\{ \
avg_val += analogRead(SOUTH); \
\} \
avg_val/=1000; \
//north = (avg_val*5.0)/1023.0; \
south = avg_val; \
south = map(south,0,200,0,5); \
lcd.print("S:"); \
lcd.print(south); \
lcd.print(" "); \
avg_val = 0; \
for(i=0;i<1000;i++) \
\{ \

\f0\b avg_val += analogRead(EAST); 
\f1\b0 \
\} \
avg_val/=1000; \
//north = (avg_val*5.0)/1023.0; \
east = avg_val; \
east = map(east,0,200,0,5); \
lcd.print("E:"); \
lcd.print(east); \
lcd.print(" "); \
avg_val = 0; \
for(i=0;i<1000;i++) \
\{ 
\f2\fs22 64 \
\pard\pardeftab720\partightenfactor0

\f1\fs24 \cf0 \
avg_val += analogRead(WEST); \
\} \
avg_val/=1000; \
//north = (avg_val*5.0)/1023.0; \
west = avg_val; \
west = map(west,0,200,0,5); \
lcd.print("W:"); \
lcd.print(west); \
lcd.print(" "); \
\pard\pardeftab720\partightenfactor0

\f0\b\fs23 \cf0 \} 
\f1\b0 \

\f0\b void upload_values() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \

\f0\b if(millis() - previousMillis >= DELAY) // Sends values to WiFi Every 10 sec for uploading on Thingspeak 
\f1\b0 \
\{ \
lcd.clear(); \
lcd.print("UPLOADING..."); \
previousMillis = millis(); \
Serial.print("<T");Serial.print(temp);Serial.println(">"); \
delay(100); \
Serial.print("<H");Serial.print(humidity);Serial.println(">"); \
delay(100); \
Serial.print("<N");Serial.print(north);Serial.println(">"); \
delay(100); \
Serial.print("<S");Serial.print(south);Serial.println(">"); \
delay(100); \
Serial.print("<E");Serial.print(east);Serial.println(">"); \
delay(100); \
Serial.print("<W");Serial.print(west);Serial.println(">"); \
delay(100); \
Serial.println("<U>"); \
delay(100); \
\} \

\f0\b \} 
\f1\b0 \

\f0\b void setup() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \
Serial.begin(9600); \
Serial.print("START"); \
lcd.begin(16, 2); \
pinMode(LED, OUTPUT); \

\f0\b digitalWrite(LED, HIGH); 
\f1\b0 \
// Print a message to the LCD. \
lcd.print(" IoT Weather "); \
lcd.setCursor(0, 1); 
\f2\fs22 65 \
\pard\pardeftab720\partightenfactor0

\f1\fs24 \cf0 \
lcd.print(" Monitor System"); \
delay(1500); // waits for the servo to get there \
digitalWrite(LED, LOW); \
lcd.clear(); \
\pard\pardeftab720\partightenfactor0

\f0\b\fs23 \cf0 previousMillis = millis(); 
\f1\b0 \

\f0\b \} 
\f1\b0 \

\f0\b void loop() 
\f1\b0 \

\f0\b \{ 
\f1\b0 \
find_temp(); \
read_humidity(); \
read_direction(); \
upload_values(); \
delay(1000); \

\f0\b \} }