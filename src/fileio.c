#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fileio.h"
#include "billing.h"
#include "parking.h"

#define DATA_FILE "data/parking_records.txt"
#define BILL_FILE "data/billing_log.txt"

extern Vehicle parkingSlots[MAX_SLOTS];

void saveParkingData() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("Error saving parking data!\n");
        return;
    }

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (parkingSlots[i].vehicleNumber[0] != '\0') {
            fprintf(fp, "%d %s %s %d %ld\n",
                    parkingSlots[i].slotNumber,
                    parkingSlots[i].vehicleNumber,
                    parkingSlots[i].ownerName,
                    parkingSlots[i].isVIP,
                    parkingSlots[i].entryTime);
        }
    }

    fclose(fp);
    printf("Parking data saved successfully.\n");
}

void loadParkingData() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    // Clear all existing slots
    for (int i = 0; i < MAX_SLOTS; i++) {
        parkingSlots[i].vehicleNumber[0] = '\0';
        parkingSlots[i].isVIP = 0;
        parkingSlots[i].slotNumber = i + 1;
        parkingSlots[i].entryTime = 0;
    }

    int slot, isVIP;
    char vnum[20], name[30];
    time_t entryTime;

    while (fscanf(fp, "%d %s %s %d %ld",
                  &slot, vnum, name, &isVIP, &entryTime) == 5) {
        if (slot >= 1 && slot <= MAX_SLOTS) {
            Vehicle v;
            v.slotNumber = slot;
            v.isVIP = isVIP;
            v.entryTime = entryTime;
            snprintf(v.vehicleNumber, sizeof(v.vehicleNumber), "%s", vnum);
            snprintf(v.ownerName, sizeof(v.ownerName), "%s", name);
            parkingSlots[slot - 1] = v;
        }
    }

    fclose(fp);
    printf("Previous parking data loaded successfully.\n");
}

void saveBill(Vehicle v, double amount) {
    FILE *fp = fopen(BILL_FILE, "a");
    if (!fp) {
        printf("Error opening billing file!\n");
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = '\0'; // remove newline

    fprintf(fp, "%s | %s | %s | ₹%.2f | %s\n",
            v.vehicleNumber,
            v.ownerName,
            v.isVIP ? "VIP" : "Normal",
            amount,
            timestamp);

    fclose(fp);
}

void generateReport() {
    FILE *fp = fopen(BILL_FILE, "r");
    if (!fp) {
        printf("No billing data available.\n");
        return;
    }

    printf("\n=== PARKING LOT REPORT ===\n");
    printf("Vehicle No | Owner | Type | Amount | Timestamp\n");
    printf("---------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    printf("\n---------------------------------------------------\n");
}
