#include "Ativo.h"

#include <fstream>
#include <cstring> // serve para usar strtok e lidar com tokens de strings
#include <sstream> // para lidar com istringstream objects
#include <iomanip> // permite usar a maravilhosa função get_time()
#include <algorithm> // permite usar a função reverse()

#include "Utilities.h" // se botar esse include no header de ativo dá pau, verificar porque.


Ativo::Ativo()
{

}

Ativo::~Ativo()
{

}

Ativo::Ativo(const string & filename, string name): filename_(filename), position_(0), name_(name) {


    const char *delimiter = ",";
    const unsigned int skip_header = 1;

    const unsigned int column_time = 0;
    const unsigned int column_open = 1;
    const unsigned int column_high = 2;
    const unsigned int column_low = 3;
    const unsigned int column_close = 4;
    const unsigned int column_vol = 5;

    //cout << "#### Abrindo dados historicos ####" << endl;

    ifstream input_file(filename_);

    unsigned int row = 0;

    while (input_file.good()) {

        string line;

        getline(input_file, line);

        if (row >= skip_header && line.length() > 0) {

            unsigned int column = 0;

            char *token = strtok(const_cast<char*>(line.c_str()), delimiter);

            Barra b;

            while (token != NULL)
            {
                const double value = stod(token); // se for string mesmo, vai botar string em value, mas é só não usar depois

                if (column == column_time) {
                    tm tm = {};
                    istringstream ss(token);
                    //ss >> get_time(&tm, "%m/%d/%Y");
                    // exemplo: "2020-10-15 17:16:00"
                    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
                    b.time = tm;
                } else if (column == column_open) {
                    b.open = value;
                    //open_.emplace_back(value);
                } else if (column == column_high) {
                    b.high = value;
                    //high_.emplace_back(value);
                } else if (column == column_low) {
                    b.low = value;
                    //low_.emplace_back(value);
                } else if (column == column_close) {
                    b.close = value;
                    //close_.emplace_back(value);
                } else if (column == column_vol) {
                    b.vol = value;
                    //vol_.emplace_back(value);
                }

                column += 1;
                token = strtok(NULL, delimiter);
            }

            raw_.emplace_back(b);
        }
        //cout << "aqui 1" << endl;
        row += 1;
    }

    if(raw_.size() == 0 ) {
        throw 8;
    }

    reverse(raw_.begin(),raw_.end());
    rawDays_ = Utilities::divideDays(raw_);

    initializeDays();

    input_file.close();

}

/*** DEPRECATED ***/
void Ativo::show() const {

    for(int i = 0; i<raw_.size(); i++) { // exemplo: "2020-10-15 17:16:00"
        cout << "Elemento " << i << ": " << raw_[i].time.tm_mday << "/" << raw_[i].time.tm_mon+1 <<
            "/" << raw_[i].time.tm_year+1900 << " " << raw_[i].time.tm_hour << ":" << raw_[i].time.tm_min <<
            ":" << raw_[i].time.tm_sec << " O: " << raw_[i].open << " H: " << raw_[i].high << " L: " <<
            raw_[i].low << " C: " << raw_[i].close << " Vol: " << raw_[i].vol << endl;
    }
}

/*** DEPRECATED ***/
void Ativo::showRawDays() {
    for(int i = 0; i<rawDays_.size(); i++) {
        cout << "i: " << i << endl;
        for(int j = 0; j<rawDays_[i].size(); j++) {
            cout << "j: " << flush;
            rawDays_[i][j].show();
        }
    }
}

void Ativo::showDays(int count) {

    if(count == 0) { // se count for 0 provavelmente user não quis digitar nada, então bota todos os dias
        count = days_.size();
    }
//    for(int i = 0; i<days_.size(); i++) {
    for(int i = 0; i<count; i++) {
        cout << "i: " << i << endl;
        //cout << "Last Close: " << days_[i].lastClose() << endl; // last close é uma variavel que é do dia
        days_[i].show();
    }

}

int Ativo::nDays() {
    //return days_.size(); // tambem funciona
    return nDays_;

}

AtivoDia Ativo::operator[](int i) {

    return days_[i];
}

void Barra::show() {
    cout << time.tm_mday << "/" << time.tm_mon+1 <<
        "/" << time.tm_year+1900 << " " << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << " O: " << open << " H: " <<
        high << " L: " << low << " C: " << close << " V: " << vol << endl;
}

void Ativo::initializeDays(){
    // vai iterar n número de dias
    // aqui não é lugar pra colocar Analyser pq ele precisa que todos os dias já estejam instanciados

    for(int i = 0; i<rawDays_.size(); i++) {
        AtivoDia ad(rawDays_[i], name_);
        // pra cada dia poderia calcular o gap, mas fica muito bizarro, melhor iterar depois
        days_.emplace_back(ad);
    }

    nDays_ = rawDays_.size();

    // CALCULA OS GAPS DE CADA DIA
    for(int i = 0; i<nDays_; i++){
        if(i != 0) {
            //days_[i].showDay();
            days_[i].setGap( ( days_[i].firstOpen()-days_[i-1].lastClose() )/( days_[i-1].lastClose() ) );
        } else {
            days_[i].setGap(0);
        }
    }
}

void Ativo::conductAnalysis( vector< AtivoDia > &vad ){
    //cout << "Ticker: " << name_ << endl;
    for (int i = 0; i<days_.size(); i++) {
        days_[i].conductAnalysis( vad );
    }
}
