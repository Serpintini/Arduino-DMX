#include <Dynamixel2Arduino.h>
#include "Conceptinetics.h"

#define DMX_SLAVE_CHANNELS   2

// Set up motor interface, requires Dynamixel2Arduino.h
const int DXL_DIR_PIN = 2;
Dynamixel2Arduino dxl(Serial1, DXL_DIR_PIN);
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

void setup_sequence(float secs_pause) {

  Serial.begin(57600);
  Serial.println("[INFO] Serial monitor up and running");
  dxl.begin(57600);
  dxl.setPortProtocolVersion(2.0);
  Serial.println("[INFO] Dynamixel motor control up and running");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("[INFO] Arduino builtin LED should be on");
  Serial.println("[INFO] Pausing");
  delay(secs_pause * 1000);
  digitalWrite(LED_BUILTIN, LOW);
  dmx_slave.enable ();
  dmx_slave.setStartAddress (190); 
  Serial.println("[INFO] DMX set up");
  Serial.println("[INFO] All LEDs should be off, let's roll");
  dxl.torqueOn(1);
  dxl.torqueOn(2);
  dxl.torqueOn(3);  

}

void move_at_angle(int direction, int speed) {
  float speeds[3] = {};
  Serial.print("[INFO] Starting movement along path: Direction: ");
  Serial.print(direction);
  Serial.print(" Speed: ");
  Serial.print(speed);
  // Raw max speed is 265, so 2.65 * speed gives appropriate raw unit
  speeds[0] = cos((direction - 45)*3.1416/180) * 2.65 * speed;
  speeds[1] = -cos((direction - 90)*3.1416/180) * 2.65 * speed;
  speeds[2] = -cos((direction + 45)*3.1416/180) * 2.65 * speed;
  dxl.setGoalVelocity(1, speeds[0]);
  dxl.setGoalVelocity(2, speeds[1]);
  dxl.setGoalVelocity(3, speeds[2]);
}

void sit_and_spin(int direction, int speed) {
  double start_pos[3];
  double motor_encoder_total;

  Serial.print("[INFO] Starting spin in place, in direction ");
  Serial.print(direction);
  Serial.print(" at ");
  Serial.print(speed);
  Serial.println("% speed.");
  if (direction > 0) {
    dxl.setGoalVelocity(1, -speed);
    dxl.setGoalVelocity(2, -speed);
    dxl.setGoalVelocity(3, -speed);
  } else if (direction < 0) {
    dxl.setGoalVelocity(1, speed);
    dxl.setGoalVelocity(2, speed);
    dxl.setGoalVelocity(3, speed);
  }
}

void stop_and_pause() {
  Serial.println("[INFO] Starting pause");
  dxl.setGoalVelocity(1, 0);
  dxl.setGoalVelocity(2, 0);
  dxl.setGoalVelocity(3, 0);
}

void setup() {
  // put your setup code here, to run once:
  setup_sequence(5);
}

void loop() {
  // put your main code here, to run repeatedly:

  float macro_number = dmx_slave.getChannelValue (1);
  float speed = dmx_slave.getChannelValue (2);
  Serial.println(" program: " + String(macro_number) +" speed: " + String(speed));
  if (speed != 0){
    if (macro_number == 181){
      sit_and_spin(1, speed);
    }
    else if (macro_number == 182){
      sit_and_spin(-1, speed);
    }
    else{
      move_at_angle(macro_number*2, speed);
    }
  }
  else {
    stop_and_pause();
  }
  
    
}
