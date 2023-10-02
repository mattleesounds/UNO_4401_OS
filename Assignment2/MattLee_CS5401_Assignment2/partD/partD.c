#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100
#define MSG_TYPE_PARENT 1
#define MSG_TYPE_CHILD 2

struct msgbuf
{
  long mtype;
  char mtext[MSG_SIZE];
};

int main()
{
  int msqid;
  key_t key;
  pid_t pid;
  struct msgbuf msg;

  if ((key = ftok("/tmp", 'b')) == -1)
  {
    perror("ftok");
    exit(1);
  }

  // Message queue
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1)
  {
    perror("msgget error");
    exit(1);
  }

  // Fork
  pid = fork();

  if (pid == -1)
  {
    perror("fork error");
    exit(1);
  }
  else if (pid == 0)
  { // Child Process
    printf("Hello from child process! PID: %d\n", getpid());

    if (msgrcv(msqid, &msg, sizeof(msg.mtext), MSG_TYPE_PARENT, 0) == -1)
    {
      perror("msgrcv child error");
      exit(1);
    }
    printf("Child received: %s\n", msg.mtext);

    printf("Child, please enter your reply: ");
    fgets(msg.mtext, sizeof(msg.mtext), stdin);

    msg.mtype = MSG_TYPE_CHILD;
    if (msgsnd(msqid, &msg, strlen(msg.mtext), 0) == -1)
    {
      perror("msgsnd child error");
      exit(1);
    }

    printf("Child sent the reply.\n");
  }
  else
  { // Parent Process
    printf("Hello from parent process! PID: %d\n", getpid());

    printf("Parent, please enter your message: ");
    fgets(msg.mtext, sizeof(msg.mtext), stdin);

    msg.mtype = MSG_TYPE_PARENT;
    if (msgsnd(msqid, &msg, strlen(msg.mtext), 0) == -1)
    {
      perror("msgsnd parent error");
      exit(1);
    }

    printf("Parent sent the message.\n");

    // Child's reply
    if (msgrcv(msqid, &msg, sizeof(msg.mtext), MSG_TYPE_CHILD, 0) == -1)
    {
      perror("msgrcv parent error");
      exit(1);
    }

    printf("I'm the parent %d!\n", getpid());
    printf("My child says: %s\n", msg.mtext);
  }

  return 0;
}
