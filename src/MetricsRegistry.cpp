//
// Created by urus on 12.06.25.
//

#include "../include/MetricsRegistry.h"

void MetricsRegistry::registerMetric(const std::string &name, std::unique_ptr<IMetric> metric) {
    std::lock_guard lock(mutex);
    metrics[name] = std::move(metric);
}

std::unordered_map<std::string, std::unique_ptr<IMetric> > MetricsRegistry::snapshot() {
    std::lock_guard lock(mutex);
    std::unordered_map<std::string, std::unique_ptr<IMetric> > newMetrics;

    for (auto &[name, metric] : metrics) {
        newMetrics[name] = metric->clone();
        metric->reset();
    }
    return newMetrics;
}

