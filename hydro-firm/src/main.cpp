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
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 03-09-2022
 */

#include <Arduino.h>
#include <Logger.h>
#include <data/process/process.h>
#include <sensors/read-sensors/read-sensors.h>
#include <system/process/process.h>

const uint32 BAUD_RATE = 115200;

// Delay in executing system loop
const uint32 DELAY = 1000;  // In milliseconds

const byte ARDUINO_UNO = 0;
const byte NODE_MCU = 1;

// Type of device
const byte DEVICE_TYPE = NODE_MCU;

// Logging enabled
const bool LOGGING_ENABLED = true;

// Read Sensors
Sensors::ReadSensors *readSensors = Sensors::ReadSensors::getInstance();

// System Process
System::Process *systemProcess = System::Process::getInstance();

// Data Processor
Data::Process *dataProcess = Data::Process::getInstance();

/**
 * Initial setup
 */
void setup() {
  Serial.begin(BAUD_RATE);

  if (DEVICE_TYPE == NODE_MCU) {
    // setupNodeMCU();
  }
  // Reset Sesonr Values to default
  // Reset Cool Down Period
  // Reset Water Cycle Timer
  // Set Water Cycle off
}

/**
 * Main Loop
 */
void loop() {
  Logger::notice("Begin Loop");
  // Get duration in millisecond after the system started running
  //  TODO(arunc): The value of millis will go back to zero in about 50 days
  //  time. This needs to be handled.
  //  TODO(arunc): Move this to a function
  // unsigned long currentMillis = millis();

  readSensors->readAllSensors();

  systemProcess->run();

  dataProcess->run();

  Logger::notice("Delay");
  delay(DELAY);

  Logger::notice("Repeating Loop");
}