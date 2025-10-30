#include <stdio.h>
#include "priority_queue.h"

Vehicle pq[MAX_PQ];
int pqSize = 0;

int isPQEmpty() {
    return pqSize == 0;
}

int isPQFull() {
    return pqSize == MAX_PQ;
}

// Enqueue by priority: higher 'isVIP' = higher priority
void pqEnqueue(Vehicle v) {
    if (isPQFull()) {
        printf("Priority Queue full! Cannot add VIP vehicle.\n");
        return;
    }

    // Insert at end
    pq[pqSize++] = v;

    // Sort by priority (descending)
    for (int i = pqSize - 1; i > 0; i--) {
        if (pq[i].isVIP > pq[i - 1].isVIP) {
            Vehicle temp = pq[i];
            pq[i] = pq[i - 1];
            pq[i - 1] = temp;
        }
    }

    printf("VIP vehicle %s added to Priority Queue.\n", v.vehicleNumber);
}

// Remove highest priority vehicle
Vehicle pqDequeue() {
    Vehicle temp;
    if (isPQEmpty()) {
        printf("Priority Queue empty.\n");
        temp.vehicleNumber[0] = '\0';
        return temp;
    }
    temp = pq[0];

    // Shift all elements left
    for (int i = 0; i < pqSize - 1; i++)
        pq[i] = pq[i + 1];
    pqSize--;

    return temp;
}

void displayPQ() {
    if (isPQEmpty()) {
        printf("Priority Queue empty.\n");
        return;
    }

    printf("\n--- VIP Priority Queue ---\n");
    for (int i = 0; i < pqSize; i++) {
        printf("%s (%s)\n", pq[i].vehicleNumber,
               pq[i].isVIP ? "VIP" : "Normal");
    }
}
