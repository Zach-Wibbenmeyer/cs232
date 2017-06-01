/******************************************************************
 * Zach Wibbenmeyer                                               *
 * Professor Norman                                               *
 * CS232 - Program 1                                              *
 ******************************************************************/



// include appropriate libraries
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// global variables

// char variable for the default message
char *message = "\nThis is an annoying message";

// char variable for when the user presses control-c
char *disable = "\nHaha this doesn't work!!!";

// bool for toggling interrupts
bool interrupt = false;

// default time
int time = 5;


/* printMessage() - method that handles printing the default message
 * @param: sign (type -> int)
 * @return: void
 */
void printMessage(int sign) {
    printf("%s\n", message);
	  alarm(time);
}

/* disableControl() - disables Cntl-C
 * @param: sign (type -> int)
 * @return: void
 */
void disableControl(int sign) {
	  printf("%s\n", disable);
}


// main program. takes in argc (type -> int) and *argv[] (type -> char)
int main (int argc, char *argv[]) {

    // for the for loop
    int i;

    printf("\ncmdline args count = %d", argc);

    printf("\nexe name = %s", argv[0]);

    for (i = 0; i < argc; i++) {
        printf("\narg%d = %s\n", i, argv[i]);

        // exit if the arguments are less than 1
       	if (argc < 1) {
            printf("\nQuitting the program");
       		  return 0;
       	}
        // enable interrupts
       	else if (strcmp(argv[i], "+i") == 0) {
       		  interrupt = true;
       	}
        // disable interrupts
		    else if (strcmp(argv[i], "-i") == 0) {
			      interrupt = false;
		    }
        // change the delay between displaying the annoying message
       	else if (strcmp(argv[i], "+t") == 0) {
       	    time = atoi(argv[i+1]);
       	}
        // input a message of your own
    	  else if (strcmp(argv[i], "-m") == 0) {
    		    message = argv[i+1];
    	  }
    }

    // disable Cntl-C if interrupts are enabled
    if (interrupt) {
        signal(SIGINT, disableControl);
    }

    // bind the handler to the signal
    signal(SIGALRM, printMessage);

    // loop through to send the annoying message
    for (;;) {
    	  alarm(time);
    	  pause();
    }

    printf("\n");
    return 0;
}
