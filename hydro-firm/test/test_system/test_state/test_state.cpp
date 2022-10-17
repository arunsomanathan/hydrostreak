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
 * @since: 14-10-2022
 */

#include "../../test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include <gmock/gmock.h>
#include <sensors/moisture-level/moisture-level.hpp>
#include <sensors/water-level/water-level.hpp>
#include <system/state/state.hpp>
#include <tuple>

#ifdef NATIVE

namespace {

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

class SystemStateWaterLevelMaxTest : public testing::TestWithParam<std::tuple<int, bool>> {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables, modernize-use-trailing-return-type)
INSTANTIATE_TEST_SUITE_P(WaterLevelValues, SystemStateWaterLevelMaxTest,
                         testing::Values(std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED, true),
                                         std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED + 1, true),
                                         std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED - 1, false),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED + 1, false),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED, false),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED - 1, false)));

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST_P(SystemStateWaterLevelMaxTest, IsWaterLevelMax) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};            // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  EXPECT_CALL(mockReadSensors, getSensorReading(Sensors::WATER_LEVEL_SENSOR)).WillOnce(Return(std::get<0>(GetParam())));
  EXPECT_EQ(state.isWaterLevelMax(), std::get<1>(GetParam())) << "Wrong water level max status"; // NOLINT
}

class SystemStateWaterLevelMinTest : public testing::TestWithParam<std::tuple<int, bool>> {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables, modernize-use-trailing-return-type)
INSTANTIATE_TEST_SUITE_P(WaterLevelValues, SystemStateWaterLevelMinTest,
                         testing::Values(std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED, false),
                                         std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED + 1, false),
                                         std::make_tuple(System::WATER_LEVEL_MAX_ALLOWED - 1, false),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED + 1, false),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED, true),
                                         std::make_tuple(System::WATER_LEVEL_MIN_ALLOWED - 1, true)));

TEST_P(SystemStateWaterLevelMinTest, IsWaterLevelMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};            // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  EXPECT_CALL(mockReadSensors, getSensorReading(Sensors::WATER_LEVEL_SENSOR)).WillOnce(Return(std::get<0>(GetParam())));
  EXPECT_EQ(state.isWaterLevelMin(), std::get<1>(GetParam())) << "Wrong water level min status"; // NOLINT
}

class SystemStateMoistureLevelMinTest : public testing::TestWithParam<std::tuple<int, bool>> {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,modernize-use-trailing-return-type)
INSTANTIATE_TEST_SUITE_P(WaterLevelValues, SystemStateMoistureLevelMinTest,
                         testing::Values(std::make_tuple(System::MOISTURE_LEVEL_MIN_ALLOWED, true),
                                         std::make_tuple(System::MOISTURE_LEVEL_MIN_ALLOWED + 1, false),
                                         std::make_tuple(System::MOISTURE_LEVEL_MIN_ALLOWED - 1, true)));

TEST_P(SystemStateMoistureLevelMinTest, IsMoistureLevelMin) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                  // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  EXPECT_CALL(mockReadSensors, getSensorReading(Sensors::MOISTURE_LEVEL_SENSOR))
      .WillOnce(Return(std::get<0>(GetParam())));
  EXPECT_EQ(state.isMoistureLevelMin(), std::get<1>(GetParam())) << "Wrong moisture level min status"; // NOLINT
}

TEST(SystemStateCoolDownStateTest, IsSetCoolDownStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                    // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.setCoolDownState();
  EXPECT_EQ(state.isCoolDownState(), true) << "Wrong status for cool down state after set"; // NOLINT
}

TEST(SystemStateCoolDownStateTest, IsResetCoolDownStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                      // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.resetCoolDownState();
  EXPECT_EQ(state.isCoolDownState(), false) << "Wrong status for cool down state after cool down reset"; // NOLINT
  EXPECT_EQ(state.isActiveState(), true) << "Wrong status for cool down state after cool down reset";    // NOLINT
}

TEST(SystemStateActiveStateTest, IsSetActiveStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.setActiveState();
  EXPECT_EQ(state.isActiveState(), true) << "Wrong status for active state"; // NOLINT
}

TEST(SystemStateActiveStateTest, IsResetActiveStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                  // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.resetActiveState();
  EXPECT_EQ(state.isActiveState(), false) << "Wrong status for active state after active state reset";  // NOLINT
  EXPECT_EQ(state.isCoolDownState(), true) << "Wrong status for active state after active state reset"; // NOLINT
}

TEST(SystemStateWateringCycleStateTest, IsSetWateringCycleStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                              // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.setWateringCycleState();
  EXPECT_EQ(state.isWateringCycleState(), true) << "Wrong status for watering cycle state after set"; // NOLINT
}

TEST(SystemStateCoolDownStateTest, IsResetWateringCycleStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                           // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.resetWateringCycleState();
  EXPECT_EQ(state.isWateringCycleState(), false) << "Wrong status for watering cycle state after reset"; // NOLINT
}

class SystemStatePumpStateTest : public testing::TestWithParam<bool> {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,modernize-use-trailing-return-type)
INSTANTIATE_TEST_SUITE_P(PumpValues, SystemStatePumpStateTest, testing::Values(true, false));

TEST_P(SystemStatePumpStateTest, IsSetPumpStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};              // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.setPumpOn(GetParam());
  EXPECT_EQ(state.isPumpOn(), GetParam()) << "Wrong value for pump state"; // NOLINT
}

class SystemStateValveStateTest : public testing::TestWithParam<bool> {};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,modernize-use-trailing-return-type)
INSTANTIATE_TEST_SUITE_P(ValveValues, SystemStateValveStateTest, testing::Values(true, false));

TEST_P(SystemStateValveStateTest, IsSetValveStateWorking) { // NOLINT
  std::list<Sensors::Sensor *> sensors = {};                // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  System::State state(mockReadSensors);
  state.setValveClosed(GetParam());
  EXPECT_EQ(state.isValveClosed(), GetParam()) << "Wrong value for valve state"; // NOLINT
}

} // namespace
#endif