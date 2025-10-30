#ifndef FILEIO_H
#define FILEIO_H
#include "parking.h"

void saveParkingData();
void loadParkingData();
void saveBill(Vehicle v, double amount);
void generateReport();

#endif
