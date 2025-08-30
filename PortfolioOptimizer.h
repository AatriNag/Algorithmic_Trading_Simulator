#ifndef PORTFOLIOOPTIMIZER_H
#define PORTFOLIOOPTIMIZER_H

#include "Instrument.h"
#include <vector>

class PortfolioOptimizer
{
public:
    static double optimize(const std::vector<Instrument *> &stocks, int budget);
};

#endif
