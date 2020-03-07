#include <Servo.h>
#define DEG1_ON_PRESS 95
#define DEG1_ON_REAST 105
#define DEG1_OFF_PRESS 130
#define DEG1_OFF_REAST 120
#define DEG2_ON_PRESS 60
#define DEG2_ON_REAST 65
#define DEG2_OFF_PRESS 100
#define DEG2_OFF_REAST 95
#define PIN_SERVO1 9
#define PIN_SERVO2 12
#define PIN_ESP1 8
#define PIN_ESP2 7
#define PIN_BTN1 3
#define PIN_BTN2 4
#define PIN1_SERVO_POW 10
#define PIN2_SERVO_POW 13

Servo servo1, servo2;

bool last_esp1_status = false;
bool last_esp2_status = false;
bool last_btn1_status = false;
bool last_btn2_status = false;
bool servo1_status = false;
bool servo2_status = false;

void sevrvo1_on() {
  digitalWrite(PIN1_SERVO_POW, HIGH);
  servo1.write(DEG1_ON_PRESS);
  delay(500);
  servo1.write(DEG1_ON_REAST);
  digitalWrite(PIN1_SERVO_POW, LOW);
}

void sevrvo1_off() {
  digitalWrite(PIN1_SERVO_POW, HIGH);
  servo1.write(DEG1_OFF_PRESS);
  delay(500);
  servo1.write(DEG1_OFF_REAST);
  digitalWrite(PIN1_SERVO_POW, LOW);
}

void sevrvo2_on() {
  digitalWrite(PIN2_SERVO_POW, HIGH);
  servo2.write(DEG2_ON_PRESS);
  delay(500);
  servo2.write(DEG2_ON_REAST);
  digitalWrite(PIN2_SERVO_POW, LOW);
}

void sevrvo2_off() {
  digitalWrite(PIN2_SERVO_POW, HIGH);
  servo2.write(DEG2_OFF_PRESS);
  delay(500);
  servo2.write(DEG2_OFF_REAST);
  digitalWrite(PIN2_SERVO_POW, LOW);
}

bool is_btn1_pressed() {
  bool val = digitalRead(PIN_BTN1);
  if (val) {
    delay(20);
    val = digitalRead(PIN_BTN1);
    if (val && last_btn1_status == false) {
      last_btn1_status = true;
      return true;
    }
    last_btn1_status = false;
  } else {
    last_btn1_status = false;
  }
  return false;
}

bool is_btn2_pressed() {
  bool val = digitalRead(PIN_BTN2);
  if (val) {
    delay(20);
    val = digitalRead(PIN_BTN2);
    if (val && last_btn2_status == false) {
      last_btn2_status = true;
      return true;
    }
    last_btn2_status = false;
  } else {
    last_btn2_status = false;
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  pinMode(PIN_ESP1, INPUT);
  pinMode(PIN_ESP2, INPUT);
  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
  pinMode(PIN1_SERVO_POW, OUTPUT);
  pinMode(PIN2_SERVO_POW, OUTPUT);
  digitalWrite(PIN1_SERVO_POW, LOW);
  digitalWrite(PIN2_SERVO_POW, LOW);
}

void loop() {
  bool esp1_status = digitalRead(PIN_ESP1);
  bool esp2_status = digitalRead(PIN_ESP2);
  bool btn1_pressed = is_btn1_pressed();
  bool btn2_pressed = is_btn2_pressed();

  // check weather to change the servo status because the button is pressed.
  if (btn1_pressed) {
    if (servo1_status) {
      sevrvo1_off();
      servo1_status = false;
    } else {
      sevrvo1_on();
      servo1_status = true;
    }
  }
  if (btn2_pressed) {
    if (servo2_status) {
      sevrvo2_off();
      servo2_status = false;
    } else {
      sevrvo2_on();
      servo2_status = true;
    }
  }
  
  // check weather to change the servo status because the ESP signal is change.
  if (esp1_status != last_esp1_status) {
    if (esp1_status == true) {
      sevrvo1_on();
      last_esp1_status = true;
      servo1_status = true;
    } else {
      sevrvo1_off();
      last_esp1_status = false;
      servo1_status = false;
    }
  }
  if (esp2_status != last_esp2_status) {
    if (esp2_status == true) {
      sevrvo2_on();
      last_esp2_status = true;
      servo2_status = true;
    } else {
      sevrvo2_off();
      last_esp2_status = false;
      servo2_status = false;
    }
  }
}
