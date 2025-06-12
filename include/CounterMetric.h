//
// Created by urus on 12.06.25.
//

#ifndef COUNTERMETRIC_H
#define COUNTERMETRIC_H
#include <atomic>
#include <string>

#include "IMetric.h"


class CounterMetric : public IMetric {
    std::string name;
    std::atomic<long long> value;
public:
    CounterMetric(const std::string &name);
    void write(std::ostream& os) const override;
    void reset() override;
    std::unique_ptr<IMetric> clone() const override;
    void increment(long long val = 1);
};



#endif //COUNTERMETRIC_H
