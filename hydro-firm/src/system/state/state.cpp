/*
 * MIT License
 *
 * Copyright (c) 2022 ARUN C S
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 09-09-2022
 */

#include <Logger.h>
#include <system/state/state.h>

/**
 * Get singleton instance of State class.
 */
auto System::State::getInstance() -> System::State* {
  if (state_ == nullptr) {
    State::state_ = new State();
  }
  return State::state_;
}

/*
 * Constructor
 */
System::State::State() = default;

/*
 * Checks if the current water level is greater than or equal to maximum
 * allowed water level.
 */
auto System::State::isWaterLevelMax() const -> bool {
  const auto waterLevel =
      readSensors->getASensorReading(Sensors::WATER_LEVEL_SENSOR);
  Logger::verbose("System>State",
                  (String("Water level: ") + String(waterLevel)).c_str());
  bool isWaterLevelMax = waterLevel >= WATER_LEVEL_MAX_ALLOWED;
  Logger::verbose("System>State", (String("Is water level at max? ") +
                                   String(static_cast<int>(isWaterLevelMax)))
                                      .c_str());
  return isWaterLevelMax;
}

/*
 * Checks if the current water level is less than or equal to minimum allowed
 * water level.
 */
auto System::State::isWaterLevelMin() const -> bool {
  auto waterLevel = readSensors->getASensorReading(Sensors::WATER_LEVEL_SENSOR);
  Logger::verbose("System>State",
                  (String("Water level: ") + String(waterLevel)).c_str());
  bool isWaterLevelMin = waterLevel <= WATER_LEVEL_MIN_ALLOWED;
  Logger::verbose("System>State", (String("Is water level at min? ") +
                                   String(static_cast<int>(isWaterLevelMin)))
                                      .c_str());
  return isWaterLevelMin;
}

/*
 * Checks if the current moisture level is less than or equal to minimum
 * allowed moisture level.
 */
auto System::State::isMoistureLevelMin() const -> bool {
  const auto moistureLevel =
      readSensors->getASensorReading(Sensors::MOISTURE_LEVEL_SENSOR);
  Logger::verbose("System>State",
                  (String("Moisture level: ") + String(moistureLevel)).c_str());
  const bool isMoistureLevelMin = moistureLevel <= MOISTURE_LEVEL_MIN_ALLOWED;
  Logger::verbose("System>State", (String("Is moisture level at min? ") +
                                   String(static_cast<int>(isMoistureLevelMin)))
                                      .c_str());
  return isMoistureLevelMin;
}

/*
 * Checks if the system is in Cool down state. Cool Down state will be enabled
 * after completing watering cycle for a predefined period of time. During
 * this period a new watering cycle will not be started.
 */
auto System::State::isCoolDownState() const -> bool {
  Logger::verbose("System>State", "Is in cool down state? ");
  return this->coolDownState;
}

/*
 * Checks if the system is in Active state. System moves to the active state
 * after completing the cool down period. In Active state system can start a
 * watering cycle provided all conditions are met.
 */
auto System::State::isActiveState() const -> bool {
  Logger::verbose("System>State", "Is in active state? ");
  return this->activeState;
}

/*
 * Checks if the system is in Watering Cycle State. In Watering Cycle State
 * system will start moving water to plant containers and hold the water in
 * plant containers for a predefined amount of time.
 */
auto System::State::isWateringCycleState() const -> bool {
  Logger::verbose("System>State", "Is in watering cycle state? ");
  return this->wateringCycleState;
}

/**
 * Set the pump on or off state
 */
void System::State::setPumpOn(const bool state) { this->pumpOn = state; }

/*
 * Checks if the pump is working.
 */
auto System::State::isPumpOn() const -> bool {
  Logger::verbose("System>State", "Is pump on? ");
  return this->pumpOn;
}

/**
 * Set the valve on or off state
 */
void System::State::setValveClosed(const bool state) {
  this->valveClosed = state;
}

/*
 * Checks if the valve is closed.
 */
auto System::State::isValveClosed() const -> bool {
  Logger::verbose("System>State", "Is valve closed? ");
  return this->valveClosed;
}

/*
 * Set system state to Watering Cycling State. In this state pump will be on
 * and valve will be closed.
 */
void System::State::setWateringCycleState() {
  Logger::verbose("System>State",
                  "Set system to watering cycle state if not already set");
  if (!isWateringCycleState()) {
    Logger::notice("System>State", "Setting system to watering cycle state");
    this->wateringCycleState = true;
  }
}

/*
 * Reset system state from Watering Cycling State. In this state pump will be
 * off and valve will be open.
 */
void System::State::resetWateringCycleState() {
  Logger::verbose(
      "System>State",
      "Reset system from watering cycle state if not already reset");
  if (isWateringCycleState()) {
    Logger::notice("System>State",
                   "Resetting system from watering cycle state");
                   this->wateringCycleState = false;
  }
}

/*
 * Set system state to Cool Down State. In this state pump should be off and
 * valve should be closed.
 */
void System::State::setCoolDownState() {
  Logger::verbose("System>State",
                  "Set system to cool down state if not already set");
  if (!isCoolDownState()) {
    Logger::notice("System>State", "Setting system to cool down state");
    this->coolDownState = true;
  }
}

/*
 * Reset system state from Cool Down State. In this state watering cycle can be
 * started. Here system transition into Active state.
 */
void System::State::resetCoolDownState() {
  Logger::verbose("System>State",
                  "Reset system from cool down state if not already reset");
  if (!isCoolDownState()) {
    Logger::notice("System>State", "Resetting system from cool down state");
    this->coolDownState=false;
    setActiveState();
  }
}

/*
 * Set system state to Active State. In this state watering cycle can be
 * started.
 */
void System::State::setActiveState() {
  Logger::verbose("System>State",
                  "Set system to active state if not already set");
  if (!isCoolDownState()) {
    Logger::notice("System>State", "Setting system to active state");
    this->activeState = true;
  }
}

/*
 * Reset system state from Active State. In this state watering cycle can be
 * started. Here system transition into Cool Down state.
 */
void System::State::resetActiveState() {
  Logger::verbose("System>State",
                  "Reset system from active state if not already reset");
  if (!isCoolDownState()) {
    Logger::notice("System>State", "Resetting system from active state");
    this->activeState = false;
    setCoolDownState();
  }
}
