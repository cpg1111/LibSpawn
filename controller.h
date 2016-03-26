#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

  extern int errno;

  typedef struct
  {
    pid_t child;
    pid_t grandChild;
    char* status;
    int code;
    char* args[];
    char* env[];
  } Controller;

  Controller *newController(char* args[], char* env[], char* status)
  {
    Controller ctl = {NULL, NULL, args, env, "spawning", NULL};
    return &ctl;
  }

  int spawn(Controller* ctl)
  {
    pid_t parent = getpid();
    pid_t pid = fork();
    if (pid == -1)
    {
      int errnum = errno;
      perror("could not spawn child process");
      fprintf(stderr, "Error spawning child process %s\n", stderr(errnum));
    }
    else if(pid > 0)
    {
      return 1;
    }
    else
    {
      if(ctl->child == NULL)
      {
        ctl->child = pid;
        return spawn(ctl);
      }
      else if(ctl->grandChild == NULL)
      {
        ctl->grandChild = pid;
        execve(ctl->args[0], ctl->args, ctl->env);
        kill(ctl->child, SIGTERM);
        exit(EXIT_FAILURE);
      }
    }
  }

#endif
