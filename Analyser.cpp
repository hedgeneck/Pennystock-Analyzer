#include "Analyser.h"

Analyser::Analyser()
{

}

// lembrar que quando temos default arguments colocamos o valor default na declaração, mas não na definição
void Analyser::conductAnalysis( int startIt, int endIt ){
    if ( endIt==0 ) { // nesse caso provavelmente o user não quis passar nada, então roda em tudo
        endIt = fm_.size();
    }

    for (int i = startIt; i<endIt ;i++) {
        Ticker t = fm_[i];
        try{
            Ativo a(t.path, t.name);
            a.conductAnalysis( vad_ );
        } catch(int num) {
            //cout << "i: " << i << " Nome: " << t.name << " NENHUM DADO FORNECIDO" << endl;
        }
    }
}

void Analyser::showAnalise2() {

    // soma algumas statistics iterando em cada Dia-Ativo filtrado
    // estamos declarando essas variáveis pois queremos overall statistics
    double openToSpikeMean = 0;
    double openToSpikeMinutesMean = 0;
    double spikeToLowMean = 0;
    double spikeToLowMinutesMean = 0;
    double spikeToPreVolFactorMean = 0;

    for (int i = 0; i < vad_.size() ;i++) {
            openToSpikeMean += ( (double)( vad_[i].openToSpikePercent() )) / ( vad_.size() );
            openToSpikeMinutesMean += ((double)(vad_[i].minutesOpenToHigh()))/(vad_.size());
            spikeToLowMean += ((double)(vad_[i].spikeToLowPercent()))/(vad_.size());
            spikeToLowMinutesMean += ((double)(vad_[i].minutesHighToLow()))/(vad_.size());
            spikeToPreVolFactorMean  += ((double)(vad_[i].spikeToPreVolFactor()))/(vad_.size());
    }

    cout << "Media percentual de open to spike: " << openToSpikeMean << endl;
    cout << "Minutos em media de open to spike: " << openToSpikeMinutesMean << endl;
    cout << "Media percentual de spike to low: " << spikeToLowMean << endl;
    cout << "Minutos em media de spike to low: " << spikeToLowMinutesMean << endl;
    cout << "Media Fator Vol to Spike // Vol Pre: " << spikeToPreVolFactorMean << endl;

    // calcula número de tickers
    int numberStocksFiltered = 1;
    string actualName = vad_[0].name();
    for(int i = 0; i < vad_.size();i++) {
        if( actualName != vad_[i].name() ){
            numberStocksFiltered += 1;
            actualName = vad_[i].name();
        }
    }

    cout << endl;
    cout << "Numero de acoes que satisfizeram o filtro: " << numberStocksFiltered << endl;
    cout << "Numero total de dias que satisfizeram o filtro: " << vad_.size() << endl;

}

void Analyser::analyseAndShowSpecific(int counter) {

    Ticker t = fm_[counter];
    cout << "Nome: " << t.name << "\t" << " Path: " << t.path << endl;
    Ativo a(t.path, t.name);
    a.showDays(30);
}

void Analyser::showFilteredDays(int first) {

    if (first == 0) {
        first = vad_.size();
    }

    for(int i = 0; i < first;i++) {

        cout << "i: " << i << " Name: " << vad_[i].name() << endl;
        vad_[i].show();
    }

}
