#include <stdio.h>
#include <time.h>
#include "billing.h"
#include "fileio.h"   // for saving bill records

void generateBill(Vehicle v) {
    time_t exitTime = time(NULL);
    double duration = difftime(exitTime, v.entryTime) / 60.0; // duration in minutes
    double rate = v.isVIP ? 2.0 : 1.0; // rate per minute
    double amount = duration * rate;

    printf("\n==== BILL ====\n");
    printf("Vehicle: %s\n", v.vehicleNumber);
    printf("Owner: %s\n", v.ownerName);
    printf("Type: %s\n", v.isVIP ? "VIP" : "Normal");
    printf("Duration: %.2f minutes\n", duration);
    printf("Amount Due: ₹%.2f\n", amount);
    printf("================\n");

    // Save this billing record to file
    saveBill(v, amount);
}
