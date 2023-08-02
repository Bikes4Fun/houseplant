/* 
Automated Houseplant Watering System
Powered by Arduino and Raspberry Pi

An initial custom smarthome project
Intended to provide automated watering, button press watering,
and wifi based anywhere watering as well as compatiblity with Apple Home 

I am very new to arduino, and I don't have all of the equipment - this code has not be tested. 
This is concept code that will be completed, validated and tested when the equipment is present. 

Initially inspired by @b_turner50: tiktok
Adapted from arduino's tutorial
Adapted from https://github.com/ryderd9323/HouseplantAutocare/tree/main
Adapted from https://littlebirdelectronics.com.au/guides/4/automatic-plant-watering-with-arduino

 Planned components:
- Arduino Uno 
- Raspberry Pi (could be replaced with an arduino wifi I believe).
- TV/Desktop monitor (if intigrating into command center).
- 5V submersible pump.
- 1 meter watering pipe.
- USB wall adapter
- Water container.
- Micro-USB cable.
- Open ended USB Cable.
- Soil moisture sensor. https://tinyurl.com/bdfjua8u
- button
*/

/*--configure pins--*/

const int buttonPin = A1; //analog in A1: button to manually initialize a watering session
const int moistureMin = 20; //percent: this plant's minimum moisture - change based on plant type, to become input from Apple Home
const int moistureMax = 90; //percent: this plants maximum moisture - to become input from Apple Home
const int moisturePin = A0; //analog in A0: moisture sensor
const int pumpPin = 2; //turn on pump
const int waterTime = 10; //watering time in seconds - to become an input from Apple Home
const int waitTime = 5; //wait time between watering in minutes 

bool watering = false; //initialize 'watering' tracking variable to not watering.
unsigned long currentTime = 0; //initialize with Apple Home current time
unsigned long startedWatering = 0; //track how long we watered.

void setup() {
    pinMode(pumpPin, OUTPUT); //initialize pumpPin as output
    Serial.begin(9600);
    stopWatering(); //initialize with pump off to avoid overwatering 
}

//connect to Apple Home or Raspberry Pi

void loop() {
    int rawMoisture = analogRead(moisturePin);
    int moisturePercent = ( 100 - ( rawMoisture / 1023.00) * 100 ); //convert analog value to percentage
    logMoisture(); //track moisture levels

    if (moisturePercent < moistureMin) {
        startWatering(moisturePercent); //call startedWatering which will ensure safety conditions for watering are met before watering
    }

    else {
        //if moisturePercent was higher than moistureMin, stop watering and delay another watering event.
        digitalWrite(motorPin, LOW);  //turn off the motor
        delay(waitTime * 60000);      //multiply by 60000 to translate minutes to milliseconds
    }
    relayVal = digitalRead(relayPin);
    Serial.write(relayVal);

}

logMoisture () {
    //set up with apple home
    logPercent = Serial.print(moisturePercent);
    digitalWrite(logPercent, HIGH);
}

void startWatering (moisturePercent) {
    if (canContinueWatering(moisturePercent)) {
        startedWatering = millis();
        watering = true;
        digitalWrite(motorPin, HIGH);
        delay(watertime * 1000); 
    }
}

void stopWatering () {
  watering = false;
  digitalWrite(motorPin, LOW);
}

void canContinueWatering () {
     // Ensure watering time hasn't elapsed. 
     // Stop watering after the configured duration
    if (watering && (millis() - startedWatering) >= waterTime*1000) || (moisturePercent > moistureMax) {
        stopWatering();
        return false;
    }
    return true;
}
