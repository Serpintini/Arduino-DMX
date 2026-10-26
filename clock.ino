#include <Dynamixel2Arduino.h>
#include "Conceptinetics.h"

#define DMX_SLAVE_CHANNELS   6

// Set up motor interface, requires Dynamixel2Arduino.h
const int DXL_DIR_PIN = 2;
Dynamixel2Arduino dxl(Serial1, DXL_DIR_PIN);
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

void setup_sequence(float secs_pause) {

  // Serial.begin(57600);
  // Serial.println("[INFO] Serial monitor up and running");
  // dxl.begin(57600);
  // dxl.setPortProtocolVersion(2.0);
  // Serial.println("[INFO] Dynamixel motor control up and running");
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, HIGH);
  // Serial.println("[INFO] Arduino builtin LED should be on");
  // Serial.println("[INFO] Pausing");
  // delay(secs_pause * 1000);
  // digitalWrite(LED_BUILTIN, LOW);
  // dmx_slave.enable ();
  // dmx_slave.setStartAddress (190); 
  // Serial.println("[INFO] DMX set up");
  // Serial.println("[INFO] All LEDs should be off, let's roll");
  // dxl.setOperatingMode(1, OP_VELOCITY);
  // dxl.setOperatingMode(2, OP_VELOCITY);
  // dxl.torqueOn(1);
  // dxl.torqueOn(2);
  // Serial.println(dxl.ping(1));
  // Serial.println(dxl.ping(2));

  Serial.begin(57600);

  dxl.begin(57600);
  dxl.setPortProtocolVersion(2.0);

  Serial.println("Ping 0 :");
  Serial.println(dxl.ping(0));

  Serial.println("Ping 1 :");
  Serial.println(dxl.ping(1));

  dxl.torqueOff(1);
  dxl.torqueOff(0);

  Serial.println("Set velocity mode 0:");
  Serial.println(dxl.setOperatingMode(0, OP_EXTENDED_POSITION));
  Serial.println("Set velocity mode 1:");
  Serial.println(dxl.setOperatingMode(1, OP_EXTENDED_POSITION));

  Serial.println("Torque on 0:");
  Serial.println(dxl.torqueOn(0));
  Serial.println("Torque on 1:");
  Serial.println(dxl.torqueOn(1));

  dmx_slave.enable();
  dmx_slave.setStartAddress (91); 
  Serial.println("[INFO] DMX set up");

  delay(500);

  Serial.println("Setting velocity...");

  Serial.print("Present velocity: ");
  Serial.println(dxl.getPresentVelocity(0));
  

}

void setup() {
  // put your setup code here, to run once:
  setup_sequence(5);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t hand1_highByte = dmx_slave.getChannelValue(1); // Coarse (MSB)
  uint8_t hand1_lowByte  = dmx_slave.getChannelValue(2); // Fine (LSB)

  uint8_t hand2_highByte = dmx_slave.getChannelValue(3); // Coarse (MSB)
  uint8_t hand2_lowByte  = dmx_slave.getChannelValue(4); // Fine (LSB)

  // Combine into a 16-bit integer (0 to 65535)
  uint16_t hand1 = (hand1_highByte << 8) | hand1_lowByte;
  uint16_t hand2 = (hand2_highByte << 8) | hand2_lowByte;

  uint8_t hand1_debug = dmx_slave.getChannelValue(5); // Coarse (MSB)
  uint8_t hand2_debug  = dmx_slave.getChannelValue(6); // Fine (LSB)
  

  dxl.setGoalVelocity(0, hand1_debug, UNIT_RAW);
  dxl.setGoalVelocity(1, hand2_debug, UNIT_RAW);

  dxl.setGoalPosition(0, hand1*11.375, UNIT_RAW);
  dxl.setGoalPosition(1, hand2*11.375, UNIT_RAW);

  if (hand1> 0){
    Serial.println("hand 1 :");
    Serial.println(hand1);
  }
  if (hand2> 0){
    Serial.println("hand 2 :");
    Serial.println(hand2);
  }
  


  

    
}
