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
  pid_t proc;

  // Parent process writes after all forks.
  pid = getpid();
  ppid = getppid();
  FILE *file = fopen("tree.csv", "a");
  fprintf(file, "%d,%d\n", pid, ppid);
  fclose(file);

  for (i = 0; i < n; i++)
  {
    proc = fork();
    if (proc == 0) // Child process
    {
      pid = getpid();
      ppid = getppid();

      FILE *file = fopen("tree.csv", "a");
      fprintf(file, "%d,%d\n", pid, ppid);
      fclose(file);

      exit(0); // Important: exit child process after writing to the file.
    }
  }
}
