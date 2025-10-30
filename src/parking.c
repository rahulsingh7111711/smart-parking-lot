#include <stdio.h>
#include <string.h>
#include <time.h>
#include "parking.h"
#include "queue.h"
#include "priority_queue.h"
#include "billing.h"


Vehicle parkingSlots[MAX_SLOTS];

void initializeParking() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        parkingSlots[i].slotNumber = i + 1;
        parkingSlots[i].vehicleNumber[0] = '\0';
        parkingSlots[i].isVIP = 0;
    }
}

void vehicleEntry() {
    Vehicle v;
    printf("\nEnter vehicle number: ");
    scanf("%s", v.vehicleNumber);
    printf("Enter owner name: ");
    scanf("%s", v.ownerName);
    printf("Is VIP? (1 = Yes, 0 = No): ");
    scanf("%d", &v.isVIP);
    v.entryTime = time(NULL);

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (parkingSlots[i].vehicleNumber[0] == '\0') {
            parkingSlots[i] = v;
            printf("Vehicle parked in slot %d.\n", parkingSlots[i].slotNumber);
            return;
        }
    }

    if (v.isVIP)
        pqEnqueue(v);
    else
        enqueue(v);

}

void vehicleExit() {
    char vehicleNum[20];
    printf("\nEnter vehicle number to exit: ");
    scanf("%s", vehicleNum);

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (strcmp(parkingSlots[i].vehicleNumber, vehicleNum) == 0) {
            printf("Vehicle %s exiting from slot %d.\n", vehicleNum, i + 1);

            // Generate bill before clearing slot
            generateBill(parkingSlots[i]);

            // Clear the slot
            parkingSlots[i].vehicleNumber[0] = '\0';
            printf("Slot %d is now free.\n", i + 1);

            // Priority reallocation: VIPs first, then normal queue
            if (!isPQEmpty()) {
                Vehicle nextVIP = pqDequeue();
                parkingSlots[i] = nextVIP;
                printf("Assigned freed slot %d to VIP vehicle %s.\n", 
                       i + 1, nextVIP.vehicleNumber);
            } else if (!isQueueEmpty()) {
                Vehicle nextNormal = dequeue();
                parkingSlots[i] = nextNormal;
                printf("Assigned freed slot %d to waiting vehicle %s.\n", 
                       i + 1, nextNormal.vehicleNumber);
            } else {
                printf("No waiting vehicles in queue.\n");
            }

            return;
        }
    }
    printf("Vehicle not found in parking.\n");
}


void displaySlots() {
    printf("\n--- Parking Slots ---\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (parkingSlots[i].vehicleNumber[0] == '\0')
            printf("Slot %2d: Free\n", i + 1);
        else
            printf("Slot %2d: %s (%s)\n", i + 1, parkingSlots[i].vehicleNumber,
                   parkingSlots[i].isVIP ? "VIP" : "Normal");
    }
}
