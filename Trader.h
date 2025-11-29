#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Instrument.h"
#include "Trade.h"
#include <map>
#include <vector>
#include <string>

class Portfolio
{
private:
    double cashBalance;
    std::map<std::string, int> holdings;
    std::vector<Trade> tradeHistory;

public:
    Portfolio(double initialCash);

    void buyStock(Instrument *stock, int qty, double price);
    void sellStock(Instrument *stock, int qty, double price);

    double getCashBalance() const;
    double getPortfolioValue(const std::vector<Instrument *> &market) const;
    void recordTrade(const Trade &trade);
    int getHoldings(const std::string &symbol) const;

    void printHoldings() const;
    void printTradeHistory() const;
};

#endif
