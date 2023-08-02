/*
setting up ideas for reusing houseplant as a template for many plants.
*/

#include houseplant

const int buttonPin = A1; //externally assigned analog pin: button to manually initialize a watering session
const int moistureMin = 1; //percent: this plant's minimum moisture - change based on plant type, to become input from Apple Home
const int moistureMax = 90; //percent: this plants maximum moisture - to become input from Apple Home
const int moisturePin = A0; //analog in A0: moisture sensor
const int pumpPin = 2; //turn on pump
const int waterTime = 60; //watering time in seconds - to become an input from Apple Home
const int waitTime = 5; //wait time between watering in minutes

void setup () {
    setPlantParameters(buttonPin, moistureMin, moistureMax, moisturePin, pumpPin, waterTime, waitTime);
    ::setup(); // Call the setup function from template.io to configure pins, etc.
    // Continuously loop over the template program
}

void loop () {
    ::loop();
    logValues();
}

void logValues () {
    //implement ability to log current values to apple home 
    Serial.print("Moisture Percent: ");
    Serial.println(moisturePercent);
}