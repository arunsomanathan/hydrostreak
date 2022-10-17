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

#ifndef TEST_EXECUTOR_MOCK_EXECUTOR_HPP
#define TEST_EXECUTOR_MOCK_EXECUTOR_HPP

#include <gmock/gmock.h>

#include "../test_data/test_process/mock-process.hpp"
#include "../test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include "../test_system/test_process/mock-process.hpp"
#include <executor/executor.hpp>

class MockExecutor : public MainExecutor::Executor // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
{
public:
  // NOLINTNEXTLINE
  MockExecutor(MockReadSensors *mockReadSensors, MockSystemProcess *mockSystemProcess, MockDataProcess *mockDataProcess)
      : MainExecutor::Executor(mockReadSensors, mockSystemProcess, mockDataProcess) {}
  // NOLINTNEXTLINE
  MOCK_METHOD(void, setup, (), (const, override));
  // NOLINTNEXTLINE
  MOCK_METHOD(void, loop, (), (const, override));
};

#endif