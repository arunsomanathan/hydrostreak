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

#ifndef SENSORS_READ_SENSORS_READ_SENSORS_H
#define SENSORS_READ_SENSORS_READ_SENSORS_H

#include <sensors/moisture-level/moisture-level.h>
#include <sensors/water-level/water-level.h>

namespace Sensors
{

  // Always keep SENSOR_MAX as the last item in the enum.
  enum ACTIVE_SENSOR
  {
    WATER_LEVEL_SENSOR,
    MOISTURE_LEVEL_SENSOR
  };

  // TODO(arunc): this may be an issue on using a different microcontroller
  const uint8_t ANALOG_READ_PIN = 02; // A0 Pin
  const uint8_t POWER_PIN = 16;       // D8 Pin

  class ReadSensors
  {

  private:
    WaterLevelSensor *waterLevelSensor;
    MoistureLevelSensor *moistureLevelSensor;
    int16_t sensorReadings[MOISTURE_LEVEL_SENSOR+1]{};

    /*
     * Constructor
     */
    explicit ReadSensors();

    static ReadSensors *readSensors_;

  public:
    /**
     * ReadSensors should not be cloneable.
     */
    ReadSensors(ReadSensors &other) = delete;
    /**
     * ReadSensors should not be assignable.
     */
    void operator=(const ReadSensors &) = delete;

    /**
     * Get singleton instance of ReadSensors class.
     */
    static ReadSensors *getInstance();

    /*
     * Read all sensors.
     */
    void readAllSensors();

    /*
     * Read a specific sensors.
     */
    void readASensor(ACTIVE_SENSOR activeSensor);

    /*
     * Method for getting the sensor reading
     */
    short *getAllSensorReading();

    /*
     * Method for getting the reading of a specific sensor
     */
    short getASensorReading(ACTIVE_SENSOR activeSensor);
  };

  ReadSensors *ReadSensors::readSensors_ = nullptr;
} // namespace Sensors


#endif
