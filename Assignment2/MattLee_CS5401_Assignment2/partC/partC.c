#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int n;
  int pid;

  FILE *file = fopen("pids.csv", "w");

  printf("Enter the number of forks: ");
  scanf("%d", &n);

  fprintf(file, "%d,%d\n", getpid(), getppid());

  for (int i = 1; i <= n; i++)
  {
    fflush(file);
    pid = fork();

    if (pid == 0)
    {
      fprintf(file, "%d,%d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
      waitpid(pid, NULL, 0);
      break;
    }
  }

  fclose(file);

  return 0;
}
