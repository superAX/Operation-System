//Endi Xu
//CSCE351
//Project 3
//Main

#include <stdio.h>

#include "alarm.h"
#include "mythread.h"
#include "mysem.h"

//Number of threads of bee
#define NUM_THREADS_BEE 10
//Number of threads of bear
#define NUM_THREADS_BEAR 1
//The pot's size
#define H 30

//Define a delay
#define MAX 100000

//Initialize two semaphores
static mysem *mutex;
static mysem *pot_full;

//Initialize the pot to be 0 first
int portions = 0;

//This the bear's process
void BEAR(unsigned int thread_ID) {
	int i = 0;
	while(i < 5) {
		mysem_down(pot_full);

		//The bear eat all the honeys
		portions = 0;
		
		//Calculate the honey eating times
		i++;
		printf("The bear finished eating. %d out of 5\n", i);
		
		mysem_up(mutex);
		//printf("UP!Now the value is %d for mutex.\n", mutex->semCounter);

		//This Loop is used for delay
		int j;
		for(j = 0; j < MAX; j++);

		if(i == 5) {
			mysem_delete(mutex);
			mysem_delete(pot_full);
			printf("Semaphores have been destroyed!!!\n");
		}
	}
}

//This is bee's Process
void BEE(unsigned int thread_ID) {
	//Each Bee could only gather 15 portions
	int i = 1;
	while(i <= 15) {
		//Lock the mutex
		mysem_down(mutex);
		//Add one portion
		portions ++;
		printf("One portion is added by Bee No. %d. %d out of 15.\n", thread_ID, i);
		printf("Now the pot is %d.\n", portions);
		//The bee have gathered one portion
		i++;

		//Check if the pot is full or not
		if(portions == H) {
			mysem_up(pot_full);
		} else {
			mysem_up(mutex);
		}
		
		//This Loop is used for delay
		int j;
		for(j = 0; j < MAX; j++);
	}
}
    
void os_primitive() {
    
	unsigned int i;
    TCB *threadPointer;
    
	//Create the semaphores
	mutex = mysem_create(1);
	pot_full = mysem_create(0);
	
	//Create and Join the thread for 10 Bees
    for (i = 0; i < NUM_THREADS_BEAR; i++) {
        threadPointer = mythreadCreate(i, 4096, BEAR);   // 4B * 4096 entries = 16KB
        mythreadStart(threadPointer);
        mythreadJoin(threadPointer);
    }
	
		//Create and Join the thread for the Bear
	for (i = NUM_THREADS_BEAR; i < NUM_THREADS_BEE + NUM_THREADS_BEAR; i++) {
        threadPointer = mythreadCreate(i, 4096, BEE);   // 4B * 4096 entries = 16KB
        mythreadStart(threadPointer);
        mythreadJoin(threadPointer);
    }
    
    if (start_alarm_succeed()) { 
        printf ("Start the alarm successfully\n");
    } else {
        printf ("Unable to start the alarm\n");
	}
	
    //Constantly printing this message after all the things all done
    while (1) {
        printf ("This is the OS primitive for my exciting CSE351 course projects!\n");
        
        //Here is used for delay
        for (i = 0; i < MAX; i++);
    }
}

int main() {
    os_primitive();
    return 0;
}
