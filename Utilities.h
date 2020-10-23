#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <iostream>

#include <sstream>
#include <iomanip>
#include <ctime>

#include "Ativo.h" // engraçado como incluindo Ativo.h incluímos uma porrada de coisa duplicada

using namespace std;

class Barra;

namespace Utilities {

int daysDifference(tm& entryDate, tm& exitDate);
int secondsDifference(tm& firstDate, tm& lastDate);

vector< vector<Barra> > divideDays(const vector<Barra>& vb);

void showVVB( vector< vector<Barra> > &vvb ); // shows Vector of Vector of Bars
bool isCoreHours(int h, int m);
bool isCoreHours(tm time);
bool isPreHours(int h, int m);
bool isPreHours(tm time);
int calculateMinutes(int startHour, int startMinute, tm endTime);
int calculateMinutes(tm startTime, tm endTime);

}

#endif
