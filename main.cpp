#include <iostream>


#include "Ativo.h"
#include "PerformanceReport.h"
#include "Utilities.h"
#include "Analyser.h"
#include "FileManager.h"

using namespace std;

int main()
{

    Analyser an;
    //an.conductAnalysis(1000,1050); // analisa os ativos, roda os filtros, grava os dias em questão numa estrutura de dados interna
    an.conductAnalysis();
    an.showAnalise2();

    //an.analyseAndShowSpecific(49);

    //an.conductAnalysis(0,100);
    //an.showFilteredDays(30);


    return 0;
}
