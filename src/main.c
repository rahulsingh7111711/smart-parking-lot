#include <stdio.h>
#include "parking.h"
#include "queue.h"
#include "priority_queue.h"
#include "billing.h"
#include "fileio.h"
#include "utils.h"

int main() {
    int choice;

    printf("=========================================\n");
    printf("   SMART PARKING LOT MANAGEMENT SYSTEM   \n");
    printf("=========================================\n");

    // ✅ Initialize parking slots first
    initializeParking();

    // ✅ Then load previous parking data (if available)
    loadParkingData();

    while (1) {
        printf("\n==== MAIN MENU ====\n");
        printf("1. Vehicle Entry\n");
        printf("2. Vehicle Exit\n");
        printf("3. View Parking Status\n");
        printf("4. Generate Report\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                vehicleEntry();
                break;

            case 2:
                vehicleExit();
                break;

            case 3:
                displaySlots();
                break;

            case 4:
                generateReport();
                break;

            case 5:
                printf("\nSaving data and exiting...\n");
                saveParkingData();
                printf("Thank you for using the Smart Parking System!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
