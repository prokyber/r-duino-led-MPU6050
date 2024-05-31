# Gyroskopický senzor s diplejem pomocí Ř-duino-LED

# Součástky
- Ř-duino-LED
- [OLED displej 0,96 palce](https://e-shop.prokyber.cz/vystupni/oled-display/)
- [MPU 6050](https://e-shop.prokyber.cz/vstupni/mpu6050-gy-521-3-osy-accelerometer-a-gyroskop/)
- [nepájivé pole](https://e-shop.prokyber.cz/konektory/nepajive-pole-170-pinu/)
- [vodiče](https://e-shop.prokyber.cz/kabely--vodice/dupont-kabel/)

# MPU 6050
Tento modul obsahuje integrovaný obvod s funkcí zastupující dvě zařízení, gyroskop a akcelerometr. Gyroskop je zařízení, které se používá hlavně v navigaci a obsahuje setrvačník, který zachovává polohu osy své rotace. Můžeme tedy díky němu poznat, jaká je poloha celého modulu vůči ploze Země. Akcelerometr je pak zařízení, které měří gravitační zrychlení a můžeme s ním tedy měřit náklon či vibrace modulu.

Námi vybraný modul gyroskopu a akcelerometru pak ještě obsahuje DMP (Digital Motion Processor), který nám velice zjednoduší práci s daty, protože v reálném čase sbírá data ze zmíněných dvou zařízení a poskytuje nám přímo tři důležité hodnoty, které udávají rotace kolem jednotlivých os. V angličtině se nazývají yaw (Z osa), pitch (Y osa) a roll (X osa). Modul má v sobě také integrovaný teploměr, ten je však velmi nepřesný a proto se nevyužívá.

# OLED displej
OLED displej s modrými znaky má v porovnání s alfanumerickými LCD displeji mnoho výhod. Patří mezi ně například vyšší rozlišení (v tomto případě 128x64 bodů) či nižší spotřeba. Právě nižší spotřeby je dosaženo tím, že u OLED displeje svítí pouze ty body, které jsou aktivovány. Pro projekt vybraný OLED displej obsahuje řídící obvod SSD1306, který obstarává komunikaci s Ř-DUINEM po rozhraní I2C či SPI, v tomto případě je použita sběrnice I2C. Co se týká velikosti, tak tento displej má úhlopříčku 0,96 palce a celková velikost modulu je 2,7 x 2,7 cm.

# I2C
I2C graf Inter-Integrated Circuit je sériový komunikační protokol používaný pro komunikaci mezi mikrocontroly nebo jinými elektronickými součástkami v elektronických systémech. I2C je určen pro komunikaci mezi dvěma nebo více zařízeními, která jsou propojena pomocí dvou vedení: Master-out/Slave-out (SCL) a Serial Data Line (SDA).

Přenos dat se zahajuje START bitem (S), když je SDA nízká, zatímco SCL zůstává vysoká. Pak, SDA nastaví přenášený bit zatímco SCL je nízká (modrá) a jsou odebrány vzorky dat (přijaté) při SCL stoupá (zelená). Když je přenos dokončen, je poslaný STOP bit (P) pro uvolnění datové linky, změnou SDA na vysokou, zatímco SCL je trvale vysoký. Aby se zabránilo falešně detekci, je úroveň na SDA změněn na negativní hraně a je zachycen na kladné hrany SCL.

# Zapojení

# Knihovny

# Kód
(Soubor ke stažení výše)

``` cpp
```
