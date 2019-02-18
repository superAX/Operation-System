Details of the source code:
My source code is composed by three functions.

1. "void main();" 
It is used as a main function. The prototype_os function will be called in the main.

3. "void prototype_os(param_list);"
This function will executed in an infinite loop and continously print out a senctence.
Also, a timer will be set and a "alt_alarm_start()" function will be called in this function.
Then the myinterrupt_handler can be called periodlly to interrupt the original loop.

2. "alt_u32 myinterrupt_handler(void * context);" 
It is used as a call back function. 
As metioned above, it will be called periodlly ny the "prototype_os();" to interrupt itself.

How to compile and run,

After the board is connected to the computer and the CPU is downloaded to the board. 
We can write, compile and run the program through the "Nios II 12.0sp2 Software Build Tools for Eclipse".

   