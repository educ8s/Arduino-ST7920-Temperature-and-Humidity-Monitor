#include <DHT.h>
#include <U8g2lib.h>
#include <U8x8lib.h>

#define DHTTYPE    DHT22

char temperature [5];
char humidity [5];
const char DEGREE_SYMBOL[] = { 0xB0, '\0' };

DHT dht(7, DHTTYPE);

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

void setup() {  

  dht.begin();
  Serial.begin(9600); 
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_helvB10_tf); 
  u8g2.setColorIndex(1);  
}

void loop() {  
  u8g2.firstPage();
  do {   
    draw();
  } while( u8g2.nextPage() );
}
  
void draw(){

  readTemperature();
  readHumidity();
  
  u8g2.drawFrame(0,0,128,31);         
  u8g2.drawFrame(0,33,128,31);           
  
  u8g2.drawStr( 15, 13, "Temperature");   
  u8g2.drawStr( 35, 28, temperature);   
  u8g2.drawUTF8(70, 28, DEGREE_SYMBOL);
  u8g2.drawUTF8(76, 28, "C");

  u8g2.drawStr(30,46, "Humidity");         
  u8g2.drawStr( 37, 61, humidity); 
  u8g2.drawStr(75,61, "%");  
}

void readTemperature()
{
  float t = dht.readTemperature();
  dtostrf(t, 3, 1, temperature);
}

void readHumidity()
{
  float h = dht.readHumidity();
  dtostrf(h, 3, 1, humidity);
}
