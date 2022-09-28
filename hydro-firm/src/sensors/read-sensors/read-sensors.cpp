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
 * @since: 03-09-2022
 */

#include <Logger.h>
#include <sensors/read-sensors/read-sensors.h>

namespace Sensors {

/**
 * Get singleton instance of ReadSensors class.
 */
auto ReadSensors::getInstance() -> ReadSensors* {
  if (readSensors_ == nullptr) {
    ReadSensors::readSensors_ = new ReadSensors();
  }
  return ReadSensors::readSensors_;
}

/*
 * Constructor
 */

ReadSensors::ReadSensors() {
  this->moistureLevelSensor =
      MoistureLevelSensor::getInstance(ANALOG_READ_PIN, POWER_PIN);
  this->waterLevelSensor =
      WaterLevelSensor::getInstance(ANALOG_READ_PIN, POWER_PIN);
}

/*
 * Read all sensors.
 */
void ReadSensors::readAllSensors() {
  Logger::notice("Sensors>Read-Sensors", "Start reading sensors");

  // Read moisture level
  this->moistureLevelSensor->read();
  sensorReadings[MOISTURE_LEVEL_SENSOR] =
      this->moistureLevelSensor->getReading();

  // Read water level
  this->waterLevelSensor->read();
  sensorReadings[WATER_LEVEL_SENSOR] = this->waterLevelSensor->getReading();
}

/*
 * Read a specific sensors.
 */
void ReadSensors::readASensor(ACTIVE_SENSOR activeSensor) {
  switch (activeSensor) {
    case MOISTURE_LEVEL_SENSOR:
      Logger::notice(
          "Sensors>Read-Sensors",
          (String("Start reading from ") + this->moistureLevelSensor->getType())
              .c_str());
      this->moistureLevelSensor->read();
      sensorReadings[MOISTURE_LEVEL_SENSOR] =
          this->moistureLevelSensor->getReading();

      break;
    case WATER_LEVEL_SENSOR:
      Logger::notice("Sensors>Read-Sensors", (String("Start reading from ") +
                                              this->waterLevelSensor->getType())
                                                 .c_str());
      this->waterLevelSensor->read();
      sensorReadings[WATER_LEVEL_SENSOR] = this->waterLevelSensor->getReading();

      break;
  }
}

/*
 * Method for getting the sensor reading
 */
auto ReadSensors::getAllSensorReading() -> int16_t* {
  Logger::notice("Sensors>Read-Sensors", "Get sensor reading values");
  return sensorReadings;
}

/*
 * Method for getting the reading of a specific sensor
 */
auto ReadSensors::getASensorReading(ACTIVE_SENSOR activeSensor) -> int16_t {
  switch (activeSensor) {
    case MOISTURE_LEVEL_SENSOR:
      Logger::notice("Sensors>Read-Sensors",
                     (String("Get sensor reading from ") +
                      this->moistureLevelSensor->getType())
                         .c_str());
      return sensorReadings[MOISTURE_LEVEL_SENSOR];
    case WATER_LEVEL_SENSOR:
      Logger::notice("Sensors>Read-Sensors",
                     (String("Get sensor reading from ") +
                      this->waterLevelSensor->getType())
                         .c_str());
      return sensorReadings[WATER_LEVEL_SENSOR];
  }
  return 0;
}
}  // namespace Sensors
