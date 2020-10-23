#ifndef ATIVODIA_H
#define ATIVODIA_H

#include "Ativo.h"

#include <iostream>
#include <vector>
#include "Utilities.h"

using namespace std;

struct Barra;
class Ativo;


class AtivoDia
{
    public:
        AtivoDia(vector<Barra> &vb, string name );
        double lastClose(); // precisa de getter pois Ativo calcula gap e atualiza gap com set
        double firstOpen(); // precisa de getter pois Ativo calcula gap e atualiza gap com set
        void setGap(double gap);
        double getGap();
        void conductAnalysis( vector< AtivoDia > &vad );

        void show();
        void showDay();

        string name();
        double openToSpikePercent();
        int minutesOpenToHigh();
        double spikeToLowPercent();
        int minutesHighToLow();
        double spikeToPreVolFactor();


    private:
        vector<Barra> pre_;
        vector<Barra> core_;
        string name_;
        tm today_;

        // ANALYSIS STUFF
        int volPre_;
        double moneyVolPre_;
        double openValue_;
        double gap_;
        double highCoreValue_;
        tm highCoreTime_;
        int positionHigh_;
        double openToSpikePercent_;
        double lowAfterHighValue_;
        int minutesOpenToHigh_;
        tm lowAfterHighTime_;
        int positionLow_;
        double spikeToLowPercent_;
        int minutesHighToLow_;
        int volumeToSpike_;
        double spikeToPreVolFactor_;

        AtivoDia();
};

#endif // ATIVODIA_H
