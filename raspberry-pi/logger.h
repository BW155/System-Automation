#include "timeKeeper.h"
#include "string"
#include "fstream"

#ifndef LOGGER_H
#define LOGGER_H

const string FILE_NAME = "log.txt";

void logToFile(TimeClass*, std::string);
void createIfNotExist(std::string);

#endif
