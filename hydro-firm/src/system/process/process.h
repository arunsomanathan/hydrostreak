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

#ifndef SYSTEM_PROCESS_PROCESS_H
#define SYSTEM_PROCESS_PROCESS_H

#include <system/controller/controller.h>
#include <system/state/state.h>

namespace System
{

    class Process
    {

    private:
        static Process *process_;

        State *state;
        Controller *controller;

        /*
         * Constructor
         */
        explicit Process();

        /*
         * Handle Cool down state of the system..
         */
        void handleCoolDownState();

        /*
         * Handle Active state of the system.
         */
        void handleActiveState();

        /*
         * Handle Force watering cycle state of the system.
         */
        void forceWateringCycle();

        /*
         * Drain water from the Plant Container and set system to cool down state.
         * Also resets the watering cycle state.
         */
        void drainWater();

        /*
         * Fill water to the Plant Container and set system to watering cycle state.
         */
        void fillWater();

    public:
        /**
         * Process should not be cloneable.
         */
        Process(Process &other) = delete;
        /**
         * Process should not be assignable.
         */
        void operator=(const Process &) = delete;

        /**
         * Get singleton instance of Process class.
         */
        static Process *getInstance();

        /*
         * Run the system processes.
         */
        void run();
    };

    Process *Process::process_ = nullptr;

} // namespace System

#endif