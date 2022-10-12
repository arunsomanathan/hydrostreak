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

#include "executor/executor.h"
#include <data/process/process.h>
#include <list>
#include <memory>
#include <sensors/moisture-level/moisture-level.h>
#include <sensors/read-sensors/read-sensors.h>
#include <sensors/sensor.h>
#include <sensors/water-level/water-level.h>
#include <system/process/process.h>

#ifdef NATIVE
#include <ArduinoFake.h>
#include <cstdio>

#else
#include <Arduino.h>

std::unique_ptr<MainExecutor::Executor> executor = nullptr; // NOLINT

#endif

#if defined NATIVE
const auto LOOP_COUNT = 10;

void run(MainExecutor::Executor const *executor, const int loopCount) {
  // TODO(aruncs009@gmail.com): Add logging
  executor->setup();
  for (int i = 1; i <= loopCount; ++i) {
    executor->loop();
  }
}
#elif !UNIT_TEST

/**
 * Initial setup
 */
void setup() {
  // TODO(aruncs009@gmail.com): Add logging
  auto moistureLevelSensor = std::unique_ptr<Sensors::MoistureLevelSensor>(new Sensors::MoistureLevelSensor(1, 1));
  auto waterLevelSensor = std::unique_ptr<Sensors::WaterLevelSensor>(new Sensors::WaterLevelSensor(1, 1));
  // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
  std::list<Sensors::Sensor *> sensors = {moistureLevelSensor.get(), waterLevelSensor.get()};
  auto readSensors = std::unique_ptr<Sensors::ReadSensors>(new Sensors::ReadSensors(sensors));
  auto systemProcess = std::unique_ptr<System::Process>(new System::Process());
  auto dataProcess = std::unique_ptr<Data::Process>(new Data::Process());
  executor = std::unique_ptr<MainExecutor::Executor>(
      new MainExecutor::Executor(readSensors.get(), systemProcess.get(), dataProcess.get()));
  executor->setup();
}

/**
 * Main Loop
 */
void loop() {
  // TODO(aruncs009@gmail.com): Add logging
  executor->loop();
}

#endif

#if defined NATIVE && !defined UNIT_TEST

void configureArduinoFake() {
  fakeit::When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).AlwaysReturn();
  fakeit::When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
  fakeit::When(Method(ArduinoFake(), delay)).AlwaysReturn();
  fakeit::When(Method(ArduinoFake(), analogRead)).AlwaysReturn(123);
}

auto main() -> int {
  configureArduinoFake();
  // TODO(aruncs009@gmail.com): Add logging
  auto moistureLevelSensor = std::unique_ptr<Sensors::MoistureLevelSensor>(new Sensors::MoistureLevelSensor(1, 1));
  auto waterLevelSensor = std::unique_ptr<Sensors::WaterLevelSensor>(new Sensors::WaterLevelSensor(1, 1));
  // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
  std::list<Sensors::Sensor *> sensors = {moistureLevelSensor.get(), waterLevelSensor.get()};
  auto readSensors = std::unique_ptr<Sensors::ReadSensors>(new Sensors::ReadSensors(sensors));
  auto systemProcess = std::unique_ptr<System::Process>(new System::Process());
  auto dataProcess = std::unique_ptr<Data::Process>(new Data::Process());
  auto executor = std::unique_ptr<MainExecutor::Executor>(
      new MainExecutor::Executor(readSensors.get(), systemProcess.get(), dataProcess.get()));
  run(executor.get(), LOOP_COUNT);
  return 0;
}

#endif
