#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main()
{
  int n = 3; // Number of layers you want to create
  int i;

  // Open file in write mode for the original process
  FILE *file = fopen("tree.csv", "w");

  fprintf(file, "PID,ParentPID\n"); // CSV header

  fclose(file);

  for (i = 0; i < n; i++)
  {
    int pid = fork();

    int current_pid = getpid();
    int parent_pid = getppid();

    // Open file in append mode for each process
    file = fopen("tree.csv", "a");

    fprintf(file, "%d,%d\n", current_pid, parent_pid);

    fclose(file);

    // Parent waits for the child to complete
    if (pid > 0)
    {
      wait(NULL);
    }
  }
}
