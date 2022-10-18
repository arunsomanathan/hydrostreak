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
 * @since: 02-10-2022
 */

#include "../test_data/test_process/mock-process.hpp"
#include "../test_sensors/mock-sensors.hpp"
#include "../test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include "../test_system/test_controller/mock-controller.hpp"
#include "../test_system/test_process/mock-process.hpp"
#include "../test_system/test_state/mock-state.hpp"
#include <ArduinoFake.h>
#include <executor/executor.hpp>
#include <gmock/gmock.h>
#include <memory>

#ifdef NATIVE
namespace {
using namespace fakeit; // NOLINT(google-build-using-namespace)
using ::testing::Exactly;

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(ExecutorTest, IsLoopWorking) {          // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  When(Method(ArduinoFake(), delay)).AlwaysReturn();
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockState(mockReadSensors);
  MockSystemController mockController(mockState);
  MockSystemProcess mockSystemProcess(mockController, mockState);
  MockDataProcess mockDataProcess;
  MainExecutor::Executor executor(mockReadSensors, mockSystemProcess, mockDataProcess);
  EXPECT_CALL(mockReadSensors, readAllSensors()).Times(Exactly(1));
  EXPECT_CALL(mockSystemProcess, run()).Times(Exactly(1));
  executor.loop();
  Verify(Method(ArduinoFake(), delay).Using(MainExecutor::DELAY)).Once();
}

TEST(ExecutorTest, IsSetupWorking) {         // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).AlwaysReturn();
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockState(mockReadSensors);
  MockSystemController mockController(mockState);
  MockSystemProcess mockSystemProcess(mockController, mockState);
  MockDataProcess mockDataProcess;
  MainExecutor::Executor executor(mockReadSensors, mockSystemProcess, mockDataProcess);
  EXPECT_CALL(mockReadSensors, readAllSensors()).Times(Exactly(0));
  EXPECT_CALL(mockSystemProcess, run()).Times(Exactly(0));
  executor.setup();
  Verify(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long)).Using(MainExecutor::BAUD_RATE)).Once();
}

} // namespace
#endif