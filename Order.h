#ifndef ORDER_H
#define ORDER_H

#include "Stock.h"
#include "Portfolio.h"
#include <string>

// --- Abstract Base Class ---
class Order
{
protected:
    Stock *stock;
    int quantity;
    double price;
    Portfolio *traderPortfolio; // Portfolio owning this order

public:
    Order(Stock *s, int q, double p, Portfolio *portfolio)
        : stock(s), quantity(q), price(p), traderPortfolio(portfolio) {}

    virtual std::string orderType() const = 0;

    Stock *getStock() const { return stock; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    Portfolio *getPortfolio() const { return traderPortfolio; }

    void reduceQuantity(int q) { quantity -= q; }
};

// --- Derived Classes ---

#endif
