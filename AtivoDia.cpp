#include "AtivoDia.h"

AtivoDia::AtivoDia()
{
    //ctor
}

AtivoDia::AtivoDia( vector<Barra> &vb, string name ): gap_(0), volPre_(0), name_(name){

    // COPIA DADOS PRE E CORE
    for (int i=0; i<vb.size();i++){ // aqui eu precisaria verificar se uma hora está entre dois horários no dia
        if( Utilities::isCoreHours(vb[i].time) ){
            core_.emplace_back(vb[i]);
        } else if( Utilities::isPreHours(vb[i].time) ){
            pre_.emplace_back(vb[i]);
        }
    }

    // se tem pre mas não tem core, pega os preços do ultimo elemento do pre, ajusta time, bota vol = 0 e bota no core_
    if (pre_.size() > 0 && core_.size()==0 ) { // essa parte resolve um puta bug
        Barra b = pre_.back(); // verificar se é back mesmo
        b.time.tm_hour = 9;
        b.time.tm_min = 31;
        b.vol=0;
        core_.emplace_back(b);
    }

    // se não tem pre_ nem core_ é porque só tem pos_, então faz o mesmo esquema e adiciona no core_
    if (pre_.size() == 0 && core_.size()== 0 ) { // essa parte resolve um puta bug
        Barra b = vb[0]; // verificar se é back mesmo
        b.time.tm_hour = 16;
        b.time.tm_min = 0;
        b.vol=0;
        core_.emplace_back(b);
    }

    today_ = core_[0].time;

    // ALGUNS CÁLCULOS QUE PRECISAM DE DADOS DE OUTROS DIAS SERÃO CALCULADOS FORA DA CLASSE E PASSADOS PRA CLASSE VIA SETTERS
    // classe Ativo calcula gap_ via setter em initializeDays()

    // CALCULA VOLUME DE PRE MARKET
    int volPre = 0;
    for (int i = 0; i < pre_.size(); i++) {
        volPre += pre_[i].vol;
    }
    volPre_ = volPre;

    // CALCULA MONEY VOLUME DE PRE MARKET
    int moneyVolPre = 0;
    for (int i = 0; i < pre_.size(); i++) {
        moneyVolPre += (pre_[i].vol * pre_[i].close );
    }
    moneyVolPre_ = moneyVolPre;

    // CALCULA OPEN VALUE (valor da ação na abertura)
    openValue_ = core_[0].open;

    // CALCULA HIGH DO CORE
    highCoreValue_ = core_[0].high;
    highCoreTime_ = core_[0].time;
    positionHigh_ = 0;
    for (int i = 0; i<core_.size(); i++) {
        if( highCoreValue_ < core_[i].high ) {
            highCoreValue_ = core_[i].high;
            highCoreTime_ = core_[i].time;
            positionHigh_ = i;
        }
    }

    // CALCULA LOW DEPOIS DO SPIKE
    lowAfterHighValue_ = core_[positionHigh_].high;
    lowAfterHighTime_ = core_[positionHigh_].time;
    positionLow_ = positionHigh_;
    for (int i = positionHigh_; i<core_.size(); i++) {
        if(lowAfterHighValue_ > core_[i].low ) {
            lowAfterHighValue_ = core_[i].low;
            lowAfterHighTime_ = core_[i].time;
            positionLow_ = i;
        }
    }

    // CALCULA VARIAÇÃO PERCENTUAL DO OPEN ATÉ O SPIKE
    openToSpikePercent_ = (core_[positionHigh_].high - core_[0].open)/(core_[0].open);

    // CALCULA VARIAÇÃO PERCENTUAL DO SPIKE ATÉ O LOW
    spikeToLowPercent_ = ( core_[positionLow_].low - core_[positionHigh_].high )/(core_[positionHigh_].high);

    // CALCULA MINUTES DESDE O OPEN ATÉ O SPIKE
    minutesOpenToHigh_ = Utilities::calculateMinutes(9,31,highCoreTime_);

    // CALCULA MINUTES DESDE O HIGH ATÉ O LOW DEPOIS DO HIGH
    minutesHighToLow_ = Utilities::calculateMinutes(highCoreTime_,lowAfterHighTime_);

    // CALCULA VOLUME FROM START OF CORE TO SPIKE
    volumeToSpike_ = 0;
    for (int i = 0; i<=positionHigh_; i++) {

        volumeToSpike_ += core_[i].vol;
    }

    // CALCULA FATOR VOLUME ATÉ O SPIKE DIVIDIDO PELO VOLUME PRE

    if ( volPre_ == 0 ) { // == funciona pois vol é int
        spikeToPreVolFactor_ = 0;
    } else {
        spikeToPreVolFactor_ = (double)(volumeToSpike_)/(double)(volPre_);
    }
}

void AtivoDia::show() {

    cout << "Volume Pre Market: " << volPre_ << endl;
    cout << "Money Volume Pre Market: " << moneyVolPre_ << endl;
    cout << "Gap from D-1 last close To D first open: " << gap_ << endl;
    cout << "Open Value Core: " << openValue_ << endl;
    cout << "High dia: " << highCoreValue_ << " em " << highCoreTime_.tm_hour << ":" << highCoreTime_.tm_min << endl;
    cout << "Low after High: " << lowAfterHighValue_ << " em " << lowAfterHighTime_.tm_hour << ":" << lowAfterHighTime_.tm_min << endl;
    cout << "Open to Spike Variation in percent: " << openToSpikePercent_ << endl;
    cout << "Spike to Low Variation in percent: " << spikeToLowPercent_ << endl;
    cout << "Minutes from Open to High: " << minutesOpenToHigh_ << endl;
    cout << "Minutes from High to Low: " << minutesHighToLow_ << endl;
    cout << "Volume until Spike: " << volumeToSpike_ << endl;
    cout << "Factor: Volume to Spike // Pre Volume " << spikeToPreVolFactor_ << endl;

    cout << "pre_" << endl;

    for(int i = 0; i < pre_.size();i++) {
        pre_[i].show();
    }

    cout << "core_" << endl;

    for(int i = 0;i < core_.size();i++) {
        core_[i].show();
    }

}

void AtivoDia::showDay(){
    cout << name_ << " " << core_[0].time.tm_mday << "/" << core_[0].time.tm_mon + 1 << "/" << core_[0].time.tm_year + 1900 << endl;
}

double AtivoDia::lastClose(){
    return core_.back().close;
}

double AtivoDia::firstOpen(){
    return core_.front().open;
}

void AtivoDia::setGap(double gap) {
    gap_ = gap;
}


double AtivoDia::getGap() {
    return gap_;
}

void AtivoDia::conductAnalysis( vector< AtivoDia > &vad ) {
    if (volPre_ > 800000) {
        if (gap_ >= 0.1) {
            if(openValue_ > 1 ) {
                vad.emplace_back( *this );
                cout << name_ << " " << core_[0].time.tm_mday << "/" << core_[0].time.tm_mon + 1 << "/"
                    << core_[0].time.tm_year + 1900 << endl;
            }
        }
    }
}

string AtivoDia::name() {
    return name_;
}

double AtivoDia::openToSpikePercent() {
    return openToSpikePercent_;
}

int AtivoDia::minutesOpenToHigh() {
    return minutesOpenToHigh_;
}

double AtivoDia::spikeToLowPercent() {
    return spikeToLowPercent_;
}

int AtivoDia::minutesHighToLow() {
    return minutesHighToLow_;
}

double AtivoDia::spikeToPreVolFactor(){
    return spikeToPreVolFactor_;
}
