#ifndef STOCK_H
#define STOCK_H

#include "Instrument.h"
#include <vector>
#include <string>
#include <random>

class Stock : public Instrument
{
private:
    std::string symbol;
    double price;
    std::vector<double> history;

public:
    Stock(const std::string &sym, double initPrice);
    void updatePrice();
    double getPrice() const override;
    double getExpectedReturn() const override;
    std::string getSymbol() const override;
};

#endif
