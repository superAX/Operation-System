There are total four source codes in my file. There are "TCB.h", "TCB.C", "main.c" and "MyScheduler.S"

The "TCB.h" and "TCB.c" is the header file defined by myself. It will be include in the main.c.
It contains the structure definition of the TCB and the functions related with it.
The functions includes:
	void mythread(int thread_id);
	TCB* mythread_create();
	void mythread_destroy(TCB *tcb);
	void mythread_join(TCB *tcb);
	int getRunQsize();

In the "mainc.c", it will perfom the main functions. And the thread scheduler function is also in it.
The function includes:
	void os_prototype();
	void *mythread_scheduler(void *context);
	alt_u32 myinterrupt_handler(void *context);
	int global_flag_checker();

The code can be compiled and run through "Nios II 12.0sp2 Software Build Tools for Eclipse"
