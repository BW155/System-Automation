#include "logger.h"

using namespace std;


void logToFile(TimeClass *timeObject, string text) {
    //createIfNotExist(FILE_NAME);

    /*ofstream outfile;
    outfile.open(FILE_NAME, ios_base::app); // append instead of overwrite
    outfile << timeObject->getTimeString() << " | " << text; 
    outfile.close();*/

    ofstream fout;  // Create Object of Ofstream
    ifstream fin;
    fin.open(FILE_NAME);
    fout.open(FILE_NAME, ios::app); // Append mode
    if(fin.is_open())
        fout << timeObject->getTimeString() << " | " << text << endl; 
    cout<<"\n Data has been appended to file";
    fin.close();
    fout.close(); // Closing the file
}

void createIfNotExist(string name) {
    ofstream file(name);
    if (!file) {
        file << "";
        file.close();
    }
}

