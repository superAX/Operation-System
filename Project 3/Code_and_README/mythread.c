//Endi Xu
//CSCE 351
//Project 3
//mythread
//Original Author: Dongyuan Zhan

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "alarm.h"
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

//Refer to the current running thread 
static TCB *currentThread = NULL;

//Pointing to the stack/context of main() 
static unsigned int *mainSP = NULL;

//Function used to create the thread
TCB *mythreadCreate(unsigned int thread_ID, unsigned int stackSize, void (*mythread)(unsigned int thread_ID)) {
	
    unsigned int *tmp_ptr;
    
    //Initialize a threadPointer and allocate memory for it
    TCB *threadPointer;    
    threadPointer = (TCB *)malloc(sizeof(TCB));
    
	//Check for the exception
	if (threadPointer == NULL) {
        printf("Unable to allocate space!\n");
        exit(1);
    }
    
    // initialize the thread's tcb 
    threadPointer->thread_ID = thread_ID;
    threadPointer->stack = (unsigned int *)malloc(sizeof(unsigned int) * stackSize);
    
	//Check the exception
	if (threadPointer->stack == NULL) {
        printf("Unable to allocate space!\n");
        exit(1);
    }
	
    threadPointer->stackSize = stackSize;
    threadPointer->stackPointer = (unsigned int *)(threadPointer->stack + stackSize - 19);
    threadPointer->state = NEW;
    
    // initialize the thread's stack 
    tmp_ptr = threadPointer->stackPointer;
    tmp_ptr[18] = (unsigned int)mythread;                               //ea
    tmp_ptr[17] = 1;                                                    //estatus
    tmp_ptr[5] = thread_ID;                                             //r4
    tmp_ptr[0] = (unsigned int)mythreadCleanup;                         //ra
    tmp_ptr[-1] = (unsigned int)(threadPointer->stack + stackSize);		//fp
           
    return threadPointer;
	
}

//Make the thread to ready
void mythreadStart(TCB *threadPointer) {
    threadPointer->state = READY;
}

//Join each thread
void mythreadJoin(TCB *threadPointer) {
    enqueue((void *)threadPointer);
}

//Make the thread to block
void mythreadBlock(TCB *threadPointer) {
    threadPointer->state = BLOCKED;
}

//Make the thread to be terminated
void mythreadTerminate(TCB *threadPointer) {
    threadPointer->state = TERMINATED;
}

void *mythreadScheduler(void *context) {
	
    if (getQsize() > 0) {
		
		if (currentThread != NULL) {

				//Check if it is blocked
				if(currentThread->state == BLOCKED) {
					currentThread->stackPointer = (unsigned int *)context;
					enqueue(currentThread);
				} else {
					currentThread->state = READY;
					currentThread->stackPointer = (unsigned int *)context;
					enqueue(currentThread);
				}

		} else if (mainSP == NULL) {
			
			mainSP = (unsigned int *)context;
		
		}
        
        currentThread = (TCB *)dequeue();
        
		//If the thread is blocked, keep blocking it
        if(currentThread->state != BLOCKED) {
        	currentThread->state = RUNNING;
        }

        context = (void *)(currentThread->stackPointer);
		
	} else if (currentThread == NULL && mainSP != NULL) {        
    
		context = (void *)mainSP;
    
	}

    return context;

}

unsigned int mythread_isQempty() {
    return (getQsize() == 0) && (currentThread == NULL);
}

void mythreadCleanup() {
    DISABLE_INTERRUPTS();
    mythreadTerminate(currentThread);
    free(currentThread->stack);
    free(currentThread);
    currentThread = NULL;
    ENABLE_INTERRUPTS();
    while(1);
}

TCB *getCurrentThread() {
	return currentThread;
}


