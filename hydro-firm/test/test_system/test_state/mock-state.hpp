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

#ifndef TEST_SYSTEM_TEST_STATE_TEST_STATE_HPP
#define TEST_SYSTEM_TEST_STATE_TEST_STATE_HPP

#include "gmock/gmock.h"

#include <sensors/read-sensors/read-sensors.hpp>
#include <system/state/state.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
class MockSystemState : public System::State {
public:
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
  explicit MockSystemState(Sensors::ReadSensors &readSensors) : System::State(readSensors){};
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isWaterLevelMax, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isWaterLevelMin, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isMoistureLevelMin, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isCoolDownState, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isActiveState, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isWateringCycleState, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, setPumpOn, (bool state), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isPumpOn, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, setValveClosed, (bool state), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(bool, isValveClosed, (), (const, override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, setWateringCycleState, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, resetWateringCycleState, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, setCoolDownState, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, resetCoolDownState, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, setActiveState, (), (override));
  // NOLINTNEXTLINE(modernize-use-trailing-return-type)
  MOCK_METHOD(void, resetActiveState, (), (override));
};

#endif