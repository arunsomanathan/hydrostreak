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

#ifndef SENSORS_SENSOR_H
#define SENSORS_SENSOR_H

#include <Arduino.h>

namespace Sensors
{

  enum SENSOR_TYPE
  {
    ANALOG = true,
    DIGITAL = false
  };

  class Sensor
  {

  private:
    static const short DEFAULT_DELAY = 10;

    // Sensor type
    const String type;
    // Delay after power on the sensor and reading the value
    int16_t readDelay;
    // Pin for reading the sensor
    byte readPin;
    // Pin for powering the sensor
    byte powerPin;
    // Is sensor Analog.pr digital
    SENSOR_TYPE isAnalogOrDigital;
    // Enable powering on of sensor
    bool isPowerOnEnabled;

    // Sensor value
    int reading;

    /*
     * Private constructor for Sensors
     */
    explicit Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital, byte readPin, byte powerPin, short readDelay, bool isPowerOnEnabled);

  public:
    static const bool ENABLE_POWER_ON = true;
    static const bool DISABLE_POWER_ON = true;

    /*
     * Read different sensor data and save for further processing.
     */
    void read();

    /*
     * Get the sensor type
     */
    String getType();

    /*
     * Get the sensor reading value
     */
    short getReading();

  protected:
    /*
     * Protected constructor for Sensors
     */
   explicit Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital,
                   byte readPin, byte powerPin, int16_t readDelay);

   /*
    * Protected constructor for Sensors
    */
   explicit Sensor(const String &type, SENSOR_TYPE isAnalogOrDigital,
                   byte readPin, byte powerPin);

   /*
    * Protected constructor for Sensors
    */
   explicit Sensor(const String &type, byte readPin, byte powerPin,
                   int16_t readDelay);

   /*
    * Protected constructor for Sensors
    */
   explicit Sensor(const String &type, byte readPin, byte powerPin);

   /*
    * Protected constructor for Sensors
    */
   explicit Sensor(const String &type, byte readPin);

   /*
    * Protected constructor for Sensors
    */
   explicit Sensor(const String &type, SENSOR_TYPE isAnalog, byte readPin);

   /*
    * Calibrate the sensor
    */
   void calibrateSensor();

   /*
    * Initialize sensor before reading.
    */
   void initSensor();

   /*
    * Reset the sensor.
    */
   void resetSensor();

   /*
    * Power on the sensor
    */
   void powerOnSensor();

   /*
    * Power off the sensor
    */
   void powerOffSensor();

   /*
    * Read the sensor
    */
   void readSensor();

   /*
    * Read from analog sensor
    */
   void readAnalogSensor();

   /*
    * Read from digital sensor
    */
   void readDigitalSensor();
  };
} // namespace Sensors

#endif
