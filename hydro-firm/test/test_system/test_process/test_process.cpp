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

#include "../../test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include "../test_controller/mock-controller.hpp"
#include "../test_state/mock-state.hpp"

#include <gmock/gmock.h>
#include <system/process/process.hpp>

#ifdef NATIVE
namespace {

using ::testing::Exactly;
using ::testing::Return;
using ::testing::StrictMock;

TEST(SystemProcessTest, InCoolDownStateAndWaterLevelMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};               // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(true));
  EXPECT_CALL(mockController, closeValve()).Times(Exactly(1));
  process.run();
}

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(SystemProcessTest, InCoolDownStateAndWaterLevelNotMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                  // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(false));
  EXPECT_CALL(mockController, turnOffPump()).Times(Exactly(1));
  EXPECT_CALL(mockController, openValve()).Times(Exactly(1));
  EXPECT_CALL(mockState, resetWateringCycleState()).Times(Exactly(1));
  EXPECT_CALL(mockState, setCoolDownState()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, InActiveStateAndWaterLevelMax) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};             // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(true));
  EXPECT_CALL(mockController, turnOffPump()).Times(Exactly(1));
  EXPECT_CALL(mockController, openValve()).Times(Exactly(1));
  EXPECT_CALL(mockState, resetWateringCycleState()).Times(Exactly(1));
  EXPECT_CALL(mockState, setCoolDownState()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, InActiveStateAndWaterLevelNotMaxAndNotMinAndNotInWateringCycleState) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWateringCycleState()).WillOnce(Return(false));
  EXPECT_CALL(mockController, closeValve()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, InActiveStateAndWaterLevelNotMaxAndNotMinAndInWateringCycleState) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWateringCycleState()).WillOnce(Return(true));
  process.run();
}

TEST(SystemProcessTest, InActiveStateAndWaterLevelMinAndMositureLevelNotMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isMoistureLevelMin()).WillOnce(Return(false));
  EXPECT_CALL(mockController, closeValve()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, InActiveStateAndWaterLevelMinAndMositureLevelMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                                // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMin()).WillOnce(Return(true));
  EXPECT_CALL(mockState, isMoistureLevelMin()).WillOnce(Return(true));
  EXPECT_CALL(mockController, closeValve()).Times(Exactly(1));
  EXPECT_CALL(mockController, turnOnPump()).Times(Exactly(1));
  EXPECT_CALL(mockState, setWateringCycleState()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, NotActiveStateAndNotCoolDownStateAndWaterLevelMax) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                                 // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(true));
  EXPECT_CALL(mockController, turnOffPump()).Times(Exactly(1));
  EXPECT_CALL(mockController, openValve()).Times(Exactly(1));
  EXPECT_CALL(mockState, resetWateringCycleState()).Times(Exactly(1));
  EXPECT_CALL(mockState, setCoolDownState()).Times(Exactly(1));
  process.run();
}

TEST(SystemProcessTest, NotActiveStateAndNotCoolDownStateAndWaterLevelNotMax) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  StrictMock<MockReadSensors> mockReadSensors(sensors);
  StrictMock<MockSystemState> mockState(mockReadSensors);
  StrictMock<MockSystemController> mockController(mockState);
  System::Process process(mockController, mockState); // NOLINT
  EXPECT_CALL(mockState, isCoolDownState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isActiveState()).WillOnce(Return(false));
  EXPECT_CALL(mockState, isWaterLevelMax()).WillOnce(Return(false));
  EXPECT_CALL(mockController, turnOnPump()).Times(Exactly(1));
  EXPECT_CALL(mockController, closeValve()).Times(Exactly(1));
  EXPECT_CALL(mockState, setWateringCycleState()).Times(Exactly(1));
  process.run();
}

} // namespace
#endif