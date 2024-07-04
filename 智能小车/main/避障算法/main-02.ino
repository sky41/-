#include <Servo.h>

#define trigPinL 2  // 左侧超声波 trig 引脚
#define echoPinL 3  // 左侧超声波 echo 引脚
#define trigPinM 4  // 中间超声波 trig 引脚
#define echoPinM 5  // 中间超声波 echo 引脚
#define trigPinR 6  // 右侧超声波 trig 引脚
#define echoPinR 7  // 右侧超声波 echo 引脚

Servo servo1;// 第一个舵机
Servo servo2;// 第二个舵机

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  servo1.attach(9);  // 将第一个舵机连接到9号引脚
  servo2.attach(8);  // 将第二个舵机连接到8号引脚
}

void loop() {
  unsigned int distanceL = getDistance(trigPinL, echoPinL);
  unsigned int distanceM = getDistance(trigPinM, echoPinM);
  unsigned int distanceR = getDistance(trigPinR, echoPinR);

  if (distanceL < 20) {
    servo1.write(0);  // 舵机1向左转
    servo2.write(180);  // 舵机2向右转
  } else if (distanceR < 20) {
    servo1.write(180);  // 舵机1向右转
    servo2.write(0);  // 舵机2向左转
  } else {
    servo1.write(90);  // 舵机1恢复初始位置
    servo2.write(90);  // 舵机2恢复初始位置
  }
}