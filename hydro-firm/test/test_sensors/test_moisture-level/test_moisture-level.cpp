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
 * @since: 09-10-2022
 */

#include <ArduinoFake.h>
#include <gtest/gtest.h>
#include <sensors/moisture-level/moisture-level.h>

#ifdef NATIVE

using namespace fakeit; // NOLINT(google-build-using-namespace)

namespace {
const uint8_t READ_PIN = A0;
const uint8_t POWER_PIN = A1;
const int DEFAULT_DELAY = 10;
const int EXPECTED_READING = 123;

class MoistureLevelSensorTest : public ::testing::Test {
protected:
  void SetUp() override { ArduinoFakeReset(); } // NOLINT(readability-convert-member-functions-to-static)
};

// cppcheck-suppress [syntaxError,unmatchedSuppression]
TEST_F(MoistureLevelSensorTest, IsConstructorWorking) { // NOLINT
  Sensors::MoistureLevelSensor moistureLevelSensor(READ_PIN, POWER_PIN);
  EXPECT_EQ(moistureLevelSensor.getType(), Sensors::MOISTURE_LEVEL_SENSOR)
      << "Constructor initialization of member variable for Moisture Level Sensor: type not woring"; // NOLINT
  EXPECT_EQ(moistureLevelSensor.getReading(), 0)
      << "Constructor initialization of member variable for Moisture Level Sensor: reading not woring"; // NOLINT
}

TEST_F(MoistureLevelSensorTest, IsReadMoistureLevelSensorWorking) { // NOLINT
  When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
  When(Method(ArduinoFake(), delay)).AlwaysReturn();
  When(Method(ArduinoFake(), analogRead)).AlwaysReturn(EXPECTED_READING);
  const uint8_t readPin = A0;
  const uint8_t powerPin = A1;
  Sensors::MoistureLevelSensor moistureLevelSensor(READ_PIN, POWER_PIN);
  moistureLevelSensor.readSensor();
  EXPECT_EQ(moistureLevelSensor.getReading(), EXPECTED_READING)
      << "Sensor reading is different from the expected reading"; // NOLINT
  Verify(Method(ArduinoFake(), digitalWrite).Using(POWER_PIN, HIGH)).Once();
  Verify(Method(ArduinoFake(), delay).Using(DEFAULT_DELAY)).Once();
  Verify(Method(ArduinoFake(), analogRead).Using(READ_PIN)).Once();
  Verify(Method(ArduinoFake(), digitalWrite).Using(POWER_PIN, LOW)).Once();
}

} // namespace
#endif