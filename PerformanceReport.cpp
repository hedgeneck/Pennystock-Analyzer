#include "PerformanceReport.h"

#include "Utilities.h"

PerformanceReport::PerformanceReport()
{
    //ctor
}

void PerformanceReport::insertTrade(tm entryDate, tm exitDate, double entryPrice, double exitPrice, Type entryType, Type exitType)
{
    Trade t;
    t.entryDate = entryDate;
    t.exitDate = exitDate;
    t.entryPrice = entryPrice;
    t.exitPrice = exitPrice;
    t.entryType = entryType;
    t.exitType = exitType;

    trades_.emplace_back(t);

    tradeStatistics_.emplace_back( calculateTradeStatistics(t) );
}

void PerformanceReport::showTrades(){

    for(int i = 0; i<trades_.size();i++){

        string entryType;
        switch( (int)trades_[i].entryType ){
            case 2:
                entryType = "Buy";
            break;
            case 1:
                entryType = "Buy To Cover";
            break;
            case -1:
                entryType = "Sell";
            break;
            case -2:
                entryType = "Sell Short";
            break;
        }

        string exitType;
        switch( (int)trades_[i].exitType ){
            case 2:
                exitType = "Buy";
            break;
            case 1:
                exitType = "Buy To Cover";
            break;
            case -1:
                exitType = "Sell";
            break;
            case -2:
                exitType = "Sell Short";
            break;
        }

        cout << "i: " << i << " " << endl;
        cout << entryType << " " << trades_[i].entryDate.tm_mday << "/" << trades_[i].entryDate.tm_mon+1 <<
                "/" << trades_[i].entryDate.tm_year+1900 << " Entry Price: " << trades_[i].entryPrice << endl;
        cout << exitType << " " << trades_[i].exitDate.tm_mday << "/" << trades_[i].exitDate.tm_mon+1 <<
                "/" << trades_[i].exitDate.tm_year+1900 << " Exit Price: " << trades_[i].exitPrice << endl;
        cout << endl;
        //cout << (int)trades_[i].entryType << endl;
    }
}

void PerformanceReport::showTradeStatistics() {

    for(int i = 0; i<tradeStatistics_.size() ;i++) {
        cout << "i: " << i << " " << endl;
        cout << " Net Profit: " << tradeStatistics_[i].netProfit << endl;
        cout << " Cum Profit: " << tradeStatistics_[i].cumProfit << endl;
        cout << " Days in the Trade: " << tradeStatistics_[i].numberDays << endl;
        cout << endl;
    }

}

TradeStatistics PerformanceReport::calculateTradeStatistics(Trade t) {

    TradeStatistics ts;

    // NET PROFIT
    if(t.entryType == Type::Buy){
        ts.netProfit = (t.exitPrice-t.entryPrice)*100000;
    }
    if(t.entryType == Type::SellShort){
        ts.netProfit = -(t.exitPrice-t.entryPrice)*100000;
    }

    // ts.percentProfit = (t.exitPrice-t.entryPrice)/t.entryPrice*100; // lembrar que o *100 multiplica o numerador
    // falta calcular cumulativeProfit

    // CUMULATIVE PROFIT
    double cumProfit = ts.netProfit; // o cumSum é o net profit do trade mais todos os anteriores
    for(int i = 0; i<tradeStatistics_.size(); i++) {
        cumProfit+=tradeStatistics_[i].netProfit;
    }
    ts.cumProfit = cumProfit;

    // NUMBER OF DAYS IN TRADE
    int numberDays;
    numberDays = Utilities::daysDifference(t.entryDate,t.exitDate);
    ts.numberDays = numberDays; // esse estilo está legal de quebrar em 3 linhas? Poderia ser tudo em uma linha. Ver quantlib.

    return ts;
}

void PerformanceReport::calculateOverallStatistics() {

    // NET PROFIT
    double netProfit = 0;
    for(int i = 0; i < tradeStatistics_.size(); i++) {
        netProfit += tradeStatistics_[i].netProfit;
    }
    overallStatistics_.netProfit = netProfit;

    // TOTAL NUMBER OF TRADES
    int totalNumberOfTrades = trades_.size();
    overallStatistics_.totalNumberOfTrades = totalNumberOfTrades;

    // AVERAGE DAYS IN TRADE
    double averageDaysInTrade = 0;
    for (int i = 0; i < tradeStatistics_.size();i++) {
        averageDaysInTrade += (double)tradeStatistics_[i].numberDays/(double)totalNumberOfTrades;
    }
    overallStatistics_.averageDaysInTrade = averageDaysInTrade;

    cout << "Calculando overall statistics" << endl;
}

void PerformanceReport::showOverallStatistics() {
    cout << "Net Profit: " << overallStatistics_.netProfit << endl;
    cout << "Total Number of Trades: " << overallStatistics_.totalNumberOfTrades << endl;
    cout << "Average Days in Each Trade: " << overallStatistics_.averageDaysInTrade << endl;
}
