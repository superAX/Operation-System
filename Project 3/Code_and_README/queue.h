//Endi Xu
//CSCE351
//Project 3
//Header file of the queue
//Original Author: Dongyuan Zhan

//Define the struct of each element in queue
typedef struct elementType {
    void *data;
    struct elementType *next;
} Etype;

//Define the struct of  queue
typedef struct queueType {
    Etype *head;
    Etype *tail;
    unsigned int size;
} Qtype;

//Function prototype
void enqueue(void *data);

void *dequeue();

unsigned int getQsize();
