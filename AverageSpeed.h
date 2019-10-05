
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
    bool write(Logger& logger) const;
};



#endif /* AVERAGESPEED_H_ */
