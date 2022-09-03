//Maximum allowed water level
const short WATER_LEVEL_MAX_ALLOWED = 10;

//Maximum allowed water level
const short WATER_LEVEL_MIN_ALLOWED = 0;

//Minimum allowed moisture level
const short MOISTURE_LEVEL_MIN_ALLOWED = 10;

//Delay in executing system loop
const unsigned long DELAY = 1000;  //In milliseconds

//Water Level
short waterLevel = 0;

//Water Level
short waterLevel = 0;

//Mositure Level
short moistureLevel = 0;

/**
* Initial setup
*/
void setup() {
  // Reset Sesonr Values to default
  // Reset Cool Down Period
  // Reset Water Cycle Timer
  // Set Water Cycle off
}

/**
* Main Loop
*/
void loop() {

  //Get duration in millisecond after the system started running
  //TODO: The value of millis will go back to zero in about 50 days time. This needs to be handled.
  //TODO: Move this to a function
  unsigned long currentMillis = millis();

  readSensors();

  run();

  processData();

  delay(DELAY);
}

/*
 * Read different sensor data and save for further processing.
 */
void readSensors() {
  //TODO: Read Water Level

  //TODO: Read Moisture Level
}

/*
 * Run the system processes.
 */
void run() {
  if (isCoolDownState()) {
    handleCoolDownState();
  } else if (isActiveState()) {
    handleActiveState();
  } else {
    forceWateringCycle();
  }
}

/*
 * Handle Cool down state of the system..
 */
void handleCoolDownState() {
  if (isWaterLevelMin()) {
    //Close the valve after draining all the water
    closeValve();
  } else {
    //Continue water draining if in water level is not minimum in cool down
    drainWater();
  }
}

/*
 * Handle Active state of the system.
 */
void handleActiveState() {
  if (isWaterLevelMax()) {
    drainWater();
  } else {
    if (isWaterLevelMin()) {
      if (isMoistureLevelMin()) {
        fillWater();
      } else {
        closeValve();
      }
    }
  }
}

/*
 * Handle Force watering cycle state of the system.
 */
void forceWateringCycle() {
  //Force Watering Cycle Mode
  if (isWaterLevelMax()) {
    drainWater();
  } else {
    fillWater();
  }
}

/*
 * Drain water from the Plant Container and set system to cool down state.
 * Also resets the watering cycle state.
 */
void drainWater() {

  turnOffPump();

  openValve();

  resetWateringCycleState();

  setCoolDownState();
}

/*
 * Fill water to the Plant Container and set system to watering cycle state.
 */
void fillWater() {

  closeValve();

  turnOnPump();

  setWateringCycleState();
}

//=============== Date Analytics and Storage Operation - Begin ===============/

void processData() {
  //TODO a place holder function for processing data
}
//=============== Date Analytics and Storage Operation - End ===============/

//=============== State Check Section - Begin ===============/
//TODO: Can be moved to another file

/*
 * Checks if the current water level is greater than or equal to maximum
 * allowed water level.
 */
bool isWaterLevelMax() {
  return waterLevel >= WATER_LEVEL_MAX_ALLOWED;
}

/*
 * Checks if the current water level is less than or equal to minimum allowed
 * water level.
 */
bool isWaterLevelMin() {
  return waterLevel >= WATER_LEVEL_MIN_ALLOWED;
}

/*
 * Checks if the current moisture level is less than or equal to minimum
 * allowed moisture level.
 */
bool isMoistureLevelMin() {
  return moistureLevel <= MOISTURE_LEVEL_MIN_ALLOWED;
}

/*
 * Checks if the system is in Cool down state. Cool Down state will be enabled
 * after completing watering cycle for a predefined period of time. During
 * this period a new watering cycle will not be started.
 */
bool isCoolDownState() {
  //TODO: Check if system is in Cool Down state
  return false;
}

/*
 * Checks if the system is in Active state. System moves to the active state
 * after completing the cool down period. In Active state system can start a
 * watering cycle provided all conditions are met.
 */
bool isActiveState() {
  //Check if system is in Active State
  return true;
}

/*
 * Checks if the system is in Watering Cycle State. In Watering Cycle State
 * system will start moving water to plant containers and hold the water in
 * plant containers for a predefined amount of time.
 */
bool isWateringCycleState() {
  //Check if system is in Watering Cycle state
  return false;
}

/*
 * Checks if the pump is working. 
 */
bool isPumpOn() {
  //TODO: Check if the pump is working
  return false;
}

/*
 * Checks if the valve is closed. 
 */
bool isValveClosed() {
  //TODO: Check if the valve is closed
  return false;
}

//=============== State Check Section - End ===============/


//=============== Set State Section - Begin ===============/

/*
 * Set system state to Watering Cycling State. In this state pump will be on
 * and valve will be closed. 
 */
void setWateringCycleState() {
  //TODO: Set watering cycle state
  if (!isWateringCycleState()) {
  }
}

/*
 * Reset system state from Watering Cycling State. In this state pump will be
 * off and valve will be open. 
 */
void resetWateringCycleState() {
  //TODO: Reset watering cycle state
}

/*
 * Set system state to Cool Down State. In this state pump should be off and
 * valve should be closed. 
 */
void setCoolDownState() {
  //TODO: Set Cool Down State.
  if (!isCoolDownState()) {
  }
}

/*
 * Reset system state from Cool Down State. In this state watering cycle can be
 * started. Here system transition into Active state. 
 */
void resetCoolDownState() {
  //TODO: Reset Cool Down State
  setActiveState();
}

/*
 * Set system state to Active State. In this state watering cycle can be
 * started.
 */
void setActiveState() {
  //TODO: Set Active State
}

/*
 * Reset system state from Active State. In this state watering cycle can be
 * started. Here system transition into Cool Down state. 
 */
void resetActiveState() {
  //TODO: Reset Active State
  setCoolDownState();
}

//=============== Set State Section - End ===============/

//=============== Controller Section - Begin ===============/

/*
 * Turn On Pump. 
 */
void turnOnPump() {
}

/*
 * Turn Off Pump. 
 */
void turnOffPump() {
  if (isPumpOn()) {
  }
}

/*
 * Close Valve. 
 */
void closeValve() {
  if (!isValveClosed()) {
    //TODO: close the valve
  }
}

/*
 * Open valve.
 */
void openValve() {
  if (isValveClosed()) {
    //TODO: Open the valve
  }
}

//=============== Controller Section - End =================/


//=============== Sensor Section - Begin ====================/

/*
 * Reads the water level in Plant containers and saves it to water level
 * global variable
 */
void readWaterLevel() {
  //TODO: Water Level reading logic
  waterLevel = 0;
}

/*
 * Reads the moinsture level in Plant containers and saves it to moisture level
 * global variable
 */
void readMoistureLevel() {
  //TODO: Moisture Content reading logic
  moistureLevel = 0;
}
//=============== Sensor Section - End ====================/