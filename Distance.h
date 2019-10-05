#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "Logger.h"
class Distance
{
private:
    float v;
public:
    Distance(): v(0.0){}
    float value() const {return v;};
    void add(const float& speed);
    bool write(Logger& logger) const;
};



#endif /* DISTANCE_H_ */
