# Fingerprinting Ultrasonic Sensors With Machine Learning

## Hey there! This is my research project for the 2024 REU program at Tennessee Tech University.

### Data Collection
* Collect data from a series of ultrasonic sensors (4) using Arduino
* Each ultrasonic sensor is connected to its own INA219 current sensor, which measures electrical quantities
* Data to collect: Distance, Voltages, Current, and Power across the ultrasonic sensor
* There were two "types" of distances collected: Distance from a static box, and Distance from a moving box
  * Static: box was placed at different ranges from sensors and data was collected
  * Moving: box was placed at different ranges, but was pulled closer (100cm) to sensors by a stepper motor
* Around 30,000 samples were collected across ~9 hours (aggregate)

### Machine Learning
* Goal is to identify which sensor a given segment of data is from
* Data was stored into a txt files in an undesirable format
* Developed python script to combine all txt files and reformat data into 1 clean CSV file
* Used PyTorch & Scikit-Learn to build Decision Tree & SVM ML models. 
