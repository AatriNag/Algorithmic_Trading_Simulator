#include "Portfolio.h"
#include <iostream>

Portfolio::Portfolio(double initialCash) : cashBalance(initialCash) {}

void Portfolio::buyStock(Instrument *stock, int qty, double price)
{
    double cost = qty * price;
    if (cashBalance >= cost)
    {
        cashBalance -= cost;
        holdings[stock->getSymbol()] += qty;
        recordTrade(Trade(stock->getSymbol(), qty, price));
    }
    else
    {
        std::cout << "Insufficient cash to buy " << stock->getSymbol() << "\n";
    }
}

void Portfolio::sellStock(Instrument *stock, int qty, double price)
{
    if (holdings[stock->getSymbol()] >= qty)
    {
        holdings[stock->getSymbol()] -= qty;
        cashBalance += qty * price;
        recordTrade(Trade(stock->getSymbol(), -qty, price));
    }
    else
    {
        std::cout << "Not enough holdings to sell " << stock->getSymbol() << "\n";
    }
}

double Portfolio::getCashBalance() const
{
    return cashBalance;
}

double Portfolio::getPortfolioValue(const std::vector<Instrument *> &market) const
{
    double total = cashBalance;
    for (auto &kv : holdings)
    {
        for (auto *stock : market)
        {
            if (stock->getSymbol() == kv.first)
            {
                total += kv.second * stock->getPrice();
            }
        }
    }
    return total;
}

void Portfolio::recordTrade(const Trade &trade)
{
    tradeHistory.push_back(trade);
}

int Portfolio::getHoldings(const std::string &symbol) const
{
    auto it = holdings.find(symbol);
    if (it != holdings.end())
        return it->second;
    return 0;
}

void Portfolio::printHoldings() const
{
    std::cout << "Holdings:\n";
    for (auto &kv : holdings)
    {
        std::cout << "  " << kv.first << ": " << kv.second << " shares\n";
    }
    std::cout << "Cash Balance: " << cashBalance << "\n";
}

void Portfolio::printTradeHistory() const
{
    std::cout << "Trade History:\n";
    for (auto &t : tradeHistory)
    {
        std::cout << (t.quantity > 0 ? "BUY " : "SELL ")
                  << abs(t.quantity) << " of " << t.stockSymbol
                  << " at " << t.price << "\n";
    }
}
