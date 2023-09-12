#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  int n, i;
  pid_t *children; // Array to hold child process IDs
  int status;
  FILE *fp;

  printf("Enter the value for n: ");
  scanf("%d", &n);

  children = malloc(n * sizeof(pid_t)); // Allocate memory for child process IDs

  for (i = 0; i < n; i++)
  {
    pid_t pid = fork();
    if (pid == 0)
    {          // Child process
      exit(0); // Child process exits immediately
    }
    else if (pid > 0)
    {                    // Parent process
      children[i] = pid; // Store child process ID
    }
    else
    {
      printf("Fork failed.\n");
      return 1;
    }
  }

  // Open the file in the parent process after all forks are done
  fp = fopen("output.json", "w");
  fprintf(fp, "{\n  \"processes\": [\n");

  // Wait for each child and collect their data
  for (i = 0; i < n; i++)
  {
    waitpid(children[i], &status, 0); // Wait for the specific child to terminate
    fprintf(fp, "    {\"ProcessID\": %d, \"ParentProcessID\": %d}", children[i], getpid());
    if (i < n - 1)
    {
      fprintf(fp, ",\n");
    }
    else
    {
      fprintf(fp, "\n");
    }
  }

  fprintf(fp, "  ]\n}\n");
  fclose(fp);     // Close the file
  free(children); // Free the allocated memory for child process IDs

  return 0;
}