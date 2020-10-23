#include "Utilities.h"

namespace Utilities {

int daysDifference(tm& entryDate, tm& exitDate) {

    time_t entryTime = mktime(&entryDate);
    time_t exitTime = mktime(&exitDate);

    double secondsDiff = difftime(exitTime,entryTime);

    int daysDiff = secondsDiff / (60 * 60 * 24); // se não tivesse return acho que isso seria o retornado

    return daysDiff;
}


int secondsDifference(tm& firstDate, tm& lastDate) {

    time_t firstTime = mktime(&firstDate);
    time_t lastTime = mktime(&lastDate);

    int secondsDiff = difftime(lastTime,firstTime);

    return secondsDiff;
}

vector< vector<Barra> > divideDays(const vector<Barra>& vb){

    vector< vector<Barra> > vvb;
    vector<Barra> temp;

    tm actualDay = vb[0].time;

    for (int i = 0; i < vb.size();i++) {
        tm day = vb[i].time;

        // se o dia do loop for o mesmo do dia fora do loop, é um dia normal, vai acumulando no vetor
        if( (day.tm_mday==actualDay.tm_mday) && (day.tm_mon==actualDay.tm_mon) && (day.tm_year==actualDay.tm_year) ) {
            temp.emplace_back(vb[i]);
        } else { // chegou num novo dia
            vvb.emplace_back(temp); // joga em vbb as bars do dia anterior que tu coletou até agora
            temp.clear(); // limpa o buffer pra começar a jogar Bars do novo dia
            temp.emplace_back(vb[i]); // com o buffer zerado começa a jogar no novo dia
            actualDay = day; // esse vai ser o novo dia, vamos registrar isso fora do loop
        }
    }

    return vvb;
}

void showVVB( vector< vector<Barra> > &vvb ){

    for(int i = 0; i<vvb.size(); i++) {
        cout << i << endl;
    }
}

bool isCoreHours(int h, int m) {
    //checa se o tempo passado h:m está entre 09:30 < h:m <= 16:00

    //const unsigned int startHour = 9;
    //const unsigned int startMin = 30;
    //const unsigned int endHour = 16;
    //const unsigned int endMin = 00;

    bool condition1; // testa se o tempo é maior que 09:30
    if( h == 9 && m > 30 ) {
        condition1 = true;
    } else if(h>=10){
        condition1 = true;
    } else{
        condition1 = false;
    }

    bool condition2; // testa se o tempo é menor que 16:00
    if(h<=15) {
        condition2 = true;
    } else if(h == 16 && m == 0) {
        condition2 = true;
    } else {
        condition2 = false;
    }

    return condition1 && condition2; // se as duas conditions forem true, retorna true.
}

bool isCoreHours(tm time) {

    int h = time.tm_hour;
    int m = time.tm_min;

    bool condition1; // testa se o tempo é maior que 09:30
    if( h == 9 && m > 30 ) {
        condition1 = true;
    } else if(h>=10){
        condition1 = true;
    } else{
        condition1 = false;
    }

    bool condition2; // testa se o tempo é menor que 16:00
    if(h<=15) {
        condition2 = true;
    } else if(h == 16 && m == 0) {
        condition2 = true;
    } else {
        condition2 = false;
    }

    return condition1 && condition2; // se as duas conditions forem true, retorna true.
}

bool isPreHours(int h, int m) {
    //checa se o tempo passado h:m é menor ou igual que 09:30

    //const unsigned int endHour = 09;
    //const unsigned int endMin = 30;

    bool condition; // testa se o tempo é maior que 09:30
    if( h == 9 && m < 30 ) {
        condition = true;
    } else if(h<=8){
        condition = true;
    } else{
        condition = false;
    }

    return condition;
}

bool isPreHours(tm time) {

    int h = time.tm_hour;
    int m = time.tm_min;

    bool condition; // testa se o tempo é maior que 09:30
    if( h == 9 && m < 30 ) {
        condition = true;
    } else if(h<=8){
        condition = true;
    } else{
        condition = false;
    }

    return condition;
}

int calculateMinutes(int startHour, int startMinute, tm endTime) {

    int hours = endTime.tm_hour - startHour;
    int minutes = endTime.tm_min - startMinute;

    return hours*60 + minutes;
}

int calculateMinutes(tm startTime, tm endTime) {

    int hours = endTime.tm_hour - startTime.tm_hour;
    int minutes = endTime.tm_min - endTime.tm_min;

    return hours*60 + minutes;
}

}
