#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int n, i;
  pid_t child;
  FILE *fp;

  printf("Enter the number of processes to create: ");
  scanf("%d", &n);

  fp = fopen("processes.csv", "w");
  for (i = 0; i < n; i++)
  {
    child = fork();
    printf("Child process ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid());
    fprintf(fp, "%d,%d\n", getpid(), getppid());
    return 0;
  }

  fclose(fp);

  return 0;
}