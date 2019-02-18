//Endi Xu
//CSCE351 
//Project 3
//alarm
//Original Author: Dongyuan Zhan

#include <stdio.h>
#include <sys/alt_alarm.h>

#include "alarm.h"
#include "mythread.h"

//Define a local alarm instance 
static alt_alarm alarm;

//Define a global flag for the alarm interrupt 
unsigned int alarmflag = 0;

//Test if "alarmflag" is set 
unsigned int is_alarmflag_set() {
    return alarmflag != 0;
}

//Reset "alarmflag" 
void reset_alarmflag() {
    alarmflag = 0;
}

//The alarm interrupt handler
alt_u32 myinterrupt_handler(void* context) {
	
    alarmflag = 1;
    
	if(mythread_isQempty()) {
        printf("Interrupted by the DE2 timer!\n");
    }
    
    return alt_ticks_per_second();
}

unsigned int start_alarm_succeed() {
    return alt_alarm_start(&alarm, alt_ticks_per_second(), myinterrupt_handler, NULL) >= 0;
}
