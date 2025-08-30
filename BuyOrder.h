#ifndef BUYORDER_H
#define BUYORDER_H

#include "Order.h"
class BuyOrder : public Order
{
public:
    using Order::Order;
    std::string orderType() const override { return "BUY"; }
};

#endif
