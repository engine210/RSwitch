#include <Servo.h>
#define DEG1_ON_PRESS 140
#define DEG1_ON_REAST 130
#define DEG1_OFF_PRESS 95
#define DEG1_OFF_REAST 105
#define DEG2_ON_PRESS 100
#define DEG2_ON_REAST 95
#define DEG2_OFF_PRESS 60
#define DEG2_OFF_REAST 65
#define PIN_SERVO1 9
#define PIN_SERVO2 12
#define PIN_ESP1 8
#define PIN_ESP2 7
#define PIN_BTN1 3
#define PIN_BTN2 4

Servo servo1, servo2;

bool last_esp1_status = false;
bool last_esp2_status = false;
bool last_btn1_status = false;
bool last_btn2_status = false;
bool servo1_status = false;
bool servo2_status = false;

void sevrvo1_on() {
  servo1.attach(PIN_SERVO1);
  servo1.write(DEG1_ON_PRESS);
  delay(500);
  servo1.write(DEG1_ON_REAST);
  servo1.detach();
}

void sevrvo1_off() {
  servo1.attach(PIN_SERVO1);
  servo1.write(DEG1_OFF_PRESS);
  delay(500);
  servo1.write(DEG1_OFF_REAST);
  servo1.detach();
}

void sevrvo2_on() {
  servo2.attach(PIN_SERVO2);
  servo2.write(DEG2_ON_PRESS);
  delay(500);
  servo2.write(DEG2_ON_REAST);
  servo2.detach();
}

void sevrvo2_off() {
  servo2.attach(PIN_SERVO2);
  servo2.write(DEG2_OFF_PRESS);
  delay(500);
  servo2.write(DEG2_OFF_REAST);
  servo2.detach();
}

int is_btn_pressed() {
  bool val1 = digitalRead(PIN_BTN1);
  bool val2 = digitalRead(PIN_BTN2);
  bool r1, r2;
  if (val1 || val2) {
    delay(20);
    val1 = digitalRead(PIN_BTN1);
    val2 = digitalRead(PIN_BTN2);
    if (val1 && last_btn1_status == false) {
      last_btn1_status = true;
      r1 = true;
    } else {
      last_btn1_status = false;
      r1 = false;
    }
    if (val2 && last_btn2_status == false) {
      last_btn2_status = true;
      r2 = true;
    } else {
      last_btn2_status = false;
      r2 = false;
    }
  } else {
    last_btn1_status = false;
    last_btn2_status = false;
    r1 = false;
    r2 = false;
  }

  if (!r1 && !r2) {
    return 0;
  } else if (r1 && !r2) {
    return 1;
  } else if (!r1 && r2) {
    return 2;
  } else {
    return 3;
  }
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
  pinMode(PIN_ESP1, INPUT);
  pinMode(PIN_ESP2, INPUT);
  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
}

void loop() {
  bool esp1_status = digitalRead(PIN_ESP1);
  bool esp2_status = digitalRead(PIN_ESP2);
//  bool btn1_pressed = is_btn1_pressed();
//  bool btn2_pressed = is_btn2_pressed();
  int btn_pressed = is_btn_pressed();
  // check weather to change the servo status because the button is pressed.
  if (btn_pressed == 1) {
    if (servo1_status) {
      sevrvo1_off();
      servo1_status = false;
    } else {
      sevrvo1_on();
      servo1_status = true;
    }
  } else if (btn_pressed == 2) {
    if (servo2_status) {
      sevrvo2_off();
      servo2_status = false;
    } else {
      sevrvo2_on();
      servo2_status = true;
    }
  } else if (btn_pressed == 3) {
    if (servo1_status) {
      sevrvo1_off();
      servo1_status = false;
    } else {
      sevrvo1_on();
      servo1_status = true;
    }
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
