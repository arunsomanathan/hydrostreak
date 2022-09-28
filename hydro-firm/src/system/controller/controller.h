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

#ifndef SYSTEM_CONTROLLER_CONTROLLER_H
#define SYSTEM_CONTROLLER_CONTROLLER_H

#include <system/state/state.h>

namespace System
{
    class Controller
    {

    private:
        static Controller *controller_;

        State *state;

        /*
         * Constructor.
         */
        explicit Controller();

    public:
        /**
         * Controller should not be cloneable.
         */
        Controller(Controller &other) = delete;
        /**
         * Controller should not be assignable.
         */
        void operator=(const Controller &) = delete;

        /**89
         * Get singleton instance of Controller class.
         */
        static Controller *getInstance();

        /*
         * Turn On Pump.
         */
        void turnOnPump();

        /*
         * Turn Off Pump.
         */
        void turnOffPump();

        /*
         * Close Valve.
         */
        void closeValve();

        /*
         * Open valve.
         */
        void openValve();
    };

      Controller *Controller::controller_ = nullptr;

}  // namespace System

#endif