#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int n = 3; // as an example
  pid_t pid;

  // Open a CSV file for writing only if it doesn't exist
  FILE *file = fopen("tree.csv", "a");

  fprintf(file, "PID,Parent_PID\n");

  for (int i = 0; i < n; i++)
  {
    pid = fork();

    fprintf(file, "%d,%d\n", getpid(), getppid());
    // No break, so child will continue to fork as well
  }

  fclose(file);
  return 0;
}
