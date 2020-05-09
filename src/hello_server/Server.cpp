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

#include <sniper/event/Loop.h>
#include <sniper/event/Timer.h>
#include <sniper/http/Server.h>
#include <sniper/log/log.h>
#include <sniper/std/check.h>
#include <sniper/threads/Stop.h>
#include "Server.h"

namespace sniper {

Server::Server()
{
    for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
        _workers.emplace_back(&Server::worker_noexcept, this, i);
}

Server::~Server()
{
    for (auto& w : _workers)
        if (w.joinable())
            w.join();
}

void Server::worker_noexcept(unsigned int thread_num) noexcept
{
    try {
        worker(thread_num);
    }
    catch (std::exception& e) {
        log_err(e.what());
    }
    catch (...) {
        log_err("[Server] non std::exception occured");
    }

    threads::Stop::get().stop();
}

void Server::worker(unsigned thread_num)
{
    auto loop = event::make_loop();
    check(loop, "[Server] cannot init event loop");

    auto config = http::server::make_config();
    config->normalize = true;
    config->add_server_header = true;
    config->add_date_header = true;

    http::Server server(loop, config);
    check(server.bind("", 8080));

    server.set_cb([&, this](const auto& conn, const auto& req, const auto& resp) {
        resp->code = http::ResponseStatus::OK;
        resp->add_header_nocopy("Access-Control-Allow-Origin: *\r\n");
        conn->send(resp);
    });

    event::TimerRepeat timer_stop(loop, 1s, [&loop] {
        if (threads::Stop::get().is_stopped())
            loop->break_loop(ev::ALL);
    });

    loop->run();
}

} // namespace sniper
