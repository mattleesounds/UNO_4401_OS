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

  fprintf(file, "PID,ParentPID\n");              // CSV header
  fprintf(file, "%d,%d\n", getpid(), getppid()); // Write the root process

  fclose(file);

  // Loop through each layer of the tree
  for (i = 0; i < n; i++)
  {
    int pid1 = fork(); // First child
    if (pid1 == 0)
    {
      // In first child process
      file = fopen("tree.csv", "a");
      fprintf(file, "%d,%d\n", getpid(), getppid());
      fclose(file);
    }
    else
    {
      int pid2 = fork(); // Second child
      if (pid2 == 0)
      {
        // In second child process
        file = fopen("tree.csv", "a");
        fprintf(file, "%d,%d\n", getpid(), getppid());
        fclose(file);
      }
      else
      {
        // In parent process
        wait(NULL); // Wait for first child
        wait(NULL); // Wait for second child
        exit(0);    // Parent process exits
      }
    }
  }
}
