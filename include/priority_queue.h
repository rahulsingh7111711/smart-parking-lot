#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "parking.h"

#define MAX_PQ 10

void pqEnqueue(Vehicle v);
Vehicle pqDequeue();
int isPQEmpty();
int isPQFull();
void displayPQ();

#endif
