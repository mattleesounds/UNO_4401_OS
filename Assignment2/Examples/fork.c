#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
  int pid;
  int parentPID;
  int pid2;
  int parentPID2;

  pid = getpid();
  parentPID = getppid();

  printf("1. Test getpid() and getppid() \n");
  printf("PID: %d \n", pid);
  printf(" Parent PID: %d \n", parentPID);

  fork();
  pid2 = getpid();
  parentPID2 = getppid();

  if (pid == pid2)
  {
    waitpid(-1, NULL, 0);
  }
  printf("\n\n2. Test fork\n");
  printf("PID:%d \n", pid2);
  printf("Parent PID: %d \n", parentPID2);
}