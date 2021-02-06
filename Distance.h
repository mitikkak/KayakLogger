#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "Logger.h"
class Distance
{
private:
    double v;
public:
    Distance(): v(0.0){}
    double value() const {return v;};
    void add(const double& speed, unsigned const measPeriodMillisecs);
    bool write(Logger& logger) const;
};



#endif /* DISTANCE_H_ */
