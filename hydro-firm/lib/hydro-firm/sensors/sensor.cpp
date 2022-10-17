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
 * @since: 08-09-2022
 */

#include <sensors/sensor.hpp>

#ifdef NATIVE
#include <ArduinoFake.h>
#else
#include <Arduino.h>
#endif

namespace Sensors {

/*
 * Protected constructor for Sensors
 */
Sensor::Sensor(const std::string &type, const SENSOR_TYPE isAnalogOrDigital, const uint8_t readPin,
               const uint8_t powerPin)
    : type(type), isAnalogOrDigital(isAnalogOrDigital), readPin(readPin), powerPin(powerPin), readDelay(DEFAULT_DELAY),
      isPowerOnEnabled(ENABLE_POWER_ON) {
  this->setupSensor(); // LCOV_EXCL_BR_LINE
}

/*
 * Protected constructor for Sensors
 */
Sensor::Sensor(const std::string &type, const SENSOR_TYPE isAnalogOrDigital, const uint8_t readPin)
    : type(type), isAnalogOrDigital(isAnalogOrDigital), readPin(readPin), powerPin(-1), readDelay(DEFAULT_DELAY),
      isPowerOnEnabled(DISABLE_POWER_ON) {
  this->setupSensor(); // LCOV_EXCL_BR_LINE
}

/*
 * Setup the sensor
 */
void Sensor::setupSensor() {
  this->reading = 0;
  this->calibrateSensor();
}

/*
 * Calibrate the sensor
 */

void Sensor::calibrateSensor() {
  // Logger::verbose("Sensors>sensor", (String("Calibrating sensor: ") +
  // this->type).c_str());
}

/*
 * Initialize sensor before reading. This method will be called each time the
 * sensor is powered on.
 */
void Sensor::initSensor() {
  // Logger::verbose("Sensors>sensor", (String("Initialising sensor: ") +
  // this->type).c_str());
}

/*
 * Reset sensor.
 */
void Sensor::resetSensor() {
  // Logger::verbose("Sensors>sensor", (String("Resetting sensor: ") +
  // this->type).c_str());
  reading = 0;
}

/*
 * Power on the sensor
 */
void Sensor::powerOnSensor() const {
  // Logger::verbose("Sensors>sensor", (String("Powering on sensor: ") +
  // this->type).c_str());
  digitalWrite(this->powerPin, HIGH);
}

/*
 * Power off the sensor
 */
void Sensor::powerOffSensor() const {
  // Logger::verbose("Sensors>sensor", (String("Powering off sensor") +
  // this->type).c_str());
  digitalWrite(this->powerPin, LOW);
}

/*
 * Read the sensor
 */
void Sensor::readSensor() {

  if (this->isPowerOnEnabled) {
    this->powerOnSensor();
    delay(this->readDelay);
  }

  this->initSensor();

  // Logger::verbose("Sensors>sensor", (String("Reading from sensor: ") +
  // this->type).c_str());

  if (this->isAnalogOrDigital == ANALOG) {
    this->readAnalogSensor();
  } else {
    this->readDigitalSensor();
  }

  if (this->isPowerOnEnabled) {
    this->powerOffSensor();
  }
}

/*
 * Read from analog sensor
 */
void Sensor::readAnalogSensor() {
  // Logger::verbose("Sensors>sensor", (String("Reading from Analog sensor: ") +
  // this->type).c_str());
  this->reading = analogRead(this->readPin);
}

/**
 * Read from digital sensor
 */
void Sensor::readDigitalSensor() {
  // Logger::verbose("Sensors>sensor", (String("Reading from Digital sensor: " +
  // this->type).c_str()));
  this->reading = digitalRead(this->readPin);
}

/**
 * Get the type of sensor
 */
auto Sensor::getType() -> std::string { return this->type; }

/**
 * Get the sensor reading
 */
auto Sensor::getReading() const -> int { return this->reading; }

} // namespace Sensors
