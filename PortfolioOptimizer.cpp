#include "PortfolioOptimizer.h"
#include <algorithm>

double PortfolioOptimizer::optimize(const std::vector<Instrument *> &stocks, int budget)
{
    int n = stocks.size();
    std::vector<std::vector<double>> dp(n + 1, std::vector<double>(budget + 1, 0.0));

    for (int i = 1; i <= n; i++)
    {
        int price = (int)stocks[i - 1]->getPrice();
        double ret = stocks[i - 1]->getExpectedReturn();
        for (int w = 0; w <= budget; w++)
        {
            if (price <= w)
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - price] + ret);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][budget];
}
