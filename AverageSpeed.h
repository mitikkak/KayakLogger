
#ifndef AVERAGESPEED_H_
#define AVERAGESPEED_H_

class AverageSpeed
{
private:
    double total;
    unsigned int samples;
public:
    AverageSpeed(): total(0), samples(0) {}
    double value() const;
    void add(const double& speed);
    bool write(Logger& logger) const;
};



#endif /* AVERAGESPEED_H_ */
