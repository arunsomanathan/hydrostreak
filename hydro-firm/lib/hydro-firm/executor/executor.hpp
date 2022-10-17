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
 * @since: 29-09-2022
 */

#ifndef EXECUTOR_EXECUTOR_H
#define EXECUTOR_EXECUTOR_H

#include <cstdint>
#include <data/process/process.hpp>
#include <sensors/read-sensors/read-sensors.hpp>
#include <system/process/process.hpp>

namespace MainExecutor {

const uint32_t BAUD_RATE = 115200;

// Delay in executing system loop
const uint32_t DELAY = 1000; // In milliseconds

// const uint8_t ARDUINO_UNO = 0;
const uint8_t NODE_MCU = 1;

// Type of device
const uint8_t DEVICE_TYPE = NODE_MCU;

// Logging enabled
const bool LOGGING_ENABLED = true;

class Executor {

private:
  Sensors::ReadSensors *readSensors = nullptr;
  System::Process *systemProcess = nullptr;
  Data::Process *dataProcess = nullptr;

public:
  explicit Executor(Sensors::ReadSensors *readSensors, System::Process *systemProcess, Data::Process *dataProcess);

  /*
   * Runner the Setup
   */
  virtual void setup() const;

  /*
   * Runner the Loop
   */
  virtual void loop() const;
};

} // namespace MainExecutor

#endif