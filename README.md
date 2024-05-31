# Gyroskopický senzor s diplejem pomocí Ř-duino-LED

# Součástky
- Ř-duino-LED
- [OLED displej 0,96 palce](https://e-shop.prokyber.cz/vystupni/oled-display/)
- [MPU 6050](https://e-shop.prokyber.cz/vstupni/mpu6050-gy-521-3-osy-accelerometer-a-gyroskop/)
- [nepájivé pole](https://e-shop.prokyber.cz/konektory/nepajive-pole-170-pinu/)
- [vodiče](https://e-shop.prokyber.cz/kabely--vodice/dupont-kabel/)

# MPU 6050
<img alt="MPU 6050" src="https://github.com/prokyber/r-duino-led-MPU6050/blob/main/img/MPU6050.png" style=" Height: 30vh;">

Tento modul obsahuje integrovaný obvod s funkcí zastupující dvě zařízení, gyroskop a akcelerometr. Gyroskop je zařízení, které se používá hlavně v navigaci a obsahuje setrvačník, který zachovává polohu osy své rotace. Můžeme tedy díky němu poznat, jaká je poloha celého modulu vůči ploze Země. Akcelerometr je pak zařízení, které měří gravitační zrychlení a můžeme s ním tedy měřit náklon či vibrace modulu.

Námi vybraný modul gyroskopu a akcelerometru pak ještě obsahuje DMP (Digital Motion Processor), který nám velice zjednoduší práci s daty, protože v reálném čase sbírá data ze zmíněných dvou zařízení a poskytuje nám přímo tři důležité hodnoty, které udávají rotace kolem jednotlivých os. V angličtině se nazývají yaw (Z osa), pitch (Y osa) a roll (X osa). Modul má v sobě také integrovaný teploměr, ten je však velmi nepřesný a proto se nevyužívá.

# OLED displej
<img alt="OLED displej" src="https://github.com/prokyber/r-duino-led-MPU6050/blob/main/img/OLEDDisplej.webp" style=" Height: 30vh;">

OLED displej s modrými znaky má v porovnání s alfanumerickými LCD displeji mnoho výhod. Patří mezi ně například vyšší rozlišení (v tomto případě 128x64 bodů) či nižší spotřeba. Právě nižší spotřeby je dosaženo tím, že u OLED displeje svítí pouze ty body, které jsou aktivovány. Pro projekt vybraný OLED displej obsahuje řídící obvod SSD1306, který obstarává komunikaci s Ř-DUINEM po rozhraní I2C či SPI, v tomto případě je použita sběrnice I2C. Co se týká velikosti, tak tento displej má úhlopříčku 0,96 palce a celková velikost modulu je 2,7 x 2,7 cm.

# I2C
<img alt="I2C schéma" src="https://github.com/prokyber/r-duino-led-MPU6050/blob/main/img/900px-I2C_data_transfer.png">

I2C graf Inter-Integrated Circuit je sériový komunikační protokol používaný pro komunikaci mezi mikrocontroly nebo jinými elektronickými součástkami v elektronických systémech. I2C je určen pro komunikaci mezi dvěma nebo více zařízeními, která jsou propojena pomocí dvou vedení: Master-out/Slave-out (SCL) a Serial Data Line (SDA).

Přenos dat se zahajuje START bitem (S), když je SDA nízká, zatímco SCL zůstává vysoká. Pak, SDA nastaví přenášený bit zatímco SCL je nízká (modrá) a jsou odebrány vzorky dat (přijaté) při SCL stoupá (zelená). Když je přenos dokončen, je poslaný STOP bit (P) pro uvolnění datové linky, změnou SDA na vysokou, zatímco SCL je trvale vysoký. Aby se zabránilo falešně detekci, je úroveň na SDA změněn na negativní hraně a je zachycen na kladné hrany SCL.

# Zapojení
<img alt="Zapojení" src="https://github.com/prokyber/r-duino-led-MPU6050/blob/main/img/zapojeni.png" style=" Height: 60vh;">


# Knihovny
Před tím než začeme psát kód tak si pro účely tohoto projektu budeme muset stáhnou jednu externí knihovnu díky které si usnadníme komunikaci s displejem. Klikněte na Nástorje -> Spravovat knihovny. Na levé straně by se vám měla otevřít lišta s možností vyhledávání. Zde vyhledejte "U8glib" vybereme verzi 1.19.1 a dáme instalovat.

# Kód
(Soubor ke stažení výše)

``` cpp

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

```
