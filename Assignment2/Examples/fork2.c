#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main()
{
  int n = 3;
  int i;

  FILE *file = fopen("tree.csv", "w");

  fprintf(file, "PID,ParentPID\n");
  fprintf(file, "%d,%d\n", getpid(), getppid());

  fclose(file);

  for (i = 0; i < n; i++)
  {
    int pid1 = fork();
    if (pid1 == 0)
    {

      file = fopen("tree.csv", "a");
      fprintf(file, "%d,%d\n", getpid(), getppid());
      fclose(file);
    }
    else
    {
      int pid2 = fork();
      if (pid2 == 0)
      {
        file = fopen("tree.csv", "a");
        fprintf(file, "%d,%d\n", getpid(), getppid());
        fclose(file);
      }
      else
      {
        wait(NULL);
        wait(NULL);
        exit(0);
      }
    }
  }
}
