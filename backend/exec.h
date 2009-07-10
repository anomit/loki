#ifndef EXEC_H
#define EXEC_H

#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/syscall.h>

void exec();

#endif
