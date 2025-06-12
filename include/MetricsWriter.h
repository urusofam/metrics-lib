//
// Created by urus on 12.06.25.
//

#ifndef METRICSWRITER_H
#define METRICSWRITER_H
#include <atomic>
#include <fstream>
#include <thread>
#include <iomanip>

#include "MetricsRegistry.h"


class MetricsWriter {
    MetricsRegistry& registry;
    std::chrono::seconds interval;
    std::atomic<bool> running;
    std::thread thread;
    std::ofstream file;
    void run();
public:
    MetricsWriter(MetricsRegistry& registry, std::chrono::seconds interval, const std::string &filepath);
    ~MetricsWriter();
};



#endif //METRICSWRITER_H
