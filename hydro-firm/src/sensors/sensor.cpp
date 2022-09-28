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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

#include <sensors/sensor.h>
#include <Logger.h>
#include <Arduino.h>
#include <utility>

namespace Sensors
{

  /*
   * Private constructor for Sensors
   */
Sensor::Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital, byte readPin,
               byte powerPin, int16_t readDelay, bool isPowerOnEnabled)
    : type(std::move(type)) {
  this->isAnalogOrDigital = isAnalogOrDigital;
  this->readPin = readPin;
  this->powerPin = powerPin;
  this->readDelay = readDelay;
  this->isPowerOnEnabled = isPowerOnEnabled;
  this->reading = 0;
  calibrateSensor();
}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital, byte readPin,
               byte powerPin, int16_t readDelay) :
  Sensor(type, isAnalogOrDigital, readPin, powerPin, readDelay,
         ENABLE_POWER_ON)
{}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital, byte readPin,
               byte powerPin) : Sensor(type, isAnalogOrDigital, readPin, powerPin, DEFAULT_DELAY)
{}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, byte readPin, byte powerPin,
               int16_t readDelay) :Sensor(type, DIGITAL, readPin, powerPin, readDelay)
{}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, byte readPin, byte powerPin) : Sensor(type, readPin, powerPin, DEFAULT_DELAY)
{}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital, byte readPin)
    : type(std::move(type)) {
  this->isAnalogOrDigital = isAnalogOrDigital;
  this->readPin = readPin;
  this->isPowerOnEnabled = DISABLE_POWER_ON;
  this->powerPin = -1;
  this->readDelay = -1;
  this->reading = 0;
}

  /*
   * Protected constructor for Sensors
   */
Sensor::Sensor(const String &type, byte readPin) : Sensor(type, DIGITAL, readPin)
{}

  /*
   * Calibrate the sensor
   */

  void Sensor::calibrateSensor()
  {
    Logger::verbose("Sensors>sensor", (String("Calibrating sensor: ") + this->type).c_str());
  }

  /*
   * Initialize sensor before reading. This method will be called each time the sensor is powered on.
   */
  void Sensor::initSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Initialising sensor: ") + this->type).c_str());
  }

  /*
   * Reset sensor.
   */
  void Sensor::resetSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Resetting sensor: ") + this->type).c_str());
  }

  /*
   * Power on the sensor
   */
  void Sensor::powerOnSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Powering on sensor: ")+ this->type).c_str());
    digitalWrite(powerPin, HIGH);
  }

  /*
   * Power off the sensor
   */
  void Sensor::powerOffSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Powering off sensor") + this->type).c_str());
    digitalWrite(powerPin, LOW);
  }

  /*
   * Read the sensor
   */
  void Sensor::readSensor()
  {

    if (isPowerOnEnabled)
    {
      powerOnSensor();
    }

    this->initSensor();

    Logger::verbose("Sensors>sensor",(String("Reading from sensor: ")+ this->type).c_str());
    delay(this->readDelay);
    if (isAnalogOrDigital == ANALOG)
    {
      this->readAnalogSensor();
    }
    else
    {
      this->readDigitalSensor();
    }

    if (isPowerOnEnabled)
    {
      this->powerOffSensor();
    }
  }

  /*
   * Read from analog sensor
   */
  void Sensor::readAnalogSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Reading from Analog sensor: ")+this->type).c_str());
    reading = analogRead(readPin);
  }

  /**
   * Read from digital sensor
   */
  void Sensor::readDigitalSensor()
  {
    Logger::verbose("Sensors>sensor",(String("Reading from Digital sensor: "+ this->type).c_str()));
    reading = digitalRead(readPin);
  }
} // namespace Sensors
