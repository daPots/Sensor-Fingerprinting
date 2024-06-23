#include <Wire.h>
#include <Adafruit_INA219.h>

const int NUM_SENSORS = 4;

Adafruit_INA219 ina219_sensors[NUM_SENSORS] = {Adafruit_INA219(0x41), Adafruit_INA219(0x44), Adafruit_INA219(0x40), Adafruit_INA219(0x45)};
int trigPins[NUM_SENSORS] = {13, 11, 9, 7};
int echoPins[NUM_SENSORS] = {12, 10, 8, 6};

long duration;
double distancemm;
int iteration = 0;

void setup() {
  for(int i=0; i<NUM_SENSORS; i++){
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
  Serial.begin(9600);
  while(!Serial) delay(1);
  for(int i=0; i<NUM_SENSORS; i++){
    if (!ina219_sensors[i].begin()){
      Serial.println("Failed to find INA219 chip");
      while(1) delay(10);
    }
  }
}

void loop() {
  Serial.print("GROUP "); Serial.println(iteration);
  printDistance(trigPins[iteration], echoPins[iteration]);
  printCVP(iteration);
  if(iteration<NUM_SENSORS-1) iteration++;
  else iteration = 0;
  delay(100);
}

void printDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distancemm= duration*0.343/2.0;
  delay(100);

  Serial.print("Distance: "); Serial.print(distancemm); Serial.println("mm  ");
  delay(100);
}

void printCVP(int sensor){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219_sensors[sensor].getShuntVoltage_mV();
  busvoltage = ina219_sensors[sensor].getBusVoltage_V();
  current_mA = ina219_sensors[sensor].getCurrent_mA();
  power_mW = ina219_sensors[sensor].getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
}
