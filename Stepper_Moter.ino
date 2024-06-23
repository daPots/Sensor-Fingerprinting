const int stepsPerRevolution = 32;
#include <Stepper.h>
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {myStepper.setSpeed(350);}

void loop() {myStepper.step(stepsPerRevolution);}
