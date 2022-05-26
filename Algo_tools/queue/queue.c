#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, Agnode_t* n) {
  //if (q->rear == SIZE - 1)
    //printf("\nQueue is Full!!");
 // else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = n;
  //}
}

// Removing elements from queue
Agnode_t* dequeue(struct queue* q) {
  Agnode_t* item;
  if (isEmpty(q)) {
    //printf("Queue is empty");
    item = NULL;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      //printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
/*void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}*/
