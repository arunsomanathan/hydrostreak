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

#include "executor/executor.hpp"
#include <data/process/process.hpp>
#include <list>
#include <memory>
#include <sensors/moisture-level/moisture-level.hpp>
#include <sensors/read-sensors/read-sensors.hpp>
#include <sensors/sensor.hpp>
#include <sensors/water-level/water-level.hpp>
#include <system/process/process.hpp>

#ifdef NATIVE
#include <ArduinoFake.h>
#include <cstdio>

#else
#include <Arduino.h>

std::unique_ptr<MainExecutor::Executor> executor = nullptr; // NOLINT

#endif

#if defined NATIVE
const auto LOOP_COUNT = 10;

void run(MainExecutor::Executor const &executor, const int loopCount) {
  // TODO(aruncs009@gmail.com): Add logging
  executor.setup();
  for (int i = 1; i <= loopCount; ++i) {
    executor.loop();
  }
}
#elif !UNIT_TEST

/**
 * Initial setup
 */
void setup() {
  // TODO(aruncs009@gmail.com): Add logging
  Sensors::MoistureLevelSensor moistureLevelSensor(1, 1);
  Sensors::WaterLevelSensor waterLevelSensor(1, 1);
  // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
  std::list<Sensors::Sensor *> sensors = {&moistureLevelSensor, &waterLevelSensor};
  Sensors::ReadSensors readSensors(sensors);
  System::State state(readSensors);
  System::Controller controller(state);
  System::Process systemProcess(controller, state);
  Data::Process dataProcess;
  executor =
      std::unique_ptr<MainExecutor::Executor>(new MainExecutor::Executor(readSensors, systemProcess, dataProcess));
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
  Sensors::MoistureLevelSensor moistureLevelSensor(1, 1);
  Sensors::WaterLevelSensor waterLevelSensor(1, 1);
  // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
  std::list<Sensors::Sensor *> sensors = {&moistureLevelSensor, &waterLevelSensor};
  Sensors::ReadSensors readSensors(sensors);

  System::State state(readSensors);
  System::Controller controller(state);
  System::Process systemProcess(controller, state);
  Data::Process dataProcess;
  MainExecutor::Executor executor(readSensors, systemProcess, dataProcess);
  run(executor, LOOP_COUNT);
  return 0;
}

#endif
