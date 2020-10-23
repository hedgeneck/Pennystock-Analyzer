#ifndef PERFORMANCEREPORT_H
#define PERFORMANCEREPORT_H

#include <iostream>

#include <ctime>
#include <vector>

using namespace std;

struct TradeStatistics{
    // public statistics
    double netProfit;
    double cumProfit;
    int numberDays;
    // private statistics
};

struct OverallStatistics{
    double netProfit;
    int totalNumberOfTrades;
    double averageDaysInTrade;
};

enum class Type {   SellShort = -2, // se estivermos Long, ele fecha com Sell e depois dá o SellShort
                    Sell = -1, // se estivermos Long, ele vende pra sair da posição. Ele nunca vai ficar vendido.
                    BuyToCover = 1, // se estivermos Short, ele compra pra sair da posição, nunca vai ficar comprado.
                    Buy = 2 }; // se estivermos Short, ele da BuyToCover pra sair da posição e depois dá o Buy
// notar que só teremos dois pares de trade. Ou um Buy com Sell, ou um SellShort com um BuyToCover

struct Trade
{
    tm entryDate;
    tm exitDate;
    double entryPrice;
    double exitPrice;
    Type entryType;
    Type exitType;
};

class PerformanceReport
{
    public:
        PerformanceReport();
        void insertTrade(tm entryDate, tm exitDate, double entryPrice, double exitPrice, Type entryType, Type exitType);
        void showTrades();
        void showTradeStatistics();
        void showOverallStatistics();
        void calculateOverallStatistics();

    private:
        TradeStatistics calculateTradeStatistics(Trade t);
        vector<Trade> trades_;
        vector<TradeStatistics> tradeStatistics_;
        OverallStatistics overallStatistics_;
};

#endif // PERFORMANCEREPORT_H
