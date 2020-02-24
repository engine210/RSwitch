#include <Servo.h>
#define DEG1_ON_PRESS 95
#define DEG1_ON_REAST 100
#define DEG1_OFF_PRESS 135
#define DEG1_OFF_REAST 130
#define DEG2_ON_PRESS 60
#define DEG2_ON_REAST 65
#define DEG2_OFF_PRESS 100
#define DEG2_OFF_REAST 95
#define PIN_SERVO1 8
#define PIN_SERVO2 9
#define PIN_SW1 3
#define PIN_SW2 2

Servo servo1, servo2;

bool last_status1 = false;
bool last_status2 = false;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  pinMode(PIN_SW1, INPUT);
  pinMode(PIN_SW2, INPUT);
}

void loop() {
  bool sw1 = digitalRead(PIN_SW1);
  bool sw2 = digitalRead(PIN_SW2);

  if (sw1 != last_status1) {
    if (sw1 == true) {
      servo1.write(DEG1_ON_PRESS);
      delay(500);
      servo1.write(DEG1_ON_REAST);
      last_status1 = true;
    } else {
      servo1.write(DEG1_OFF_PRESS);
      delay(500);
      servo1.write(DEG1_OFF_REAST);
      last_status1 = false;
    }
  }

  if (sw2 != last_status2) {
    if (sw2 == true) {
      servo2.write(DEG2_ON_PRESS);
      delay(500);
      servo2.write(DEG2_ON_REAST);
      last_status2 = true;
    } else {
      servo2.write(DEG2_OFF_PRESS);
      delay(500);
      servo2.write(DEG2_OFF_REAST);
      last_status2 = false;
    }
  }
}
