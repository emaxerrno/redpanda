/*
 * Copyright 2022 Redpanda Data, Inc.
 *
 * Licensed as a Redpanda Enterprise file under the Redpanda Community
 * License (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * https://github.com/redpanda-data/redpanda/blob/master/licenses/rcl.md
 */

#pragma once

#include "cloud_storage/access_time_tracker.h"
#include "seastarx.h"

#include <seastar/core/future.hh>
#include <seastar/core/gate.hh>

#include <chrono>

namespace cloud_storage {
struct file_list_item {
    std::chrono::system_clock::time_point access_time;
    ss::sstring path;
    uint64_t size;
};
class recursive_directory_walker {
public:
    ss::future<> stop();

    // recursively walks start_dir, returns the total size of files in this
    // directory and a list of files sorted by access time from oldest to newest
    ss::future<std::pair<uint64_t, std::vector<file_list_item>>>
    walk(ss::sstring start_dir, const access_time_tracker& tracker);

private:
    ss::gate _gate;
};

} // namespace cloud_storage
