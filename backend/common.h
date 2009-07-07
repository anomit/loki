#ifndef COMMON_H
#define COMMON_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>


extern char *server;
extern char *user;
extern char *password;
extern char *database;

extern char *chroot_jail_path;
extern char *source_file_path;
extern char *execfilepath_prefix;
#endif
