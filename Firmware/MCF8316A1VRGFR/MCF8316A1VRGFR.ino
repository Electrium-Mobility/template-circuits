#include <Wire.h>

#define SCL 1
#define SDA 2
#define BRAKE 3
#define DIR 4
#define DRVOFF 5
#define SPEED 6
#define FG 7
#define NFAULT 8
#define SOX 9

const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(SPEED, ledChannel);

  pinMode(BRAKE, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(DRVOFF, OUTPUT);
  pinMode(FG, INPUT);
  pinMode(NFAULT, INPUT);
  pinMode(SOX, INPUT);

  digitalWrite(BRAKE, 0);
  digitalWrite(DIR, 1);
  digitalWrite(DRVOFF, 0)  

  // configure pwm speed control
  Wire.beginTransmission(0x01);
  Wire.write(0b00010000);
  Wire.write(0x00);
  Wire.write(0xA4);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(100);
}

void loop() {
  uint_8_t spd = Serial.read(); 
  ledcWrite(pwmChannel, spd);
  Serial.println(spd);
  
  if (digitalRead(NFAULT) == 0) {
    Serial.println("Fault");
  }
  delay(100);
}
