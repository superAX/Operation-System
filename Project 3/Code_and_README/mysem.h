//Endi Xu
//CSCE351
//Project 3
//Header file of the mysem

//Define the struct of each element in queue
typedef struct blockElement {
    void *data;
    struct blockElement *next;
} BE;

//Define the struct of  queue
typedef struct blockQueue {
    BE *head;
    BE *tail;
    unsigned int size;
} BQ;

//define the struct of semaphore
typedef struct {
	int semCounter;
	int numWaitingThread;
	BQ *queue;
} mysem;


//Function Prototype
void bEnqueue(void *data, BQ *queue);

void *bDequeue(BQ *queue);

mysem *mysem_create(int value);

void mysem_up(mysem *sem);

void mysem_down(mysem *sem);

void mysem_delete(mysem *sem);

int mysem_waitCount(mysem *sem);

int mysem_value(mysem *sem);

