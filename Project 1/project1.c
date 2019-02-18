//Endi Xu
//Project 1
//Code


#include <stddef.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"

#define ALARMTICKS(x) ((alt_ticks_per_second()*(x))/10)

void main() {
   //Call the prototype_os
   prototype_os();
}

//when interrupt is occurred, this function will be called
alt_u32 myinterrupt_handler(void * context) {
	alt_printf("Interrupted by the timer!\n");
	return ALARMTICKS(20);
}

void prototype_os(param_list) {
    //Here: initialize the timer and its interrupt handler
	static alt_alarm alarm;
	//Here is used to call back the function
	alt_alarm_start(&alarm, alt_ticks_per_second(), myinterrupt_handler, NULL);
	//Here is to cause the infinite loop
	alt_u32 i = 0;
    while(i == 0) {
        alt_printf("This is the prototype os for my exciting CSE351 course projects!\n");
        alt_u32 j;
        for(j = 0 ; j < 200000; j++);  //this loop is used for delay
    }
 }
  
