#include "FileManager.h"

#include <fstream>
#include <cstring>

FileManager::FileManager()
{
    string root = "..\\..\\..\\Data\\data_dist\\";
    const char *delimiter = ",";
    unsigned int column_ticker = 0;
    unsigned int column_path = 1;

    ifstream input_file("names.txt");

    while (input_file.good()) {
        string line;

        getline(input_file, line);

        if( line.length() > 0 ) {
           unsigned int column = 0;

            char *token = strtok(const_cast<char*>(line.c_str()), delimiter);

            Ticker t;

            while (token != NULL)
            {
                string value = token;

                if (column == column_ticker) {
                    t.name = value;
                } else if (column == column_path) {
                    t.path = root + value;
                }

                column += 1;
                token = strtok(NULL, delimiter);
            }

            tickers_.emplace_back(t);
        }
    }
}

void FileManager::showTickers() {

    for(int i = 0; i<tickers_.size();i++) {
        cout << "i: " << i << " Ticker: " << tickers_[i].name << " Path: " << tickers_[i].path << endl;
    }
}

int FileManager::size() {
    return tickers_.size();
}

Ticker FileManager::operator[](int i) {
    return tickers_[i];
}
