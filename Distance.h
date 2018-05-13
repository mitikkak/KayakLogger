#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "StatusIndicator.h"
#include "Logger.h"
class Distance
{
private:
    float v;
public:
    Distance(): v(0.0){}
    float value() const {return v;};
    void add(const float& speed);
    StatusIndicator::Status write(Logger& logger) const;
};



#endif /* DISTANCE_H_ */
