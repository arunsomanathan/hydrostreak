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
 * @since: 17-10-2022
 */

#include "../../test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include "../../test_system/test_state/mock-state.hpp"
#include <gmock/gmock.h>
#include <system/controller/controller.hpp>
#include <tuple>

#ifdef NATIVE

namespace {

using ::testing::Exactly;
using ::testing::Return;

TEST(SystemControllerTest, IsTurnOnPumpWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};      // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockSystemState(mockReadSensors);
  System::Controller controller(mockSystemState);
  EXPECT_CALL(mockSystemState, isPumpOn()).Times(Exactly(1));
  controller.turnOnPump();
}

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(SystemControllerTest, IsTurnOffPumpWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};       // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockSystemState(mockReadSensors);
  System::Controller controller(mockSystemState);
  EXPECT_CALL(mockSystemState, isPumpOn()).Times(Exactly(1));
  controller.turnOffPump();
}

TEST(SystemControllerTest, IsCloseValveWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};      // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockSystemState(mockReadSensors);
  System::Controller controller(mockSystemState);
  EXPECT_CALL(mockSystemState, isValveClosed()).Times(Exactly(1));
  controller.closeValve();
}

TEST(SystemControllerTest, IsOpenValveWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};     // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockSystemState(mockReadSensors);
  System::Controller controller(mockSystemState);
  EXPECT_CALL(mockSystemState, isValveClosed()).Times(Exactly(1));
  controller.openValve();
}

} // namespace
#endif