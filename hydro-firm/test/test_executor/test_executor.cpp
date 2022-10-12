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

#include "../test_data/test_process/mock-process.h"
#include "../test_sensors/mock-sensors.h"
#include "../test_sensors/test_read-sensors/mock-read-sensors.h"
#include "../test_system/test_process/mock-process.h"
#include <ArduinoFake.h>
#include <executor/executor.h>
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
  auto const mockReadSensors = std::unique_ptr<MockReadSensors>(new MockReadSensors(sensors));
  auto const mockSystemProcess = std::unique_ptr<MockSystemProcess>(new MockSystemProcess());
  auto const mockDataProcess = std::unique_ptr<MockDataProcess>(new MockDataProcess());
  auto executor = new MainExecutor::Executor(mockReadSensors.get(), mockSystemProcess.get(), mockDataProcess.get());
  EXPECT_CALL(*mockReadSensors.get(), readAllSensors()).Times(Exactly(1));
  EXPECT_CALL(*mockSystemProcess.get(), run()).Times(Exactly(1));
  executor->loop();
  Verify(Method(ArduinoFake(), delay).Using(MainExecutor::DELAY)).Once();
}

TEST(ExecutorTest, IsSetupWorking) {         // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).AlwaysReturn();
  auto const mockReadSensors = std::unique_ptr<MockReadSensors>(new MockReadSensors(sensors));
  auto const mockSystemProcess = std::unique_ptr<MockSystemProcess>(new MockSystemProcess());
  auto const mockDataProcess = std::unique_ptr<MockDataProcess>(new MockDataProcess());
  auto executor = new MainExecutor::Executor(mockReadSensors.get(), mockSystemProcess.get(), mockDataProcess.get());
  EXPECT_CALL(*mockReadSensors.get(), readAllSensors()).Times(Exactly(0));
  EXPECT_CALL(*mockSystemProcess.get(), run()).Times(Exactly(0));
  executor->setup();
  Verify(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long)).Using(MainExecutor::BAUD_RATE)).Once();
}

TEST(ExecutorTest, ExceptionOnNullReadSensor) { // NOLINT
  auto const mockSystemProcess = std::unique_ptr<MockSystemProcess>(new MockSystemProcess());
  auto const mockDataProcess = std::unique_ptr<MockDataProcess>(new MockDataProcess());
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(new MainExecutor::Executor(nullptr, mockSystemProcess.get(), mockDataProcess.get()),
               std::invalid_argument);
}

TEST(ExecutorTest, ExceptionOnNullSystemProcess) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};       // NOLINT(cppcoreguidelines-init-variables)
  auto const mockReadSensors = std::unique_ptr<MockReadSensors>(new MockReadSensors(sensors));
  auto const mockDataProcess = std::unique_ptr<MockDataProcess>(new MockDataProcess());
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(new MainExecutor::Executor(mockReadSensors.get(), nullptr, mockDataProcess.get()),
               std::invalid_argument);
}

TEST(ExecutorTest, ExceptionOnNullDataProcess) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};     // NOLINT(cppcoreguidelines-init-variables)
  auto const mockReadSensors = std::unique_ptr<MockReadSensors>(new MockReadSensors(sensors));
  auto const mockSystemProcess = std::unique_ptr<MockSystemProcess>(new MockSystemProcess());
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(new MainExecutor::Executor(mockReadSensors.get(), mockSystemProcess.get(), nullptr),
               std::invalid_argument);
}

TEST(ExecutorTest, ExceptionOnNullReadSensorAndSystemProcess) { // NOLINT
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
  EXPECT_THROW(new MainExecutor::Executor(nullptr, nullptr, nullptr), std::invalid_argument);
}
} // namespace
#endif