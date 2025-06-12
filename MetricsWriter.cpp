//
// Created by urus on 12.06.25.
//

#include "MetricsWriter.h"

MetricsWriter::MetricsWriter(MetricsRegistry &registry, std::chrono::seconds interval, const std::string &filepath) : registry(registry), interval(interval), running(true) {
    file.open(filepath,std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filepath);
    }

    thread = std::thread(&MetricsWriter::run, this);
}

MetricsWriter::~MetricsWriter() {
    running.store(false);
    thread.join();
    file.close();
}

void MetricsWriter::run() {
    while (running.load()) {
        std::this_thread::sleep_for(interval);
        auto metrics = registry.snapshot();
        if (metrics.empty()) {
            continue;
        }

        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = std::chrono::system_clock::to_time_t(now);
        std::tm time = *std::localtime(&timer);

        file << std::put_time(&time, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count() << " ";

        for (const auto&[name, metric] : metrics) {
            metric->write(file);
            file << " ";
        }
        file << "\n";
    }
}

