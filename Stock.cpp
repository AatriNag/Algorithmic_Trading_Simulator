#include "Stock.h"
#include <cmath>

Stock::Stock(const std::string &sym, double initPrice)
    : symbol(sym), price(initPrice)
{
    history.push_back(initPrice);
}

void Stock::updatePrice()
{
    static std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.95, 1.05);
    price *= dist(gen);
    history.push_back(price);
}

double Stock::getPrice() const
{
    return price;
}

double Stock::getExpectedReturn() const
{
    if (history.size() < 2)
        return 0.0;
    return (history.back() - history.front()) / history.front();
}

std::string Stock::getSymbol() const
{
    return symbol;
}
