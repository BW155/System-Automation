#include "timeKeeper.h"
#include "string"
#include "fstream"

const string FILE_NAME = "log.txt";

void logToFile(TimeClass*, std::string);
void createIfNotExist(std::string);

