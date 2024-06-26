#include <Servo.h>

#define trigPinL 2 // 左侧超声波 trig 引脚
#define echoPinL 3 // 左侧超声波 echo 引脚
#define trigPinM 4 // 中间超声波 trig 引脚
#define echoPinM 5 // 中间超声波 echo 引脚
#define trigPinR 6 // 右侧超声波 trig 引脚
#define echoPinR 7 // 右侧超声波 echo 引脚
#define leftTurnPin 10 // 左转向灯引脚
#define rightTurnPin 11 // 右转向灯引脚
#define motorPin1 12   // 电机连接引脚1
#define motorPin2 13   // 电机连接引脚2

Servo servo1; // 第一个舵机
Servo servo2; // 第二个舵机
  

void setup() {
 servo1.attach(9); // 将第一个舵机连接到9号引脚
 servo2.attach(8); // 将第二个舵机连接到8号引脚
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
}

  

void loop() {
 unsigned int distanceL = getDistance(trigPinL, echoPinL);
 unsigned int distanceM = getDistance(trigPinM, echoPinM);
 unsigned int distanceR = getDistance(trigPinR, echoPinR);
 // 根据距离控制速度
 int leftSpeed = 255; // 默认最大速度
 int rightSpeed = 255; // 默认最大速度
 if (distanceL < 20) {
  servo1.write(50); // 左侧距离小于20cm时，舵机1顺时针转动40度
  turnOnLeftTurnSignal(); // 打开左转向灯
 } else if (distanceR < 20) {
  servo2.write(140); // 右侧距离小于20cm时，舵机2逆时针转动40度
  turnOnRightTurnSignal(); // 打开右转向灯
 } else if (distanceM < 20) {
  servo1.write(90); // 中侧距离小于20cm时，舵机1恢复到初始位置
  servo2.write(90); // 中侧距离小于20cm时，舵机2恢复到初始位置
  turnOffTurnSignal(); // 关闭转向灯
 } else {
  servo1.write(20); // 左右距离大于20cm时，舵机1顺时针转动70度
  servo2.write(160); // 左右距离大于20cm时，舵机2逆时针转动70度
  turnOffTurnSignal(); // 关闭转向灯
 }
 analogWrite(motorPin1, leftSpeed);
 analogWrite(motorPin2, rightSpeed);
}

  

// 获取超声波测得的距离

unsigned int getDistance(int trigPin, int echoPin) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 unsigned long duration = pulseIn(echoPin, HIGH);
 unsigned int distance = duration * 0.034 / 2;
 return distance;
}
// 打开左转向灯
void turnOnLeftTurnSignal() {
 digitalWrite(leftTurnPin, HIGH);
 digitalWrite(rightTurnPin, LOW);
}
// 打开右转向灯
void turnOnRightTurnSignal() {
 digitalWrite(leftTurnPin, LOW);
 digitalWrite(rightTurnPin, HIGH);
}
// 关闭转向灯
void turnOffTurnSignal() {
 digitalWrite(leftTurnPin, LOW);
 digitalWrite(rightTurnPin, LOW);
}