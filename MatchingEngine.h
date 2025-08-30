// MatchingEngine.h
#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include "Order.h"
#include <queue>
#include <vector>
#include <iostream>

struct BuyComparator
{
    bool operator()(Order *a, Order *b) { return a->getPrice() < b->getPrice(); }
};

struct SellComparator
{
    bool operator()(Order *a, Order *b) { return a->getPrice() > b->getPrice(); }
};

class MatchingEngine
{
    std::priority_queue<Order *, std::vector<Order *>, BuyComparator> buyHeap;
    std::priority_queue<Order *, std::vector<Order *>, SellComparator> sellHeap;

public:
    MatchingEngine() {}
    void placeOrder(Order *order);
    void matchOrders();
};

#endif
