//Endi Xu
//CSCE351
//Project 3
//Header File of the mythread
//Original Author: Dongyuan Zhan

//Define the thread states
enum threadState {NEW, READY, RUNNING, BLOCKED, TERMINATED, NUM_TSTATES};

//Define the TCB
typedef struct {
	unsigned int thread_ID;
	unsigned int *stack;
	unsigned int *stackSize;
	unsigned int *stackPointer;
	enum threadState state;
} TCB;

//Function Prototype
TCB *mythreadCreate(unsigned int thread_ID, unsigned int stackSize, void (*mythread)(unsigned int thread_ID));

void mythreadStart(TCB *thread_pointer);

void mythreadJoin(TCB *thread_pointer);

void mythreadBlock(TCB *thread_pointer);

void mythreadTerminate(TCB *thread_pointer);

void *mythreadScheduler(void *context);

unsigned int mythread_isQempty();

void mythreadCleanup();

TCB *getCurrentThread();
