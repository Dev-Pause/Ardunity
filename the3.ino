#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TouchScreen.h>
#include <MPU9250.h>
#include <Adafruit_MAX9814.h>

// TFT 디스플레이 설정
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// 터치 스크린 설정
#define TS_CS 8
#define TS_IRQ 7
Adafruit_TouchScreen ts = Adafruit_TouchScreen(TS_CS, TS_IRQ);

// MPU9250 설정
MPU9250 imu;

// MAX9814 설정
#define MIC_PIN A0
Adafruit_MAX9814 mic = Adafruit_MAX9814();

// 핑퐁 공의 초기 위치와 속도
float ballX = 160;
float ballY = 120;
float ballSpeedX = 2;
float ballSpeedY = 2;

void setup() {
  Serial.begin(115200);

  // TFT 디스플레이 초기화
  tft.begin();

  // MPU9250 초기화
  if (!imu.begin()) {
    Serial.println("Failed to initialize MPU9250!");
    while (1);
  }

  mic.begin();


  tft.fillScreen(ILI9341_BLACK);
}

void loop() {

  imu.readSensor();

  int micValue = mic.read();

  ballSpeedX = map(imu.getAccelY_mss(), -9.8, 9.8, -5, 5);
  ballSpeedY = map(imu.getAccelX_mss(), -9.8, 9.8, -5, 5);


  if (micValue > 50) {
    ballSpeedX *= 2;
    ballSpeedY *= 2;
  }


  ballX += ballSpeedX;
  ballY += ballSpeedY;

  if (ballX < 0 || ballX > 320) {
    ballSpeedX *= -1;
  }
  if (ballY < 0 || ballY > 240) {
    ballSpeedY *= -1;
  }

  tft.fillCircle(ballX, ballY, 5, ILI9341_WHITE);
  delay(10);
  tft.fillCircle(ballX, ballY, 5, ILI9341_BLACK);
}
