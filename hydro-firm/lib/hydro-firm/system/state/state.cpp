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

#include <sensors/moisture-level/moisture-level.hpp>
#include <sensors/water-level/water-level.hpp>
#include <system/state/state.hpp>

/*
 * Constructor
 */
System::State::State(Sensors::ReadSensors &readSensors) : readSensors{&readSensors} {}

/*
 * Checks if the current water level is greater than or equal to maximum
 * allowed water level.
 */
// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
auto System::State::isWaterLevelMax() -> bool {
  const auto waterLevel = this->readSensors->getSensorReading(Sensors::WATER_LEVEL_SENSOR);
  return (waterLevel >= WATER_LEVEL_MAX_ALLOWED);
}

/*
 * Checks if the current water level is less than or equal to minimum allowed
 * water level.
 */
// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
auto System::State::isWaterLevelMin() -> bool {
  const auto waterLevel = this->readSensors->getSensorReading(Sensors::WATER_LEVEL_SENSOR);
  return waterLevel <= WATER_LEVEL_MIN_ALLOWED;
}

/*
 * Checks if the current moisture level is less than or equal to minimum
 * allowed moisture level.
 */
// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
auto System::State::isMoistureLevelMin() const -> bool {
  const auto moistureLevel = this->readSensors->getSensorReading(Sensors::MOISTURE_LEVEL_SENSOR);
  return moistureLevel <= MOISTURE_LEVEL_MIN_ALLOWED;
}

/*
 * Set system state to Cool Down State. In this state pump should be off and
 * valve should be closed.
 */
void System::State::setCoolDownState() { this->coolDownState = true; }

/*
 * Reset system state from Cool Down State. In this state watering cycle can be
 * started. Here system transition into Active state.
 */
void System::State::resetCoolDownState() {
  this->coolDownState = false;
  setActiveState();
}

/*
 * Checks if the system is in Cool down state. Cool Down state will be enabled
 * after completing watering cycle for a predefined period of time. During
 * this period a new watering cycle will not be started.
 */
auto System::State::isCoolDownState() const -> bool { return this->coolDownState; }

/*
 * Set system state to Active State. In this state watering cycle can be
 * started.
 */
void System::State::setActiveState() { this->activeState = true; }

/*
 * Reset system state from Active State. In this state watering cycle can be
 * started. Here system transition into Cool Down state.
 */
void System::State::resetActiveState() {
  this->activeState = false;
  setCoolDownState();
}

/*
 * Checks if the system is in Active state. System moves to the active state
 * after completing the cool down period. In Active state system can start a
 * watering cycle provided all conditions are met.
 */
auto System::State::isActiveState() const -> bool { return this->activeState; }

/*
 * Set system state to Watering Cycling State. In this state pump will be on
 * and valve will be closed.
 */
void System::State::setWateringCycleState() { this->wateringCycleState = true; }

/*
 * Reset system state from Watering Cycling State. In this state pump will be
 * off and valve will be open.
 */
void System::State::resetWateringCycleState() { this->wateringCycleState = false; }

/*
 * Checks if the system is in Watering Cycle State. In Watering Cycle State
 * system will start moving water to plant containers and hold the water in
 * plant containers for a predefined amount of time.
 */
auto System::State::isWateringCycleState() const -> bool { return this->wateringCycleState; }

/**
 * Set the pump on or off state
 */
void System::State::setPumpOn(const bool state) { this->pumpOn = state; }

/*
 * Checks if the pump is working.
 */
auto System::State::isPumpOn() const -> bool { return this->pumpOn; }

/**
 * Set the valve on or off state
 */
void System::State::setValveClosed(const bool state) { this->valveClosed = state; }

/*
 * Checks if the valve is closed.
 */
auto System::State::isValveClosed() const -> bool { return this->valveClosed; }
