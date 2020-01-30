#include "logger.h"

using namespace std;


void logToFile(TimeClass *timeObject, string text) {
//    createIfNotExist(FILE_NAME);xt
    if (text.compare("")) {
        ofstream fout;  // Create Object of Ofstream
        ifstream fin;
        fin.open(FILE_NAME);
        fout.open(FILE_NAME, ios::app); // Append mode
        if (fin.is_open())
            fout << timeObject->getTimeString() << " | " << text << endl;
        fin.close();
        fout.close(); // Closing the file
    }
}

void createIfNotExist(string name) {
    ofstream file(name);
    if (!file) {
        file << "";
        file.close();
    }
}

