#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <string>
class Instrument
{
public:
    virtual double getPrice() const = 0;
    virtual double getExpectedReturn() const = 0;
    virtual std::string getSymbol() const = 0;
    virtual ~Instrument() {}
};

#endif
