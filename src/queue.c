#include <stdio.h>
#include "queue.h"

Vehicle queue[MAX_QUEUE];
int front = -1, rear = -1;

int isQueueEmpty() {
    return front == -1;
}

int isQueueFull() {
    return (rear + 1) % MAX_QUEUE == front;
}

void enqueue(Vehicle v) {
    if (isQueueFull()) {
        printf("Queue full! Cannot add more vehicles.\n");
        return;
    }
    if (isQueueEmpty()) front = 0;
    rear = (rear + 1) % MAX_QUEUE;
    queue[rear] = v;
    printf("Added %s to waiting queue.\n", v.vehicleNumber);
}

Vehicle dequeue() {
    Vehicle temp;
    if (isQueueEmpty()) {
        printf("Queue empty!\n");
        temp.vehicleNumber[0] = '\0';
        return temp;
    }
    temp = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX_QUEUE;
    return temp;
}

void displayQueue() {
    if (isQueueEmpty()) {
        printf("Queue empty.\n");
        return;
    }
    printf("\n--- Waiting Queue ---\n");
    int i = front;
    while (1) {
        printf("%s (%s)\n", queue[i].vehicleNumber,
               queue[i].isVIP ? "VIP" : "Normal");
        if (i == rear) break;
        i = (i + 1) % MAX_QUEUE;
    }
}
