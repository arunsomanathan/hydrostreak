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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 09-09-2022
 */

#include <system/process/process.hpp>

/*
 * Constructor
 */
System::Process::Process(System::Controller &controller, System::State &state)
    : controller(&controller), state(&state) {}

/*
 * Run the system processes.
 */
void System::Process::run() {
  if (state->isCoolDownState()) {
    this->handleCoolDownState();
  } else if (state->isActiveState()) {
    this->handleActiveState();
  } else {
    this->forceWateringCycle();
  }
}

/*
 * Handle Cool down state of the system..
 */
void System::Process::handleCoolDownState() {
  if (state->isWaterLevelMin()) {
    controller->closeValve();
  } else {
    drainWater();
  }
}

/*
 * Handle Active state of the system.
 */
void System::Process::handleActiveState() {
  if (state->isWaterLevelMax()) {
    drainWater();
  } else {
    if (state->isWaterLevelMin()) {
      if (state->isMoistureLevelMin()) {
        fillWater();
      } else {
        controller->closeValve();
      }
    } else if (!state->isWateringCycleState()) {
      controller->closeValve();
    }
  }
}

/*
 * Handle Force watering cycle state of the system.
 */
void System::Process::forceWateringCycle() {
  if (state->isWaterLevelMax()) {
    drainWater();
  } else {
    fillWater();
  }
}

/*
 * Drain water from the Plant Container and set system to cool down state.
 * Also resets the watering cycle state.
 */
void System::Process::drainWater() {
  controller->turnOffPump();
  controller->openValve();
  state->resetWateringCycleState();
  state->setCoolDownState();
}

/*
 * Fill water to the Plant Container and set system to watering cycle state.
 */
void System::Process::fillWater() {
  controller->closeValve();

  controller->turnOnPump();

  state->setWateringCycleState();
}
