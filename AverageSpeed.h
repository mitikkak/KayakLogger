
#ifndef AVERAGESPEED_H_
#define AVERAGESPEED_H_

class AverageSpeed
{
private:
    float total;
    unsigned int samples;
public:
    AverageSpeed(): total(0), samples(0) {}
    float value() const;
    void add(const float& speed);
    StatusIndicator::Status write(Logger& logger, float& val) const;
};



#endif /* AVERAGESPEED_H_ */
