#include <ESP8266WiFi.h>
#include <Servo.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define FIREBASE_HOST "tetas-telur-otomatis-default-rtdb.firebaseio.com"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Master75wew"
Servo servo;
#define DHTPIN 0
DHT dht(DHTPIN, DHT11);

int relay = 16;
float  t;
float kelembapan, suhu;
int h;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
  lcd.backlight();
  lcd.init();

  servo.attach(2); //D4
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  servo.write(0);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Firebase.begin(FIREBASE_HOST);
  delay(1000);


}

void loop() {

  cek_suhu();


  rolling();

}



void rolling() {
  for (int i = 0; i <= 180; i++) {
    servo.write(i);
    delay(100);
    cek_suhu();
  }

  for (int i = 180; i >= 0; i--) {
    servo.write(i);
    delay(100);
    cek_suhu();
  }

}

void cek_suhu() {
  suhu = Firebase.getString("suhu").toFloat();
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (t >= suhu) {
    digitalWrite(relay, LOW);
    Serial.println("Lampu Mati");
  }
  if (t < suhu) {
    digitalWrite(relay, HIGH);
    Serial.println("Lampu Hidup");
  }
  Serial.println(h);
  Serial.println(t);
  Firebase.setFloat("data_suhu", t);
  Firebase.setFloat("data_lembap", h);
  lcd.setCursor(0, 0);
  lcd.print("Suhu : ");
  lcd.setCursor(7, 0);
  lcd.print(t);
  
  lcd.setCursor(0, 1);
  lcd.print("Kelembapan : ");
  lcd.setCursor(13, 1);
  lcd.print(h);

}






