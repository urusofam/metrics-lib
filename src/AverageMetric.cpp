//
// Created by urus on 12.06.25.
//

#include "../include/AverageMetric.h"

AverageMetric::AverageMetric(const std::string &name) : name(name), sum(0), count(0) {}

void AverageMetric::write(std::ostream &os) const  {
    long double avg = (count == 0) ? 0 : sum.load() / count.load();
    os << name << " " << avg;
}

void AverageMetric::reset()  {
    sum.store(0);
    count.store(0);
}

std::unique_ptr<IMetric> AverageMetric::clone() const  {
    auto cloned = std::make_unique<AverageMetric>(name);
    cloned->sum = this->sum.load();
    cloned->count = this->count.load();
    return cloned;
}

void AverageMetric::add(long double value) {
    sum.fetch_add(value);
    count.fetch_add(1);
}
