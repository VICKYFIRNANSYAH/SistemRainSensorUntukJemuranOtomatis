//SISTEM RAIN SENSOR UNTUK JEMURAN OTOMATIS
//BY MUHAMMAD VICKY FIRNANSYAH 
//https://github.com/VICKYFIRNANSYAH
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin
const int rainSensorPin = A0;
const int servoPin = 3;

const int maksimumKering = 700;   // Disesuaikan dengan sensormu
const int jedaServo = 1000;

Servo servoJemuran;
bool jemuranDiDalam = false;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  servoJemuran.attach(servoPin);
  servoJemuran.write(0); // Posisi awal jemuran keluar

  lcd.setCursor(0, 0);
  lcd.print("Sistem Jemuran");
  lcd.setCursor(0, 1);
  lcd.print("Siap Digunakan");
  delay(2000);
  lcd.clear();
  //https://github.com/VICKYFIRNANSYAH
}

void loop() {
  int nilaiHujan = analogRead(rainSensorPin);

  Serial.print("Sensor Hujan: ");
  Serial.println(nilaiHujan);

  lcd.setCursor(0, 0);

  if (nilaiHujan > maksimumKering) {
    // Cuaca cerah
    lcd.print("Cuaca: Cerah   ");
    Serial.println("Cuaca Cerah");

    if (jemuranDiDalam) {
      // Keluarkan jemuran
      lcd.setCursor(0, 1);
      lcd.print("Keluarkan Jemuran");
      Serial.println("Jemuran keluar");
      servoJemuran.write(0);
      delay(jedaServo);
      jemuranDiDalam = false;
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Jemuran di luar ");
    }

  } else {
    // Hujan
    lcd.print("Cuaca: Hujan   ");
    Serial.println("Cuaca Hujan");

    if (!jemuranDiDalam) {
      // Tarik jemuran ke dalam
      lcd.setCursor(0, 1);
      lcd.print("Tarik Jemuran   ");
      Serial.println("Menarik jemuran");
      servoJemuran.write(90); // Ubah sudut sesuai kebutuhan
      delay(jedaServo);
      jemuranDiDalam = true;
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Jemuran di dalam");
    }
  }

  delay(1000);
}
