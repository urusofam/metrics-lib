//
// Created by urus on 12.06.25.
//

#include "CounterMetric.h"

CounterMetric::CounterMetric(const std::string &name) : name(name), value(0) {}

void CounterMetric::write(std::ostream &os) const  {
    os << name << " " << value.load();
}

std::unique_ptr<IMetric> CounterMetric::clone() const  {
    auto cloned = std::make_unique<CounterMetric>(name);
    cloned->value = this->value.load();
    return cloned;
}


void CounterMetric::increment(const long long val) {
    value.fetch_add(val);
}

void CounterMetric::reset()  {
    value.store(0);
}




