#include <Arduino.h>
#include <Stepper.h>

const float turnSteps = 2048; // 2相励磁 2048がモータが1回転するステップ数
int rotation = 0;   // 初期値で0を設定

const int rpm = 10; // 回転スピード

#define Stepper1_IN1 32
#define Stepper1_IN2 33
#define Stepper1_IN3 25
#define Stepper1_IN4 26

#define Stepper2_IN1 27
#define Stepper2_IN2 14
#define Stepper2_IN3 12
#define Stepper2_IN4 13

#define LED1 4
#define LED2 18
#define LED3 19

Stepper stepper1(turnSteps, Stepper1_IN3, Stepper1_IN1, Stepper1_IN2, Stepper1_IN4);
Stepper stepper2(turnSteps, Stepper2_IN1, Stepper2_IN3, Stepper2_IN2, Stepper2_IN4);

void setup() {
  // PCとの通信用
  Serial.begin(115200);
  // 親機との通信用
  Serial2.begin(115200);
  
  // 回転スピードを設定
  stepper1.setSpeed(rpm);
  stepper2.setSpeed(rpm);
}

void loop() {
  if (Serial2.available()) {
    String command = Serial2.readStringUntil('\n');
    command.trim();
    Serial.println(command);

    if (command.isEmpty()) {
      digitalWrite(LED1, LOW);
    } else {
      digitalWrite(LED1, HIGH);
    }

    if (command == "motor1") {
      Serial.println("rotate motor1!!");
      stepper1.step(turnSteps / 4);
      // delay(2000);
      digitalWrite(Stepper1_IN1, LOW);
      digitalWrite(Stepper1_IN2, LOW);
      digitalWrite(Stepper1_IN3, LOW);
      digitalWrite(Stepper1_IN4, LOW);
    } else if (command == "motor2") {
      Serial.println("rotate motor2!!");
      stepper2.step(turnSteps / 4);
      // delay(2000);
      digitalWrite(Stepper2_IN1, LOW);
      digitalWrite(Stepper2_IN2, LOW);
      digitalWrite(Stepper2_IN3, LOW);
      digitalWrite(Stepper2_IN4, LOW);
    } else {
      Serial.println("unknown command!!");
    }
  }
}
