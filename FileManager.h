#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// tentei sem muito sucesso usar a lib <filesytem> do gcc 17, mas não está boa ainda.
// precisaremos fazer um programa em python que pega o nome de todos os arquivos do diretorio e joga num txt
// dava pra usar filysistem, mas o gcc é antigo
// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
#include <iostream>
#include <vector>

using namespace std;

struct Ticker
{
    string name;
    string path;
};

class FileManager
{
    public:
        FileManager();
        void showTickers();
        int size();
        Ticker operator[](int i);

    private:
        vector<Ticker> tickers_;
};

#endif // FILEMANAGER_H
