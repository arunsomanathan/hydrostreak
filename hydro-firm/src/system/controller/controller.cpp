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
 * @since: 03-09-2022
 */

#include <system/controller/controller.h>
#include <Logger.h>

namespace System
{

    /**
     * Get singleton instance of Controller class.
     */
    auto Controller::getInstance() -> Controller *
    {
        if (controller_ == nullptr)
        {
            Controller::controller_ = new Controller();
        }
        return Controller::controller_;
    }

    /*
     * Constructor.
     */
    Controller::Controller()
    {
        this->state = State::getInstance();
    }

    /*
     * Turn On Pump.
     */
    void Controller::turnOnPump()
    {
        Logger::verbose("System>Controller","Turn on the pump if off");
        if (!state->isPumpOn())
        {
            Logger::notice("System>Controller","Turning on the pump");
        }
    }

    /*
     * Turn Off Pump.
     */
    void Controller::turnOffPump()
    {
        Logger::verbose("System>Controller","Turn off the pump if on");
        if (state->isPumpOn())
        {
            Logger::notice("System>Controller","Turning off the pump");
        }
    }

    /*
     * Close Valve.
     */
    void Controller::closeValve()
    {
        Logger::verbose("System>Controller","Close valve if open");
        if (!state->isValveClosed())
        {
            Logger::notice("System>Controller","Closing Valve");
        }
    }

    /*
     * Open valve.
     */
    void Controller::openValve()
    {
        Logger::verbose("System>Controller","Open valve if closed");
        if (state->isValveClosed())
        {
            Logger::notice("System>Controller","Opening Valve");
        }
    }
} // namespace System