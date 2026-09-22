// #include <stdio.h>
#include <Servo.h>
#include <Stepper.h>

int PIN_LED_SERVO = 13;
int PIN_LED_STEPPER = 10;
int PIN_BTN_SERVO = 11;
int PIN_BTN_STEPPER = 12;

int PIN_SERVO = 9;

int PIN_STEPPER_EN_A = 5;
int PIN_STEPPER_IN_1 = 6;
int PIN_STEPPER_IN_2 = 7;

Servo servo;


void setup() {

  Serial.begin(9600);

  // Buttons and lights

  pinMode(PIN_LED_SERVO, OUTPUT);
  pinMode(PIN_LED_STEPPER, OUTPUT);
  pinMode(PIN_BTN_SERVO, INPUT);
  pinMode(PIN_BTN_STEPPER, INPUT);

  // pinMode(PIN_SERVO_PWR, OUTPUT);

  // Stepper Motor

  pinMode(PIN_STEPPER_EN_A, OUTPUT);
  pinMode(PIN_STEPPER_IN_1, OUTPUT);
  pinMode(PIN_STEPPER_IN_2, OUTPUT);

  digitalWrite(PIN_STEPPER_IN_1, LOW);
  digitalWrite(PIN_STEPPER_IN_2, HIGH);
  analogWrite(PIN_STEPPER_EN_A, 0);

  // Servo

  servo.attach(PIN_SERVO);
  servo.write(0);
  
  delay(100);

  // Let everything settle and signal all good
  delay(1000);

  digitalWrite(PIN_LED_STEPPER, HIGH);
  digitalWrite(PIN_LED_SERVO, HIGH);
  delay(100);
  digitalWrite(PIN_LED_STEPPER, LOW);
  digitalWrite(PIN_LED_SERVO, LOW);
  delay(100);
  digitalWrite(PIN_LED_STEPPER, HIGH);
  digitalWrite(PIN_LED_SERVO, HIGH);
  delay(100);
  digitalWrite(PIN_LED_STEPPER, LOW);
  digitalWrite(PIN_LED_SERVO, LOW);
  delay(200);

}


void testServo(int start = 0, int stop = 180, int incr = 1, int stepDelay = 5) {
  
  if(Serial){
    Serial.print("Testing servo ");
    Serial.print(start);
    Serial.print(" -> ");
    Serial.print(stop);
    Serial.print("\n");
  }

  int dir = 1;
  dir = (start < stop) ? 1 : -1;

  // digitalWrite(PIN_LED, HIGH);
  if(dir == 1) {
    for(int p = start; p <= stop; p += incr) {
      servo.write(p);
      delay(stepDelay);
    }
  }

  if(dir == -1) {
    for(int p = start; p >= stop; p -= incr) {
      servo.write(p);
      delay(stepDelay);
    }
  }
  
  //servo.detach();

  // digitalWrite(PIN_LED, LOW);
}

void testMotor(int dir = 1, int speed = 255, int duration = 5000) {

  if(Serial) {
    String dirStr = (dir > 0) ? "forwards" : "backwards";
    Serial.print("Running motor ");
    Serial.print(dirStr);
    Serial.print(" for ");
    Serial.print(duration);
    Serial.print("ms\n");
  }

  // digitalWrite(PIN_LED, HIGH);

  if(dir > 0) {
    digitalWrite(PIN_STEPPER_IN_1, HIGH);
    digitalWrite(PIN_STEPPER_IN_2, LOW);
  }

  else {
    digitalWrite(PIN_STEPPER_IN_1, LOW);
    digitalWrite(PIN_STEPPER_IN_2, HIGH);
  }

  // digitalWrite(PIN_LED, HIGH);
  analogWrite(PIN_STEPPER_EN_A, speed);
  delay(duration);
  analogWrite(PIN_STEPPER_EN_A, 0);
  
  // digitalWrite(PIN_LED, LOW);

}

void testMotorAccel(int start = 0, int target = 255, int duration = 5000, int hold = 2000) {

  // Accelerate forwards
  digitalWrite(PIN_STEPPER_IN_1, HIGH);
  digitalWrite(PIN_STEPPER_IN_2, LOW);

  if(Serial)
    Serial.println("Testing acceleration");

  int delayTime = duration / 100;

  // Speed up

  for(int i = 0; i <= 100; i += 1) {
    int value = map(i, 0, 100, start, target);
    // analogWrite(PIN_LED, value);
    analogWrite(PIN_STEPPER_EN_A, value);

    delay(delayTime);
  }

  delay(hold);

  // Slow down

  for(int i = 100; i >= 0; i -= 1) {
    int value = map(i, 0, 100, start, target);
    // analogWrite(PIN_LED, value);
    analogWrite(PIN_STEPPER_EN_A, value);

    delay(delayTime);
  }

}

void loop() {

  // Servo button

  if(digitalRead(PIN_BTN_SERVO)) {
    digitalWrite(PIN_LED_SERVO, HIGH);
    servo.write(180);
  }

  else {
    digitalWrite(PIN_LED_SERVO, LOW);
    servo.write(0);
  }



  if(digitalRead(PIN_BTN_STEPPER)) {
    digitalWrite(PIN_LED_STEPPER, HIGH);
    // digitalWrite(13, HIGH);

    // digitalWrite(PIN_STEPPER_IN_1, HIGH);
    // digitalWrite(PIN_STEPPER_IN_2, LOW);
    analogWrite(PIN_STEPPER_EN_A, 200);

  }

  else {
    digitalWrite(PIN_LED_STEPPER, LOW);
    // digitalWrite(13, LOW);
    analogWrite(PIN_STEPPER_EN_A, 0);
  }

  delay(100);

  return;

}