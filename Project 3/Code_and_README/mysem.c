//Endi Xu
//CSCE351
//Project 3
//mysem 

#include <stdio.h>
#include <stdlib.h>
#include "mysem.h"
#include "mythread.h"
#include "queue.h"

//The assemble line for disable and enable the interrupt
#define DISABLE_INTERRUPTS() {  \
    asm("wrctl status, zero");  \
}

#define ENABLE_INTERRUPTS() {   \
    asm("movi et, 1");          \
    asm("wrctl status, et");    \
}

//This function is used to enqueue data to the queue
void bEnqueue(void *data, BQ *queue) {
    BE *elem;

    if ((elem = (BE *)malloc(sizeof(BE))) == NULL) {
        printf("Unable to allocate space!\n");
        exit(1);
    }

    elem->data = data;
    elem->next = NULL;

    if (queue->head == NULL) {
        queue->head = elem;
	} else {
        queue->tail->next = elem;
	}

    queue->tail = elem;

    queue->size++;
}

//This function is used to dequeue data from the queue
void *bDequeue(BQ *queue) {
    BE *elem;
    void *data = NULL;

    if (queue->size != 0) {
        elem = queue->head;

		if (queue->size == 1) {
            queue->tail = NULL;
		}

        queue->head = queue->head->next;

        queue->size--;
        data = elem->data;
        free(elem);
    }

    return data;
}

//This function is used to create a semaphore
mysem *mysem_create(int value) {
	
	//Allocate memory for the sem
	mysem *sem;
	sem = (mysem *)malloc(sizeof(mysem));

	//Get the initialize value of the semaphore
	sem->semCounter = value;
	
	//Get the number of waiting thread
	sem->numWaitingThread = 0;
	
	//This queue is used to hold block arrays and initialize it
	sem->queue = (BQ *) malloc(sizeof(BQ));
	sem->queue->head = NULL;
	sem->queue->tail = NULL;
	sem->queue->size = 0;

	return sem;
}

//This function is used to get the number of waiting thread
int mysem_waitCount(mysem *sem) {
	return sem->numWaitingThread;	
}

//This function is used to get the semaphore value
int mysem_value(mysem *sem) {
	return sem->semCounter;
}

//Release the semaphore
void mysem_up(mysem *sem) {
	DISABLE_INTERRUPTS();
	if (mysem_waitCount(sem) > 0) {
		//Release the thread
		TCB *threadBuffer = (TCB *) bDequeue(sem->queue);
		threadBuffer->state = READY;
	} else {
		//Plus the value of the semaphore
		sem->semCounter++;
	}
	ENABLE_INTERRUPTS();
}

//Lock the semaphore
void mysem_down(mysem *sem) {
	DISABLE_INTERRUPTS();
	if(mysem_value(sem) > 0) {
		//Minus the value of the semaphore 
		sem->semCounter--;
		ENABLE_INTERRUPTS();
	} else {
		//Block the thread
		TCB *threadBuffer = getCurrentThread();
		mythreadBlock(threadBuffer);
		bEnqueue(threadBuffer, sem->queue);
		sem->numWaitingThread = sem->queue->size;
		ENABLE_INTERRUPTS();
		//Keep blocking it
		while(threadBuffer->state == BLOCKED);
	}
}

//delete the semaphore
void mysem_delete(mysem *sem) {
	DISABLE_INTERRUPTS();
	free(sem->queue);
	free(sem);
	ENABLE_INTERRUPTS();
}
