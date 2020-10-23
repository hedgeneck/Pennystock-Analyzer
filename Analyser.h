#ifndef ANALYSER_H
#define ANALYSER_H

#include "Ativo.h"
#include "FileManager.h"
#include "AtivoDia.h"
#include <vector>

using namespace std;

class AtivoDia;

class Analyser
{
    public:
        Analyser();
        void conductAnalysis(int startIt = 0, int endIt = 0);
        void showAnalise2();
        void analyseAndShowSpecific(int counter);
        void showFilteredDays(int first = 0);

    private:
        FileManager fm_;
        vector< AtivoDia > vad_;
};

#endif // ANALYSER_H
