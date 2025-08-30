#ifndef TRADE_H
#define TRADE_H

#include <string>

struct Trade
{
    std::string stockSymbol;
    int quantity;
    double price;

    Trade(const std::string &sym, int qty, double pr)
        : stockSymbol(sym), quantity(qty), price(pr) {}
};

#endif
