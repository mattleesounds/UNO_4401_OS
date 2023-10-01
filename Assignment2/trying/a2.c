#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int n;
  int pid;

  FILE *file = fopen("pids.csv", "w");

  printf("Enter the value of n: ");
  scanf("%d", &n);

  fprintf(file, "%d,%d\n", getpid(), getppid());

  for (int i = 1; i <= n; i++)
  {
    // Flushing the file buffer avoids duplicate lines
    fflush(file);
    pid = fork();

    // If pid is zero, process is a child
    if (pid == 0)
      fprintf(file, "%d,%d\n", getpid(), getppid());
  }

  // Sleep for 1 second to allow all processes to finish writing to the file
  sleep(1);

  fclose(file);

  return 0;
}