//
// Created by urus on 12.06.25.
//

#ifndef METRICSREGISTRY_H
#define METRICSREGISTRY_H
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "IMetric.h"


class MetricsRegistry {
    std::unordered_map<std::string, std::unique_ptr<IMetric>> metrics;
    std::mutex mutex;
public:
    void registerMetric(const std::string &name, std::unique_ptr<IMetric> metric);
    template<typename T>
    T *getMetric(const std::string &name) {
        std::lock_guard lock(mutex);
        const auto it = metrics.find(name);
        if (it == metrics.end()) {
            return nullptr;
        }
        return dynamic_cast<T*>(it->second.get());
    }
    std::unordered_map<std::string, std::unique_ptr<IMetric>> snapshot();
};



#endif //METRICSREGISTRY_H
