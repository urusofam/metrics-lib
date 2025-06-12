//
// Created by urus on 12.06.25.
//

#ifndef AVERAGEMETRIC_H
#define AVERAGEMETRIC_H
#include <atomic>
#include <string>

#include "IMetric.h"


class AverageMetric : public IMetric {
    std::string name;
    std::atomic<long double> sum;
    std::atomic<long long> count;
public:
    AverageMetric(const std::string &name);
    void write(std::ostream& os) const override;
    void reset() override;
    std::unique_ptr<IMetric> clone() const override;
    void add(long double value);
};



#endif //AVERAGEMETRIC_H
