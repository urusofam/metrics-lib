//
// Created by urus on 12.06.25.
//

#ifndef IMETRIC_H
#define IMETRIC_H
#include <iosfwd>
#include <memory>

class IMetric {
public:
    virtual ~IMetric() = default;
    virtual void write(std::ostream& os) const = 0;
    virtual void reset() = 0;
    virtual std::unique_ptr<IMetric> clone() const = 0;
};

#endif //IMETRIC_H
