#ifndef PARKING_H
#define PARKING_H

#include <time.h>   // <-- Add this line

#define MAX_SLOTS 10

typedef struct {
    int slotNumber;
    char vehicleNumber[20];
    char ownerName[30];
    int isVIP;
    time_t entryTime;
} Vehicle;

void initializeParking();
void vehicleEntry();
void vehicleExit();
void displaySlots();

extern Vehicle parkingSlots[MAX_SLOTS];

#endif
