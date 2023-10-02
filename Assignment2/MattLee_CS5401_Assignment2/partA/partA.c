#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int n;
  int pid;

  FILE *file = fopen("partA(n=7).csv", "w");

  printf("Enter the number of forks: ");
  scanf("%d", &n);

  fprintf(file, "%d,%d\n", getpid(), getppid());

  for (int i = 1; i <= n; i++)
  {
    fflush(file);
    pid = fork();

    // If pid is zero, process is a child
    if (pid == 0)
      fprintf(file, "%d,%d\n", getpid(), getppid());
  }

  sleep(1);

  fclose(file);

  return 0;
}