#ifndef ATIVO_H
#define ATIVO_H

#include <iostream>
#include <vector>
#include <ctime> // para usar a struct tm

#include "AtivoDia.h"
#include "Analyser.h"


using namespace std;

class AtivoDia;

struct Barra
{
    tm time;
    double open;
    double high;
    double low;
    double close;
    int vol;

    void show();
};

//struct AtivoStatistics
//{
//    int nDaysWith10Gap;
//};

class Ativo
{
    public:
        Ativo(const string & filename, string name);
        virtual ~Ativo();
        void show() const; // deprecated
        void showRawDays(); // deprecated
        void showDays(int count = 0);
        void initializeDays();
        int nDays();
        void showStatistics();
        void conductAnalysis( vector< AtivoDia > &vad );

        AtivoDia operator[](int i);

    private:
        string filename_;
        string name_;

        vector<Barra> raw_;
        vector< vector<Barra> > rawDays_;
        vector<AtivoDia> days_;


        int position_;
        int nDays_;

        Ativo(); // proibido chamar construtor sem argumento
};

#endif // ATIVO_H
