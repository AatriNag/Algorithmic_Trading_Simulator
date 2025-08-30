// MatchingEngine.cpp
#include "MatchingEngine.h"
#include <algorithm>        // std::min
#include <initializer_list> // optional

void MatchingEngine::placeOrder(Order *order)
{
    if (order->orderType() == "BUY")
        buyHeap.push(order);
    else
        sellHeap.push(order);

    matchOrders();
}

void MatchingEngine::matchOrders()
{
    while (!buyHeap.empty() && !sellHeap.empty())
    {
        Order *buy = buyHeap.top();
        Order *sell = sellHeap.top();

        // Check stock ticker
        if (buy->getStock()->getSymbol() != sell->getStock()->getSymbol())
        {
            // Not the same stock, cannot match
            break;
        }

        // Check seller’s available holdings
        int availableQty = sell->getPortfolio()->getHoldings(sell->getStock()->getSymbol());
        if (availableQty <= 0)
        {
            // Seller has nothing to sell, discard order
            sellHeap.pop();
            continue;
        }

        // Determine trade quantity
        int qty = std::min({buy->getQuantity(), sell->getQuantity(), availableQty});

        if (qty <= 0)
            break;

        double tradePrice = sell->getPrice(); // use seller’s price

        std::cout << "TRADE: " << qty
                  << " shares of " << buy->getStock()->getSymbol()
                  << " at " << tradePrice << "\n";

        // Execute trade
        buy->getPortfolio()->buyStock(buy->getStock(), qty, tradePrice);
        sell->getPortfolio()->sellStock(sell->getStock(), qty, tradePrice);

        // Reduce quantities
        buy->reduceQuantity(qty);
        sell->reduceQuantity(qty);

        if (buy->getQuantity() == 0)
            buyHeap.pop();
        if (sell->getQuantity() == 0)
            sellHeap.pop();
    }
}
