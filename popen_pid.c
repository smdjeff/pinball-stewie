////////////////////////////////////////////////////////////////////////////////
// Francesco Boi
//  Sep 5 2019
//  https://stackoverflow.com/questions/26852198/getting-the-pid-from-popen
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include "popen_pid.h"



FILE * popen_pid(char **args, char type, pid_t* pid)
{
    pid_t child_pid;
    int fd[2];
    pipe(fd);

    if((child_pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    /* child process */
    if (child_pid == 0)
    {
        if (type == 'r')
        {
            close(fd[0]);    //Close the READ end of the pipe since the child's fd is write-only
            dup2(fd[1], 1); //Redirect stdout to pipe
        }
        else
        {
            close(fd[1]);    //Close the WRITE end of the pipe since the child's fd is read-only
            dup2(fd[0], 0);   //Redirect stdin to pipe
        }

        setpgid(child_pid, child_pid); //Needed so negative PIDs can kill children of /bin/sh
        execvp(args[0],args);
        exit(0);
    }
    else
    {
        //printf("child pid %d\n", child_pid);
        if (type == 'r')
        {
            close(fd[1]); //Close the WRITE end of the pipe since parent's fd is read-only
        }
        else
        {
            close(fd[0]); //Close the READ end of the pipe since parent's fd is write-only
        }
    }

    *pid = child_pid;

    if (type == 'r')
    {
        return fdopen(fd[0], "r");
    }

    return fdopen(fd[1], "w");
}

int pclose_pid(FILE * fp, pid_t pid)
{
    int stat;

    fclose(fp);
    while (waitpid(pid, &stat, 0) == -1)
    {
        if (errno != EINTR)
        {
            stat = -1;
            break;
        }
    }

    return stat;
}

