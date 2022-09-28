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

#include <system/process/process.h>
#include <system/state/state.h>

#include <Logger.h>

namespace System
{

  /**
   * Get singleton instance of Process class.
   */
  auto Process::getInstance() -> Process *
  {
    if (process_ == nullptr)
    {
      Process::process_ = new Process();
    }
    return Process::process_;
  }

  /*
   * Constructor
   */
  Process::Process()
  {
    this->state = State::getInstance();
    this->controller = Controller::getInstance();
  }

  /*
   * Run the system processes.
   */
  void Process::run()
  {
    Logger::verbose("System>Process","Run system process");
    if (state->isCoolDownState())
    {
      Logger::verbose("System>Process","System in Cool Down State");
      handleCoolDownState();
    }
    else if (state->isActiveState())
    {
      Logger::verbose("System>Process","System in Active State");
      handleActiveState();
    }
    else
    {
      Logger::verbose("System>Process","System in Force Watering Cycle state");
      forceWateringCycle();
    }
    Logger::verbose("System>Process","Completed running system process");
  }

  /*
   * Handle Cool down state of the system..
   */
  void Process::handleCoolDownState()
  {
    if (state->isWaterLevelMin())
    {
      Logger::verbose("System>Process","Closing the valve since water level is at minimum");
      controller->closeValve();
    }
    else
    {
      Logger::notice("System>Process","Continue draining water since water level is not at minimum");
      drainWater();
    }
  }

  /*
   * Handle Active state of the system.
   */
  void Process::handleActiveState()
  {
    if (state->isWaterLevelMax())
    {
      Logger::notice("System>Process","Draining water since the water level is at max");
      drainWater();
    }
    else
    {
      if (state->isWaterLevelMin())
      {
        if (state->isMoistureLevelMin())
        {
          Logger::notice("System>Process","Filling the water since both Water level and moisture level at min");
          fillWater();
        }
        else
        {
          Logger::verbose("System>Process","Close the valve since water level is at minimum and moisture level not at minimum");
          controller->closeValve();
        }
      }
      else
      {
        Logger::warning("System>Process","Opening the valve since water level is not at min. System is now in a unexpected state");
        controller->openValve();
      }
    }
  }

  /*
   * Handle Force watering cycle state of the system.
   */
  void Process::forceWateringCycle()
  {
    Logger::verbose("System>Process","Forcing System into water cycle state after reaching maximum period without watering");
    if (state->isWaterLevelMax())
    {
      Logger::warning("System>Process","Unexpected state, water level full when forcing watering cycle");
      drainWater();
    }
    else
    {
      Logger::notice("System>Process","Forcing System into water cycling");
      fillWater();
    }
  }

  /*
   * Drain water from the Plant Container and set system to cool down state.
   * Also resets the watering cycle state.
   */
  void Process::drainWater()
  {
    Logger::verbose("System>Process","Draining water");

    controller->turnOffPump();
    controller->openValve();
    state->resetWateringCycleState();
    state->setCoolDownState();
  }

  /*
   * Fill water to the Plant Container and set system to watering cycle state.
   */
  void Process::fillWater()
  {
    Logger::verbose("System>Process","Filling water");

    controller->closeValve();

    controller->turnOnPump();

    state->setWateringCycleState();
  }
  }  // namespace System