/*
 * Copyright (c) 2017 Jason Lowe-Power
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "tutorial/my_goodbye_object.hh"

#include "base/trace.hh"
#include "debug/MyHelloExample.hh"
#include "sim/sim_exit.hh"

namespace gem5
{

MyGoodbyeObject::MyGoodbyeObject(const Params &params) :
    SimObject(params), event([this]{ processEvent(); }, name() + ".event"),
    bandwidth(params.write_bandwidth), bufferSize(params.buffer_size)
{
    buffer = new char[bufferSize]();
    DPRINTF(MyHelloExample, "Created the goodbye object\n");
}

MyGoodbyeObject::~MyGoodbyeObject()
{
    delete[] buffer;
}

void
MyGoodbyeObject::processEvent()
{
    DPRINTF(MyHelloExample, "Processing the event!\n");

    // Actually do the "work" of the event
    fillBuffer();
}

void
MyGoodbyeObject::sayGoodbye(std::string other_name)
{
    DPRINTF(MyHelloExample, "Saying goodbye to %s\n", other_name);

    message = "Goodbye " + other_name + "!! ";

    // Kick off the the first buffer fill. If it can't fill the whole buffer
    // because of a limited bandwidth, then this function will schedule another
    // event to finish the fill
    fillBuffer();
}

void
MyGoodbyeObject::fillBuffer()
{
    // Check things are OK (There better be a message)

    // Copy from the message to the buffer per byte.
    // Make sure not to use too much bandwidth!

    if (bufferUsed < bufferSize - 1) {
        // Wait for the next copy for as long as it would have taken

    } else {
        DPRINTF(MyHelloExample, "Goodbye done copying!\n");
        // Exit the simulation when we're done.
        // Be sure to take into account the time for the last bytes
    }
}

} // namespace gem5
