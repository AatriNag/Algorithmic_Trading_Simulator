#include "Stock.h"
#include "Trader.h"
#include "Order.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include "MatchingEngine.h"
#include "PortfolioOptimizer.h"
#include <iostream>
#include <vector>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    // --- 1. Create Stocks ---
    Stock aapl("AAPL", 150);
    Stock goog("GOOG", 2800);
    Stock tsla("TSLA", 700);
    std::vector<Instrument *> market = {&aapl, &goog, &tsla};

    // --- 2. Create Traders with different cash ---
    Portfolio trader1(10000);
    Portfolio trader2(5000);
    Portfolio trader3(2000);
    std::vector<Portfolio *> traders = {&trader1, &trader2, &trader3};

    // --- 3. Initial holdings allocation ---
    trader1.buyStock(&aapl, 10, aapl.getPrice()); // 10 AAPL
    trader1.buyStock(&goog, 2, goog.getPrice());  // 2 GOOG
    trader2.buyStock(&aapl, 5, aapl.getPrice());  // 5 AAPL
    trader3.buyStock(&tsla, 5, tsla.getPrice());  // 5 TSLA

    // --- 4. Multi-day simulation ---
    for (int day = 1; day <= 3; day++)
    {
        std::cout << "\n=== Day " << day << " Prices ===\n";

        // Update stock prices to simulate market
        aapl.updatePrice();
        goog.updatePrice();
        tsla.updatePrice();

        for (auto s : market)
        {
            std::cout << s->getSymbol() << ": $" << s->getPrice()
                      << " | Expected return: " << s->getExpectedReturn() << "\n";
        }

        MatchingEngine engine;

        // Day-specific orders
        if (day == 1)
        {
            engine.placeOrder(new SellOrder(&aapl, 5, aapl.getPrice(), &trader1)); // Trader1 sells 5 AAPL
            engine.placeOrder(new BuyOrder(&aapl, 5, aapl.getPrice(), &trader2));  // Trader2 buys 5 AAPL
            engine.placeOrder(new BuyOrder(&goog, 1, goog.getPrice(), &trader3));  // Trader3 buys 1 GOOG
        }

        if (day == 2)
        {
            engine.placeOrder(new SellOrder(&tsla, 2, tsla.getPrice(), &trader3)); // Trader3 sells 2 TSLA
            engine.placeOrder(new BuyOrder(&tsla, 2, tsla.getPrice(), &trader2));  // Trader2 buys 2 TSLA
        }

        if (day == 3)
        {
            engine.placeOrder(new SellOrder(&goog, 1, goog.getPrice(), &trader1)); // Trader1 sells 1 GOOG
            engine.placeOrder(new BuyOrder(&goog, 1, goog.getPrice(), &trader3));  // Trader3 buys 1 GOOG
        }

        // Execute trades
        engine.matchOrders();
    }

    // --- 5. Print final portfolios ---
    int id = 1;
    for (auto trader : traders)
    {
        std::cout << "\n--- Trader " << id++ << " Portfolio ---\n";
        trader->printHoldings();
        trader->printTradeHistory();
        std::cout << "Total value: $" << trader->getPortfolioValue(market) << "\n";
    }

    // --- 6. Portfolio Optimization per trader ---
    std::cout << "\n--- Portfolio Optimization Suggestion ---\n";
    id = 1;
    for (auto trader : traders)
    {
        int budget = static_cast<int>(trader->getCashBalance());
        double maxReturn = PortfolioOptimizer::optimize(market, budget);
        std::cout << "Trader " << id++ << " optimal expected return (budget $"
                  << budget << "): " << maxReturn << "\n";
    }

    return 0;
}

