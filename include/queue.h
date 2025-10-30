#ifndef QUEUE_H
#define QUEUE_H
#include "parking.h"

#define MAX_QUEUE 10

void enqueue(Vehicle v);
Vehicle dequeue();
int isQueueEmpty();
int isQueueFull();
void displayQueue();

#endif
