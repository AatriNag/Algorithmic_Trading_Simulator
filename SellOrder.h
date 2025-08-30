#ifndef SELLOADER_H
#define SELLOADER_H

#include "Order.h"

class SellOrder : public Order
{
public:
    using Order::Order;
    std::string orderType() const override { return "SELL"; }
};

#endif
