#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main()
{
  int n = 3;
  int i;
  int pid;
  int ppid;

  FILE *file = fopen("tree.csv", "w");

  /*  fprintf(file, "PID,ParentPID\n");
   fprintf(file, "%d,%d\n", getpid(), getppid());

   fclose(file); */

  for (i = 0; i < n; i++)
  {
    fork();
    pid = getpid();
    ppid = getppid();
    file = fopen("tree.csv", "a");
    fprintf(file, "%d,%d\n", pid, ppid);
    fclose(file);
  }
}
