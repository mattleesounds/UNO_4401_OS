#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process
{
  int ProcessID;
  int ParentProcessID;
} Process;

void build_json(Process *list, int size, int parent_id, char *json_output)
{
  strcat(json_output, "[");
  int first = 1;
  for (int i = 0; i < size; i++)
  {
    if (list[i].ParentProcessID == parent_id)
    {
      if (first == 1)
      {
        first = 0;
      }
      else
      {
        strcat(json_output, ",");
      }
      strcat(json_output, "{\"ProcessID\": ");
      char pid[10];
      sprintf(pid, "%d", list[i].ProcessID);
      strcat(json_output, pid);

      strcat(json_output, ", \"ParentProcessID\": ");
      char ppid[10];
      sprintf(ppid, "%d", list[i].ParentProcessID);
      strcat(json_output, ppid);

      strcat(json_output, ", \"Children\": ");
      build_json(list, size, list[i].ProcessID, json_output);
      strcat(json_output, "}");
    }
  }
  strcat(json_output, "]");
}

int main()
{
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  Process list[n];

  for (int i = 0; i < n; i++)
  {
    printf("Enter ProcessID and ParentProcessID for process %d: ", i + 1);
    scanf("%d %d", &list[i].ProcessID, &list[i].ParentProcessID);
  }

  char json_output[1024] = "";
  int root_id = -1; // Assuming -1 is the root parent ID
  build_json(list, n, root_id, json_output);

  printf("JSON output: %s\n", json_output);

  return 0;
}
