#include <Arduino.h>
#include "SCServo.h"

#define SERVO3_CENTER_POSITION 511
#define SERVO4_CENTER_POSITION 511
#define SERVO3_LOWER_LIMIT 20
#define SERVO3_UPPER_LIMIT 1000
#define SERVO4_LOWER_LIMIT 20
#define SERVO4_UPPER_LIMIT 1000
#define WRIST_SERVO_SPEED  500
#define SERVO_ID_0 0
#define SERVO_ID_1 1
#define RX_PIN 16 //TODO
#define TX_PIN 17 //TODO

SCServo SERVO;

void moveServo(){
   // convert euler angles to servo commands
    uint16_t pos0 = (uint16_t) (0 + SERVO3_CENTER_POSITION);
    uint16_t pos1 = (uint16_t) (0 + SERVO3_CENTER_POSITION);
    
    // set limits for servo 0
    if(SERVO3_LOWER_LIMIT > pos0){
        pos0 = SERVO3_LOWER_LIMIT;
    }
    if(pos0 > SERVO3_UPPER_LIMIT){
        pos0 = SERVO3_UPPER_LIMIT;
    }

    // set limits for servo 1
    if(SERVO4_LOWER_LIMIT > pos1){
        pos1 = SERVO4_LOWER_LIMIT;
    }
    if(pos1 > SERVO4_UPPER_LIMIT){
        pos1 = SERVO4_UPPER_LIMIT;
    }

    // send position to servos
    SERVO.WritePos(SERVO_ID_0, pos0%1024, 100, WRIST_SERVO_SPEED);
    SERVO.WritePos(SERVO_ID_1, pos1%1024, 100, WRIST_SERVO_SPEED);
    return;
}

void setup() {
  Serial2.begin(1000000, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize Serial2 for servo communication
  SERVO.pSerial = &Serial2; // Assign Serial to the SCServo instance
}

void loop() {
  moveServo();
}


