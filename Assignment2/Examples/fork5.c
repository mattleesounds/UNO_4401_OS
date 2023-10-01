#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  int n = 3;
  int pids[2 * n - 1];
  int ppids[2 * n - 1];
  int index = 0;

  for (int i = 0; i < n; i++)
  {
    if (i != n - 1) // Don't fork on the last iteration
    {
      if (fork() == 0) // Child
      {
        pids[index] = getpid();
        ppids[index] = getppid();
        index++;
        break; // Child breaks out of the loop and does not fork
      }
    }

    // This will be executed by the parent in every loop iteration
    // and by the child in the last iteration
    pids[index] = getpid();
    ppids[index] = getppid();
    index++;
  }

  // Let the original parent process handle writing to the file
  if (getpid() == pids[0])
  {
    FILE *file = fopen("tree.csv", "w");
    fprintf(file, "PID,ParentPID\n");
    for (int j = 0; j < index; j++)
    {
      fprintf(file, "%d,%d\n", pids[j], ppids[j]);
    }
    fclose(file);
  }

  return 0;
}
