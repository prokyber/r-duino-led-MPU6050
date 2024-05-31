

// OLED displej přes I2C
// řadič SSD1306

// připojení knihovny U8glib
#include "U8glib.h"

// inicializace OLED displeje z knihovny U8glib
U8GLIB_SSD1306_128X64 mujOled(U8G_I2C_OPT_NONE);
// Arduino gyroskop a akcelerometr 1

// připojení knihovny Wire
#include <Wire.h>
// inicializace proměnné pro určení adresy senzoru
// 0x68 nebo 0x69, dle připojení AD0
const int MPU_addr=0x68;
// inicializace proměnných, do kterých se uloží data
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

// proměnná pro uchování času poslední obnovy displeje
long int prepis = 0;

void setup(void) {
  // pro otočení displeje o 180 stupňů
  // stačí odkomentovat řádek níže
  // mujOled.setRot180();
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
 // zapnutí přenosu
  
}

void loop(void) {
  // porovnání uloženého a aktuálního času
  // při rozdílu větším než 100 ms se provede
  // obnovení displeje, čas můžeme nastavit dle potřeby
  Wire.beginTransmission(MPU_addr);
  // zápis do registru ACCEL_XOUT_H
  Wire.write(0x3B);
  Wire.endTransmission(false);
  // vyzvednutí dat z 14 registrů
  Wire.requestFrom(MPU_addr,14,true);
  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
 
  if (millis()-prepis > 100) {
    // následující skupina příkazů
    // obnoví obsah OLED displeje
    mujOled.firstPage();
    do {
      // funkce vykresli vykreslí žádaný obsah
      vykresli();
    } while( mujOled.nextPage() );
    // uložení posledního času obnovení
    prepis = millis();
  }
  
  // zde je místo pro další příkazy pro Arduino
  
  // volitelná pauza 10 ms pro demonstraci
  // vykonání dalších příkazů
  delay(10);
}
// funkce vykresli pro nastavení výpisu informací na OLED
void vykresli(void) {
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  mujOled.setFont(u8g_font_unifont);
  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  mujOled.setPrintPos(0, 10);
  // výpis textu na zadanou souřadnici
  mujOled.print("prokyber navody");
  mujOled.setPrintPos(0, 25);
  mujOled.print("osa x  ");
  mujOled.print(GyX);
  mujOled.setPrintPos(0, 40);
  mujOled.print("osa y  ");
  mujOled.print(GyY);
  mujOled.setPrintPos(0, 55);
  mujOled.print("osa z  ");
  mujOled.print(GyZ);
}
