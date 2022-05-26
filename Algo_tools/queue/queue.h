#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#define SIZE 500

struct queue {
  Agnode_t* items[SIZE];
  int front;
  int rear;

};


struct queue* createQueue();
void enqueue(struct queue* q, Agnode_t* n);
Agnode_t* dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);


#endif
