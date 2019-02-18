Endi Xu
CSCE351 Project 3 
README File

PART I

There are 10 source codes files for this project. The following is the list.
1. alarm.h
2. alarm.c
3. queue.h
4. queue.c
5. mythread.h
6. mythread.c
7. exception_handler.S 
8. mysem.h
9. mysem.c
10. project_3_main.c

The "alarm.h" and "alarm.c" are the header file provided by the professor and revised by me. 
It is used for triggering interrupting.
It is included in the "mythread.c" and "project_3_main.c".
The function of this header file included:
	unsigned int is_alarmflag_set(); 
	void reset_alarmflag();
	alt_u32 myinterrupt_handler(void* context);
	unsigned int start_alarm_succeed();

The "queue.h" and "queue.c" are the header file provided by the professor and revised by me. 
It is used for storing running threads.
It is included in the "mythread.c".
The function of this header file included:
	void enqueue(void *data);
	void *dequeue();
	unsigned int getQsize();

The "mythread.h" and "mythread.c" are the header file provided by the professor revised by me. 
It is used for creating a thread control block type called "TCB". It is also used to schedule each thread.
It is included in the "alarm.c", "mysem.c" and "project_3_main.c".
The function of this header file included:
	TCB *mythreadCreate(unsigned int thread_ID, unsigned int stackSize, void (*mythread)(unsigned int thread_ID));
	void mythreadStart(TCB *thread_pointer);
	void mythreadJoin(TCB *thread_pointer);
	void mythreadBlock(TCB *thread_pointer);
	void mythreadTerminate(TCB *thread_pointer);
	void *mythreadScheduler(void *context);
	unsigned int mythread_isQempty();
	void mythreadCleanup();
	TCB *getCurrentThread();

The "mythread.h" and "mythread.c" are the header file created by myself.
It is used for creating a semaphore type called "mysem". It also includes the basic operation of semaphore like sem up, sem down, sem delete.
It is included in the "project_3_main.c".
The function of this header file included:
	void bEnqueue(void *data, BQ *queue);
	void *bDequeue(BQ *queue);
	mysem *mysem_create(int value);
	void mysem_up(mysem *sem);
	void mysem_down(mysem *sem);
	void mysem_delete(mysem *sem);
	int mysem_waitCount(mysem *sem);
	int mysem_value(mysem *sem);

The "project_3_main.c" is the main function created by myself.
It performs as a main function. The bear process and bee process are defined inside it.
The function in the main included:
	void BEAR(unsigned int thread_ID);
	void BEE(unsigned int thread_ID);
	void os_primitive();
	int main();

PART II

Way to Compile and Run the Program:
The code can be compiled and run through "Nios II 12.0sp2 Software Build Tools for Eclipse" with the DE2 BOARD