/*
 * Fork Demo #5.  Parent forks off two
 * children and waits for each without
 * blocking.  Uses waitpid.
 *
 * Example for CISC 220, Fall 2020
 * author: M. Lamb, adapted by A. McLeod
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
  /* Fork off first child process */
  pid_t child1 = fork();
  if (child1 == 0) {
    /* This is the first child process.  Loops for 10 seconds,
     * then prints a message and exits.*/
    #define CHILD1_REPEATS 10
    int i;
    for (i = 1; i <= CHILD1_REPEATS; i++) {
      sleep(1);
      printf("child 1: %d of %d\n", i, CHILD1_REPEATS);
    } /* end for */
    printf("child 1 finishing.\n");
    exit(EXIT_SUCCESS);
  }
  else if (child1 < 0) {
    fprintf(stderr, "unable to create the first child process\n");
    exit(EXIT_FAILURE);
  } /* end if */

  printf("first child process is %d\n", child1);

  /* Fork off second child process */
  pid_t child2 = fork();
  if (child2 == 0) {
    /* This is the second child process.  Loops for 6 seconds,
     * then prints a message and exits.*/
    #define CHILD2_REPEATS 6
    int i;
    for (i = 1; i <= CHILD2_REPEATS; i++) {
      sleep(1);
      printf("child 2: %d of %d\n", i, CHILD2_REPEATS);
    } /* end for */
    printf("child 2 finishing.\n");
    exit(EXIT_SUCCESS);
  }
  else if (child2 < 0) {
    fprintf(stderr, "unable to create the second child process\n");
    exit(EXIT_FAILURE);
  } /* end if */

  printf("second child process is %d\n", child2);

  /* Parent process loops until both children are done */
  int done1 = FALSE;
  int done2 = FALSE;
  pid_t waitResult; /* result from a waitpid call */
  while (!done1 || !done2) {
    /* sleep for a second so parent is not using up all
     * the processor time with constant calls to waitpid */
    sleep(1);
    /* check the status of each child */
    if (!done1) {
      waitResult = waitpid(child1, NULL, WNOHANG);
      if (waitResult != 0) {
	/* child1 is finished now */
	printf("parent notes child1 is finished\n");
	done1 = TRUE;
      } /* end if */
    } /* end if */
    if (!done2) {
      waitResult = waitpid(child2, NULL, WNOHANG);
      if (waitResult != 0) {
	/* child2 is finished now */
	printf("parent notes child2 is finished\n");
	done2 = TRUE;
      } /* end if */
    } /* end if */
  } /* end while */
  printf("Both children are done.\n");

  exit(EXIT_SUCCESS);
} /* end main */
