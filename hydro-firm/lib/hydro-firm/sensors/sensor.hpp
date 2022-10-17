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

#ifndef SENSORS_SENSOR_HPP
#define SENSORS_SENSOR_HPP

#include <cstdint>
#include <string>

namespace Sensors {

enum SENSOR_TYPE { ANALOG, DIGITAL };

class Sensor {

private:
  static const int16_t DEFAULT_DELAY = 10;

  // Sensor type
  const std::string type;
  // Is sensor Analog.pr digital
  const SENSOR_TYPE isAnalogOrDigital;
  // Pin for reading the sensor
  const uint8_t readPin;
  // Pin for powering the sensor
  const uint8_t powerPin;
  // Delay after power on the sensor and reading the value
  const int16_t readDelay;
  // Enable powering on of sensor
  const bool isPowerOnEnabled;

  // Sensor value
  int reading = 0;

  /*
   * Power on the sensor
   */
  void powerOnSensor() const;

  /*
   * Power off the sensor
   */
  void powerOffSensor() const;

  /*
   * Read from analog sensor
   */
  void readAnalogSensor();

  /*
   * Read from digital sensor
   */
  void readDigitalSensor();

  /*
   * Calibrate the sensor
   */
  void calibrateSensor();

  /*
   * Setup the sensor
   */
  void setupSensor();

public:
  static const bool ENABLE_POWER_ON = true;
  static const bool DISABLE_POWER_ON = false;

  /*
   * Read different sensor data and save for further processing.
   */
  virtual void readSensor();

  /*
   * Initialize sensor before reading.
   */
  virtual void initSensor();

  /*
   * Reset the sensor.
   */
  virtual void resetSensor();

  /*
   * Get the sensor type
   */
  virtual auto getType() -> std::string;

  /*
   * Get the sensor reading value
   */
  virtual auto getReading() const -> int;

protected:
  /*
   * Protected constructor for Sensors
   */
  explicit Sensor(const std::string &type, SENSOR_TYPE isAnalogOrDigital, uint8_t readPin, uint8_t powerPin);

  /*
   * Protected constructor for Sensors without power on & off functionality
   */
  explicit Sensor(const std::string &type, SENSOR_TYPE isAnalogOrDigital, uint8_t readPin);
};
} // namespace Sensors

#endif
