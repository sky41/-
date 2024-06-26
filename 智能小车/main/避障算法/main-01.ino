// 基本功能：
// 1.根据三个超声波传感器的数据,去控制两个转向舵机
// 2.使用OLED模块获取超声波数据
// 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define trigPinL 2  // 左侧超声波 trig 引脚
#define echoPinL 3  // 左侧超声波 echo 引脚
#define trigPinM 4  // 中间超声波 trig 引脚
#define echoPinM 5  // 中间超声波 echo 引脚
#define trigPinR 6  // 右侧超声波 trig 引脚
#define echoPinR 7  // 右侧超声波 echo 引脚
#define leftTurnPin 10     // 左转向灯引脚
#define rightTurnPin 11    // 右转向灯引脚
#define motorPin1 12       // 电机连接引脚1
#define motorPin2 13       // 电机连接引脚2

Servo servo1;  // 第一个舵机
Servo servo2;  // 第二个舵机

void setup() {
  servo1.attach(9);  // 将第一个舵机连接到9号引脚
  servo2.attach(8);  // 将第二个舵机连接到8号引脚
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinM, OUTPUT);
  pinMode(echoPinM, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(leftTurnPin, OUTPUT);
  pinMode(rightTurnPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  unsigned int distanceL = getDistance(trigPinL, echoPinL);
  unsigned int distanceM = getDistance(trigPinM, echoPinM);
  unsigned int distanceR = getDistance(trigPinR, echoPinR);

  // 根据距离控制速度
  int leftSpeed = 255;  // 默认最大速度
  int rightSpeed = 255;  // 默认最大速度
// 舵机控制逻辑
if (distanceL < 20) {
    // 左侧距离小于20cm时的逻辑
    servo1.write(40);  // 左侧距离小于20cm时，舵机1顺时针转动40度
    servo2.write(40);  // 左侧距离小于20cm时，舵机2顺时针转动40度
  } else if (distanceR < 20) {
    // 右侧距离小于20cm时的逻辑
    servo1.write(140);  // 右侧距离小于20cm时，舵机1逆时针转动40度
    servo2.write(140);  // 右侧距离小于20cm时，舵机2逆时针转动40度
  } else if (distanceM < 20) {
    // 中间距离小于20cm时的逻辑
    // ...
  } else {
    // 距离大于20cm时的逻辑
    servo1.write(90);  // 当距离大于20cm时，舵机1恢复到初始位置
    servo2.write(90);  // 当距离大于20cm时，舵机2恢复到初始位置
  }
  

  // 显示距离数据
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Distance L: " + String(distanceL) + " cm");
  display.println("Distance M: " + String(distanceM) + " cm");
  display.println("Distance R: " + String(distanceR) + " cm");
  display.display();
}

unsigned int getDistance(int trigPin, int echoPin) {
  // 返回从超声波传感器测得的距禈
}

void turnOnLeftTurnSignal() {
  digitalWrite(leftTurnPin, HIGH);
  digitalWrite(rightTurnPin, LOW);
}

void turnOnRightTurnSignal() {
  digitalWrite(leftTurnPin, LOW);
  digitalWrite(rightTurnPin, HIGH);
}

void turnOffTurnSignal() {
  digitalWrite(leftTurnPin, LOW);
  digitalWrite(rightTurnPin, LOW);
}