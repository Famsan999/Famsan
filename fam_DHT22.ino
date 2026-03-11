#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define BUZZER 8

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float set_temp = 40.0;   // เปลี่ยนเป็น 40°C

void setup() {

  Serial.begin(9600);
  dht.begin();

  lcd.begin();
  lcd.backlight();

  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);   // ปิดเสียงตอนเริ่มต้น

  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0,0);
    lcd.print("Sensor Error");
    return;
  }

  // แสดงอุณหภูมิ
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperature,1);
  lcd.write(223);
  lcd.print("C   ");

  // แสดงความชื้น
  lcd.setCursor(0,1);
  lcd.print("Hum:");
  lcd.print(humidity,1);
  lcd.print("%   ");

  // เงื่อนไขเสียง
  if (temperature >= set_temp) {

    tone(BUZZER, 1000);   // ดังเมื่ออุณหภูมิ ≥ 40°C
    lcd.setCursor(13,1);
    lcd.print("!!!");

  } else {

    noTone(BUZZER);       // ต่ำกว่า 40°C เงียบ
    lcd.setCursor(13,1);
    lcd.print("   ");
  }

  delay(1000);
}