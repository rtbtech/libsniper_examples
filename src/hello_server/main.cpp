/*
 * Copyright (c) 2020, RTBtech, Oleg Romanenko (oleg@romanenko.ro)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <csignal>
#include <gperftools/malloc_extension.h>
#include <sniper/event/Loop.h>
#include <sniper/event/Sig.h>
#include <sniper/event/Timer.h>
#include <sniper/log/log.h>
#include <sniper/std/check.h>
#include <sniper/threads/Stop.h>
#include "Server.h"

using namespace sniper;

void stop_signal(const event::loop_ptr& loop)
{
    log_warn("Stop signal. Exiting");
    threads::Stop::get().stop();
    loop->break_loop(ev::ALL);
}

static void sigsegv_handler(int sig)
{
    log_err("Error: signal {} ({})", strsignal(sig), sig);
    log_err("{}", stacktrace_to_string(boost::stacktrace::stacktrace()));
    exit(1);
}

int main(int argc, char** argv)
{
    log_info("hello_server: ({}, {} UTC)", __DATE__, __TIME__);

    auto loop = event::make_loop();
    if (!loop) {
        log_err("Main: cannot init event loop");
        return EXIT_FAILURE;
    }

    signal(SIGPIPE, SIG_IGN);
    signal(SIGSEGV, sigsegv_handler);
    signal(SIGABRT, sigsegv_handler);

    event::Sig sig_int(loop, SIGINT, stop_signal);
    event::Sig sig_term(loop, SIGTERM, stop_signal);

    log_info("hello_server starting...");

    Server server;

    event::TimerRepeat timer_tcmalloc(loop, 10s, [] { MallocExtension::instance()->ReleaseFreeMemory(); });

    log_info("hello_server started");
    loop->run();
    log_info("hello_server stopped");

    return EXIT_SUCCESS;
}
