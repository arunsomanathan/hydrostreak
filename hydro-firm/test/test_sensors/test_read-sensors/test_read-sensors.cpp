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

#include "../mock-sensors.h"
#include <ArduinoFake.h>
#include <gmock/gmock.h>
#include <memory>
#include <sensors/read-sensors/read-sensors.h>

#ifdef NATIVE
namespace {
using ::testing::Exactly;
using ::testing::Return;

auto const READ_PIN = 1;
auto const POWER_PIN = 2;
auto const DEFAULT_READ_VALUE = 123;
std::string const FIRST_SENSOR_TYPE = "First Sensor";
std::string const SECOND_SENSOR_TYPE = "Second Sensor";

//  cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(ReadSensorsTest, IsReadSingleSensorsWorking) { // NOLINT

  auto const mockSensor = std::unique_ptr<MockSensor>(new MockSensor(FIRST_SENSOR_TYPE, READ_PIN, POWER_PIN));
  std::list<Sensors::Sensor *> sensors = {mockSensor.get()}; // NOLINT(cppcoreguidelines-init-variables)
  auto readSensors = std::unique_ptr<Sensors::ReadSensors>(new Sensors::ReadSensors(sensors));
  EXPECT_CALL(*mockSensor.get(), readSensor()).Times(Exactly(1));
  EXPECT_CALL(*mockSensor.get(), getType()).Times(Exactly(1)).WillOnce(Return(FIRST_SENSOR_TYPE));
  EXPECT_CALL(*mockSensor.get(), getReading()).Times(1).WillOnce(Return(DEFAULT_READ_VALUE));
  readSensors->readAllSensors();
  EXPECT_EQ(readSensors->getAllSensorReading().size(), 1) << "Size of Sensor reading map is incorrect "; // NOLINT
  EXPECT_EQ(readSensors->getAllSensorReading()[FIRST_SENSOR_TYPE], DEFAULT_READ_VALUE)
      << "Incorect sensor reading"; // NOLINT
}

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(ReadSensorsTest, IsReadAllSensorsWorking) { // NOLINT
  auto const mockFirstSensor = std::unique_ptr<MockSensor>(new MockSensor(FIRST_SENSOR_TYPE, READ_PIN, POWER_PIN));
  auto const mockSecondSensor = std::unique_ptr<MockSensor>(new MockSensor(SECOND_SENSOR_TYPE, READ_PIN, POWER_PIN));
  // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
  std::list<Sensors::Sensor *> sensors = {mockFirstSensor.get(), mockSecondSensor.get()};
  auto readSensors = std::unique_ptr<Sensors::ReadSensors>(new Sensors::ReadSensors(sensors));
  EXPECT_CALL(*mockFirstSensor.get(), readSensor()).Times(Exactly(1));
  EXPECT_CALL(*mockFirstSensor.get(), getType()).Times(Exactly(1)).WillOnce(Return(FIRST_SENSOR_TYPE));
  EXPECT_CALL(*mockFirstSensor.get(), getReading()).Times(1).WillOnce(Return(DEFAULT_READ_VALUE));
  EXPECT_CALL(*mockSecondSensor.get(), readSensor()).Times(Exactly(1));
  EXPECT_CALL(*mockSecondSensor.get(), getType()).Times(Exactly(1)).WillOnce(Return(SECOND_SENSOR_TYPE));
  EXPECT_CALL(*mockSecondSensor.get(), getReading()).Times(1).WillOnce(Return(DEFAULT_READ_VALUE));
  readSensors->readAllSensors();
  EXPECT_EQ(readSensors->getAllSensorReading().size(), 2) << "Size of Sensor reading map is incorrect "; // NOLINT
  EXPECT_EQ(readSensors->getAllSensorReading()[FIRST_SENSOR_TYPE], DEFAULT_READ_VALUE)
      << "Incorect sensor reading"; // NOLINT
  EXPECT_EQ(readSensors->getAllSensorReading()[SECOND_SENSOR_TYPE], DEFAULT_READ_VALUE)
      << "Incorect sensor reading"; // NOLINT
}

//  cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST(ReadSensorsTest, EmptySensorList) {     // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  auto readSensors = std::unique_ptr<Sensors::ReadSensors>(new Sensors::ReadSensors(sensors));
  readSensors->readAllSensors();
  EXPECT_EQ(readSensors->getAllSensorReading().size(), 0) << "Size of Sensor reading map is incorrect "; // NOLINT
}

} // namespace
#endif