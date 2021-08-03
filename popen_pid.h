#ifndef _POPEN_PID_H_
#define _POPEN_PID_H_

#include <stdlib.h>
#include <stdio.h>

FILE * popen_pid(char **args, char type, pid_t* pid);
int pclose_pid(FILE * fp, pid_t pid);

#endif // _POPEN_PID_H_

