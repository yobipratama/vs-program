#include <Arduino.h>
#include <SimpleDHT.h>

// Pin LED RGB
#define LED_R D3
#define LED_G D2
#define LED_B D1

// Kategori suhu
#define Suhu_Dingin 20
#define Suhu_Normal 30
#define Suhu_Panas 40

SimpleDHT11 dht11(D5); //instan sensor dht11

void KelembabanSuhu() {
  int err = SimpleDHTErrSuccess;
  byte temperature = 0;
  byte humidity = 0;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  float suhu_celsius = (float)temperature;
  // float suhu_kelvin = suhu_celsius + 273.15; // Konversi suhu ke Kelvin
  // float suhu_reaumur = suhu_celsius * 0.8; // Konversi suhu ke Reaumur

  Serial.print("Suhu: ");
  Serial.print(suhu_celsius);
  Serial.print(" *C, Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");

  // Indikator LED RGB
  if (suhu_celsius < Suhu_Dingin) {
    analogWrite(LED_R, 0); // LED Merah mati
    analogWrite(LED_G, 255); // LED Hijau nyala
    analogWrite(LED_B, 0); // LED Biru mati
  } else if (suhu_celsius >= Suhu_Dingin && suhu_celsius < Suhu_Normal) {
    analogWrite(LED_R, 0); // LED Merah mati
    analogWrite(LED_G, 0); // LED Hijau mati
    analogWrite(LED_B, 255); // LED Biru nyala
  } else {
    analogWrite(LED_R, 255); // LED Merah nyala
    analogWrite(LED_G, 0); // LED Hijau mati
    analogWrite(LED_B, 0); // LED Biru mati
  } 

  delay(1500);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Alat Pembaca Suhu dan Kelembaban");
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  delay(1000);
}

void loop() {
  KelembabanSuhu();
}
